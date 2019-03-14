#include "Matrix.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

int main(int argc, char* argv[]) {

    //to compile run script: g++ main.cpp Matrix.cpp && ./a.out

    Matrix *a = new Matrix(2, 2, 10);
    Matrix *b = new Matrix(2, 2, 8);

    double vals[] = {1,4,7,4, 7, 2};
    Matrix *v = new Matrix(vals, 2, 3);


    double valsg[] = {2,1,9,4, 1, 6, 4, 8, 2, 4, 2, 5};
    Matrix *g = new Matrix(valsg, 3, 4);

    v->printAll();
    g->printAll();

    Matrix *c = Matrix::matMul(v, g);

    (c->printAll());

    return 0;
}