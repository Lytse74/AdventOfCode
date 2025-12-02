#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;

bool isDoubleSeq( long long n )
{
    string nstr = to_string(n);
    int len = nstr.size();

    // get substring
    string sstr = nstr.substr(len/2);

    // remove leading zeros
    //  sstr.erase(0, std::min(sstr.find_first_not_of('0'), sstr.size() - 1));
    // cout << sstr << endl;

    return ( nstr.find(sstr,0) == 0 && sstr.size() <= len/2);
}

bool isMultiSeq( long long n )
{
    string nstr = to_string(n);
    int len = nstr.size();

    bool ret = false;

    for (int i=2; i<=len; i++)
    {
        if ( (len % i) != 0 )
            continue;

        
        // get substring
        string sstr = nstr.substr((i-1)*len/i);

      
        //cout << sstr << endl;

        bool eq = true;
        for (int j=0;j<i;j++)
        {
            std::size_t t = nstr.find(sstr,j*len/i);
            if (t!=std::string::npos)
            if ( t == j*len/i )
                continue;
            eq = false;
        }
        ret = eq;

        if ( ret == true )
            break;
    }
    return ret;
}

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day02.input");
    string str;

    long long answer1 {0};
    long long answer2 {0};

    while ( getline( is, str, ',' ))
    {
        cout << str << endl;
        istringstream range(str);

        long long rstart { 0 };
        long long rend { 0 };
        char sep;

        range >> rstart;
        range >> sep;
        range >> rend;

        cout << rstart << sep << rend <<  endl;

        for ( long long i= rstart; i<= rend; i++ )
        {
            if ( isDoubleSeq(i) )
                answer1 += i;

            if ( isMultiSeq(i) )
            {
                cout << i << endl;
                answer2 += i;
            }
        }
        cout << endl;
    }

    is.close();

    bool b = isMultiSeq( 565656 );
    b = isMultiSeq( 2121212121 );
    b = isMultiSeq( 999 );
    b = isMultiSeq( 111 );
    b = isMultiSeq( 222222 );
    b = isMultiSeq( 1001 );

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
}
