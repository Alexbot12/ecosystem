#include<iostream>
#include<fstream>
#include<vector>
#include"../glut/glut.h"
#include"../Headers/vector.h"

using namespace std;
#ifndef __MAP_H
#define __MAP_H

enum type	// ��� �����������
{
	ground = 1,
	sand,
	rock,
	vater
};

class Point
{
private:
	double volume; // ����� ����� 
	type ty;
	float height; // ������/������� ���� �����/����
	Vector pos; // ���������� �������
public:
	Point();
	Point(double,type,float,Vector);
	double Getvol();
	type Gettype();
	int Getheig();
	Vector Getpos();
	GLfloat* heightcolor(GLfloat* color);
	void Drowpoint();
	void writePoint(FILE*);
	void writePoint_wthisout_vol(FILE*);
	void writePoint_vol(FILE*);
};

class Map
{
private:
	vector <Point> po; // ��� ������� �����
	int num_point; // ���������� ��������
	vector <Point> vat;
public:
	Map();
	void readMap(const char* fail); // ���������� �� �����
	void drawMap(Vector centre); // ��������� �����
	void writeMap(vector <Point>,const char*);
	void genMap(int N, double vol, float p, const char* fail);
	int GetNumVat() {return vat.size();}
	Point GetVat(int n) {return vat.at(n);}
};
#endif;