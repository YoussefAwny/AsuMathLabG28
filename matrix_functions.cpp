#include "header.h"
using namespace std;



	Matrix::Matrix()
	{
		rows = 0;
		columns = 0;
		values = NULL;
	}

	Matrix::Matrix(int Rows, int Columns)
	{
		 rows = Rows;
		 columns = Columns;

	}

	Matrix::Matrix(int r, int c, double** d)
	{
	    rows=r;
	    columns=c;
	    values=d;
	}

	Matrix::Matrix(Matrix& m)
	{
	    values=NULL;
	    copy(m);
	}

	Matrix::Matrix(const Matrix& m)
	{
	    values=NULL;
	    copy(m);
	}

	Matrix::Matrix(int nR, int nC, int initialization, double initializationValue)
	{
		this->rows = nR;
		this->columns = nC;
		if ((rows*columns) == 0)
		{
			values = NULL;
			return;
		}
		values = new double*[rows];
		for (int iR = 0; iR<rows; iR++)
		{
			values[iR] = new double[columns];
			for (int iC = 0; iC<columns; iC++)
			{
				switch (initialization)
				{
				case MI_ZEROS: values[iR][iC] = 0; break;
				case MI_ONES: values[iR][iC] = 1; break;
				case MI_EYE: values[iR][iC] = (iR == iC) ? 1 : 0; break;
				case MI_RAND: values[iR][iC] = (rand() % 1000000) / 1000000.0; break;
				case MI_VALUE: values[iR][iC] = initializationValue; break;
				}
			}
		}
	}

	double** Matrix::get_dpointer()
	{
	  return values;
	}

	int Matrix::get_rows()
	{
	   return rows;
	}

	int Matrix::get_columns()
	{
	   return columns;
	}


	Matrix Matrix::operator=(double l)
	{
		copy(l);
		return *this;
	}
	Matrix Matrix::operator=(const Matrix & m)
	{
		copy(m);
		return *this;
	}
	Matrix::~Matrix()
	{
	    reset();
	}
	void Matrix::reset()
	{
		if (values)
		{
			for (int i = 0; i < rows; i++)
				delete[] values[i];
			delete[] values;
		}
		rows = columns = 0;
		values = NULL;
	}
	void Matrix::copy(double d) {
		reset();
		this->rows = 1;
		this->columns = 1;
		values = new double*[1];
		values[0] = new double[1];
		values[0][0] = d;
	}
	void Matrix::copy(Matrix & m)
	{    reset();
         this->rows = m.rows; this->columns = m.columns;
         if((rows*columns)==0){values=NULL; return;}
         values = new double*[rows];
          for(int iR=0;iR<rows;iR++)
            { values[iR] = new double[columns];
          for(int iC=0;iC<columns;iC++)
            { values[iR][iC] = m.values[iR][iC]; } }
        }

    void Matrix::copy(const Matrix & m)
	{    reset();
         this->rows = m.rows; this->columns = m.columns;
         if((rows*columns)==0){values=NULL; return;}
         values = new double*[rows];
          for(int iR=0;iR<rows;iR++)
            { values[iR] = new double[columns];
          for(int iC=0;iC<columns;iC++)
            { values[iR][iC] = m.values[iR][iC]; } }
        }


	void Matrix::add(Matrix& m)
	{
		if (rows != m.rows || columns != m.columns)
			throw("Invalid matrix dimension");

		for (int R = 0; R < rows; R++)
			for (int C = 0; C < columns; C++)
				values[R][C] += m.values[R][C];
	}

	void Matrix::operator+=(Matrix& m)
	{
		add(m);
	}
	void Matrix::operator+=(double d)
	{
	    Matrix m (rows, columns, MI_VALUE, d);
		add(m);
	}
	Matrix Matrix::operator+(Matrix& m)
	{
		Matrix r = *this;
		r += m;
		return r;
	}

	Matrix Matrix::operator+(double d)
	{

		Matrix r = *this;
		r += d;
		return r;
	}

	void Matrix::sub(Matrix& m)
	{
		if (rows != m.rows || columns != m.columns)
			throw("Invalid matrix dimension");

		for (int iR = 0; iR < rows; iR++)
			for (int iC = 0; iC < columns; iC++)
				values[iR][iC] -= m.values[iR][iC];
	}
	void Matrix::operator-=(Matrix& m)
	{
		sub(m);
	}
	void Matrix::operator-=(double d)
	{
	    Matrix m (rows, columns, MI_VALUE, d);
		sub(m);
	}
	Matrix Matrix::operator-(Matrix& m)
	{
		Matrix r = *this;
		r -= m;

		return r;
	}

	Matrix Matrix::operator-(double d)
	{
		Matrix r = *this;
		r -= d;

		return r;
	}

    Matrix Matrix::div2(Matrix& m1,Matrix& m2)
	{
		if (m1.rows != m2.rows || m1.columns != m2.columns)
			throw("Invalid matrix dimension");

		for (int R = 0; R < m1.rows; R++)
			{for (int C = 0; C < m1.columns; C++)
				{m1.values[R][C] /= m2.values[R][C];}}
        return m1;
	}

	Matrix Matrix::div2(Matrix& m1,double d)
	{
	    Matrix m2 (m1.rows, m1.columns, MI_VALUE, d);

		for (int R = 0; R < m1.rows; R++)
			{for (int C = 0; C < m1.columns; C++)
				{m1.values[R][C] /= m2.values[R][C];}}
		return m1;
	}

	Matrix Matrix::div2(double d,Matrix& m2)
	{
	    Matrix m1 (m2.rows, m2.columns, MI_VALUE, d);

		for (int R = 0; R < m2.rows; R++)
			{for (int C = 0; C < m2.columns; C++)
				{m1.values[R][C] /= m2.values[R][C];}}
		return m1;
	}

	Matrix Matrix::mul2(Matrix& m1,Matrix& m2)
	{
		if (m1.rows != m2.rows || m1.columns != m2.columns)
			throw("Invalid matrix dimension");

		for (int R = 0; R < m1.rows; R++)
			{for (int C = 0; C < m1.columns; C++)
				{m1.values[R][C] *= m2.values[R][C];}}
        return m1;
	}

	Matrix Matrix::mul2(Matrix& m1,double d)
	{
	    Matrix m2 (m1.rows, m1.columns, MI_VALUE, d);

		for (int R = 0; R < m1.rows; R++)
			{for (int C = 0; C < m1.columns; C++)
				{m1.values[R][C] *= m2.values[R][C];}}
		return m1;
	}

	Matrix Matrix::mul2(double d,Matrix& m2)
	{
	    Matrix m1 (m2.rows, m2.columns, MI_VALUE, d);

		for (int R = 0; R < m2.rows; R++)
			{for (int C = 0; C < m2.columns; C++)
				{m1.values[R][C] *= m2.values[R][C];}}
		return m1;
	}

   Matrix Matrix :: power (Matrix& m1 ,Matrix& m2)
    {
        if(m1.rows != m2.rows && m1.columns !=m2.columns)
            throw("Invalid matrix dimension");
        Matrix m (m1.rows,m1.columns,MI_ZEROS,0);
        for (int i=0 ; i<m1.rows ; i++)
        {
            for (int j=0 ; j<m1.columns ; j++)
            {
                m.values[i][j]=pow(m1.values[i][j],m2.values[i][j]);
            }
        }
        return m ;
    }

    Matrix Matrix :: power (Matrix& m1 ,Matrix& m2)
    {
        if(m1.rows != m2.rows && m1.columns !=m2.columns)
            throw("Invalid matrix dimension");
        Matrix m (m1.rows,m1.columns);
        for (int i=0 ; i<m1.rows ; i++)
        {
            for (int j=0 ; j<m1.columns ; j++)
            {
                m.values[i][j]=pow(m1.values[i][j],m2.values[i][j]);
            }
        }
        return m ;
    }
    Matrix Matrix :: IMatrix (Matrix&m)
    {
        for (int i=0 ;i<m.rows ; i++)
        {
            for (int j=0 ; j<m.columns ; j++)
            {
                if (i=j)
                    m.values[i][j]=1;
                else
                    m.values[i][j]=0;
            }
        }
        return m ;
    }
    Matrix Matrix :: power (Matrix&m ,double d)
    {
        if(m.rows !=m.columns) // this type applies for square matrix only
            throw("Invalid matrix dimension");
        Matrix c =*this;
        if (d==0)
        {
            c=IMatrix(m);
            return c ;
        }
        if (d==1)
        {
            c=m;
            return c ;
        }
        if (d==2)
        {
            c=m*m;
            return c;
        }
        if (d==3)
        {
            c=m*m;
            c*=m;
            return c ;
        }
        if (d>3)
        {
            c=m*m;
            for (int i=0 ;i<d-2 ; i++)
            {
                c=c*m;
            }
            return c ;
        }
    }
    Matrix :: Matrix squareRoot (Matrix& m)
    {
        int flag =0;
        for (int i=0 ; i<m.rows ; i++)
        {
            for (int j=0 ; j<m.columns ; j++)
            {
               if (m.values[i][j]<0)
               {
                   flag=1;
                   break;
               }
            }
        }
        if (flag==1)
            throw("can't compute square root for negative values");
        Matrix c = *this ;
        for (int i=0 ; i<m.rows ; i++)
        {
            for (int j=0 ; j<m.columns ; j++)
            {
               c.values[i][j]=sqrt(m.values[i][j]);
            }
        }
        return c ;
    }

