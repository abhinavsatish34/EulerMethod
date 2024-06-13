#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

double expressionSeperator(string, string[]);
double elementCorrector(string, double, double, double);
double expressionSolver (double[], double);
double approximate(double, double, double, double);

int main() {
    cout << "Welcome to Abhinav's Euler's Method Calculator!" << endl << endl;
    string choice;
    cout << "What calculator would you like to use? " << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == "e" || choice == "E") {
        cin.clear();
        // Calculate Derivative:
        string userEqu;
        string equation[18];
        double elements[18];
        double d, size, stepSize, x0, y0, x1;
        int count = -1, add;
        cout << "Enter the Derivative Equation: " ;
        getline(cin, userEqu);
        cout << "Enter the initial x value: ";
        cin >> x0;
        cout << "Enter the initial y value: ";
        cin >> y0;
        cout << "Enter the ending x value: ";
        cin >> x1;
        cout << "Enter the size of every step: ";
        cin >> stepSize;
        size = expressionSeperator(userEqu, equation);
        cout << endl << "Iteration   Current X   Current Y   Derivative" << endl;

        cout << "----------------------------------------------" << endl;
        while (x0 < x1) {
            count++;
            for (int i = 0; i < size; i++) {
                unsigned long length = equation[i].length();
                if (equation[i] == "+") {
                    elements[i] = 998;
                }
                else if (equation[i] == "-") {
                    elements[i] = 997;
                }
                else if (equation[i] == "*") {
                    elements[i] = 1000;
                }
                else if (equation[i] == "/") {
                    elements[i] = 999;
                }
                else {
                    elements[i] = elementCorrector(equation[i], x0, y0, length);
                }
            }
            d = expressionSolver(elements, size);
            y0 += approximate(d, x0, y0, stepSize);
            add = approximate(d, x0, y0, stepSize);
            x0 += stepSize;
            cout << setw(9) << count << setw(12) << x0 << setw(12) << y0 << setw(13) << d << endl;
        }
        cout << "----------------------------------------------" << endl;
        cout << endl;
        return 0;
    }
    else if (choice == "i" || choice == "I") {
        return 2;
    }
    return -1;
}
double expressionSeperator(string userEqu, string equation[]) {
    int k = 0;
    int size = 0;
    stringstream ssin(userEqu);
    while (ssin.good() && k < 80){
       ssin >> equation[k];
        ++k;
        size++;
    }
    cout << endl;
    return size;
}
double elementCorrector(string element, double xCurr, double yCurr, double length) {
    vector<double> stack;
    int num = 0, carrotLoc = -1;
    bool negative = false, raise = false;
    double ans = 1.0;
    if (element[0] == '-') {
        stack.push_back(-1);
        negative = true;
    }
    if (!isdigit(element[0])) {
        if (element.substr(0, 2) == "ln") {
            return log(elementCorrector(element.substr(3, length - 3), xCurr, yCurr, length - 3));
        }
        else if (element.substr(0, 4) == "sqrt") {
            return sqrt(elementCorrector(element.substr(5, length - 5), xCurr, yCurr, length - 5));
        }
        else if (element.substr(0, 4) == "cbrt") {
            return cbrt(elementCorrector(element.substr(5, length - 5), xCurr, yCurr, length - 5));
        }
        else if (element.substr(0, 3) == "sin") {
            return sin(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 3) == "cos") {
            return cos(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 3) == "tan") {
            return tan(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 3) == "sec") {
            return 1.0 / sin(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 3) == "csc") {
            return 1.0 / cos(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 3) == "cot") {
            return 1.0 / tan(elementCorrector(element.substr(4, length - 4), xCurr, yCurr, length - 4));
        }
        else if (element.substr(0, 4) == "asin") {
            return asin(elementCorrector(element.substr(5, length - 5), xCurr, yCurr, length - 5));
        }
        else if (element.substr(0, 4) == "acos") {
            return acos(elementCorrector(element.substr(5, length - 5), xCurr, yCurr, length - 5));
        }
        else if (element.substr(0, 4) == "atan") {
            return atan(elementCorrector(element.substr(5, length - 5), xCurr, yCurr, length - 5));
        }
    }
    for (int j = 0; j < length; j++) {
        if (isdigit(element[j])) {
            num++;
        }
        if (element[j] == '^') {
            carrotLoc = j;
            raise = true;
            break;
        }
    }
    if (num > 0) {
        stack.push_back(stod(element.substr(0, num)));
    }
    if (carrotLoc >= 0) {
        for (int a = 0; a < carrotLoc; a++) {
            if (element[a] == 'x') {
                stack.push_back(xCurr);
            }
            else if (element[a] == 'y') {
                stack.push_back(yCurr);
            }
        }
    }
    else {
        for (int a = 0; a < length; a++) {
            if (element[a] == 'x') {
                stack.push_back(xCurr);
            }
            else if (element[a] == 'y') {
                stack.push_back(yCurr);
            }
        }
    }
    for (int q = 0; q < stack.size(); q++) {
        ans *= stack[q];
    }
    if (raise == false) {
        return ans;
    }
    else {
        return pow(ans, elementCorrector(element.substr(carrotLoc + 1, length), xCurr, yCurr, length));
    }
}
double expressionSolver (double elements[], double size) {
    double ans = 0;
    vector<double> multStack;
    vector<double> stack;
    for (int i = 0; i < size; i++) {
        if (elements[i] == 1000) {
            if (elements[i - 1] != 996) {
                multStack.push_back(elements[i - 1]);
            }
            if (elements[i + 1] != 996) {
                multStack.push_back(elements[i + 1]);
            }
            elements[i - 1] = 996;
            elements[i + 1] = 996;
            stack.push_back(multStack[0] * multStack[1]);
            multStack.pop_back();
            multStack.pop_back();
        }
        else if (elements[i] == 999) {
            if (elements[i - 1] != 996) {
                multStack.push_back(elements[i - 1]);
            }
            if (elements[i + 1] != 996) {
                multStack.push_back(1 / elements[i + 1]);
            }
            elements[i - 1] = 996;
            elements[i + 1] = 996;
            if (i > 1) {
                if (elements[i - 2] == 997) {
                    stack.push_back(-1 * multStack[0] * multStack[1]);
                }
            }
            else {
                stack.push_back(multStack[0] * multStack[1]);
            }
            multStack.pop_back();
            multStack.pop_back();
        }
    }
    for (int j = 0; j < size - 1; j++) {
        if (elements[j] == 997) {
            if (elements[j + 1] != 996 && elements[j + 1] != 997 && elements[j + 1] != 998 && elements[j + 1] != 1000) {
                stack.push_back(-1 * elements[j + 1]);
            }
        }
        else if (elements[j] == 998) {
            if (elements[j + 1] != 996 && elements[j + 1] != 997 && elements[j + 1] != 998 && elements[j + 1] != 1000) {
                stack.push_back(elements[j + 1]);
            }
        }
    }
    if (elements[0] != 996) {
        stack.push_back(elements[0]);
    }
    for (int q = 0; q < stack.size(); q++) {
        ans += stack[q];
    }
    return ans;
}
double approximate(double derivative, double xCurr, double yCurr, double stepSize) {
    return derivative * stepSize;
}
