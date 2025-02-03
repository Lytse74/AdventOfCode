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

enum BlockType  { Wall, Robot, Supplies };

bool strategySupplies( char move, set<tuple<int,int,BlockType>> & blocks, set<tuple<int,int,BlockType>>::iterator & supplies )
{
    bool ret = true;
    int dr {0}, dc {0};

    switch( move )
    {
        case '^':
            dr = -1; dc = 0;
            break;
        case '<':
            dr = 0;  dc = -1;
            break;
        case 'v':
            dr = 1;  dc = 0;
            break;
        case '>':
            dr = 0; dc = 1;
            break;
        default:
            return false;
            break;
    }
    
    set<tuple<int,int,BlockType>>::iterator object = blocks.begin();
    while ( object != blocks.end() )
    {
        if ( get<0>(*object)-dr == get<0>(*supplies) 
            && get<1>(*object)-dc == get<1>(*supplies) )
        {
            if ( get<2>(*object) == Wall )
            {
                ret = false;
                break;
            }
            else if ( get<2>(*object) == Supplies )
            {
                ret = strategySupplies( move, blocks, object );
            }
        }
        object++;
    }

    if (ret)
    {
        tuple<int,int,BlockType> t = *supplies;
        blocks.erase(supplies);
        get<0>(t) += dr;
        get<1>(t) += dc;
        blocks.insert(t);
        for ( supplies = blocks.begin(); supplies != blocks.end(); supplies++ )
        {
            if ( get<0>(*supplies) == get<0>(t) && get<1>(*supplies) == get<1>(t) && get<2>(*supplies) == Robot )
                break;
        }
    }

    return ret;
}

bool strategyRobot( char move, set<tuple<int,int,BlockType>> & blocks, set<tuple<int,int,BlockType>>::iterator & robot )
{
    bool ret = true;
    int dr {0}, dc {0};

    switch( move )
    {
        case '^':
            dr = -1; dc = 0;
            break;
        case '<':
            dr = 0;  dc = -1;
            break;
        case 'v':
            dr = 1;  dc = 0;
            break;
        case '>':
            dr = 0; dc = 1;
            break;
        default:
            return false;
            break;
    }
    
    set<tuple<int,int,BlockType>>::iterator object = blocks.begin();
    while ( object != blocks.end() )
    {
        if ( get<0>(*object)-dr == get<0>(*robot) 
            && get<1>(*object)-dc == get<1>(*robot) )
        {
            if ( get<2>(*object) == Wall )
            {
                ret = false;
                break;
            }
            else if ( get<2>(*object) == Supplies )
            {
                ret = strategySupplies( move, blocks, object );
            }
        }
        object++;
    }

    if (ret)
    {
        tuple<int,int,BlockType> t = *robot;
        blocks.erase(robot);
        get<0>(t) += dr;
        get<1>(t) += dc;
        blocks.insert(t);
        for ( robot = blocks.begin(); robot != blocks.end(); robot++ )
        {
            if ( get<0>(*robot) == get<0>(t) && get<1>(*robot) == get<1>(t) && get<2>(*robot) == Robot )
                break;
        }
    }


    return ret;
}


bool hanldeMove( char move, set<tuple<int,int,BlockType>> & blocks, set<tuple<int,int,BlockType>>::iterator & robot )
{
    bool ret = strategyRobot( move, blocks, robot );
    return ret;

}

void print( set<tuple<int,int,BlockType>> block )
{
    int c {0};
    int nc {0};
    for ( auto b : block )
    {
        if ( get<1>(b) == 0 )
        {
            cout << endl;
            c = 0;
        }
        if ( get<2>(b) == Wall )
        {
            nc = get<1>(b);

            while (c++<nc)
                cout << '.';
            
            cout << '#';
        }
        else if ( get<2>(b) == Supplies )
        {
            nc = get<1>(b);

            while (c++<nc)
                cout << '.';
            
            cout << 'O';
        }
        else if ( get<2>(b) == Supplies )
        {
            nc = get<1>(b);

            while (c++<nc)
                cout << '.';
            
            cout << 'O';
        }
        else if ( get<2>(b) == Robot )
        {
            nc = get<1>(b);

            while (c++<nc)
                cout << '.';
            
            cout << '@';
        }
    }
    cout << endl;
}
int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day15.test1");
    
    string str;
    long long answer1 {0};
    long long answer2 {0};

    set<tuple<int,int,BlockType>> blocks;
    vector<string> commands;
    set<tuple<int,int,BlockType>>::iterator robot;
    int rc {0}, rr {0};
    int r {0}, c {0};

    while ( getline( is, str  ))
    {
        if ( str.empty() )
            break;

        c=0;
        for (auto ch : str )
        {
            if (ch=='.')
            {
            }
            else if (ch=='#')
                blocks.insert(make_tuple( r, c, Wall ));
            else if (ch=='O')
                blocks.insert(make_tuple( r, c, Supplies ));
            else if (ch=='@')
            {
                blocks.insert(make_tuple(r,c,Robot));
                for ( robot = blocks.begin(); robot != blocks.end(); robot++ )
                {
                    if ( get<0>(*robot) == r && get<1>(*robot) == c && get<2>(*robot) == Robot )
                        break;
                }
            }
            c++;
        }

        r++;
    }
    while ( getline( is, str  ))
    {
        commands.push_back(str);
    }
    is.close();



    for (  auto cmds : commands )
    {
        for ( auto cmd : cmds )
        {
            bool ret = false;
            ret = hanldeMove( cmd, blocks, robot );
            cout << "Robot @" << get<0>(*robot) << "," << get<1>(*robot) << " did " << (ret?"":"not ") << "move on " << cmd << endl;
            //std::sort(blocks.begin(),blocks.end());
            print( blocks );
        }
    }

    for ( auto b: blocks)
    {
        if ( get<2>(b) == Supplies )
        {
            answer1 += (100 * get<0>(b) + get<1>(b));
        }

    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
