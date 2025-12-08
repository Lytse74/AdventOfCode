#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <tuple>
#include <map>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;
using std::tuple;
using std::set;
using std::make_tuple;
using std::map;

int main()
{
    ifstream is("day07.input");
    string str;

    set<tuple<int,int,char>> xtree;
    set<tuple<int,char>> xcur;
    set<int> curbeam;
    set<int> nxtbeam;
    map<int,long long> curbeam2;
    map<int,long long> nxtbeam2;

    long long answer1 {0};
    long long answer2 {0};

    int r {0};
    while ( getline( is, str ))
    {
        cout << str << endl;
        xcur.clear();
        int c {0};
        for ( char s : str )
        {
            if (s=='S')
            {
                xtree.insert( make_tuple( r, c, s));
                nxtbeam.insert(c);
                nxtbeam2[c]++;
            }

            if (s=='^' && curbeam.find(c)!=curbeam.end())
            {
                xtree.insert( make_tuple(r,c,'*'));
                xtree.insert( make_tuple(r,c-1,'|'));
                xtree.insert( make_tuple(r,c+1,'|'));
                nxtbeam.insert(c-1);
                nxtbeam.insert(c+1);
                nxtbeam2[c-1] += curbeam2[c];
                nxtbeam2[c+1] += curbeam2[c];
                answer1++;
            }
            else if (s=='^')
            {
                xtree.insert(make_tuple(r,c,'x'));
            }

            if (s=='.' & curbeam.find(c)!=curbeam.end())
            {
                xtree.insert( make_tuple(r,c,'|'));
                nxtbeam.insert(c);
                nxtbeam2[c] += curbeam2[c];
            }
            ++c;
        }

        curbeam = nxtbeam;
        curbeam2 = nxtbeam2;
        nxtbeam.clear();
        nxtbeam2.clear();
        ++r;
    }

    is.close();

    for ( auto m : curbeam2 )
    {
        answer2 += m.second;
    }
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

}