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


long long recur( std::string cond, std::vector<int> igrp, std::map<std::tuple<int,int,int>,long long> & rep, int pos, int bpos, int dpos )
{
  std::tuple<int,int,int> key = std::make_tuple( pos, bpos, dpos );
  long long answer = 0;
  
  // if input was calculated before return it
  if ( rep.find(key) != rep.end() )
    return rep[key];

  // the end of the conditional string was reached
  if ( pos == cond.length() )
    // all blocks were matched
    if ( bpos == igrp.size() && dpos==0 )
      return 1;
    // the last block was matched  
    else if ( bpos == igrp.size()-1 && igrp[bpos]==dpos )
      return 1;
    // not all the blocks were matched
    else
      return 0;

  for ( auto c: {'.', '#'} )
  {
    if ( cond[pos] == c || cond[pos]=='?' )
      if ( c == '.' && dpos == 0 ) 
        answer += recur( cond, igrp, rep, pos+1, bpos, 0 );
      else if ( c == '.' && dpos > 0 && bpos < igrp.size() && igrp[bpos] == dpos )
        answer += recur( cond, igrp, rep, pos+1, bpos+1, 0 );
      else if (  c == '#' )
        answer += recur( cond, igrp, rep, pos+1, bpos, dpos+1 );
  }
  
  rep[key] = answer;

  return answer;
}

int main() {
  // open the file
  std::ifstream is("day12.input");
  std::string str;
  long long cnt {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    std::string cond;
    std::string cgrp;
    std::vector<std::string> split;
    long long cnti { 0 };

    while ( getline( iss, sstr, ' ' ) )
    {
      split.push_back( sstr );
    }

    cond = split[0] + "?" + split[0] + "?" + split[0] + "?" + split[0] + "?" + split[0];
    cgrp = split[1] + "," + split[1] + "," + split[1] + "," + split[1] + "," + split[1];

    int dashSrc = getDashCount( getGroupConf( cond ));
    int dashTgt = getDashCount( cgrp );
    int questSrc = getQuestionCount( cond );

    cout << cond << "|" << getGroupConf( cond ) << "|" << dashSrc << "|" << questSrc << endl;
    cout << cgrp << "|" << dashTgt <<  endl;
    
    assert( dashTgt >= dashSrc );

    std::istringstream viss(cgrp);
    std::vector<int> igrp ;
    while ( getline( viss, sstr, ',') )
    {
      igrp.push_back( stoi(sstr) );
    }

    std::map<std::tuple<int,int,int>,long long> rep;

    cnti = recur( cond, igrp, rep, 0, 0, 0 );

    cnt += cnti;

    cout << cnti << "|" << rep.size() << endl;

  }

  cout << "count = " << cnt << endl;

  is.close();
} 