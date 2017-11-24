#include "header.h"
using namespace std;

string Remove (string x, string r)
{
	int l=r.length();
        while(x.find(r)!=-1)
      {
        x.erase(x.find(r),l);
      }
      return x;
}

double ** split (int nrows , int ncolumns , char* text)
{
    double ** a = new double * [nrows];
	for (int i=0 ; i<nrows ; i++){
		a[i] = new double [ncolumns];}
	char * space = " ;[]";
	//char* context	= NULL;
	char * p =strtok(text,space);//,&context);
	int r =0;
	int c =0 ;
	while (p != NULL)
    {
		a[r][c] = atof(p);
        p = strtok (NULL, space);//,&context);
        c++;
		if (c==ncolumns)
		{
			r++;
			c=0;
		}
    }
	return a ;
}


string ** split_string (int nrows , int ncolumns , char* text)
{
    string ** a = new string * [nrows];
	for (int i=0 ; i<nrows ; i++){
		a[i] = new string [ncolumns];}
	char * space = " ;[]";
	char * p =strtok(text,space);
	int r =0;
	int c =0 ;
	while (p != NULL)
    {
		a[r][c] = p;
        p = strtok (NULL, space);
        c++;
		if (c==ncolumns)
		{
			r++;
			c=0;
		}
    }
	return a ;
}

int no_rows (string input)
{
	int rows =1 ;
	for (int i=0 ; i<input.length()-1 ; i++)
		{if (input[i]==';'&&!(input[i+1]==']'))
			rows++;
			//if(input[i]==']') break;
			}
	return rows ;
}
int no_columns (string input)
{
	int columns = 0 ;
    input=input.substr(input.find('[')+1,input.find(';')-input.find('[')-1);
    char* in=new char[input.length()];
    strcpy(in,input.data());
	char * space = " ;[]";
	char * p =strtok(in,space);
	while (p != NULL)
    {
        columns++;
        p = strtok (NULL, space);
    }

	return columns;
}
int check_if_values (string input)
{
    for(int i=0;i<input.length();i++)
    {
        if(input[i]=='[')
        {
            return 1;
        }
        }
        return 0;
}

int check_if_values_adv(string x)
{
    x=x.substr(x.find('=')+1);
    string exceptions[] ={"sin(","cos(","tan(","cot(","csc(","sec(","log(","exp(","sqrt("};
    int c=4;
    for(int i=0;i<9;i++)
    {
       i==8?c=5:c=4;
      while(x.find(exceptions[i])!=-1)
      {
        x.erase(x.find(exceptions[i]),c);
      }
    }
    int flag=check_if_number(x);
    if (x.find('[')!=-1) flag=0;
    if (flag==1)return 1;
    else return 0;
}

int get_matrix_number (string x, vector<string> y)
{
    for(int i=0;i<y.size();i++)
    {
     if(y[i]==x)
     {
         return i;
     }
    }
    return -1;
}
string name_from_input (string y)

{
    char *x=new char[y.length()];
    int i=0;
    y=y.substr(0,y.find('='));
    y.copy(x,y.length());
    x[y.length()]=0;
    while (x[i]==' ')
    {
        x[i]=0; x++; i++;
    }
    i= strlen(x)-1;
    while (x[i]==' ')
    {
        x[i]=0; i--;
    }
    y=x;
    return y;
}

string space_remover (string y)
{
    char *x=new char[y.length()];
    int i=0;
    y.copy(x,y.length());
    x[y.length()]=0;
    i= strlen(x)-1;
    while (x[i]==' ')
    {
        x[i]=0; i--;
    }
    i=0;
    while (x[i]==' ')
    {
        x[i]=0; x++; i++;
    }
        y=x;
    return y;
}

int check_if_number(string x)
{
    int flag=1;

    for(int i=65;i<91;i++)
    {
      for(int j=0;j<x.length();j++)
      {
        if(x[j]==i) {flag=0;}
      }
    }
    for(int i=97;i<123;i++)
    {
      for(int j=0;j<x.length();j++)
      {
        if(x[j]==i) {flag=0;}
      }
    }
   return flag;
}
int get_number_of_open_br (string x)
{
    int c=0;
   for(int i=0;i<x.length();i++)
   {
      if(x[i]=='[') c++;
   }
   return c;
}
int get_number_of_close_br (string x)
{
    int c=0;
   for(int i=0;i<x.length();i++)
   {
      if(x[i]==']') c++;
   }
   return c;
}

int check_if_math_op (string x)
{
    int flag=0;
    string r[]={"+","-","*","/","sin(","cos(","tan(","cot(","csc(","sec(","sqrt(","log(","exp("};
    for(int i=0;i<13;i++)
    {
        if((x.find(r[i]))!=-1) flag=1;
    }
    return flag;
}


