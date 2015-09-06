#include<time.h>
#include<Windows.h>
#include<vector>
#include"../Headers/map.h"
#include"../Headers/vector.h"


#ifndef __ANIMAL_H
#define __ANIMAL_H 

class Priznak // храниище данных о параметре
{
public:
	int num;// значение 
	double* par;//указатель на параметр
	bool reg;  // возможность регенерации
	double* age; //возрастная характерисика
	Priznak();
	Priznak(int, double *,bool,double*);
	virtual void deviant(double dev); 
	virtual void mutation(double mutate);
};

class Dig_Pri : public Priznak
{
public:
	Dig_Pri();
	void deviant(double dev); 
	void mutation(double mutate);
};

class Typ_Pri : public Priznak
{
private:
	int max;
	void new_len(int con);
public:
	int len;
	Typ_Pri();
	void deviant(double dev); 
	void mutation(double mutate);
};

class Gene
{
private:
	double dev; // коэфициент отклонения 
	double mut; // вероятность мутации;  на dev* 4
public:
	Priznak * pri; // знaчение, которое кодирует ген
	bool dom;// доминантность

	Gene();
	Gene(Priznak*,bool, double, double);
	void deviant();
	void mutation();
};

class Chromosome
{
public:
	Gene * gen;//гены хромосомы
	int len;// количество генов
	double mutation; //вероятносьт мутации длинны хромосомы и/или порядка генов
	Chromosome();
	Chromosome(Gene* gen1, int len1,double mutation1);
	void mutat();
	void Addgen(Gene * gen1, int len1);
	Chromosome* crossing(Chromosome ch);
	bool operator!=(Chromosome& const right);
};

class Parametr : public Priznak
{
private:
	double* norm_par;
	double oldage;
public:
	Parametr();
	Parametr(Priznak);
	virtual void dam(double damage);
	virtual void regen(double dt);
	virtual void change_age(double ages, double max_ages);
	double* live(double damage,double dt,double ages, double max_ages)
	{
		dam(damage);
		regen(dt);
		change_age(ages,max_ages);
		return par;
	}
};

class Dig_Par : public Parametr
{
public:
	Dig_Par();
};

class Typ_Par : public Parametr
{
public:
	int len;
	Typ_Par();
	void dam(double damage);
	void regen(double dt);
	void change_age(double ages, double max_ages);
};

enum target
{
	sav_life = 1,
	eat,
	reprod // размножение
};
using namespace std;
class Animal
{
private:
	Chromosome* chr;
	int num_chr; // для двойного набора
public:
	Parametr* param;
	const int max_num_p; // const
	double age;
	Vector position;
	Vector finish; // в дальнейшем заменить на маршрут
	double hunger; // голод
	double thirst; // жажда
	target targ;
	
	Animal();
	Animal(Chromosome* chr1, int num_chr, Vector pos1);
	Animal(Parametr* par1);
	int GetNumChr(){return num_chr;}
	Chromosome GetChr(int n) {if(n<= num_chr)return chr[n]; else return Chromosome();}

	Animal& operator= (Animal val);
	vector <Animal> search(int num_anim, Animal* anim, Map * mp); // кажется норматьно, not test
	bool ishome(Animal); // определить
	void SetPar();
	Animal* cross(int num,Animal * anim);

	void new_maj(vector <Animal>); // додел
	void move(Vector tar, double dt); // определить
	void relax(); // определить
	void atak(Animal); // определить
	void drink(double dt); // определить
	void eating(double dt); // определить
	void live();
};
#endif;

