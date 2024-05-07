#include <iostream>
#include <stack>
#include <string>

using namespace std;

string parsingTable[12][9] = {
    {"S5", "", "", "S4", "", "", "1", "2", "3"},
    {"", "S6", "", "", "", "ACC", "", "", ""},
    {"", "R2", "S7", "", "R2", "R2", "", "", ""},
    {"", "R4", "R4", "", "R4", "R4", "", "", ""},
    {"S5", "", "", "S4", "", "", "8", "2", "3"},
    {"", "R6", "R6", "", "R6", "R6", "", "", ""},
    {"S5", "", "", "S4", "", "", "", "9", "3"},
    {"S5", "", "", "S4", "", "", "", "", "10"},
    {"", "S6", "", "", "S11", "", "", "", ""},
    {"", "R1", "S7", "", "R1", "R1", "", "", ""},
    {"", "R3", "R5", "", "R3", "R3", "", "", ""},
    {"", "R5", "R5", "", "R5", "R5", "", "", ""},  //maybe I should use a map for this instead of 2d array 
};

int variablesToColNumber(const string& var) {
    if (var == "id") {
        return 0;
    } else if (var == "+") {
        return 1;  
    } else if (var == "*") {
        return 2;  
    } else if (var == "(") {
        return 3;  
    } else if (var == ")") {
        return 4;  
    } else if (var == "$") {
        return 5;  
    } else if (var == "E") {
        return 6;  
    } else if (var == "T") {
        return 7;  
    } else if (var == "F") {
        return 8;  
    } else {
        return 404; //ERROR
    }
}
void PrintStack(stack<string> st) {
    cout << "Stack content:" << endl;
    while (!st.empty()) {
        cout << st.top() << endl;
        st.pop();
    }
}

bool parseInput(const string& input) {
  stack<string> parsingStack;
  parsingStack.push("$"); // Push the end marker
  parsingStack.push("0"); // Push initial state
  int inputCounter = 0; //this is to keep track of input counter 
  
  for (int initialState = 0;initialState < input.length(); initialState++) {

    if (input[initialState] == 'i') { //handle id here
      string action = parsingTable[input[initialState]][variablesToColNumber(input.substr(initialState, 2))]; //initialState needs to be top of the stack instead. Looking for a fix.
      parsingStack.push(action);
      initialState++;
    }
      else {
        string action = parsingTable[stoi(parsingStack.top())][variablesToColNumber(input.substr(initialState,1))];
        parsingStack.push(action);
      } 
}
  PrintStack(parsingStack);
  return false;
}

  int main() {
    string input1 = "(id";
    parseInput(input1);
    return 0;
  }