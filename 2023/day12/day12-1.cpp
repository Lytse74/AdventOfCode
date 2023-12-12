#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
using std::cout;
using std::endl;


// https://graphics.stanford.edu/~seander/shacks.html
long long getNext( long long v )
{
  //unsigned int v; // current permutation of bits 
  long long w; // next permutation of bits

  long long t = v | (v - 1); // t gets v's least significant 0 bits set to 1
  // Next set to 1 the most significant bit to change, 
  // set to 0 the least significant ones, and add the necessary 1 bits.
  w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  
  return w;
}

// https://stackoverflow.com/questions/45352352/most-efficient-way-to-set-n-consecutive-bits-to-1
long long bitmask ( int n ) {
  long long x = (n ^ 64) >> 6;
  return (x << (n & 63)) - 1;
}

int getDashCount( std::string s1 )
{
  std::istringstream is(s1);
  std::string str;

  int ret {};

  while ( getline( is, str, ',' ) )
  {
    ret += stoi( str );
  }

  return ret;
}

int getQuestionCount( std::string s1 )
{
  return ( std::count(s1.begin(), s1.end(), '?') );
}


std::string getGroupConf( std::string s1 )
{
  std::istringstream is(s1);
  std::string ret;

  char cch;
  char pch;
  int dcnt {};
  bool f = true;

  if ( is.get( pch ) && pch == '#' )
    dcnt++;
  while ( is.get( cch ) )
  {
    if ( pch == '#' && cch == '#' )
    {
      dcnt++;
    }
    else if ( pch == '#' )
    {
      if ( !f ) ret += ',';
      f = false;
      ret += std::to_string(dcnt);
      dcnt = 0;
    }
    else if ( cch == '#' )
    {
      dcnt++;
    }
    pch = cch;
  }
  if ( dcnt != 0 )
  {
    if ( !f ) ret += ',';
    f = false;
    ret += std::to_string(dcnt);
    dcnt = 0;
  }

  return ret;
}

int main() {
  // open the file
  std::ifstream is("day12.input");
  std::string str;
  int cnt {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    std::string cond;
    std::string cgrp;
    std::vector<std::string> split;

    while ( getline( iss, sstr, ' ' ) )
    {
      split.push_back( sstr );
    }

    cond = split[0];
    cgrp = split[1];

    int dashSrc = getDashCount( getGroupConf( cond ));
    int dashTgt = getDashCount( cgrp );
    int questSrc = getQuestionCount( cond );

    cout << cond << "|" << getGroupConf( cond ) << "|" << dashSrc << "|" << questSrc << endl;
    cout << cgrp << "|" << dashTgt <<  endl;
    
    assert( dashTgt >= dashSrc );
    int nbits { dashTgt - dashSrc };
    //assert( nbits > 0 );
    if ( nbits == 0 )
      cout<<endl;

    cout << questSrc << " above " << nbits << endl;

    assert( questSrc <= 20 );
    std::string bits;  
    long long x {};
    std::string tmp;
    int pos {};
    int pos2 {};

    x = bitmask( nbits );
    bits = std::bitset<20>(x).to_string();
    std::replace( bits.begin(), bits.end(), '1', '#');
    std::replace( bits.begin(), bits.end(), '0', '.');
    std::reverse(bits.begin(),bits.end());
    tmp = cond;
    pos2 = questSrc -1;
    while ((pos = tmp.rfind("?")) != std::string::npos)
      tmp.replace(pos, 1, bits, pos2--, 1 );
    
    cout << getGroupConf(tmp) << endl;
    if ( getGroupConf(tmp) == cgrp )
      cnt++;
    
    long long nx = getNext(x);
    while (  nx != x && nx < ( 0x1 << questSrc) )
    {
      bits = std::bitset<20>(nx).to_string();
      std::replace( bits.begin(), bits.end(), '1', '#');
      std::replace( bits.begin(), bits.end(), '0', '.');
      std::reverse(bits.begin(),bits.end());
      tmp = cond;
      pos2 = questSrc -1;
      while ((pos = tmp.rfind("?")) != std::string::npos)
        tmp.replace(pos, 1, bits, pos2--, 1 );
      
      cout << getGroupConf(tmp) << endl;
      if ( getGroupConf(tmp) == cgrp )
        cnt++;
      
      x = nx;
      nx = getNext(x);
    }
    cout << endl;
  }

  cout << "count = " << cnt << endl;

  is.close();
} 