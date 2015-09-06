#include<cmath>
#include"../Headers/vector.h"
Vector::Vector()
{
	x=0;
	y=0;
}
Vector::Vector(double x1,double y1)
{
	x = x1;
	y = y1;
}
	double Vector::length()
	{
		return sqrt( x*x + y*y);
	}
	double Vector::length2()
	{
		return x*x + y*y;
	}

	Vector Vector::operator+(Vector& const right)
	{
		return Vector(x+right.GetX(), y+right.GetY());
	}
	Vector Vector::operator-(Vector& const right)
	{
		return Vector(x - right.GetX(), y - right.GetY());
	}
	Vector Vector::operator-()
	{
		return Vector(-x, -y); 
	}
	Vector Vector::operator*(double scale)
	{
		return Vector(x * scale, y * scale);
	}
	Vector Vector::operator/(double u)
	{
		return Vector(x,y)*(1/u);
	}
	Vector Vector::operator/(Vector& const right)
	{
		return Vector(this->GetX()/right.GetX(),
					this->GetY()/right.GetY());
	}
	
	double Vector::operator&(Vector& const right)
	{
		//scalar multiply
		return x * right.GetX() + y * right.GetY(); 
	}
	double Vector::operator^(Vector& const right)
	{
		return( (x * right.GetX() + y * right.GetY()) / (sqrt( (x * x + y * y) * right.length())) );
	}
	Vector sqrt_ve(Vector& const value)
	{
		return Vector(	
			sqrt(value.GetX()), 
			sqrt(value.GetY()));
	}
	Vector Vector::operator>(Vector& const right)
	{
		return Vector(
			x * right.x,
			y * right.y);
	}
	Vector& Vector::operator= (Vector val)
	{
		x = val.GetX();
		y = val.GetY();
		return *this;
	}

	bool Vector::operator<(double value)
	{	
		return value <= 0 || this->length2() < value*value;
	}
	bool Vector::operator==(Vector& const right)
	{
		return x == right.GetX() && y == right.GetY();
	}
	bool Vector::operator!=(Vector& const right)
	{
		return x != right.GetX() || y != right.GetY();	
	}
	Vector Vector_norm(Vector value)
	{
		if(value != Vector(0,0))
		{
		double longg  = sqrt(value.GetX()* value.GetX() + value.GetY() * value.GetY()); 
		return Vector(
			value.GetX() / longg,
			value.GetY() / longg);
		}
		return value;
	}