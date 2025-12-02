#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;

bool handleCmdAndCheckZero( int & pos, string  str )
{
    istringstream cmd(str);

    char dir;
    int clicks;

    cmd >> dir;
    cmd >> clicks;

    if ( dir == 'R' )
        pos += clicks;

    if ( dir == 'L' )
        pos -= clicks;

    pos = pos % 100;

    if ( pos < 0 )
        pos += 100;

    cout << "dir = " << dir << ", clicks = " << clicks << ", pos = " << pos << endl;

    return ( pos == 0 );
}

int handleCmdAndCountZero( int & pos, string  str )
{
    istringstream cmd(str);

    char dir;
    int clicks;
    int count {0};
    
    cmd >> dir;
    cmd >> clicks;

    if ( dir == 'R' )
    {
        pos += clicks;
        count = pos / 100;
    }

    if ( dir == 'L' )
    {
        if ( pos == 0 )
            count -= 1;
        pos -= clicks;
        if ( pos > 0 )
            count -= 1;
        count += ( -pos / 100 +1);
  
    }

    pos = pos % 100;

    if ( pos < 0 )
        pos += 100;

    cout << "dir = " << dir << ", clicks = " << clicks << ", pos = " << pos << ", count = " << count << endl;

    return ( count );
}

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day01.input");
    string str;
    int pos {50}; // start position
    int answer1 {0};
    int answer2 {0};

    while ( getline( is, str ))
    {
        cout << str << endl;
        //if ( handleCmdAndCheckZero( pos, str ) )
        //    answer1++;
        answer2 += handleCmdAndCountZero( pos, str );
    }

    is.close();

    cout << "answer2 = " << answer2 << endl;
}

