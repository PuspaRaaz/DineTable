#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

class Matrix
{
private:
	int row, col;
public:
	float *data;

	//constructor
	Matrix(int r, int c):row(r),col(c){
		data = new float[row * col];
	}

	//copy constructor
	Matrix(const Matrix& mat){
		row = mat.row;
		col = mat.col;
		data = new float[row * col];
		data = mat.data;
	}

	//destructor
	~Matrix(){};

	float& operator() (int r, int c); //returns the value of Matrix(r,c)
	float& operator() (int pos); //returns the value of Matrix(pos) = Matrix.data[pos]
	Matrix operator+ (Matrix& mat); //returns this + mat
	Matrix operator- (Matrix& mat); //returns this - mat
	Matrix operator* (Matrix& mat); //returns this * mat (cross-product)
	void displayMat(); //display matrix in row*col form
};

float& Matrix::operator() (int r, int c){
	int pos = col*r + c;
	return data[pos];
}

float& Matrix::operator() (int pos){
	return data[pos];
}

Matrix Matrix::operator+ (Matrix& mat){
	if(row != mat.row && col != mat.col)
		throw "ERROR";
	Matrix res(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			int pos = (col)*i + j;
			res(i,j) = data[pos] + mat(i,j);
		}
	}
	return res;
}

Matrix Matrix::operator- (Matrix& mat){
	if(row != mat.row && col != mat.col)
		throw "ERROR";
	Matrix res(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			int pos = (col)*i + j;
			res(i,j) = data[pos] - mat(i,j);
		}
	}
	return res;
}

Matrix Matrix::operator* (Matrix& mat){
	if(col != mat.row)
		throw "ERROR";
	Matrix res(row, mat.col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < mat.col; j++){
			res(i,j) = 0;
			for (int k = 0; k < col; k++){
				int pos = (col)*i + k;
				res(i,j) += data[pos] * mat(k,j);
			}
		}
	}
	return res;
}

void Matrix::displayMat(){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			int pos = col*i + j;
			std::cout<<data[pos]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

#endif