#ifndef MATRIX_H
#define MATRIX_H


class Matrix{
    
    private:
        int rows;
        int columns;
        int NumElements;

        void initMatrix(int rows, int columns);

    public:

        double *Nvalues;
        double *Tvalues;
        double *currentVals;

        Matrix(int rows, int columns, double val);

        //~Matrix();

        Matrix(double * const a, int rows, int columns);


        double get(int i, int j);

        void transpose();

        Matrix* clone();

        double hashGet(int i);

        Matrix* operator + ( Matrix *const x);

        Matrix* operator * (double d);

        Matrix* operator - ( Matrix * const x);

        void printAll();

        static void printAll( Matrix *const x);

        void set(int i, int j,double d);

        static Matrix* matMul( Matrix *const x,  Matrix *const y);
};

#endif