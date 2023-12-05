#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using std::cout;
using std::endl;
using std::make_pair;

int main() {
  // open the file
  std::ifstream is("day05.input");
  std::string str;

  // block by block  
  // seeds
  std::vector<std::pair<long long,long long>> seeds;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;
    int idx=0;
    long long rng {};

    while ( getline( iss, sstr, ':' ) )
    {
      if ( idx == 1 )
      {
        std::istringstream isss(sstr);
        long long nr {};
        while ( isss >> nr )
        {
          isss >> rng;

          //for ( long long i = nr; i < nr + rng; i++ ) 
          seeds.push_back( make_pair( nr , nr + rng -1 ) );
          //seeds.push_back( nr );
          //seeds.push_back( nr + rng - 1);
        }
      }

      ++idx; 
      cout << sstr << endl;
    }
  }

  // seed to soil map
  std::map<std::pair<long long,long long>,long long> msee2soi;
  std::map<std::pair<long long,long long>,long long>::iterator it_msee2soi;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    msee2soi[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // soil to fert map
  std::map<std::pair<long long,long long>,long long> msoi2fer;
  std::map<std::pair<long long,long long>,long long>::iterator it_msoi2fer;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    msoi2fer[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // fert to water map
  std::map<std::pair<long long,long long>,long long> mfer2wat;
  std::map<std::pair<long long,long long>,long long>::iterator it_mfer2wat;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    mfer2wat[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // water to light map
  std::map<std::pair<long long,long long>,long long> mwat2lig;
  std::map<std::pair<long long,long long>,long long>::iterator it_mwat2lig;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    mwat2lig[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // light to temp map
  std::map<std::pair<long long,long long>,long long> mlig2tem;
  std::map<std::pair<long long,long long>,long long>::iterator it_mlig2tem;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    mlig2tem[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // temp to humidity map
  std::map<std::pair<long long,long long>,long long> mtem2hum;
  std::map<std::pair<long long,long long>,long long>::iterator it_mtem2hum;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    mtem2hum[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  // humidity to loc map
  std::map<std::pair<long long,long long>,long long> mhum2loc;
  std::map<std::pair<long long,long long>,long long>::iterator it_mhum2loc;
  while ( getline( is, str ) && str != "" )
  {
    std::istringstream iss(str);
    std::string sstr;

    long dst {}; long src {}; long rng {};
 
    cout << str << endl;
    
    if ( str.back() == ':' ) continue;

    iss >> dst; iss >> src; iss >> rng;

    mhum2loc[ make_pair( src, src + rng -1 ) ] = dst - src;
  }
  cout << endl;

  long long minloc { 3831146575 }; 

  // this can be done much faster
  for ( auto range: seeds )
  for ( auto seed = range.first ; seed <= range.second; seed++)
  {
    long long tmp {};
    tmp = seed;
    //cout << tmp;

    it_msee2soi = std::find_if ( msee2soi.begin(), msee2soi.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_msee2soi != msee2soi.end() )
      tmp += it_msee2soi->second;
    //cout << "->" << tmp;

    it_msoi2fer = std::find_if ( msoi2fer.begin(), msoi2fer.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_msoi2fer != msoi2fer.end() )
      tmp += it_msoi2fer->second;
    //cout << "->" << tmp;

    it_mfer2wat = std::find_if ( mfer2wat.begin(), mfer2wat.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_mfer2wat != mfer2wat.end() )
      tmp += it_mfer2wat->second;
    //cout << "->" << tmp;

    it_mwat2lig = std::find_if ( mwat2lig.begin(), mwat2lig.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_mwat2lig != mwat2lig.end() )
      tmp += it_mwat2lig->second;
    //cout << "->" << tmp;

    it_mlig2tem = std::find_if ( mlig2tem.begin(), mlig2tem.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_mlig2tem != mlig2tem.end() )
      tmp += it_mlig2tem->second;
    //cout << "->" << tmp;

    it_mtem2hum = std::find_if ( mtem2hum.begin(), mtem2hum.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_mtem2hum != mtem2hum.end() )
      tmp += it_mtem2hum->second;
    //cout << "->" << tmp;

    it_mhum2loc = std::find_if ( mhum2loc.begin(), mhum2loc.end(), 
      [&tmp](auto const& elem)
      {
        return elem.first.first <= tmp && elem.first.second >= tmp ;
      }
    );
    if ( it_mhum2loc != mhum2loc.end() )
      tmp += it_mhum2loc->second;
    //cout << "->" << tmp;

    if ( tmp < minloc )
     minloc = tmp;

    //cout << endl;
  }

  cout << "min = " << minloc  << endl;

  is.close();
}