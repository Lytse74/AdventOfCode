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
    ifstream is("day24.input");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    map<string,bool> inputs;
    vector<tuple<string,string,string,string>> gates;
    map<string,bool> outputs;

    while ( getline( is, str  ))
    {
        if ( str.empty() )
            break;
        
        istringstream iss(str);
        string sstr_in;
        string sstr_val;
        getline(iss,sstr_in,':');
        getline(iss,sstr_val,':');

        inputs[sstr_in]= (sstr_val==" 1")?true:false;
    }

    while ( getline( is, str  ))
    {
        istringstream iss(str);
        
        string sstr_in1;
        string sstr_in2;
        string sstr_out;
        string sstr_op;
        string sstr_dummy;

        getline(iss,sstr_in1,' ');
        getline(iss,sstr_op,' ');
        getline(iss,sstr_in2,' ');
        getline(iss,sstr_dummy,' ');
        getline(iss,sstr_out,' ');

        gates.push_back( make_tuple( sstr_in1, sstr_in2, sstr_out, sstr_op ));
    }
    is.close();

    for ( auto i:inputs )    {
        cout << i.first << "->" << i.second << endl;
    }

    // use overflow to test gates
    // first tests 2^44+2^44=2^45 OK
    // use 0 and all 1 to test
    // - x11..x23 en x28..x37 broken
    // - x11..x23 en x28 .x37 broken
    // add 1 to all 1 to test
    // - x24..x27 en x38,,x44 and x45 broken
    // - x24..x27 en x38,,x44 and x45 broken
    // all 1 to all 1
    // - z28 en z38 nok
    // *11 one causes an overflow
    // *24 does not pickup  ooverflpw
    // interleave pattern x24 -> x25 x28 -> x29 x38 -> x39, x11-.x12
    


    bool intl = true;
    for( auto & i:inputs)
    {
        i.second = intl;
        intl = not intl;
        if (i.first[0]=='x')
            i.second = false;
    }



    vector<tuple<string,string,string,string>> hgates;

    auto g = gates.begin();
    while(g!=gates.end())
    {
        if ( inputs.find( get<0>(*g) ) != inputs.end()
            && inputs.find( get<1>(*g) ) != inputs.end() )
        {
            bool res;
            if (get<3>(*g)=="AND")
                res = inputs[get<0>(*g)]&&inputs[get<1>(*g)];
            else if (get<3>(*g)=="OR")
                res = inputs[get<0>(*g)]||inputs[get<1>(*g)];
            else if (get<3>(*g)=="XOR")

            res = inputs[get<0>(*g)]^inputs[get<1>(*g)];

            // is it used as input?
            bool isInput = false;
            for (auto tg:gates)
            { 
                if ( get<2>(*g) == get<0>(tg) 
                    || get<2>(*g) == get<1>(tg) )
                    isInput = true; 
            }
            if ( isInput )
                inputs[get<2>(*g)] = res;
            else
                outputs[get<2>(*g)] = res;
            
            hgates.push_back(*g);
            g = gates.erase(g);
            g = gates.begin();
        }
        else
        {
            g++;
            if (gates.size()>0 && g==gates.end())
                g=gates.begin(); 
        }                           
    }

    std::bitset<100> z;
    
    for ( auto o :outputs)
    {
        string tstr = o.first.substr(1);
        cout << stoi(tstr) << " " << o.second << "   ";
        if ((stoi(tstr)%8)==7)
            cout << endl;
        if (o.second)
            z.set(stoi(tstr));
    }

    answer1 = z.to_ulong();
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = ";

    return 0;
}