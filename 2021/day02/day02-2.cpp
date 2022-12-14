#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main() {
  string fwd = "forward";
  string up = "up";
  string down = "down";

  // open the file
  ifstream is("day02.input");
   
  // read the command from the file
  string cmd = "";
  int op = -1;

  int dist = 0;
  int depth = 0;
  int aim = 0;

  //cout << cmd << "-" << op << "- dist:" << dist << "- depth:" << depth << endl;

  while ( is >> cmd >> op )
  {
    //cout << cmd << "*" <<op << endl;
    if ( cmd.compare(fwd) == 0)
    {
      dist += op;
      depth += (aim*op);
    }

    if ( cmd.compare(up) == 0 )
      aim -= op;

    if ( cmd.compare(down) == 0 )
      aim += op;
    
    if ( depth < 0 || depth > 0x7fffffff )
      cout << "ERROR" << endl;
    //cout << cmd << "-" << op << "- dist:" << dist << "- depth:" << depth << endl;
  }

  cout << "mul=" << depth*dist << endl;
   
  //close the file
  is.close();
}
