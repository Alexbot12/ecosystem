
#ifndef __VECTOR_H
#define __VECTOR_H

class Vector
{
private:
	double X;
	double Y;
public:
	Vector();
	Vector(double,double);
	void SetX(const double x1)
	{X= x1;}
	void SetY(const double y1)
	{Y = y1;}
	double GetX()
	{return X;}
	double GetY()
	{return Y;}
};
#endif;