#include <fstream>
#include <iostream>
#include <string>
#include <sstream>




int main() {
  // open the file
  std::ifstream is("day02.input");
  std::string str;

  const int maxred = 12;
  const int maxgreen = 13;
  const int maxblue = 14;

  int cnt = 0;
  int powers = 0;


  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;

    int idx = 0;
    int game = -1;
    int nr = -1;

    enum Color { red, green, blue };
    Color color;

    bool possible = true;

    int nrofred = 0, nrofgreen=0, nrofblue=0;
    int minred = 0, mingreen=0, minblue=0;
    
    while ( getline( iss, sstr, ' ' ) )
    {
      if ( idx == 1 )
      {
        game = std::stoi( sstr );
        std::cout << "game = " << game << std::endl;
      }
      else
      {
        if ( idx > 0 && !(idx & 0x1 ) )
        {
          nr = stoi( sstr );
          //std::cout << "nr = " << nr << std::endl;
        }
        else 
        {
          if ( idx > 0 )
          {
            if ( sstr == "red" || sstr == "red;" || sstr == "red," )
              color = red;
            if ( sstr == "green" || sstr == "green;" || sstr == "green," )
              color = green;
            if ( sstr == "blue" || sstr == "blue;" || sstr == "blue," )
              color = blue;

            //std::cout << "color = " << color << std::endl;
            
            switch ( color )
            {
              case red:
                nrofred = nr;
                if ( nr > maxred ) possible = false;
                break;
              case green:
                nrofgreen = nr;
                if ( nr > maxgreen ) possible = false;
                break;
              case blue:
                nrofblue = nr;
                if ( nr > maxblue ) possible = false;
                break;
            }
            
            if ( sstr.find_first_of(";") != std::string::npos || iss.eof() )
            {
              std::cout << "red = " << nrofred << " green = " << nrofgreen << " blue = " << nrofblue;
              if (nrofred > minred ) minred = nrofred;
              if (nrofgreen > mingreen ) mingreen = nrofgreen;
              if (nrofblue > minblue ) minblue = nrofblue;
              std::cout << " ROUND" << std::endl;
            }
          }
        }
      }
      idx++;
    }
    if ( possible )
      cnt += game;

    std::cout << "mred = " << minred << " mgreen = " << mingreen << " blue = " << minblue;
    int power = minred*mingreen*minblue;
    std::cout << " power = " << power << std::endl;

    powers+=power;

    std::cout << std::endl;
  }
  std::cout << "count = " << cnt << std::endl;
  std::cout << "powers = " << powers << std::endl;

  is.close();
}