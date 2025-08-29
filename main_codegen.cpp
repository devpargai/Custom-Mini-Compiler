#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "icg.h"
#include "optimizer.h"
#include "codegen.h"
#include <iostream>
#include <vector>
#include <algorithm>  // required for std::begin and std::end

using namespace std;

int main() {
 cout << "Enter your source code (end with # on a new line):\n";
    string line, code;
    while (getline(cin, line)) {
        if (line == "#") break;
        code += line + "\n";
    }

    vector<Token> tokens = tokenize(code);
    cout << "\n--- Tokens ---\n";
    printTokens(tokens);

    Parser parser(tokens);
    ParseNode* root = parser.parse();

    if (!root) {
        cout << "\n--- Syntax Error ---\n";
        cout << "Parsing failed. Stopping compilation.\n";
        return 1;
    }

    cout << "\n--- Parse Tree ---\n";
    parser.printParseTree(root);

    SemanticAnalyzer sema;
    sema.analyze(root);
    sema.printErrors();

    if (sema.hasErrors()) {
        cout << "\nCompilation stopped due to semantic errors.\n";
        return 1;
    }

    // ICG
    IntermediateCodeGenerator icg;
    icg.generate(root);

    cout << "\n--- Intermediate Code ---\n";
    icg.printInstructions();  // ✅ correct method

    // Optimization
    Optimizer optimizer;
    vector<Instruction> optimized = optimizer.optimize(icg.getICG());  // ✅ correct type

    cout << "\n--- Optimized Code ---\n";
    for (const auto& instr : optimized) {
        if (instr.op == "label") {
            cout << instr.result << ":\n";
        } else if (instr.op == "goto") {
            cout << "goto " << instr.result << "\n";
        } else if (instr.op == "ifFalse") {
            cout << "ifFalse " << instr.arg1 << " goto " << instr.result << "\n";
        } else if (instr.op == "call") {
            cout << "call " << instr.result << "\n";
        } else if (instr.op == "return") {
            cout << "return " << instr.arg1 << "\n";
        } else if (instr.op == "=") {
            cout << instr.result << " = " << instr.arg1 << "\n";
        } else if (instr.op == "param") {
            cout << "param " << instr.arg1 << "\n";
        } else if (instr.op == "print") {
            cout << "print " << instr.arg1 << "\n";
        } else {
            cout << instr.result << " = " << instr.arg1 << " " << instr.op << " " << instr.arg2 << "\n";
        }
    }

    // Assembly generation

    cout << "\n--- Code Generation ---\n";
    CodeGenerator codegen;
    codegen.generateAssembly(optimized);  // ✅ correct type

    return 0;
}
