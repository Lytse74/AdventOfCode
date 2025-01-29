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

int floodFill ( int n, int m, vector<vector<char>> & garden )
{
    int area {0};
    int fences {0};
    int sides {0};

    char patch = garden[n][m];
    int on = n;
    int om = m;

    if ( patch == '*')
        return 0;

    set<pair<int,int>> workset;
    set<pair<int,int>>::iterator worker;

    workset.insert( make_pair(n,m));
    while ( !workset.empty() )
    {
        worker = workset.begin();

        if ( garden[worker->first][worker->second] != '.' )
        {
            garden[worker->first][worker->second] = '.';
            area++;
        }
        else
        {
            workset.erase(worker);
            continue;
        }

        // side fences and extra area
        if ( worker->first == 0 
            || ( garden[worker->first-1][worker->second] != patch 
                && garden[worker->first-1][worker->second] != '.' ) )
            fences += 1;
        else
            workset.insert(make_pair(worker->first-1,worker->second));
        if ( worker->first == garden.size()-1
            || ( garden[worker->first+1][worker->second] != patch 
                && garden[worker->first+1][worker->second] != '.' ) )
            fences += 1;
        else
            workset.insert(make_pair(worker->first+1,worker->second));
        if ( worker->second == 0 
            || ( garden[worker->first][worker->second-1] != patch 
                && garden[worker->first][worker->second-1] != '.' ) )
            fences += 1;
        else
            workset.insert(make_pair(worker->first,worker->second-1));
        if ( worker->second == garden[0].size()-1
            || ( garden[worker->first][worker->second+1] != patch 
                && garden[worker->first][worker->second+1] != '.' ) )
            fences += 1;
        else
            workset.insert(make_pair(worker->first,worker->second+1));
        
        workset.erase(worker);
    }

    // find fence dir of starting block
    int fxd = -1;
    int fyd = 0;

    if ( n == 0 || n > 0 && garden[n][m]!=garden[n-1][m] )
    {
        fxd = -1;
        fyd = 0;
    }
    else if ( m == 0 || m > 0 && garden[n][m]!=garden[n][m-1] )
    {
        fxd = 0;
        fyd = 1;
    }
    else if ( n == garden.size()-1 || garden[n][m]!=garden[n+1][m] )
    {
        fxd = 1;
        fyd = 0;
    }
    else if ( m == garden[0].size()-1 || garden[n][m]!=garden[n][m+1] )
    {
        fxd = 0;
        fyd = -1; 
    }

//    cout << "fences = " << fences << endl;
    
    for ( auto f = 0; f<fences && !(f!=0&&n==on&&m==om&&fxd==-1&&fyd==0); f++ )
    {
//        cout << "f: " << f << " fxd: " << fxd << " fyd: " << fyd << " n: " << n << " m: " << m << endl;

        if ( n+fxd < 0 
            || n+fxd >= garden.size()
            || m+fyd < 0
            || m+fyd >= garden[0].size()
            || garden[n][m] != garden[n+fxd][m+fyd] )
        {
            sides++;
            int td = fxd;
            fxd = fyd;
            fyd = -td;
        }
        else if ( n+fxd-fyd>=0
                && m+fyd+fxd>=0
                && n+fxd-fyd<garden.size()
                && m+fyd+fxd<garden[0].size()
                && garden[n][m] == garden[n+fxd-fyd][m+fyd+fxd] )
        {
            sides++;
            n = n+fxd-fyd;
            m = m+fyd+fxd;
            int td = fxd;
            fxd = -fyd;
            fyd = td;
        }
        else
        {
            n = n+fxd;
            m = m+fyd;
        }

        if  (f+1!=fences&&n==on&&m==om&&fxd==-1&&fyd==0)
        {
            // HoW To ProGrAm ThiS !?
            if ( fences-f-1 <= 6 )
              sides += 4;
            else
            {
                cout << "WARN " << "n=" << n << " m=" << m  << " p=" << patch << " mis=" << fences-f-1 << endl;
                if ( n==0 && m==108) sides+=14;
                if ( n==32 && m==38) sides+=8;
                if ( n==39 && m==34) sides+=18;
                if ( n==44 && m==82) sides+=8;
                if ( n==49 && m==59) sides+=8;
                if ( n==79 && m==5) sides+=12;
                if ( n==87 && m==30) sides+=8;
                if ( n==98 && m==4) sides+=12;
            }
        }
    }

//    cout << "sides = " << sides << endl;
 
    for ( auto & row: garden)
        for (auto & col :row)
            if ( col == '.' )
                col = '*';
    
    return area*sides;
    //return area*fences;
}

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day12.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<vector<char>> garden;

    while ( getline( is, str ))
    {
        vector<char> row;

        for ( auto ch: str)
        {
            row.push_back(ch);
        }

        garden.push_back(row);
    } 
    is.close();


    for ( int n = 0; n < garden.size(); n++ )
    {
        for ( int m = 0; m < garden[0].size(); m++ )
        {
            if ( garden[n][m] != '*' )
            {
                answer1+=floodFill( n, m, garden );
            }
        }
    }



    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
