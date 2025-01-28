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

long long blink( int nr, list<string> st )
{
    long long res = 0;

    if (nr==0)
        res = st.size();
    else
    for ( auto s:st)
    {
        if ( s == "0")
        {
            s = "1";
            list<string> nls;
            nls.push_back(s);
            res += blink(nr-1,nls);
        }
        else
        if ( ((s).length()) & 1 )
        {
            // odd
            s = std::to_string(std::stoll(s)*2024);
            list<string> nls;
            nls.push_back(s);
            res += blink(nr-1,nls);
        }
        else
        {
            // even
            int ln = (s).length()/2;
            list<string> nls;
            string newstr = (s).substr(0,ln);
            nls.push_back(newstr);
            s = std::to_string(std::stoll((s).substr(ln,ln)));
            nls.push_back(s);
            res += blink(nr-1,nls);
        }
    }

    return res;
}

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

    // blink
    answer1 = blink(25,stones);
    answer2 = blink(30,stones);

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}
