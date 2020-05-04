class Optab {
private:
  map<string, string> code;
public:
  Optab();
  void displayOptab();
};

Optab::Optab() {
  ifstream opfile("Files/optab.txt", ios::in);
  string line, label, opcode;
  while(getline(opfile, line)) {
    removeExtraSpaces(line);
    stringstream ss(line);
    getline(ss, label, ' ');
    getline(ss, opcode, ' ');
    code[label] = opcode;
  }
  opfile.close();
}

void Optab::displayOptab() {
  for(auto itr : code) {
    cerr << itr.first << " " << itr.second << endl;
  }
}