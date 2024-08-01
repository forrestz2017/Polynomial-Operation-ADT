// ------------------------------------------------ poly.cpp -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 6/20/2024
// Date of Last Modification: 6/27/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implementation file for the Poly class, which represents a polynomial with nonnegative exponents using an array of terms.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions.
// This file contains the implementations of the Poly class member functions, including constructors, destructors, operator overloads, accessors, and mutators.
// --------------------------------------------------------------------------------------------------------------------

#include "poly.h"
#include <algorithm>
#include <cstring>

// Constructor
Poly::Poly(int coeff, int exp) {
	size = exp + 1;
	terms = new int[size](); // Array is initialized to zero
	terms[exp] = coeff;
}

// Copy Constructor
Poly::Poly(const Poly& copiedPoly) : size(copiedPoly.size) {
	terms = new int[size]; // Allocate memory for array that "terms" points to
	std::copy(copiedPoly.terms, copiedPoly.terms + size, terms); // Source: copiedPoly.terms, Destination: terms
}

// Destructor
Poly::~Poly() {
	delete[] terms;
}

// Assignment Operator
Poly& Poly::operator=(const Poly& rhs) {
	if (this != &rhs) { // Avoid self-assignment
		delete[] terms; // Delete the existing array
		size = rhs.size; // Copy the size
		terms = new int[size]; // Allocate new memory
		std::copy(rhs.terms, rhs.terms + size, terms); // Copy the coefficients
	}
	return *this;
}

// Addition Operator
Poly Poly::operator+(const Poly& rhs) const {
	int newSize = std::max(size, rhs.size); // Determine the size of the result array
	Poly result(0, newSize - 1); // Create result object with coeff = 0 and exp = newSize - 1
	for (int i = 0; i < newSize; ++i) {
		if (i < size) result.terms[i] += terms[i]; // Add coefficients from the left-hand side
		if (i < rhs.size) result.terms[i] += rhs.terms[i]; // Add coefficients from the right-hand side
	}
	return result;
}

// Subtraction Operator
Poly Poly::operator-(const Poly& rhs) const {
	int newSize = std::max(size, rhs.size); // Determine the size of the result array
	Poly result(0, newSize - 1); // Create a result Poly object
	for (int i = 0; i < newSize; ++i) {
		if (i < size) result.terms[i] += terms[i]; // Add coefficients from the left-hand side
		if (i < rhs.size) result.terms[i] -= rhs.terms[i]; // Subtract coefficients from the right-hand side
	}
	return result;
}

// Multiplication Operator
Poly Poly::operator*(const Poly& rhs) const {
	int newSize = size + rhs.size - 1; // Determine the size of the result array
	Poly result(0, newSize - 1); // Create a result Poly object
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < rhs.size; ++j) {
			result.terms[i + j] += terms[i] * rhs.terms[j]; // Multiply coefficients and add to the result
		}
	}
	return result;
}

// Compound Assignment Operator +=
Poly& Poly::operator+=(const Poly& rhs) {
	*this = *this + rhs; // Use the addition operator
	return *this;
}

// Compound Assignment Operator -=
Poly& Poly::operator-=(const Poly& rhs) {
	*this = *this - rhs; // Use the subtraction operator
	return *this;
}

// Compound Assignment Operator *=
Poly& Poly::operator*=(const Poly& rhs) {
	*this = *this * rhs;
	return *this;
}

// Equality Operator
bool Poly::operator==(const Poly& rhs) const {
	if (size != rhs.size) return false; // If sizes are different, they are not equal
	for (int i = 0; i < size; ++i) {
		if (terms[i] != rhs.terms[i]) return false; // Check each coefficient
	}
	return true;
}

// Inequality Operator
bool Poly::operator!=(const Poly& rhs) const {
	return !(*this == rhs); // Use the equality operator
}

// Accessor for Getting Coefficient
int Poly::getCoeff(int exp) const {
	if (exp < 0 || exp >= size) return 0; // Return 0 if the exponent is out of range
	return terms[exp];
}

// Mutator for Setting Coefficient
void Poly::setCoeff(int coeff, int exp) {
	if (exp >= size) {
		resize(exp + 1); // Resize the array if the exponent is out of the current range
	}
	terms[exp] = coeff; // Set the coefficient
}

// Resize Function
void Poly::resize(int newSize) {
	int* newCoefficients = new int[newSize](); // Allocate new memory
	std::copy(terms, terms + std::min(size, newSize), newCoefficients); // Copy existing coefficients
	delete[] terms; // Delete the old array
	terms = newCoefficients; // Update the coefficients pointer
	size = newSize; // Update the size
}

// Overload >> Operator for Input
std::istream& operator>>(std::istream& inStream, Poly& inputPoly) {
	int coeff, exp;
	while (true) {
		inStream >> coeff >> exp; // Read coefficient and exponent pairs
		if (coeff == -1 && exp == -1) break; // Terminate on -1 -1
		inputPoly.setCoeff(coeff, exp); // Set the coefficient
	}
	return inStream;
}

// Overload << Operator for Output
std::ostream& operator<<(std::ostream& outStream, Poly& outputPoly) {
	bool first = true;
	for (int i = outputPoly.size - 1; i >= 0; --i) {
		if (outputPoly.terms[i] != 0) {
			if (!first) outStream << " "; // Add a space between terms
			if (outputPoly.terms[i] > 0 && !first) outStream << "+";
			outStream << outputPoly.terms[i]; // Output the coefficient
			if (i > 0) outStream << "x"; // Output x for non-zero exponents
			if (i > 1) outStream << "^" << i; // Output the exponent if greater than 1
			first = false;
		}
	}
	if (first) outStream << "0"; // Output 0 if all coefficients are zero
	return outStream;
}
