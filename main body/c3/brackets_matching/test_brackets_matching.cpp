//
// Created by Lenovo on 2022/4/14.
//

#include "vector"
#include "map"
#include "iostream"

// 定义不同括号的匹配关系
std::map<char, char> brackets
        {std::pair<char, char>{')', '('},
         std::pair<char, char>{']', '['},
         std::pair<char, char>{'}', '{'}};


// 判断括号序列是否匹配
bool is_matched(std::string s){
    std::vector<char> stack;
    for (int i = 0; i < s.length(); ++i) {
        if (brackets.find(s[i])->first != s[i]){
            stack.push_back(s[i]);
        } else if (!stack.empty() && brackets[s[i]] == stack.back()){
            stack.pop_back();
        } else{
            return false;
        }
    }
    return stack.empty();
}

void test_matching(std::vector<std::string> test){
    for (int i = 0; i < test.size(); ++i) {
        std::cout << "#" << i << ", ";
        std::cout << test[i] << ", ";
        std::cout << "res: " << is_matched(test[i]) << std::endl;
    }
}

int main(){
    std::vector<char> c = std::vector<char>('1');
    std::vector<std::string> test =
            {"(([[{{}}]]))", "(()()[]{{}}[]()())", "{{}{(})", "((())"};
    test_matching(test);
    return 0;
}