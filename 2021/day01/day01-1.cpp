#include <fstream>
#include<iostream>
using namespace std;


// print function return 1 for increase -1 for decrease 0 otherwise
int print( int prev, int curr )
{
  int ret= 0;

  if ( prev==-1 || curr == -1 )
  {
    cout << prev << " (N/A - no previous measurement)" << endl;
  } 

  if ( prev < curr && curr != -1 )
  {
    cout << curr << " (increased)" << endl;
    ret = 1;
  } 

  if ( prev > curr && curr != -1)
  {
    cout << curr << " (decreased)" << endl;
    ret = -1;
  } 

  if ( prev == curr )
  {
    cout << curr << " (stuck?)" << endl;
  } 

  return ret;
}


int main() {
  // open the file
  ifstream is("day01.test");
   
  // read the first integer from the file
  int curr=-1;
  int prev=-1;
  int nrOfInc=0;

  if ( is >> prev )
  {
    // print the first difference
    if ( print( prev, curr ) == 1 )
      nrOfInc++;

    while ( is >> curr )
    {
      if ( print( prev, curr ) == 1 )
        nrOfInc++;
      prev = curr;
    }
  }
  else
  {
    cout << "Something went wrong!" << endl;
  }

  cout << "Total of " << nrOfInc << " increases!" << endl;
   
  //close the file
  is.close();
}
