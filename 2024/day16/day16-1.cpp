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
#include <iomanip>

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

enum Dir { N, S, E, W };

void tracks ( enum Dir dir, bool start, vector<vector<char>> & m, vector<vector<long long>> s, pair<long long,long long> e )
{
    if ( s[e.first][e.second] == -1 )
        return;
    
    m[e.first][e.second] = 'O';

    bool stepped = false;

    if ( s[e.first][e.second] == s[e.first-1][e.second]+1
        || (s[e.first][e.second] == s[e.first-1][e.second]-999)&&!start
         &&((s[e.first][e.second] == s[e.first+1][e.second]-1001)&&dir==N)
        || s[e.first][e.second] == s[e.first-1][e.second]+1001 )
    {
        tracks( N, false, m, s, make_pair( e.first-1, e.second ) );
        stepped = true;
    }
    if ( s[e.first][e.second] == s[e.first+1][e.second]+1
        ||  (s[e.first][e.second] == s[e.first+1][e.second]-999)&&!start
         &&(s[e.first][e.second] == s[e.first-1][e.second]-1001)&&dir==S
    ||  s[e.first][e.second] == s[e.first+1][e.second]+1001 )
    {
        tracks(S,false,  m, s, make_pair( e.first+1, e.second ) );
        stepped = true;
    }




    if ( s[e.first][e.second] == s[e.first][e.second-1]+1

       ||  (s[e.first][e.second] == s[e.first][e.second-1]-999)&&!start 
        &&  (s[e.first][e.second] == s[e.first][e.second+1]-1001)&&dir==W
    ||  s[e.first][e.second] == s[e.first][e.second-1]+1001 )
    {
        tracks(W,false, m, s, make_pair( e.first, e.second-1 ) );
        stepped = true;
    }
    if ( s[e.first][e.second] == s[e.first][e.second+1]+1
         ||  (s[e.first][e.second] == s[e.first][e.second+1]-999)&&!start 
        &&  (s[e.first][e.second] == s[e.first][e.second-1]-1001)&&dir==E
     ||  s[e.first][e.second] == s[e.first][e.second+1]+1001 )
    {
        tracks(E,false, m, s, make_pair( e.first, e.second+1 ) );
        stepped = true;
    }

    if (!stepped)
    {
        cout << e.first << "|" << e.second << endl;

        // only 124,9
        m[e.first+1][e.second] = 'O';
        
        tracks(dir, false,  m, s, make_pair( e.first+2, e.second ) );
    }
}

long long step( vector<vector<char>> & m, vector<vector<long long>> & s, long long v, enum Dir d, int r, int c )
{
    if ( s[r][c] != -1 && s[r][c]<=v) 
        return -2;
    else
    {
//if ( (s[r][c] %1000) < (v%1000) && s[r][c]!=-1)
//cout << r << "," << c << "|" << s[r][c] << "->" << v << endl;

        s[r][c] = v;
    }

    if( m[r][c]=='E')
        return s[r][c];

    map<Dir,long long> dirs;

    map<Dir,long long>::iterator it;
    
    // find the direction of posiiton
    if ( m[r-1][c]!='#' && d != S )
      dirs[N]=0;
    if ( m[r+1][c]!='#' && d != N )
      dirs[S]=0;
    if ( m[r][c+1]!='#' && d != W )
      dirs[E]=0;
    if ( m[r][c-1]!='#' && d != E )
      dirs[W]=0;

    // calc the steps
    for ( it = dirs.begin(); it!=dirs.end(); it++ )
    {
        int dr{0},dc{0};
        if (it->first == N )
            dr=-1;
        else if (it->first == S )
            dr=1;
        else if (it->first == E )
            dc=1;
        else if (it->first == W )
            dc=-1;

        if(  it->first == d )
            it->second = step(m, s, s[r][c]+1, d, r + dr, c + dc);
        else if (it->first == N && d != S )
            it->second = step(m, s, s[r][c]+1001, N, r + dr, c + dc);
        else if (it->first == S && d != N )
            it->second = step(m, s, s[r][c]+1001, S, r + dr, c + dc);
        else if (it->first == E && d != W )
            it->second = step(m, s, s[r][c]+1001, E, r + dr, c + dc);
        else if (it->first == W && d != E )
            it->second = step(m, s, s[r][c]+1001, W, r + dr, c + dc);
    } 
    
    return s[r][c];
}



int main()
{
    // first read the pairs of page ordering rule
    ifstream is("day16.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<vector<char>> maze;
    vector<vector<long long>> score;
    pair<int,int> s;
    pair<int,int> e;
    
    while ( getline( is, str  ))
    {
        vector<char> row;
        vector<long  long> row2;
        for (auto ch : str )
        {
            if (ch=='S')
                s = make_pair( maze.size(), row.size() );
            
            if (ch=='E')
                e = make_pair( maze.size(), row.size() );
            
            row.push_back(ch);
            row2.push_back(-1);
        }
        maze.push_back(row);
        score.push_back(row2);
    }
    is.close();

    step(maze, score,0, E, s.first, s.second);
    answer1 = score[e.first][e.second];

    tracks(S,true,maze,score,e);


    for ( auto row: maze )
    {
        for ( auto col: row )
        {
            if ( col == 'O' )
                answer2++;
            //cout << col;
        }
        //
        cout << endl;
    }
/*
    int rc {0}, cc {0};

    for ( auto row: score )
    {
        for ( auto col: row )
        {
            if ((rc>=0)&&(rc<17)&&(cc>=24)&&(cc<=38))
                cout << std::setw(6) << col;
            cc++;
        }
        if ((rc>=0)&&(rc<17))

            cout << endl;
        rc++; cc=0;
    }
    */
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 

    return 0;
}