#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <string>

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
	Matrix(const Matrix& m){
		data = new float[m.row*m.col];
		row = m.row;
		col = m.col;
		memcpy(data, m.data, row*col*sizeof(float));
	}

	//destructor
	~Matrix(){
		if(this->data){
			delete []data;
		}
	};

	//matrix initializer, receives any numbers of arguments
	template<typename... Types>
	void init(Types... args){
		const int size = sizeof...(args);
		if(size != row*col)
			return;
		float temp[] = {static_cast<float>(args)...};
		memcpy(data, temp, row*col*sizeof(float));
	}

	const float& operator() (int, int) const;
	const float& operator() (int) const;
	float& operator() (int, int); //returns the value of Matrix(r,c)
	float& operator() (int); //returns the value of Matrix(pos) = Matrix.data[pos]
	Matrix operator+ (const Matrix&) const; //returns this + mat
	Matrix operator- (const Matrix&) const; //returns this - mat
	Matrix operator* (const Matrix&) const; //returns this * mat (cross-product)
	void operator%= (const Matrix&); //returns mat * this (cross product)
	void operator= (const Matrix&); //assignment operator overloaded
	void displayMat(); //display matrix in row*col form
	int giveRow(){return row;}
	int giveCol(){return col;}
};

const float& Matrix::operator() (int r, int c) const {
	int pos = col*r + c;
	return data[pos];
}

const float& Matrix::operator() (int pos) const {
	return data[pos];
}

float& Matrix::operator() (int r, int c){
	int pos = col*r + c;
	return data[pos];
}

float& Matrix::operator() (int pos){
	return data[pos];
}

void Matrix::operator= (const Matrix& mat){
	if(this == &mat)
		return;
	if(row*col != mat.row*mat.col){
		delete []data;
		data = new float[mat.row*mat.col];
	}
	row = mat.row;
	col = mat.col;
	memcpy(data, mat.data, row*col*sizeof(float));
}

Matrix Matrix::operator+ (const Matrix& mat) const{
	if(row != mat.row && col != mat.col){
		std::cout<<"Unequal matrix dimensions. (operator+)\n";
		throw "ERROR";
	}
	Matrix res(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			int pos = (col)*i + j;
			res(i,j) = data[pos] + mat(i,j);
		}
	}
	return res;
}

Matrix Matrix::operator- (const Matrix& mat) const{
	if(row != mat.row && col != mat.col){
		std::cout<<"Unequal matrix dimensions. (operator-)\n";
		throw "ERROR";
	}
	Matrix res(row, col);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			int pos = (col)*i + j;
			res(i,j) = data[pos] - mat(i,j);
		}
	}
	return res;
}

Matrix Matrix::operator* (const Matrix& mat) const{
	if(col != mat.row){
		std::cout<<"Unequal matrix dimensions. (operator*)\n";
		throw "ERROR";
	}
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

void Matrix::operator%= (const Matrix& mat){
	Matrix temp = mat*(*this);
	*this = temp;
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