#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

int main() {
  // open the file
  std::ifstream is("day08.input");
  std::string str;
  int cnt = 0;
  int sum = 0;

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    bool piped = false;
    std::map<std::string,int> m;
    std::map<int,std::string> mr;

    int val = 0;

    while ( getline( iss, sstr, ' ' ) )
    {
      std::sort( sstr.begin(), sstr.end() );
      if ( sstr == "|" )
      {
        piped = true;

        // find the 3
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 5 && value == -1)
          {
            std::string tmp = key + mr[1];
            std::sort(tmp.begin(),tmp.end());
            auto last = std::unique(tmp.begin(),tmp.end());
            tmp.erase(last, tmp.end());
            if ( tmp.length() == 5 )
            {
              m[key] = 3;
              mr[3] = key;
            }
          }
        }
        // find the 9
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 6 && value == -1)
          {
            std::string tmp = mr[3] + mr[4];
            std::sort(tmp.begin(),tmp.end());
            auto last = std::unique(tmp.begin(),tmp.end());
            tmp.erase(last, tmp.end());
            if ( tmp == key )
            {
              m[key] = 9;
              mr[9] = key;
            }
          }
        }
        // find the 5
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 5 && value == -1)
          {
            std::string tmp = key + mr[1];
            std::sort(tmp.begin(),tmp.end());
            auto last = std::unique(tmp.begin(),tmp.end());
            tmp.erase(last, tmp.end());
            if ( tmp == mr[9] )
            {
              m[key] = 5;
              mr[5] = key;
            }
          }
        }
        // find the 2
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 5 && value == -1)
          {
            m[key] = 2;
            mr[2] = key;
          }
        }
        // find the 6
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 6 && value == -1)
          {
            std::string tmp = key + mr[1];
            std::sort(tmp.begin(),tmp.end());
            auto last = std::unique(tmp.begin(),tmp.end());
            tmp.erase(last, tmp.end());
            if ( tmp == mr[8] )
            {
              m[key] = 6;
              mr[6] = key;
            }
          }
        }
        // find the 0
        for (const auto& [key, value] : m)
        {
          if ( key.length() == 6 && value == -1)
          {
            m[key] = 0;
            mr[0] = key;
          }
        }

      }

      int len = sstr.length();

      if ( !piped )
      {
        if (len==2) { m[sstr] = 1; mr[1] = sstr; }
        if (len==3) { m[sstr] = 7; mr[7] = sstr; }
        if (len==4) { m[sstr] = 4; mr[4] = sstr; }
        if (len==7) { m[sstr] = 8; mr[8] = sstr; }
        if (len==5) m[sstr] = -1;
        if (len==6) m[sstr] = -1;
      }

      if ( piped && sstr != "|" )
      {
        //std::cout << sstr << '-';
        val *= 10;
        std::cout << m[sstr] << '-';
        val += m[sstr];

        if ( m[sstr] == 1
          || m[sstr] == 7
          || m[sstr] == 4
          || m[sstr] == 8 )
        cnt++;
      }
    }
    for ( const auto& [key, value] : m)
      std::cout << '[' << key << "][" << key.length() << "] = " << value << "; ";
    std::cout << val;
    std::cout << std::endl;
    sum += val;
  }

  std::cout << "count = " << cnt << std::endl;
  std::cout << "sum = " << sum << std::endl;

  is.close();

}
