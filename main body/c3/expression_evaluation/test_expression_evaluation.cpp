//
// Created by Lenovo on 2022/4/15.
//
#include "iostream"
#include "vector"
#include "map"
#include "algorithm"

// 装箱函数
std::vector<char> putin(std::string s){
    std::vector<char> res;
    for (int i = 0; i < s.size(); ++i) {
        res.push_back(s[i]);
    }
    return res;
}

// 运算符集合及其优先级
std::map<char, int> operators
        {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

// 判断两个运算符间的优先级
bool higher_priority(char op1, char op2){
    return operators.find(op1)->second - operators.find(op2)->second > 0;
}

// 判断能否将运算符入栈
bool can_push(std::vector<char> stack, char o){
    // 1.辅助栈空时可以 2.被比较的是左括号时可以 3.比栈顶操作符优先级高（作为新栈顶先输出）
    return stack.empty() || stack.back() == '(' || higher_priority(o, stack.back());
}

// 解析运算符
std::string eval(char ops, std::string a, std::string b){
    std::map<char, int> eval {{'+', stoi(a) + stoi(b)},{'-', stoi(a) - stoi(b)},
                              {'*', stoi(a) * stoi(b)}, {'/', stoi(a) / stoi(b)}};
    return std::to_string(eval.find(ops)->second);
}

// 中缀转后缀表达式
std::vector<char> mid_to_post(std::vector<char> c){
    std::vector<char> res;
    std::vector<char> stack;
    for (int i = 0; i < c.size(); ++i) {
        if (isdigit(c[i])){
            res.push_back(c[i]);
        } else if (c[i] == '('){
            stack.push_back(c[i]);
        } else if (operators.find(c[i])->first == c[i]){
            // 不断出栈，直至满足入栈条件
            while (!can_push(stack, c[i])){
                char back = stack.back();
                res.push_back(back);
                stack.pop_back();
            }
            stack.push_back(c[i]);
            // 当前序列符号是右括号
        } else{
            std::vector<char> tmp;
            while (stack.back() != '('){
                char back = stack.back();
                tmp.push_back(back);
                stack.pop_back();
            }
            stack.pop_back();
            reverse(tmp.begin(), tmp.end());
            res.insert(res.end(), tmp.begin(), tmp.end());
        }
    }
    while (!stack.empty()){
        char back = stack.back();
        res.push_back(back);
        stack.pop_back();
    }
    return res;
}

// 计算后缀表达式
int eval_post(std::vector<char> post){
    std::vector<std::string> nums;
    std::vector<char> op;
    for (int i = 0; i < post.size(); ++i) {
        if (operators.find(post[i])->first == post[i]){
            op.push_back(post[i]);
            if (op.size() > 0 && nums.size() > 1){
                std::string num = eval(post[i], nums[nums.size() - 2], nums[nums.size() - 1]);
                nums.pop_back();
                nums.pop_back();
                op.pop_back();
                nums.push_back(num);
            }
        } else{
            nums.push_back(std::string {} = (post[i]));
        }
    }
    return stoi(nums[0]);
}

void test(std::vector<char> mid){
    std::cout << "mid: ";
    for (int i = 0; i < mid.size(); ++i) {
        std::cout << mid[i] << " ";
    }
    std::cout << std::endl;
    std::vector<char> post = mid_to_post(mid);
    std::cout << "post: ";
    for (int i = 0; i < post.size(); ++i) {
        std::cout << post[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "val: " << eval_post(post) << std::endl;
}

int main(){
    test(putin("(4+3+5)/2*4+7*(2+3)"));
    return 0;
}