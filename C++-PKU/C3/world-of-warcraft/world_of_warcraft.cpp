/***********************************************
ħ�������ռ���
���ʱ�䣺2017/12/31
������
***********************************************/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//#pragma warning(disable:4996)   // �ļ��ض���visual studio Ҫ�õ�

/***********************************************
ȫ�ֱ�����
��ħ��˾�������ʿ��˳��{ 2,3,4,1,0 }
��ħ��˾�������ʿ��˳��{ 3,0,1,2,4 }
TOTALTIME����ʱ��
arrow_atk�������Ĺ�����
loyalty_loss���ҳ϶ȵ���ʧ
initialLifeValue��˾��ĳ�ʼ����Ԫ
numOfCity����������
GameOver����Ϸ�Ƿ����
***********************************************/
int redOrder[5] = { 2,3,4,1,0 };
int blueOrder[5] = { 3,0,1,2,4 };
int TOTALTIME = 0;
int arrow_atk;
int loyalty_loss;
int initialLifeValue, numOfCity;
bool GameOver = false;

/***********************************************
ʱ����
***********************************************/
class Time
{
public:
	int hour;
	int minute;
	Time(int h, int m) :hour(h), minute(m) {}
	void init(int h, int m)
	{
		hour = h;
		minute = m;
	}
	void updateTime()
	{
		minute++;
		if (minute == 60)
		{
			hour++;
			minute = 0;
		}
	}
	friend ostream& operator<<(ostream &o, const Time &t);
};

// ��Ϸʱ��
Time gameTime(0, 0);

class Warrior;

/***********************************************
������
void printMove()������ƶ���Ϣ
void Fight()����Ҫ�Ǵ���40��ʱ�������¼�
***********************************************/
class City
{
protected:
	int id;
	string flag;  // "None", "red", "blue"
	int LifeValue;
	City *next;
	City *prior;
	friend Warrior;
public:
	Warrior *redWarrior;
	Warrior *blueWarrior;
	string lastWinner;
	City() {}
	void init(int i, City *p, City *n)
	{
		id = i;
		flag = "None";
		LifeValue = 0;
		redWarrior = NULL;
		blueWarrior = NULL;
		lastWinner = "None";
		next = n;
		prior = p;
	}
	void produceLifeValue() { LifeValue += 10; }
	void printMove();
	void Fight();
	void set_flag(string flag)
	{
		this->flag = flag;
		cout << gameTime << " " << flag << " flag raised in city " << id << endl;
	}
	int get_id() { return id; }
	string get_flag() { return flag; }
	Warrior* get_red() { return redWarrior; }
	Warrior* get_blue() { return blueWarrior; }
	virtual int get_numOfInvader() { return 0; }  // ��Ҫ�Ǹ�˾�ʹ��
};

/***********************************************
˾���
Warrior *invader�������������˽���˾�������Ϸ��������˶�һ������invader������Ƚ���˾��ĵ���
void makeWarrior()��������ʿ
void award()������ʤ������ʿ����Ԫ
void reportElements()�����浱ǰ����Ԫ
***********************************************/
class Headquarter :public City
{
private:
	string alliance;   // "red", "blue"
	int numOfWarrior;
	int ProduceOrder[5];
	friend Warrior;
	Warrior *warrior[1000] = { NULL };
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	Warrior *invader;
	int numOfInvader;
	Headquarter(string a) :alliance(a) {}
	void init(int lv, int po[])
	{
		invader = NULL;
		numOfWarrior = 0;
		numOfInvader = 0;
		LifeValue = lv;
		for (int i = 0; i < 5; i++)
		{
			ProduceOrder[i] = po[i];
		}
	}
	~Headquarter()
	{
		for (int i = 0; i < numOfWarrior; i++)
		{
			if (warrior[i])
			{
				delete warrior[i];
			}
		}
	}
	void makeWarrior();
	void award(Warrior *w);
	void reportElements()
	{
		cout << gameTime << " " << LifeValue << " elements in " << alliance << " headquarter" << endl;
	}
	// ��ȡ��Ա�����ĺ���
	string get_alliance() { return alliance; }
	int get_LifeValue() { return LifeValue; }
	int get_numOfWarrior() { return numOfWarrior; }
};

