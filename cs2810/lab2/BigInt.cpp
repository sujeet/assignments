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

#ifndef WIDTH
#define WIDTH 4 
#endif

#ifndef BASE
#define BASE 10000
#endif    

#ifndef TYPE
#define TYPE int
#endif

using namespace std;

BigInt::~BigInt()
{
     this->list->clear();
     delete this->list;
}

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

BigInt::BigInt (TYPE num)
{
     this->list = new IntList();
     if (num >= 0) {
          this->sign = '+';
     }
     else {
          this->sign = '-';
          num = 0 - num;
     }
     IntList::Iterator iter = this->list->begin();
     TYPE value;
     if (num == 0) {
          this->list->insert_after(iter, 0);
     }
     else {
          for (int i = 0; num > 0; i++) {
               value = num % BASE;
               num = num / BASE;
               this->list->insert_after(iter, value);
               if (i != 0) ++iter;
          }
     }
     
}

BigInt::BigInt (string str)
{
     this->list = new IntList();
     this->sign = '+';
     IntList::Iterator iter = this->list->begin();
     string substring;
     TYPE value;
     if (str[0] == '-') {
          this->sign = '-';
          str.erase(0, 1);
     }
     unsigned int str_length = str.length();
     for (unsigned int i = 0; i < str_length/WIDTH; i++) {
          substring = str.substr(str.length() - WIDTH);
          str.erase(str.length() - WIDTH);
          value = (TYPE) atol(substring.c_str());
          this->list->insert_after(iter, value);
          if (i != 0) ++iter;
     }
     if (str.length() != 0) {
          value = (TYPE) atol(str.c_str());
          this->list->insert_after(iter, value);
     }
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
     
BigInt& BigInt::operator =(string str)
{
     BigInt bigint(str);
     return (this->operator=(bigint));
}
BigInt& BigInt::operator =(TYPE num)
{
     BigInt bigint(num);
     return (this->operator=(bigint));
}
     
void BigInt::flip_sign()
{
     if (this->sign == '-') this->sign = '+';
     else this->sign = '-';
}

void BigInt::trim_zeroes()
{
     TYPE digit = this->list->pop_back();
     while ((digit == 0)&&(this->list->length() > 0)) {
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
     // This function is not supposed to be used directly
     // it is a helper function of add_bigints

     // note that, shorter and longer basically denote the bigint list length
     // it is assumed that both the numbers have same sign
     // hence only their magnitudes are added
     IntList::Iterator answer_iter, short_iter, long_iter;
     BigInt answer;
     TYPE carry = 0;
     TYPE sum;
     short_iter = shorter.list->begin();
     long_iter = longer.list->begin();
     answer_iter = answer.list->begin();
     unsigned int shorter_length = shorter.list->length();
     for (unsigned int i = 0; i < shorter_length; i++) {
          sum = *short_iter + *long_iter + carry ;
          answer.list->insert_after(answer_iter, sum%BASE);
          if (i != 0 ) ++answer_iter;
          carry = sum / BASE;
          ++short_iter;
          ++long_iter;
     }
     IntList::Iterator null_iter; // this is same as one returned by list.end()
     while (long_iter != null_iter) {
          sum = *long_iter + carry;
          answer.list->insert_after(answer_iter, sum%BASE);
          carry = sum / BASE;
          ++answer_iter;
          ++long_iter;
     }
     if (carry != 0) {
          answer.list->insert_after(answer_iter, carry);
     }
     answer.sign = shorter.sign;
     // assuming that both the numbers have been trimmed of 
     // their zeroes already, the answer need not be trimmed
     // of its zeroes
     return answer;
}

BigInt add_bigints(BigInt& num1, BigInt& num2)
{
     // This function is not supposed to be used directly
     // it is helper function of the operator +

     // note that by add, we mean that the sum of
     // the magnitudes of the two numbers is to be 
     // calculated.

     // as the function is never called directly, and
     // care is taken to trim zeroes of both the bigints,
     // no need to trim zeroes
     if (num1.list->length() < num2.list->length()) {
          return add_bigints_sorted(num1, num2);
     }
     else return add_bigints_sorted(num2, num1);
}

BigInt subtract_bigints_sorted(const BigInt& smaller, const BigInt& bigger)
{
     // This function is not supposed to be used directly
     // it is helper function of the function subtract_bigints

     // smaller and bigger in terms of magnitude, not value.
     // note that this 'sortedness' is different from the 
     // one in add_bigints_sorted()
     IntList::Iterator answer_iter, small_iter, big_iter;
     BigInt answer;
     TYPE borrow = 0;
     TYPE difference;
     small_iter = smaller.list->begin();
     big_iter = bigger.list->begin();
     answer_iter = answer.list->begin();

     // note that smaller is also shorter
     unsigned int smaller_length = smaller.list->length();
     for (unsigned int i = 0; i < smaller_length; i++) {
          difference = *big_iter - ( *small_iter + borrow );
          if ( difference < 0 ) {
               difference = BASE + difference;
               borrow = 1;
          }
          answer.list->insert_after(answer_iter, difference);
          if (i != 0) ++answer_iter;
          ++small_iter;
          ++big_iter;
     }
     IntList::Iterator null_iter; // this is same as one returned by list.end()
     while (big_iter != null_iter) {
          difference = *big_iter - borrow;
          if ( difference < 0 ) {
               difference = BASE + difference;
               borrow = 1;
          }
          answer.list->insert_after(answer_iter, difference);
          ++answer_iter;
          ++big_iter;
     }
     answer.sign = bigger.sign;
     answer.trim_zeroes();
     return answer;
}

BigInt subtract_bigints(BigInt& num1, BigInt& num2)
{
     // This function is not supposed to be used directly
     // it is helper function of the operator +

     // note that by subtract, we mean the difference 
     // between the magnitudes of the two numbers has
     // to be calculated.

     // as the function is never called directly, and
     // care is taken to trim zeroes of both the bigints,
     // no need to trim zeroes
     if (num1.list->length() < num2.list->length()) {
          return subtract_bigints_sorted(num1, num2);
     }
     else if (num2.list->length() < num1.list->length()) {
          return subtract_bigints_sorted(num2, num1);
     }
     else {
          IntList list1(*(num1.list));
          IntList list2(*(num2.list));
          TYPE int1 = list1.pop_back();
          TYPE int2 = list2.pop_back();
          while ((int1 == int2)&&(list1.length() > 0)) {
               int1 = list1.pop_back();
               int2 = list2.pop_back();
          }
          if ((list1.length() == 0) && (int1 == int2)) {
               // the second condition above is for the cases
               // when there is only one 'digit' in the bigint
               BigInt ans(0);
               return ans;
          }
          else if (int1 > int2) {
               return subtract_bigints_sorted(num2, num1);
          }
          else {
               return subtract_bigints_sorted(num1, num2);
          }
     }
}
     
ComparisonResult BigInt::compare_magnitude_with(BigInt& num)
{
     // This function is not supposed to be used directly
     // it is helper function 

     // as the function is never called directly,
     // care must be taken to trim zeroes by the caller
     if (this->list->length() < num.list->length())
          return IS_SMALLER;
     if (this->list->length() > num.list->length())
          return IS_GREATER;
     
     IntList list1(*(this->list));
     IntList list2(*(num.list));
     TYPE int1 = list1.pop_back();
     TYPE int2 = list2.pop_back();
     while ((int1 == int2)&&(list1.length() > 0)) {
          int1 = list1.pop_back();
          int2 = list2.pop_back();
     }
     if ((list1.length() == 0) && (int1 == int2))
          // the second condition above is for the cases
          // when there is only one 'digit' in the bigint
          return IS_EQUAL;
     else if (int1 > int2)
          return IS_GREATER;
     else
          return IS_SMALLER;
}

bool BigInt::operator ==(BigInt& num)
{
     if (this->sign != num.sign) 
          return false;
     else {
          this->trim_zeroes();
          num.trim_zeroes();
          return (this->compare_magnitude_with(num) == IS_EQUAL);
     }
}

bool BigInt::operator <(BigInt& num)
{
     if ((this->sign == '+')&&(num.sign == '-'))
          return false;
     if ((this->sign == '-')&&(num.sign == '+'))
          return true;
     if (*this == num)
          return false;
     this->trim_zeroes();
     num.trim_zeroes();
     if (this->sign == '-')
          return ( this->compare_magnitude_with(num) == IS_GREATER );
     else 
          return ( this->compare_magnitude_with(num) == IS_SMALLER );
}

bool BigInt::operator >(BigInt& num)
{
     return (! ( (*this == num)|| (*this < num)) );
}

bool BigInt::operator <=(BigInt& num)
{
     return ( ! (*this > num) );
}

bool BigInt::operator >=(BigInt& num)
{
     return ( ! (*this < num) );
}

bool BigInt::operator ==(TYPE num)
{
     BigInt bigint(num);
     return (*this == bigint);
}

bool BigInt::operator <(TYPE num)
{
     BigInt bigint(num);
     return (*this < bigint);
}

bool BigInt::operator >(TYPE num)
{
     BigInt bigint(num);
     return (*this > bigint);
}

bool BigInt::operator <=(TYPE num)
{
     BigInt bigint(num);
     return (*this <= bigint);
}

bool BigInt::operator >=(TYPE num)
{
     BigInt bigint(num);
     return (*this >= bigint);
}

const BigInt BigInt::operator +(BigInt& num)
{
     this->trim_zeroes();
     num.trim_zeroes();
     if (this->sign == num.sign) return add_bigints(*this, num);
     else return subtract_bigints(*this, num);
}

const BigInt BigInt::operator +(TYPE num)
{
     BigInt bigint(num);
     return *this + bigint;
}

BigInt BigInt::operator ++(int foo)
{
     // postfix : increment, return old one
     BigInt old(*this);
     *this = *this + 1;
     return old;
}

BigInt BigInt::operator ++()
{
     // prefix : increment, return incremented
     *this = *this + 1;
     return *this;
}

const BigInt BigInt::operator -(BigInt& num)
{
     BigInt negative = num;
     negative.flip_sign();
     return (*this + negative);
}

const BigInt BigInt::operator -(TYPE num)
{
     BigInt bigint(num);
     return *this - bigint;
}

BigInt BigInt::operator --(int foo)
{
     // postfix : decrement, return old one
     BigInt old(*this);
     *this = *this - 1;
     return old;
}

BigInt BigInt::operator --()
{
     // prefix : decrement, return decremented
     *this = *this - 1;
     return *this;
}

BigInt multiply_bigint_by_positive_number(const BigInt& bigint, TYPE number)
{
     BigInt answer;
     IntList::Iterator ans_iter = answer.list->begin();
     IntList::Iterator iter = bigint.list->begin();
     TYPE carry = 0;
     TYPE product;
     unsigned int length_of_bigint = bigint.list->length();
     for (unsigned int i = 0; i < length_of_bigint; i++) {
          product = ( (*iter) * number ) + carry;
          answer.list->insert_after(ans_iter, product%BASE);
          carry = product / BASE;
          if (i != 0) ++ans_iter;
          ++iter;
     }
     if (carry != 0) {
          answer.list->insert_after(ans_iter, carry);
     }
     answer.sign = bigint.sign;
     return answer;
}
     
const BigInt BigInt::operator *(BigInt& num)
{
     IntList::Iterator iter2 = num.list->begin();
     num.trim_zeroes();
     this->trim_zeroes();
     BigInt product;
     BigInt answer(0);
     unsigned int num_length = num.list->length();
     for (unsigned int i = 0; i < num_length; i++){
          product = multiply_bigint_by_positive_number(*this, *iter2);
          for (unsigned int j = 0; j < i; j++) {
               product.list->push_front(0); // push left
          }
          ++iter2;
          answer = answer + product;
     }
     if (this->sign != num.sign) answer.sign = '-';
     return answer;
}

const BigInt BigInt::operator *(TYPE num)
{
     this->trim_zeroes();
     if ( num < 0 ) {
          BigInt ans = multiply_bigint_by_positive_number(*this, (0-num));
          ans.flip_sign();
          return ans;
     }
     else {
          return multiply_bigint_by_positive_number(*this, num);
     }
}

