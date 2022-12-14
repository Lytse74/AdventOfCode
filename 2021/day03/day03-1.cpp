#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
using namespace std;


int main() {
  // open the file
  ifstream is("day03.input");
   
  // read the bit_string from the file
  string bit_string = "";

  // a priori 12 bits
  const int nofb = 12;

  // array of 12 ints
  int bit_count[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
  int samples = 0;

  while ( is >> bit_string )
  {
    //cout << bit_string << endl;
    bitset<nofb> bits(bit_string);

    for (size_t i=0; i<bits.size(); ++i)
    {
      bit_count[i] += (bits.test(i) ? 1 : -1);
    }

    samples++;
    //cout << bits << endl;
  }


  // result

  bitset<nofb> gamma;
  bitset<nofb> epsilon;

  for (size_t i=0; i<nofb; ++i)
  {
    if ( bit_count[i]>0 )
      gamma.set(i);

    if ( bit_count[i]<0 && bit_count[i] > -samples )
      epsilon.set(i);


    //cout << "bit_count[" << i << "]=" << bit_count[i] << endl;
  }

  cout << gamma.to_ulong() << endl;
  cout << epsilon.to_ulong() << endl;

  cout << "mulitply=" << gamma.to_ulong()*epsilon.to_ulong() << endl;

  //close the file
  is.close();
}
