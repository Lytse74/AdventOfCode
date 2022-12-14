#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  // open the file
  ifstream is("day10.input");
  string str;

  int regx = 1;
  int pc = 1;
  int val = 0;
  
  while ( getline ( is , str ) )
  {
    istringstream iss(str);
    string str2;
    int op;

    iss >> str2;

    if ( str2.compare("noop") == 0 )
    {
      if ( (pc-1)%40 >= regx-1 && (pc-1)%40 <= regx+1 )
        cout << "#";
      else
        cout << ".";

      if ( ( (pc -20) % 40 ) == 0 )
      {
        val += ( pc * regx );
        //cout << pc << " " << regx << endl;
      }
      if ( ( pc % 40 ) == 0 )
        cout << endl;
      pc++;
    }
    if ( str2.compare("addx") == 0 )
    {
      iss >> op;
      if ( (pc-1)%40 >= regx-1 && (pc-1)%40 <= regx+1 )
        cout << "#";
      else
        cout << ".";
        
      if ( ( (pc -20) % 40 ) == 0 )
      {
        val += ( pc * regx );
        //cout << pc << " " << regx << endl;
      }
      if ( ( pc % 40 ) == 0 )
        cout << endl;
      pc++;
      if ( (pc-1)%40 >= regx-1 && (pc-1)%40 <= regx+1 )
        cout << "#";
      else
        cout << ".";
        
      if ( ( (pc -20) % 40 ) == 0 )
      {
        val += ( pc * regx );
        //cout << pc << " " << regx << endl;
      }
      if ( ( pc % 40 ) == 0 )
        cout << endl;
      pc++;
      regx += op;
      //cout << "pc:" << pc << " op:" << op << " regx:" << regx << endl;
    }

  }

  cout << "P1 val: " << val << endl;

  //close the file
  is.close();
 }
