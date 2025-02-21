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
using std::tuple;
using std::make_tuple;
using std::get;

const int N=71;
const int M=71;


int floodFill ( vector<vector<int>> m )
{
    // start at 0,0

    set<pair<int,int>> h;
    h.insert(make_pair(0,0));
    m[0][0]=1;

    int c=0;

    while(!h.empty())
    {
        auto i = h.begin();
        if ( i->first>0 )
        {
            if ( m[i->first-1][i->second]==0
            || m[i->first-1][i->second]>0 && m[i->first][i->second]+1<m[i->first-1][i->second] )
            {
                m[i->first-1][i->second] = m[i->first][i->second] + 1;
                h.insert( make_pair(i->first-1,i->second));
            }
        }
        if ( i->first<N-1 )
        {
            if ( m[i->first+1][i->second]==0
              || m[i->first+1][i->second]>0 && m[i->first][i->second]+1<m[i->first+1][i->second] )
            {
                m[i->first+1][i->second] = m[i->first][i->second] + 1;

                h.insert( make_pair(i->first+1,i->second));

            }
        }
        if ( i->second>0 )
        {
            if ( m[i->first][i->second-1]==0
              || m[i->first][i->second-1]>0 && m[i->first][i->second]+1<m[i->first][i->second-1] )
            {
                m[i->first][i->second-1] = m[i->first][i->second] + 1;
                h.insert( make_pair(i->first,i->second-1));
            }
        }
        if ( i->second<M-1 )
        {
            if ( m[i->first][i->second+1]==0
              || m[i->first][i->second+1]>0 && m[i->first][i->second]+1<m[i->first][i->second+1] )
            {
                m[i->first][i->second+1] = m[i->first][i->second] + 1;
                h.insert( make_pair(i->first,i->second+1));
            }
        }
        h.erase(i);
        c++;
    }

//    cout << "erases=" << c << endl;


    return m[N-1][M-1]-1;

}

int main()
{
    ifstream is("day18.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    vector<vector<int>> map;
    vector<pair<int,int>> bytes;

    while ( getline( is, str  ))
    {
        istringstream iss(str);
        string sstr;
        int row {-1};
        int col {-1};
        getline( iss, sstr, ',');
        row = std::stoi(sstr);
        getline( iss, sstr, ',');
        col = std::stoi(sstr);
        bytes.push_back(make_pair(row,col));
    }

    for (auto n=0; n<N; n++)
    {
        vector<int> row;
        for ( auto m=0; m<M; m++)
        {
            row.push_back(0);
        }
        map.push_back(row);
    }

    // first 12 bytes
    for( auto b=0; b< 1024; b++ )
    //for( auto b=0; b< 1024; b++ )
    {
        map[bytes[b].first][bytes[b].second]--;
    }

    for ( auto r: map)
    {
        for ( auto c: r)
        {
            if (c<0)
            {
                if (c==-2)
                    cout << 'x';
                else
                    cout << '#';
            }
            else if (c==0)
                cout << '.';
            else
                cout << c%10;
        }
        
        cout << endl;
    }

    answer1=floodFill(map);

    int b=1024;
    while(floodFill(map)>0)
    {
        map[bytes[b].first][bytes[b].second]--;
        b++;
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << bytes[b-1].first <<  "," << bytes[b-1].second << endl;
 
    return 0;
}
