#include<time.h>
#include<Windows.h>
#include<vector>
#include"../Headers/animal.h"
#include"../Headers/map.h"
#include"../Headers/vector.h"

double chance()
{
	return rand() * time(NULL) + GetTickCount();
}

//Priznak
Priznak::Priznak()
{
	num = 0;
	par = new double;
	reg = false;
	age = new double[4];
}
Priznak::Priznak(int num1,double* par1,bool reg1,double* age1)
{
	num = num1;
	par = par1;
	reg = reg1;
	age = age1;
}
void Priznak::deviant(double dev)
{
		*par = *par + dev;
}// not test
void Priznak::mutation(double mutat)
{
	if(mutat > 0)
		*par = *par * mutat;
	else
		*par = *par * -1/mutat;
}// not test

//Dig_Pri
Dig_Pri::Dig_Pri()
{
	Priznak();
}
void Dig_Pri::deviant(double dev)
{
		*par = *par + dev;
}// not test
void Dig_Pri::mutation(double mutat)
{
	if(mutat > 0)
		*par = *par * mutat;
	else
		*par = *par * -1/mutat;
}// not test

// Typ_Pri
Typ_Pri::Typ_Pri()
{
	Priznak();
}
void Typ_Pri::new_len(int con)
{
	double * cop = new double[len];
	for(int i =0;i<len;i++)
	{
		cop[i] = par[i];
	}
	delete(par);
	len++;
	par = new double [len];
	for(int i = 0;i<len-1;i++)
	{
		par[i] = cop[i];
	}
	delete(cop);
	par[len] = con;
}// not test
void Typ_Pri::deviant(double dev)
{
		dev = 0;
}// not test
void Typ_Pri::mutation(double mutat)
{
	int mu = (int)(mutat*10);
	if(mu %4 ==0)
		new_len(mu%max);
	else
		par[mu % len]  = mu % max;
}// not test

// Gene
Gene::Gene()
{
	pri = &Priznak();
	dom = false;
	dev = 0;
	mut = 0;
}
Gene::Gene(Priznak * pri1, bool dom1,double dev1,double mut1)
{
	pri = pri1;
	dom = dom1;
	dev = dev1;
	mut = mut1;
}
void Gene::deviant()
{
	pri->deviant(dev);
}// not test
void Gene::mutation()
{
	int t = (int)(chance);
	if(t%1000 < mut)
	{
		if(t%10000 < 5000)
			pri->mutation(-(t* 0.0003 + 1.5));
		else
			pri->mutation((t* 0.0003 + 1.5));
	}
}// not test

//Chromosome
Chromosome::Chromosome()
{
	gen = NULL;
	len = 0;
	mutation = 0;
}
Chromosome::Chromosome(Gene * gen1,int len1, double mutation1)
{
	gen = gen1;
	len = len1;
	mutation = mutation1;
}
void Chromosome::mutat()
{
	int t = (int)(chance);
	if(t%10000 < mutation)
	{
		int num = (int)(t* time(NULL))%len;
		Gene cop = gen[num];
		gen[num] = gen[num+1];
		gen[num+1] = cop;
	}
}// not test
void Chromosome::Addgen(Gene * gen1, int len1)
{
	if(len>0)
	{
		Gene * cop = new Gene[len];
		for(int i = 0;i<len;i++)
		{
			cop[i] = gen[i];
		}
		delete(gen);
		gen = new Gene[len + len1];
		for(int i = 0;i< len + len1;i++)
		{
			if(i<(len))
				gen[i] = cop[i];
			else
				gen[i] = gen1[i-len];
		}
		delete(cop);
	}
} // not test
Chromosome* Chromosome::crossing(Chromosome ch)
{
	Chromosome* chr1 = NULL;
	if(ch.len == len)
	{
		chr1 = new Chromosome[2];
		chr1[0].len = len;
		chr1[1].len = len;
		int t = (int)chance%len;
		int e = (int)chance%len;
		if(t<e)
		{
			int cop = t;
			t = e;
			e = cop;
		}
		if(t!=e)
		{
			chr1[0].Addgen(gen,e);
			chr1[0].Addgen(&ch.gen[e],t-e);
			chr1[0].Addgen(&gen[t],len-t);
			chr1[1].Addgen(ch.gen,e);
			chr1[1].Addgen(&gen[e],t-e);
			chr1[1].Addgen(&ch.gen[t],len-t);
		}
		if(t == e)
		{
			chr1[0].Addgen(gen,e);
			chr1[0].Addgen(&ch.gen[e],len-e);
			chr1[1].Addgen(ch.gen,e);
			chr1[1].Addgen(&gen[e],len-e);
		}
		if(t%2 ==0)
		{
			Chromosome cop = Chromosome();
			cop = chr1[0];
			chr1[0] = chr1[1];
			chr1[1] = cop;
		}
		chr1->mutation = (mutation + ch.mutation) * 0.5;
	}
	return chr1;
}// not test
bool Chromosome::operator!=(Chromosome& const right)
{
	if( len!= right.len)
		return true;
	for(int i =0;i<len;i++)
	{
		if(gen[i].pri->num != right.gen[i].pri->num)
			return true;
	}
	return false;
}

