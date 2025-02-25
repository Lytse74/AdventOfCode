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


string controlKeypad(string s)
{
    string ret;

    char k1 = 'A';

    // starts at A
    // +---+---+---+
    // | 7 | 8 | 9 |
    // +---+---+---+
    // | 4 | 5 | 6 |
    // +---+---+---+
    // | 1 | 2 | 3 |
    // +---+---+---+
        // | 0 | A |
        // +---+---+
        
    map<string,string> xlat = { 
        {"A0","<A"},{"A3","^A"},{"A1","^<<A"},{"A5","<^^A"},{"A7","^^^<<A"},{"A4","^^<<A"},{"A9","^^^A"},{"A3","^A"}
    ,   {"02","^A"},{"0A",">A"}
    ,   {"17","^^A"},{"14","^A"}
    ,   {"29",">^^A"},{"2A","v>A"}
    ,   {"37","<<^^A"},{"34","<<^A"},{"3A","vA"}
    ,   {"45",">A"},{"40",">vvA"},{"49","^>>A"},{"46",">>A"}
    ,   {"56",">A"},{"58","^A"}
    ,   {"6A","vvA"},{"63","vA"}
    ,   {"79",">>A"},{"78",">A"}
    ,   {"80","vvvA"},{"82","vvA"}
    ,   {"9A","vvvA"},{"98","<A"}  };


    for ( char k2: s )
    {
        string lookup;
        lookup.push_back(k1);
        lookup.push_back(k2);

        ret += xlat[lookup];

        k1 = k2;
    }

    return ret;
}

string controlDirectional(string s)
{
    string ret;

    char k1 = 'A';

    map<string,string> xlat = { 
        {"A^","<A"},{"A>","vA"},{"Av","<vA"},{"A<","v<<A"},{"AA","A"}
    ,   {"^^","A"},{"^>","v>A"},{"^v","vA"},{"^<","v<A"},{"^A",">A"}
    ,   {">^","<^A"},{">>","A"},{">v","<A"},{"><","<<A"},{">A","^A"}
    ,   {"v^","^A"},{"v>",">A"},{"vv","A"},{"v<","<A"},{"vA","^>A"}
    ,   {"<^",">^A"},{"<>",">>A"},{"<v",">A"},{"<<","A"},{"<A",">>^A"}
    };


        //+---+---+
        //| ^ | A |
    //+---+---+---+
    //| < | v | > |
    //+---+---+---+

    for ( char k2: s )
    {
        string lookup;
        lookup.push_back(k1);
        lookup.push_back(k2);

        ret += xlat[lookup];

        k1 = k2;
    }

    return ret;
}

string outputDirectional( string s )
{
    string ret;

    char state = 'A';

    for ( auto c: s )
    {
        switch ( state )
        {
            case 'A':
            {
                switch ( c )
                {
                    case 'A':
                    ret.push_back('A');
                    break;
                    case ' ':
                    ret.push_back(' ');
                    break;
                    case '<':
                    ret.push_back(' ');
                    state = '^';
                    break;
                    case 'v':
                    ret.push_back(' ');
                    state = '>';
                    break;
                    default:
                    ret.push_back('E');
                    break;
                }
            }
            break;
            case '>':
            {
                switch ( c )
                {
                    case 'A':
                    ret.push_back('>');
                    break;
                    case ' ':
                    ret.push_back(' ');
                    break;
                    case '<':
                    ret.push_back(' ');
                    state = 'v';
                    break;
                    case '^':
                    ret.push_back(' ');
                    state = 'A';
                    break;
                    default:
                    ret.push_back('E');
                    break;
                }
            }
            break;
            case '^':
            {
                switch ( c )
                {
                    case 'A':
                    ret.push_back('^');
                    break;
                    case ' ':
                    ret.push_back(' ');
                    break;
                    case '>':
                    ret.push_back(' ');
                    state = 'A';
                    break;
                    case 'v':
                    ret.push_back(' ');
                    state = 'v';
                    break;
                    default:
                    ret.push_back('E');
                    break;
                }
            }
            break;
            case 'v':
            {
                switch ( c )
                {
                    case 'A':
                    ret.push_back('v');
                    break;
                    case ' ':
                    ret.push_back(' ');
                    break;
                    case '>':
                    ret.push_back(' ');
                    state = '>';
                    break;
                    case '^':
                    ret.push_back(' ');
                    state = '^';
                    break;
                    case '<':
                    ret.push_back(' ');
                    state = '<';
                    break;
                    default:
                    ret.push_back('E');
                    break;
                }
            }
            break;
            case '<':
            {
                switch ( c )
                {
                    case 'A':
                    ret.push_back('<');
                    break;
                    case ' ':
                    ret.push_back(' ');
                    break;
                    case '>':
                    ret.push_back(' ');
                    state = 'v';
                    break;
                    default:
                    ret.push_back('E');
                    break;
                }
            }
            break;
            default:
            break;
        }
    }

    return ret;
}

