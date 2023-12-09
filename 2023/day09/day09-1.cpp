#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cout;
using std::endl;

int diff( int n, int m, const std::vector<int> & v )
{
  assert( n>=0 );
  assert( m>=0 );
  if ( n==0 )
  {
    return v[m];
  }
  else
  {
    return ( diff( n-1, m+1, v) - diff( n-1, m, v ) );
  }
}

int main() {
  // open the file
  std::ifstream is("day09.input");
  std::string str;
  int sum1 {};
  int sum2 {};
  
  while ( getline( is, str ) )
  {
    std::vector<int> numbers;
    int num{};

    std::istringstream iss(str);
    while ( iss >> num )
    {
      numbers.push_back(num);
      cout << num << " ";
    } 
    cout << endl;

    std::vector<int> last;
    std::vector<int> first;
    int i { 1 };
    
    last.push_back( numbers.back() );
    first.push_back( numbers.front() );

    for ( int i = 1 ; i < numbers.size() - 1 ; ++i  )
    {
      bool allZero =  true;
      for ( int j = 0  ; j< numbers.size() - i ; ++j )
      {
        if ( diff( i, j, numbers ) != 0 ) 
        {
          allZero = false;
          break;
        }
      }
      int tmp1 = diff( i, numbers.size() -i -1, numbers );
      last.push_back( tmp1 );
      int tmp2 = diff( i, 0, numbers );
      first.push_back( tmp2 );
      //cout << tmp1 << " ";
      //cout << tmp2 << " ";
      if ( allZero ) break;
    }
    cout << endl;
    auto result1 = std::accumulate(last.begin(), last.end(), 0 );
    cout << "result1 = " << result1 << endl;

    std::vector<int>::iterator it_first;
    std::reverse( first.begin(),first.end());

    it_first = first.begin();
    it_first++;

    int result2 {};

    while( it_first != first.end() )
    {
      result2 = *it_first - result2;
      it_first++;
    }

    cout << "result2 = " << result2 << endl;

    sum1 += result1;
    sum2 += result2;
  }
  cout << "sum1 = " << sum1 << endl;
  cout << "sum2 = " << sum2 << endl;

  is.close();
}