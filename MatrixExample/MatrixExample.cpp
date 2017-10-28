// MatrixExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>

#include "../YAOLAW/la_baseobject.h"
#include "../YAOLAW/matrix.h"


int main()
{
	Matrix<double> A(2, 3);
	Matrix<double> B(3, 2);

	Matrix<double> C;

	for (unsigned int r = 0; r < A.getNRows(); r++)
	{
		for (unsigned int c = 0; c < A.getNCols(); c++)
		{
			A(r, c) = c + r*A.getLeadingDim();
		}
	}

	for (unsigned int r = 0; r < B.getNRows(); r++)
	{
		for (unsigned int c = 0; c < B.getNCols(); c++)
		{
			B(r, c) = c + r*B.getLeadingDim();
		}
	}

	std::cout << std::setprecision(2) << std::scientific;
	std::cout << "A:" << std::endl << A << std::endl;
	std::cout << "B:" << std::endl << B << std::endl;

	C = A * B;

	C += -10.0;

	Matrix<double> D;
	D = C * 100.0;
	Matrix<double> E = D + C;

	std::cout << "A*B:" << std::endl << C << std::endl;
}

