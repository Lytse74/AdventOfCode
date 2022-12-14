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

    char carr[14] = { '*','*','*','*','*','*','*','*','*','*','*','*','*','*' };

    for ( char& c: str)
    {
      cnt++;

      for ( auto i=0; i<13; ++i)
      {
       carr[i] = carr[i+1];
      }
      carr[13] = c;

      bool chk = (carr[0] != '*');
      for ( auto i=0; i<13 && chk ; ++i)
        for ( auto j=i+1; j<14 && chk ; ++j)
        {
          chk = chk && (carr[i] != carr[j]);
        }
      
      if ( chk )
      {
        for ( auto i=0; i<14; ++i)
        {
          cout << "c" << i << ": " << carr[i] << " ";
        }
        cout << endl;
        break;
      }
    }

    cout << "cnt: " << cnt << endl;


  }

  //close the file
  is.close();
}
