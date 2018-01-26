#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include<math.h>
#include <cstdlib>
//#ifndef MATRIX_H
//#define MATRIX_H
#define Lower 13
#define Upper 17
using namespace std;

class Matrix
{  //
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
	static Matrix mul2(Matrix& m1,Matrix& m2);
	static Matrix mul2(Matrix& m1,double d);
	static Matrix mul2(double d,Matrix& m2);
	static Matrix power2(Matrix& m1, Matrix& m2);
	static Matrix power (Matrix&m ,double d);
	static Matrix IMatrix (Matrix& m);
	static Matrix squareRoot (Matrix& m);
    double getDeterminant();
	Matrix getInverse();
	void Pivot_Form(int x,double& pivot,int& sign,int type);
	void Approach_Triangular_Form(int x, double pivot,int type);
   /* Matrix getMinor(int r, int c);
    Matrix get_Minors_Cofactor_Matrix() ;*/
    Matrix operator *(double d);
    void mul (Matrix &m);
	void operator *= (Matrix &m);
	void operator *= (double d);
	Matrix operator * ( Matrix &m );
	void div (Matrix &m);
	void operator /= (Matrix &m);
	void operator /= (double d);
	Matrix operator / (Matrix &m);
	Matrix operator / (double d);
	void print();
	string get_string();
	static Matrix sinm(Matrix& m );
	static Matrix cosm(Matrix& m);
	static Matrix tanm(Matrix& m);
	static Matrix cosecm(Matrix& m);
	static Matrix secm(Matrix& m);
	static Matrix cotanm(Matrix& m);
    static Matrix logm(Matrix& m);
    static Matrix expm(Matrix& m);
   	};
 string Remove (string x, string r);
 double ** split (int nrows , int ncolumns , char* text);
 int no_rows (string input);
 int no_columns (string input);
 int check_if_values (string input);
 int check_if_values_adv(string x);
 int get_matrix_number (string x, vector<string> y);
 string name_from_input (string x);
 string space_remover (string y);
 int check_if_number(string x);
 int get_number_of_open_br (string x);
 int get_number_of_close_br (string x);
 string ** split_string (int nrows , int ncolumns , char* text);
string matrix_conc(string MatOne);
string bracket_operation(string s);
 string normal_operation(string s);
 string Find_First_Number(string s, int index);
 string to_string(double value);
 double string_operation(string s);
 string putMatrixInString (string x , Matrix &m ,int index1 , int index2);
 int check_if_blank(string x);
 int check_if_math_op (string x);
//endif // !MATRIX_H
int* index_finder (string s, string s1, int &count);
int* minus_index_finder (string s, int&c);
