#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//TODO functions need to be refactored and need to recftify functions for Tvalues

class Matrix{
    
    private:
        int rows;
        int columns;
        int NumElements;

        void initMatrix(int rows, int columns) {
            Nvalues = new double[rows * columns];
            Tvalues = new double[rows * columns];
            currentVals = Nvalues;

            this->rows = rows;
            this->columns = columns;
            this->NumElements = rows * columns;
        }

    public:

        double *Nvalues;
        double *Tvalues;
        double *currentVals;

        Matrix(int rows, int columns, double val = 0) {
            initMatrix(rows, columns);
            if(val != 0) {
                for(int i = 0;i<NumElements;i++) {
                    this->currentVals[i] = val;
                }
            }
        }

        Matrix static makeMatrix(int rows, int columns, double val = 0) {
            return *(new Matrix(rows, columns, val));
        }

        Matrix(double *a, int rows, int columns) {
            initMatrix(rows, columns);
            memcpy(this->Nvalues, a, sizeof(*a) * rows * columns);
            //also need to implement corresponding function for Tvalues
        }


        double get(int i, int j) {
            return currentVals[columns*i + j ];
        }

        void transpose() {
            currentVals = Tvalues;
            int t = rows;
            rows = columns;
            columns = t;
        }

        Matrix clone() {
            Matrix *c = new Matrix(rows, columns);
            for(int i = 0;i<NumElements;i++) {
                c->Nvalues[i] = this->Nvalues[i];
                c->Tvalues[i] = this->Tvalues[i];
            }
            if(this->currentVals == c->Nvalues) {
                c->currentVals = c->Nvalues;
            } else if (this->currentVals == c-> Tvalues) {
                c->currentVals = c->Tvalues;
            } else {
                printf("Current vals is not pointing to correct vars");
                exit(EXIT_FAILURE);
            };
            return *c;
        }

        double hashGet(int i) {
            return this->currentVals[i/columns % rows, i % columns];
        }

        Matrix operator + (Matrix x) {
            if(x.rows != this -> rows || x.columns != this->columns) {
                printf("Matrix shapes do not conform for Matrix addidtion\n");
                exit(EXIT_FAILURE);
            }
            Matrix* c = new Matrix(rows, columns);
            for(int i = 0;i<this->NumElements;i++) {
               c->currentVals[i] = this->currentVals[i] + x.currentVals[i]; 
            }
            return *c;
        }

        Matrix operator * (double d) {
            Matrix* c = new Matrix(rows, columns);
            for(int i = 0;i<this->NumElements;i++) {
               c->currentVals[i] = this->currentVals[i] * d; 
            }
            return *c;
        }

        Matrix operator - (Matrix x) {
           return *this + (x * -1) ;
        } 

        void printAll() {
            for(int i=0;i<NumElements;i++) {
                if(i % columns == 0) {
                    printf("\n");
                }
                printf("%f ", this->currentVals[i]);
            }
            printf("\n");
        }

        static void printAll(Matrix *x) {
            (x)->printAll();
        }

        void set(int i, int j,double d) {
            this->Nvalues[i*columns + j] = d;
            this->Tvalues[j*rows + i] = d;
        }

        static Matrix* matMul(Matrix x, Matrix y) {
            //WILL BE REIMPLEMTED USING THE STRASSEN ALGO 
            if(x.columns != y.rows) {
                printf("shapes do not conform for Matrix Multiplication \n");
                exit(EXIT_FAILURE);
            }
            Matrix *c = new Matrix(x.rows, y.columns, 0);
            for(int i=0;i<x.rows;i++) {
                for(int j = 0;j<y.columns;j++) {
                    for(int k = 0;k<x.columns;k++) {
                        c->set(i ,j, (*c).get(i, j) + x.get(i, k) * y.get(k, j));
                    }
                }
            }
            return c;
        }
};


int main() {

    Matrix a = Matrix::makeMatrix(2, 2, 10);
    Matrix b = Matrix::makeMatrix(2, 2, 8);

    double vals[] = {1,4,7,4, 7, 2};
    Matrix *v = new Matrix(vals, 2, 3);


    double valsg[] = {2,1,9,4, 1, 6, 4, 8, 2, 4, 2, 5};
    Matrix *g = new Matrix(valsg, 3, 4);

    v->printAll();
    g->printAll();

    Matrix *c = Matrix::matMul(*v, *g);

    (c->printAll());

    return 0;
}