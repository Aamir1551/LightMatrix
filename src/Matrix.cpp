#include "Matrix.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//TODO functions need to be refactored and need to recftify functions for Tvalues
//TODO Add comments & use constants as params (const par, const par*, ...)


void Matrix::initMatrix(int rows, int columns) {
    Nvalues = new double[rows * columns];
    Tvalues = new double[rows * columns];
    currentVals = Nvalues;
    this->rows = rows;
    this->columns = columns;
    this->NumElements = rows * columns;
}
    
Matrix::Matrix(int rows, int columns, double val) {
    initMatrix(rows, columns);
    if(val != 0) {
        for(int i = 0;i<NumElements;i++) {
            this->currentVals[i] = val;
        }
    }
}

Matrix::Matrix(double * const a, int rows, int columns) {
    initMatrix(rows, columns);
    memcpy(this->Nvalues, a, sizeof(*a) * rows * columns);
    //also need to implement corresponding function for Tvalues
}


double Matrix::get(int i, int j) {
    return currentVals[columns*i + j];
}

void Matrix::transpose() {
    currentVals = Tvalues;
    int t = rows;
    rows = columns;
    columns = t;
}

Matrix* Matrix::clone() {
    Matrix *c = new Matrix(rows, columns, 0);
    for(int i = 0;i<NumElements;i++) {
        c->Nvalues[i] = this->Nvalues[i];
        c->Tvalues[i] = this->Tvalues[i];
    }
    if(this->currentVals == this->Nvalues) {
        c->currentVals = c->Nvalues;
    } else if (this->currentVals == this-> Tvalues) {
        c->currentVals = c->Tvalues;
    } else {
        printf("Current vals is not pointing to correct vars");
        exit(EXIT_FAILURE);
    };
    return c;
}

double Matrix::hashGet(int i) {
    return this->currentVals[i/columns % rows, i % columns];
}

Matrix* Matrix::operator + (Matrix * const x) {
    if(x->rows != this -> rows || x->columns != this->columns) {
        printf("Matrix shapes do not conform for Matrix addidtion\n");
        exit(EXIT_FAILURE);
    }
    Matrix* c = new Matrix(rows, columns, 0);
    for(int i = 0;i<this->NumElements;i++) {
        c->currentVals[i] = this->currentVals[i] + x->currentVals[i]; 
    }
    return c;
}

Matrix* Matrix::operator * (double d) {
    Matrix* c = new Matrix(rows, columns, 0);
    for(int i = 0;i<this->NumElements;i++) {
        c->currentVals[i] = this->currentVals[i] * d; 
    }
    return c;
}

Matrix* Matrix::operator - ( Matrix * const x) {
    return *this + ( *x * -1) ;
} 

void Matrix::printAll() {
    for(int i=0;i<NumElements;i++) {
        if(i % columns == 0) {
            printf("\n");
        }
        printf("%f ", this->currentVals[i]);
    }
    printf("\n");
}

void Matrix::printAll(Matrix * const x) {
    x->printAll();
}

void Matrix::set(int i, int j,double d) {
    this->Nvalues[i*columns + j] = d;
    this->Tvalues[j*rows + i] = d;
}

Matrix* Matrix::matMul(Matrix * const x, Matrix * const y) {
    //WILL BE REIMPLEMTED USING THE STRASSEN ALGO 
    if(x->columns != y->rows) {
        printf("shapes do not conform for Matrix Multiplication \n");
        exit(EXIT_FAILURE);
    }
    Matrix *c = new Matrix(x->rows, y->columns, 0);
    for(int i=0;i<x->rows;i++) {
        for(int j = 0;j<y->columns;j++) {
            for(int k = 0;k<x->columns;k++) {
                c->set(i ,j, (*c).get(i, j) + x->get(i, k) * y->get(k, j));
            }
        }
    }
    return c;
}
