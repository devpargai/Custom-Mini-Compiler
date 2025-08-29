#ifndef ICG_H
#define ICG_H

#include <string>
#include <vector>
#include "parser.h"   // <-- Include syntax.h for ParseNode
#include "lexer.h" 

using namespace std;

// Structure for intermediate representation instructions
struct Instruction {
    string op;
    string arg1;
    string arg2;
    string result;
};

class IntermediateCodeGenerator {
private:
    int tempCount;   // For generating new temporary variables
    int labelCount;  // For generating unique labels

    // Stack of pairs: (startLabel, endLabel) for loop handling
    vector<pair<string, string>> labelStack;

    // Helper methods
    string newTemp();
    string newLabel();
    string evaluateExpression(ParseNode* node);  // Use ParseNode*

    void traverse(ParseNode* node);  // Recursive traversal of AST

public:
    vector<Instruction> instructions;
    IntermediateCodeGenerator();
    void generate(ParseNode* root);  // Entry point
    void printInstructions();   // Output IR
    vector<Instruction> getICG();     // ✅ Correct type

};

#endif
