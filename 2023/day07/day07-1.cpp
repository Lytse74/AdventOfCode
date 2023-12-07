#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using std::cout;
using std::endl;

int checkHand( std::string s )
{
  enum hand {
  FiveOfaKind  = 6,
  FourOfaKind = 5,
  FullHouse = 4,
  ThreeOfaKind = 3,
  TwoPair = 2,
  OnePair = 1,
  HighCard = 0 };


  hand sHand;

  if ( s[0] == s[1] && s[1] == s[2] && s[2] == s[3] && s[3] == s[4] )
    sHand = FiveOfaKind;
  else if ( s[0] == s[1] && s[1] == s[2] && s[2] == s[3] 
         || s[0] == s[1] && s[1] == s[2] && s[2] == s[4] 
         || s[0] == s[1] && s[1] == s[3] && s[3] == s[4] 
         || s[0] == s[2] && s[2] == s[3] && s[3] == s[4] 
         || s[1] == s[2] && s[2] == s[3] && s[3] == s[4] )
    sHand = FourOfaKind;
  else if ( s[0] == s[1] && s[1] == s[2] && s[3] == s[4] 
         || s[0] == s[1] && s[1] == s[3] && s[2] == s[4]  
         || s[0] == s[2] && s[2] == s[3] && s[1] == s[4]  
         || s[1] == s[2] && s[2] == s[3] && s[0] == s[4]  
         || s[0] == s[1] && s[1] == s[4] && s[2] == s[3]  
         || s[0] == s[2] && s[2] == s[4] && s[1] == s[3]  
         || s[1] == s[2] && s[2] == s[4] && s[0] == s[3]  
         || s[0] == s[3] && s[3] == s[4] && s[1] == s[2]  
         || s[1] == s[3] && s[3] == s[4] && s[0] == s[2]  
         || s[2] == s[3] && s[3] == s[4] && s[0] == s[1] )
    sHand = FullHouse;
  else if ( s[0] == s[1] && s[1] == s[2]
         || s[0] == s[1] && s[1] == s[3]
         || s[0] == s[2] && s[2] == s[3]
         || s[1] == s[2] && s[2] == s[3]
         || s[0] == s[1] && s[1] == s[4]
         || s[0] == s[2] && s[2] == s[4]
         || s[1] == s[2] && s[2] == s[4]
         || s[0] == s[3] && s[3] == s[4]
         || s[1] == s[3] && s[3] == s[4]
         || s[2] == s[3] && s[3] == s[4] )
    sHand = ThreeOfaKind;
  else if ( s[0] == s[1] && ( s[2] == s[3] || s[2] == s[4] || s[3] == s[4] )
         || s[0] == s[2] && ( s[1] == s[3] || s[1] == s[4] || s[3] == s[4] ) 
         || s[0] == s[3] && ( s[1] == s[2] || s[1] == s[4] || s[2] == s[4] ) 
         || s[0] == s[4] && ( s[1] == s[2] || s[1] == s[3] || s[2] == s[3] ) 
         || s[1] == s[2] && ( s[0] == s[3] || s[0] == s[4] || s[3] == s[4] ) 
         || s[1] == s[3] && ( s[0] == s[2] || s[0] == s[4] || s[2] == s[4] ) 
         || s[1] == s[4] && ( s[0] == s[2] || s[0] == s[3] || s[2] == s[3] ) 
         || s[2] == s[3] && ( s[0] == s[1] || s[0] == s[4] || s[1] == s[4] ) 
         || s[2] == s[4] && ( s[0] == s[1] || s[0] == s[3] || s[1] == s[3] ) 
         || s[3] == s[4] && ( s[0] == s[1] || s[0] == s[2] || s[1] == s[2] ) )
    sHand = TwoPair;
  else if ( s[0] == s[1]
         || s[0] == s[2]
         || s[0] == s[3]
         || s[0] == s[4]
         || s[1] == s[2]
         || s[1] == s[3]
         || s[1] == s[4]
         || s[2] == s[3]
         || s[2] == s[4]
         || s[3] == s[4] )
    sHand = OnePair;
  else
    sHand = HighCard;

  return sHand;
}


bool cmpHands( std::string s1, std::string s2 )
{
  bool retVal = true;
  int idx {};

  if ( checkHand(s1) != checkHand(s2) )
  {
    return ( checkHand(s1) < checkHand(s2) );
  }

  std::map<char,int> face = { {'2',0}, {'3',1}, {'4',2}, {'5',3}, {'6',4}, {'7',5}, {'8',6}, {'9',7}, {'T',8}, {'J',9}, {'Q',10}, {'K',11}, {'A',12} };

  while ( s1[idx] && s1[idx] == s2[idx] )
    idx++;

  if ( s1[idx] )
  { 
    retVal = face[s1[idx]] < face[s2[idx]];
  }

  return retVal;
}

bool cmpChar( char a, char b)
{
  std::map<char,int> face = { {'2',0}, {'3',1}, {'4',2}, {'5',3}, {'6',4}, {'7',5}, {'8',6}, {'9',7}, {'T',8}, {'J',9}, {'Q',10}, {'K',11}, {'A',12} };

  return ( face[a] > face[b] );
}

int main() {
  // open the file
  std::ifstream is("day07.input");
  std::string str;

  std::vector<std::pair<std::string,int>> hands;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    std::string hand;
    int val {};

    iss >> hand;
    iss >> val;
    hands.push_back(make_pair(hand,val));

    cout <<  "h=" << hand << ",v=" << val << endl;

    //while ( getline( iss, sstr, ' ' ) )
  }
  is.close();
  cout << endl;
  
  std::sort(hands.begin(), hands.end(), [](auto &left, auto &right) 
    {
      return cmpHands( left.first, right.first );
    });

  int idx { 1 };
  int val { 0 };

  for ( auto h : hands )
  {
    if ( checkHand( h.first ) >= 0 )
    {
      //cout << h.first << " " << h.second;
      std::sort(h.first.begin(),h.first.end(), [](auto &left, auto&right)
        {
          return cmpChar( left, right );
        });
      cout << h.first << endl;
    }
    val += idx * h.second;
    idx++;
  }

  cout << "val = " << val << endl;

}