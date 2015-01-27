class Matrix
{
    private:
        float* data;
        int row, col;
    public:
        Matrix(int rows,int column) : row(rows), col(column)
        {
            data = new float[row*col];
        }

        Matrix(const Matrix& mat)
        {
            row = mat.row;
            col = mat.col;
            data = new float[row*col];
            data = mat.data;
        }

        float& operator() (int r, int c);
        float& operator() (int pos) ;
        Matrix operator * (Matrix& mat);
        Matrix operator + (Matrix& mat);
        Matrix operator - (Matrix& mat);

};

Matrix Matrix::operator*(Matrix& mat)
{
    if (this->col != mat.row) throw "ERROR";
    int pos;
    Matrix res(row,mat.col);

    for(int i = 0; i< this->row; i++ )
    {
        for (int j= 0; j< mat.col; j++)
        {
            res(i,j) = 0;
            for(int k=0; k< this->col; k++)
            {
                pos = (this->col)*i + k ; // ith row kth column
                res(i,j) += data[pos] * mat(k,j);
            }
        }
    }
    return res;
}

float& Matrix::operator() (int r, int c)
{
    int pos = col* r + c ;
    return data[pos];
}

float& Matrix::operator() (int pos)
{
    return data[pos];
}

Matrix Matrix::operator+(Matrix& mat)
{
    if ((this->row != mat.row) || (this->col != mat.col))
        throw "ERROR";
    Matrix res(this->row,this->col);
    int pos;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            res(i,j) = data[pos] + mat(i,j);
        }
    }
    return res;
}

Matrix Matrix::operator - (Matrix& mat)
{
    if ((this->row != mat.row) || (this->col != mat.col))
        throw "ERROR";
    Matrix res(this->row,this->col);
    int pos;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            res(i,j) = data[pos] - mat(i,j);
        }
    }
    return res;
}

//
//int main()
//{
//    Matrix m(3,3);
//    Matrix n(3,3);
//
//    m(0) = 1; m(1) = 2; m(2) = 3;
//    m(3) = 4; m(4) = 5; m(5) = 6;
//    m(6) = 2; m(7) = 4; m(8) = 5;
//
//    n(0) = 1; n(1) = 0; n(2) = 0;
//    n(3) = 0; n(4) = 1; n(5) = 0;
//    n(6) = 0; n(7) = 0; n(8) = 1;
//
//    n = m * n;
//
//    for (int i =0; i< 3; i++,std::cout << std::endl)
//        for (int j =0; j< 3; j++)
//            std::cout << n(i,j) << " ";
//
//}
