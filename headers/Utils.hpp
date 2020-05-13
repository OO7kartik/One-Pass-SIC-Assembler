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
  /*
    :param line: line to strip spaces from
    :functionality: replaces all continous spaces with a single space
    :return: void, modifies line through reference
  */
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

string toHex(int s) {
  stringstream ss;
  ss << hex << s;
  string hexString = ss.str();
  for(int i=0; i<hexString.length(); i++) hexString[i] = toupper(hexString[i]);
  return hexString;
}

int toDec(string s) {
  stringstream ss;
  int dec;
  ss << s;
  ss >> hex >> dec;
  return dec;
}

int lengthOfConst(const string &character_const) {
  int div_factor = (character_const[0] == 'C') ? 1 : 2;

  return (character_const.size()-3) / div_factor;
}

int lengthOfTextRecord(const string &text_record) {
  int count = 0;
  for(int i = 1; i < text_record.size(); i++) {
    if(text_record[i] != '^') {
      count++;
    }
  }
  return count;
}

bool canAccomodate(const string &current_record, int length) {
  if(lengthOfTextRecord(current_record) + length > 30) {
    return false;
  }
  return true;
}

string getEntitiesOfConst(const string& operand, int &length) {
  length = lengthOfConst(operand);

  string to_ret = "";
  if(operand[0] == 'X') {
    to_ret = operand.substr(2, operand.size()-3);
  }
  else {
    for(int i = 2; i < operand.size()-1; i++) {
      int ascii_val = operand[i];
      string object_code = toHex(ascii_val);

      to_ret += (string(2-object_code.size(), '0') + object_code);
    }
  }

  return to_ret;
}

string padWithZeroes(const string& s, int length) {
  int lengthToPad = max(0UL, length - s.length());
  return string(lengthToPad, '0') + s;
}

bool nonIndexify(string& operand) {
  int length = operand.length();
  if (length>=3 && operand.substr(length-2, 2) == ",X") {
    operand = operand.substr(0, length-2);
    return true;
  }
  return false;
}