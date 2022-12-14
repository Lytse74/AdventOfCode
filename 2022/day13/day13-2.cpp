#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;


bool breakList( istringstream& iss, int& niv, string& tmp )
{
  char c;
  bool extra=false;

  tmp.erase();

  while ( iss >> c )
  { 
    if ( c == '[' && niv == 0 )
      niv++; 
    else if ( c == '[' && niv != 0 )
    {
      niv++;
      tmp += c;
    }
    else if ( c == ']' && niv != 1 )
    {
      niv--;
      tmp += c;
    }
    else if ( c == ']' && niv == 1)
    {
      //cout << tmp << endl;
      break;
    }
    else if ( c == ',' && niv == 1)
    {
      //cout << tmp << endl;
      extra = true;
      break;
    }
    else
      tmp += c;
  }

  return extra;
}

bool isValue( string& tst)
{
  return ( !tst.empty() && tst[0] != '[' );
}

bool isArray( string& tst)
{
  return ( !tst.empty() && tst[0] == '[' );
}

int check_strings(string str1, string str2)
{
    istringstream iss1(str1);
    istringstream iss2(str2);

    //cout << str1 << endl;
    //cout << str2 << endl;
    
// If both values are integers, the lower integer should come first. 
// If the left integer is lower than the right integer, the inputs are in the right order. 
// If the left integer is higher than the right integer, the inputs are not in the right order. 
// Otherwise, the inputs are the same integer; continue checking the next part of the input.

// If both values are lists, compare the first value of each list, then the second value, and so on.
// If the left list runs out of items first, the inputs are in the right order. 
// If the right list runs out of items first, the inputs are not in the right order.
// If the lists are the same length and no comparison makes a decision about the order, continue checking the next part of the input.

// If exactly one value is an integer, convert the integer to a list which contains that integer as its only value, then retry the comparison. 
// For example, if comparing [0,0,0] and 2, convert the right value to [2] (a list containing 2); the result is then found by instead comparing [0,0,0] and [2].
    int niv1=0, niv2=0;
    string tmp1,tmp2;
    bool result1=true,result2=true;

    int ret=0;

    while ( (result1 || result2) && ret==0 )
    {
      result1 = breakList( iss1, niv1, tmp1 );
      result2 = breakList( iss2, niv2, tmp2 );

      //cout << tmp1 << " - ";
      //cout << tmp2 << endl;

      // Check empty
      if ( tmp1.empty() || tmp2.empty() && ret==0 )
      {
        if (tmp1.empty() && !tmp2.empty() )
          ret=1;
        if (!tmp1.empty() && tmp2.empty() )
          ret=-1;
      }

      // Check compare
      if ( isValue(tmp1) && isValue(tmp2) && ret==0 ) 
      {
        if ( stoi(tmp1) < stoi(tmp2) )
          ret=1;
        if ( stoi(tmp1) > stoi(tmp2) )
          ret=-1;
      }

      if ( isArray(tmp1) && isArray(tmp2) && ret==0 )
        ret = check_strings( tmp1, tmp2 );
      else if ( isArray(tmp1) && ret==0 )
      {
        tmp2 = '[' + tmp2 + ']';
        ret = check_strings( tmp1, tmp2 );
      }
      else if ( isArray(tmp2) && ret==0 )
      {
        tmp1 = '[' + tmp1 + ']';
        ret = check_strings( tmp1, tmp2 );
      }

    }

    return ret;
}

bool compare_adventofcode (const string& first, const string& second)
{
  bool bret;

  string str1 = first;
  string str2 = second;

  int ret=check_strings( str1, str2 );

  if (ret==1)
    bret = true;

  if (ret==-1)
    bret = false;

  return ( bret );
}

int main() {
  // open the file
  ifstream is("day13.input");
  string str1, str2;
  string dummy;
  list<string> message;
  list<string>::iterator it;

  int val=0;
  int idx=1;

  while ( getline( is, str1 ) && getline( is, str2 ) )
  {
    message.push_back(str1);
    message.push_back(str2);
    
    getline( is, dummy );
  }
  message.push_back("[[2]]");
  message.push_back("[[6]]");

  cout << "before sort:" << endl;
  for (it=message.begin(); it!=message.end(); ++it)
    cout << ' ' << *it << endl;;

  message.sort( compare_adventofcode );

  int idx2 = 0;
  int idx6 = 0;
  int idxc = 1;

  cout << "after sort:" << endl;
  for (it=message.begin(); it!=message.end(); ++it)
  {
    cout << ' ' << *it << endl;
    if ( (*it).compare("[[2]]") == 0 )
      idx2 = idxc;
    if ( (*it).compare("[[6]]") == 0 )
      idx6 = idxc;
    idxc++;
  }


  cout << "P2:" << idx2*idx6 << endl;

  //close the file
  is.close();
 }
