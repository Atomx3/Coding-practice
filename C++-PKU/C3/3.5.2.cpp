/*
3. C++程序设计
5. 第5周
2. 编程题＃2： 魔兽世界之二：装备

程序要求：
在之前的魔兽世界程序基础上，增加武器、士气、忠诚度等属性，并在武士降生时输出相应的信息。

武器编号及名称：
0：sword
1：bomb
2：arrow

武士获得武器的规则：
- dragon：一件武器，编号为 n % 3
- ninja：两件武器，编号为 n % 3 和 (n+1) % 3
- iceman：一件武器，编号为 n % 3

dragon 还需要输出士气，lion 需要输出忠诚度。
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// 定义输入顺序对应的武士种类名称
string inputOrder[5] = { "dragon","ninja","iceman","lion","wolf" };
// 红方武士的制造顺序
string redWarriorOrder[5] = { "iceman","lion","wolf","ninja","dragon" };
// 蓝方武士的制造顺序
string blueWarriorOrder[5] = { "lion","dragon","ninja","iceman","wolf" };
// 按照 inputOrder 顺序存储初始生命值
int initialLifeValues[5];

// 武器名称数组
string weaponNames[3] = { "sword", "bomb", "arrow" };

// 武士类
class Warrior {
private:
    int id;             // 武士编号
    int kindNo;         // 武士种类编号（0-4），对应 inputOrder 的下标
    string kindStr;     // 武士种类名称
    int hp;             // 生命值
    double morale;      // dragon 的士气
    int loyalty;        // lion 的忠诚度
    int weapon[2];      // 武器编号数组，最多持有两件武器

public:
    // 构造函数，初始化武士的属性
    Warrior(int id_, int kindNo_, int hp_, int totalHp, string alliance) {
        id = id_;
        kindNo = kindNo_;
        kindStr = inputOrder[kindNo];
        hp = hp_;
        morale = 0;
        loyalty = 0;
        weapon[0] = -1; // 初始化为 -1 表示没有武器
        weapon[1] = -1;

        // 根据武士种类分配特殊属性和武器
        if (kindStr == "dragon") {
            weapon[0] = id % 3; // 获得一件武器
            morale = (double)totalHp / hp_; // 计算士气
        }
        else if (kindStr == "ninja") {
            weapon[0] = id % 3;         // 获得第一件武器
            weapon[1] = (id + 1) % 3;   // 获得第二件武器
        }
        else if (kindStr == "iceman") {
            weapon[0] = id % 3; // 获得一件武器
        }
        else if (kindStr == "lion") {
            loyalty = totalHp; // 忠诚度等于司令部剩余生命元
        }
        // wolf 没有特殊属性
    }

    // 输出武士的额外信息
    void printExtraInfo() {
        if (kindStr == "dragon") {
            // dragon 输出武器和士气
            cout << "It has a " << weaponNames[weapon[0]] << ",and it's morale is "
                 << fixed << setprecision(2) << morale << endl;
        }
        else if (kindStr == "ninja") {
            // ninja 输出两件武器
            cout << "It has a " << weaponNames[weapon[0]] << " and a "
                 << weaponNames[weapon[1]] << endl;
        }
        else if (kindStr == "iceman") {
            // iceman 输出武器
            cout << "It has a " << weaponNames[weapon[0]] << endl;
        }
        else if (kindStr == "lion") {
            // lion 输出忠诚度
            cout << "It's loyalty is " << loyalty << endl;
        }
        // wolf 没有额外信息输出
    }

    // 获取武士种类名称
    string getKindStr() {
        return kindStr;
    }
};

// 司令部类
class Headquarters {
private:
    string alliance;        // 阵营名称，"red" 或 "blue"
    int totalHp;            // 司令部剩余的生命元
    int curMakingSeqIdx;    // 当前应制造的武士序号索引
    int warriorNum[5];      // 每种武士的数量，按 inputOrder 顺序
    int stopped;            // 标记是否停止制造武士
    int totalWarriorNum;    // 已制造武士的总数
    Warrior* pWarriors[1000];   // 指针数组，保存已制造的武士对象

    int makingSeq[5];       // 制造武士的顺序序列，存储 kindNo

public:
    // 构造函数，初始化司令部属性
    Headquarters(string alliance_, int m_, int seq[5]) {
        alliance = alliance_;
        totalHp = m_;
        curMakingSeqIdx = 0;
        totalWarriorNum = 0;
        stopped = 0;
        for (int i = 0; i < 5; i++) {
            warriorNum[i] = 0;        // 初始化每种武士的数量
            makingSeq[i] = seq[i];    // 复制制造序列
        }
    }

    // 析构函数，释放动态分配的武士对象
    ~Headquarters() {
        for (int i = 0; i < totalWarriorNum; i++)
            delete pWarriors[i];
    }

    // 判断是否已停止制造武士
    int isStopped() {
        return stopped;
    }

    // 尝试制造武士并输出相应的信息
    void makeWarrior(int time) {
        if (stopped) {
            return;
        }
        int kindNo;
        int attempt = 0; // 尝试次数
        while (attempt < 5) {
            kindNo = makingSeq[curMakingSeqIdx]; // 获取当前要制造的武士种类编号
            int hpNeeded = initialLifeValues[kindNo]; // 该武士需要的生命元
            if (totalHp >= hpNeeded) {
                // 司令部有足够的生命元来制造该武士
                totalHp -= hpNeeded;          // 扣除生命元
                totalWarriorNum++;            // 武士总数加一
                warriorNum[kindNo]++;         // 该种武士数量加一
                // 创建武士对象并保存
                Warrior* p = new Warrior(totalWarriorNum, kindNo, hpNeeded, totalHp, alliance);
                pWarriors[totalWarriorNum - 1] = p;
                // 输出武士降生信息
                cout << setw(3) << setfill('0') << time << " " << alliance << " " << p->getKindStr()
                     << " " << totalWarriorNum << " born with strength " << hpNeeded << ","
                     << warriorNum[kindNo] << " " << p->getKindStr() << " in " << alliance
                     << " headquarter" << endl;
                p->printExtraInfo();  // 输出武士的额外信息
                // 更新制造序列索引，循环取值 0-4
                curMakingSeqIdx = (curMakingSeqIdx + 1) % 5;
                break; // 结束制造
            }
            else {
                // 生命元不足，尝试下一个武士
                curMakingSeqIdx = (curMakingSeqIdx + 1) % 5;
                attempt++;
            }
        }
        if (attempt == 5) {
            // 尝试了5次仍无法制造武士，司令部停止制造
            stopped = 1;
            // 输出司令部停止制造的消息
            cout << setw(3) << setfill('0') << time << " " << alliance << " headquarter stops making warriors" << endl;
        }
    }
};

int main() {
    int testCases;
    cin >> testCases; // 读取测试用例数
    int m;            // 司令部初始生命元
    int caseNo = 1;   // 用于输出案例编号
    while (testCases--) {
        cin >> m; // 输入司令部初始生命元
        for (int i = 0; i < 5; i++) {
            cin >> initialLifeValues[i]; // 输入按照 inputOrder 顺序的初始生命值
        }
        cout << "Case:" << caseNo++ << endl; // 输出案例编号
        int redSeq[5] = { 2,3,4,1,0 };   // red 制造序列对应的 kindNo
        int blueSeq[5] = { 3,0,1,2,4 };  // blue 制造序列对应的 kindNo

        // 创建 red 和 blue 司令部对象
        Headquarters redHQ("red", m, redSeq);
        Headquarters blueHQ("blue", m, blueSeq);

        int time = 0; // 初始化时间为 0
        // 当任一司令部未停止制造时，继续循环
        while (!redHQ.isStopped() || !blueHQ.isStopped()) {
            if (!redHQ.isStopped()) {
                // red 司令部制造武士
                redHQ.makeWarrior(time);
            }
            if (!blueHQ.isStopped()) {
                // blue 司令部制造武士
                blueHQ.makeWarrior(time);
            }
            time++; // 时间加一（小时）
        }
    }
    return 0;
}