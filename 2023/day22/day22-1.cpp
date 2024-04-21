#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;

int main() {
  // open the file
  std::ifstream is("day22.input");
  std::string str;
  int mx {}; int my {}; int mz {};
  int lx {9} ; int ly {9}; int lz {9};
  int n {0};

  vector<tuple<int,int,int,int,int,int,int>> lines;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    int idx {};
    int jdx {};
    int x1 {}; int y1 {}; int z1 {};
    int x2 {}; int y2 {}; int z2 {};

    while ( getline(iss,sstr, '~'))
    {
//      cout << idx << ':' << sstr << endl;
      std::istringstream isss(sstr);
      string ssstr;

      jdx =0;
      while ( getline( isss,ssstr, ',' ) )
      {
        if (jdx == 0 && idx == 0)
          x1 = stoi( ssstr );
        else if (jdx == 1 && idx == 0)
          y1 = stoi( ssstr );
        else if (jdx == 2 && idx == 0)
          z1 = stoi( ssstr );
        else if (jdx == 0 && idx == 1)
          x2 = stoi( ssstr );
        else if (jdx == 1 && idx == 1)
          y2 = stoi( ssstr );
        else if (jdx == 2 && idx == 1)
          z2 = stoi( ssstr );
        jdx++;
      }

      
      idx++;
    }
//    cout << "P1: " << x1 << "|" << y1 << "|" << z1 << endl;
//    cout << "P2: " << x2 << "|" << y2 << "|" << z2 << endl;
//    cout << " D : " << x2-x1+1 << "|" << y2-y1+1 << "|" << z2-z1+1 << endl;


    if (x1>mx) mx=x1; if (x2>mx) mx=x2;
    if (y1>my) my=y1; if (y2>my) my=y2;
    if (z1>mz) mz=z1; if (z2>mz) mz=z2;
    if (x1<lx) lx=x1; if (x2<lx) lx=x2;
    if (y1<ly) ly=y1; if (y2<ly) ly=y2;
    if (z1<lz) lz=z1; if (z2<lz) lz=z2;

    if (z2<z1)
    {
      std::swap( z1,z2); std::swap(y1,y2); std::swap(x1,x2);
    }
    else if (z1 == z2 && y2<y1)
    {
      std::swap( y2,y1 ); std::swap( x2, x1 );
    } 
    else if (z1 == z2 && y1 == y2 && x2 < x1 )
    {
      std::swap(x2,x1);
    }
    lines.push_back( make_tuple(x1,y1,z1,x2,y2,z2,++n));

  }
  cout <<  "M: " << mx << "|" << my << "|" << mz << endl;
  cout <<  "L: " << lx << "|" << ly << "|" << lz << endl;

  is.close();

  std::sort(begin(lines), end(lines), 
    [](tuple<int, int, int, int, int, int, int> const &t1, tuple<int,int, int, int, int, int, int> const &t2) {
        return ( get<2>(t1) < get<2>(t2) 
          || get<2>(t1) == get<2>(t2) && get<1>(t1) < get<1>(t2)
          || get<2>(t1) == get<2>(t2) && get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2) ); // or use a custom compare function
    }
  );

  vector<vector<vector<int>>> stack;
  vector<vector<int>> floor;
  for ( auto f=0; f<=305; f++ )
  { 
    vector<vector<int>> plane;
    for ( auto g=0; g<10; g++ )
    {
      vector<int> line;
      for ( auto h=0; h<10; h++ )
      {
        line.push_back(0);
      }
      plane.push_back(line);
      if (f==0) floor.push_back(line);
    }
    stack.push_back(plane);
  }
  
  // place the lines in the stack
  for (auto & l: lines)
  {
    // create a floor for the current block
    // check height of floor where tfloor has a brick
    vector<vector<int>> tfloor;
    int height { 0 };
    height = get<5>(l) - get<2>(l) +1;
    int zval = 0;
    for ( auto g=0; g<10; g++ )
    {
      vector<int> line;
      for ( auto h=0; h<10; h++ )
      {
        if ( h>= get<0>(l) && g>= get<1>(l) && h<= get<3>(l) && g<= get<4>(l) )
        {
          line.push_back(height);
          if ( floor[g][h] > zval ) 
            zval = floor[g][h];
        }
        else
          line.push_back(0);
      }
      tfloor.push_back(line);
    }
    int tzval = get<2>(l);

    // Add tfloor to floor
    assert(tzval>zval);
    if (tzval-zval>1)
    {
      // correct z
      get<2>(l) -= (tzval-zval-1);
      get<5>(l) -= (tzval-zval-1);
      tzval = get<2>(l);
    }
    
    assert(tzval-zval==1);
    for ( auto g=0; g<10; g++ )
    {
      for ( auto h=0; h<10; h++ )
      {
        if ( tfloor[g][h]>0 )
        {
          floor[g][h] = zval + tfloor[g][h];
        }
      }
    }
  }
  
  std::sort(begin(lines), end(lines), 
    [](tuple<int, int, int, int, int, int, int> const &t1, tuple<int,int, int, int, int, int, int> const &t2) {
        return ( get<2>(t1) < get<2>(t2) 
          || get<2>(t1) == get<2>(t2) && get<1>(t1) < get<1>(t2)
          || get<2>(t1) == get<2>(t2) && get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2) ); // or use a custom compare function
    }
  );

  // A brick can only be disintegrated if it supports no other nodes 
  // or if all the nodes it supports are supported by another node

  // Supports
  map<int,set<int>> supports;
  map<int,set<int>> leanson;

  // given a brick find the bricks it supports
  int dcnt { 0 };

  for (auto l: lines)
  {
    int supc { 0 };
    int supac { 0 };
    set<int> supp;
    set<int> lean;

    for (auto m: lines)
    {
      if ( get<5>(l) +1 != get<2>(m) )
        continue;
      if ( get<0>(l) > get<3>(m) )
        continue;
      if ( get<3>(l) < get<0>(m) )
        continue;
      if ( get<1>(l) > get<4>(m) )
        continue;
      if ( get<4>(l) < get<1>(m) )
        continue;
      supc++;
      lean.clear();

      // m always leans on l
      lean.insert(get<6>(l));

      cout << "  [" << get<0>(m) << "," << get<1>(m) << "," << get<2>(m) << "," << get<3>(m) << "," << get<4>(m) << "," << get<5>(m) << "]" << endl;
      bool a = false;
      
      for (auto n: lines)
      {
        if ( get<2>(m) -1 != get<5>(n) )
          continue;
        if ( get<0>(m) > get<3>(n) )
          continue;
        if ( get<3>(m) < get<0>(n) )
          continue;
        if ( get<1>(m) > get<4>(n) )
          continue;
        if ( get<4>(m) < get<1>(n) )
          continue;
        if ( l == n )
          continue;

        // m also leans on n
        lean.insert(get<6>(n));
        cout << "    [" << get<0>(n) << "," << get<1>(n) << "," << get<2>(n) << "," << get<3>(n) << "," << get<4>(n) << "," << get<5>(n) << "]" << endl;
        a=true;
      }

      if ( a )
        supac++;

      supp.insert( get<6>(m) );
      leanson[get<6>(m)] = lean;
    }
    supports[get<6>(l)] = supp;

    if ( supc > 1 )
      cout << "are";
    if ( supc == 1 )
      cout << "is";
    if ( supc > 0)
      cout << " supported by ";
    if ( supc >= 0 )
      cout << "[" << get<0>(l) << "," << get<1>(l) << "," << get<2>(l) << "," << get<3>(l) << "," << get<4>(l) << "," << get<5>(l) << "]";
    if (supc>0 && supc == supac)
    {
      cout <<  " but can be disintegrated";
      dcnt++;
    }
    if ( supc == 0 )
    {
      cout << " can be disintegrated";
      dcnt++;
    }
    cout << endl;
  }

  cout << "answer = " << dcnt << endl; 

  map<int,set<int>>::iterator supp_it;
  map<int,set<int>>::iterator lean_it;

  map<int,int> blastbrick;
  map<int,int>::iterator it_bb;
  
  for ( lean_it = leanson.begin() ; lean_it != leanson.end() ; lean_it++ )
  {
    set<int> blasted;
    set<int>::iterator it_blast;
    set<int>::iterator it_sp;

    if ( lean_it->second.size() == 1 )
    {
      //cout << "brick ";
      cout << *(lean_it->second.begin()) << " found! ";

      blasted.insert( *(lean_it->second.begin()) );
      it_blast = blasted.begin();
      while ( it_blast != blasted.end() )
      {
        bool recfound = false;
        for ( it_sp = supports[*it_blast].begin(); it_sp != supports[*it_blast].end(); it_sp++ )
        {
          // check if brick that is blasted will fall
          if ( std::includes(blasted.begin(),blasted.end(),leanson[*it_sp].begin(),leanson[*it_sp].end() ) )
          {
            if ( blasted.find(*it_sp) == blasted.end() )
            {
              blasted.insert(*it_sp);
              recfound = true;
            }
          }
        }
        if ( recfound )
        { 
          it_blast = blasted.begin();
        }
        else
          it_blast++;
      }

      cout << "blasting it wil make " << blasted.size()-1 << " bricks fall!" << endl;
      blastbrick[*(lean_it->second.begin())] = blasted.size()-1;
    }
  }

  int answer2 { 0 };

  for ( it_bb = blastbrick.begin(); it_bb != blastbrick.end(); it_bb++ )
  {
    answer2 += it_bb->second;
  }

  cout << "answer2 = " << answer2 << endl;

/* graphviz output:
  for ( auto e : leanson )
  {
    cout << (e.first) << " -> ";
    bool first { true };
    for ( auto s : e.second )
    {
      if ( first )
      {
        cout << s;
        first = false;
      }
      else
      {
        cout << ", " << s;
      }
    }
    cout << "[color=cyan]" << endl;
  }

  for ( auto e : supports )
  {
    if (e.second.size()==0)
      continue;

    cout << (e.first) << " -> ";
    bool first { true };
    for ( auto s : e.second )
    {
      if ( first )
      {
        cout << s;
        first = false;
      }
      else
      {
        cout << ", " << s;
      }
    }
    cout << "[color=green]" << endl;
  }
*/ 
  

}