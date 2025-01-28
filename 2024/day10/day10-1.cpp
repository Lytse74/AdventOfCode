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
    ifstream is("day10.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<vector<char>> map;
    vector<pair<pair<int,int>,int>> trailheads;

    while ( getline( is, str ))
    {
        vector<char> row;
        for (auto ch: str)
        {
            if ( ch == '0')
            {
                trailheads.push_back(make_pair(make_pair(map.size(),row.size()),50*map.size()+row.size()));
            }
            row.push_back(ch);
        }
        map.push_back( row );
    }
    is.close();

    for (int len=0; len<9; len++)
    {
        vector<pair<pair<int,int>,int>> trailheads2;
        for ( auto th:trailheads)
        {
            if ( th.first.first > 0 && map[th.first.first][th.first.second]+1 == map[th.first.first-1][th.first.second])
            {
                trailheads2.push_back( make_pair( make_pair( th.first.first-1, th.first.second), th.second ) );
            }
            if ( th.first.first < map.size()-1 && map[th.first.first][th.first.second]+1 == map[th.first.first+1][th.first.second])
            {
                trailheads2.push_back( make_pair( make_pair( th.first.first+1, th.first.second), th.second ) );
            }
            if ( th.first.second > 0 && map[th.first.first][th.first.second]+1 == map[th.first.first][th.first.second-1])
            {
                trailheads2.push_back( make_pair( make_pair( th.first.first, th.first.second-1), th.second ) );
            }
            if ( th.first.second < map[0].size()-1 && map[th.first.first][th.first.second]+1 == map[th.first.first][th.first.second+1])
            {
                trailheads2.push_back( make_pair( make_pair( th.first.first, th.first.second+1), th.second ) );
            }
        }
        trailheads.clear();
        trailheads = trailheads2;
        trailheads2.clear();
    }

    set<pair<pair<int,int>,int>> trailheads2;
    for ( auto th:trailheads)
       trailheads2.insert( th );

   answer1 = trailheads2.size();
   answer2 = trailheads.size();

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}
