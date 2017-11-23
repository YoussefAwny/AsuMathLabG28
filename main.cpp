#include "header.h"


using namespace std;


int main (int argc, char *argv[]){

    vector<string> matrix_names;
    vector<Matrix> matrix;
    int x,y,vector_counter=0;
    string user_input,file_path;
    ifstream infile;
    if(argc==2){file_path=argv[1];
      infile.open(file_path.data());}
    while(argc==1||argc==2){ try{
    if(argc==2){if(!getline(infile, user_input)){break;}}
	if(argc==1) getline(cin,user_input);
	if(check_if_values(user_input))
    {
        if(get_number_of_open_br(user_input)>get_number_of_close_br(user_input))
        {
            string temp;
            if(user_input[user_input.length()-1]==13||user_input[user_input.length()-1]==10||user_input[user_input.length()-1]==12)user_input.erase(user_input.length()-1);
            do
            {
                if(argc==1){getline(cin,temp);}
                else if(argc==2){getline(infile,temp);}
                if(temp[temp.length()-1]==13||temp[temp.length()-1]==10||temp[temp.length()-1]==12)temp.erase(temp.length()-1);
                if(temp[temp.length()-1]==']')temp+=",";
                user_input+=temp;

            }while(get_number_of_open_br(user_input)>get_number_of_close_br(user_input));
        }
         if(get_matrix_number(name_from_input(user_input),matrix_names)==-1)   //if new matrix
            {
                matrix_names.push_back(name_from_input(user_input));
                vector_counter++;
                x =no_rows(user_input);
                y =no_columns(user_input);
                string user_input2=user_input.substr(user_input.find('[')+1,user_input.find(']')-user_input.find('[')-1);
                char* input_to_split= new char[user_input2.length()];
                strcpy(input_to_split, user_input2.c_str());
                double ** dpointer = split(x,y,input_to_split);
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
         if(!(user_input.find('+')==-1))
         {
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
         {
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
         {
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
       if(!(user_input.find('*')==-1))
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