/*
//old inverse
double Matrix:: getDeterminant()
	{
		if(this->rows==2 && this->columns==2)
			return (values[0][0]*values[1][1]-values[0][1]*values[1][0]);
		else
		{
			double sum=0;
			int sign=1;
			for(int i=0;i< this->columns;i++)
			{
				sum+=(sign*values[0][i]*((this->getMinor(0,i)).getDeterminant()));
				sign*=-1;
			}
			return sum;
		}
	}
	Matrix Matrix:: getMinor(int r, int c)     //Parameters are the index of the element to which we calculate the minor
	{
		Matrix Minor((this->rows)-1,(this->columns)-1, 0,0);
		int i_Minor=0;
		int j_Minor=0;
		for(int i=0; i<this->rows; i++)
		{
			if(i==r) continue;
			else
			{
			    for(int j=0;j<this->columns;j++)
		        {
					if(j==c) continue;
					if(j_Minor>(this->columns)-1 || i_Minor>(this->rows)-1) throw("index exceeded array size");
					 Minor.values[i_Minor][j_Minor]=values[i][j];   j_Minor++;
			    }
				i_Minor++;
				j_Minor=0;
			}
		}
		return Minor;
	}
	Matrix Matrix:: get_Minors_Cofactor_Matrix()        //to return adjugate
	{
			Matrix Minors_Cofactor_Matrix(this->rows,this->columns, 0,0);
			int sign;
		for(int i=0; i<this->rows; i++)
		{
			if(i%2==0) sign=1;
			else sign=-1;
			for(int j=0;j<this->columns;j++)
			{
				Minors_Cofactor_Matrix.values[i][j]=sign*((this->getMinor(i,j)).getDeterminant());
				sign*=-1;
			}
		}
		return Minors_Cofactor_Matrix;
	}
	Matrix Matrix:: getInverse()
	{
		if(!rows==columns) throw("Invalid Matrix dimensions");
		if(this->getDeterminant()==0)throw("Invalid Matrix values");
		return ((this->get_Minors_Cofactor_Matrix()).getTranspose())*(1.0/(this->getDeterminant()));
	}
	Matrix Matrix::operator *(double x)
	{
		for(int i=0; i<this->rows; i++)
		{
			for(int j=0;j<this->columns;j++)
			{
				this->values[i][j]*=x;
			}
		}
		return *this;
	}
	*/

	Matrix Matrix:: getTranspose()
{
	Matrix transpose(this->columns,this->rows,0,0);
	for(int i=0; i<this->columns; i++)
	{
		for(int j=0; j<this->rows ; j++)
		{
			transpose.values[i][j]=this->values[j][i];
		}
	}
	return transpose;
}

