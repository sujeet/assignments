/////////////////////////////////////////////////////////////////////////////////////////
// roll number                    : cs09b010                                           //
// name                           : sujeet gholap <sujeetgholap@gmail.com>             //
// aim                            : to implement a class BigInt to handle big integers //
/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "IntList.h"
#include "BigInt.h"

#define WIDTH 4 
#define BASE 10000    
#define TYPE int

using namespace std;

BigInt::BigInt()
{
     this->sign = '+';
     this->list = new IntList();
}

BigInt::BigInt(const BigInt& num)
{
     IntList * new_list = new IntList(*(num.list));
     this->sign = num.sign;
     this->list = new_list;
}

BigInt& BigInt::operator =(const BigInt& num)
{
     if (this == &num) return *this;
     else {
          this->list->clear();
          delete this->list;
          IntList * new_list = new IntList(*(num.list));
          this->sign = num.sign;
          this->list = new_list;
          return *this;
     }
}
     
void BigInt::flip_sign()
{
     if (this->sign == '-') this->sign = '+';
     else this->sign = '-';
}

void BigInt::trim_zeroes()
{
     TYPE digit = this->list->pop_back();
     while ((digit == 0)&&(this->list->length() > 1)) {
          digit = this->list->pop_back();
     }
     this->list->push_back(digit);
}

ostream& operator<< (ostream& out, BigInt& num)
{
     IntList * temp = new IntList(*(num.list));
     if (num.sign == '-') out << '-';
     if (temp->length() > 0) {
          out << temp->pop_back();
     }
     for (int i = temp->length(); i > 0; i--){
          // in first run, print the most significant
          // part of the bigint, then output the subsequent
          // parts in a fixed width mode
          out << setfill('0') << setw(WIDTH);
     	  out << temp->pop_back();
     }
     return out;
}

BigInt add_bigints_sorted(const BigInt& shorter, const BigInt& longer)
{
     IntList::Iterator answer_iter, short_iter, long_iter;
     BigInt answer;
     TYPE carry = 0;
     TYPE sum;
     short_iter = shorter.list->begin();
     long_iter = longer.list->begin();
     answer_iter = answer.list->begin();
     for (unsigned int i = 0; i < shorter.list->length(); i++) {
          sum = *short_iter + *long_iter + carry ;
          answer.list->insert_after(answer_iter, sum%BASE);
          if (i != 0 ) answer_iter ++;
          carry = sum / BASE;
          short_iter ++;
          long_iter ++;
     }
     while (long_iter != longer.list->end()) {
          sum = *long_iter + carry;
          answer.list->insert_after(answer_iter, sum%BASE);
          carry = sum / BASE;
          answer_iter ++;
          long_iter ++;
     }
     if (carry != 0) {
          answer.list->insert_after(answer_iter, carry);
     }
     answer.sign = shorter.sign;
     answer.trim_zeroes();
     return answer;
}

BigInt add_bigints(const BigInt& num1, const BigInt& num2)
{
     // note that by add, we mean that the sum of
     // the magnitudes of the two numbers is to be 
     // calculated.
     if (num1.list->length() < num2.list->length()) {
          return add_bigints_sorted(num1, num2);
     }
     else return add_bigints_sorted(num2, num1);
}

BigInt subtract_bigints_sorted(const BigInt& smaller, const BigInt& bigger)
{
     // smaller and bigger in terms of magnitude, not value
     IntList::Iterator answer_iter, small_iter, big_iter;
     BigInt answer;
     TYPE borrow = 0;
     TYPE difference;
     small_iter = smaller.list->begin();
     big_iter = bigger.list->begin();
     answer_iter = answer.list->begin();
     for (unsigned int i = 0; i < smaller.list->length(); i++) {
          difference = *big_iter - ( *small_iter + borrow );
          if ( difference < 0 ) {
               difference = BASE + difference;
               borrow = 1;
          }
          answer.list->insert_after(answer_iter, difference);
          if (i != 0) answer_iter ++;
          small_iter ++;
          big_iter ++;
     }
     while (big_iter != bigger.list->end()) {
          difference = *big_iter - borrow;
          if ( difference < 0 ) {
               difference = BASE + difference;
               borrow = 1;
          }
          answer.list->insert_after(answer_iter, difference);
          answer_iter ++;
          big_iter ++;
     }
     answer.sign = bigger.sign;
     answer.trim_zeroes();
     return answer;
}
     
BigInt subtract_bigints(const BigInt& num1, const BigInt& num2)
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
          TYPE int1 = list1.pop_back();
          TYPE int2 = list2.pop_back();
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

const BigInt BigInt::operator +(const BigInt& num)
{
     if (this->sign == num.sign) return add_bigints(*this, num);
     else return subtract_bigints(*this, num);
}

const BigInt BigInt::operator -(const BigInt& num)
{
     BigInt negative = num;
     negative.flip_sign();
     return (*this + negative);
}

BigInt multiply_bigint_by_positive_number(const BigInt& bigint, TYPE number)
{
     BigInt answer;
     IntList::Iterator ans_iter = answer.list->begin();
     IntList::Iterator iter = bigint.list->begin();
     TYPE carry = 0;
     TYPE product;
     for (unsigned int i = 0; i < bigint.list->length(); i++) {
          product = ( (*iter) * number ) + carry;
          answer.list->insert_after(ans_iter, product%BASE);
          carry = product / BASE;
          if (i != 0) ans_iter ++;
          iter++;
     }
     if (carry != 0) {
          answer.list->insert_after(ans_iter, carry);
     }
     answer.trim_zeroes();
     answer.sign = bigint.sign;
     return answer;
}
     
const BigInt BigInt::operator *(const BigInt& num)
{
     IntList::Iterator iter2 = num.list->begin();
     BigInt product, answer;
     answer.list->push_front(0); // left shift
     for (unsigned int i = 0; i < num.list->length(); i++){
          product = multiply_bigint_by_positive_number(*this, *iter2);
          for (unsigned int j = 0; j < i; j++) {
               product.list->push_front(0);
          }
          iter2 ++;
          answer = add_bigints(answer, product);
     }
     answer.trim_zeroes();
     if (this->sign != num.sign) answer.sign = '-';
     return answer;
}

BigInt bigint_from_string(string str)
{
     BigInt num;
     IntList::Iterator iter = num.list->begin();
     string substring;
     TYPE value;
     if (str[0] == '-') {
          num.sign = '-';
          str.erase(0, 1);
     }
     unsigned int str_length = str.length();
     for (unsigned int i = 0; i < str_length/WIDTH; i++) {
          substring = str.substr(str.length() - WIDTH);
          str.erase(str.length() - WIDTH);
          value = (TYPE) atol(substring.c_str());
          num.list->insert_after(iter, value);
          if (i != 0) iter++;
     }
     if (str.length() != 0) {
          value = (TYPE) atoi(str.c_str());
          num.list->insert_after(iter, value);
     }
     return num;
}
