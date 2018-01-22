#include <iostream>
#include <iomanip>
#include "matrixphase2.h"

using namespace std;

string Matrix::modify(char* s)
{
    if( s == NULL) return (string)s;
    char * modified_s=new double [s.length()+1];
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
}

