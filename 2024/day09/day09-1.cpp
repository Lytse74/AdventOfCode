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

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day09.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<int> filespace;

    while ( getline( is, str ))
    {
        bool file = true;
        int fid = 0;
        cout << str.length() << endl;
        for ( auto c: str)
        {
            int cnt = c - '0';
            while (cnt--)
            {
                if (file)
                    filespace.push_back(fid);
                else
                    filespace.push_back(-1);    
            }
            if (file)
                file = !file;
            else
            {
                file = !file;
                fid++;
            }
        }
    }
    is.close();

    for ( int i=0; i<filespace.size(); i++ )
    {
        if (!(filespace[i]<0))
            continue;
        else
        {
            auto elm = filespace.back();
            while (elm<0)
            {
                filespace.pop_back();
                elm = filespace.back();
            }
            filespace[i] = elm;
            filespace.pop_back();
        }
    }

    int idx1 = 0;
    for ( auto i: filespace)
    {
        answer1 += ( idx1*i );
        idx1++;
    }
    
    cout << "answer1 = " << answer1 << endl;;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}