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


int maxYoltage2( string bank )
{ 
    int retVal {0};
    size_t tens[9];
    size_t ones[9];
    string cell = "1";

    for (char i=0 ; i<9; i++ )
    {
        cell[0] = i + '1';
        tens[i] = 
        bank.find_first_of(cell,0);
        if ( tens[i] == (bank.size()-1) )
            tens[i] = std::string::npos;

        ones[i] =
        bank.find_last_of(cell);
        if ( ones[i] == 0 )
            ones[i] = std::string::npos;
    }

    size_t bestten;
    for (char i=8; i>=0; i--)
    {
        if ( tens[i] != std::string::npos )
        {
            bestten = tens[i];
            retVal = (i+1)*10;
            break;
        }
    }
    for (char i=8; i>=0; i--)
    {
        if ( ones[i] != std::string::npos
          && ones[i] > bestten )
        {
            retVal += (i+1);
            break;
        }
    }

    return retVal;
}

long long maxYoltage12( string bank )
{
    long long retVal = 0;
    string cell = "1";
    size_t spos = 0;
    size_t pos;

    char b=11;
    while ( b>= 0 )
    {
        retVal *= 10;
    char i=8;
    while ( i>=0 )
    {
        cell[0]='1'+i;
        pos = bank.find_first_of(cell,spos);
        if ( pos != std::string::npos
            && pos < bank.size()-b)
        {
            retVal += (i+1);
            spos = pos+1;
            break;
        }
        --i;
    }
        --b;
    }

    return retVal;
}

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day03.input");
    string str;

    long long answer1 {0};
    long long answer2 {0};

    while ( getline( is, str ))
    {
        cout << str << endl;

        istringstream range(str);

        answer1 += maxYoltage2( str );
        answer2 += maxYoltage12( str );
    }

    is.close();

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;




}