#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>

using std::cout;
using std::endl;

bool isReady( std::vector<std::string> my )
{
  bool ret = true;

  std::vector<std::string>::iterator it;
  for (it = my.begin(); it!=my.end(); it++ )
  {
    if ( it->back() != 'Z' )
    {
      ret = false;
      break;
    }
  }

  return ret;
}

void Update( std::vector<std::string> &my, char ch, std::map<std::string,std::pair<std::string,std::string>> dessert )
{
  std::vector<std::string>::iterator it;
  for (it = my.begin(); it!=my.end(); it++ )
  {
    if ( ch == 'L' )
      *it = dessert[*it].first;
    else
      *it = dessert[*it].second;
  }

  return;
}

// https://stackoverflow.com/questions/72117373/factorization-of-numbers
std::vector<int> PrimeFactors(int n) {
    std::vector<int> r;
    for (int i = 2; i * i <= n; i += 1 + (i > 2)) {
        while ((n % i) == 0) {
            r.push_back(i);
            n /= i;
        }
    }
    if (n != 1)
        r.push_back(n);
    return r;
}



int main() {
  // open the file
  std::ifstream is("day08.input");
  std::string str;

  std::string instr;

  getline( is, instr );
  getline( is, str );

  std::map<std::string,std::pair<std::string,std::string>> dessert;
  std::vector<std::string> startp;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;

    std::string tstart;
    std::string tleft;
    std::string tright;
    int idx {};

    while ( getline( iss, sstr, ' ' ) )
    {
      if ( idx == 0 )
      {
        tstart = sstr;
        if ( tstart.back() == 'A' )
          startp.push_back( tstart );
      }
      if ( idx == 2 )
      {
        tleft = sstr.substr( 1,3 );
      }
      if ( idx == 3 )
      {
        tright = sstr.substr( 0, 3  );
        dessert[tstart] = std::make_pair( tleft, tright );
      }
      ++idx;
    }
  }
  cout << endl;

  is.close();

  std::string::iterator ins;
  long long steps {};
  long long answer { 1 };
  std::set<int> factors;

  for ( auto p : startp )
  {
    ins = instr.begin();
    steps = 0;
    int round {};
    bool cont {};

    while ( p.back() != 'Z' || cont )
    {
      if ( *ins == 'L' )
        p = dessert[p].first;
      else
        p = dessert[p].second;

      ++ins;
      if (ins == instr.end() )
        ins = instr.begin();
      ++steps;
    }
    //cout << "r = " << round+1 << " p = " << p << " steps = " << steps << "/r = " << steps / (round+1) << endl;
    if ( p == "ZZZ" )
      cout << "answer1 = " << steps << endl; 

    std::vector<int> fp = PrimeFactors( steps );
    for ( auto f = fp.begin(); f != fp.end(); f++ )
    {
      //cout << *f << " ";
      factors.insert( *f );

    }
    //cout << endl;
  }

  for ( auto f = factors.begin(); f != factors.end(); f++ )
  {
    answer *= *f;
  }

   
  cout << "answer2 = " << answer << endl; 
}
