#include "header.h"
using namespace std ;

void Matrix :: mul (Matrix &m )
{
	if (columns!=m.rows)
		throw  (" invalid matrix dimensions " );
	Matrix r ( rows , m.columns ,0,0) ;
	for ( int iR=0 ; iR<r.rows ; iR++ )
	{
		for (int iC=0 ; iC < r.columns ; iC++ )
		{
			r.values [iR] [iC] = 0 ;
			for (int k=0 ; k<m.columns ;k++ )
			{
				r.values [iR][iC]+=values[iR][k]*m.values[k][iC];
			}
		}
	}
	copy (r) ;
}
void Matrix :: operator *= (Matrix &m )
{
	mul (m) ;
}
void Matrix :: operator *= (double d)
{
 for(int iR=0; iR<rows; iR++)
 {
     for(int iC=0; iC<columns; iC++)
     {
         values[iR][iC] *= d ;
     }
 }
}
Matrix Matrix :: operator * ( Matrix &m )
{
	Matrix r = *this ;
	r*=m ;
	return r ;
}
Matrix Matrix :: operator * ( double d )
{
	Matrix r = *this ;
	r*=d ;
	return r ;
}
void Matrix:: div (Matrix &m )
{
	if (columns!=m.rows)
		throw  (" invalid matrix dimensions " );
	Matrix im(m.getInverse()) ;
	mul(im);
}
void Matrix :: operator /= (Matrix &m )
{
	div (m) ;
}
void Matrix :: operator /= (double d)
{
 for(int iR=0; iR<rows; iR++)
 {
     for(int iC=0; iC<columns; iC++)
     {
         values[iR][iC] /= d ;
     }
 }
}

Matrix Matrix :: operator / ( Matrix &m )
{
	Matrix r = *this ;
	r/=m ;
	return r ;
}
Matrix Matrix :: operator / ( double d )
{
	Matrix r = *this ;
	r/=d ;
	return r ;
}
