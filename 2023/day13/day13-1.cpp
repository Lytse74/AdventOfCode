#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using std::cout;
using std::endl;

// https://stackoverflow.com/questions/47981/how-to-set-clear-and-toggle-a-single-bit
inline int bit_set(int number, int n) {
    return number | ((int)1 << n);
}

// https://www.geeksforgeeks.org/check-whether-two-numbers-differ-one-bit-position/
// function to check if x is power of 2
bool isPowerOfTwo(int x)
{
    // First x in the below expression is
    // for the case when x is 0
    return x && (!(x & (x - 1)));
}
 
// function to check whether the two numbers
// differ at one bit position only
bool differAtOneBitPos(int a,
                       int b)
{
    return isPowerOfTwo(a ^ b);
}




int main() {
  // open the file
  std::ifstream is("day13.input");
  std::string str;

  std::vector<std::vector<char>> field;
  std::vector<int> cols,rows;
  long long cprt1 {};
  long long cprt2 {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;

    std::vector<char> v;
    while ( iss.get(ch) )
    {
      v.push_back( ch );
    }

    if ( v.size() > 0 )
      field.push_back( v );
    
    if ( str == "" || is.peek() == EOF )
    { 
      cout << "calc w = " << field[0].size() << " h = " << field.size() << endl;

      for ( auto i=0; i<field.size(); i++ )
      {
        int vrow {};

        for ( auto j=0; j<field[i].size(); j++ )
        {
          if ( field[i][j] == '#' )
            vrow = bit_set( vrow, j );
        }
        //cout << "R" << i << vrow << " ";
        rows.push_back( vrow );
      }
      //cout << endl;
      
      for ( auto j=0; j<field[0].size(); j++ )
      {
        int vcol {};

        for ( auto i=0; i<field.size(); i++ )
        {
          if ( field[i][j] == '#' )
            vcol = bit_set( vcol, i );
        }
        cout << "C" << j << " " << vcol << " ";
        cols.push_back( vcol );
      }
      cout << endl;

      for ( auto j=0; j<cols.size()-1; j++)
      {
        if (cols[j] == cols[j+1] ) // possible mirror
        {
          bool mirror = true;
          for ( auto k=0; k<=j && j+k+1 < cols.size() ; k++ )
          {
            if ( cols[j-k] != cols[j+1+k] )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror )
          {
            cout << "C1 mirror " << j << endl;
            cprt1 += (j+1);
            break;
          }
        }
      }

      for ( auto j=0; j<cols.size()-1; j++)
      {
        if ( cols[j] == cols[j+1] || differAtOneBitPos( cols[j],cols[j+1] ) ) // possible mirror
        {
          bool mirror = true;
          int dcnt {};
          
          for ( auto k=0; k<=j && j+k+1 < cols.size() ; k++ )
          {
            if ( differAtOneBitPos( cols[j-k], cols[j+k+1] ) )
            {
              dcnt++;
            }
            else
            if ( cols[j-k] != cols[j+1+k] )
            // && !differAtOneBitPos( cols[j-k], cols[j+k+1] ) )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror && dcnt == 1)
          {
            cout << "C2 mirror " << j << endl;
            cprt2 += (j+1);
            break;
          }
        }
      }
/*
      bool diffused = false; 
      for ( auto j=0; j<cols.size()-1; j++)
      {
        bool diff = false;
        
        if ( !diffused && differAtOneBitPos( cols[j],cols[j+1] ) )
        {
          diffused = true;
          diff = true;
        }
        
        if (cols[j] == cols[j+1] || diff  ) //possible mirror
        {
          bool mirror = true;
          for ( auto k=0; k<=j && j+k+1 < cols.size() ; k++ )
          {
            if ( !diffused && differAtOneBitPos( cols[j-k],cols[j+1+k] ) )
            {
              diffused = true;
              diff = true;
            }

            if ( cols[j-k] != cols[j+1+k] && !diff )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror  && diffused && diff )
          {
            cout << "C3 mirror " << j << endl;
            cprt1 += (j+1);
            diffused = false;
            break;
          }
          diffused = false;
        }
      }
*/
      for ( auto i=0; i<rows.size()-1; i++)
      {
        if (rows[i] == rows[i+1] ) //possible mirror
        {
          bool mirror = true;
          for ( auto k=0; k<=i && i+k+1 < rows.size() ; k++ )
          {
            if ( rows[i-k] != rows[i+1+k] )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror )
          {
            cout << "R mirror " << i <<  endl;
            cprt1 += 100*(i+1);
            break;
          }
        }
      }
      for ( auto i=0; i<rows.size()-1; i++)
      {
        if (rows[i] == rows[i+1] || differAtOneBitPos( rows[i],rows[i+1] ) ) //possible mirror
        {
          bool mirror = true;
          int dcnt {};
          
          for ( auto k=0; k<=i && i+k+1 < rows.size() ; k++ )
          {
            if ( differAtOneBitPos( rows[i-k],rows[i+k+1] ) )
            {
              dcnt++;
            }
            else
            if ( rows[i-k] != rows[i+1+k] )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror && dcnt == 1 )
          {
            cout << "R mirror " << i <<  endl;
            cprt2 += 100*(i+1);
            break;
          }
        }
      }
/*
      for ( auto i=0; i<rows.size()-1; i++)
      {
        //bool diff = false;

        //if ( !diffused && differAtOneBitPos( rows[i],rows[i+1] ) )
        //{
       //   diffused = true;
         // diff = true;
        //}
        
        if (rows[i] == rows[i+1] )//|| diff ) //possible mirror
        {
          bool mirror = true;
          for ( auto k=0; k<=i && i+k+1 < rows.size() ; k++ )
          {
            //bool diff = false;

//            if ( !diffused && differAtOneBitPos( rows[i-k],rows[i+1+k] ) )
  //          {
    //          diffused = true;
      //        diff = true;
       //     }
            
            if ( rows[i-k] != rows[i+1+k] ) //&& !diff )
            { 
              mirror = false;
              break;
            }
          }
          if ( mirror )//&& diffused && diff )
          {
            cout << "R mirror " << i <<  endl;
            cprt1 += 100*(i+1);
            //diffused = false;
            break;
          }
          //diffused = false;
        }
      }
*/

      field.clear();
      rows.clear();
      cols.clear();
    }
  }
  cout << "count1 = " << cprt1 << endl;
  cout << "count2 = " << cprt2 << endl;

  is.close();
}
