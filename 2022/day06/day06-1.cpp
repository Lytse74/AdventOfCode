#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main() {
  // open the file
  ifstream is("day06.input");

  string str;

  while ( is >> str )
  {
    cout << str << endl;

    int cnt=0;

    char c1='*',c2='*',c3='*',c4='*';

    for ( char& c: str)
    {
      cnt++;
      c1=c2; c2=c3; c3=c4; c4=c;

      if ( c1 != c2 && c1 != c3 && c1 != c4
        && c2 != c3 && c2 != c4 
        && c3 != c4 
        && c1 != '*')
      {
        cout << "c1:" << c1 << "c2:" << c2 << "c3:" << c3 << "c4:" << c4 << endl;
        break;
      }
    }

    cout << "cnt: " << cnt << endl;


  }

  //close the file
  is.close();
}
