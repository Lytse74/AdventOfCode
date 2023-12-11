#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>

using std::cout;
using std::endl;

int main() {
  // open the file
  std::ifstream is("day11.input");
  std::string str;

  int row {};
  int col {};
  std::set<std::pair<int,int>> glx;
  std::set<int> rows;
  std::set<int> icols;
  int mcol {};
  bool fGlx = false;
  std::vector<int> erows;
  std::vector<int> ecols;
  int e {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    col = 0;
    fGlx = false;


    while ( iss.get(ch) )
    {
      if ( ch == '#' )
      {
        glx.insert( std::make_pair( row,col ) );
        fGlx = true;
        icols.insert(col);
      }

      col++;
    }
    
    mcol = col;
    if (!fGlx)
      rows.insert(row);
    row++;
  }
  cout << endl;

  is.close();

  for ( auto i = 0; i<row; i++ )
  {
    if ( rows.find(i) != rows.end())
      e++;
    erows.push_back( e );
  }
  e = 0;
  for ( auto i = 0; i<mcol; i++ )
  {
    if ( icols.find(i) == icols.end())
      e++;
    ecols.push_back( e );
  }

  long long sum1 {};
  long long sum2 {};

  std::set<std::pair<int,int>> tglx = glx;
  for ( auto g1 : glx )
  {
    tglx.erase( g1 );
    for ( auto g2 : tglx)
    {
      long long dist1 {};
      long long dist2 {};
      int fac { 999999 };
      dist1 = std::abs(erows[g1.first]+g1.first - (erows[g2.first]+g2.first))+ std::abs(ecols[g1.second]+g1.second-(ecols[g2.second]+g2.second));
      dist2 = std::abs(fac*erows[g1.first]+g1.first - (fac*erows[g2.first]+g2.first))+ std::abs(fac*ecols[g1.second]+g1.second-(fac*ecols[g2.second]+g2.second));
      sum1 += dist1;
      sum2 += dist2;
    }
  }
  cout << "sum1 = " << sum1 <<endl;
  cout << "sum2 = " << sum2 <<endl;
}