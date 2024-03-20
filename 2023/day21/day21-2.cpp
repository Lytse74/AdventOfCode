#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;
using std::pair;
using std::make_pair;

set<tuple<int,int>> FloodIt( vector<vector<int>> & grid, set<tuple<int,int>> checkPt,  int color = 0 )
{
  set<tuple<int,int>> ret;

  for ( auto it = checkPt.begin(); it != checkPt.end(); it++ )
  {
    int r {}; int c {};
    tie(r,c) = *it;

    grid[r][c] = color;

    if ((r>0) && grid[r-1][c] == -1 )
      ret.insert( make_tuple( r-1, c ) );
    if ((c>0) && grid[r][c-1] == -1 )
      ret.insert( make_tuple( r, c-1 ) );
    if (( r < grid.size()-1) && grid[r+1][c] == -1 )
      ret.insert( make_tuple( r+1, c ) );
    if (( c < grid[0].size()-1) && grid[r][c+1] == -1 )
      ret.insert( make_tuple( r, c+1 ) );
  }

  return ret;
}

int print( vector<vector<int>> grid, bool p, int steps )
{
  int count {};
  for ( auto line: grid )
  {
    for ( auto pt: line )
    {
      if ( pt == -1 )
      {
        if(p) {cout << ".";}
      }
      else if ( pt == -2 )
      {
        if(p) {cout << "#";}
      }
      else
      {
        // here check for odd/even steps
        if ( ( pt & 0x1 ) == (steps & 0x1) )
          count++;
        if(p) {cout << (char)('0' + ((pt % 131)%11));}
      }
    }
    if(p) {cout << endl;}
  }
  cout << "count = " << count << endl;
  //cout << " " << count;// << endl;

  return count;
}

int main() {
  // open the file
  std::ifstream is("day21.test3");
  std::string str;

  vector<vector<int>> grid;
  tuple<int,int> start = make_tuple(-1,-1);
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch {};

    vector<int> line;
   
    while ( iss.get(ch) )
    {
      int val {};
      if ( ch == '.' )
        val = -1;
      if ( ch == '#' )
        val = -2;
      if ( ch == 'S' )
      {
        val = -1;
        get<0>(start) = grid.size();
        get<1>(start) = line.size();
      }
      line.push_back(val);
      cout << ch;
    }
    grid.push_back(line);
    cout << endl;
  }
  cout << endl;

  is.close();

  set<tuple<int,int>> checkPt;
  checkPt.insert( start );

  print( grid, true, 0);

  int color {};
  cout <<  "color = " << color << endl;

  long long cnt { 0 };
  long long prev_cnt { 0 };

  map<pair<int,char>,int> base;
  map<pair<int,char>,int> divs;
  map<pair<int,char>,int> inc;
  map<pair<int,char>,int> dinc;

  int iready = 0;
  int ibreak = 0;
  int modready = 0;

  //while( !checkPt.empty() )
  for ( auto i=0; i<=500; i++)
  { 
    checkPt = FloodIt( grid, checkPt, color );

    cnt = print( grid, false, i );
    
    char ch;
    int mod;

    if ( (i & 0x1) == 0x0 )
      ch = 'e';
    else 
      ch = 'o';

    mod = i % 131; // solution specific
    pair<int,char> tmp = make_pair(mod,ch);
    pair<int,char> tmp2 = make_pair(mod,'*');

    // check increment
    int incr = cnt - prev_cnt;
    int dincr = incr - inc[tmp2];

    base[tmp2] = cnt; // not neede to split the oddd/even  stat=rts!?
    inc[tmp2] = incr;
    divs[tmp2] = i / 131;
    
    if ( dincr != dinc[tmp2] )
    {
      ibreak = 0;
      dinc[tmp2] = dincr;
    }
    else
      ibreak++;
    
    prev_cnt = cnt;
    iready = i;
    modready = mod;
    color++;
    if ( i == 64 )
    {
      cout << "count = " << cnt << endl;
    }
    
    if ( ibreak == 131 )
    {
      cout << "iready = " << iready << endl;
      break;
    }
  }

  //print( grid, true, iready );

/*
In exactly 100 steps, he can reach 6536 garden plots.
In exactly 500 steps, he can reach 167004 garden plots.
In exactly 1000 steps, he can reach 668697 garden plots.
In exactly 5000 steps, he can reach 16733044 garden plots.
*/
  //vector<int> vex = { 100, 500, 1000, 5000 };
  vector<int> vex = { 26501365 };
  //vector<int> vex = { 495 };

  for ( auto v : vex )
  {
    char ch;
    int mod;
    int div;

    if ( (v & 0x1) == 0x0 )
      ch = 'e';
    else 
      ch = 'o';
    ch = '*'; //  its not neede to diferentiate the odd ]/ev en starts

    mod = v % 131; // solution specific
    div = v / 131;
    pair<int,char> tmp = make_pair(mod,ch);
    pair<int,char> tmp2 = make_pair(mod,'*');

    // modready = 4
    long long base_start = base[make_pair( modready, ch )];
    int div_start = divs[make_pair( modready, '*' )];
    int mod_start = (modready+1)%131;
    if ( mod_start == 0)
      div_start++;
    
    cout << base_start << ":"  << div_start << "|" << mod_start << "-" << div << "|" << mod << endl;

    // complete current mod iteration
    if ( div_start < div && mod_start > 0)
    {
      for ( int mi = mod_start; mi<131; mi++ )
      {
        base_start += (inc[make_pair(mi,'*')]+dinc[make_pair(mi,'*')]);
        inc[make_pair(mi,'*')] = (inc[make_pair(mi,'*')]+dinc[make_pair(mi,'*')]);
      }
      div_start++;
      mod_start=0;
    }
    
    cout << base_start << ":"  << div_start << "|" << mod_start << "-" << div << "|" << mod << endl;
   
    if (div_start < div )
    {
      long long di = div - div_start;

      for ( int mi=0; mi<131; mi++ )
      {
        base_start += ( di * inc[make_pair(mi,'*') ] + (( di * di + di ) /2) * dinc[make_pair(mi,'*')]);
        inc[make_pair(mi,'*') ] = ( inc[make_pair(mi,'*') ] +  di * dinc[make_pair(mi,'*')]);
      }
      div_start=div;
    }
    
    cout << base_start << ":"  << div_start << "|" << mod_start << "-" << div << "|" << mod << endl;
   
    if ( div_start == div )
    {
      for ( int mi=0; mi<=mod; mi++ )
      {
        base_start += (inc[make_pair(mi,'*')]+dinc[make_pair(mi,'*')]);
        inc[make_pair(mi,'*')] = (inc[make_pair(mi,'*')]+dinc[make_pair(mi,'*')]);
      }
      mod_start=mod;
    }
    
    cout << base_start << ":"  << div_start << "|" << mod_start << "-" << div << "|" << mod << endl;
   
  }
}