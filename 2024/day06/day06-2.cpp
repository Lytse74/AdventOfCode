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
    ifstream is("day06.input");
    string str;
    int answer1 {0};
    int answer2 {0};

    vector<vector<char>> map;
    int xp {0};
    int yp {0};
    int pxp {0};
    int pyp {0};
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


    vector<vector<char>> mapsave = map;
    bool inloop = false;
    
    for ( auto row=0; row<map.size(); row++)
    {
       for ( auto col=0; col<map[0].size(); col++)
        {
            map = mapsave;
            inloop = false;
            xp = sxp;
            dxp = -1;
            yp = syp;
            dyp = 0;
            answer1 = 0;
            
            if ( map[row][col]=='#')
                continue;
            else
                map[row][col]='#';
           
    while ( (xp >= 0) && (yp >= 0) && (xp < map.size()) && (yp<map[0].size() ) )
    {
        if ( (xp+dxp >= 0) && (yp+dyp >= 0) && (xp+dxp < map.size()) && (yp+dyp<map[0].size() ) && map[xp+dxp][yp+dyp]=='#')
        {
            // change direction y,-x
            int tdp = dxp;
            dxp = dyp;
            dyp = -tdp;
            if ( map[xp][yp] != '+' )
            {
                map[xp][yp] = '+';
                pxp = xp;
                pyp = yp;
                //cout << "+:"<<xp<<"_"<<yp<<endl;
                continue;
            }
            else if ( pxp != xp || pyp != yp )
            {
                inloop = true;
                break;
            }
        }

        if ( map[xp][yp]!='x' 
            //&& map[xp][yp]!='n' 
            //&& map[xp][yp]!='e' 
            //&& map[xp][yp]!='s' 
            //&& map[xp][yp]!='w' 
            && map[xp][yp]!='*' 
            && map[xp][yp]!='+'
            )
        {
            map[xp][yp]='x';
            answer1++;
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

    if ( inloop == true )
    {
        answer2++;
        cout << row << "-" << col << endl;
    }
    }
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