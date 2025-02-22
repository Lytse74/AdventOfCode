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

#include <algorithm> 
#include <cctype>
#include <locale>

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
using std::tuple;
using std::make_tuple;
using std::get;

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

map<string,long long> lookup;

long long isCovered( string w, vector<string> ss )
{
    long long ret = 0;
    vector<string>::iterator it=ss.begin();

    if (lookup.find(w) != lookup.end())
        return lookup[w];

    while ( it!=ss.end() )
    { 
        std::size_t found = w.find(*it);

        if (found!=std::string::npos)
        {
            //cout<< " word: " << w << " symbol: " << *it << " found at: " << found << endl;
            if ( found == 0 )
            {
                if ( w.length()>(*it).length() )
                {
                    ret += isCovered( w.substr((*it).length()), ss );
                }
                else
                {
                    ret += 1;
                }
            }
            it++;
        }
        else
            it = ss.erase(it);
    }
    
    //cout<< "word: " << w << " ret: " << ret << endl;

    lookup[w]=ret;

    return ret;
}

int main()
{
    ifstream is("day19.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    vector<string> symbols;
    vector<string> words;

    getline(is,str);
    istringstream iss(str);
    string sstr;
    while( getline( iss, sstr, ','))
    {
        trim( sstr );
        symbols.push_back(sstr);
    }
    while ( getline( is, str  ))
    {
        if ( str.empty() )
            continue;
        words.push_back(str);
    }

    is.close();

    for ( auto w : words )
//    auto w = words[6];
    {
        cout << w << endl;
        long long ret = isCovered( w, symbols );
        if ( ret )
            answer1++;
        if ( ret )
            answer2 += ret;


        cout << " : " << ret << endl;
        lookup.erase(lookup.begin(),lookup.end());
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
