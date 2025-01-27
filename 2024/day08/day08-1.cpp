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

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day08.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    map<char,vector<pair<int,int>>> antenna;
    set<pair<int,int>> antinodes;
    set<pair<int,int>> antinodes2;
    
    int irow {0};
    int icol {0};

    int mrow;
    int mcol;

    while ( getline( is, str ))
    {
        icol = 0;
        for ( auto ch: str )
        {
            if ( ch != '.' )
            {
                if ( antenna.count(ch) == 0 )
                {
                    vector<pair<int,int>> positions;
                    antenna[ch] = positions;
                }
                antenna[ch].push_back( make_pair( irow,icol ));
            }
            icol++;
        }
        mcol = icol;
        irow++;
    }
    mrow = irow;

    is.close();

    for ( auto v: antenna )
    {
        for ( auto n=0; n<v.second.size();n++)
        {
            for (auto m = n+1; m<v.second.size(); m++ )
            {
                int mir1 = v.second[n].first - v.second[m].first;
                int mir2 = v.second[n].second - v.second[m].second;

                antinodes.insert(make_pair(v.second[n].first+mir1,v.second[n].second+mir2));
                antinodes.insert(make_pair(v.second[m].first-mir1,v.second[m].second-mir2));

                for ( int t=0; t<mrow; t++)
                {
                    antinodes2.insert(make_pair(v.second[n].first+t*mir1,v.second[n].second+t*mir2));
                    antinodes2.insert(make_pair(v.second[m].first-t*mir1,v.second[m].second-t*mir2));
                }
            }
        }
    }

    for ( auto a: antinodes)
    {
        if ( a.first<mrow && a.first>=0 && a.second <mcol && a.second>=0)
            answer1++;
    }

    for ( auto a: antinodes2)
    {
        if ( a.first<mrow && a.first>=0 && a.second <mcol && a.second>=0)
            answer2++;
    }

    cout << "answer1 = " << answer1 << endl;;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}