void Matrix::print()
{
              for (int i=0 ; i<rows; i++ )
            {
                for (int j =0 ; j<columns; j++)
                    cout<<values[i][j]<<" ";
                cout<<endl;
            }

}
string Matrix::get_string()
{
    string x;
    int flag=0;
    if(rows!=1&&columns!=1)x="[";
    for(int i=0; i<rows;i++)
    {
        for(int j=0; j<columns; j++)
        {
          if ((i==0)&&(j==0)) flag=1;
          if(flag==0)x+=" ";
          x+=static_cast<ostringstream*>( &(ostringstream() <<values[i][j]) )->str();
            //if(x[x.length()-1]==NULL)x.erase(x.length()-1);
        flag=0;
        }
       if(!(i==rows-1)) x+=";";
    }
    if(rows!=1&&columns!=1)x+="]";

    return x;
}

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
Matrix Matrix::operator * ( Matrix &m )
{
	Matrix r = *this ;
	r*=m ;
	return r ;
}
Matrix Matrix::operator * ( double d )
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
Matrix Matrix::sinm(Matrix& m)
 {
     Matrix r (m.rows, m.columns,MI_ZEROS,0);
     int flag =0;
   for (int iR = 0; iR < m.rows; iR++)
	{
		for (int iC = 0; iC < m.columns; iC++)
			{
			   /* if ( m.values[iR][iC]==(1/0))
                  {
                      cout << "please enter valid numbers in the matrix." <<endl;
               //    flag = 1;
                  break;

                  }
                else
                {*/
                    r.values[iR][iC] = sin(m.values[iR][iC]);


			}
			// if ( flag == 1)
              //  break;
	}
	//if (flag != 1 )
	return r;
 }

