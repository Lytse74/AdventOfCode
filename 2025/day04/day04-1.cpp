#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;
using std::pair;
using std::set;
using std::make_pair;

int prune( set<pair<int,int>> & paper, set<pair<int,int>> & remove)
{
    set<pair<int,int>>::iterator paper_it;

    for ( auto p: paper )
    {
        int count {0};
        paper_it = paper.find( make_pair( p.first, p.second +1 ) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first -1, p.second +1 ) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first -1, p.second) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first -1, p.second -1 ) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first, p.second -1 ) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first +1, p.second -1) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first +1, p.second) );
        if( paper_it != paper.end()) 
            count++;
        paper_it = paper.find( make_pair( p.first +1, p.second +1) );
        if( paper_it != paper.end()) 
            count++;
        if( count < 4 )
            remove.insert(p);
    }
    
    set<pair<int,int>> diff;
    std::set_difference(paper.begin(), paper.end(), remove.begin(), remove.end(),
                        std::inserter(diff, diff.begin()));

    paper = diff;

    return remove.size();
}

int main( )
{
    // first read the pairs of page ordering rules
    ifstream is("day04.input");

    string str;
    set<pair<int,int>> paper;

    long long answer1 {0};
    long long answer2 {0};

    int r = 0;
    while ( getline( is, str ))
    {
        cout << str << endl;
        int c = 0;
        for (char s: str)
        {
            if (s == '@' )
            {
            paper.insert(make_pair(r,c));
            }
            ++c;
        }
        ++r;
    }

    is.close();

    set<pair<int,int>> remove;
    answer1 = prune( paper, remove );
    answer2 = answer1;

    while( remove.size() > 0)
    {
        remove.clear(); 
        answer2 += prune( paper, remove );
    }
    

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
}