Headquarter red("red"), blue("blue");

/***********************************************
��ʿ��
***********************************************/
class Warrior
{
protected:
	Headquarter *hq;
	City *pCity;
	int id;
	int strength;
	int attack;
	int weapon[3] = { 0 };
	const string weaponName[3] = { "sword","bomb","arrow" };
	string classes;   // ��ʿ���ࣺ"dragon","ninja","iceman","lion","wolf"
	int classesID;    // ��ʿ�����ţ�0�� 1�� 2�� 3�� 4�� 5
	friend Headquarter;
	friend ostream& operator<<(ostream &o, const Warrior *w);
public:
	bool win;
	static string warriorClasses[5];  // ������ʿ����
	static int initialStrength[5];    // ��ʼ����
	static int initialAttack[5];      // ��ʼ������
	Warrior() {}
	Warrior(Headquarter *hq, int id, int s, int atk, int cid) :hq(hq), id(id), strength(s), attack(atk), classesID(cid), win(false)
	{
		classes = warriorClasses[classesID];
	}
	virtual void printBornMessage()
	{
		cout << gameTime << " " << this << " born" << endl;
	}
	virtual void Attack(Warrior *enemy);
	virtual void FightBack(Warrior *enemy);
	virtual void putArrow(Warrior *enemy);
	virtual void bomb(Warrior *enemy);
	virtual void Hurt(Warrior *enemy, int atk);
	virtual void earn_elements();
	virtual void ReportWeapon();
	virtual void move();
	virtual void escape() {}
	virtual void yell() {}
	virtual void disarm(Warrior *enemy) {}
	void setWeapon(int kind)
	{
		if (kind == 0)
		{
			weapon[0] = attack * 0.2;
		}
		else if (kind == 1)
		{
			weapon[1] = 1;
		}
		else
		{
			weapon[2] = 3;
		}
	}
	void set_strength(int s) { strength = s; }
	int get_strength() { return strength; }
	int get_weapon(int i) { return weapon[i]; }
	int get_attack() { return attack; }
};

string Warrior::warriorClasses[5] = { "dragon","ninja","iceman","lion","wolf" };
int Warrior::initialStrength[5] = { 0 };
int Warrior::initialAttack[5] = { 0 };

