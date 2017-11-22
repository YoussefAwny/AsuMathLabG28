#include "header.h"
using namespace std;

void remove (char * text , char c)
{
	char*dest=text;
	while (*text)
	{
		if(*text !=c)
			*dest++=*text;
		text++;
	}
	*dest='\0';
}

double ** split (int nrows , int ncolumns , char* text)
{
    double ** array = new double * [nrows];
	for (int i=0 ; i<nrows ; i++){
		array[i] = new double [ncolumns];}
	char * space = " ;";
	char * p =strtok(text,space);
	int r =0;
	int c =0 ;
	while (p != NULL)
    {
		array[r][c] = atof(p);
        p = strtok (NULL, space);
		c++;
		if (c==ncolumns)
		{
			r++;
			c=0;
		}
    }
	return array ;
}

int no_rows (string input)
{
	int rows =1 ;
	for (int i=0 ; i<input.length() ; i++)
		{if (input[i]==';'&&!(input[i+1]==']'))
			rows++;
			if(input[i]==']') break;
			}
	return rows ;
}
int no_columns (string input)
{
	int columns = 0 ;
    input=input.substr(input.find('['),input.find(';')-input.find('[')-1);
    char* in=new char[input.length()];
    strcpy(in,input.data());
	char * space = " ;";
	char * p =strtok(in,space);
	int r =0;
	int c =0 ;
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


