#include "header.h"
#include <vector>
#include <string>
using namespace std;

string matrix_conc(string MatOne)
{
  int rows = 1, cols = 1, nR1 = 1, nR2 =1 , nC1 = 1, nC2 = 1;
  bool Space = 0; //to elimenate spaces to only 1
  bool semicolon = 0;//to ensure that no spaces before or after semicolon is used to increment no of COLs
  bool eom = 0; //is HIGH when ']' is reached
  int j = 0, k = 0; // j is index for rows and k index for coloumns
  string final;

  //this loop to know no of rows and no of cols
  for (int i = 0; i < MatOne.length(); i++)
  {
    switch (MatOne[i])
    {
    case ' ': if ((!Space) && (!semicolon)) { cols++; } if (eom) { nC2++; }if (!eom) { nC1++; }  Space = 1; semicolon = 0;  break;
    case ';':semicolon = 1; rows++; if (eom) { nR2++; } if (!eom) {if(MatOne[i+1]!=']'){cols = 1; nC1 = 1; nR1++; }}; Space = 0; break;
    case '[':rows = 1; if (eom) {} Space = 0; semicolon = 0; break;
    case ']':if (!eom) { cols++; }; eom = 1; Space = 1; semicolon = 0; break;

    default: semicolon = 0; Space = 0; break;
    }
  }

  eom = 0, Space = 0; semicolon = 0;
  if ( nR1 != nR2 )
  {
    cout << "Matrix Dimensions error";
  }


  string **array = new string*[rows];
  for (int row = 0; row < rows; row++)
  {
    array[row] = new string[cols];
  }


  //this loop if input is 1 string
  for (int i = 0; i < MatOne.length(); i++)
  {
    switch (MatOne[i])
    {
    case ' ': if ((!Space)&&(!semicolon)) { k++; } Space = 1; semicolon = 0;  break;
    case ';':if(MatOne[i+1]!=']'){semicolon = 1; j++; if (!eom) { k = 0; };} Space = 0; break;
    case '[':j = 0; Space = 0; semicolon = 0; break;
    case ']':if (!eom) {k++; }; eom = 1; Space = 1; semicolon = 0; break;
    case',':break;
    default: semicolon = 0; Space = 0; array[j][k] += MatOne[i]; break;
    }

  }




  for (int j = 0; j < rows; j++)//putting the array into a string so it can be returned
  {
    for (int k = 0; k < cols; k++)
    {
      final += array[j][k];
	  if (k!=cols-1)final += ' ';
    }


    if (j!= rows-1)
    {
      final += "; ";
    }
  }

  for (int row = 0; row < rows; row++)
  {
    delete[] array[row];
  }
  delete[] array;

  return final;

}

int check_if_in_array(int a,int* b, int c)
{
    if(b==NULL)return 0;
    for(int i=0;i<c;i++)
    {
       if(b[i]==a)
        return 1;
    }
   return 0;
}

void Operation(string x, int& index, int& flag, int* arr,int arrc)
{
    bool pow, mult, div, plus, minus;
    pow = false;
    mult = false;
    div = false;
    plus = false;
    minus = false;
    int powIndex, mulltIndex, divIndex, plusIndex, minusIndex;
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == '^' && pow==false) { pow = true; powIndex = i; }
        else if (x[i] == '*' && mult==false) { mult = true; mulltIndex = i; }
        else if (x[i] == '/' && div==false) { div = true; divIndex = i; }
        else if (x[i] == '+' && plus==false) { plus = true; plusIndex = i; }
        else if (x[i] == '-' && minus==false&&check_if_in_array(i,arr,arrc)) { minus = true; minusIndex=i; }
    }

    if (pow) { flag = 1; index = powIndex; return; }
    else if (mult && div)
    {
        if (mulltIndex < divIndex)
        {
            flag = 2;
            index = mulltIndex;
            return;
        }
        else
        {
            flag = 3;
            index = divIndex;
            return;
        }
    }

    else if (mult) { flag = 2; index = mulltIndex; return; }
    else if (div) { flag = 3; index = divIndex; return; }
    else if (plus && minus)
    {
        if (plusIndex < minusIndex)
        {
            flag = 4;
            index = plusIndex;
            return;
        }
        else
        {
            flag = 5;
            index = minusIndex;
            return;
        }

    }
    else if (plus) { flag = 4; index = plusIndex; return; }
    else if (minus) { flag = 5; index = minusIndex; return; }
    else { flag = 0; index = 0; }
}


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

