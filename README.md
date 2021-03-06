# AsuMathsLab
**Intro**
==========
AsuMathsLab is a project aimed at providing a well defined enviroment for running airethmatic operations on matrices,
It supports a wide range of operations including: summation,subtraction,multiplication,division,inversion,determinant and transpose calculation.

It can be considered as a full C++ version of Matlab.

**Specifications**
====================
*Using C++.*

*Development under Linux, it is made to run perfectly under unix based systems.*

*g++ compiler is used.*



**Developers**
===============
This project is written by a group of engineering students at Ain Shams university.
The students are:

*-Paula Magdy*

*-Mark Maged*

*-Youssef Awny*

*-Youssef Adel*

*-George Mohsen*

*-Kirollos Sherif Wadie*



**Operating System**
=======================
AsuMathsLab is made to run perfectly on linux based systems, as g++ compiler is used.



# Project phases

Project execution is divided into three phases.

Phase 1 is ready to use and we still have another 2 to do.

## Phase 1

targets core operations:

  *Support dynamic creation and destruction of matrices.*

  *Support addition, subtraction, division, multiplication, Transpose, and inversion.* 
 
  *Process input user commands as well as file inputs.*

## Phase 2

targets advanced operations and tuning.

*Support trignometric functions, logarithmic functions, roots and powers.*

*Support mathematical expressions either with dot or not.*

*Support flexible matrix parser.*

*Support error handling.*

## Phase 3

more advanced system operations.


**Syntax**
=============

Provides user-friendly coding technique for users to write the input. It could be perfectly matched with Matlab's coding technique.
Please notice the following examples to be able to use the program:

  A = [8.9 7.3 4.8 2.4; 2.3 6.5 8.9 1.2; 4.9 3.8 7.2 7.5; 9.8 3.4 7.5 8.9]
  
B = [1.2 5.7 4.2 1.4; 6.3 2.5 8.1 3.1; 6.4 2.8 7.1 8.1; 3.2 5.1 7.2 6.2]

C = A + B

D = A - B

H = B'

G = 1 ./ A

E = A * B

F = A / B

L=inv(A)

**For the second phase:**

  A = 5.5 + 12 * sin(0.4) + 2.2^4;
  
  B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]];
  
  C = [[B [3.4; 2.1; 3.5+9.1]] 
     1.2^3 3+1.2 15/(2.1+10*sin(0.12))  1.2]
     
  D = rand(4,4)
  
  E = eye(4, 4)
  
  F = zeros(2, 3)
  
  G = ones(3, 6)
  
L = (1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))

X = ((C*D .+ 4)./2.1 + sqrt(D))./C.^2

Y = (C^3 * sin(1./D))^(0.1)

