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

    map<string,long long> stones;

    while ( getline( is, str ))
    {
        istringstream iss(str);
        string sstr;

        while ( getline( iss, sstr, ' '))
        {
            stones[sstr]++;
        }
    }

    is.close();

//    stones.clear();
//    stones.push_back("0");

    // blink
    map<string,long long>::iterator it_st;
    map<string,long long> stones2;

    for ( int i =0; i<75; i++)
    {
    for ( it_st = stones.begin(); it_st != stones.end(); it_st++ )
    {
        if ( it_st->first == "0")
            stones2["1"] += it_st->second;
        else

        if ( ((it_st->first).length()) & 1 )
        {
            // odd
            string tstr = std::to_string(std::stoll(it_st->first)*2024);
            stones2[tstr]+=it_st->second;
        }
        else
        {
            // even
            int ln = (it_st->first).length()/2;
            string newstr = (it_st->first).substr(0,ln);
            stones2[newstr]+=it_st->second;
            string tstr = std::to_string(std::stoll((it_st->first).substr(ln,ln)));
            stones2[tstr]+=it_st->second;
        }
    }

    stones.erase(stones.begin(),stones.end());
    stones = stones2;
    stones2.erase(stones2.begin(),stones2.end());

    if (i==24)
        for ( auto s1 :stones)
            answer1 += s1.second;
    }

    for ( auto s1 :stones)
    {
        answer2 += s1.second;
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
