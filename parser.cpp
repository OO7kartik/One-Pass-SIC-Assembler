#include <bits/stdc++.h>
using namespace std;

#include "headers/Utils.hpp"
#include "headers/Optab.hpp"
#include "headers/Symtab.hpp"

ifstream input;
fstream output;
int locctr = 0, startingAddress = -1;
string label, opcode, operand;
string line;


int getEntities() {
  if(!getline(input, line)) {
    return 0;
  } 
  if(line[0] == '.') {
    return getEntities();
  }
  removeExtraSpaces(line);
  label = opcode = operand = " ";
  
  stringstream ss(line);
  getline(ss, label, ' ');
  getline(ss, opcode, ' ');
  getline(ss, operand, ' ');

  return 1;
}


int main() {
  input.open("Files/input_program.txt", ios::in);
  freopen("Files/debug.txt", "w", stderr);

  //display how program reads lines
  cerr << "-------------INPUT PROGRAM-----------" << endl;
  while(getEntities()) {
    cerr << left
         << setw(7) << label 
         << setw(7) << opcode
         << setw(7) << operand << endl;
  }
  cerr << "-------------------------------------" << endl;

  //display contents of OPTAB
  cerr << "-----------OPTAB---------------" << endl;
  Optab optab = Optab();
  optab.displayOptab();
  cerr << "-------------------------------" << endl;

  input.close();
  return 0;
}