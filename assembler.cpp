#include <bits/stdc++.h>
using namespace std;

#include "headers/Utils.hpp"
#include "headers/parser.hpp"
#include "headers/Optab.hpp"
#include "headers/Symtab.hpp"


int main(int argc, char **argv) {
  freopen("Files/debug.txt", "w", stderr); // debugging purpose
  // freopen("object_program.txt", "w", stdout);

  int locctr = 0, prev_locctr = 0, firstExec;
  bool isIndexed, force_new = false, firstExecSet = false;
  string label, opcode, operand, objcode, symbolval;
  vector<string> object_program; //int: counts number of '^', string contains records

  string inputFilename, outputFilename;

  // Parse args
  if(argc < 3) {
    cout << "FATAL: Too few arguments. Required 2." << endl;
    return 0;
  }
  else {
    if(argc > 3) {
      cout << "WARNING: Too many arguments. Excess args will be ignored." << endl;
    }
    inputFilename = string(argv[1]);
    outputFilename = string(argv[2]);
    
    ifstream file(inputFilename);
    if(!file.good()) {
      cout << "FATAL: Input file does not exist." << endl;
      return 0;
    }
    file.close();
  }


  Parser parser(inputFilename);
  Symtab symtab;
  Optab optab;

  parser.getEntities(label, opcode, operand);

  if(opcode == "START") {
    locctr = toDec(operand);
    // cout << "LOC: " << locctr << endl; 
  }
  symtab.insert(START, to_string(locctr));
  object_program.push_back("H^" + opcode + "^" + padWithZeroes( toHex(stoi(symtab.address(START))),6 ) );
  object_program.push_back("T^" + padWithZeroes(toHex(locctr), 6) + "^00");

  parser.getEntities(label, opcode, operand);
  while(opcode != END) {
    prev_locctr = locctr;
    isIndexed = nonIndexify(operand);
    symbolval = string(4, '0');

    // cout << "\nLabel: " << label << endl;

    if(label != EMPTY_STRING) {
        // vector<string> foundSymbolList = SYMTAB[LABEL]; // search SYMTAB for LABEL
                                                        // ## NOTE return value as per implementation

        if(symtab.check(label) != 0) // if found (entry exists)
        {
            // cout << "Entry exists for " << label << endl;
            if(symtab.check(label) == 1) // if symbol value is NULL
            {
                // cerr << "For " << label << endl;
                symtab.print();
                // cerr << "-------" << endl;
                // cout << "Symbol value is NULL" << endl;

                if(opcode == WORD || opcode == RESW || opcode == RESB || opcode == BYTE) {
                  // cout << "DEF=>Label: " << label << " Check: " << symtab.check(label) 
                  //     << " Address: " << symtab.address(label) << endl;
                  if( symtab.address(label)==NOT_FOUND ) {
                    cout << "Error: Forward Reference used for Data Symbol: " << label << "\nAborting...\n";
                    return 0;
                  }
                }

                // END PREV RECORD IF INCOMPLETE ?

                // foundSymbolList[0] = LOCCTR; // set LOCCTR as symbol value ?
                // symbolval = padWithZeroes(toHex(locctr), 6);
                // cout << "Symbol value is updated to " << symbolval << endl;

                vector<string> list = symtab.getLinkedList(label);

                for (int i = 1; i < list.size(); i++) // traverse list
                {
                    // cout << "Replace " << toHex(stoi(list[i])) << endl;
                    // WRITE NEW TEXT RECORD ?
                    writeTextRecord(object_program, toHex(locctr), toHex(stoi(list[i])), true);
                }
                // Update SYMTAB ?
            }
            // cout << "Symbol value is updated to " << to_string(locctr) << endl;
            symtab.insert(label, to_string(locctr), true); // Update SYMTAB
        }
        else 
        {
          // cout << label << ": Symbol value is updated to " << toHex(locctr) << endl;
          symtab.insert(label, to_string(locctr), true);
        }
        objcode = symtab.address(label);
    }
    // cout << "LOC: " << toHex(locctr) << endl;

    string code = optab.getCode(opcode); // search OPTAB for OPCODE
    // cout << "CODE: " << code << endl;
    if(code != EMPTY_STRING) {
      if(!firstExecSet) {
        firstExec = locctr;
        firstExecSet = true;
      }
      // vector<string> foundSymbolList = SYMTAB[OPERAND]; // search SYMTAB for OPERAND address

      if(operand!=EMPTY_STRING) {
        if(symtab.check(operand) != 0) // if found (entry exists)
        {
            // cout << "Operand label found " << operand << endl;
            if(symtab.address(operand) != NOT_FOUND) // if symbol value is not NULL
            {
                // cout << "OPERAND: " << operand << endl;
                symbolval = padWithZeroes(toHex(stoi(symtab.address(operand))), 4); // store symbol value as OPERAND address 
                // cout << "Symbol value is updated to " << symbolval << endl;
                // cout << "Symbol value is not NULL: " << symbolval << endl;
            }
            else
            {
                symtab.insert(operand, to_string(locctr+1), false); // insert LOCCTR at end of LL
                // symbolval = string(4, '0');
            }
        }
        else
        {
            // cout << "Operand label not found " << operand << endl;
            symtab.insert(operand); // insert (LABEL, null) 
            symtab.insert(operand, to_string(locctr+1) );
            // symtab.print();
            // cerr << "+++" << endl;
            // symbolval = string(4, '0');
        }
      }
      locctr+= 3;
      objcode = code + symbolval;
    }
    else if(opcode == WORD) {
      // convert operand(dec) to object code ? 
      objcode = padWithZeroes(toHex(stoi(operand)), 6);
      locctr += 3;
    }
    else if(opcode == RESW) {
      // cout << "RESW adding " << 3 * stoi(operand) << " to locctr" << endl;
      locctr += (3 * stoi(operand));
    }
    else if(opcode == RESB) {
      // cout << "RESB adding " << stoi(operand) << " to locctr" << endl;
      locctr += stoi(operand);
    }
    else if(opcode == BYTE) {
        int length;
        objcode = getEntitiesOfConst(operand, length); // find length of const, convert const to object code 
        locctr += length;
    } 


    /*

    if("object code will not fit in current text record ? ")
    {
        // Write current text record to object program (file) ?
        // init new text record ?
    }
    
    // Add object code to text record ?

    */

    
    if(isIndexed) {
      int value = toDec(objcode);
      value += toDec("8000");
      objcode = toHex(value);
    }
    // cout << "OBJCODE: " 
    //       << ((opcode.substr(0, 3) == "RES")? "SKIP" : objcode) << endl;

    if(opcode.substr(0, 3) != "RES") {
      // cout << "writing: --- " << objcode << endl;
      if(force_new) {
        object_program.push_back("T^" + padWithZeroes(toHex(prev_locctr), 6) + "^00^" + objcode);
        force_new = false;
      }
      else writeTextRecord(object_program, objcode, toHex(prev_locctr));
    } 
    else {
      force_new = true;
    }

    parser.getEntities(label, opcode, operand);
  }

  // write last text record ?
  // write end record ?
  // write last listing line ????

  // opcode == END at this point
  // object_program.push_back("E^" + padWithZeroes(toHex(stoi(symtab.address(START))), 6));
  object_program.push_back("E^" + padWithZeroes(toHex(firstExec), 6));
  //handle when characters are less, ie add padding
  object_program[0] += "^" + padWithZeroes(toHex(locctr-stoi(symtab.address(START))), 6);
  
  vectorToFile(object_program, outputFilename);
  symtab.errorCheck(outputFilename);

  
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