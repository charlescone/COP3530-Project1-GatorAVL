//#include "../src/main.cpp"
//
//#include <stdlib.h>
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//
//
//	To check output (At the Project1 directory):
//		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
//
//
//TEST_CASE("Incorrect Commands", "[flag]") {
//    AVLTree tree;   // Create a Tree object
//    vector<string> actualOutput;
//
//    actualOutput.push_back(tree.validateInsert("insert \"A1bert\" 12345678"));
//    actualOutput.push_back(tree.validateSearchID("search 123"));
//    actualOutput.push_back(tree.validateSearchName("search \"B3N\""));
//    actualOutput.push_back(tree.validateRemove("remove \"Albert\""));
//    actualOutput.push_back(tree.validateRemoveInorder("removeInorder -1"));
//
//
//    vector<string> expectedOutput = {"unsuccessful", "unsuccessful", "unsuccessful", "unsuccessful", "unsuccessful"};
//
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("Edge Cases", "[flag]") {
//    AVLTree tree; // Create a Tree object
//    // Insert three nodes for some edge cases.
//    tree.insert("Albert", 22345678);
//    tree.insert("Alberta", 12345678);
//    tree.insert("Chris", 32345678);
//
//    vector<string> actualOutput;
//    // Checking the return value of searching for a node with an ID that doesn't exist.
//    actualOutput.push_back(tree.validateSearchID("search 11111111"));
//    // Checking the return value of removing a node with an ID that doesn't exist.
//    actualOutput.push_back(tree.validateRemove("remove 11111111"));
//    // Checking the return value of trying to remove the 100th node, when there are only 3 in the tree.
//    actualOutput.push_back(tree.validateRemoveInorder("removeInorder 100"));
//
//    // Expectation
//    vector<string> expectedOutput = {"unsuccessful", "unsuccessful", "unsuccessful"};
//
//    // Assertions
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("All Rotations", "[flags]") {
//    AVLTree tree;
//    // Right-Right Case (Left Rotation)
//    tree.insert("A", 5);
//    tree.insert("B", 8);
//    tree.insert("C", 12);
//    // Left-Left Case (Right Rotation)
//    tree.insert("D", 4);
//    tree.insert("E", 0);
//    // Right-Left Case (Right Left Rotation)
//    tree.insert("F", 14);
//    tree.insert("G", 13);
//    // Left-Right Case (Left Right Rotation)
//    tree.insert("H", 7);
//    tree.insert("I", 6);
//
//    // The expected preOrder traversal
//    vector<int> expectedOutput = {8, 4, 0, 6, 5, 7, 13, 12, 14};
//    vector<int> actualOutput;
//    // The actual preOrder traversal
//    tree.preOrder(actualOutput);
//
//    // Assertions
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("Deletion Cases", "[flag]") {
//    AVLTree tree;
//    // Inserting nodes to create a tree that can facilitate:
//    // No children, One child, and Two children removal.
//    tree.insert("A", 6);
//    tree.insert("B", 2);
//    tree.insert("C", 7);
//    tree.insert("D", 8);
//    tree.insert("E", 5);
//    tree.insert("F", 9);
//
//    tree.remove(5); // No Child case
//    tree.remove(8); // Two Children case
//    tree.remove(7); // One Child case
//
//    vector<int> expectedOutput = {6, 2, 9}; // Expected preOrder traversal
//    vector<int> actualOutput;
//    tree.preOrder(actualOutput); // Actual preOrder traversal
//
//    // Assertions
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(actualOutput == expectedOutput);
//}
//
//TEST_CASE("Large Insertion with Deletion", "[flags]") {
//    // Initialization
//    AVLTree tree;
//    vector<int> expectedOutput, actualOutput;
//
//    // Inserting 100 random nodes into the tree and in the expected output vector.
//    for (int i = 0; i < 100; i++) {
//        int randInput = rand();
//        if (count(expectedOutput.begin(), expectedOutput.end(), randInput) == 0) {
//            expectedOutput.push_back(randInput);
//            tree.insert("Albert", randInput);
//        }
//    }
//    // Sort the expectedOutput vector because removal is done to a sorted tree by default.
//    sort(expectedOutput.begin(), expectedOutput.end());
//    // Ten randomly generated indices.
//    int randInt = 2;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 26;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 15;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 22;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 34;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 40;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 2;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 11;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 57;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//    randInt = 31;
//    tree.removeInorder(randInt);
//    expectedOutput.erase(expectedOutput.begin()+randInt);
//
//
//    // Actual inorder traversal
//    tree.inOrder(actualOutput);
//
//    // Assertions
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE(expectedOutput == actualOutput);
//}