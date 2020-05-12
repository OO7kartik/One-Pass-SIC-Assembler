#include <bits/stdc++.h>
using namespace std;

#include "headers/Utils.hpp"
#include "headers/parser.hpp"
#include "headers/Optab.hpp"
#include "headers/Symtab.hpp"


int main() {
  freopen("Files/debug.txt", "w", stderr); // debugin purpose
  freopen("object_program.txt", "w", stdout);

  int locctr = 0;
  string label, opcode, operand;
  vector<pair<int,string>> object_program; //int: counts number of '^', string contains records

  Parser parser("Files/input_program.txt");
  Symtab symtab;


  // // tried starting some work
  // parser.getEntities(label, opcode, operand);
  // if(opcode == START) {
  //   locctr = stoi(operand);
  // }
  // symtab.insert(START, to_string(locctr));
  // object_program.push_back({2, "H^" + opcode + "^00" + symtab.address(START)});

  // parser.getEntities(label, opcode, operand);
  // while(opcode != END) {
  //   if(label != EMPTY_STRING) {

  //   }
  //   else if(opcode != EMPTY_STRING) {

  //   }

  //   locctr += 3;
  //   parser.getEntities(label, opcode, operand);
  // }
  // if(opcode == END) {
  //   object_program.push_back({1, "E^" + symtab.address(START)});
  //   //handle when characters are less, ie add padding
  //   object_program[0].second += "^" + to_hex(locctr-stoi(symtab.address(START)));
  // }


  /* ----------------display how program reads lines--------------------------- */

  // cerr << "-------------INPUT PROGRAM-----------" << endl;
  // while(parser.getEntities(label, opcode, operand)) {
  //   cerr << left
  //        << setw(7) << label 
  //        << setw(7) << opcode
  //        << setw(7) << operand << endl;
  // }
  // cerr << "-------------------------------------" << endl;

  /* ------------------display contents of OPTAB-------------*/
  // cerr << "-----------OPTAB---------------" << endl;
  // Optab optab = Optab();
  // optab.displayOptab();
  // cerr << "-------------------------------" << endl;

  // //testing symtab
  // Symtab symtab;
  // symtab.insert("a", "0");
  // symtab.insert("b", "3");
  // symtab.insert("c", "6");

  // symtab.print();

  // cout << (symtab.address("a")) << endl;
  // cout << (symtab.address("z")) << endl;
  // if(symtab.address("z") == NOT_FOUND) {
  //   cerr << "not" << endl;
  //   symtab.insert("z", "x");
  // }

  // symtab.print();

  return 0;
}