class Parser {
private:
  string _line, _label, _operand, _opcode;
  ifstream input;
public:
  Parser(string file_name);
  ~Parser();
  int getEntities(string &label, string& opcode, string& operand);
};

Parser::Parser(string file_name) {
  input.open(file_name, ios::in);
  _line = "";
  _label = "";
  _operand = "";
  _opcode = "";
}

Parser::~Parser() {
  input.close();
}


int Parser::getEntities(string &label, string &opcode, string &operand) {
  if(!getline(input, _line)) {
    return 0;
  } 
  if(_line.find('.') != string::npos || _line == "") {
    return getEntities(label, opcode, operand);
  }
  removeExtraSpaces(_line);
  _label = _opcode = _operand = "";
  
  stringstream ss(_line);
  getline(ss, _label, ' ');
  getline(ss, _opcode, ' ');
  getline(ss, _operand, ' ');

  label = _label;
  opcode = _opcode;
  operand = _operand;

  return 1;
}
