#include <iostream>
#include <string>
#include "slugify-cpp.hpp"

using namespace std;

void slugify_demo(){
    slugify_init();
    string s1="我爱北京天安门";
    string s2="混合的字符串 mixed string ♥";

    cout << "slugify示例：" << endl;
    cout << s1 << " => " << slugify(s1) << endl;
    cout << s2 << " => " << slugify(s2) << endl;
}
int main(){
    slugify_demo();
}
