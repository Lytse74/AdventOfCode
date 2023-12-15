#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

void UpdateLens( int boxnr, std::string lens, int focus, char op, std::vector<std::vector<std::pair<std::string,int>>> & boxes)
{
  std::vector<std::pair<std::string,int>>::iterator it;

  it = std::find_if ( boxes[boxnr].begin(), boxes[boxnr].end(), 
    [&lens](std::pair<std::string,int> const& elem) {
      return elem.first == lens;
    });

  if ( it == boxes[boxnr].end() && op == '=' )
  {
    boxes[boxnr].push_back( std::make_pair( lens, focus ) );
  }
  else if ( it != boxes[boxnr].end() && op == '-' )
  {
    it = boxes[boxnr].erase( it );
  }
  else if ( op == '=' ) 
  {
    *it = std::make_pair( lens, focus );
  }
  return;
}

int main() {
  // open the file
  std::ifstream is("day15.input");
  std::string str;
  long long result1 {};
  long long result2 {};
  int cnt {};
  std::vector<std::vector<std::pair<std::string,int>>> boxes;
  std::vector<std::pair<std::string,int>> abox;

  for ( auto i=0; i<256; i++ )
  {
    boxes.push_back( abox );
  }

  
  while ( getline( is, str, ',' ) )
  {
    std::istringstream iss(str);
    char ch {};
    int hash1 {};
    int hash2 {};
    char op {};
    int lensfocus { -1 };
    std::string lens;

    std::size_t pos = str.find_first_of("-=");
    lens = str.substr(0,pos);
    
    // Determine the ASCII code for the current character of the string.
    // Increase the current value by the ASCII code you just determined.
    // Set the current value to itself multiplied by 17.
    // Set the current value to the remainder of dividing itself by 256.

    
    while ( iss.get(ch) )
    {
      if ( op != '\0' )
      {
        lensfocus = ( ch - '0' );
      }
      
      if ( ch == '-' || ch == '=' )
      {
        hash2 = hash1;
        op = ch;
      }
      
      hash1 += static_cast<int>(ch);
      assert( static_cast<int>(ch) < 256 );
      assert( static_cast<int>(ch) >= 0 );
      hash1 *= 17;
      hash1 &= 255;
      cout << ch;
    }
    cout << " hash1 = " << hash1 << endl;
    cout << " hash2 = " << hash2 << endl;
    result1 += hash1;
    cnt++;
    cout << "box = " << hash2 << " lens = " << lens << " focus = " << lensfocus << " op = " << op << endl;
    UpdateLens( hash2, lens, lensfocus, op, boxes );
  }


  for ( auto b=0; b < boxes.size(); b++ )
  {
    for ( auto fs=0; fs < boxes[b].size(); fs++ )
    {
      result2 += ( (b+1)*(fs+1)*boxes[b][fs].second );
    }
  }
  
  cout << "result1 = " << result1 << endl;
  //cout << "count = " << cnt << endl;
  cout << "result2 = " << result2 << endl;

  is.close();
}