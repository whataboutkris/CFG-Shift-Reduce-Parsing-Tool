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
    {"", "R5", "R5", "", "R5", "R5", "", "", ""},  
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

bool parsing{false};
    int inputIterator = 0;
while (!parsingStack.empty()) {
    //for (int initialState = 0;initialState < input.length()+1; initialState++) { //this was my intial loop, but needed to change
    if (parsingStack.top() == "ACC") {
        parsing = true;
        stack<string> clearedStack;
        parsingStack.swap(clearedStack);
    }
    if (parsingStack.top().substr(0, 1) == "R") {   //handle reduces here
        string topElement = parsingStack.top(); 
        inputIterator--;
        parsingStack.pop();
        parsingStack.pop();

        if (topElement == "R1") { //Reduce 1
            parsingStack.pop(); // remove 9
            parsingStack.pop(); // remove T
            parsingStack.pop(); // remove S6
            parsingStack.pop(); // remove +
            parsingStack.pop(); // remove 8 
            parsingStack.pop(); // remove E
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("E");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][6]); // 6 is E on the table;

        }
        else if (topElement == "R2") { //Reduce 2
            parsingStack.pop(); // remove 2
            parsingStack.pop(); // remove T
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("E");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][6]); // 6 is E on the table;
        }
        else if (topElement == "R3") { //Reduce 3
            parsingStack.pop(); // remove 10
            parsingStack.pop(); // remove F
            parsingStack.pop(); // remove S7
            parsingStack.pop(); // remove *
            parsingStack.pop(); // remove 2 
            parsingStack.pop(); // remove T
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("T");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][7]); // 7 is T on the table;
        }
        else if (topElement == "R4") { //Reduce 4
            parsingStack.pop(); // remove 3
            parsingStack.pop(); //remove F
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("T");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][7]); // 7 is T on the table;
        }
        else if (topElement == "R5") {  //Reduce 5
            parsingStack.pop(); // remove S11
            parsingStack.pop(); // remove )
            parsingStack.pop(); // remove 8
            parsingStack.pop(); // remove E
            parsingStack.pop(); // remove S4 
            parsingStack.pop(); // remove (
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("F");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][8]); // 8 is F on the table;


        }
        else if (topElement == "R6") {  //Reduce 6
            parsingStack.pop(); //remove s5
            parsingStack.pop(); //remove id 
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("F");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][8]); // 8 is F on the table;
        }
    } 

    else if (input[inputIterator] == 'i') { //handle id here
        string topElement = parsingStack.top(); // Get the top string of the stack
        char lastChar = topElement.back(); // Get the last character of the string
        int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
        string action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator, 2))]; 
        parsingStack.push("id");
        parsingStack.push(action);

        inputIterator += 2; //so we can get through the 'd' of 'id'
    }
      else if (input[inputIterator] != 'i') {  //if its NOT id 
        int intLastChar;
        string action;
        string topElement = parsingStack.top();
        int test = parsingStack.top().length();
        if (test == 3) {
            topElement = "11";
            intLastChar = stoi(topElement);
            action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator,1))];
            parsingStack.push(input.substr(inputIterator,1));
            parsingStack.push(action);
        }
            else {
                char lastChar = topElement.back();
                int intLastChar = lastChar - '0';
                action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator,1))];
                parsingStack.push(input.substr(inputIterator,1));
                parsingStack.push(action);
            }
        //string topElement = parsingStack.top(); // Get the top string of the stack
        //char lastChar = topElement.back(); // Get the last character of the string          
        //int intLastChar = stoi(topElement);     // Convert the last character to an integer

        if (action == "ACC") {
            parsing = true;
        }


        inputIterator++;
      } 
}


  PrintStack(parsingStack);
  return parsing;
}

  int main() {
    string input1 = "(id+id)*id$";
      if (parseInput(input1)) {
        cout << "Accepted" << endl;
      }
      else {
          cout << "Not Accepted" << endl;
      }
    return 0;

  }