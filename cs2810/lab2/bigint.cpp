/////////////////////////////////////////////////////////////////////////////////////////
// roll number                    : cs09b010                                           //
// name                           : sujeet gholap <sujeetgholap@gmail.com>             //
// aim                            : to implement a class BigInt to handle big integers //
/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "intlist.h"

using namespace std;

istream * in;
ostream * out;
const char END_COMMAND = 'q';
const char ENDCHAR = '$';


class BigInt 
{
public :
     IntList * list;
     char sign;
     BigInt();
     void flip_sign();
     void trim_zeroes();
     void print(ostream *);
};

BigInt::BigInt()
{
     this->sign = '+';
     this->list = new IntList();
}

void BigInt::flip_sign()
{
     if (this->sign == '-') this->sign = '+';
     else this->sign = '-';
}

void BigInt::trim_zeroes()
{
     int digit = this->list->pop_back();
     while (digit == 0) {
	  digit = this->list->pop_back();
     }
     this->list->push_back(digit);
}

void BigInt::print(ostream * out = &cout)
{
     IntList * temp = new IntList(*(this->list));
     if (this->sign == '-') *out << '-';
     for (int i = temp->length(); i > 0; i--){
     	  *out << temp->pop_back();
     }
     *out << endl;
}

void initiate_io(int argc, char ** argv, istream *& in, ostream *& out, ifstream& input, ofstream& output)
{
     // function which sets *in and *out according to the commandline arguments
     switch (argc) {
     case 1 :
     {
          in = &cin;
          out = &cout;
          break;
     }
     case 2 :
     {
          input.open(argv[1]);
          in = &input;
          out = &cout;
          break;
     }
     case 3:
     {
          input.open(argv[1]);
          output.open(argv[2]);
          in = &input;
          out = &output;
          break;
     }
     default :
          cerr << "ERROR : Too many arguments." << endl;
          exit (-1);
     }
}

void shut_down_io(int argc, char ** argv, istream *& in, ostream *& out, ifstream& input, ofstream& output)
{
     switch (argc) {
     case 1 :
     {
          break;
     }
     case 2 :
     {
          input.close();
          break;
     }
     case 3:
     {
          input.close();
          output.close();                 
          break;
     }
     }
}

BigInt add_bigints_sorted(BigInt shorter, BigInt longer)
{
     IntList::Iterator short_iter, long_iter;
     BigInt answer;
     int carry = 0;
     int sum;
     short_iter = shorter.list->begin();
     long_iter = longer.list->begin();
     for (unsigned int i = 0; i < shorter.list->length(); i++) {
	  sum = *short_iter + *long_iter + carry ;
	  answer.list->push_back( sum%10 );
	  carry = sum / 10;
	  short_iter ++;
	  long_iter ++;
     }
     while (long_iter != longer.list->end()) {
	  sum = *long_iter + carry;
	  answer.list->push_back( sum%10 );
	  carry = sum / 10;
	  long_iter ++;
     }
     if (carry != 0) {
	  answer.list->push_back(carry);
     }
     answer.sign = shorter.sign;
     answer.trim_zeroes();
     return answer;
}

BigInt add_bigints(BigInt num1, BigInt num2)
{
     // note that by add, we mean that the sum of
     // the magnitudes of the two numbers is to be 
     // calculated.
     if (num1.list->length() < num2.list->length()) {
	  return add_bigints_sorted(num1, num2);
     }
     else return add_bigints_sorted(num2, num1);
}

BigInt subtract_bigints_sorted(BigInt smaller, BigInt bigger)
{
     // smaller and bigger in terms of magnitude, not value
     IntList::Iterator small_iter, big_iter;
     BigInt answer;
     int borrow = 0;
     int difference;
     small_iter = smaller.list->begin();
     big_iter = bigger.list->begin();
     for (unsigned int i = 0; i < smaller.list->length(); i++) {
	  difference = *big_iter - ( *small_iter + borrow );
	  if ( difference < 0 ) {
	       difference = 10 + difference;
	       borrow = 1;
	  }
	  answer.list->push_back( difference );
	  small_iter ++;
	  big_iter ++;
     }
     while (big_iter != bigger.list->end()) {
	  difference = *big_iter - borrow;
	  if ( difference < 0 ) {
	       difference = 10 + difference;
	       borrow = 1;
	  }
	  answer.list->push_back( difference );
	  big_iter ++;
     }
     answer.sign = bigger.sign;
     answer.trim_zeroes();
     return answer;
}

     
BigInt subtract_bigints(BigInt num1, BigInt num2)
{
     // note that by subtract, we mean the difference 
     // between the magnitudes of the two numbers has
     // to be calculated.
     if (num1.list->length() < num2.list->length()) {
	  return subtract_bigints_sorted(num1, num2);
     }
     if (num2.list->length() < num1.list->length()) {
	  return subtract_bigints_sorted(num2, num1);
     }
     else {
	  IntList list1(*(num1.list));
	  IntList list2(*(num2.list));
	  int int1 = list1.pop_back();
	  int int2 = list2.pop_back();
	  while (int1 == int2) {
	       int1 = list1.pop_back();
	       int2 = list2.pop_back();
	  }
	  if (int1 < int2) {
	       return subtract_bigints_sorted(num1, num2);
	  }
	  else return subtract_bigints_sorted(num2, num1);
     }
}

BigInt multiply_bigints(BigInt num1, BigInt num2)
{
     cout << "multiplying the two..." << endl;
     return num1;
}

BigInt read_bigint()
{
     char digit;
     BigInt num;
     *in >> digit;
     if (digit == '-') {
          num.sign = '-';
          *in >> digit;
     }
     while (digit == '0') {
	  *in >> digit;
     }
     while (digit != ENDCHAR) {
          if ((digit <= '9')&&(digit >= '0')) {
	       num.list->push_front(int(digit - 48));
          }
          *in >> digit;
     }
     return num;
}
          
void do_operation(char oper)
{
     switch (oper) {
     case '+' :
     {
          BigInt num1 = read_bigint();
          BigInt num2 = read_bigint();
          BigInt ans;
          if ( num1.sign == num2.sign ) ans = add_bigints(num1, num2);
          else ans = subtract_bigints(num1, num2);
	  ans.print(out);
	  break;
     }
     case '-' :
     {
          BigInt num = read_bigint();
	  num.flip_sign();
	  num.print(out);
	  break;
     }
     case '*' :
     {
          BigInt num1 = read_bigint();
          BigInt num2 = read_bigint();
          BigInt ans = multiply_bigints(num1, num2);
	  ans.print(out);
	  break;
     }
     case '!' :
     {
          // not decided yet
     }
     }
}


int main( int argc, char ** argv)
{
     ifstream input;
     ofstream output;
     initiate_io(argc, argv, in, out, input, output);
     // now use *in and *out normally as you would use cin and cout
     char oper;                 // operator is a keyword and I can't think of a better word than oper
     *in >> oper;
     while (oper != END_COMMAND) {
          do_operation(oper);
          if (!(in->eof())){
               *in >> oper;
          }
          if (in->eof()) {
	       break;
	  }
     }

     shut_down_io(argc, argv, in, out, input, output);
     return 0;
}
