#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "parser.h"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct Symbol {
    string type;
    string name;
};

class SemanticAnalyzer {
    unordered_map<string, Symbol> symbolTable;
    vector<string> errors;
    int loopDepth = 0; // to check if break/continue are valid
    string currentReturnType = "intt"; // assuming mainn returns intt, extend if you have other functions

public:
    void analyze(ParseNode* root);
    void traverse(ParseNode* node);
    string getExprType(ParseNode* node);  // Added: to infer expression type
    void printErrors();
    bool hasErrors() const;

};

#endif
