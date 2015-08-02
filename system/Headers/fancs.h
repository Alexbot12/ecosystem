#include<iostream>
#include<vector>
#include<Windows.h>

using namespace std;
#ifndef __FANCS_H
#define __FANCS_H

//Perlin Noise
float Noise(int x, int y)
{
	int n = x + y * 57;
	int f =0;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0);  
}
float Smoothed(float x, float y)
{
	double corners = ( Noise(x-1,y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
    double sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8;
    double center  =  Noise(x, y) / 4;
    return corners + sides + center;
}
float Interpolated(float v0, float v1, float v2, float v3, float f)
{
	float P = (v3 - v2) - (v0 - v1);
    float Q = (v0 - v1) - P;
    float R = v2 - v0;
    float S = v1;

    return P*f*f*f + Q*f*f + R*f + S;
}
float InterpolatedNoise(float x, float y)
{
	float integer_X    = (int)x;
    float fractional_X = x - integer_X;
    float integer_Y    = (int)y;
    float fractional_Y = y - integer_Y;
	float v0 = Smoothed(integer_X - 1, integer_Y - 1);
	float v1 = Smoothed(integer_X - 1, integer_Y);
	float v2 = Smoothed(integer_X ,    integer_Y - 1);
    float v3 = Smoothed(integer_X,     integer_Y);
    float v4 = Smoothed(integer_X + 1, integer_Y);
    float v5 = Smoothed(integer_X,     integer_Y + 1);
    float v6 = Smoothed(integer_X + 1, integer_Y + 1);
	float i1 = Interpolated(v0, v1 , v2 , v3, fractional_X);
	float i2 = Interpolated(v1, v2 , v3 , v4, fractional_X);
	float i3 = Interpolated(v2, v3 , v4 , v5, fractional_X);
	float i4 = Interpolated(v3, v4 , v5 , v6, fractional_X);

    return Interpolated(i1 , i2 , i3, i4, fractional_Y);
}
float PerlinNoise(float x, float y, float p, int oct)// ������� ��������� �����, ���-�� �����, ���������, � �����
{
	float noise = 0;
	int n = oct - 1;
	for(int t = 1;t<=n;t++)
	{
		float frequency = 2* t;
        float amplitude = p * t;
		noise = noise + InterpolatedNoise(x / frequency, y / frequency) * amplitude;
	}
	return noise;
}
//Some fancs
int readdigit(string str)
{
	int dig;
	int len = str.length();
	bool neg = false;
	for(int i = 0;i<len;i++)
	{
		if(str[0]=='-')
		{
			neg = true;
			str.erase(str.begin());
			len--;
		}
		if(i ==0)
			dig =((int)str[i] - 48);
		else
			dig = dig*10 + ((int)str[i] - 48);
	}
	if(neg)
		dig = -dig;
	return dig;
}
string readFUntilDigit(FILE * fail)
{
	string st;
	char s = '1';
	while(!feof(fail) && (isdigit(s) || s=='-'))
	{
		s = fgetc(fail);
		st +=s;
	}
	st.erase(end(st)-1);
	return st;
}
int readFdigit(FILE * file)
{
	string st = readFUntilDigit(file);
	return readdigit(st);
}
string to_string(int in)
{
	string st; 
	bool neg = false;
	if(in == 0)
		st.push_back('0');
	else
	{
		if(in<0)
		{
			neg = true;
			in = -in;
		}
		while(in!=0)
		{
			st.push_back((char)(in%10 + 48));
			in = in/10;
		}
	}
	reverse(st.begin(), st.end());
	if(neg)
		st.insert(st.begin(),'-');
	return st;
}
#endif;