int check_if_values_adv(string x)//to check if the input is matrix values or operations
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
int check_if_blank(string x)
{
    int flag=1;

    for(int i=33;i<127;i++)
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
    string r[]={"^","+","-","*","/","sin(","cos(","tan(","cot(","csc(","sec(","sqrt(","log(","exp("};
    for(int i=0;i<14;i++)
    {
        if((x.find(r[i]))!=-1) flag=1;
    }
    return flag;
}



string bracket_operation(string s)
{
    int bracket_count=0;
    vector <int> init;
    //cout<<"max size is: "<<init.max_size()<<endl;
    string s_sub="";
    string s_sub_done="";
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='(')
            {bracket_count++; init.push_back(i);}
        else if(s[i]==')')
            {
                bracket_count--;
                s_sub=s.substr(init.back()+1,i-init.back()-1);
                s_sub_done=normal_operation(s_sub);
                s.erase(init.back(),i-init.back()+1);
                s.insert(init.back(),s_sub_done);
                i=init.back()+s_sub_done.length()-1;
                init.pop_back();
            }
    }
          //unclosed open brackets
    if(bracket_count!=0)
        throw("Syntax Error");

        return s;
}


string normal_operation(string s)
{
    for(int i=0;i<s.length();i++)
    {
        switch(s[i])
        {

    case's':
        if(s[i+1]=='i')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            double sin_out_d=sin(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }
        else if(s[i+1]=='e')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            double sin_out_d=1/cos(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }
        else if(s[i+1]=='q')
        {
            string s_sub_num=Find_First_Number(s,i+4);
            double sin_out_d=sqrt(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,4+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }

        case 'e':

        if(s[i+1]=='x')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            double sin_out_d=exp(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }

    case 'c':
        if(s[i+1]=='o')
        {
            if(s[i+2]=='s')
            {
                string s_sub_num=Find_First_Number(s,i+3);
                double sin_out_d=cos(atof(s_sub_num.c_str()));
                string sin_out_str=to_string(sin_out_d);
                s.erase(i,3+s_sub_num.length());
                s.insert(i,sin_out_str);
                i+=sin_out_str.length()-1;
            }
            else if(s[i+2]=='t')
            {
                string s_sub_num=Find_First_Number(s,i+3);
                /*double angle=atof(s_sub_num.c_str());
                while(angle>2*3.1415)
                    angle-=2*3.1415;
                while(angle<0)
                    angle+=2*3.1415;
                if(angle==0 || (angle>3.1415-0.01 && angle<3.1415+0.01) || (angle>2*(3.1415-0.01) && angle<2*(3.1415+0.01)))
                throw("Math Error: cot");*/
                if(atof(s_sub_num.c_str())==0)
                    throw("Math error: cot");
                double sin_out_d=1/tan(atof(s_sub_num.c_str()));
                string sin_out_str=to_string(sin_out_d);
                s.erase(i,3+s_sub_num.length());
                s.insert(i,sin_out_str);
                i+=sin_out_str.length()-1;
            }
        }
        else if(s[i+1]=='s')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            double sin_out_d=1/sin(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }
    case 't':
        if(s[i+1]=='a')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            /*double angle=atof(s_sub_num.c_str());
                while(angle>2*3.1415)
                    angle-=2*3.1415;
                while(angle<0)
                    angle+=2*3.1415;
                if((angle>(3.1415-0.01)/2 && angle<(3.1415+0.01)/2)|| (angle>3*(3.1415-0.01)/2 && angle<3*(3.1415+0.01)/2))
                throw("Math Error: tan");*/
            if(atof(s_sub_num.c_str())>(3.1415-0.01)/2 && atof(s_sub_num.c_str())<(3.1415+0.01)/2)
                throw("Math Error: tan");
            double sin_out_d=tan(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }
    case 'l':
        if(s[i+1]=='o')
        {
            string s_sub_num=Find_First_Number(s,i+3);
            double sin_out_d=log(atof(s_sub_num.c_str()));
            string sin_out_str=to_string(sin_out_d);
            s.erase(i,3+s_sub_num.length());
            s.insert(i,sin_out_str);
            i+=sin_out_str.length()-1;
        }

    }
    }

    /*vector <string> number;
    vector <char> op;
    for(int i=0; i<op.size();i++)
    {
        switch(op[i])
    case'*':
        double product_d=atof(number[i])*atof(number[i+1]);
            string product_str=to_string(product_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length());
            s.insert(i,sin_out_str);
            i+=s_sub_num.length()-1;
    }*/
    string s_sub_num="";
    string s_sub_num_2="";

    for(int i=0;i<s.length();i++)
    {
        s_sub_num=Find_First_Number(s,i);
        double result_d;
        if(s[i+s_sub_num.length()]=='^')
        {
            s_sub_num_2=Find_First_Number(s,i+s_sub_num.length()+1);
            result_d=pow(atof(s_sub_num.c_str()),atof(s_sub_num_2.c_str()));
            string result_str=to_string(result_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length()+1);
            s.insert(i,result_str);
            i--;
        }
    }


    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='-') continue;
        s_sub_num=Find_First_Number(s,i);
        double result_d;
        if(s[i+s_sub_num.length()]=='*')
        {
            s_sub_num_2=Find_First_Number(s,i+s_sub_num.length()+1);
            result_d=atof(s_sub_num.c_str())*atof(s_sub_num_2.c_str());
            string result_str=to_string(result_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length()+1);
            s.insert(i,result_str);
            i--;
        }
        else if(s[i+s_sub_num.length()]=='/')
        {
            s_sub_num_2=Find_First_Number(s,i+s_sub_num.length()+1);
            if(atof(s_sub_num_2.c_str())==0)
                throw("Math Error: /");
            result_d=atof(s_sub_num.c_str())/atof(s_sub_num_2.c_str());
            string result_str=to_string(result_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length()+1);
            s.insert(i,result_str);
            i--;
        }

     }


     for(int i=0;i<s.length();i++)
     {
        double result_d;
        s_sub_num=Find_First_Number(s,i);

        if(s[i+s_sub_num.length()]=='+')
        {
            s_sub_num_2=Find_First_Number(s,i+s_sub_num.length()+1);
            result_d=atof(s_sub_num.c_str())+atof(s_sub_num_2.c_str());
            string result_str=to_string(result_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length()+1);
            s.insert(i,result_str);
            i--;
        }
        else if(s[i+s_sub_num.length()]=='-')
        {
            s_sub_num_2=Find_First_Number(s,i+s_sub_num.length()+1);
            result_d=atof(s_sub_num.c_str())-atof(s_sub_num_2.c_str());
            string result_str=to_string(result_d);
            s.erase(i,s_sub_num.length()+s_sub_num_2.length()+1);
            s.insert(i,result_str);
            i--;
        }
     }
     return s;
}

