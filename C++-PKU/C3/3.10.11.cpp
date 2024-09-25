/*
3. C程序设计进阶
10. 第10周
11. 编程题＃11：数据库内的学生信息

该程序仅仅支持增加和查询，不支持对原有数据的修改

*/

#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class MysMultimap {
public:
    map<string, int> m; // 使用标准库中的map来存储数据

    void Set(const string& key, int value) {
        auto range = m.equal_range(key);
        for (auto it = range.first; it != range.second; ++it) {
            it->second = value;
        }
    }

    void Insert(const string& key, int value) {
        m.insert(make_pair(key, value));
    }

    int Query(const string& key) {
        auto it = m.find(key);
        if (it != m.end()) {
            return it->second;
        }
        return -1; // 如果查不到，则返回-1
    }
};

ostream& operator<<(ostream& os, const pair<string, int>& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}


template <typename K, typename V, typename Comp = greater<K>>
class MyMultimap : public multimap<K, V, Comp> {
public:
    void Set(K key, V value) {
        auto range = this->equal_range(key);
        for (auto it = range.first; it != range.second; ++it) {
            it->second = value;
        }
    }
};

template <typename K, typename V>
ostream& operator<<(ostream& os, const pair<K, V>& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}


struct Student
{
        string name;
        int score;
};
template <class T>
void Print(T first,T last) {
        for(;first!= last; ++ first)
                cout << * first << ",";
        cout << endl;
}

int main()
{

        Student s[] = { {"Tom",80},{"Jack",70},
                                        {"Jone",90},{"Tom",70},{"Alice",100} };
        MyMultimap<string,int> mp;
        for(int i = 0; i<5; ++ i)
                mp.insert(make_pair(s[i].name,s[i].score));
        Print(mp.begin(),mp.end()); //按姓名从大到小输出

        mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
        Print(mp.begin(),mp.end());


        MyMultimap<int,string,less<int> > mp2;
        for(int i = 0; i<5; ++ i)
                mp2.insert(make_pair(s[i].score,s[i].name));

        Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
        mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
        Print(mp2.begin(),mp2.end());
        cout << "******" << endl;

        mp.clear();
        
        string name;
        string cmd;
        int score;
        while(cin >> cmd ) {
                if( cmd == "A") {
                        cin >> name >> score;
                        if(mp.find(name) != mp.end() ) {
                                cout << "erroe" << endl;
                        }
                        mp.insert(make_pair(name,score));
                }
                else if(cmd == "Q") {
                        cin >> name;
                        MyMultimap<string,int>::iterator p = mp.find(name);
                        if( p!= mp.end()) {
                                cout << p->second << endl;
                        }
                        else {
                                cout << "Not Found" << endl;
                        }
                }
        }
        return 0;
}
