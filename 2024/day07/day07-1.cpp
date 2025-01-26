// - https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring

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

using std::cout;
using std::endl;

using std::ifstream;
using std::string;
using std::vector;

using std::pair;
using std::istringstream;

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}




int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day07.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<pair<long long,vector<int>>> equations;

    while ( getline( is, str ))
    {
        istringstream iss(str); 
        string sstr;
        int idx = 0;
        long long result = -1;
        vector<int> params;

        while ( getline ( iss, sstr, ':'))
        {
            if  (idx==0)
            {
                result = stoll(sstr);
            }
            else if ( idx == 1 )
            {
                ltrim(sstr);
                istringstream issp(sstr);
                string pstr;
                while ( getline ( issp, pstr, ' ' ) )
                {
                    params.push_back( stoi(pstr));
                }
                equations.push_back( make_pair( result, params ) );
            }
            idx++;
        }
    }
    is.close();

    int max_size = 0;
    long long total = 0;

    for ( auto eq: equations )
    { 
        bool b1 =false;
        bool b2 =false;
        for ( auto op = 0; op < pow(3,eq.second.size()-1); op++ )
        {
            //cout << std::bitset<12>(op) << endl;
            int top = op;

            long long result = eq.second[0];
            long long result2 = eq.second[0];

            for ( auto nr = 0; nr < eq.second.size()-1; nr++,top /= 3 )
            {
                if ( (top % 3) == 1 )
                {
                    result *= eq.second[nr+1];
                    result2 *= eq.second[nr+1];
                }
                else if ( (top % 3 ) == 0 )
                {
                    result += eq.second[nr+1];
                    result2 += eq.second[nr+1];
                }
                else if ( (top%3)==2 )
                {   
                    result=eq.first+1;
                    //cout << result2 <<  eq.second[nr+1] << endl;
                    string tstr = ( std::to_string(result2)+std::to_string(eq.second[nr+1]));
                    long long result3 = stoll( tstr );
                    if ( result3 > result2 )
                        result2 = result3;
                    else
                        result2 = eq.first+1;
                    //cout << eq.first << " - " << result2 << endl;
                    if ( result2 > eq.first )
                        result2 = eq.first+1;
                    //if ( tstr == std::to_string(result2) )
                    //    cout << result2 << "," << tstr << endl;
                }
            }
            if ( result == eq.first && !b1 )
            {
                answer1 += result;
                b1 = true;
            }
            if ( result2 == eq.first && !b2)
            {
                answer2 += result2;
                b2 = true;
            }
            if (b1&&b2)
                break;
        }
        if ( eq.second.size() >  max_size )
            max_size = eq.second.size();

        long long totalnew = total + eq.first;
        if ( totalnew >= total )
            total = totalnew;
        else
            cout << "ERROR" << endl;
    }

    cout << "answer1 = " << answer1 << endl;;
    cout << "answer2 = " << answer2 << endl;
    cout << "total = " << total << endl;

    return 0;
}