void Warrior::Attack(Warrior *enemy)
{
	if (enemy != NULL)
	{
		cout << gameTime << " " << this << " attacked " << enemy
			<< " in city " << pCity->get_id() << " with " << strength << " elements and force " << attack << endl;
		enemy->Hurt(this, attack + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
		enemy->FightBack(this);
	}
}

void Warrior::FightBack(Warrior *enemy)
{
	// ninja������
	if (strength != 0 && classes != "ninja")
	{
		cout << gameTime << " " << this << " fought back against " << enemy << " in city " << pCity->get_id() << endl;
		enemy->Hurt(this, attack / 2 + weapon[0]);
		weapon[0] = weapon[0] * 0.8;
	}
}

void Warrior::putArrow(Warrior *enemy)
{
	if (weapon[2] > 0 && enemy != NULL)
	{
		// ������˾������ʿ
		if (enemy->pCity->id == 0 || enemy->pCity->id == numOfCity + 1)
		{
			return;
		}
		enemy->Hurt(NULL, arrow_atk);  // ������޷����������Դ���NULLָ��
		weapon[2]--;
		if (enemy->strength == 0)
		{
			cout << gameTime << " " << this << " shot and killed " << enemy << endl;
		}
		else
		{
			cout << gameTime << " " << this << " shot" << endl;
		}
	}
}

void Warrior::bomb(Warrior *enemy)
{
	if (enemy && weapon[1])
	{
		if (strength == 0 || enemy->strength == 0)
		{
			return;
		}
		bool redFirst = pCity->get_flag() == "red" || (pCity->get_flag() == "None" && pCity->id % 2 == 1);
		if (redFirst && hq->alliance == "red" || !redFirst && hq->alliance == "blue")
		{
			// �ҷ��ȳ���������ɱ
			if (enemy->classes != "ninja" && attack + weapon[0] < enemy->strength && strength <= enemy->attack / 2 + enemy->weapon[0])
			{
				// ����ը��
				strength = 0;
				enemy->strength = 0;
				pCity->redWarrior = NULL;
				pCity->blueWarrior = NULL;
				cout << gameTime << " " << this << " used a bomb and killed " << enemy << endl;
			}
		}
		else if (strength <= enemy->attack + enemy->weapon[0])
		{
			// �з��ȳ������ᱻɱ��
			strength = 0;
			enemy->strength = 0;
			pCity->redWarrior = NULL;
			pCity->blueWarrior = NULL;
			cout << gameTime << " " << this << " used a bomb and killed " << enemy << endl;
		}
	}
}

void Warrior::Hurt(Warrior *enemy, int atk)
{
	strength -= atk;
	if (strength <= 0)
	{
		strength = 0;
		if (enemy != NULL)
		{
			// enemy != NULL ˵���Ƿ�����ս�������Ǳ�����
			enemy->win = true;
			cout << gameTime << " " << this << " was killed in city " << pCity->get_id() << endl;
		}
	}
}

void Warrior::move()
{
	// ����ʿ�������ƶ�
	if (hq->alliance == "red")
	{
		if (pCity->id == numOfCity + 1)
		{
			pCity->redWarrior = NULL;
			blue.invader = this;
			return;
		}
		else if (pCity->id == numOfCity)
		{
			blue.numOfInvader++;
		}
		pCity->redWarrior = NULL;
		pCity = pCity->next;
		pCity->redWarrior = this;
	}
	else
	{
		// ����ʿ�Զ������ƶ�
		if (pCity->id == 0)
		{
			pCity->blueWarrior = NULL;
			red.invader = this;
			return;
		}
		else if (pCity->id == 1)
		{
			red.numOfInvader++;
		}
		pCity->blueWarrior = NULL;
		pCity = pCity->prior;
		pCity->blueWarrior = this;
	}

}

//��ȡ��������Ԫ���ܲ�
void Warrior::earn_elements()
{
	cout << gameTime << " " << this << " earned " << pCity->LifeValue << " elements for his headquarter" << endl;
	hq->LifeValue += pCity->LifeValue;
	pCity->LifeValue = 0;
}

// ��������
void Warrior::ReportWeapon()
{
	int num_weapon = (weapon[0] != 0) + (weapon[1] != 0) + (weapon[2] != 0);
	if (num_weapon == 0)
	{
		cout << gameTime << " " << this << " has no weapon" << endl;
	}
	else
	{
		cout << gameTime << " " << this << " has ";
		if (weapon[2])
		{
			cout << "arrow(" << weapon[2] << ")";
			num_weapon--;
			if (num_weapon)
			{
				cout << ",";
			}
		}
		if (weapon[1])
		{
			cout << "bomb";
			num_weapon--;
			if (num_weapon)
			{
				cout << ",";
			}
		}
		if (weapon[0])
		{
			cout << "sword(" << weapon[0] << ")";
		}
		cout << endl;
	}
}

/***********************************************
��ʿ�����ࣺDragon��
***********************************************/
class Dragon : public Warrior
{
private:
	double morale; // ʿ��
public:
	Dragon(Headquarter *hq, int id, int strength, int atk, double m, int cid = 0) :Warrior(hq, id, strength, atk, cid), morale(m)
	{
		classes = "dragon";
		setWeapon(id % 3);
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
	}
	void yell()
	{
		// �ж��Ƿ���������
		bool active_attack = (hq->get_alliance() == "red" && (pCity->get_flag() == "red" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 1)))
			|| (hq->get_alliance() == "blue" && (pCity->get_flag() == "blue" || (pCity->get_flag() == "None" && pCity->get_id() % 2 == 0)));
		if (morale > 0.8 && strength > 0 && active_attack)
		{
			cout << gameTime << " " << this << " yelled in city " << pCity->get_id() << endl;
		}
	}
	virtual void Attack(Warrior *enemy)
	{
		Warrior::Attack(enemy);
		enemy->get_strength() == 0 ? morale += 0.2 : morale -= 0.2;
		yell();
	}
};

/***********************************************
��ʿ�����ࣺNinja��
***********************************************/
class Ninja : public Warrior
{
public:
	Ninja(Headquarter *hq, int id, int strength, int atk, int cid = 1) : Warrior(hq, id, strength, atk, cid)
	{
		setWeapon(id % 3);
		setWeapon((id + 1) % 3);
	}
};

