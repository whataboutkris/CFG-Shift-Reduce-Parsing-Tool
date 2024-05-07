#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
using namespace std;

string parsingTable[12][9] = {
    {"5", "", "", "4", "", "", "1", "2", "3"},
    {"", "6", "", "", "", "ACC", "", "", ""},
    {"", "R2", "7", "", "R2", "R2", "", "", ""},
    {"", "R4", "R4", "", "R4", "R4", "", "", ""},
    {"5", "", "", "4", "", "", "8", "2", "3"},
    {"", "R6", "R6", "", "R6", "R6", "", "", ""},
    {"5", "", "", "4", "", "", "", "9", "3"},
    {"5", "", "", "4", "", "", "", "", "10"},
    {"", "6", "", "", "11", "", "", "", ""},
    {"", "R1", "7", "", "R1", "R1", "", "", ""},
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
void printStack(stack<string> stk) {
    stack<string> tempStack;

    // Reverse the stack by popping elements and pushing them onto a temporary stack
    while (!stk.empty()) {
        tempStack.push(stk.top());
        stk.pop();
    }

    // Print the reversed stack
    while (!tempStack.empty()) {
        cout << tempStack.top();
        tempStack.pop();
    }

    cout << endl;
}


bool parseInput(const string& input) {
  stack<string> parsingStack;
  parsingStack.push("$"); // Push the end marker
  parsingStack.push("0"); // Push initial state
  printStack(parsingStack);

bool parsing{false};
    int inputIterator = 0;
while (!parsingStack.empty()) {
    //for (int initialState = 0;initialState < input.length()+1; initialState++) { //this was my intial loop, but needed to change
    if (parsingStack.top().substr(0, 1) == "R") {   //handle reduce cases here
        string topElement = parsingStack.top(); 
        inputIterator--;
        parsingStack.pop();
        parsingStack.pop();
        printStack(parsingStack);
        if (topElement == "R1") { //Reduce 1 E→E + T
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
            printStack(parsingStack);

        }
        else if (topElement == "R2") { //Reduce 2 E → T
            parsingStack.pop(); // remove 2
            parsingStack.pop(); // remove T
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("E");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][6]); // 6 is E on the table;
            printStack(parsingStack);
        }
        else if (topElement == "R3") { //Reduce 3 T→ T * F
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
            printStack(parsingStack);
        }
        else if (topElement == "R4") { //Reduce 4 T→ F
            parsingStack.pop(); // remove 3
            parsingStack.pop(); //remove F
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("T");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][7]); // 7 is T on the table;
            printStack(parsingStack);
        }
        else if (topElement == "R5") {  //Reduce 5 F→ (E)
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
            printStack(parsingStack);


        }
        else if (topElement == "R6") {  //Reduce 6 F→ id
            parsingStack.pop(); //remove s5
            parsingStack.pop(); //remove id 
            topElement = parsingStack.top(); //get Top element of stack 
            parsingStack.push("F");
            char lastChar = topElement.back(); // Get the last character of the string
            int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
            parsingStack.push(parsingTable[intLastChar][8]); // 8 is F on the table;
            printStack(parsingStack);
        }
    } 

    else if (input[inputIterator] == 'i') { //handle 'id' cases here
        string topElement = parsingStack.top(); // Get the top string of the stack
        //char lastChar = topElement.back(); // Get the last character of the string
        //int intLastChar = lastChar - '0';     // Convert the last character to an integer using black magic
        int intLastChar = stoi(topElement);
        string action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator, 2))]; 
        parsingStack.push("id");
        parsingStack.push(action);
        printStack(parsingStack);

        inputIterator += 2; //so we can get through the 'd' of 'id'
    }
      else if (input[inputIterator] != 'i') {  //if its NOT id, which is '(', ')', '+', '$', '*'
        int intLastChar;
        string action;
        string topElement = parsingStack.top();
        if (parsingStack.top().length() == 3) {
            topElement = "11"; //S11 was giving me problems here 
            intLastChar = stoi(topElement);
            action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator,1))];
            parsingStack.push(input.substr(inputIterator,1));
            parsingStack.push(action);
            printStack(parsingStack);
        }
            else {
                int intLastChar = stoi(topElement);
                action = parsingTable[intLastChar][variablesToColNumber(input.substr(inputIterator,1))];
                parsingStack.push(input.substr(inputIterator,1));
                parsingStack.push(action);
                printStack(parsingStack);
            }
          
        //string topElement = parsingStack.top(); // Get the top string of the stack
        //char lastChar = topElement.back(); // Get the last character of the string          
        //int intLastChar = stoi(topElement);     // Convert the last character to an integer

        if (action == "ACC") {
            parsing = true;
            stack<string> clearedStack;
            parsingStack.swap(clearedStack);
        }
        else if (action == "") {
            parsing = false;
            stack<string> clearedStack;
            parsingStack.swap(clearedStack);
            cout << "ERROR" << endl;
        }


        inputIterator++;
      } 
}

  return parsing;
}

  int main() {
      char choice = 'Y'; // Initialize choice to 'Y' to enter the loop
      while (choice == 'Y' || choice == 'y') {
          std::string input;
          // Ask user for input
          std::cout << "Enter a string (make sure '$' is at the end): ";
          std::cin >> input;
          for (int i = 0; i < 101; i++) { //Whitespace to separate the stacks between inputs
              cout << endl;
          }
          cout << "STACK: " << endl;
          if (parseInput(input)) {
              cout << "String is accepted!" << endl;
          } else {
              cout << "String is not accepted.." << endl;
          }
          std::cout << "Do you want to enter more inputs? (Y/N): ";
          std::cin >> choice;
      }

      std::cout << "Goodbye!" << std::endl;

    return 0;
}