
#ifndef __VECTOR_H
#define __VECTOR_H

class Vector
{
private:
	double x;
	double y;
public:
	Vector();
	Vector(double,double);
	void SetX(const double x1){x= x1;}
	void SetY(const double y1){y = y1;}
	double GetX(){return x;}
	double GetY(){return y;}

	double length();
	double length2();

	Vector operator+(Vector& const right);
	Vector operator-(Vector& const right);
	Vector operator-();
	Vector operator*(double scale);
	Vector operator/(double u);
	Vector operator/(Vector& const right);
	
	double operator&(Vector& const right);
	double operator^(Vector& const right);
	double operator%(Vector& const right);
	Vector operator*(Vector& const right);
	Vector operator>(Vector& const right);
	Vector& operator= (Vector val);

	bool operator<(double value);
	bool operator==(Vector& const right);
	bool operator!=(Vector& const right);
};
Vector Vector_norm(Vector value);
#endif;