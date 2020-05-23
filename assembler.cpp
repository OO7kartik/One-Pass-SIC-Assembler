#include <bits/stdc++.h>
using namespace std;

#include "headers/Utils.hpp"
#include "headers/parser.hpp"
#include "headers/Optab.hpp"
#include "headers/Symtab.hpp"


int main(int argc, char **argv) {

  int locctr = 0, prev_locctr = 0, firstExec;
  bool isIndexed, force_new = false, firstExecSet = false;
  string label, opcode, operand, objcode, symbolval;
  vector<string> object_program; //int: counts number of '^', string contains records

  string inputFilename, outputFilename;

  // Check if arguments are valid and sufficient
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
      return -1;
    }
    file.close();
  }


  Parser parser(inputFilename);
  Symtab symtab;
  Optab optab;

  parser.getEntities(label, opcode, operand);

  if(opcode == "START") {
    locctr = toDec(operand);
  }
  symtab.insert(START, to_string(locctr));
  object_program.push_back("H^" + padWithSpaces(label, 6) + "^" + padWithZeroes( toHex(stoi(symtab.address(START))),6 ) );
  object_program.push_back("T^" + padWithZeroes(toHex(locctr), 6) + "^00");

  parser.getEntities(label, opcode, operand);
  while(opcode != END) {
    prev_locctr = locctr;
    isIndexed = nonIndexify(operand);
    symbolval = string(4, '0');

    if(label != EMPTY_STRING) {
        // vector<string> foundSymbolList = SYMTAB[LABEL]; // search SYMTAB for LABEL
                                                        // ## NOTE return value as per implementation

        if(symtab.check(label) != 0) // if found (entry exists)
        {
            if(symtab.check(label) == 1) // if symbol value is NULL
            {
                if(opcode == WORD || opcode == RESW || opcode == RESB || opcode == BYTE) {
                  if( symtab.address(label)==NOT_FOUND ) {
                    dataSymbolError(outputFilename, label);
                    cout << "Error: Forward Reference used for Data Symbol: " << label << "\nAborting...\n";
                    return -1;
                  }
                }

                vector<string> list = symtab.getLinkedList(label);

                for (int i = 1; i < list.size(); i++) // traverse list
                {
                    writeTextRecord(object_program, toHex(locctr), toHex(stoi(list[i])), true);
                }
            }
            symtab.insert(label, to_string(locctr), true); // Update SYMTAB
        }
        else 
        {
          symtab.insert(label, to_string(locctr), true);
        }
        objcode = symtab.address(label);
    }

    string code = optab.getCode(opcode); // search OPTAB for OPCODE
    if(code != EMPTY_STRING) {
      if(!firstExecSet) {
        firstExec = locctr;
        firstExecSet = true;
      }
      // vector<string> foundSymbolList = SYMTAB[OPERAND]; // search SYMTAB for OPERAND address

      if(operand!=EMPTY_STRING) {
        if(symtab.check(operand) != 0) // if found (entry exists)
        {
            if(symtab.address(operand) != NOT_FOUND) // if symbol value is not NULL
            {
                symbolval = padWithZeroes(toHex(stoi(symtab.address(operand))), 4); // store symbol value as OPERAND address 
            }
            else
            {
                symtab.insert(operand, to_string(locctr+1), false); // insert LOCCTR at end of LL
            }
        }
        else
        {
            symtab.insert(operand); // insert (LABEL, null) 
            symtab.insert(operand, to_string(locctr+1) );
        }
      }
      locctr+= 3;
      objcode = code + symbolval;
    }
    else if(opcode == WORD) {
      objcode = padWithZeroes(toHex(stoi(operand)), 6);
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
        objcode = getEntitiesOfConst(operand, length); // find length of const, convert const to object code 
        locctr += length;
    } 
    
    if(isIndexed) {
      int value = toDec(objcode);
      value += toDec("8000");
      objcode = toHex(value);
    }

    if(opcode.substr(0, 3) != "RES") {
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

  object_program.push_back("E^" + padWithZeroes(toHex(firstExec), 6));
  object_program[0] += "^" + padWithZeroes(toHex(locctr-stoi(symtab.address(START))), 6);
  
  vectorToFile(object_program, outputFilename);
  symtab.errorCheck(outputFilename);

  return 0;
}