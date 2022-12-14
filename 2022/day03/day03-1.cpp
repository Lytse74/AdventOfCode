#include <fstream>
#include <iostream>
#include <string>

using namespace std;


int main() {
  // open the file
  ifstream is("day03.input");
  
  const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string str;

  // calculate value
  int val = 0;
  
  while ( is >> str )
  {
    //cout << str << endl;
    
    string half = str.substr(0, str.length()/2);

    //cout << half << endl;

    size_t found = str.find_first_of( half, str.length()/2 );

    //cout << str[found] << endl;

    size_t pos = alphabet.find( str[found] );

    //cout << pos+1 << endl;

    val += pos + 1;
  }

  cout << "val: " << val << endl;

  //close the file
  is.close();
}
