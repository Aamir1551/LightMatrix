#include<stdio.h>
#include<stdlib.h>

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


        int get(int row, int column) {
            return currentVals[row + column * rows];
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

        int hashGet(int i) {
            return this->currentVals[i/columns % rows, i % columns];
        }

        Matrix operator + (Matrix x) {
            if(x.rows != this-> rows && x.columns != this->columns) {
                printf("Matrix shapes do not conform");
                exit(EXIT_FAILURE);
            }
            Matrix* c = new Matrix(rows, columns);
            for(int i = 0;i<this->NumElements;i++) {
               c->currentVals[i] = this->currentVals[i] + x.currentVals[i]; 

            }
            return *c;
        }

        Matrix operator + (Matrix *x) {
            return (*x + *this);
        }

        Matrix operator * (double a) {
            Matrix* c = new Matrix(rows, columns);
            for(int i = 0;i<this->NumElements;i++) {
               c->currentVals[i] = this->currentVals[i] * a; 
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
        }
};


int main() {

    Matrix* a = new Matrix(4, 5, 2);
    Matrix* b = new Matrix(4, 5, 8);

    //Matrix c = a + b;

    a->printAll();

    return 0;
}