int main()
{
    ifstream is("day21.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    vector<string> codes;

    while ( getline( is, str  ))
    {
        codes.push_back(str);
    }


    answer2=0;

    map<string,pair<long long, string>> lookup;


    for ( auto code:codes)
    {
        string keys = controlKeypad( code );
        string dir1 = controlDirectional( keys );
        string dir2 = controlDirectional( dir1 );
        string dir3 = controlDirectional( dir2 );
        string dir4 = controlDirectional( dir3 );

        std::size_t pos5 = 0;
        long long dir2len = 0;

        long long dir5len = 0;
        long long dir10len = 0;
        long long dir15len = 0;
        long long dir20len = 0;
        long long dir25len = 0;
        while (keys.find("A",pos5)!=std::string::npos)
        {
            std::size_t npos5 = keys.find("A",pos5);
            string dir5 = keys.substr(pos5,npos5-pos5+1);
            //cout  << dir5.length() << endl;
            for (int t = 1; t<=5; t++)
            {   
                dir5 = controlDirectional( dir5 );


                //cout << t <<  ".."<< dir5.length() << endl;
                if (t==2)
                    dir2len += dir5.length();
            }
            pos5 = npos5+1;
            dir5len += dir5.length();
            std::size_t pos10 = 0;
            while (dir5.find("A",pos10)!=std::string::npos)
            {
                std::size_t npos10 = dir5.find("A",pos10);
                string dir10 = dir5.substr(pos10,npos10-pos10+1);
                //cout << npos10 << "/" << dir5.length() << ":" << npos5 << "/" << keys.length() << endl;
                if ( lookup.find(dir10) != lookup.end() )
                {
                    dir10 = lookup[dir10].second;       
                }
                else
                {
                    for (int t = 6; t<=10; t++)
                    {   
                        dir10 = controlDirectional( dir10 );
                    }
                    lookup[dir5.substr(pos10,npos10-pos10+1)] = make_pair(dir10.length(),dir10 );
                }
                pos10 = npos10+1;
                dir10len += dir10.length();
                std::size_t pos15 = 0;
                while (dir10.find("A",pos15)!=std::string::npos)
                {
                    std::size_t npos15 = dir10.find("A",pos15);
                    string dir15 = dir10.substr(pos15,npos15-pos15+1);
         
                    if ( lookup.find(dir15) != lookup.end() )
                    {
                        dir15 = lookup[dir15].second;       
                    }
                    else
                    {
                        for (int t = 11; t<=15; t++)
                        {   
                            dir15 = controlDirectional( dir15 );
                        }
                        lookup[dir10.substr(pos15,npos15-pos15+1)] = make_pair(dir15.length(),dir15 );
                    }
                    pos15 = npos15+1;
                    dir15len += dir15.length();
                    std::size_t pos20 = 0;
                    while (dir15.find("A",pos20)!=std::string::npos)
                    {
                        std::size_t npos20 = dir15.find("A",pos20);
                        string dir20 = dir15.substr(pos20,npos20-pos20+1);
                        if ( lookup.find(dir20) != lookup.end() )
                        {
                            dir20 = lookup[dir20].second;       
                        }
                        else
                        {
                            for (int t = 16; t<=20; t++)
                            {   
                                dir20 = controlDirectional( dir20 );
                            }
                            lookup[dir15.substr(pos20,npos20-pos20+1)] = make_pair(dir20.length(),dir20 );
                        }
                        pos20 = npos20+1;
                        dir20len += dir20.length();
                        std::size_t pos25 = 0;
                        while (dir20.find("A",pos25)!=std::string::npos)
                        {
                            std::size_t npos25 = dir20.find("A",pos25);
                            string dir25 = dir20.substr(pos25,npos25-pos25+1);
                            if ( lookup.find(dir25) != lookup.end() )
                            {
                                dir25 = lookup[dir25].second;       
                            }
                            else
                            {
                                for (int t = 21; t<=25; t++)
                                {   
                                    dir25 = controlDirectional( dir25 );
                                }
                                lookup[dir20.substr(pos25,npos25-pos25+1)] = make_pair(dir25.length(),dir25 );
                            }
                            pos25 = npos25+1;
                            dir25len += dir25.length();
                        }
                    }
                }
            }
        }
        //cout << code << " => " << keys << endl << " => " << dir1 << " => " << endl << dir2 << " (" << dir2.length() << ":" << dir3.length() << ")" << stoi(code) <<endl <<dir4<<endl;
        //cout << outputDirectional(dir4) << endl;/
        //cout << outputDirectional(outputDirectional(outputDirectional((dir4)))) << endl;
        //cout << outputDirectional(outputDirectional(outputDirectional(outputDirectional(dir4)))) << endl;
        answer1 += dir2.length()*stoi(code);

        answer2 += dir25len * stoi(code);
        //answer2 += dir2len*stoi(code);    
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
