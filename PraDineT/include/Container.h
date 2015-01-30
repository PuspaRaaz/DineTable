#ifndef __CONTAINER__
#define __CONTAINER__

template <typename T>
struct Dual
{
	T x, y;
	Dual(T X, T Y):x(X), y(Y){}
};

template <typename T>
struct Threesome
{
	T x, y, z;
	Threesome(T XX, T YY, T ZZ):x(XX), y(YY), z(ZZ){}
};

template <typename T>
struct Foursome
{
	T x, y, z, w;
	Foursome(T XXX, T YYY, T ZZZ, T WWW):x(XXX), y(YYY), z(ZZZ), w(WWW){}
};

#endif