string Find_First_Number(string s, int index)
{
    string s_num="";
    for(int i=index;i<s.length();i++)
    {
        if(i==index)
        {
            while(s[i]==' '||s[i]=='-')
            {
                s_num+=s[i];
                if(!(s_num.find("--",0)==-1))
                   s_num.erase(s_num.find("--",0),2);
                i++;
            }

        }

        if((s[i]<=57 && s[i]>=48) || (s[i]=='.') || (s[i]==' ')|| (s[i]=='-'&&s[i-1]=='e') || (s[i]=='e' && ( (s[i+1]<=57 && s[i+1]>=48)||s[i+1]=='-' ) ))
            s_num+=s[i];
        else break;
    }
        return s_num;
}


double string_operation(string s)
{
    string final_result;
    final_result=bracket_operation(s);
    final_result=normal_operation(final_result);
    if(!(final_result.find("--",0)==-1))
                   final_result.erase(final_result.find("--",0),2);
    return atof(final_result.c_str());
}

int FindLimit(string s, int index,int select)
{
    int i=index;
    if(select==0)
    {
        while(!(s[i]=='+' ||s[i]=='-' || s[i]=='*'||s[i]=='/' ||s[i]=='%' || s[i]=='^' || s[i]=='(' || i==0))
        i--;
        if(s[i]=='-' && (s[i-1]=='+' || s[i-1]=='-' || s[i-1]=='*' || s[i-1]=='/' || s[i-1]=='%' || s[i-1]=='^'))
        {i--;cout<<"!!"<<endl;}
        i=(i==0)?i-1:i;
        return i+1;
    }
    else if(select==1)
    {
        while(!(s[i]=='+' ||s[i]=='-' || s[i]=='*'||s[i]=='/' ||s[i]=='%' || s[i]=='^' || s[i]==')' || (s[i]='.' && (s[i+1]=='+' ||s[i+1]=='-' || s[i+1]=='*'||s[i+1]=='/' ||s[i+1]=='%' || s[i+1]=='^') )|| i==s.length()-1) )
        i++;
        i=(i==s.length()-1)?i+1:i;
        return i-1;
    }
}

