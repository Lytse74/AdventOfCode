#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <map>
#include <regex>

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

int getMinLength( std::vector<int> v )
{
  int ret {};
 
  for ( auto& n : v )
    ret += n + 1;
  ret -= 1;

  return ret;
}

int getQuestionCount( std::string s1 )
{
  return ( std::count(s1.begin(), s1.end(), '?') );
}

std::string getGroupConf2( std::string s1 )
{
  std::istringstream is(s1);
  std::string ret;

  char cch;
  char pch;
  int dcnt {};
  bool f = true;

  if ( is.get( pch ) && ( pch == '#' || pch == '?' ) )
    dcnt++;
  while ( is.get( cch ) )
  {
    if ( ( pch == '#' || pch == '?' ) && ( cch == '#' || cch == '?' ) )
    {
      dcnt++;
    }
    else if ( ( pch == '#' || pch == '?' ) )
    {
      if ( !f ) ret += ',';
      f = false;
      ret += std::to_string(dcnt);
      dcnt = 0;
    }
    else if ( ( cch == '#' || cch == '?' ) )
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

void placeDots( std::string & s1, int n )
{
  char cch;
  char pch;
  int dcnt {};

  for ( auto ch = s1.begin(); ch < s1.end(); ch++ )
  {
    cch = *ch;
    if ( *ch == '#')
    {
      dcnt++;
      pch = *ch;
    }
    else if ( pch == '#' )
    {
      if ( dcnt >= n )
        *ch = '.';
      dcnt = 0;
    }
  }
  
  for ( auto ch = s1.rbegin(); ch < s1.rend(); ch++ )
  {
    cch = *ch;
    if ( *ch == '#')
    {
      dcnt++;
      pch = *ch;
    }
    else if ( pch == '#' )
    {
      if ( dcnt >= n )
        *ch = '.';
      dcnt = 0;
    }
  }

  return;
}

int recur( std::string s1, std::vector<int> v, std::map<int,std::string> mreg )
{
  std::size_t mlen = getMinLength( v ) +2;
  std::size_t tgtlen = s1.length();
  std::string s2;
  int result = 0;

  if (  mlen > tgtlen )
    return 0;

  std::size_t pdot = s1.find_first_of(".",1);
  std::size_t phash = s1.find_first_of("#");
  
  std::size_t wiggle1 = tgtlen - mlen;
  std::size_t wiggle2 = pdot;
  std::size_t wiggle3 = phash-1;

  std::size_t thewiggle = (  wiggle2 < wiggle3 ) ? ( ( wiggle2 < wiggle1 ) ? wiggle2 : wiggle1 ) : ( ( wiggle3 < wiggle1 ) ? wiggle3 : wiggle1 );

  std::vector<int>::iterator it;
  it = v.begin();

  if ( it == v.end() )
    return 1;

  auto const regex = std::regex(mreg[*it]);
  auto sres = std::smatch{};
  auto pit = *it;
  it = v.erase(it);

  while ( thewiggle +1 > 0 )
  {
  bool const found = std::regex_search( s1, sres, regex);
  cout << s1 << " " << mreg[1] << endl;
  cout << "found = " << sres.size() << " " << found << " position = " << sres.position() << " length = " << sres.length() << endl;
  
  s2 = "." + s1.substr( sres.position()+sres.length() );
  cout << s2 << " " << mreg[pit] << endl;
  if ( !v.empty() )
  {
    cout << "rb:" << result << endl; 
    result += recur( s2, v, mreg ) ;
    cout << "ra:" << result << endl; 
  }
  else if ( found ) 
  {
    result += 1;
    cout << "rf:" << result << endl; 
  }

  thewiggle  -= 1;
  if ( found )
    s1 = s1.substr(sres.position()+1);
  }  
  return result;
}


int main() {
  // open the file
  std::ifstream is("day12.test");
  std::string str;
  long long cnt {};
  std::map<int,std::string> mreg;
  
  for ( auto i=1; i<=20; i++ )
  {
    mreg[i] = "[.\?][#\?]{" + std::to_string( i ) + "}[.\?]";
  }

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
    //cond = split[0] + "?" + split[0] + "?" + split[0] + "?" + split[0] + "?" + split[0];
    cgrp = split[1];
    //cgrp = split[1] + "," + split[1] + "," + split[1] + "," + split[1] + "," + split[1];

    int dashSrc = getDashCount( getGroupConf( cond ));
    int dashTgt = getDashCount( cgrp );
    int questSrc = getQuestionCount( cond );

    cout << cond << "|" << getGroupConf( cond ) << "|" << dashSrc << "|" << questSrc << endl;
    cout << cgrp << "|" << dashTgt <<  endl;
    
    assert( dashTgt >= dashSrc );

    // filter out unwanted questions
    std::vector<int> v,w,u;
    std::vector<int>::iterator it_v;
    std::string tcgrp = getGroupConf2( cond );
    cout << tcgrp << endl;

    std::istringstream is2(cgrp);
    while ( getline ( is2, sstr, ',' ) )
    {
      v.push_back( std::stoi( sstr ) );
    }
    
    // let cond always start with a dot
    cond = "." + cond + ".";
    long long pipo = recur( cond, v, mreg );

    cout << "recur = " << pipo;
    cout << endl;
  }

  cout << "count = " << cnt << endl;

  is.close();
} 