/***********************************************
��ʿ�����ࣺIceman��
***********************************************/
class Iceman : public Warrior
{
private:
	int moveStep;  // �ƶ�����
public:
	Iceman(Headquarter *hq, int id, int strength, int atk, int cid = 2) : Warrior(hq, id, strength, atk, cid)
	{
		setWeapon(id % 3);
		moveStep = 0;
	}
	virtual void move()
	{
		Warrior::move();
		moveStep++;
		if (moveStep % 2 == 0)
		{
			strength = strength - 9 > 0 ? strength - 9 : 1;
			attack += 20;
		}
	}
};

/***********************************************
��ʿ�������ࣺLion��
���ԣ����ҳ϶ȣ�������
***********************************************/
class Lion : public Warrior
{
private:
	int loyalty;
public:
	Lion(Headquarter *hq, int id, int strength, int atk, int cid = 3) : Warrior(hq, id, strength, atk, cid)
	{
		loyalty = hq->get_LifeValue();
	}
	void printBornMessage()
	{
		Warrior::printBornMessage();
		cout << "Its loyalty is " << loyalty << endl;
	}
	void escape()
	{
		if (loyalty <= 0)
		{
			hq->get_alliance() == "red" ? pCity->redWarrior = NULL : pCity->blueWarrior = NULL;
			cout << gameTime << " " << this << " ran away" << endl;
		}
	}
	virtual void Attack(Warrior *enemy);
	virtual void FightBack(Warrior *enemy);
	virtual void Hurt(Warrior *enemy, int atk);
	void loseLoyalty()
	{
		loyalty -= loyalty_loss;
		if (loyalty < 0) { loyalty = 0; }
	}
};

void Lion::Attack(Warrior *enemy)
{
	Warrior::Attack(enemy);
	if (enemy->get_strength() != 0)
	{
		loseLoyalty();
	}
}

void Lion::FightBack(Warrior *enemy)
{
	Warrior::FightBack(enemy);
	if (enemy->get_strength() != 0)
	{
		loseLoyalty();
	}
}

void Lion::Hurt(Warrior *enemy, int atk)
{
	static int tmpStrength;
	tmpStrength = strength;
	Warrior::Hurt(enemy, atk);
	// ��������ת������
	if (enemy == NULL)
	{
		return;
	}
	else if (strength == 0)
	{
		enemy->set_strength(enemy->get_strength() + tmpStrength);
	}
}

/***********************************************
��ʿ�������ࣺWolf��
�ص㣺���Խɻ���˵�����
***********************************************/
class Wolf :public Warrior
{
public:
	Wolf(Headquarter *hq, int id, int strength, int atk, int cid = 4) : Warrior(hq, id, strength, atk, cid) {}
	virtual void disarm(Warrior *enemy)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!weapon[i])
			{
				weapon[i] = enemy->get_weapon(i);
			}
		}
	}
};

void Headquarter::makeWarrior()
{
	// ��ȡ��ǰ������ʿ�������ţ�����ֵ������ֵ
	int classID = ProduceOrder[numOfWarrior % 5];
	int strength = Warrior::initialStrength[classID];
	int atk = Warrior::initialAttack[classID];

	if (LifeValue < strength)
	{
		return;
	}

	LifeValue -= strength;
	int id = numOfWarrior + 1;
	numOfWarrior++;
	switch (classID)
	{
	case 0:
		warrior[id] = new Dragon(this, id, strength, atk, (double)LifeValue / strength);
		break;
	case 1:
		warrior[id] = new Ninja(this, id, strength, atk);
		break;
	case 2:
		warrior[id] = new Iceman(this, id, strength, atk);
		break;
	case 3:
		warrior[id] = new Lion(this, id, strength, atk);
		break;
	case 4:
		warrior[id] = new Wolf(this, id, strength, atk);
	}
	warrior[id]->printBornMessage();
	if (alliance == "red")
	{
		redWarrior = warrior[id];
		redWarrior->pCity = this;
	}
	else
	{
		blueWarrior = warrior[id];
		blueWarrior->pCity = this;
	}
}

