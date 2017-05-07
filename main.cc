#include <iostream>
#include <ncurses.h>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <cmath>
using namespace std;

const int UP = 65;
vector<float> numbers;
vector<string> variables;

void uppercaseify(string& mystr) {                              //Converts the passed in string to all uppercase.
    for (auto& c: mystr)
        c = toupper(c);
}

bool is_alpha(string& mystr) {                                  //True if the passed in string is all letters.
    for (auto& c: mystr)
        if(!(isalpha(c)))
            return false;
    return true;
}
bool is_digit(string& mystr) {
    for (auto& c: mystr)
        if(!(isdigit(c)))
            return false;
    return true;
}

long long index(string key) {                                   //Returns the index location of the variable within the vector.
    auto it = find(variables.begin(), variables.end(), key);
    auto index = distance(variables.begin(), it);
    return index;
}
void die() {                                                    //Exits program.
    cout << "BAD INPUT" << endl;
    exit(0);
}


int main() {
    float number;
    float answer;
    float scalor;
    string variable;
    string operation;
    string a;
    char operand;
    char equals;
    while(cin) {                                                //MAIN LOOP.
        cin >> operation;
        uppercaseify(operation);
        if(operation == "QUIT") break;
        if(operation == "LET") {                                //Takes in "LET" to make sure they are creating variables.
            cin >> variable;
            uppercaseify(variable);
                                                                //If the variable has already been created die().
            if(find(variables.begin(), variables.end(), variable) != variables.end()) die();
            if(!(is_alpha(variable))) die();                    //If the variable is not a letter die().
            if(variable.size() > 1) die();                  //If the variavle is more than 1 letter die().
            variables.push_back(variable);
            cin >> equals;                                      //Eats the '=', use it to make sure that they used a '=' though.
            if(equals == '=') {
                cin >> number;
                if(!cin) die();
                else if(number < 0 || number > 255) die();      //If the number is greater than 255 or negative die().
                else numbers.push_back(number);
            }
        }

        if(operation.size() == 1) {
            if(is_alpha(operation)) {
                answer = numbers.at(index(operation));
                numbers[index(operation)] += 1;
            }
            else if(is_digit(operation)){
                answer = atoi(operation.c_str());
            }
            else break;
            while(cin) {
                cin >> operand;
                if(operand == '+') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)) {
                        answer += numbers.at(index(a));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());               //Converts numbers in a string to an int.
                        answer += scalor;
                    }
                }
                else if(operand == '-') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)){
                        answer -= numbers.at(index(a));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());
                        answer -= scalor;
                    }
                }
                else if(operand == '*') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)){
                        answer *= numbers.at(index(a));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());
                        answer *= scalor;
                    }
                }
                else if(operand == '/') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)){
                        answer /= numbers.at(index(a));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());
                        answer /= scalor;
                    }
                }
                else if(operand == '^') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)){
                        answer = pow(answer, (numbers.at(index(a))));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());
                        answer = pow(answer, scalor);
                    }
                }
                else if(operand == '%') {
                    cin >> a;
                    uppercaseify(a);
                    if(is_alpha(a)){
                        answer = (int)answer % (int)(numbers.at(index(a)));
                        numbers[index(a)] += 1;
                    }
                    else {
                        scalor = atoi(a.c_str());
                        answer = (int)answer %  (int)scalor;        //Casts the values as ints; can't use float values with (%).
                    }
                }
                if(cin.get() == '\n') {
                    break;
                }
            }
            cout << "answer = " << answer << endl;
        }
        if(operation == "AS") {
            int j = 0;
            for(auto i : variables) {
                cout << i << " = ";
                cout << numbers[j] << endl;
                j++;
            }
        }
    }
}


