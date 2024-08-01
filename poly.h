// ------------------------------------------------ poly.h -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 6/20/2024
// Date of Last Modification: 6/27/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Header file for the Poly class, which represents a polynomial with nonnegative exponents using an array of terms.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
// This file contains the class definition for Poly, including constructors, destructors, operator overloads, accessors, and mutators.
// --------------------------------------------------------------------------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

class Poly {

	friend istream& operator>>(istream& inStream, Poly& inputPoly); // overload >> to input a polynomial
	friend ostream& operator<<(ostream& outStream, Poly& outputPoly); // overload << to output polynomial

public:
	Poly(int coeff = 0, int exp = 0); // default constructor
	Poly(const Poly& copiedPoly); // copy constructor
	~Poly(); // destructor

	Poly& operator=(const Poly&); // Assignment Operator

	Poly operator+(const Poly&) const; // overload operator + function with type "Poly", and constant parameter of reference to Poly object
	Poly operator-(const Poly&) const; //overload operator -
	Poly operator*(const Poly&) const; //overload operator *

	bool operator==(const Poly&) const; //overload operator ==
	bool operator!=(const Poly&) const; //overload operator !=

	Poly& operator+=(const Poly&); //overload assignment operator +=
	Poly& operator-=(const Poly&); //overload assignment operator -=
	Poly& operator*=(const Poly&); //overload assignment operator *=

	int getCoeff(int exp) const; // Accessor for getting the coefficient of a specific exponent
	void setCoeff(int coeff, int exp); // Mutator for setting the coefficient of a specific exponent

private:
	int* terms; // array to store coeff at index exponent
	int size; // size of array terms

	void resize(int newSize); // Helper function to resize the dynamic array when needed
};