void Headquarter::award(Warrior *w)
{
	if (w && (w->hq->alliance == alliance) && w->win)
	{
		w->win = false;
		if (LifeValue - 8 >= 0)
		{
			w->strength += 8;
			LifeValue -= 8;
		}
	}
}

void City::printMove()
{
	// ����ʿ���ֺ�˾�
	if (id == 0 && blueWarrior)
	{
		cout << gameTime << " " << blueWarrior << " reached red headquarter with " << blueWarrior->get_strength() << " elements and force " << blueWarrior->get_attack() << endl;
		if (red.numOfInvader == 2)
		{
			cout << gameTime << " " << "red headquarter was taken" << endl;
			GameOver = true;
		}
	}
	// ����ʿ������˾�
	else if (id == numOfCity + 1 && redWarrior)
	{
		cout << gameTime << " " << redWarrior << " reached blue headquarter with " << redWarrior->get_strength() << " elements and force " << redWarrior->get_attack() << endl;
		if (blue.numOfInvader == 2)
		{
			cout << gameTime << " " << "blue headquarter was taken" << endl;
			GameOver = true;
		}
	}
	else
	{
		if (redWarrior)
		{
			cout << gameTime << " " << redWarrior << " marched to city " << id << " with " << redWarrior->get_strength() << " elements and force " << redWarrior->get_attack() << endl;
		}
		if (blueWarrior)
		{
			cout << gameTime << " " << blueWarrior << " marched to city " << id << " with " << blueWarrior->get_strength() << " elements and force " << blueWarrior->get_attack() << endl;
		}
	}
}

void City::Fight()
{
	// ֻ��һ����ʿ�ұ�������û�з���ս��
	if (!redWarrior && blueWarrior && blueWarrior->get_strength() == 0)
	{
		blueWarrior = NULL;
	}
	if (redWarrior && !blueWarrior && redWarrior->get_strength() == 0)
	{
		redWarrior = NULL;
	}
	// ������ʿ���ڣ���Ϊ������һ��ս��
	if (redWarrior && blueWarrior)
	{
		// ��������
		if (redWarrior->get_strength() == 0 && blueWarrior->get_strength() == 0)
		{
			blueWarrior = NULL;
			redWarrior = NULL;
			return;
		}
		// һ��������
		else if (redWarrior->get_strength() == 0 && blueWarrior->get_strength() > 0)
		{
			blueWarrior->win = true;
			blueWarrior->yell();
		}
		else if (redWarrior->get_strength() > 0 && blueWarrior->get_strength() == 0)
		{
			redWarrior->win = true;
			redWarrior->yell();
		}
		// �ж�����������������ս��
		else
		{
			if (flag == "red" || (flag == "None" && id % 2 == 1))
			{
				redWarrior->Attack(blueWarrior);
			}
			else
			{
				blueWarrior->Attack(redWarrior);
			}
		}
		if (redWarrior->win)
		{
			redWarrior->earn_elements();
			redWarrior->disarm(blueWarrior);  // Wolf��е
			if (lastWinner == "red" && flag != "red")  // ��ʤ����
			{
				set_flag("red");
			}
			blueWarrior = NULL;
			lastWinner = "red";
		}
		else if (blueWarrior->win)
		{
			blueWarrior->earn_elements();
			blueWarrior->disarm(redWarrior);
			if (lastWinner == "blue" && flag != "blue")
			{
				set_flag("blue");
			}
			redWarrior = NULL;
			lastWinner = "blue";
		}
		else
		{
			lastWinner = "None";
		}
	}
}

/***********************************************
������������
�����ʿ��Ϣ��ʱ��
***********************************************/
ostream& operator<<(ostream &o, const Warrior *w)
{
	o << w->hq->alliance << " " << w->classes << " " << w->id;
	return o;
}

ostream& operator<<(ostream &o, const Time &t)
{
	o << setw(3) << setfill('0') << t.hour << ":" << setw(2) << t.minute;
	return o;
}

