/*
  CONSTANTS
*/
const string NOTFOUND = "***";


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