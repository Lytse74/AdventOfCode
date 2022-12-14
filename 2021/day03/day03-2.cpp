#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include <list>

using namespace std;


int main() {
  // open the file
  ifstream is("day03.input");
   
  // read the bit_string from the file
  string bit_string = "";

  // a priori 12 bits
  const int nofb = 12;

  list<bitset<nofb>> ones;
  list<bitset<nofb>> zeros;

  // read the bits in a list
  while ( is >> bit_string )
  {
    bitset<nofb> bits(bit_string);

    if ( bits.test(nofb-1) )
      ones.push_back( bits );
    else
      zeros.push_back( bits );
  }

  // result
  cout << "ones:" << ones.size() <<  endl;
  cout << "zeros:" << zeros.size() << endl;

  unsigned long o2, co2;

  list<bitset<nofb>> work;

  list<bitset<nofb>> tmp_ones;
  list<bitset<nofb>> tmp_zeros;

  // oxygen
  tmp_ones.assign( ones.begin(), ones.end() );
  tmp_zeros.assign( zeros.begin(), zeros.end() );

  for ( int i=nofb-2; i>=0; --i )
  {
    cout << "i:" << i << endl;

    if ( tmp_zeros.size() > tmp_ones.size() )
      work.assign( tmp_zeros.begin(), tmp_zeros.end() );
    else
      work.assign( tmp_ones.begin(), tmp_ones.end() );

    if ( work.size() <= 1 )
      break;

    // empty tmp
    tmp_ones.clear();
    tmp_zeros.clear();

    // iterate work
    for (list<bitset<nofb>>::iterator it=work.begin(); it != work.end(); ++it)
    {
      if ( (*it).test(i) )
        tmp_ones.push_back( *it );
      else
        tmp_zeros.push_back( *it );
    }

    cout << "ones:" << tmp_ones.size() <<  endl;
    cout << "zeros:" << tmp_zeros.size() << endl;
  }

  if ( tmp_zeros.size() > tmp_ones.size() )
    work.assign( tmp_zeros.begin(), tmp_zeros.end() );
  else
    work.assign( tmp_ones.begin(), tmp_ones.end() );

  for (list<bitset<nofb>>::iterator it=work.begin(); it != work.end(); ++it)
  {
    cout << "oxygen:" << *it << endl;
    o2 = (*it).to_ulong();
  }

  // carbon
  tmp_ones.assign( ones.begin(), ones.end() );
  tmp_zeros.assign( zeros.begin(), zeros.end() );

  for ( int i=nofb-2; i>=0; --i )
  {
    cout << "i:" << i << endl;

    if ( tmp_zeros.size() <= tmp_ones.size() )
      work.assign( tmp_zeros.begin(), tmp_zeros.end() );
    else
      work.assign( tmp_ones.begin(), tmp_ones.end() );

    if ( work.size() <= 1 )
      break;

    // empty tmp
    tmp_ones.clear();
    tmp_zeros.clear();

    // iterate work
    for (list<bitset<nofb>>::iterator it=work.begin(); it != work.end(); ++it)
    {
      if ( (*it).test(i) )
        tmp_ones.push_back( *it );
      else
        tmp_zeros.push_back( *it );
    }

    cout << "ones:" << tmp_ones.size() <<  endl;
    cout << "zeros:" << tmp_zeros.size() << endl;
  }

  if ( tmp_zeros.size() <= tmp_ones.size() )
    work.assign( tmp_zeros.begin(), tmp_zeros.end() );
  else
    work.assign( tmp_ones.begin(), tmp_ones.end() );

  for (list<bitset<nofb>>::iterator it=work.begin(); it != work.end(); ++it)
  {
    cout << "carbon:" << *it << endl;
    co2 = (*it).to_ulong();
  }

  cout << "o2:" << o2 << " co2:" << co2 << " mulitply=" << o2*co2 << endl;

  //close the file
  is.close();
}
