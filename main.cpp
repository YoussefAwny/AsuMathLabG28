#include "header.h"


using namespace std;


vector<string> matrix_names;
vector<Matrix> matrix;
int vector_counter=0;



int main (int argc, char *argv[]){
    int x,y;
    string user_input,file_path;
    ifstream infile;
    if(argc==2){file_path=argv[1];
      infile.open(file_path.data());}
    while(argc==1||argc==2){ try{
    if(argc==2){if(!getline(infile, user_input)){break;}}
	if(argc==1) getline(cin,user_input);
    if(user_input.find('=')==-1)
        { if(user_input.find(';')==-1)
            {
              if (check_if_blank(user_input)) continue;
              else if(get_matrix_number(user_input,matrix_names)==-1) throw("ERROR: Matrix not defined");
              else {matrix[get_matrix_number(user_input,matrix_names)].print();}}
              else continue;
        }
    else if((user_input.find("rand(")!=-1) ||(user_input.find("eye(")!=-1)||(user_input.find("zeros(")!=-1)||(user_input.find("ones(")!=-1))
    {
        if(get_matrix_number(name_from_input(user_input),matrix_names)==-1)   //if new matrix
            {
                matrix_names.push_back(name_from_input(user_input));
                vector_counter++;
                int x =atof(user_input.substr(user_input.find('(')+1,user_input.find(',')-user_input.find('(')-1).data());
                int y =atof(user_input.substr(user_input.find(',')+1,user_input.find(')')-user_input.find(',')-1).data());
                if(user_input.find("rand(")!=-1)
                matrix.push_back(Matrix(x,y,3,0));
                else if(user_input.find("eye(")!=-1)
                matrix.push_back(Matrix(x,y,2,0));
                else if(user_input.find("zeros(")!=-1)
                matrix.push_back(Matrix(x,y,0,0));
                else if(user_input.find("ones(")!=-1)
                matrix.push_back(Matrix(x,y,1,1));

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
        }
        else
        {
                int i=get_matrix_number(name_from_input(user_input),matrix_names);
                int x =atof(user_input.substr(user_input.find('(')+1,user_input.find(',')-user_input.find('(')-1).data());
                int y =atof(user_input.substr(user_input.find(',')+1,user_input.find(')')-user_input.find(',')-1).data());

                if(user_input.find("rand(")!=-1)
                matrix[i]=Matrix(x,y,3,0);
                else if(user_input.find("eye(")!=-1)
                matrix[i]=Matrix(x,y,2,0);
                else if(user_input.find("zeros(")!=-1)
                matrix[i]=Matrix(x,y,0,0);
                else if(user_input.find("ones(")!=-1)
                matrix[i]=Matrix(x,y,1,1);


                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[i]<<"="<<endl;
                matrix[i].print();}
        }
    }
    else if(check_if_values_adv(user_input))
        {
            if(get_matrix_number(name_from_input(user_input),matrix_names)==-1)   //if new matrix
            {
                matrix_names.push_back(name_from_input(user_input));
                vector_counter++;
                double d=string_operation(user_input.substr(user_input.find("=")+1));
                matrix.push_back(Matrix(1,1,4,d));

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}


        }
        else
        {
                int i=get_matrix_number(name_from_input(user_input),matrix_names);
                double d=string_operation(user_input.substr(user_input.find("=")+1));
                matrix[i]=Matrix(1,1,4,d);

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[i]<<"="<<endl;
                matrix[i].print();}
        }
        }
     else if(check_if_values(user_input))
    {
        if(user_input[user_input.length()-1]==13||user_input[user_input.length()-1]==10||user_input[user_input.length()-1]==12)user_input.erase(user_input.length()-1);
        if(get_number_of_open_br(user_input)>get_number_of_close_br(user_input))
        {
            string temp;
            do
            {
                if(user_input[user_input.length()-1]==']')temp+=";";
                if(argc==1){getline(cin,temp);}
                else if(argc==2){getline(infile,temp);}
                if(temp[temp.length()-1]==13||temp[temp.length()-1]==10||temp[temp.length()-1]==12)temp.erase(temp.length()-1);
                while((temp[temp.length()-2]==' ')&&(temp[temp.length()-1]==' '))temp.erase(temp.length()-2,1);
                while((temp[1]==' ')&&(temp[0]==' '))temp.erase(0,1);
                user_input+=temp;

            }while(get_number_of_open_br(user_input)>get_number_of_close_br(user_input));
        } //getting all the strings in one line


        string temp=user_input.substr(user_input.find("=")+1);
        for(int i=0;i<vector_counter;i++)//putting the values of matrix in input
        {
            while(temp.find(matrix_names[i])!=-1)
            {
                int x=temp.find(matrix_names[i]);
                temp.erase(x,matrix_names[i].length());
                temp.insert(x,matrix[i].get_string());
            }
        }
        if(check_if_values_adv(temp.substr(temp.find("[")+1,temp.find("]")-temp.find("[")-1))) throw("Undefined Matrix");
        if(vector_counter==0 && check_if_values_adv(user_input.substr(user_input.find("[")+1))==0) throw("Undefined Matrix");
        user_input.erase(user_input.find("=")+1);
        user_input+=temp;

         while(get_number_of_open_br(user_input)>1)//matrix_conc
        {
           int pos_of_first_brc=user_input.find('[',user_input.find('[')+1);
           int pos_of_last_brc,semicolon_flag=0;
           if(user_input.find('[',pos_of_first_brc+1)>user_input.find(']',pos_of_first_brc+1))
           {
             pos_of_last_brc= user_input.find(']',user_input.find(']')+1);
           }
           else
            {
             pos_of_last_brc= user_input.find(']',user_input.find(']',user_input.find(']')+1)+1);
            }
             string to_merge=user_input.substr(pos_of_first_brc,pos_of_last_brc-pos_of_first_brc+1);
             if(user_input[pos_of_last_brc+1]==';')semicolon_flag=1;
             //if(vector_counter!=1)
             user_input.erase(pos_of_first_brc,pos_of_last_brc-pos_of_first_brc+1);
             to_merge=matrix_conc(to_merge);
             if(!semicolon_flag)to_merge+=";";
             user_input.insert(pos_of_first_brc ,to_merge);
         }
         if(get_matrix_number(name_from_input(user_input),matrix_names)==-1)   //if new matrix
            {
                matrix_names.push_back(name_from_input(user_input));
                vector_counter++;
                x =no_rows(user_input);
                y =no_columns(user_input);
                string user_input2=user_input.substr(user_input.find('[')+1);
                user_input2=Remove(user_input2,"[");
                user_input2=Remove(user_input2,"]");
                char* input_to_split= new char[user_input2.length()];
                strcpy(input_to_split, user_input2.c_str());

                double ** dpointer=new double*[x] ;//= split(x,y,input_to_split);
                string ** dpointer_s = split_string(x,y,input_to_split);
                for(int i=0;i<x;i++)
                {
                    dpointer[i]=new double[y];
                    for(int j=0;j<y;j++)
                    {
                        if(check_if_math_op((dpointer_s[i][j])))
                          dpointer[i][j]=string_operation((dpointer_s[i][j]));

                         else dpointer[i][j]=atof((dpointer_s[i][j]).data());
                    }
                }

                matrix.push_back(Matrix(x,y,dpointer));

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
        }
        else
        {
                int i=get_matrix_number(name_from_input(user_input),matrix_names);
                x =no_rows(user_input);
                y =no_columns(user_input);
                user_input=user_input.substr(user_input.find('[')+1,user_input.find(']')-user_input.find('[')-1);
                char* input_to_split= new char[user_input.length()];
                strcpy(input_to_split, user_input.c_str());
                double ** dpointer = split(x,y,input_to_split);

                matrix[i]=Matrix(x,y,dpointer);

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[i]<<"="<<endl;
                matrix[i].print();}
        }
      }
     else //if operation
     {
        if(user_input[user_input.length()-1]==13||user_input[user_input.length()-1]==10||user_input[user_input.length()-1]==12)user_input.erase(user_input.length()-1);

          int no_open_brac,no_close_brac;
          int* pos_open_brac=index_finder(user_input,"(",no_open_brac);
          int* pos_close_brac=index_finder(user_input,")",no_open_brac);
          int no_sin,no_cos,no_tan,no_cot,no_csc,no_sec,no_pow,no_sqrt,no_log,no_exp,no_multi,no_div,no_minus,no_plus;
          int* pos_sin=index_finder(user_input,"sin(",no_sin);
          int* pos_cos=index_finder(user_input,"cos(",no_cos);
          int* pos_tan=index_finder(user_input,"tan(",no_tan);
          int* pos_cot=index_finder(user_input,"cot(",no_cot);
          int* pos_csc=index_finder(user_input,"csc(",no_csc);
          int* pos_sec=index_finder(user_input,"sec(",no_sec);
          int* pos_pow=index_finder(user_input,"^",no_pow);
          int* pos_sqrt=index_finder(user_input,"sqrt(",no_sqrt);
          int* pos_log=index_finder(user_input,"log(",no_log);
          int* pos_exp=index_finder(user_input,"exp(",no_exp);
          int* pos_multi=index_finder(user_input,"*",no_multi);
          int* pos_div=index_finder(user_input,"/",no_div);
          int* pos_plus=index_finder(user_input,"+",no_plus);
          int* pos_minus=minus_index_finder(user_input,no_minus);

          string out=name_from_input(user_input);
          user_input=user_input.substr(user_input.find("=")+1);
          while(no_open_brac!=1 && no_close_brac!=1)
          {
             string current_brackets=first_operation(user_input);
             int current_operator_index,current_operator,first,last;
             do{
             Operation(current_brackets,current_operator_index,current_operator);
             LimitsIndex(current_brackets,current_operator_index,first,last);
             cout<<current_brackets<<" "<<current_operator_index<<" "<<current_operator<<" "<<first<<" "<<last<<endl;
             string in1,in2;
             int int_flag1=0,int_flag2=0,in1_index,in2_index,temp_flag1=0,temp_flag2=0;
             if(current_brackets[current_operator_index-1]=='.'){current_brackets.erase(current_operator_index-1,1);}
             in1=space_remover(current_brackets.substr(first,current_operator_index-first));
             in2=space_remover(current_brackets.substr(current_operator_index+1,last-current_operator_index));

             if(get_matrix_number(in1,matrix_names)!=-1){in1_index=get_matrix_number(in1,matrix_names);}
             else if (get_matrix_number(in1,temp_names)!=-1){in1_index=get_matrix_number(in1,temp_names);temp_flag1=1;}
             else if (check_if_number(in1)){int_flag1=1;}
             else throw("Matrix Not Defined");

             if(get_matrix_number(in2,matrix_names)!=-1){in2_index=get_matrix_number(in2,matrix_names);}
             else if (get_matrix_number(in2,temp_names)!=-1){in2_index=get_matrix_number(in2,temp_names);temp_flag2=1;}
             else if (check_if_number(in2)){int_flag2=1;}
             else throw("Matrix Not Defined");

             switch(current_operator)
             {case 1:
                 {


                 }
             case 2:
                 {

                 }
             case 3:
                 {

                 }
             case 4:
                 {

                 }
             case 5:
                 {

                 }}

             } while(current_operator!=0);

break;
          }


         if(!(user_input.find('+')==-1))
         {
             if(user_input[user_input.find('+')-1]=='.')user_input.erase(user_input.find('+')-1,1);
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find('+')-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find('+')+1));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);
             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;
                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)]));
                     matrix[vector_counter-1]+=atof(in1.data());
                 }

                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1]+=atof(in2.data());
                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1].add(matrix[get_matrix_number(in2,matrix_names)]);
                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }
             else //
             {
                 if(check_if_number(in1))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in2,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]+=atof(in1.data());
                 }

                 else if(check_if_number(in2))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]+=atof(in2.data());
                 }
                 else
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]+=matrix[get_matrix_number(in2,matrix_names)];
                 }

                 if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
             }
         }
         else if(!(user_input.find('-')==-1))
         {if(user_input[user_input.find('-')-1]=='.')user_input.erase(user_input.find('-')-1,1);
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find('-')-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find('-')+1));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);
             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;
                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)].get_rows(),matrix[get_matrix_number(in2,matrix_names)].get_columns(),4,atof(in1.data())));
                     matrix[vector_counter-1]-=matrix[get_matrix_number(in2,matrix_names)];
                 }

                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1]-=atof(in2.data());
                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1].sub(matrix[get_matrix_number(in2,matrix_names)]);
                 }
                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }
             else
             {
                 if(check_if_number(in1))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=atof(in1.data());
                     matrix[get_matrix_number(out,matrix_names)]-=matrix[get_matrix_number(in2,matrix_names)];
                 }

                 else if(check_if_number(in2))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]-=atof(in2.data());
                 }
                 else
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]-=matrix[get_matrix_number(in2,matrix_names)];
                 }

                 if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}

             }

         }
         else if(!(user_input.find('\'')==-1))
         {if(user_input[user_input.find('\'')-1]=='.')user_input.erase(user_input.find('\'')-1,1);
             string out,in1;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find('\'')-user_input.find('=')-1));
             if(in1[in1.length()-1]==13||in1[in1.length()-1]==10||in1[in1.length()-1]==12)in1.erase(in1.length()-1);
             if(in1[in1.length()-1]==';')in1.erase(in1.length()-1);

             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;
                 matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].getTranspose()));
                  if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}

             }
             else
             {
                 matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)].getTranspose();
                 if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
             }
         }
         else if(!(user_input.find("./")==-1))
         {
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find("./")-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find("./")+2));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);

             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;

                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)].get_rows(),matrix[get_matrix_number(in2,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::div2(atof(in1.data()),matrix[get_matrix_number(in2,matrix_names)]);

                 }
                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].get_rows(),matrix[get_matrix_number(in1,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::div2(matrix[get_matrix_number(in1,matrix_names)],atof(in2.data()));

                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].get_rows(),matrix[get_matrix_number(in1,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::div2(matrix[get_matrix_number(in1,matrix_names)],matrix[get_matrix_number(in2,matrix_names)]);

                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }

            else
            {
                if(check_if_number(in1))
                 {
                    matrix[get_matrix_number(out,matrix_names)]=Matrix::div2(atof(in1.data()),matrix[get_matrix_number(in2,matrix_names)]);

                 }
                 else if(check_if_number(in2))
                 {
                   matrix[get_matrix_number(out,matrix_names)]=Matrix::div2(matrix[get_matrix_number(in1,matrix_names)],atof(in2.data()));

                 }
                 else
                 {
                    matrix[get_matrix_number(out,matrix_names)]=Matrix::div2(matrix[get_matrix_number(in1,matrix_names)],matrix[get_matrix_number(in2,matrix_names)]);

                 }

                 if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
            }

            }
            else if(!(user_input.find(".*")==-1))
         {
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find(".*")-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find(".*")+2));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);

             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;

                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)].get_rows(),matrix[get_matrix_number(in2,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::mul2(atof(in1.data()),matrix[get_matrix_number(in2,matrix_names)]);

                 }
                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].get_rows(),matrix[get_matrix_number(in1,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::mul2(matrix[get_matrix_number(in1,matrix_names)],atof(in2.data()));

                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].get_rows(),matrix[get_matrix_number(in1,matrix_names)].get_columns(),0,0));
                     matrix[vector_counter-1]=Matrix::mul2(matrix[get_matrix_number(in1,matrix_names)],matrix[get_matrix_number(in2,matrix_names)]);

                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }

            else
            {
                if(check_if_number(in1))
                 {
                    matrix[get_matrix_number(out,matrix_names)]=Matrix::mul2(atof(in1.data()),matrix[get_matrix_number(in2,matrix_names)]);

                 }
                 else if(check_if_number(in2))
                 {
                   matrix[get_matrix_number(out,matrix_names)]=Matrix::mul2(matrix[get_matrix_number(in1,matrix_names)],atof(in2.data()));

                 }
                 else
                 {
                    matrix[get_matrix_number(out,matrix_names)]=Matrix::mul2(matrix[get_matrix_number(in1,matrix_names)],matrix[get_matrix_number(in2,matrix_names)]);

                 }

                 if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
            }

            }

      else if(!(user_input.find("inv(")==-1))
       {
           string out,in1;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('(')+1,user_input.find(")")-user_input.find('(')-1));
             if(in1[in1.length()-1]==13||in1[in1.length()-1]==10||in1[in1.length()-1]==12)in1.erase(in1.length()-1);
             if(in1[in1.length()-1]==';')in1.erase(in1.length()-1);

             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)].getInverse()));
                 vector_counter++;
                //cout<<matrix[vector_counter-1].getDeterminant()<<endl;
                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}

             }
             else
             {
                matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)].getInverse();
                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
             }

       }
       if((!(user_input.find('*')==-1)&&(user_input.find('.')==-1)))
         {
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find('*')-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find('*')+1));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);
             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;
                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)]));
                     matrix[vector_counter-1]*=atof(in1.data());
                 }

                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1]*=atof(in2.data());
                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1].mul(matrix[get_matrix_number(in2,matrix_names)]);
                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }
             else //
             {
                 if(check_if_number(in1))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in2,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]*=atof(in1.data());
                 }

                 else if(check_if_number(in2))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]*=atof(in2.data());
                 }
                 else
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]*=matrix[get_matrix_number(in2,matrix_names)];
                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
             }
         }

         if((!(user_input.find('/')==-1))&&(user_input.find('.')==-1))
         {
             string out,in1,in2;
             out=name_from_input(user_input);
             in1=space_remover(user_input.substr(user_input.find('=')+1,user_input.find('/')-user_input.find('=')-1));
             in2=space_remover(user_input.substr(user_input.find('/')+1));
             if(in2[in2.length()-1]==13||in2[in2.length()-1]==10||in2[in2.length()-1]==12)in2.erase(in2.length()-1);
             if(in2[in2.length()-1]==';')in2.erase(in2.length()-1);
             if(get_matrix_number(out,matrix_names)==-1)
             {
                 matrix_names.push_back(out);
                 vector_counter++;
                 if(check_if_number(in1))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in2,matrix_names)].get_rows(),matrix[get_matrix_number(in2,matrix_names)].get_columns(),4,atof(in1.data())));
                     matrix[vector_counter-1]/=matrix[get_matrix_number(in2,matrix_names)];
                 }

                 else if(check_if_number(in2))
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1]/=atof(in2.data());
                 }
                 else
                 {
                     matrix.push_back(Matrix(matrix[get_matrix_number(in1,matrix_names)]));
                     matrix[vector_counter-1].div(matrix[get_matrix_number(in2,matrix_names)]);
                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[vector_counter-1]<<"="<<endl;
                matrix[vector_counter-1].print();}
            }
             else //
             {
                 if(check_if_number(in1))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=atof(in1.data());
                     matrix[get_matrix_number(out,matrix_names)]/=matrix[get_matrix_number(in2,matrix_names)];
                 }


                 else if(check_if_number(in2))
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]/=atof(in2.data());
                 }
                 else
                 {
                     matrix[get_matrix_number(out,matrix_names)]=matrix[get_matrix_number(in1,matrix_names)];
                     matrix[get_matrix_number(out,matrix_names)]/=matrix[get_matrix_number(in2,matrix_names)];
                 }

                if(user_input[user_input.length()-1]!=';'){
                cout<<matrix_names[get_matrix_number(out,matrix_names)]<<"="<<endl;
                matrix[get_matrix_number(out,matrix_names)].print();}
             }
         }

     }
        }//try
      catch(char const* x){cout<<x<<endl;}

    }//input loop
      if(argc==2) infile.close();


	return 0 ;
	}
