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

        Matrix(int rows, int columns, double val = 0);

        //~Matrix();

        Matrix(double *a, int rows, int columns);


        double get(int i, int j);

        void transpose();

        Matrix* clone();

        double hashGet(int i);

        Matrix* operator + (Matrix *x);

        Matrix* operator * (double d);

        Matrix* operator - (Matrix *x);

        void printAll();

        static void printAll(Matrix *x);

        void set(int i, int j,double d);

        static Matrix* matMul(Matrix *x, Matrix *y);
};

#endif