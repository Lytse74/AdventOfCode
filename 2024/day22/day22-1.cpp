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

inline long long secretgen( long long sec )
{
    long long rsec = 0;
    // 24 bit
    //SHL 6 bit
    //XOR
    rsec = ((sec << 6)^sec)&0xffffff;
    //cout << rsec << endl;
    sec = rsec;
    
    //SHR 5 bit
    //XOR
    rsec = ((sec >> 5)^ sec)&0xffffff;
    //cout << rsec << endl;
    sec = rsec;
    
    //SHL 11 bit
    //XOR
    rsec = ((sec << 11)^sec)&0xffffff;
    //cout << rsec << endl;

    return rsec;
}

int main()
{
    ifstream is("day22.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    vector<long long> codes;

    while ( getline( is, str  ))
    {
        codes.push_back(stoll(str));
    }

    long long sec = 123;
    for ( auto n=0;n<10;n++)
    {
        sec = secretgen(sec);
        //cout << ( sec ) << endl;
    }
    //cout << ( sec ) << endl;
    //15887950
    //16495136
    //527345
    //704524
    //1553684
    //12683156
    //11100544
    //12249484
    //7753432
    //5908254

    //cout << (42^15) << endl;
    //cout << (100000000%16777216) << endl;

        
    long long idx=0;
    /* value, d1, d2,d3,d4 */
    map<tuple<int,int,int,int,int>,int> values;
    for ( auto code:codes)
    {
        vector<int> bananas;
        vector<int> d;

        for ( auto n=0;n<2000;n++)
        {
            bananas.push_back(code%10);
            code = secretgen(code);
            d.push_back((code%10)-bananas.back());
            if (n>2)
            {
                tuple<int,int,int,int,int> tup = make_tuple(d[n-3],d[n-2],d[n-1],d[n],idx);
                if ( values.find( tup ) == values.end() )
                {
                    values[tup]=code%10;
                }
            }
        }
        //cout << code << endl;;
        answer1+=code;
        idx++;
    }

    map<tuple<int,int,int,int>,int> agg;
    for (auto v :values)
    {
        tuple<int,int,int,int> ag = make_tuple( get<0>(v.first),get<1>(v.first),get<2>(v.first),get<3>(v.first));
        /*if ( ag == make_tuple( -2,1,-1,3) )
        {
            cout << get<4>(v.first) << "|" << v.second << endl;
        }*/
        agg[ag] +=  v.second;
    }
    int max_agg = 0;
    tuple<int,int,int,int> max_aggt;

    for (auto ag:agg)
    {
        if (ag.second > max_agg )
        {
            max_agg = ag.second;
            max_aggt = ag.first;
        }
    }
    answer2 = max_agg;

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
