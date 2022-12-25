#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  // open the file
  ifstream is("day18.input");
  string str;

  int mix=255,miy=255,miz=255,max=0,may=0,maz=0;

  int lavadrop[22][22][22];
  for ( auto i=0; i<22; i++)
    for ( auto j=0; j<22; j++)
      for ( auto k=0; k<22; k++)
        lavadrop[i][j][k] = 0;
    
  while ( getline( is, str ) )
  {
    istringstream iss(str);
    string sstr;
    int idx=0;
    int x,y,z;

    while ( getline( iss, sstr, ',' ) )
    {
      int tmp = stoi(sstr);
      if (idx==0)
      {
        if ( tmp < mix ) mix = tmp;
        if ( tmp > max ) max = tmp;
        x = tmp;
      }
      if (idx==1)
      {
        if ( tmp < miy ) miy = tmp;
        if ( tmp > may ) may = tmp;
        y = tmp;
      }
      if (idx==2)
      {
        if ( tmp < miz ) miz = tmp;
        if ( tmp > maz ) maz = tmp;
        z = tmp;
      }
      idx++;
    }

    cout << x << ',' << y << ',' << z <<  endl;
    lavadrop[x][y][z] = 1;
  }

  for ( auto i=0; i<22; i++)
    for ( auto j=0; j<22; j++)
      for ( auto k=0; k<22; k++)
      {
        if ( lavadrop[i][j][k]>0 )
        {
          if ( i==21 || lavadrop[i+1][j][k] <= 0 )
            lavadrop[i][j][k]++;
          if ( i==0 || lavadrop[i-1][j][k] <= 0 )
            lavadrop[i][j][k]++;
          if ( j==21 || lavadrop[i][j+1][k] <= 0 )
            lavadrop[i][j][k]++;
          if ( j==0 || lavadrop[i][j-1][k] <= 0 )
            lavadrop[i][j][k]++;
          if ( k==21 || lavadrop[i][j][k+1] <= 0 )
            lavadrop[i][j][k]++;
          if ( k==0 || lavadrop[i][j][k-1] <= 0 )
            lavadrop[i][j][k]++;
        }
      }

  int total=0;        
  for ( auto i=0; i<22; i++)
    for ( auto j=0; j<22; j++)
      for ( auto k=0; k<22; k++)
      {
        if ( lavadrop[i][j][k] > 0 )
          total += (lavadrop[i][j][k] -1);
      }
      
  cout << "P1:" << total << endl;
  //close the file
  is.close();
}
