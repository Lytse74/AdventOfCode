#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <set>
#include <vector>

using std::cout;
using std::endl;

using std::ifstream;
using std::string;
using std::istringstream;
using std::set;
using std::pair;
using std::make_pair;
using std::vector;

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day05.input");
    string str;
    set<pair<int,int>> rules;
    vector<int> update;
    int answer1 {0};
    int answer2 {0};


    while ( getline( is, str ))
    {
        if ( str == "" )
          break;

        istringstream iss(str);
        string sstr;
        int r1 {0}, r2 {0};
        char cdum {0};
        
        iss >> r1 >> cdum >> r2;
        rules.insert(make_pair(r1,r2));


        cout << r1 << "-" << r2 << endl;
    }
    while ( getline( is, str ))
    {
        istringstream iss(str);
        string sstr;
        bool correct = true;

        update.clear();

        while ( getline( iss, sstr, ',') )
        {
            update.push_back(stoi(sstr));
        }

        for ( auto i=0; i<update.size()-1; ++i)
        {
            for ( auto j=i+1; j<update.size(); ++j )
            {
                if ( rules.find(make_pair(update[j],update[i])) != rules.end() )
                {
                     cout << update[i] << "[" << i << "]-" << update[j] << "[" << j << "]" << endl;
                      correct = false;
                     int tmp = update[i];
                     update[i]=update[j];
                     update[j]=tmp;
                }
            }
        }
        
        if (correct)
        {
            cout << str << endl;
            answer1 += update[update.size()/2];
        }
        else
        {
            cout << str << endl;
            answer2 += update[update.size()/2];
        }
    }
    is.close();
 
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
    return 0;

}