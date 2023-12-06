#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

// floor of square root of n 
long long ceilSqrt(long long n) 
{ 
    // Base cases 
    if (n == 0 || n == 1) 
    return n; 
    
    long long i = 1, result = 1; 
    while (result <= n) 
    { 
      i++; 
      result = i * i; 
    } 
    return i; 
} 

long long WaysToBeat( long long time, long long record )
{
  long long cnt {};

  // i² - time *i + record
  // D = time * time - 4 * record
  // x = ( time - ,/ D  ) / 2
  // x = ( time + ,/ D  ) / 2 

  long long D = time * time - record;
  //cout << "D = "  << D << " floor = " << ceilSqrt( D ) << endl;
  long long ib = ( time - ceilSqrt( D ) ) / 2;
  long long ie = ( time + ceilSqrt( D ) ) / 2;

  for ( auto i=ib; i<= ie; i++ )
  { 
    long long val {};
    val = i * ( time - i );

    if ( val > record )
    {
      //cout << i <<"->"<< val << endl;
      cnt++;
    }
  }
   
  return cnt;
}

int main() {
  // open the file
  std::ifstream is("day06.input");
  std::string str;

  std::vector<long long> time;
  std::vector<long long> record;
  long long stime {};
  long long srecord {};

  int idxo {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    int idxi {};

    while ( getline( iss, sstr, ':' ) )
    {
      if (  idxi == 1 )
      {
        std::istringstream isss(sstr);
        long long val {};
        std::string special = sstr;

        special.erase(std::remove_if(special.begin(), special.end(), isspace), special.end());
        cout << "special = " << special << endl;
        if ( idxo == 0 )
          stime = std::stoll(special);
        if ( idxo == 1 )
          srecord = std::stoll(special);

        while ( isss >> val )
        {
          if ( idxo == 0 )
            time.push_back( val );
          if ( idxo == 1 )
            record.push_back( val );
        }
      }
      idxi++;
    }
    idxo++;
  }
  cout << endl;

  is.close();

  long long answer { 1 };

  for ( auto i=0; i< time.size(); ++i )
  {
    cout << time[i] << "," << record[i] << endl;
    cout << WaysToBeat( time[i], record[i] ) << endl;
    answer *= WaysToBeat( time[i], record[i] );
  }

  cout << "answer = " << answer << endl;

  cout << "answer2 = " << WaysToBeat( stime, srecord ) << endl;


}