void LimitsIndex(string s,int oprtr, int& start, int& finish)
{
    if(oprtr==0){start=0;finish=0;return;}
    switch(s[oprtr])
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
        start=FindLimit(s,oprtr-1,0);
        finish=FindLimit(s,oprtr+1,1);
        break;
    default:
        start=oprtr;
        finish=s.find(')',oprtr);
        break;

    }
}



//needs includesstrem statement
string to_string(double value)
{
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

vector <string> temp_names ;
vector <Matrix> temp_matrices ;

string putMatrixInString (string x , Matrix &m ,int index1 , int index2)
{
    static int Count = 0 ;
    temp_matrices.push_back(m);
    temp_names.push_back("temp"+to_string(Count));
    x.erase(index1,index2-index1+1);
    x.insert(index1,temp_names[Count]);
    Count++;
    return x ;
}
int* index_finder (string s, string s1, int &count)

{
    int* pos;
string t = s;    count = 0;
    int pos1 ;
 do {  pos1 = t.find (s1);
  t=t.substr(pos1+1);
  if ( pos1 >= 0 )
    count ++ ;
 }
 while (pos1 >= 0);
     pos = new int [count];
int base = 0;
for ( int i=0; i<count;i++)
{
int pos2 = s.find (s1);
if (i!=0)
base=base+pos2+1;
else base=base+pos2;
pos[i]=base;

s=s.substr(pos2+1);
}
return pos ;
}

int* minus_index_finder (string s, int&c)
{
    c=0;
    for(int i=0;i<s.length();i++)
    {
    if (i!=0&& s[i]=='-' && s[i+1]==' ' && s[i-1]==' ')
        c++;
    else if (i!=0&& s[i]=='-' && s[i+1]!=' ' && s[i-1]!=' ')
        c++;
    }
    if(c==0)
    {
        int* p=NULL;

        return p;
    }
    int* p=new int[c];
    int j=0;
    for(int i=0;i<s.length();i++)
    {
      if (i!=0&&s[i]=='-' && s[i+1]==' ' && s[i-1]==' ')
        {p[j]=i; j++;}
    else if (i!=0&&(s[i]=='-' && s[i+1]!=' ' && s[i-1]!=' '))
        {p[j]=i; j++;}
    }
    return p;
}

/*	string modify_space(char* s)
{
    if( s == NULL) return (string)s;
    char * modified_s=new double [strlen(s)+1];
    for(int i=0;s[i]!= "\0" ;i++)
    {
      if (s[i]== " ")
      {   if(s[i-1] == "+" ||s[i-1] == "-" ||s[i-1] == "^" ||s[i-1] == "*" ||s[i-1] == "/")
                continue;
          if((s[i+1] == "+" ||s[i+1] == "-" ||s[i+1] == "^" ||s[i+1] == "*" ||s[i+1] == "/") && (s[i+2]== " "))
                continue;
      }
        modified_s[i]=s[i];
    }
    return (string)modified_s;
}*/

string  first_operation(string s/*,int opened_parentheses,int closed_parentheses*/)
    {
         int opened_parenthese_location;
        char* mystring = new char[s.length()+1];
        strcpy(mystring,s.c_str());
      /* if(opened_parentheses != closed_parentheses )
            {
             throw("please enter same number of opened and closed parentheses in the matrix. \n ");
             return (string) s;
            }*/
        for(int i=0;i<s.length()+1;i++)
            {
            if(mystring[i] == '(')
                opened_parenthese_location = i ;
            else if(mystring[i] == ')')
                return s.substr((opened_parenthese_location+1),(i-(opened_parenthese_location+1)));
            else
                continue;
            }
}
