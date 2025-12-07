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
    string str;

    long long answer1 {0};
    long long answer2 {0};

    vector<vector<int>> operands;
    vector<char> operation;

    while (getline( is, str ))
    {
        cout << str << endl;

        istringstream iss(str);

        vector<int> opers;
        string sstr;
        while ( iss.peek() == ' ' )
            iss.get();
        while (getline(iss,sstr,' '))
        {
            while ( iss.peek() == ' ' )
                iss.get();

            if ( sstr[0] == '+' || sstr[0] == '*')
                operation.push_back(sstr[0]);
            else
                opers.push_back(stoi(sstr));
            cout << sstr << endl;
        }
        
        if ( sstr[0] != '+' && sstr[0] != '*')
            operands.push_back(opers);
    }

    is.close();

    for (  int i=0; i<operation.size(); i++ )
    {
        long long result;
        if(operation[i]=='+')
        {
            result = 0;
            for ( int j=0; j<operands.size(); j++)
                result += operands[j][i];
        }
        if(operation[i]=='*')
        {
            result = 1;
            for ( int j=0; j<operands.size(); j++)
                result *= operands[j][i];
        }

        answer1 += result;
    }

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
}