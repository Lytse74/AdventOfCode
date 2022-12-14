#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main() {
  // open the file
  ifstream is("day03.input");
  
  const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string str1,str2,str3;

  // calculate value
  int val = 0;
  
  while ( is >> str1 >> str2 >> str3 )
  {
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;

    string common;

    // find common characters in str1 and str2
    for(string::iterator it = str1.begin(); it != str1.end(); ++it)
    {
      size_t pos = str2.find( *it );
      if ( pos != string::npos )
        common.push_back( str2[pos] );
    }
 
    cout << common << endl;

    size_t found = str3.find_first_of( common );

    cout << str3[found] << endl;

    size_t pos = alphabet.find( str3[found] );

    cout << pos+1 << endl;

    val += pos + 1;
  }

  cout << "val: " << val << endl;

  //close the file
  is.close();
}
