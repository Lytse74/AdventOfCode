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

int N {0};
int M {0};

int floodFill ( pair<int,int> s, pair<int,int> e, vector<vector<int>> & m )
{
    // start at 0,0

    set<pair<int,int>> h;
    h.insert(s);
    m[s.first][s.second]=1;

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


    return m[e.first][e.second]-1;

}

int shortcuts2( vector<vector<int>> m)
{
    map<int,int> use;
    for ( int i=1; i<N-1; i++ )
    {
        for ( int j=1; j<M-1; j++ )
        {
            if ( m[i][j]==-1 && m[i+1][j]!=-1 && m[i-1][j] !=-1 ) 
            {
                int v = m[i+1][j] - m[i-1][j];
                if (v<0) v = -v;
                use[v] += 1;
                //cout << i << "," << j << "|" << v << endl;
                //cout << m[i-1][j] << " " << m[i][j] << " " << m[i+1][j] << endl;          
            }
            if ( m[i][j]==-1 && m[i][j+1]!=-1 && m[i][j-1] !=-1 ) 
            {
                int v = m[i][j+1] - m[i][j-1];
                if (v<0) v = -v;
                use[v] += 1;
                //cout << i << "," << j << "|" << v << endl;
            }
        }
    }

    int ret = 0;
    for ( auto u : use)
    {
        if ( u.first >= 102 )
            ret += u.second;
    }

    return ret;
}

int shortcuts20( vector<vector<int>> m)
{
    map<int,int> use;
    for ( int i=0; i<N; i++ )
    {
        for ( int j=0; j<M; j++ )
        {
            for ( int k=2; k<=20; k++ )
            {
                for ( int p=0; p<k; p++ )
                {
                    if ( i<N-(k-p) && j<M-p && m[i][j]!=-1 && m[i+(k-p)][j+p]!=-1)
                    {
                        int v = m[i][j] - m[i+(k-p)][j+p];
                        if (v<0) v = -v;
                        if (v>k)
                            use[v-k] += 1;
                    }
                    if ( i<N-p && j<M-(k-p) && m[i+p][j]!=-1 && m[i][j+(k-p)]!=-1 )
                    {
                        int v = m[i+p][j] - m[i][j+(k-p)];
                        if (v<0) v = -v;
                        if (v>k)
                            use[v-k] += 1;
                    }

                }
            }
        }
    }

    int ret = 0;
    for ( auto u : use)
    {
        if ( u.first >= 100 )
            ret += u.second;
    }

    return ret;
}
int main()
{
    ifstream is("day20.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    vector<vector<int>> map;
    pair<int,int> s;
    pair<int,int> e;

    while ( getline( is, str  ))
    {
        vector<int> row;
        for ( auto c : str )
        {
            if ( c == '#' )
                row.push_back(-1);
            else if ( c == 'S')
            {
                s = make_pair( map.size(), row.size() );
                row.push_back(0);
            }
            else if ( c == 'E')
            {
                e = make_pair( map.size(), row.size() );
                row.push_back(0);
            }
            else
                row.push_back(0);
        }
        map.push_back(row);
    }

    N = map.size();
    M = map[0].size();
        

    answer1=floodFill(s,e,map);

    answer1=shortcuts2(map);

    answer2=shortcuts20(map);

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

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
