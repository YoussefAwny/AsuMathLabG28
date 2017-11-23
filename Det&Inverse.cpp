
#include "header.h"
using namespace std;
#define Lower 0
#define Upper 1

void Matrix::Pivot_Form(int x,double& pivot,int& sign,int type)
{
	if(type==Upper)
	{
		for(int i=x;i<rows;i++)
	    {
		    if(values[i][x]==0) continue; //pivot still not found

	        //pivot found
		    pivot=values[i][x];
		    if(i==x) break;

		    //swap to put pivot in right place
		    double*temp_array=new double[columns];
	        for(int j=0;j<columns;j++)
	        {
			    temp_array[j]=values[i][j];
			    values[i][j]=values[x][j];
			    values[x][j]=temp_array[j];
		    }
		    delete [] temp_array;
		    sign*=-1;
		    break;
	    }
	}
	else if(type==Lower)
	{
		for(int i=x;i>=0;i--)
	    {
		    if(values[i][x]==0) continue; //pivot still not found

	        //pivot found
		    pivot=values[i][x];
		    if(i==x) break;

		    //swap to put pivot in right place
		    double*temp_array=new double[columns];
	        for(int j=0;j<columns;j++)
	        {
			    temp_array[j]=values[i][j];
			    values[i][j]=values[x][j];
			    values[x][j]=temp_array[j];
		    }
		    delete [] temp_array;
		    sign*=-1;
		    break;
	    }
	}
}

void Matrix:: Approach_Triangular_Form(int x, double pivot,int type)
{
	if(type==Upper)
	{
	     for(int i=x+1;i<rows;i++)
	     {
		     if(values[i][x]==0) continue;
		     //use elementary row operations to make values[i][x] equals zero
		     double factor=values[i][x]/pivot;
		     for(int j=0;j<columns;j++)
			     values[i][j]=values[i][j]-factor*values[x][j];
		 }
	}
	else if(type==Lower)
	{
		for(int i=x+1;i>=0;i--)
	     {
		     if(values[i][x]==0) continue;
		     //use elementary row operations to make values[i][x] equals zero
		     double factor=values[i][x]/pivot;
		     for(int j=0;j<columns;j++)
			     values[i][j]=values[i][j]-factor*values[x][j];
		 }
	}
}

double Matrix::getDeterminant()
{
	int sign=1;
	for(int i=0;i<rows-1;i++)
	{
		double pivot=0;
		this->Pivot_Form(i,pivot,sign,Upper);
		if(pivot==0) continue;
	    this->Approach_Triangular_Form(i,pivot,Upper);
	}

	double det=1;
	for(int D_index=0;D_index<rows;D_index++)
		det*=values[D_index][D_index];
	return sign*det;


}

Matrix Matrix:: getInverse()
{
	//Concatenate matrix with identity matrix in big matrix
	Matrix Big(this->rows,(this->columns)*2,MI_ZEROS,0);
	for(int i=0;i<Big.get_rows();i++)
	{
		for(int j=0;j<Big.get_columns();j++)
		{
			if(j>this->columns-1)
			{
				if(i==j-this->columns)
				Big.values[i][j]=1;
				else Big.values[i][j]=0;
			}
			else
			{
				Big.values[i][j]=this->values[i][j];
			}
		}
	}

	//upper triangular form
	int sign=1;
	for(int k=0;k<Big.get_rows()-1;k++)
	{
		double pivot=0;
		Big.Pivot_Form(k,pivot,sign,Upper);
		if(pivot==0) continue;
	    Big.Approach_Triangular_Form(k,pivot,Upper);
	}

	//lower triangular form
	for(int k=Big.get_rows()-1;k>=0;k--)
	{
		double pivot=0;
		Big.Pivot_Form(k,pivot,sign,Lower);
		if(pivot==0) continue;
	    Big.Approach_Triangular_Form(k,pivot,Lower);
	}

	//make Main Diagonal ones
	for(int i=0;i<Big.get_rows()-1;i++)
		for(int j=0;j<Big.get_columns();j++)
			Big.values[i][j]=Big.values[i][j]/Big.values[i][i];

	//get the inverse from the big matrix
	Matrix inverse(this->rows,this->columns,MI_ZEROS,0);
	for(int i=0;i<this->rows;i++)
		for(int j=0;j<this->columns;j++)
			inverse.values[i][j]=Big.values[i][j+this->columns];

	return inverse;
}
