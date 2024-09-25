# Coding practice

## [程序设计与算法 Specialization]（https://www.coursera.org/specializations/biancheng-suanfa）

## Folder name
- C1, 计算导论与C语言基础
- C2, C程序设计进阶
- C3, C++程序设计
- C4, 算法基础
- C5, 数据结构基础
- C6, 高级数据结构与算法
- C7, 程序开发项目实践

### File name
文件名规则：例如 2.3.3.cpp
* 2.C程序设计进阶 (系列课程的第二课)
* 3.函数递归（该课第三周）
* 3.编程题＃4：扩号匹配问题（该周第四题）

不能保证全部代码都通过coursera或[POJ](http://pkuic.openjudge.cn/)的评价



Debugging case：  
% c++ 3.9.1.cpp  
3.9.1.cpp:83:9: warning: 'auto' type specifier is a C++11 extension [-Wc++11-extensions]  
for(auto p : v) {  
^  
3.9.1.cpp:83:16: warning: range-based for loop is a C++11 extension [-Wc++11-extensions]  
for(auto p : v) {  
^  
2 warnings generated.  


## Standard compile in terminal of Macbook pro：  
g++ -std=c++11 -o program 3.9.1.cpp
./program 
