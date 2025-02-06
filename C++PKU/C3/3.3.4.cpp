/*
3. C++程序设计
3. 第3周
4. 编程题＃4：魔兽世界之一：备战

魔兽游戏程序：
3.3.4.cpp，编程题＃4：魔兽世界之一：备战
3.5.2.cpp，编程题＃2： 魔兽世界之二：装备
3.6.4.cpp, 编程题＃4： 魔兽世界终极版

I have never played this game, and finished this program with the help of AI.

*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string inputOrder[5] = { "dragon","ninja","iceman","lion","wolf" };
string redWarrior[5] = { "iceman","lion","wolf","ninja","dragon" };
int redInitialStrength[5];
string blueWarrior[5] = { "lion","dragon","ninja","iceman","wolf" };
int blueInitialStrength[5];

class Warrior
{
private:
	int id;
	int strength;
	int attack;
	string classes;
public:
	Warrior() {}
	Warrior(int id, int s, int atk, string classes) :
		id(id), strength(s), attack(atk), classes(classes) {}
	int getStrength()
	{
		return strength;
	}
	string getClasses()
	{
		return classes;
	}
};

class Headquater // class definition
{
private:
	string alliance;
	static int redTotalStrength;
	static int blueTotalStrength;
	static int redWarriorCount;
	static int blueWarriorCount;
	int numOfEachClasses[5]= { 0 };
	int warriorIndex;
	Warrior warrior[1000];
	// track if each headquarter is stopped.
	bool redStop = false;
	bool blueStop = false;

public:
	Headquater(string a) :alliance(a), warriorIndex(0){ }
	static void SetToalStrength(int strength)
	{
		redTotalStrength = strength;
		blueTotalStrength = strength;
	}
	static void ResetWarriorCount()
	{
		redWarriorCount = 0;
		blueWarriorCount = 0;
	}
	int makeWarrior();
	void setRedStop(bool stop) {
      redStop = stop; 
    }
    void setBlueStop(bool stop) {
       blueStop = stop;
    }
};

int Headquater::redWarriorCount = 0;
int Headquater::blueWarriorCount = 0;
int Headquater::redTotalStrength = 0;
int Headquater::blueTotalStrength = 0;

int Headquater::makeWarrior()
{
	static int notMadeCount = 0;
	if (alliance == "red")
	{
		 // check the redStop flag at the beginning of the red logic
		if (redStop) {
			return false;
		}

		string classes = redWarrior[warriorIndex];
		int strength = redInitialStrength[warriorIndex];
		if (redTotalStrength - strength >= 0)
		{
			notMadeCount = 0;
			redTotalStrength -= strength;// decrement strength
			warrior[redWarriorCount] = Warrior(redWarriorCount,strength,0,classes);
			redWarriorCount++;
			numOfEachClasses[warriorIndex]++;
			cout << "red " << classes << " " << redWarriorCount << " born with strength " << strength << "," << numOfEachClasses[warriorIndex] << " " << classes << " in red headquarter" << endl;
			++warriorIndex %= 5;
			return true;
		}
		else
		{
			notMadeCount++;
			++warriorIndex %= 5;
			if (notMadeCount > 5)
			{
				notMadeCount = 0;
				return false;
			}
			return this->makeWarrior();
		}
	}
	else if (alliance == "blue")
	{
		 // check the blueStop flag at the beginning of the blue logic
		if (blueStop) {
			return false;
		}
		//testing and debugging the status of blue block.
		// cout <<'\n'<<"Blue total strength: " << blueTotalStrength << endl;
		// cout << "Warrior index: " << warriorIndex << endl;
    	// cout << "Not made count: " << notMadeCount << endl;

		string classes = blueWarrior[warriorIndex];
		int strength = blueInitialStrength[warriorIndex];
		if (blueTotalStrength - strength >= 0)
		{
			// make warrior
			//cout << "Making blue warrior!" << endl;
  		
			notMadeCount = 0;
			blueTotalStrength -= strength;// decrement strength
			warrior[blueWarriorCount] = Warrior(blueWarriorCount,strength,0,classes);
			blueWarriorCount++;
			numOfEachClasses[warriorIndex]++;
			cout << "blue " << classes << " " << blueWarriorCount << " born with strength " << strength << "," << numOfEachClasses[warriorIndex] << " " << classes << " in blue headquarter" << endl;
			++warriorIndex %= 5;
			return true;
				
		}
		else
		{
			notMadeCount++;// Increment failure count
			++warriorIndex %= 5; // Try next warrior
			if (notMadeCount > 5)
			{
				notMadeCount = 0;
				//cout << "Not enough strength to make blue warrior!" << endl;
				return false;
			}
			else{
			return this->makeWarrior(); // Recursive call without printing
			}
		}

		
	}
    return 0;
}

int main()
{
	string redStr = "red";
	Headquater redHQ(redStr); 
	string blueStr = "blue";
	Headquater blueHQ(blueStr);
	redHQ.setRedStop(true);
	blueHQ.setBlueStop(true);

	int numOfTest = 0;
	cin >> numOfTest;

	for (int i = 1; i <= numOfTest; i++)
	{
		int M = 0;
		cin >> M;
		Headquater::SetToalStrength(M);
		Headquater::ResetWarriorCount();
		string redStr = "red", blueStr = "blue"; 
		Headquater red(redStr), blue(blueStr);


		for (int j = 0; j < 5; j++)
		{
			int strength;
			cin >> strength;
			for (int k = 0; k < 5; k++)
			{
				if (inputOrder[j] == redWarrior[k])
				{
					redInitialStrength[k] = strength;
				}
			}
			for (int k = 0; k < 5; k++)
			{
				if (inputOrder[j] == blueWarrior[k])
				{
					blueInitialStrength[k] = strength;
				}
			}
		}

		cout << "Case:" << i << endl;
		bool redStop = false;
		bool blueStop = false;
		int time = 0;
		while (true)
		{
			if (!redStop)
			{
				cout << setw(3) << setfill('0') << time << " ";
				redStop = !red.makeWarrior();
				if (redStop)
				{
					cout << "red headquarter stops making warriors" << endl;
					redHQ.setRedStop(true);
				}

			}
			if (!blueStop)
			{
				cout << setw(3) << setfill('0') << time << " ";
				blueStop = !blue.makeWarrior();
				if (blueStop)
				{
					cout << "blue headquarter stops making warriors" << endl;
					blueHQ.setBlueStop(true);
				}
			}
			if (redStop && blueStop)
			{
				break;
			}
			time++;
		}

	}
	return 0;
}