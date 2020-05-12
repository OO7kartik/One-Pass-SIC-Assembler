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
  Optab optab;

  // tried starting some work
  parser.getEntities(label, opcode, operand);
  if(opcode == START) {
    locctr = stoi(operand);
  }
  symtab.insert(START, to_string(locctr));
  object_program.push_back({2, "H^" + opcode + "^00" + symtab.address(START)});

  parser.getEntities(label, opcode, operand);
  while(opcode != END) {
    if(label != EMPTY_STRING) {

        // vector<string> foundSymbolList = SYMTAB[LABEL]; // search SYMTAB for LABEL
                                                        // ## NOTE return value as per implementation

        if(symtab.check(label) != 0) // if found (entry exists)
        {
            if(symtab.check(label) == 1) // if symbol value is NULL
            {
                // END PREV RECORD IF INCOMPLETE ?

                // foundSymbolList[0] = LOCCTR; // set LOCCTR as symbol value ?
                vector<string> list = symtab.getLinkedList(label);

                for (int i = 1; i < list.size(); i++) // traverse list
                {
                    // WRITE NEW TEXT RECORD ?
                }
                // Update SYMTAB ? ========> combined [1]
            }
            else
            {
                // SYMTAB[LABEL] = vector<string>({to_string(LOCCTR)}); // insert (LABEL, LOCCTR) into SYMTAB ========> combined [2]
            }
            symtab.insert(label, to_string(locctr), true); // Update SYMTAB, force[=true] delete linked list if any <========= here [1,2]
        }
    }

    string code = optab.getCode(opcode); // search OPTAB for OPCODE

    if(opcode != EMPTY_STRING) {

      // vector<string> foundSymbolList = SYMTAB[OPERAND]; // search SYMTAB for OPERAND address

      if(symtab.check(label) != 0) // if found (entry exists)
      {
          if(symtab.check(label) != 1) // if symbol value is not NULL
          {
              // store symbol value as OPERAND address ?
          }
          else
          {
              symtab.insert(label, to_string(locctr), false); // insert LOCCTR at end of LL
          }
      }
      else
      {
          symtab.insert(label, to_string(locctr), false); // insert (LABEL, null) into SYMTAB (and also the ref addr)
      }
      locctr+= 3;

    }
    else if(opcode == WORD) {
      locctr += 3;
    }
    else if(opcode == RESW) {
      locctr += (3 * stoi(operand));
    }
    else if(opcode == RESB) {
      locctr += stoi(operand);
    }
    else if(opcode == BYTE) {
        int length;
        string objcode = getEntitiesOfConst(operand, length); // find length of constant (could be hex[ X'...' ] or char[ C'...' ])
                                                      // convert constant to object code 
        locctr += length;
        

    }

    /*

    if("object code will not fit in current text record ? " 1)
    {
        // Write current text record to object program (file) ?
        // init new text record ?
    }
    
    // Add object code to text record ?

    // write last text record ?
    // write end record ?
    // write last listing line ????


    */

    parser.getEntities(label, opcode, operand);
  }
  if(opcode == END) {
    object_program.push_back({1, "E^" + symtab.address(START)});
    //handle when characters are less, ie add padding
    object_program[0].second += "^" + toHex(locctr-stoi(symtab.address(START)));
  }


  
  /* ----------------------BELOW PART FOR TESTING PURPOSE--------------------- */


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