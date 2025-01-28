#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <algorithm> 
#include <cctype>
#include <locale>

#include <vector>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#include <list>

using std::cout;
using std::endl;

using std::ifstream;
using std::string;
using std::vector;

using std::pair;
using std::istringstream;

using std::map;
using std::set;
using std::make_pair;
using std::list;

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day11.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    list<string> stones;

    while ( getline( is, str ))
    {
        istringstream iss(str);
        string sstr;

        while ( getline( iss, sstr, ' '))
        {
            stones.push_back(sstr);
        }
    }

    is.close();

//    stones.clear();
//    stones.push_back("0");

    // blink
    list<string>::iterator it_st;

    for ( int i =0; i<30; i++)
    {
    for ( it_st = stones.begin(); it_st != stones.end(); it_st++ )
    {
        if ( *it_st == "0")
            *it_st = "1";
        else

        if ( ((*it_st).length()) & 1 )
        {
            // odd
            *it_st = std::to_string(std::stoll(*it_st)*2024);
        }
        else
        {
            // even
            int ln = (*it_st).length()/2;
            string newstr = (*it_st).substr(0,ln);
            stones.insert(it_st,newstr);
            (*it_st) = std::to_string(std::stoll((*it_st).substr(ln,ln)));
        }
    }

    if (i==24)
        answer1 = stones.size();
    }

    answer2 = stones.size();

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    map<string,int> hist;
    for ( auto s1 :stones)
    {
        hist[s1]++;
    }

    return 0;
}
