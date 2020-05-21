class Symtab {
private:
  map<string, vector<string>> table;
public:
  Symtab();
  int insert(string label, string adr, bool force);
  int check(string label);
  string address(string label);
  vector<string> getLinkedList(string label);
  void errorCheck(string file_name);
  void print();
}; 

Symtab::Symtab() {
  table = map<string, vector<string>>();
}

/*
returns 
  0: symbol not in symtab
  1: symbol already exist
*/
int Symtab::check(string label) {
  if(table.find(label) != table.end()) {
    return 1;
  }
  return 0;
}


int Symtab::insert(string label, string adr = NOT_FOUND, bool force = false) {
  int situation = check(label);

  if(force) {
    table[label] = {adr};
  }
  else if(situation == 1 && table[label][0] != NOT_FOUND) {
    cerr << "symbol already present in symtab" << endl;
    return 0;
  }
  else {
    table[label].push_back(adr);
  }
  // print();
  // cerr << "-------" << endl;
  return 1;
}


string Symtab::address(string label) {
  int situation = check(label);

  if(situation == 0) {
    table[label].push_back(NOT_FOUND);
  }

  return table[label][0];
}


vector<string> Symtab::getLinkedList(string label) {
  return table[label];
}


void Symtab::print() {
  for(pair<string, vector<string>> itr : table) {
    cerr << itr.first << ": ";
    for(string s : itr.second) {
      cerr << " - " << s << " ";
    }
    cerr << endl;
  }
}

void Symtab::errorCheck(string file_name) {
  for(auto itr : table) {
    if(itr.second.size() && itr.second[0] == NOT_FOUND) {
      outputError(file_name);
      break;
    }
  }
}