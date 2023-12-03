#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>

int main() {
  // open the file
  std::ifstream is("day03.input");
  std::string str;
  int row=0;
  int col=0;

  std::set<std::pair<int,int>> symbols;
  std::set<std::pair<int,int>> gears;
  std::set<std::pair<int,int>>::iterator it_gears;
  std::map<std::pair<int,int>,int> numbers;
  std::map<std::pair<int,int>,int>::iterator it_numbers;
  int sum {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    int nr;
    col = 0;

    while ( ( ch = iss.peek() ) != EOF )
    {
      if ( std::isdigit(ch) )
      {
        std::string tmp;
        iss >> nr;
        std::cout << nr;
        numbers[std::make_pair(row,col)]=nr;
        tmp = std::to_string(nr);
        
        // correct col
        col += tmp.length()-1;
      }
      else
      {
        iss.get(ch);
        std::cout << ch;
        if ( ch != '.')
        {
          symbols.insert( std::make_pair(row,col));
        }
        if ( ch == '*')
        {
          gears.insert( std::make_pair(row,col));
        }
      }
      ++col;
    }
    ++row;
    std::cout << std::endl;
  }
  std::cout << std::endl;
  
  is.close();

  it_numbers = numbers.begin();
  while ( it_numbers != numbers.end() )
  {
    int x; int y; int num; int digits { 1 }; 
    x=it_numbers->first.first;
    y=it_numbers->first.second;
    num=it_numbers->second;
    while( num /= 10 )
      digits++;

    // check if number touches a symbol
    bool touch = false;
    for ( int i = x-1; i< x+2; i++ )
    {
      for ( int j = y-1; j< y+digits+1; j++ )
      {
         touch = ( symbols.find( std::make_pair(i,j) ) != symbols.end() ) || touch; 
      }
    }

    if ( touch )
      sum += it_numbers->second;

    it_numbers++;
  }

  it_numbers = numbers.begin();
  while ( it_numbers != numbers.end() )
  {
    int x; int y; int num; int digits { 1 }; 
    x=it_numbers->first.first;
    y=it_numbers->first.second;
    num=it_numbers->second;

    if ( numbers.find( std::make_pair(x,y-1) ) != numbers.end() )
    {
      it_numbers++;
      continue;
    }

    while( num /= 10 )
      digits++;

    for ( int i=1; i<digits ; i++ ) 
      numbers[std::make_pair(x,y+i)]=it_numbers->second;
    
    it_numbers++;
  }

  int gearsum {};

  it_gears = gears.begin();
  while ( it_gears != gears.end() )
  {
    int x {}; int y {};
    std::set<int> ts;

    x = it_gears->first;
    y = it_gears->second;

    for ( int i = x-1; i< x+2; i++ )
    {
      for ( int j = y-1; j< y+2; j++ )
      {
         if ( numbers.find( std::make_pair(i,j) ) != numbers.end() )
         {
           ts.insert( numbers[std::make_pair(i,j)] );
         }
      }
    }

    if ( ts.size() == 2 )
    {
      int val { 1 };

      for ( std::set<int>::iterator i = ts.begin(); i != ts.end(); i++) 
      {
        val *= *i;
      }

      gearsum += val;
    }
    

    it_gears++;
  }

    

  std::cout << "sum = " << sum << std::endl;
  std::cout << "gearsum = " << gearsum << std::endl;
}