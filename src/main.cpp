#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include "avltree.h"

using namespace std;

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

int main(){
    AVLTree tree;

    //Insert at beginning, unlimited amount of characters within quotes, and the 8-digit ID at the end.
    regex insertCommand = regex("^insert \"([A-Z]?[a-z]* *)*\" \\d{8}$");
    //Remove at the beginning of the input, followed by a space and 8-digit ID number.
    regex removeCommand = regex("^remove \\d{8}$");
    //"search" followed by a space and 8 digits.
    regex searchIDCommand = regex("^search \\d{8}$");
    //"search" followed by a name with only letters/spaces enclosed in "".
    regex searchNameCommand = regex("^search \"([A-Z]?[a-z]* *)*\"$");
    regex printInorderCommand = regex("^printInorder$"); //Only item in string.
    regex printPreorderCommand = regex("^printPreorder$"); //Only item in string.
    regex printPostorderCommand = regex("^printPostorder$"); //Only item in string.
    regex printLevelCountCommand = regex("^printLevelCount$"); //Only item in string.
    //"removeInorder" followed by a space and at least one digit.
    regex removeInorderCommand = regex("^removeInorder \\d+$");

    string inputLine;
    // Parsing Number of Commands
    getline(cin, inputLine);
    int numOfCommands = stoi(inputLine);
    while (numOfCommands != 0) {
        getline(cin, inputLine);
        if (regex_match(inputLine, insertCommand)) {
            //Parsing input text
            string subString = inputLine.substr(8);
            int endOfName = subString.find('"');
            tree.insert(inputLine.substr(8, endOfName), stoi(inputLine.substr(endOfName+10, 8)));
        }
        else if (regex_match(inputLine, removeCommand)) {
            //Parsing input text
            string subString = inputLine.substr(7);
            int idToRemove = stoi(subString);
            tree.remove(idToRemove);
        }
        else if (regex_match(inputLine, searchIDCommand)) {
            //Parsing input text
            string subString = inputLine.substr(7);
            int idToSearch = stoi(subString);
            tree.searchID(idToSearch);
        }
        else if (regex_match(inputLine, searchNameCommand)) {
            //Parsing input text
            string subString = inputLine.substr(8);
            int endOfName = subString.find('"');
            tree.searchName(inputLine.substr(8, endOfName));
        }
        else if (regex_match(inputLine, printInorderCommand)) {
            //Parsing input text
            vector<int> IDS; // Vector present for unit testing and debugging
            tree.inOrder(IDS);
        }
        else if (regex_match(inputLine, printPreorderCommand)) {
            //Parsing input text
            vector<int> IDS; // Vector present for unit testing and debugging
            tree.preOrder(IDS);
        }
        else if (regex_match(inputLine, printPostorderCommand)) {
            //Parsing input text
            tree.postOrder();
        }
        else if (regex_match(inputLine, printLevelCountCommand)) {
            //Parsing input text
            tree.printLevelCount();
        }
        else if (regex_match(inputLine, removeInorderCommand)) {
            //Parsing input text
            string subString = inputLine.substr(14);
            int indexToRemove = stoi(subString);
            tree.removeInorder(indexToRemove);
        }
        else {
            // For when the input matches none of the regular expressions.
            cout << "unsuccessful" << endl;
        }
        numOfCommands--;
    }
    return 0;
}