Matrix Matrix::cosm(Matrix& m)
 {
     Matrix r (m.rows, m.columns,MI_ZEROS,0);
     int flag =0 ;
   for (int iR = 0; iR < m.rows; iR++)
    {
		for (int iC = 0; iC < m.columns; iC++)
			{
			/*    if ( m.values[iR][iC]==(1/0))
                {

                    cout << "please enter valid numbers in the matrix." <<endl;
                    flag=1;
                    break;

                }*/
                //else
                 //{
                    r.values[iR][iC] = cos(m.values[iR][iC]);
                //}
			}
            //   if ( flag == 1)
              //   break;
    }
   // if (flag == 1 )
    return r;
 }
 Matrix Matrix::tanm(Matrix& m)
 {
  Matrix r (m.rows, m.columns,MI_ZEROS,0);
              int flag = 0 ;

   for (int iR = 0; iR < m.rows; iR++)
	{
		for (int iC = 0; iC < m.columns; iC++)
            {


     //           if ( m.values[iR][iC]==(1/0))
       //         {
         //           cout << "please enter valid numbers in the matrix." <<endl;
           //        flag = 1 ;
             //       break;

               // }
                //else
                //{
                   r.values[iR][iC] = tan(m.values[iR][iC]);

                //}
            }
             //if(flag == 1)
             //{
               //  break;
             //}

	}
//	if (flag != 1 )
    return r;
 }


 Matrix Matrix::cosecm(Matrix& m)
 {
     Matrix r (m.rows, m.columns,MI_ZEROS,0);
     		int flag =0 ;
   for (int iR = 0; iR < m.rows; iR++)
		{
		for (int iC = 0; iC < m.columns; iC++)
			{
			    if (  m.values[iR][iC]==(0))
                  {
                      cout << "Matrix is a singular to working precision" << endl ;
                   flag =1;
                  break;

                  }
                else
                {
                    r.values[iR][iC] = (1/sin(m.values[iR][iC]));
                }
			}
        if ( flag == 1)
        break;
        }
        if (flag != 1 )
         return r;
 }

Matrix Matrix::secm(Matrix& m)
 {
      Matrix r (m.rows, m.columns,MI_ZEROS,0);
      int flag = 0  ;
   for (int iR = 0; iR < m.rows; iR++)
    {
        for (int iC = 0; iC < m.columns; iC++)
			{
			    //if ( m.values[iR][iC]==(1/0))
                //{

                  //  cout << "please enter valid numbers in the matrix." <<endl;
                    //flag =1;
                //    break;
                //}
                //else
                //{
                      r.values[iR][iC] = (1/cos(m.values[iR][iC]));
                //}
			}
               //if ( flag == 1)
                //break;
    }
   // if (flag != 1 )
    return r;
 }

Matrix Matrix::cotanm(Matrix& m)
{
     Matrix r (m.rows, m.columns,MI_ZEROS,0);
     int flag =0;
   for (int iR = 0; iR < m.rows; iR++)
	{
		for (int iC = 0; iC < m.columns; iC++)
            {
                if ( m.values[iR][iC]==(0) )
                {
                    cout << "Matrix is a singular to working precision" << endl ;
                flag=1;
                    break;
                }
                else
                {
                   r.values[iR][iC] = (1/tan(m.values[iR][iC]));

                }
            }
            if(  flag == 1 )
               {
                   break;
               }

	}
            if (flag != 1 )
            return r;
 }

    Matrix Matrix::logm(Matrix& m)
{
     Matrix r (m.rows, m.columns,MI_ZEROS,0);
     int flag =0;
         for (int iR = 0; iR < m.rows; iR++)
        {

            for (int iC = 0; iC < m.columns; iC++)
            {

                if (m.values[iR][iC] > 0 )
                {
                    r.values[iR][iC] = log(m.values[iR][iC]);

                }

     else
     {
         cout << "Matrix is a singular to working precision" << endl ;
        flag =1;
        break;
     }
            }

	if (flag == 1 )
	break;
        }
        if (flag != 1 )
        return r;
}


  Matrix Matrix::expm(Matrix& m)
{
    Matrix r (m.rows, m.columns,MI_ZEROS,0);
    int flag =0 ;
         for (int iR = 0; iR < m.rows; iR++)
	{
		for (int iC = 0; iC < m.columns; iC++)
        {
              //  if (m.values[iR][iC] != (1/0) )
                //{
                    r.values[iR][iC] = exp(m.values[0][0]);
                //}

//     else
  //          {
    //            cout << "Please enter a matrix containing valid numbers only!" << endl ;
      //          flag = 1;
        //        break;
          //  }
        }

	//if (flag == 1 )
	//break;

	}
//if (flag != 1 )
    return r;
}










