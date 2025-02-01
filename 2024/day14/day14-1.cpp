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

void print( vector<pair<pair<int,int>,pair<int,int>>> r, int dx, int dy )
{
    std::sort(r.begin(),r.end());

    bool ok = true;

    vector<vector<char>> draw;
    for (int i=0; i<dx; i++)
    {
        vector<char> row;
        for ( int j=0; j<dy; j++)
        {
            row.push_back('.');
        }
        draw.push_back(row);
    }

    for (auto e:r)
    {
        draw[e.first.first][e.first.second]='*';
    }
    
    int cnt =  0;
    for (auto rr: draw)
    {
        for (auto cc: rr)
        {
            if ( cc == '*' )
                 cnt++;
        }
    }

//    if ( cnt < 500 )
  //      return;

    for (auto rr: draw)
    {
        for (auto cc: rr)
        {
            cout << cc;
        }
        cout << endl;
    }

    return;
}


int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day14.input");
    //int dimx = 11;
    int dimx = 101;
    //int dimy = 7;
    int dimy = 103;
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<pair<pair<int,int>,pair<int,int>>> robots;

    while ( getline( is, str ))
    {
        istringstream iss(str);
        string sstr;
        int idx=0;
        int px {0};
        int py {0};
        int vx {0};
        int vy {0};
        char ch;
        
        while ( getline( iss, sstr, '=' ) )
        {
            //cout << idx << ":" << sstr << endl;
            if (idx==0)
            {
                //positionn
                iss >> px;
                iss >> ch; //",";
                iss >> py;
            }
            else 
            {
                // velocity
                iss >> vx;
                iss >> ch; //",";
                iss >> vy;
            }
            idx++;
        }

        robots.push_back( make_pair(make_pair(px,py),make_pair(vx,vy)) );
    } 
    is.close();

    // the robots move
    print(robots,dimx,dimy);
    for(int m=0;m<10403;m++) {
    for (auto & r:robots)
    {
        r.first.first += (r.second.first *1);
        r.first.first %= dimx;
        if (r.first.first <0)
            r.first.first += dimx;
        r.first.second += (r.second.second *1);
        r.first.second %= dimy;
        if (r.first.second <0)
            r.first.second += dimy;
    }
    print(robots,dimx,dimy);
    cout << "moves = "  << m+1 << endl;
    }


    int q1 {0}, q2 {0}, q3 {0}, q4 {0};
    for (auto r:robots)
    {
        if ( r.first.first > dimx/2
        && r.first.second < dimy/2 )
            q1++;
        else if ( r.first.first < dimx/2
        && r.first.second < dimy/2 )
            q2++;
        else if ( r.first.first < dimx/2
        && r.first.second > dimy/2 )
            q3++;
        else if ( r.first.first > dimx/2
        && r.first.second > dimy/2 )
            q4++; 
    }                     
    answer1 = q1*q2*q3*q4;

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
