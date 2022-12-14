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

  if ( prev > curr && curr != -1 )
  {
    cout << curr << " (decreased)" << endl;
    ret = -1;
  } 

  if ( prev == curr )
  {
    cout << curr << " (no change)" << endl;
  } 

  return ret;
}


int main() {
  // open the file
  ifstream is("day01.input");
   
  // read the first window from the file
  int w1=-1,w2=-1,w3=-1,w4=-1;
  int curr=-1;
  int prev=-1;
  int nrOfInc=0;

  if ( is >> w1 && is>>w2 && is>>w3 )
  {
    // print the first difference
    prev = w1+w2+w3;
    if ( print( prev, curr ) == 1 )
      nrOfInc++;

    while ( is>>w4 )
    {
      curr = w2+w3+w4;

      if ( print( prev, curr ) == 1 )
        nrOfInc++;
      
      prev = curr;
      w1=w2; w2=w3; w3=w4;
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
