#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

int mapDigit( char ch )
{
  switch ( ch )
  {
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '-':
      return -1;
      break;
    case '=':
      return -2;
      break;
    case '0':
      return 0;
      break;
    default:
      return 0;
      break;
  }
}

vector<int> simpleAdd(vector<int> a1,vector<int> a2)
{
  vector<int> tmp;
  int a1s = a1.size();
  int a2s = a2.size();

  int asmax = a1s;
  if (a2s > a1s) asmax = a2s;


  // for overflow
  tmp.push_back(0);

  // just add
  for ( int i=0; i<asmax; ++i )
  {
    int v=0;
    if ( i >= asmax-a1s )
      v+=a1[a1s-asmax+i];
    if ( i >= asmax-a2s )
      v+=a2[a2s-asmax+i];
    tmp.push_back(v);
  }

  // cleanup
  for ( int i=tmp.size()-1; i>0; --i)
  {
    // 4 = 5 -1
    // 3 = 5 -2
    // -3 = -5 +2
    // -4 = -5 +1
    // 5 = 5 
    // -5 = -5 
    //cout << tmp[i] << " >>> ";

    switch ( tmp[i] )
    {
      case 5:
        tmp[i]=0;
        tmp[i-1]+=1;
        break;
      case 4:
        tmp[i]=-1;
        tmp[i-1]+=1;
        break;
      case 3:
        tmp[i]=-2;
        tmp[i-1]+=1;
        break;
      case -3:
        tmp[i]=2;
        tmp[i-1]-=1;
        break;
      case -4:
        tmp[i]=1;
        tmp[i-1]-=1;
        break;
      case -5:
        tmp[i]=0;
        tmp[i-1]-=1;
        break;
      default:
        break;
    }

    //cout << tmp[i] << endl;
  }


  
  return tmp;
}

void printDecimal( vector<int> n )
{
  int length = n.size();
  long long power=1;
  long long val=0;
  for( int i=0; i<length; i++ )
  {
    val += (power*n[length-i-1]);
    power *= 5; 
  }

  cout << "val: " << val << endl;
}

void printSnafu( vector<int> n )
{
  int length = n.size();
  bool print=false;

  cout << "val: ";

  for( int i=0; i<length; i++ )
  {
    if ( print || n[i] != 0 )
    {
      print = true;
      if ( n[i] >= 0 )
        cout << n[i];
      else if ( n[i] == -1 )
        cout << '-';
      else if ( n[i] == -2 )
        cout << '=';
      else
        cout << '*';
    }
  }
  cout << endl;
}



int main() {
  // open the file
  ifstream is("day25.input");
  string str;

  vector<vector<int>> numbers;

  while ( getline( is, str ) )
  {
    vector<int> tmp;

    for ( char ch: str )
    {
      tmp.push_back( mapDigit(ch) );       
      cout << "+" << ch;
    }
    cout << " >>> " << str;
    numbers.push_back( tmp );
    cout << " >>> ";
    printSnafu( tmp );
    cout << endl;
  }
  cout << "^^INPUT^^" << endl;

  //close the file
  is.close();

  vector<int> ans;

  for ( auto n : numbers )
  {
    printDecimal(n);
    printSnafu(n);
    ans = simpleAdd( ans, n );
    printDecimal(ans);
  }

  printSnafu( ans );
}
