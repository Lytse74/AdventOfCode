#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
  // open the file
  std::ifstream is("day01.input");
  std::string str;
  std::string res;
  int f=-1, l=-1;
  int sum=0; int pos=0;

  while ( getline( is, str ) )
  {
    while ( (pos = str.find("zero")) != std::string::npos )
      str.replace( pos+2, 0, "0" );
    while ( (pos = str.find("one")) != std::string::npos )
      str.replace( pos+2, 0, "1" );
    while ( (pos = str.find("two")) != std::string::npos )
      str.replace( pos+2, 0, "2" );
    while ( (pos = str.find("three")) != std::string::npos )
      str.replace( pos+2, 0, "3" );
    while ( (pos = str.find("four")) != std::string::npos )
      str.replace( pos+2, 0, "4" );
    while ( (pos = str.find("five")) != std::string::npos )
      str.replace( pos+2, 0, "5" );
    while ( (pos = str.find("six")) != std::string::npos )
      str.replace( pos+2, 0, "6" );
    while ( (pos = str.find("seven")) != std::string::npos )
      str.replace( pos+2, 0, "7" );
    while ( (pos = str.find("eight")) != std::string::npos )
      str.replace( pos+2, 0, "8" );
    while ( (pos = str.find("nine")) != std::string::npos )
      str.replace( pos+2, 0, "9" );
    
    f=str.find_first_of("0123456789");
    l=str.find_last_of("0123456789");

    res = str.substr(f,1) + str.substr(l,1);

    sum += stoi( res );

    std::cout << str << f << l << "r" << res << "s" << sum << std::endl;
  }

  std::cout << "sum = " << sum << std::endl;

  is.close();
}
