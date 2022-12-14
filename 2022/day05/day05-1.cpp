#include <fstream>
#include <iostream>
#include <string>
#include <list>
using namespace std;

int main() {
  // open the file
  ifstream is("day05.input");

  string str;

  // first get the boxes
  const int nrOfStack = 9;

  list<char> myStack[nrOfStack];

  getline( is, str );

  while ( str[1] != '1' )
  {
    cout << str << endl;

    for ( auto i=0; i<(str.length()+1)/4; ++i )
    {
      if ( str[4*i+1] != ' ')
        myStack[i].push_back( str[4*i+1] );
    }
    getline( is, str );
  }

  for ( auto i=0; i<nrOfStack; ++i)
  {
    for ( char& c: myStack[i] )
       cout << c  << ' ';
    cout << endl;
  }

  // Do the shuffling
  int cmd1, cmd2, cmd3;
  while ( is >> str >> cmd1 >> str >> cmd2 >> str >> cmd3 )
  {
    //cout << cmd1 << cmd2 << cmd3 << endl;

    for ( auto i=0; i<cmd1; ++i)
    {
      myStack[cmd3-1].push_front( myStack[cmd2-1].front() );
      myStack[cmd2-1].pop_front();
    }
  }

  for ( auto i=0; i<nrOfStack; ++i)
  {
    for ( char& c: myStack[i] )
       cout << c  << ' ';
    cout << endl;
  }

  for ( auto i=0; i<nrOfStack; ++i)
  {
    cout << myStack[i].front();
  }
  cout << endl;
 
  //close the file
  is.close();
}
