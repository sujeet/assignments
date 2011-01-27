#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include "IntList.h"

#ifndef TYPE
#define TYPE int
#endif

enum ComparisonResult
{
     IS_SMALLER,
     IS_EQUAL,
     IS_GREATER
};
     
class BigInt 
{
public :
     IntList * list;
     char sign;
private :
     ComparisonResult compare_magnitude_with(BigInt&);
public :
     /* constructors */
     BigInt();
     BigInt(const BigInt&);
     BigInt(std::string);
     BigInt(TYPE);

     /* operator overloads */
     BigInt& operator =(const BigInt &);
     BigInt& operator =(std::string);
     BigInt& operator =(TYPE);
     const BigInt operator +(BigInt &);
     const BigInt operator -(BigInt &);
     const BigInt operator *(BigInt &);
     const BigInt operator +(TYPE);
     const BigInt operator -(TYPE);
     const BigInt operator *(TYPE);
     bool operator ==(BigInt&);
     bool operator <(BigInt&);
     bool operator >(BigInt&);
     bool operator <=(BigInt&);
     bool operator >=(BigInt&);
     bool operator ==(TYPE);
     bool operator <(TYPE);
     bool operator >(TYPE);
     bool operator <=(TYPE);
     bool operator >=(TYPE);
     
     BigInt operator ++();
     BigInt operator --();
     BigInt operator ++(int);
     BigInt operator --(int);
     friend std::ostream& operator<< (std::ostream&, BigInt&);

     /* misc functions */
     void flip_sign();
     void trim_zeroes();

     /* destructor */
     ~BigInt();
};

#endif
