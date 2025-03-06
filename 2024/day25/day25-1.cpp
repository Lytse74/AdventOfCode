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
#include <bitset>

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




int main()
{
    ifstream is("day25.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    struct SchematicS {
        short pin1;
        short pin2;
        short pin3;
        short pin4;
        short pin5;
    };

    vector<SchematicS> keys;
    vector<SchematicS> locks;

    while ( getline( is, str  ))
    {
        vector<string> tmp;
        while ( !str.empty() )
        {
            tmp.push_back(str);
            getline( is,str );
        }

        SchematicS stmp;
        stmp.pin1 = (tmp[0][0]=='#')*1+(tmp[1][0]=='#')*2+(tmp[2][0]=='#')*4+(tmp[3][0]=='#')*8+(tmp[4][0]=='#')*16+(tmp[5][0]=='#')*32+(tmp[6][0]=='#')*64;
        stmp.pin2 = (tmp[0][1]=='#')*1+(tmp[1][1]=='#')*2+(tmp[2][1]=='#')*4+(tmp[3][1]=='#')*8+(tmp[4][1]=='#')*16+(tmp[5][1]=='#')*32+(tmp[6][1]=='#')*64;
        stmp.pin3 = (tmp[0][2]=='#')*1+(tmp[1][2]=='#')*2+(tmp[2][2]=='#')*4+(tmp[3][2]=='#')*8+(tmp[4][2]=='#')*16+(tmp[5][2]=='#')*32+(tmp[6][2]=='#')*64;
        stmp.pin4 = (tmp[0][3]=='#')*1+(tmp[1][3]=='#')*2+(tmp[2][3]=='#')*4+(tmp[3][3]=='#')*8+(tmp[4][3]=='#')*16+(tmp[5][3]=='#')*32+(tmp[6][3]=='#')*64;
        stmp.pin5 = (tmp[0][4]=='#')*1+(tmp[1][4]=='#')*2+(tmp[2][4]=='#')*4+(tmp[3][4]=='#')*8+(tmp[4][4]=='#')*16+(tmp[5][4]=='#')*32+(tmp[6][4]=='#')*64;

        if ( tmp[0] == "#####")
            locks.push_back(stmp);
        else
            keys.push_back(stmp);

        cout << "pin1 = " << stmp.pin1 << endl;
    }

    is.close();

    for ( auto k: keys )
    {
        for ( auto l: locks )
        {
            if ( (k.pin1 & l.pin1) == 0
                && (k.pin2 & l.pin2) == 0
                && (k.pin3 & l.pin3) == 0
                && (k.pin4 & l.pin4) == 0
                && (k.pin5 & l.pin5) == 0
            )
            {
                answer1++;
            }
        }
    }


    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = ";

    return 0;
}