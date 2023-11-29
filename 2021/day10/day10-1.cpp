#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>

int main() {
  // open the file
  std::ifstream is("day10.input");
  std::string str;
  int points = 0;
  long long score = 0;
  std::vector<long long> scores;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    std::stack<char> stk;

    score = 0;

    while ( iss.get(ch) )
    {
      std::cout << ch << "-";
      if ( ch == '[' || ch == '{' || ch == '(' || ch == '<' )
        stk.push( ch );
      else if ( ( ch == ']' && !stk.empty() && stk.top() == '[' )
        || ( ch == '}' && !stk.empty() && stk.top() == '{' )
        || ( ch == ')' && !stk.empty() && stk.top() == '(' )
        || ( ch == '>' && !stk.empty() && stk.top() == '<' ) )
        stk.pop();
      else
      {
        if ( ch == ']' ) points += 57;
        if ( ch == '}' ) points += 1197;
        if ( ch == ')' ) points += 3;
        if ( ch == '>' ) points += 25137;
        while ( !stk.empty() ) stk.pop();
        break;
      }
    }
    if ( !stk.empty() )
    {
      while ( !stk.empty() )
      {
        score *= 5;
        if ( stk.top() == '[' ) score += 2;
        if ( stk.top() == '{' ) score += 3;
        if ( stk.top() == '(' ) score += 1;
        if ( stk.top() == '<' ) score += 4;
        stk.pop();
      }
      std::cout << "score = " << score << std::endl;
      scores.push_back( score );
    }
    std::cout << std::endl;
  }

  std::cout << "points = " << points << std::endl;
  std::sort( scores.begin(), scores.end() );
  std::cout << "score = " << scores[ scores.size() / 2 ] << std::endl; 

  is.close();
}
