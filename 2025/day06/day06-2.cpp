#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;
using std::vector;

int main()
{
    // first read the pairs of page ordering rulest
    ifstream is("day06.input");
    string str1;
    string str2;
    string str3;
    string str4;
    string str5;

    long long answer1 {0};
    long long answer2 {0};

    vector<vector<int>> operands;
    vector<char> operation;

    getline( is, str1 );
    getline( is, str2 );
    getline( is, str3 );
    
    getline( is, str4 );
    getline( is, str5 );
    
    is.close();

    size_t cur {0};
    size_t nxt {0};

    while ( nxt != string::npos)
    {
    nxt = str5.find_first_of("+*",cur+1);
    string t1,t2,t3,t4;
    int len = -1;
    if ( nxt != string::npos)
    {
        len = nxt-cur-1;
        t1 = str1.substr(cur,nxt-cur-1);
        t2 = str2.substr(cur,nxt-cur-1);
        t3 = str3.substr(cur,nxt-cur-1);
        t4 = str4.substr(cur,nxt-cur-1);
    }
    else
    {
        len = str5.size() - cur;
        t1 = str1.substr(cur);
        t2 = str2.substr(cur);
        t3 = str3.substr(cur);
        t4 = str4.substr(cur);

    }

    long long result = -1;

    if (str5[cur] == '+')
    {
        result = 0;

        for( int n = 0; n<len; n++ )
        {
            string ostr = "xxxx";
            ostr[0] = t1[n];
            ostr[1] = t2[n];
            ostr[2] = t3[n];
            ostr[3] = t4[n];
            
            result += stoi(ostr);
        }
    }
    else if ( str5[cur] == '*' )
    {
        result = 1;

        for( int n = 0; n<len; n++ )
        {
            string ostr = "xxxx";
            ostr[0] = t1[n];
            ostr[1] = t2[n];
            ostr[2] = t3[n];
            ostr[3] = t4[n];
            
            result *= stoi(ostr);
        }
    
    }
    answer2 += result;
    cur = nxt;
    }
   
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
}