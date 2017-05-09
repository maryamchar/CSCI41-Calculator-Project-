#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> values;
vector<string> variables;

vector<string> loopVariables;
vector<char> loopOperators;
//Converts the passed in string to all uppercase.
void uppercaseify(string& mystr) {
    for (auto& c : mystr)
        c = toupper(c);
}
//True if the passed in string is all letters.
bool is_alpha(string& mystr) {
    for (auto& c : mystr)
        if (!(isalpha(c)))
            return false;
    return true;
}
//true if mystr is all digits
bool is_digit(string& mystr) {
    for (auto& c : mystr)
        if (!(isdigit(c)))
            return false;
    return true;
}
//Returns the index location of the variable within the vector.
long long index(string key) {
    auto it = find(variables.begin(), variables.end(), key);
    auto index = distance(variables.begin(), it);
    return index;
}
void die() {                                                    //Exits program.
    cout << "BAD INPUT" << endl;
    exit(0);
}


int main() {
    bool loopTrue = false;
    int loop = 0, counter = 0, number, answer, scalor;
    string variable, function, a;
    char operation, equals;
    while (cin) {                                                //MAIN LOOP.
        int defaultLoop = 1;
        cin >> function;
        uppercaseify(function);
        if (function == "QUIT") break;
        if (function == "LET") {                               //Takes in "LET" to make sure they are creating variables.
            cin >> variable;
            uppercaseify(variable);
            if (find(variables.begin(), variables.end(), variable) != variables.end()) die(); //If the variable has already been created die().
            if (!(is_alpha(variable))) die();                   //If the variable is not a letter die().
            if (variable.size() > 1) die();                     //If the variavle is more than 1 letter die().
            variables.push_back(variable);
            cin >> equals;                                      //Eats the '=', use it to make sure that they used a '=' though.
            if (equals == '=') {
                cin >> number;
                if (!cin) die();
                else if (number < 0 || number > 255) die();     //If the number is greater than 255 or negative die().
                else values.push_back(number);
            }
            else die();
        }
        if (function == "LOOP") {                               //loop was called
            cin >> loop;
            loop -= 1;
        }
        if (function.size() == 1 || is_digit(function)) {       //user inputted a number or a single letter
            while (defaultLoop || loop) {

                if (loop == 0 && loopTrue) {
                    loopTrue = false;
                    break;
                }
                if (loop != 0 && loopTrue == true) {            //if loopTrue = true, will enter automatic loop after regular user entered loop
                    if(is_alpha(function)) {
                        answer = values.at(index(function));
                        values[index(function)] += 1;
                    }else {
                        answer = atoi(function.c_str());
                    }
                }else if (is_alpha(function)) {             //if the user inputs a variable
                    answer = values.at(index(function));        //determines the first variable value of the operation based on corresponding value in the parallel "values" vector
                    values[index(function)] += 1;               //post-increments the value in the "values" vector
                }else if (is_digit(function)) {             //if the user input a number:
                    answer = atoi(function.c_str());            //the string "operation" will be convert to an int for usage
                }else break;
                while (defaultLoop || loop) {
                    if(loop != 0 && loopTrue == true) operation = loopOperators.at(counter);
                    else cin >> operation;
                    if (defaultLoop != 0 && !(loopTrue)) loopOperators.push_back(operation);
                    if (operation == '+') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);//if loopTrue
                        else {                                                       //a='the next value in the loopVariables vector
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer += values.at(index(a));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());               //Converts values in a string to an int.
                            answer += scalor;
                        }
                    } else if (operation == '-') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);
                        else {
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer -= values.at(index(a));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());
                            answer -= scalor;
                        }
                    } else if (operation == '*') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);
                        else {
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer *= values.at(index(a));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());
                            answer *= scalor;
                        }
                    } else if (operation == '/') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);
                        else {
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer /= values.at(index(a));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());
                            answer /= scalor;
                        }
                    } else if (operation == '^') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);
                        else {
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer = pow(answer, (values.at(index(a))));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());
                            answer = pow(answer, scalor);
                        }
                    } else if (operation == '%') {
                        if(loop != 0 && loopTrue == true) a = loopVariables.at(counter);
                        else {
                            cin >> a;
                            uppercaseify(a);
                        }
                        if (defaultLoop != 0) loopVariables.push_back((string)a);
                        if (is_alpha(a)) {
                            answer = answer % values.at(index(a));
                            values[index(a)] += 1;
                        }else {
                            scalor = atoi(a.c_str());
                            answer = answer % scalor;
                        }
                    }
                    //breaks from the loop after all the loops have run, reinitializes certain values,
                    //should only run once per loop command
                    if (!defaultLoop && loop == 1 && loopTrue && (counter+1) == (int)loopVariables.size()) {
                        cout << answer << endl;
                        loopOperators.clear();
                        loopVariables.clear();
                        loopTrue = false;
                        loop = 0;
                        counter = 0;
                        break;
                    }
                    //increments counter to move along the the vectors holding the operation automatically,
                    //runs a certain amount of times per loop depending on how big the operation was
                    if ((counter+1) != (int)loopVariables.size() && loopTrue) {
                        counter++;

                    //decrements loop1 after every loop and prints the answer, reinitializes counter
                    //for next loop
                    }else if (loop > 0 && loopTrue) {
                        loop--;
                        cout << answer << endl;
                        counter = 0;
                        break;

                    //only used for a regular operation ie no loop
                    }else if (cin.get() == '\n' && defaultLoop > 0) {
                        cout << answer << endl;
                        if(loop > 0) loopTrue = true;
                        defaultLoop--;
                        break;
                    }
                }
            }
        }
        //for testing purposes, prints the state of main variables in the program
        if (function == "AS") {
            int j = 0;
            for (auto i : variables) {
                cout << i << " = ";
                cout << values[j] << endl;
                j++;
            }
            cout << "loop : " << defaultLoop << endl;
            cout << "loop1 : " << loop << endl;
            cout << "loopTrue: " << loopTrue << endl;
            cout << "a: " << a <<endl;
            cout << "operand: " << operation << endl;
            cout << "scalor: " << scalor << endl;
            cout << "counter: " << counter << endl;
        }
    }
}