/***********************************************
������������
***********************************************/
int main()
{
	// �ļ��ض���
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		// ����ȫ�ֱ���
		gameTime.init(0, 0);
		GameOver = false;

		// ��������
		cin >> initialLifeValue >> numOfCity >> arrow_atk >> loyalty_loss >> TOTALTIME;
		for (int j = 0; j < 5; j++)
		{
			cin >> Warrior::initialStrength[j];
		}
		for (int j = 0; j < 5; j++)
		{
			cin >> Warrior::initialAttack[j];
		}

		// �ܲ��ͳ��г�ʼ��
		City* city[22];   // Ϊ���ó�����������ܲ�������Ϊָ��
		for (int j = 1; j <= numOfCity; j++)
		{
			city[j] = new City;
		}
		city[0] = &red;
		city[numOfCity + 1] = &blue;
		for (int j = 1; j <= numOfCity; j++)
		{
			city[j]->init(j, city[j - 1], city[j + 1]);
		}
		city[0]->init(0, NULL, city[1]);
		city[numOfCity + 1]->init(numOfCity + 1, city[numOfCity], NULL);
		// һ��Ҫ�ȵ���City��init�ڵ���Headquarter��init
		red.init(initialLifeValue, redOrder);
		blue.init(initialLifeValue, blueOrder);

		// ���Կ�ʼ
		cout << "Case " << i << ":" << endl;
		while (true)
		{
			if (gameTime.minute == 0)
			{
				red.makeWarrior();
				blue.makeWarrior();
			}
			if (gameTime.minute == 5)  // ʨ������
			{
				for (int j = 0; j <= numOfCity + 1; j++)
				{

					if (city[j]->get_red())
					{
						city[j]->get_red()->escape();
					}
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->escape();
					}
				}
			}
			if (gameTime.minute == 10)  // ��ʿ�ƶ�
			{
				// Ϊ�˷�ֹ�ƶ������һ��������Ϣ��ʧ�����ƶ������෴����move()
				for (int j = numOfCity + 1; j >= 0; j--)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->move();
					}
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					city[j]->printMove();
				}
				if (GameOver)
				{
					break;
				}
			}
			if (gameTime.minute == 20)  // ���в�������Ԫ
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j]->produceLifeValue();
				}
			}
			if (gameTime.minute == 30)  // ֻ��һ����ʿʱֱ��ȡ������Ԫ
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j]->get_red() && !city[j]->get_blue())
					{
						city[j]->get_red()->earn_elements();
					}
					else if (!city[j]->get_red() && city[j]->get_blue())
					{
						city[j]->get_blue()->earn_elements();
					}
				}
			}
			if (gameTime.minute == 35)  // �ż�
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					Warrior* redWarrior = city[j]->get_red();
					Warrior* blueWarrior = city[j]->get_blue();
					if (redWarrior)
					{
						redWarrior->putArrow(city[j + 1]->get_blue());
					}
					if (blueWarrior)
					{
						blueWarrior->putArrow(city[j - 1]->get_red());
					}
				}
			}
			if (gameTime.minute == 38)  // ��ը��
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->bomb(city[j]->get_blue());
					}
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->bomb(city[j]->get_red());
					}
				}
			}
			if (gameTime.minute == 40)  // ս��
			{
				for (int j = 1; j <= numOfCity; j++)
				{
					city[j]->Fight();
				}
				for (int j = 1; j <= numOfCity; j++)  // ���Ƚ����������
				{
					red.award(city[j]->redWarrior);
					blue.award(city[numOfCity - j + 1]->blueWarrior);
				}
			}
			if (gameTime.minute == 50)  // ˾���������ֵ
			{
				red.reportElements();
				blue.reportElements();
			}
			if (gameTime.minute == 55)  // ��ʿ��������
			{
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_red())
					{
						city[j]->get_red()->ReportWeapon();
					}
				}
				if (blue.invader)   // ���ֵ��ܲ�����ʿҲҪ����
				{
					blue.invader->ReportWeapon();
				}
				if (red.invader)
				{
					red.invader->ReportWeapon();
				}
				for (int j = 0; j <= numOfCity + 1; j++)
				{
					if (city[j]->get_blue())
					{
						city[j]->get_blue()->ReportWeapon();
					}
				}
			}

			gameTime.updateTime();
			if (60 * gameTime.hour + gameTime.minute > TOTALTIME)
			{
				break;
			}
		}

		for (int j = 1; j <= numOfCity; j++)
		{
			if (city[j])
			{
				delete city[j];
			}
		}
	}
	return 0;
}