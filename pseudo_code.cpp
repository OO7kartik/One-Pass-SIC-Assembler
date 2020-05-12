#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long int addr;

int main()
{
    bool isNotComment(const string &line);
    bool isNotEmpty(const string &str);

    string line, OPCODE, OPERAND, LABEL;
    addr START = 0, LOCCTR = 0;
    map<string, string> OPTAB;
    map<string, vector<string>> SYMTAB;

    cin >> line;
    // LABEL, OPCODE, OPERAND = parse(line); ?

    if (OPCODE == "START")
    {
        START = stoi(OPERAND);
        LOCCTR = START;

        cin >> line;
        // LABEL, OPCODE, OPERAND = parse(line); ?
    }

    while (OPCODE != "END")
    {
        if (isNotComment(line))
        {
            if(isNotEmpty(LABEL))  // if there is symbol in label field
            {
                vector<string> foundSymbolList = SYMTAB[LABEL]; // search SYMTAB for LABEL
                                                                // ## NOTE return value as per implementation

                if(!foundSymbolList.empty()) // if found (entry exists)
                {
                    if(foundSymbolList[0]=="NULL") // if symbol value is NULL
                    {
                        // END PREV RECORD IF INCOMPLETE ?

                        foundSymbolList[0] = LOCCTR;
                        for (int i = 1; i < foundSymbolList.size(); i++) // traverse list
                        {
                            // WRITE NEW TEXT RECORD ?
                        }
                        // Update SYMTAB ?
                    }
                    else
                    {
                        SYMTAB[LABEL] = vector<string>({to_string(LOCCTR)}); // insert (LABEL, LOCCTR) into SYMTAB
                    }
                }
            }

            string code = OPTAB[OPCODE]; // search OPTAB for OPCODE
            if (isNotEmpty(code)) // if found (OPCODE)
            {
                vector<string> foundSymbolList = SYMTAB[OPERAND]; // search SYMTAB for OPERAND address

                if(!foundSymbolList.empty()) // if found (entry exists)
                {
                    if(foundSymbolList[0]!="NULL") // if symbol value is not NULL
                    {
                        // store symbol value as OPERAND address ?
                    }
                    else
                    {
                        foundSymbolList.push_back(to_string(LOCCTR)); // insert LOCCTR at end of LL
                    }
                }
                else
                {
                    SYMTAB[LABEL] = vector<string>({"NULL"}); // insert (LABEL, null) into SYMTAB
                }
                LOCCTR += 3;
                
            }
            else if (OPCODE=="WORD")
            {
                LOCCTR += 3;
                // convert OPERAND(in decimal [string]) to obj code ? E.g. 4096 => 001000 (hex of 4,096)
            }
            else if (OPCODE=="RESW")
            {
                LOCCTR += ( 3 * stoi(OPERAND) );
            }
            else if (OPCODE=="RESB")
            {
                LOCCTR +=  stoi(OPERAND);
            }
            else if (OPCODE=="BYTE")
            {
                // find length of constant (could be hex[ X'...' ] or char[ C'...' ])
                // add length to LOCCTR
                // convert constant to object code 
            }
            
            if(/* object code will not fit in current text record ?*/ 1)
            {
                // Write current text record to object program (file) ?
                // init new text record ?
            }
            
            // Add object code to text record ?
        }

        // write last text record ?
        // write end record ?
        // write last listing line ????
    }
}