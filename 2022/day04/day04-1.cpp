#include <fstream>
#include <iostream>
#include <bitset>

using namespace std;


int main() {
  // open the file
  ifstream is("day04.input");

  // calculate value
  char c;
  int low1,low2,up1,up2;
  int val=0;
  
  while ( is >> low1 >> c >> up1 >> c >> low2 >> c >> up2 )
  {
    bitset<100> elve1, elve2;

    for ( auto i=low1 ; i<= up1; ++i)
      elve1.set(i);
    for ( auto i=low2 ; i<= up2; ++i)
      elve2.set(i);

    //cout << low1 << low2 << up1 << up2 << endl;
    //cout << elve1 << endl;
    //cout << elve2 << endl;

    if ( ( elve1 & elve2 )  == elve1 || ( elve1 & elve2 ) == elve2 )
    {
      //cout << "OVERLAP" << endl;
      val++;
    }
  }

  cout << "val:" << val << endl;

  //close the file
  is.close();
}
