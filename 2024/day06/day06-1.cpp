#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

using std::cout;
using std::endl;

using std::ifstream;
using std::string;
using std::vector;

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day06.test");
    string str;
    int answer1 {0};
    int answer2 {0};

    vector<vector<char>> map;
    int xp {0};
    int yp {0};
    int sxp {0};
    int syp {0};
    int dxp (-1);
    int dyp {0};

    while ( getline( is, str ))
    {  
        vector<char> tpmap;
        for ( char c : str )
        {
            if ( c == '^' )
            {
              xp = map.size();
              sxp =  xp;
              yp = tpmap.size();   
              syp = yp;
            }
            tpmap.push_back(c);
        }
        map.push_back( tpmap );   
    }
    is.close();

    while ( (xp >= 0) && (yp >= 0) && (xp < map.size()) && (yp<map[0].size() ) )
    {
        if ( (xp+dxp >= 0) && (yp+dyp >= 0) && (xp+dxp < map.size()) && (yp+dyp<map[0].size() ) && map[xp+dxp][yp+dyp]=='#')
        {
            // change direction y,-x
            int tdp = dxp;
            dxp = dyp;
            dyp = -tdp;
            map[xp][yp] = '+';
            continue;
        }

        if ( map[xp][yp]!='x' 
            && map[xp][yp]!='n' 
            && map[xp][yp]!='e' 
            && map[xp][yp]!='s' 
            && map[xp][yp]!='w' 
            && map[xp][yp]!='*' 
            //&& map[xp][yp]!='+'
            )
        {
            answer1++;
            if ( dxp == -1 && dyp  == 0)
            {
                map[xp][yp] = 'n';

                if ( xp >= 2 )
                {
                    int i=0;
                    int d2xp = dyp;
                    int d2yp = -dxp;
                    while (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='e'
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='#')
                    {
                        i++;
                    }

                    if (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]=='e'
                    )
                    {
                        cout << "O1(" << xp+2*dxp << "," <<  yp + 2*dyp << ")" << endl;
                        answer2++;
                    }
                }
            }
            
            if ( dxp == 0 && dyp  == 1)
            {
                map[xp][yp] = 'e';
                if ( yp+2 < map[0].size() )
                {
                    int i=0;
                    int d2xp = dyp;
                    int d2yp = -dxp;
                    while (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='s'
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='#')
                    {
                        i++;

                    }

                    if (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]=='s'
                    )
                    {
                        cout << "O1(" << xp+2*dxp << "," <<  yp + 2*dyp << ")" << endl;
                        answer2++;
                    }
                }
            }
            if ( dxp == 1 && dyp  == 0)
            {
                map[xp][yp] = 's';
                if ( xp+2 < map.size() )
                {
                    int i=0;
                    int d2xp = dyp;
                    int d2yp = -dxp;
                    while (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='w'
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='#')
                    {
                        i++;
                    }

                    cout << map[xp+dxp+i*d2xp][yp+dyp+i*d2yp] << "-" << xp+dxp+i*d2xp << '-' << yp+dyp+i*d2yp << endl;

                    if (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]=='w'
                    )
                    {
                        cout << "O1(" << xp+2*dxp << "," <<  yp + 2*dyp << ")" << endl;
                        answer2++;
                    }
                }
            }
            if ( dxp == 0 && dyp  == -1)
            {
                map[xp][yp] = 'w';
                if ( yp >= 2 )
                {
                    int i=0;
                    int d2xp = dyp;
                    int d2yp = -dxp;
                    while (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='n'
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]!='#')
                    {
                        i++;

                    }

                    if (
                        xp+dxp+i*d2xp >= 0
                        && yp+dyp+i*d2yp >= 0
                        && xp+dxp+i*d2xp < map.size()
                        && yp+dyp+i*d2yp < map[0].size()
                        && map[xp+dxp+i*d2xp][yp+dyp+i*d2yp]=='n'
                    )
                    {
                        cout << "O1(" << xp+2*dxp << "," <<  yp + 2*dyp << ")" << endl;
                        answer2++;
                    }
                }
            }
        }
        else if (map[xp][yp]=='+')
        {
            answer1++;
        }
        else
            map[xp][yp] = '*';

        xp+=dxp;
        yp+=dyp;

    }
    
    for ( auto row: map)
    {
        for ( auto col: row)
        {
            cout << col;
        }
        cout << endl;
    }
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}