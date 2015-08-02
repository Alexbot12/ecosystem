#include<iostream>
#include<vector>
#include<Windows.h>
#include<time.h>
#include"../glut/glut.h"
#include"../Headers/map.h"
#include"../Headers/vector.h"
#include"../Headers/colors.h"
#include"../Headers/fancs.h"

//Point
Point::Point()
{
	volume = 1;
	ty = ground;
	height = 0;
	pos = Vector();
}
Point::Point(double vo1,type ty1, float he1,Vector pos1)
{
	volume = vo1;
	ty = ty1;
	height = he1;
	pos = pos1;
}
double Point::Getvol()
{
	return volume;
}
type Point::Gettype()
{
	return ty;
}
int Point::Getheig()
{
	return height;
}
Vector Point::Getpos()
{
	return pos;
}
GLfloat* Point::heightcolor(GLfloat* color)
{
	double color0 = color[0] * height * 0.2;
	double color1 = color[1] * height * 0.2;
	double color2 = color[2] * height * 0.2;
	GLfloat col[] = {color0,color1,color2};
	return col;
}
void Point::Drowpoint()
{
	if(ty == ground)
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,brown);
	if(ty == sand)
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,yellow);
	if(ty == rock)
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,grey);
	if(ty == vater)
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,blue);
	/*GLfloat noise[] = {height,height,height};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,noise);*/ // Это для теста в градиенте
	glPushMatrix();
	glScaled(0.3,0.3,1);
	glBegin(GL_QUADS);
		glVertex2d(pos.GetX(),pos.GetY());
		glVertex2d(pos.GetX(),pos.GetY()+1);
		glVertex2d(pos.GetX()+1,pos.GetY()+1);
		glVertex2d(pos.GetX()+1,pos.GetY());
	glEnd();

	glLineWidth(2);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,black);

	glBegin(GL_LINE_LOOP);
		glVertex2d(pos.GetX(),pos.GetY());
		glVertex2d(pos.GetX(),pos.GetY()+1);
		glVertex2d(pos.GetX()+1,pos.GetY()+1);
		glVertex2d(pos.GetX()+1,pos.GetY());
	glEnd();
	glPopMatrix();
}
void Point::writePoint(FILE * F)
{
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		string vol = "(";
		vol += to_string(volume);
		vol+= ")";
		string t = "{";
		t += to_string((int)ty);
		string he = ",";
		he += to_string(height);
		string poX = ",";
		poX+= to_string(pos.GetX());
		string poY = ",";
		poY += to_string(pos.GetY());
		poY += "}";
		fputs(vol.c_str(),F);
		fputs(t.c_str(),F);
		fputs(he.c_str(),F);
		fputs(poX.c_str(),F);
		fputs(poY.c_str(),F);
	}
}
void Point::writePoint_wthisout_vol(FILE* F)
{
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		string t = "{";
		t += to_string((int)ty);
		string he = ",";
		he += to_string(height);
		string poX = ",";
		poX+= to_string(pos.GetX());
		string poY = ",";
		poY += to_string(pos.GetY());
		poY += "}";
		fputs(t.c_str(),F);
		fputs(he.c_str(),F);
		fputs(poX.c_str(),F);
		fputs(poY.c_str(),F);
	}
}
void Point::writePoint_vol(FILE* F)
{
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		string vol = "(";
		vol += to_string(volume);
		vol+= ")";
		fputs(vol.c_str(),F);
	}
}
//Map
Map::Map()
{
	num_point = 0;
}
void Map::readMap(const char* fail)
{
	FILE * F;
	F = fopen(fail,"r"); 
	char s;
	string st;
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		double volr = 1;
		type tr = ground;
		int hr = 0;
		Vector posr = Vector();
		while(!feof(F))
		{
			s = fgetc(F);
			if(s =='(')
				volr = readFdigit(F);

			if(s =='{')
			{
				tr = (type)readFdigit(F);
				hr = readFdigit(F);
				posr.SetX(readFdigit(F));
				posr.SetY(readFdigit(F));
				po.push_back(Point(volr,tr,hr,posr));
				num_point +=1;
			}
		}
		fclose(F);
	}
}
void Map::drawMap(Vector centre) // координата точки, которая выводится в левый нижний угол.
{
	glPushMatrix();
	glTranslated(centre.GetX(),centre.GetY(),0);
	for(int i =0;i<num_point;i++)
	{
		po[i].Drowpoint();
	}
	glPopMatrix();
}
void Map::writeMap(vector <Point> po,const char* fail)
{
	int len = po.size();
	FILE * F;
	F = fopen(fail,"w"); 
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		po[0].writePoint_vol(F);
		for(int i=0;i<len;i++)
		{
			po[i].writePoint_wthisout_vol(F);
		}
		fclose(F);
	}
}
void Map::genMap(int N, double vol, float p, const char* fail)// ошибка в передаче ссылки
{
	po.clear();
	num_point = 0;
	float x = rand() * time(NULL)/GetTickCount();
	float y = rand() * time(NULL)/GetTickCount();
	//float p = (rand() * time_t()/GetTickCount())%2-1;
	float h = 0;
	Point poin = Point();
	FILE * F;
	F= fopen(fail,"w");
	if(F==NULL) 
	{
		cout <<"ERROR file map";
	}
	else
	{
		poin = Point(vol,ground,0,Vector(0,0));
		poin.writePoint_vol(F);
		fputc(10,F);
		for(int i = 0;i<N;i++)
		{
			for(int e = 0;e<N;e++)
			{
				h = (PerlinNoise(x+i,y+e,p,3)+ 0.2)*20;
				if(h<0)
					poin = Point(vol,vater,h,Vector(i,e));
				if(h>=0 && h<4)
					poin = Point(vol,sand,h,Vector(i,e));
				if(h>=4 && h<15)
					poin = Point(vol,ground,h,Vector(i,e));
				if(h>=15)
					poin = Point(vol,rock,h,Vector(i,e));
				poin.writePoint_wthisout_vol(F);
				po.push_back(poin);
				num_point++;
			}
			fputc(10,F);
		}
		fclose(F);
	}
}