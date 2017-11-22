#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
//#ifndef MATRIX_H
//#define MATRIX_H

using namespace std;

class Matrix
{
private:
    int rows, columns;

	double **values;
public:
    enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
	Matrix();
	Matrix(Matrix& m);
	Matrix(const Matrix& m);
	Matrix(int Rows, int Columns);
	Matrix(int nR, int nC, int initialization, double initializationValue);
	Matrix(int r, int c, double** d);
	~Matrix();
	Matrix operator=(double l);
	Matrix operator=(const Matrix& m);
	void reset();
	void copy(double d);
	void copy( Matrix& m);
	void copy(const Matrix & m);
	void add(Matrix& m);
	void operator+=(Matrix& m);
	void operator+=(double d);
	Matrix operator+(Matrix& m);
	Matrix operator+(double d);
	void sub(Matrix& m);
	void operator-=(Matrix& m);
	void operator-=(double d);
	Matrix operator-(Matrix& m);
	Matrix operator-(double d);
	Matrix getTranspose();
	double** get_dpointer();
	int get_rows();
	int get_columns();
	static Matrix div2(Matrix& m1,Matrix& m2);
	static Matrix div2(Matrix& m1,double d);
	static Matrix div2(double d,Matrix& m2);
    double getDeterminant();
    Matrix getMinor(int r, int c);
    Matrix get_Minors_Cofactor_Matrix() ;
    Matrix getInverse();
    Matrix operator *(double d);
    void mul (Matrix &m);
	void operator *= (Matrix &m);
	void operator *= (double d);
	Matrix operator * (Matrix &m);
    void div (Matrix &m);
	void operator /= (Matrix &m);
	void operator /= (double d);
	Matrix operator / (Matrix &m);
	Matrix operator / (double d);
	void print();
};
 void remove (char * text , char c);
 double ** split (int nrows , int ncolumns , char* text);
 int no_rows (string input);
 int no_columns (string input);
 int check_if_values (string input);
int get_matrix_number (string x, vector<string> y);
 string name_from_input (string x);
 string space_remover (string y);
 int check_if_number(string x);




//endif // !MATRIX_H

