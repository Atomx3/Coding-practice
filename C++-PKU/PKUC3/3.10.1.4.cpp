/*
用程序实例说明容器的特点：map/ multimap， set/ multiset，vector, list

*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <multimap>
#include <multiset>

int main() {
    // map 容器：关键字唯一，值可以重复
    std::map<int, std::string> mapContainer;
    mapContainer[1] = "Apple";
    mapContainer[2] = "Banana";
    mapContainer[3] = "Cherry";
    // 尝试插入相同关键字的元素会覆盖原有的值
    mapContainer[3] = "Durian";

    // multimap 容器：关键字可以重复，值也可以重复
    std::multimap<int, std::string> multimapContainer;
    multimapContainer.insert(std::make_pair(1, "Apple"));
    multimapContainer.insert(std::make_pair(1, "Avocado")); // 关键字重复

    // set 容器：元素唯一，自动排序
    std::set<int> setContainer;
    setContainer.insert(3);
    setContainer.insert(1);
    setContainer.insert(2);
    // 尝试插入重复元素会失败
    setContainer.insert(2);

    // multiset 容器：元素可以重复，自动排序
    std::multiset<int> multisetContainer;
    multisetContainer.insert(3);
    multisetContainer.insert(1);
    multisetContainer.insert(2);
    // 可以插入重复元素
    multisetContainer.insert(2);

    // vector 容器：支持随机访问，按插入顺序存储
    std::vector<std::string> vectorContainer;
    vectorContainer.push_back("Apple");
    vectorContainer.push_back("Banana");
    vectorContainer.push_back("Cherry");

    // list 容器：不支持随机访问，按插入顺序存储
    std::list<std::string> listContainer;
    listContainer.push_back("Apple");
    listContainer.push_back("Banana");
    listContainer.push_back("Cherry");

    // 输出 map 容器的内容
    std::cout << "map 容器内容：" << std::endl;
    for (const auto& pair : mapContainer) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 输出 multimap 容器的内容
    std::cout << "\nmultimap 容器内容：" << std::endl;
    for (const auto& pair : multimapContainer) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 输出 set 容器的内容
    std::cout << "\nset 容器内容：" << std::endl;
    for (int elem : setContainer) {
        std::cout << elem << std::endl;
    }

    // 输出 multiset 容器的内容
    std::cout << "\nmultiset 容器内容：" << std::endl;
    for (int elem : multisetContainer) {
        std::cout << elem << std::endl;
    }

    // 输出 vector 容器的内容
    std::cout << "\nvector 容器内容：" << std::endl;
    for (const std::string& elem : vectorContainer) {
        std::cout << elem << std::endl;
    }

    // 输出 list 容器的内容
    std::cout << "\nlist 容器内容：" << std::endl;
    for (const std::string& elem : listContainer) {
        std::cout << elem << std::endl;
    }

    return 0;
}