// Parametr
Parametr::Parametr()
{
	Priznak();
	norm_par = par;
	oldage = 0;
}
Parametr::Parametr(Priznak pr)
{
	Priznak(pr.num,pr.par,pr.reg,pr.age);
	norm_par = par;
	oldage = 0;
}
void Parametr::dam(double damage)
{
	par[0] = par[0] - damage;
}
void Parametr::regen(double dt)
{
	if(reg)
		par[0] = par[0] +  dt*0.1;
}
void Parametr::change_age(double ages, double max_ages)
{
	if((ages- oldage) >= max_ages * 0.05)
	{
		float P = (age[3] - age[2]) - (age[0] - age[1]);
		float Q = (age[0] - age[1]) - P;
		float R = age[2] - age[0];
		float S = age[1];

		par[0] = (double)(P*ages*ages*ages + Q*ages*ages + R*ages + S);
	}
}

//Dig_Par
Dig_Par::Dig_Par()
{
	Parametr();
}
//Typ_Par
void Typ_Par::dam(double damage)
{
}
void Typ_Par::regen(double dt)
{
	reg = false;
}
void Typ_Par::change_age(double ages, double max_ages)
{
	age[0] = 0;
}

//Animal
Animal::Animal()
	:max_num_p(8)// <- !!!!!Изменить!!!!
{
	chr = NULL;
	num_chr = 0;

	param = NULL;
	age = 0;
	position = Vector(0,0);
	finish = Vector(0,0);
	hunger = 0; 
	thirst = 0;
	targ = sav_life;
}
// ^- !!!!!Изменить!!!!
Animal::Animal(Chromosome* chr1, int num_chr1, Vector pos1)
	:max_num_p(8)
{
	delete(chr);
	chr = new Chromosome[num_chr1];
	num_chr = num_chr1;
	chr = chr1;

	position = pos1;
	finish = Vector(0,0);
	param = NULL;
	age = 0;
	hunger = 0; 
	thirst = 0;
	targ = sav_life;
}
Animal::Animal(Parametr* par1)
	:max_num_p(0)
{
}
Animal& Animal::operator= (Animal val)
{
	chr = val.chr;
	num_chr = val.num_chr;

	param = val.param;
	age = val.age;
	position = val.position;
	finish = val.finish;
	hunger = val.hunger; 
	thirst = val.thirst;
	targ = val.targ;
	return *this;
}
using namespace std; 
vector <Animal> Animal::search(int num_anim, Animal* anim, Map * mp) // возможна модификация с разбиением пространства на квадраты и передачей animal  из квадратов
{
	int rad = 10;
	vector <Animal> an;
	double maxX = position.GetX() + rad;
	double minX = position.GetX() - rad;
	double maxY = position.GetY() + rad;
	double minY = position.GetY() - rad;
	int num_vat = mp->GetNumVat();
	//Point max = Point();
	Vector min = Vector();
	double min_vat_len = 0;
	bool first = true;
	for(int i = 0;i<num_anim;i++) // проверяем животных и воду
	{
		if(i<num_vat)
		{
			if(first)
			{
				min = mp->GetVat(i).Getpos();
				min_vat_len = (min-position).length2();
				first = false;
			}
			Vector test = mp->GetVat(i).Getpos();
			if(test.GetX()<= maxX && test.GetX()>= minX &&
				test.GetY()<= maxY && test.GetY()>= minY && 
				((test-position).length2() < min_vat_len)) // если ближе, чем все проверенные водоёмы(клетки воды)
			{
				min = test;
				min_vat_len = (test-position).length2();
			}		
		}
		Vector test = anim[i].position;
		if(test.GetX()<= maxX && test.GetX()>= minX &&
		   test.GetY()<= maxY && test.GetY()>= minY)
				an.push_back(anim[i]); // запоминаем всех животных, оказавшихся в видимости
	}
	if(num_vat > num_anim) // если воды больше, проверяем недопроверенную воду
		for(int i = num_anim;i<num_vat;i++)
		{
			if(first) // на всякий случай, вдруг животных вообще нет?
			{
				min = mp->GetVat(i).Getpos();
				min_vat_len = (min-position).length2();
				first = false;
			}
			Vector test = mp->GetVat(i).Getpos();
			if(test.GetX()<= maxX && test.GetX()>= minX &&
				test.GetY()<= maxY && test.GetY()>= minY && 
				((test-position).length2() < min_vat_len)) // если ближе, чем все проверенные водоёмы(клетки воды)
			{
				min = test;
				min_vat_len = (test-position).length2();
			}
		}
	if(num_vat != 0 && min_vat_len <= rad)
		an.push_back(Animal(NULL)); // запоминаем близжайший водоём, если он в радиусе обнаружения
	int len = an.size();
	for(int i = 0;i<len;i++)
	{
		if((an[i].position.GetX()-position.GetX()) *  (an[i].position.GetX()-position.GetX()) + 
		   (an[i].position.GetY()-position.GetY()) * (an[i].position.GetY()-position.GetY()) > rad)
		{
		   an.erase(an.begin()+i,an.begin()+i); // если животное не входит в радиус обнаружения, забываем его
		   i--;
		}
	}
	return an;
}
bool Animal::ishome(Animal anim1)
{
	bool test = true;
	if(anim1.num_chr != num_chr)
		return false;
	for(int i = 0;i<num_chr;i++)
	{
		if(chr[i] != anim1.chr[i])
			return false;
	}
	return true;
}
void Animal::SetPar()
{
	param = new param[max_num_p]
	for(int i =0;i<num_chr;i++)
	{
		for(int e;e<chr[i].len;e++)
		{
			param[chr[i].gen[e].pri->num] = chr[i].gen[e].pri->par;
		}
	}
}
Animal* Animal::cross(int num,Animal* anim)
{
	if(GetNumChr() == anim->GetNumChr())
	{
		Animal* an = new Animal[num];
		Chromosome ** chr1 = NULL;
		chr1 = new Chromosome*[4];
		chr1[0] = new Chromosome[num_chr];
		chr1[1] = new Chromosome[num_chr];
		chr1[2] = new Chromosome[num_chr];
		chr1[3] = new Chromosome[num_chr];
		Chromosome * chr2 = new Chromosome[2];
		Vector pos = (position + anim->position) * 0.5;
		int number = num/4;
		int counter = num%4;
		if(num%4 == 0)
			number++;
		for(int i = 0;i < number;i++)
		{
			for(int e = 0;e<num_chr;e+=2)
			{
				chr2 = GetChr(e).crossing(GetChr(e+1));
				if(i+1 == number)
				{
					if(counter == 1)
					{
						chr1[0][e] = chr2[0];
					}
					if(counter == 2)
					{
						chr1[0][e] = chr2[0];
						chr1[1][e] = chr2[1];
					}
					if(counter == 3)
					{
						chr1[0][e] = chr2[0];
						chr1[1][e] = chr2[1];
						chr2 = anim->GetChr(e).crossing(anim->GetChr(e+1));
						chr1[2][e] = chr2[0];
					}
				}
				else
				{
					chr1[0][e] = chr2[0];
					chr1[1][e] = chr2[1];
					chr2 = anim->GetChr(e).crossing(anim->GetChr(e+1));
					chr1[2][e] = chr2[0];
					chr1[3][e] = chr2[1];
				}
			}
			if(i+1 == number)
			{
				if(counter == 1)
				{
					an[i*4] = Animal(chr1[0],num_chr,pos);
					an[i*4].SetPar();
				}
				if(counter == 2)
				{
					an[i*4] = Animal(chr1[0],num_chr,pos);
					an[i*4+1] = Animal(chr1[1],num_chr,pos);
				}
				if(counter == 3)
				{
					an[i*4] = Animal(chr1[0],num_chr,pos);
					an[i*4+1] = Animal(chr1[1],num_chr,pos);
					an[i*4+2] = Animal(chr1[2],num_chr,pos);
				}
			}
			else
			{
				an[i*4] = Animal(chr1[0],num_chr,pos);
				an[i*4+1] = Animal(chr1[1],num_chr,pos);
				an[i*4+2] = Animal(chr1[2],num_chr,pos);
				an[i*4+3] = Animal(chr1[3],num_chr,pos);
			}

		}
		return an;
	}
	else
		return NULL;
}
void Animal::new_maj(vector <Animal> anim)
{
	int len = anim.size();
	double size = param[0].num;

	Vector min = Vector();
	double min_len = 0;
	bool first = true;

	Vector min_v = Vector();
	double min_lenv = 0;
	bool firstv = true;

	if(param[1].par[0] != 0) // травоядно
	{
		for(int i = 0;i<len;i++)
		{
		//	Animal an = anim[i];
		//	if(an.max_num_p == 0 && thirst > 15 && targ != sav_life) // если вода, хочет пить и не спасается
		//	{							// ^-изменить на значение thirs на значение параметра
		//		if(firstv)
		//		{
		//			min_v = an.position;
		//			min_lenv = (position - min_v).length2();
		//			firstv = false;
		//		}
		//		if((an.position - position).length2() < min_lenv) // поиск близжайшего источника воды
		//		{
		//			min_v = an.position;
		//			min_lenv = (an.position - position).length2();
		//			targ = eat;
		//		}
		//	} // возможна оптимизация через разделение if, надо проверить
		//	if(an.param[33].par[0] == param[33].par[0]) // один вид
		//	{
		//		if(targ != eat && targ != sav_life && an.targ == reprod && (an.param[19].par != param[19].par 
		//			|| (param[19].par == 0 && an.param[19].par == 0)))
		//		{// если в поиске и другого пола или гермофродит 
		//			if(first)// так как должно быть не задействованно 
		//			{
		//				min = an.position;
		//				min_len = (an.position - position).length2();
		//				first = false;
		//			}
		//			if((an.position - position).length2() < min_len)
		//			{
		//				min = an.position; // поиск минимального расстояния
		//				min_len = (an.position - position).length2();
		//				targ = reprod;
		//			}
		//		}
		//	}
		//	else // другой вид
		//	{
		//		double other = *an.param[0].par;
		//		if(size * 20 <= other || other * 20 <= size)
		//		{
		//			anim.erase(anim.begin()+i,anim.begin()+i);
		//			len--;
		//			break;
		//		}
		//		else
		//		{
		//			if(ishome(an))
		//			if(an.param[1].par[1] != 0 ) // обнаруженное животное плотоядно, убежать
		//			{
		//				double koef = 0;
		//				if(size >= other)
		//					koef = -(size/other) + 31;// расстояние пропорционально размеру
		//				else
		//					koef = -(other/size) + 31;
		//				Vector way = an.position- position;
		//				if(way.length2() < koef * koef )
		//				{
		//					if(targ != sav_life)
		//					{
		//						finish = Vector();
		//					}
		//					finish = finish + Vector_norm(way) * (way.length()/ koef);
		//					targ = sav_life;
		//				}
		//			}
		//			else // обнаруженное животное травоядно, отойти
		//			{
		//				double koef = 0;
		//				if(size >= other)
		//					koef = -(size/other) * 0.2 + 5;// расстояние пропорционально размеру
		//				else
		//					koef = -(other/size) * 0.2 + 5;
		//				Vector way = an.position- position;
		//				if(way.length2() < koef * koef )
		//				{
		//					if(targ != sav_life)
		//					{
		//						finish = Vector();
		//					}
		//					finish = finish + Vector_norm(way) * (way.length()/ koef); // только если записана опасность
		//					targ = sav_life;
		//				}
		//			}
		//			if(an.param[5].par[0] == 0 && an.param[5].par[1] == 0 && 
		//				an.param[5].par[2] == 0 && an.param[5].par[3] == 0 && hunger >15 && targ != sav_life)
		//			{// если животное - растение(не может двигаться)
		//				if(first)
		//				{
		//					min = an.position;
		//					min_len = (an.position - position).length2();
		//					first = false;
		//				}
		//				if((an.position - position).length2() < min_len)
		//				{
		//					min = an.position; // поиск минимального расстояния
		//					min_len = (an.position - position).length2();
		//					targ = eat;
		//				}
		//			}
		//			if(!first ||!firstv)
		//			{
		//				if(targ == eat)
		//				{
		//					if(hunger > thirst)
		//						finish = min;
		//					else
		//						finish = min_v;
		//				}
		//				if(targ == reprod)
		//					finish = min;
		//			}
		//		}
		//	}
		}
	}
}