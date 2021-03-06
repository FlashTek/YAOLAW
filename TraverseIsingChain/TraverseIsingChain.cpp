// TraverseIsingChain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <complex>
#include <iostream>
#include <iomanip>
#include "../YAOLAW/la_baseobject.h"
#include "../YAOLAW/matrix.h"
#include "../YAOLAW/MatrixUtility.h"

using cdouble = std::complex<double>;

LA::Matrix<cdouble> spinX = LA::Matrix<cdouble>(2, 2);
LA::Matrix<cdouble> spinY = LA::Matrix<cdouble>(2, 2);
LA::Matrix<cdouble> spinZ = LA::Matrix<cdouble>(2, 2);

void setupSpinMatrices()
{
	spinX(0, 1) = 1.0;
	spinX(1, 0) = 1.0;

	spinY(0, 1) = cdouble(0, 1);
	spinY(1, 0) = cdouble(0, -1);

	spinZ(0, 0) = 1;
	spinZ(1, 1) = -1;

	spinX *= 1 / 2.0;
	spinY *= 1 / 2.0;
	spinZ *= 1 / 2.0;
}

LA::Matrix<cdouble> getSpin(LA::Matrix<cdouble>& elementarySpinMatrix, size_t L, size_t i)
{
	LA::Matrix<cdouble> identity = LA::Matrix<cdouble>::identity(2);
	LA::Matrix<cdouble> result;

	if (i > 1)
	{
		result = LA::Matrix<cdouble>::identity(2);
		for (int j = 0; j < (int)i - 2; j++)
			result = result.directProduct(identity);
		result = result.directProduct(elementarySpinMatrix);
	}
	else
	{
		result = elementarySpinMatrix;
	}

	for (int j = 0; j < (int)L - (int)i; j++)
		result = result.directProduct(identity);

	return result;
}

LA::Matrix<cdouble> createHamiltonian(size_t L, double h);

LA::Matrix<cdouble> createHamiltonian(size_t L, double h)
{
	LA::Matrix<cdouble> hamilton = LA::Matrix<cdouble>((int)pow(2, L), (int)pow(2, L));

	for (size_t i = 1; i <= L; i++)
	{
		LA::Matrix<cdouble> temp = getSpin(spinX, L, i);

		std::cout << temp << std::endl;

		temp *= h;
		hamilton -= temp;
	}

	std::cout << hamilton << std::endl;

	for (size_t i = 1; i <= L - 1; i++)
	{
		auto A = getSpin(spinZ, L, i);
		auto B = getSpin(spinZ, L, i + 1);

		hamilton -= A*B;
	}

	return hamilton;
}

LA::Matrix<cdouble> createMagnetization(size_t L)
{
	LA::Matrix<cdouble> magnetization = getSpin(spinZ, L, 1);

	for (size_t i = 0; i < L; i++)
		magnetization += getSpin(spinZ, L, i);
	magnetization *= 1 / (int)L;

	return magnetization;
}



int main()
{
	setupSpinMatrices();
	size_t N = 4;

	for (int n = 1; n < 40; n++)
	{
		double h = 0.001*n;

		LA::Matrix<cdouble> H = createHamiltonian(N, h);

		std::cout << "H:" << std::endl;
		std::cout << H << std::endl;

		std::vector<cdouble> eigenvalues;
		LA::Matrix<cdouble> eigenvectors;
		H.EVD(eigenvalues, eigenvectors);

		std::cout << "eig(H)" << std::endl;
		for (size_t i = 0; i < eigenvalues.size(); i++)
			std::cout << eigenvalues[i] << ", ";
		std::cout << std::endl;

		LA::Matrix<cdouble> T;
		LA::Vector<cdouble> v = LA::Vector<cdouble>((int)pow(2, N));
		for (size_t i = 0; i < v.getSize(); i++)
			v(i) = (double)rand() / RAND_MAX;

		LA::MatrixUtility::LanczosTransformation(H, T, v, v.getSize());

		std::cout << "T:" << std::endl;
		std::cout << T << std::endl;
		

		T.EVD(eigenvalues, eigenvectors);

		std::cout << "eig(T(H))" << std::endl;
		for (size_t i = 0; i < eigenvalues.size(); i++)
			std::cout << eigenvalues[i] << ", ";
		std::cout << std::endl;






		std::vector<double> realEigenvalues;
		for (size_t i = 0; i < eigenvalues.size(); i++)
			realEigenvalues.push_back(eigenvalues.at(i).real());
		/*
		std::cout << "real eigenvalues:\n";
		for (size_t i = 0; i < realEigenvalues.size(); i++)
			std::cout << realEigenvalues.at(i) << ", ";
		std::cout << std::endl;
		*/
		double minimum = realEigenvalues.at(0);
		size_t minIndex = 0;
		for (size_t i = 1; i < realEigenvalues.size(); i++)
		{
			if (realEigenvalues.at(i) < minimum)
			{
				minimum = realEigenvalues.at(i);
				minIndex = i;
			}
		}

		//std::cout << "minimal eigenvalue " << minimum << " at index " << minIndex << std::endl;

		LA::Vector<cdouble> eigenstate = LA::Vector<cdouble>(eigenvectors.getNRows(), true);
		for (size_t i = 0; i < eigenvectors.getNRows(); i++)
			eigenstate(i) = eigenvectors(i, minIndex);

		//std::cout << "min(E)/N: " << minimum / N << std::endl;

		LA::Vector<cdouble> groundstate = LA::Vector<cdouble>(2);

		LA::Matrix<cdouble> meanSpin = LA::Matrix<cdouble>((int)pow(2, N), (int)pow(2, N));
		for (size_t i = 1; i <= N; i++)
			meanSpin += getSpin(spinZ, N, i);

		meanSpin *= 1.0 / N;

		auto meanSpinValue = (eigenstate.transpose() * meanSpin) * eigenstate;
		//std::cout << meanSpinValue << std::endl;


		std::cout << h << "\t" << minimum / N << "\t" << meanSpinValue << std::endl;
	}

	return 0;
}