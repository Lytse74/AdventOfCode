#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;
using std::pair;
using std::set;
using std::make_pair;


int main( )
{
    // first read the pairs of page ordering rules
    ifstream is("day05.input");

    string str;
    set<pair<long long,long long>> ranges;

    long long answer1 {0};
    long long answer2 {0};

    while ( getline( is, str ))
    {
        if (str=="")
            break;

        //cout << str << endl;
        
        istringstream range(str);

        long long rstart { 0 };
        long long rend { 0 };
        char sep;

        range >> rstart;
        range >> sep;
        range >> rend;

        //cout << rstart << sep << rend <<  endl;

        ranges.insert( make_pair( rstart,rend ) );
    }
    
    while ( getline( is, str ))
    {
        istringstream val(str);

        long long aval {0};
        set<pair<long long,long long>>::iterator itlow,itup;
        
        val >> aval;
        //cout << aval << endl;

        for (auto r:ranges)
        {
            if ( aval >= r.first && aval <= r.second )
            {
                //cout << "[" << r.first << "," << r.second << "]" << endl;
                answer1++;
                break;
            }
        }
    }

    is.close();

    long long p=0;

    for (auto r:ranges)
    {
        if ( p<r.first)
        {
            p = r.second;
            answer2 += (r.second - r.first +1);
        } else if ( p < r.second )
        {
            answer2 += (r.second - p);
            p = r.second;
        }
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
}