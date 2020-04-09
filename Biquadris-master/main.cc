#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "player.h"
#include "normal.h"
#include "decorator.h"
#include "blind.h"
#include "heavy.h"
#include "force.h"
#include "window.h"

using namespace std;



const vector<string> commandlist {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "norandom", "random", "sequence" ,"L", "I", "J", "Z", "S", "O", "T", "restart"};


bool contain(string s, string substring) {
  int l = static_cast<int>(substring.length());
  int m = static_cast<int>(s.length());
  if (m >= l and s.substr(0, l) == substring) {
    return true;
  }
  return false;
}

string autofill(string input) {
  vector<string> possible;
  for (string s : commandlist) {
    if (contain(s, input)) {
      possible.emplace_back(s);
    }
  }
  if (possible.size() == 1) {
    return possible[0];
  }
  else {
    return "";
  }
}


int main(int argc, const char * argv[]) {
  bool graphics = true;
  int seed = 0;
  string p1sequence = "sequence1.txt";
  string p2sequence = "sequence2.txt";
  int p1level = 0;
  int p2level = 0;
  Player * p1 = nullptr;
  Player * p2 = nullptr;



  for (int i = 1; i < argc; ++i) {
    if (static_cast<string>(argv[i]) == "-text") {
      graphics = false;
    }
    if (static_cast<string>(argv[i]) == "-seed") {
      seed = stoi(argv[++i]);
    }
    if (static_cast<string>(argv[i]) == "-scriptfile1") {
      p1sequence = argv[++i];
    }
    if (static_cast<string>(argv[i]) == "-scriptfile2") {
      p2sequence = argv[++i];
    }
    if (static_cast<string>(argv[i]) == "-startlevel") {
      p1level = p2level = stoi(argv[++i]);
    }
  }

  Xwindow *xw = graphics ? new Xwindow(616,732) : nullptr;
  if(xw){
    xw->fillRectangle(309,0,2,732,Xwindow::Black); //line to divide player 1&2
    xw->fillRectangle(0,79,616,4,Xwindow::Black); //line to divide the scoreboard
    xw->fillRectangle(0,589,616,2,Xwindow::Black); //line to divide the next block and board

  }

  p1 = new Normal{ p1level,p1sequence,seed,xw,1};
  p2 = new Normal{ p2level,p2sequence,seed,xw,2};

  bool p1win = false;
  bool p2win = false;
  bool p1SpecialAction = false;
  bool p2SpecialAction = false;
  Player * tempPlayer1 = nullptr;
  Player * tempPlayer2 = nullptr;
  ifstream fin;
  string filename = "";
  fin.open(filename.c_str());
  int i = 1;
  string command = "";
  while (true) {
    // Show next block.
    p1->setNext();

    // Player1's turn.
    cout << "It is player1's turn." << endl;
    i = 1;
    command = "";

    while (command != "drop") {
      vector<string> p1display = p1->print();
      vector<string> p2display = p2->print();
      for (int i = 0; i < 27; ++i) {
        cout << p1display[i] << "     " << p2display[i] << endl;
      }
      cout << "Please enter your command." << endl;
      // Reset command to default.
      i = 1;
      command = "";
      // Command input.
      while (true) {
        // Check if we need to read in from a file for i.
        if (!(fin >> i)) {
          if(fin.eof() || filename == ""){
            cin >> i;
          }
          else{
            i = 1;
            fin.clear();
          }
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          else {
          }
          if (cin.fail()) {
            i = 1;
          }
          cin.clear();
        }
        // Check if we need to read in from a file for command;
        if (!(fin >> command)) {
          fin.clear();
          cin >> command;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        command = autofill(command);
        if (command != "") {
          break;
        }
        cout << "Invalid input." << endl;
      }
      // Classify command.
      if (command == "left") {
        // Check if p1's turn is end.
        if (p1->left(i) == false) {
          command = "drop";
        }
      }
      if (command == "right") {
        if (p1->right(i) == false) {
          command = "drop";
        }
      }
      if (command == "down") {
        if (p1->down(i) == false) {
          command = "drop";
        }
      }
      if (command == "clockwise") {
        if (p1->clockwise(i) == false) {
          command = "drop";
        }
      }
      if (command == "counterclockwise") {
        if (p1->counterclockwise(i) == false) {
          command = "drop";
        }
      }
      if (command == "levelup") {
        int j = i;
        while (j > 0) {
          p1->levelup();
          --j;
        }
      }
      if (command == "leveldown") {
        int j = i;
        while (j > 0) {
          p1->leveldown();
          --j;
        }
      }
      if (command == "norandom") {
        string file = "";
        if (!(fin >> file)) {
          fin.clear();
          cin >> file;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        p1->norandom(file);
      }
      if (command == "random") {
        p1->random();
      }
      if (command == "sequence") {
        if (!(fin >> filename)) {
          fin.clear();
          cin >> filename;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        fin.close();
        fin.open(filename.c_str());
      }
      if (command == "I" or command == "J" or command == "L" or command == "S" or command == "Z" or command == "O" or command == "T") {
        if (p1->changeBlock(command[0]) == false) {
          p2win = true;
          break;
        }
      }
      if (command == "drop") {
        if (p1->drop(p1SpecialAction) == false) {
          // Game is end.
          p1SpecialAction = false;
          p2win = true;
        }
        else {
          // p1 triggers a special action.
          if (p1SpecialAction) {
            cout << "Player1 triggers special actions." << endl;
            cout << "Please choose from \"blind\", \"heavy\" or \"force\"." << endl;
            string s = "";
            while (s != "blind" and s != "heavy" and s != "force") {
              if (!(fin >> s)) {
                fin.clear();
                cin >> s;
                if (cin.eof()){
                  delete p1;
                  delete p2;
                  delete xw;
                  cout << "Goodbye friends, play again :)" << endl;
                  return 0;
                }
                cin.clear();
              }
            }
            cout << "You choose " << s << "." << endl;
            if (s == "blind") {
              p2 = new Blind{ p2, xw };
            }
            else if (s == "heavy") {
              p2 = new Heavy{ p2 };
            }
            else {
              char c = 0;
              while (c != 'I' && c != 'O' && c != 'Z' && c != 'S' && c != 'L' && c != 'J' && c != 'T') {
                cout << "Please enter the block that you want to force." << endl;
                if (!(fin >> c)) {
                  fin.clear();
                  cin >> c;
                  if (cin.eof()){
                    delete p1;
                    delete p2;
                    delete xw;
                    cout << "Goodbye friends, play again :)" << endl;
                    return 0;
                  }
                  cin.clear();
                }
              }
              cout << "The block is " << c << " block." << endl;
              if (p2->changeBlock(c)) {
                p2 = new Force{ p2 };
              }
              else {
                p1win = true;
              }
            }
          }
        }
      }

      if (command == "restart") {
        if (p2SpecialAction) {
          tempPlayer1 = static_cast<Decorator*>(p1)->component;
          static_cast<Decorator*>(p1)->component = nullptr;
          delete p1;
          p1 = tempPlayer1;
          tempPlayer1 = nullptr;
          p2SpecialAction = false;
        }
        p1->restart(p1level);
        p2->restart(p2level);
        p1->setNext();
      }
    }
    // End of p1's turn.
    // Set player1 back to normal.
    if (p2SpecialAction) {
      p1->fixBlindCells();
      tempPlayer1 = static_cast<Decorator*>(p1)->component;
      static_cast<Decorator*>(p1)->component = nullptr;
      delete p1;
      p1 = tempPlayer1;
      tempPlayer1 = nullptr;
      p2SpecialAction = false;
    }

    if (p1win) {
      cout << "Player1 wins!" << endl;
      cout << "Press Y to restart." << endl;
      char r{};
      cin >> r;
      cin.clear();
      if (r == 'Y') {
        p1->restart(p1level);
        p2->restart(p1level);
        p1win = false;
        p2win = false;
        continue;
      }
      break;
    }
    if (p2win) {
      cout << "Player2 wins!" << endl;
      cout << "Press Y to restart." << endl;
      char r{};
      cin >> r;
      if (r == 'Y') {
        p1->restart(p1level);
        p2->restart(p1level);
        p1win = false;
        p2win = false;
        continue;
      }
      break;
    }

    // Show next block.
    p2->setNext();

    cout << "It is player2's turn." << endl;
    i = 1;
    command = "";

    while (command != "drop") {
      vector<string> p1display = p1->print();
      vector<string> p2display = p2->print();
      for (int i = 0; i < 27; ++i) {
        cout << p1display[i] << "     " << p2display[i] << endl;
      }
      cout << "Please enter your command." << endl;
      i = 1;
      command = "";
      // Command input.
      while (true) {
        // Check if we need to read in from a file for i.
        if (!(fin >> i)) {

          if(fin.eof() || filename == ""){
            cin >> i;
          }
          else{
            i = 1;
            fin.clear();
          }
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          if (cin.fail()) {
            i = 1;
          }
          cin.clear();
        }
        // Check if we need to read in from a file for command;
        if (!(fin >> command)) {
          fin.clear();
          cin >> command;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        command = autofill(command);
        if (command != "") {
          break;
        }
        cout << "Invalid input." << endl;
      }
      // Classify command.
      if (command == "left") {
        if (p2->left(i) == false) {
          command = "drop";
        }
      }
      if (command == "right") {
        if (p2->right(i) == false) {
          command = "drop";
        }
      }
      if (command == "down") {
        if (p2->down(i) == false) {
          command = "drop";
        }
      }
      if (command == "clockwise") {
        if (p2->clockwise(i) == false) {
          command = "drop";
        }
      }
      if (command == "counterclockwise") {
        if (p2->counterclockwise(i) == false) {
          command = "drop";
        }
      }
      if (command == "levelup") {
        int j = i;
        while (j > 0) {
          p2->levelup();
          --j;
        }
      }
      if (command == "leveldown") {
        int j = i;
        while (j > 0) {
          p2->leveldown();
          --j;
        }
      }
      if (command == "norandom") {
        string file = "";
        if (!(fin >> file)) {
          fin.clear();
          cin >> file;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        p2->norandom(file);
      }
      if (command == "random") {
        p2->random();
      }
      if (command == "sequence") {
        if (!(fin >> filename)) {
          fin.clear();
          cin >> filename;
          if (cin.eof()){
            delete p1;
            delete p2;
            delete xw;
            cout << "Goodbye friends, play again :)" << endl;
            return 0;
          }
          cin.clear();
        }
        fin.close();
        fin.open(filename.c_str());
      }
      if (command == "I" or command == "J" or command == "L" or command == "S" or command == "Z" or command == "O" or command == "T") {
        if (p2->changeBlock(command[0]) == false) {
          p1win = true;
          break;
        }
      }
      if (command == "drop") {
        if (p2->drop(p2SpecialAction) == false) {
          // Game is end.
          p2SpecialAction = false;
          p1win = true;
        }
        else {
          // p2 triggers a special action.
          if (p2SpecialAction) {
            cout << "Player2 triggers special actions." << endl;
            cout << "Please choose from \"blind\", \"heavy\" or \"force\"." << endl;
            string s = "";
            while (s != "blind" and s != "heavy" and s != "force") {
              if (!(fin >> s)) {
                fin.clear();
                cin >> s;
                if (cin.eof()){
                  delete p1;
                  delete p2;
                  delete xw;
                  cout << "Goodbye friends, play again :)" << endl;
                  return 0;
                }
                cin.clear();
              }
            }
            cout << "You choose " << s << "." << endl;
            if (s == "blind") {
              p1 = new Blind{ p1, xw };
            }
            else if (s == "heavy") {
              p1 = new Heavy{ p1 };
            }
            else {
              char c = 0;
              while (c != 'I' && c != 'O' && c != 'Z' && c != 'S' && c != 'L' && c != 'J' && c != 'T') {
                cout << "Please enter the block that you want to force." << endl;
                if (!(fin >> c)) {
                  fin.clear();
                  cin >> c;
                  if (cin.eof()){
                    delete p1;
                    delete p2;
                    delete xw;
                    cout << "Goodbye friends, play again :)" << endl;
                    return 0;
                  }
                  cin.clear();
                }
              }
              cout << "The block is " << c << " block." << endl;
              if (p1->changeBlock(c)) {
                p1 = new Force{ p1 };
              }
              else {
                p2win = true;
              }
            }
          }
        }
      }
      if (command == "restart") {
        if (p1SpecialAction) {
          tempPlayer2 = static_cast<Decorator*>(p2)->component;
          static_cast<Decorator*>(p2)->component = nullptr;
          delete p2;
          p2 = tempPlayer2;
          tempPlayer2 = nullptr;
          p1SpecialAction = false;
        }
        p1->restart(p1level);
        p2->restart(p2level);
        p2->setNext();
      }
    }
    command = "";
    // End of p2's turn.

    // Set player2 back to normal.
    if (p1SpecialAction){
      p2->fixBlindCells();
      tempPlayer2 = static_cast<Decorator*>(p2)->component;
      static_cast<Decorator*>(p2)->component = nullptr;
      delete p2;
      p2 = tempPlayer2;
      tempPlayer2 = nullptr;
      p1SpecialAction = false;
    }

    if (p1win) {
      cout << "Player1 wins!" << endl;
      cout << "Press Y to restart." << endl;
      char r{};
      cin >> r;
      cin.clear();
      if (r == 'Y') {
        p1->restart(p1level);
        p2->restart(p1level);
        p1win = false;
        p2win = false;
        continue;
      }
      break;
    }
    if (p2win) {
      cout << "Player2 wins!" << endl;
      cout << "Press Y to restart." << endl;
      char r{};
      cin >> r;
      cin.clear();
      if (r == 'Y') {
        p1->restart(p1level);
        p2->restart(p1level);
        p1win = false;
        p2win = false;
        continue;
      }
      break;
    }
  }
  fin.close();
  delete p1;
  delete p2;
  delete xw;
}

