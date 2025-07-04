/*
3. C程序设计进阶
9. 第8 module  
5. 编程题＃5： 热血格斗场

input 
3
2 1
3 3
4 2

output
2 1
3 2
4 2

*/

#include <iostream>
#include <map>
using namespace std;

int main()
{
	typedef map<int, int> power_id_map;
	power_id_map members;
	members[1000000000] = 1;

	int n;
	cin >> n;
	while (n--)
	{
		int id, power;
		cin >> id >> power;
        // Declare iterators to find the closest members in terms of power.
		power_id_map::iterator i_less, i_geq, i_match;
		// Find the first member not less than the new member in terms of power.
        i_less = members.lower_bound(power);
        // Copy the iterator of the member not less than the new member's power.
		i_geq = i_less;
        // Check if 'i_less' is not pointing to the first member.
		if (i_less != members.begin())
		{// Move 'i_less' back to point to the member just less than the new member's power.
			i_less--;
		}
        // Determine the closest member to the new member's power and assign it to 'i_match'.
		// ternary conditional operator 
        i_match = (power - i_less->first) <= (i_geq->first - power) ? i_less : i_geq;
		// Output the new member's id and the id of the closest member in power.
        cout << id << " " << i_match->second << endl;
		// Add the new member to the map with their power as key and id as value.
        members[power] = id;
	}
}
