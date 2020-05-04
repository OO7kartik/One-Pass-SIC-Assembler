class Symtab {
private:
  map<string, vector<string>> table;
public:
  Symtab();
  int insert(string label, string adr);
  int check(string label);
  string address(string label);
}; 

Symtab::Symtab() {
  table = map<string, vector<string>>();
}

/*
returns 
  0: symbol already exist
  1: symbol not found
  2: symbol encountered, address NOTFOUND
*/
int Symtab::check(string label) {
  if(table.find(label) == table.end()) { //not found
    return 1;
  }
  else if(table[label][0] == NOTFOUND) {
    return 2;
  }
  return 0;
}

int Symtab::insert(string label, string adr) {
  int situation = check(label);

  if(situation == 0) {
    return 0;
  }
  else if(situation == 1) {
    table[label].push_back(adr);
  }
  else {
    //nothing for now
  }

  return 0;
}

//TODO
string Symtab::address(string label) {
  int situation = check(label);

  return "";
}