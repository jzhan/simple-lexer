#include <iostream>
#include <cstring>

enum TokenID {INT = 1, FLOAT, ID, PLUS, MIN, MUL, DIV, ASSIGN, LPAREN, RPAREN, ILLEGAL};

struct Token {
  TokenID type;

  union Info {
    char ilchr;
    char op[3];
    char id[27];
    int int_num;
    float float_num;
  } info;
};

class Lexer {
  private:
    int current_position;
    int len;
    char *str;

  public:
    struct Token current_token;

    Lexer(char *param_str) {
      str = param_str;
      
      len = strlen(str);
      current_position = 0;
    }

    bool isDigit(char chr) {
      return (chr >= '0' and chr <= '9');
    }

    bool isIdentifier(char chr) {
      return ((chr >= 'a' and chr <= 'z') or 
              (chr >= 'A' and chr <= 'Z') or 
              chr == '_');
    }

    bool getNextToken() {
      while(current_position < len and str[current_position] == ' ')
        current_position = current_position + 1;

      if(current_position == len) 
        return false;
      
      if(isDigit(str[current_position])) {
        int num = 0;

        while(current_position < len and isDigit(str[current_position])) {
          num = num * 10 + (str[current_position] - '0');

          current_position = current_position + 1;
        }

        if(current_position < len and str[current_position] == '.') {
          current_position = current_position + 1;
          float fnum = num;
          float divider = 10.f;

          while(current_position < len and isDigit(str[current_position])) {
            fnum = fnum + (str[current_position] - '0') / divider;

            divider = divider * 10;
            current_position = current_position + 1;
          }

          current_token.type = FLOAT;
          current_token.info.float_num = fnum;
        } else {
          current_token.type = INT;
          current_token.info.int_num = num;
        }  
      } else if(isIdentifier(str[current_position])) {
        char id[27];
        int i = 0;

        while(current_position < len and isIdentifier(str[current_position])) {
          if(i < 26) {
            id[i] = str[current_position];
            i = i + 1;
          }

          current_position = current_position + 1;
        }

        id[i] = 0;

        current_token.type = ID;
        strcpy(current_token.info.id, id);
      } else if(str[current_position] == '+') {
        current_token.type = PLUS;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == '-') {
        current_token.type = MIN;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == '*') {
        current_token.type = MUL;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == '/') {
        current_token.type = DIV;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == '=') {
        current_token.type = ASSIGN;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == '(') {
        current_token.type = LPAREN;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else if(str[current_position] == ')') {
        current_token.type = RPAREN;
        current_token.info.op[0] = str[current_position];
        current_token.info.op[1] = 0;

        current_position = current_position + 1;
      } else {
        current_token.type = ILLEGAL;
        current_token.info.ilchr = str[current_position];

        current_position = current_position + 1;
      }

      return true;
    }
};

int main() {
  char str[200];
  
  gets(str);

  Lexer lexer(str);

  while(lexer.getNextToken()) {
    switch(lexer.current_token.type) {
      case LPAREN:
        std::cout << "[" << lexer.current_token.info.op << ": LPAREN]";
        break;
      case RPAREN:
        std::cout << "[" << lexer.current_token.info.op << ": RPAREN]";
        break;
      case ASSIGN:
        std::cout << "[" << lexer.current_token.info.id << ": ASSIGN]";
        break;
      case ID:
        std::cout << "[" << lexer.current_token.info.id << ": ID]";
        break;
      case INT:
        std::cout << "[" << lexer.current_token.info.int_num << ": INT]";
        break;
      case FLOAT:
        std::cout << "[" << lexer.current_token.info.float_num << ": FLOAT]";
        break;
      case PLUS:
        std::cout << "[" << lexer.current_token.info.op << ": PLUS]";
        break;
      case MIN:
        std::cout << "[" << lexer.current_token.info.op << ": MIN]";
        break;
      case MUL:
        std::cout << "[" << lexer.current_token.info.op << ": MUL]";
        break;
      case DIV:
        std::cout << "[" << lexer.current_token.info.op << ": DIV]";
        break;
      case ILLEGAL:
        std::cout << "[" << lexer.current_token.info.ilchr << ": ILLEGAL]";
        break;
    }

    std::cout << " ";
  }
    
  return 0;
}
