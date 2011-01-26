#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include "IntList.h"

#define TYPE int

class BigInt 
{
public :
     IntList * list;
     char sign;
     BigInt();
     BigInt(const BigInt&);
     BigInt& operator =(const BigInt &);
     const BigInt operator +(const BigInt &);
     const BigInt operator -(const BigInt &);
     const BigInt operator *(const BigInt &);
     const BigInt operator *(TYPE);
     void flip_sign();
     void trim_zeroes();
     friend std::ostream& operator<< (std::ostream&, BigInt&);
};

BigInt bigint_from_string(std::string);

#endif
