// MatrixExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>

#include "../YAOLAW/la_baseobject.h"
#include "../YAOLAW/matrix.h"
#include "../YAOLAW/vector.h"

using namespace LA;

void addition_multiplication_test()
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

	//std::cout << std::setprecision(2) << std::scientific;
	std::cout << "A:" << std::endl << A << std::endl;
	std::cout << "B:" << std::endl << B << std::endl;

	Matrix<double> At = A.Trans();

	std::cout << "At:" << std::endl << At << std::endl;

	C = A * B;

	C += -10.0;

	Matrix<double> D;
	D = C * 100.0;
	Matrix<double> E = D + C;

	std::cout << "A*B:" << std::endl << C << std::endl;
}

template <typename T>
void EvTest1()
{
	Matrix<T> A(3, 3);

	for (unsigned int r = 0; r < A.getNRows(); r++)
		for (unsigned int c = 0; c < A.getNCols(); c++)
			A(r, c) = c + r*A.getLeadingDim();

	auto eigenvalues = std::vector<std::complex<T>>(3);
	Matrix<T> eigenvector;
	A.EVD(eigenvalues, eigenvector);

	std::cout << "eigenvalues:\n" << std::endl;
	for (size_t i = 0; i < eigenvalues.size(); i++)
		std::cout << eigenvalues.at(i) << ", ";
	std::cout << std::endl;
	std::cout << "eigenvectors:\n" << eigenvector << std::endl;
	std::cout << std::endl;
}

template <typename T>
void EvTest2()
{
	Matrix<T> A(3, 3);

	for (unsigned int r = 0; r < A.getNRows(); r++)
		for (unsigned int c = 0; c < A.getNCols(); c++)
			A(r, c) = c + r*A.getLeadingDim();

	auto eigenvalues = std::vector<T>(3);
	Matrix<T> eigenvector;
	A.EVD(eigenvalues, eigenvector);

	std::cout << "eigenvalues:\n" << std::endl;
	for (size_t i = 0; i < eigenvalues.size(); i++)
		std::cout << eigenvalues.at(i) << ", ";
	std::cout << std::endl;
	std::cout << "eigenvectors:\n" << eigenvector << std::endl;
	std::cout << std::endl;
}

template <typename T>
void SvTest1()
{
	Matrix<T> A(3, 3);

	for (unsigned int r = 0; r < A.getNRows(); r++)
		for (unsigned int c = 0; c < A.getNCols(); c++)
			A(r, c) = c + r*A.getLeadingDim();

	auto eigenvalues = std::vector<std::complex<T>>(3);
	Matrix<T> U;
	Vector<T> S;
	Matrix<T> Vt;
	A.SVD(U, S, Vt);

	std::cout << "U:\n" << U << std::endl;
	std::cout << "Sigma:\n" << S << std::endl;
	std::cout << "Vt:\n" << Vt << std::endl;
	std::cout << std::endl;
}

template <typename T>
void SvTest2()
{
	Matrix<std::complex<T>> A(3, 3);

	for (unsigned int r = 0; r < A.getNRows(); r++)
		for (unsigned int c = 0; c < A.getNCols(); c++)
			A(r, c) = c + r*A.getLeadingDim();

	auto eigenvalues = std::vector<std::complex<T>>(3);
	Matrix<std::complex<T>> U;
	Vector<T> S;
	Matrix<std::complex<T>> Vt;
	A.SVD(U, S, Vt);

	std::cout << "U:\n" << U << std::endl;
	std::cout << "Sigma:\n" << S << std::endl;
	std::cout << "Vt:\n" << Vt << std::endl;
	std::cout << std::endl;
}

void tensor_product()
{
	Matrix<std::complex<double>> A = Matrix<std::complex<double>>(2, 2);
	Matrix<std::complex<double>> B = Matrix<std::complex<double>>(2, 2);

	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			A(i, j) = (std::complex<double>)(i * 2 + j);
			B(i, j) = -(std::complex<double>)(i * 2 + j);
		}
	}



	std::cout << A << std::endl;
	std::cout << B << std::endl;

	Matrix<std::complex<double>> C = Matrix<std::complex<double>>::identity(2);
	std::cout << C << std::endl;

	for (size_t t = 0; t < 2; t++)
	{
		C = C.directProduct(B);
		std::cout << C << std::endl;
	}
}

int main()
{
	tensor_product();

	addition_multiplication_test();

	EvTest1<double>();
	EvTest1<float>();
	EvTest2<std::complex<double>>();
	EvTest2<std::complex<float>>();

	SvTest1<double>();
	SvTest1<float>();
	SvTest2<double>();
	SvTest2<float>();

	Vector<double> v1 = Vector<double>(10);
	Vector<double> v2 = Vector<double>(10, false);

	for (size_t i = 0; i < v1.getNRows(); i++)
		v1(i) = i;

	for (size_t i = 0; i < v2.getNCols(); i++)
		v2(i) = i;

	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;

	auto testMatrix = Matrix<double>::identity(10) * 2;

	std::cout << v1.transpose()*v1 << std::endl;

	std::cout << testMatrix*v1 << std::endl;


	LA::Vector<std::complex<double>> v3 = LA::Vector<std::complex<double>>(3);
	v3(0) = 1;
	v3(1) = 2;
	v3(2) = 3;

	LA::Matrix<std::complex<double>> m3 = LA::Matrix<std::complex<double>>(3,3);
	m3(0, 0) = 1;
	m3(0, 1) = 2;
	m3(0, 2) = 3;
	m3(1, 0) = 4;
	m3(1, 1) = 5;
	m3(1, 2) = 6;
	m3(2, 0) = 7;
	m3(2, 1) = 8;
	m3(2, 2) = 9;

	std::cout << v3.transpose() * m3 * v3 << std::endl;

}

