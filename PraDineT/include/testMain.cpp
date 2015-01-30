#include "Basic.h"
#include "Color.h"
#include "Container.h"
#include "Exception.h"
#include "Matrix.h"
#include "Object.h"
#include "Point.h"
#include "Vector.h"

int main(){
	//Basic.h usage
	std::cout<<"\nBasic.h"<<std::endl;

	float a = -5.32, b = 0.69, c = 5.32;
	std::cout<<"pi = "<<Basic::PI<<std::endl;
	std::cout<<"precision = "<<Basic::PRECISION<<std::endl;
	std::cout<<"ROUNDOFF(a) = "<<Basic::ROUNDOFF(a)<<std::endl;
	std::cout<<"a == b : "<<Basic::EQUAL(a, b)<<std::endl;
	std::cout<<"a == c : "<<Basic::EQUAL(a, c)<<std::endl;
	std::cout<<"ABS(a) = "<<Basic::ABS(a)<<std::endl;
	std::cout<<"MAX(a & b) = "<<Basic::MAX(a, b)<<std::endl;
	std::cout<<"MIN(a & b) = "<<Basic::MIN(a,b)<<std::endl;
	std::cout<<"Degree(pi/4) : "<<Basic::DEGREE(Basic::PI/4)<<std::endl;
	std::cout<<"RADIAN(270) : "<<Basic::RADIAN(270)<<std::endl;
	Basic::SWAP(a, b);
	std::cout<<"SWAP(a & b) = "<<a<<" "<<b<<std::endl;

	//Color.h usage
	std::cout<<"\nColor.h"<<std::endl;
	
	//Container.h usage
	std::cout<<"\nContainer.h"<<std::endl;

	Dual<float> aa(5,7), bb(5.32, -0.69);
	Threesome<int> aaa(0, 6, 9), bbb(-5, -3, -2);
	Foursome<int> aaaa(2, 0, 6, 9), bbbb(0, 5, 3, 2);
	std::cout<<aa.x<<" "<<aa.y<<" \t"<<bb.x<<" "<<bb.y<<std::endl;
	std::cout<<aaa.x<<" "<<aaa.y<<" "<<aaa.z<<" \t"<<bbb.x<<" "<<bbb.y<<" "<<bbb.z<<std::endl;
	std::cout<<aaaa.x<<" "<<aaaa.y<<" "<<aaaa.z<<" "<<aaaa.w<<" \t"<<bbbb.x<<" "<<bbbb.y<<" "<<bbbb.z<<" "<<bbbb.w<<std::endl;	
	
	//Exception.h usage
	std::cout<<"\nException.h"<<std::endl;

	Vector aV(), bV(2, 0, 6, 9);
	Vector cV(bV);
	// std::cout<<aV.x<<" "<<aV.y<<" "<<aV.z<<" "<<aV.w;
	// std::cout<<"\t"<<bV.x<<" "<<bV.y<<" "<<bV.z<<" "<<bV.w;
	// std::cout<<"\t"<<cV.x<<" "<<cV.y<<" "<<cV.z<<" "<<cV.w<<std::endl;

	//Matrix.h usage
	std::cout<<"\nMatrix.h"<<std::endl;

	Matrix aM(3,3);
	float arr[9] = {0, 6, 9, 2, 2, 8, 5, 3, 2};
	aM.data = arr;
	Matrix bM(aM);
	std::cout<<bM.getrow()<<" "<<bM.getcol()<<" "<<bM(2,2)<<" "<<bM(5)<<std::endl;
	Matrix cM = aM + bM;
	std::cout<<cM.getrow()<<" "<<cM.getcol()<<" "<<cM(2,2)<<" "<<cM(5)<<std::endl;
	cM = aM - bM;
	std::cout<<cM.getrow()<<" "<<cM.getcol()<<" "<<cM(2,2)<<" "<<cM(5)<<std::endl;
	cM = aM * bM;
	std::cout<<cM.getrow()<<" "<<cM.getcol()<<" "<<cM(2,2)<<" "<<cM(5)<<std::endl;
	cM.displayMat();

	//Object.h usage
	std::cout<<"\nObject.h"<<std::endl;

	//Point.h usage
	std::cout<<"\nPoint.h"<<std::endl;

	//Vector.h usage
	std::cout<<"\nVector.h"<<std::endl;

	return 0;
}