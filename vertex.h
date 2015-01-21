#ifndef _VERTEX_H
#define _VERTEX_H

struct vertex
{
	int x, y;
	vertex(){}
	vertex(int X, int Y):x(X), y(Y){}
	bool vertex::operator==(const vertex & point)
	{
		return ((x == point.x) && (y == point.y));
	}

	bool vertex::operator>(const vertex & point)
	{
		return (x>point.x) || ((x==point.x) && (y>point.y));
	}

	bool vertex::operator<(const vertex & point)
	{
		return (x<point.x) || ((x==point.x) && (y<point.y));
	}

	vertex vertex::operator+(const vertex & point)
	{
		return vertex(x + point.x, y + point.y);
	}

	vertex vertex::operator-(const vertex & point)
	{
		return vertex(x - point.x, y - point.y);
	}
};