/*
  CONSTANTS
*/
const string NOT_FOUND    = "***";
const string START        = "START";
const string END          =  "END"; 
const string EMPTY_STRING = "";
const string WORD         = "WORD";
const string RESW         = "RESW";
const string RESB         = "RESB";
const string BYTE         = "BYTE";


/*
  Utility functions
*/
void removeExtraSpaces(string& line) {
  string result = "";
  char prev = '*';
  for(int i = 0; i < line.size(); i++) {
    if(line[i] == ' ' && line[i] == prev) {
      continue;
    }
    prev = line[i];
    result += line[i];
  }
  line = result;
}

string to_hex(int s) {
  stringstream ss;
  ss << hex << s;
  return ss.str();
}