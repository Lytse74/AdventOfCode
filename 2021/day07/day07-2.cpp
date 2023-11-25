#include <fstream>
#include <iostream>
#include <vector>
#include <string>

long long Fuel( long long to, long long from)
{
  long long r;


  if ( to < from )
    r = (from - to);

  if ( to > from )
    r = (to - from);

  if ( to == from )
    r = 0;

  return ((r*r+r)/2);
}

int main() {
  // open the file
  std::ifstream is("day07.input");
   
  long long crab=-1;
  long long max_crab = -1;
  long long min_crab = 1000;


  std::vector<long long> crabs;

  while ( is >> crab )
  {
    std::cout << crab << std::endl;
    crabs.push_back( crab );

    if ( crab > max_crab ) max_crab = crab;
    if ( crab < min_crab ) min_crab = crab;

    if ( is.peek() == ',' )
      is.ignore();
  }
  std::cout << "cnt: " << crabs.size() << std::endl;
  std::cout << max_crab << std::endl;
  std::cout << min_crab << std::endl;
  
  //close the file
  is.close();

  long long min_fuel = (max_crab*max_crab*max_crab);
  long long min_fuel_pos = max_crab;

  for ( long long i = min_crab; i<= max_crab; ++i)
  {
    long long tot_fuel=0;
    for ( long long j=0; j< crabs.size() ; ++j )
    {
      tot_fuel += Fuel(i,crabs[j]);
      //std::cout << Fuel( i,crabs[j]) << std::endl;
    }
    //std::cout << i << " -> " << tot_fuel << std::endl;

    if ( tot_fuel < min_fuel )
    {
      min_fuel = tot_fuel;
      min_fuel_pos = i;
      std::cout<<".";
    }
  }

  std::cout << min_fuel_pos << " -> " << min_fuel << std::endl;

}
