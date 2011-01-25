/////////////////////////////////////////////////////////////////////////////////////////
// roll number                    : cs09b010                                           //
// name                           : sujeet gholap <sujeetgholap@gmail.com>             //
// aim                            : to implement a class BigInt to handle big integers //
/////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "bigint.h"

using namespace std;

istream * in;
ostream * out;
const char END_COMMAND = 'q';
const char ENDCHAR = '$';

string read_bigint_string()
{
     string bigint_str;
     char digit;
     *in >> digit;
     if (digit == '-') {
          bigint_str.push_back(digit);
     }
     while (digit == '0') {
          *in >> digit;
     }
     while (digit != ENDCHAR) {
          if ((digit <= '9')&&(digit >= '0')) {
               bigint_str.push_back(digit);
          }
          *in >> digit;
     }
     return bigint_str;
}
          
void do_operation(char oper, int& counter)
{
     switch (oper) {
     case '+' :
     {
          *out << counter << endl;
          counter ++;
          time_t start_time = time(NULL);
          BigInt num1 = bigint_from_string( read_bigint_string() );
          BigInt num2 = bigint_from_string( read_bigint_string() );
          BigInt ans;
          if ( num1.sign == num2.sign ) ans = add_bigints(num1, num2);
          else ans = subtract_bigints(num1, num2);
          time_t end_time = time(NULL);
          *out << difftime(end_time, start_time) << 's' << endl;
          *out << ans << ENDCHAR << endl;
          break;
     }
     case '-' :
     {
          *out << counter << endl;
          counter ++;
          time_t start_time = time(NULL);
          BigInt num = bigint_from_string( read_bigint_string() );
          num.flip_sign();
          time_t end_time = time(NULL);
          *out << difftime(end_time, start_time) << 's' << endl;
          *out << num << ENDCHAR << endl;
          break;
     }
     case '*' :
     {
          *out << counter << endl;
          counter ++;
          time_t start_time = time(NULL);
          BigInt num1 = bigint_from_string( read_bigint_string() );
          BigInt num2 = bigint_from_string( read_bigint_string() );
          BigInt ans = multiply_bigints(num1, num2);
          time_t end_time = time(NULL);
          *out << difftime(end_time, start_time) << 's' << endl;
          *out << ans << ENDCHAR << endl;
          break;
     }
     case '!' :
     {
          *out << counter << endl;
          counter ++;
          time_t start_time = time(NULL);
          // not decided yet
          time_t end_time = time(NULL);
          *out << difftime(end_time, start_time) << 's' << endl;
     }
     }
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

int main( int argc, char ** argv)
{
     ifstream input;
     ofstream output;
     int counter = 1;
     initiate_io(argc, argv, in, out, input, output);
     // now use *in and *out normally as you would use cin and cout
     char oper;                 // operator is a keyword and I can't think of a better word than oper
     *in >> oper;
     while (oper != END_COMMAND) {
          do_operation(oper, counter);
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
