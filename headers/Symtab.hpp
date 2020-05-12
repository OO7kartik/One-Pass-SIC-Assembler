class Symtab {
private:
  map<string, vector<string>> table;
public:
  Symtab();
  int insert(string label, string adr_or_label, bool is_second_param_label);
  int check(string label);
  string address(string label);
  vector<string> getLinkedList(string label);
  void print();
}; 

Symtab::Symtab() {
  table = map<string, vector<string>>();
}

/*
returns 
  0: symbol not in symtab
  1: symbol encountered, address NOT_FOUND
  2: symbol already exist
*/
int Symtab::check(string label) {
  if(table.find(label) != table.end()) {
    if(table[label][0] == NOT_FOUND) {
      return 1;
    }
    return 2;
  }
  return 0;
}

int Symtab::insert(string label, string adr_or_label, bool is_second_param_label = false) {
  int situation = check(label);

  // symbol found in symtab
  if(situation == 2) {
    if(table[label][0] == NOT_FOUND) { // found symbol's address is NOT_FOUND
      if(is_second_param_label) {
        table[label].push_back(adr_or_label); /// add this label as it depends on label's address (fwdref)
      }
      else {
        // solve all forward reference problems for this label
        //TODO
        //handle stuff
        table[label] = {adr_or_label}; // overwrite this list to current address
      }
    }
    else { // found symbol already has an address ERROR
      cerr << "symbol already present in symtab" << endl;
      return 0;
    }
  }
  else { // symbol does not exist, or symbol's address not found.
    table[label].push_back(adr_or_label);
  }

  return 1;
}

string Symtab::address(string label) {
  int situation = check(label);

  if(situation == 0) {
    table[label].push_back(NOT_FOUND);
  }

  return table[label][0];
}


void Symtab::print() {
  for(pair<string, vector<string>> itr : table) {
    cerr << itr.first << ": ";
    for(string s : itr.second) {
      cerr << "-" << s << " ";
    }
    cerr << endl;
  }
}

vector<string> Symtab::getLinkedList(string label) {
  return table[label];
}