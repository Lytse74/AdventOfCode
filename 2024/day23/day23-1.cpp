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


// https://stackoverflow.com/questions/12991758/creating-all-possible-k-combinations-of-n-items-in-c:
void comb(int N, int K)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        for (int i = 0; i < N; ++i) // [0..N-1] integers
 
        {
            if (bitmask[i]) std::cout << " " << i;
        }
        std::cout << std::endl;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

int main()
{
    ifstream is("day23.test");
    string str;
    
    long long answer1 {0};
    long long answer2 {0};

    set<set<string>> net;
    set<string> nodes;
    while ( getline( is, str  ))
    {
        istringstream iss(str);
        string lft;
        getline(iss,lft,'-');
        nodes.insert(lft);
        string rght;
        getline(iss,rght,'-');
        nodes.insert(rght);
        set<string> ss;
        ss.insert(lft);
        ss.insert(rght);
        net.insert(ss);
    }
    is.close();

    set<set<string>> result;

    for ( auto n : nodes )
    {
        for ( auto e1 : net )
        {
            if ( e1.find(n) != e1.end() )
            {
                set<string>::iterator it1;
                it1 = e1.begin();
                if (*it1==n)
                    it1++;
                for ( auto e2 : net )
                {
                    if ( e2.find(*it1) != e2.end() )
                    {
                        set<string>::iterator it2;
                        it2 = e2.begin();
                        if (*it2==*it1 && n!=* it2)
                        {
                            it2++;
                            set<string> tss;
                            tss.insert(*it2);
                            tss.insert(n);
                            if(net.find(tss)!= net.end() )
                            {
                                tss.insert(*it1);
                                result.insert(tss);
                            }
                        }
                    }
                }    
            }
        }
    }

    for (auto r:result)
    {
        for (auto n:nodes)
        {
            if (n[0]!='t')
                continue;
        
            if ( r.find(n)!=r.end() )
            {
                answer1++;
                break;
            }
        }
    }

    // expand result
    int max_size=3;
    auto r=result.begin();
    while (r!=result.end())
    {
        bool changed = false;
        for (auto n:nodes)
        {
            if ( r->find(n)== r->end() )
            {
                bool nok=false;
                for (auto m:*r)
                {
                    set<string>  ts;
                    ts.insert(n);
                    ts.insert(m);
                    if (net.find(ts)==net.end())
                    {
                        nok =true;
                        break;
                    }
                }
                if (!nok)
                {
                    set<string> tss=*r;
                    r =result.erase(r);
                    tss.insert(n);
                    if (tss.size()> max_size)
                        max_size = tss.size();
                    result.insert(tss);
                    r=result.begin();
                    changed=true;
                    break;
                }
            }
        }

        
        if (!changed)
        {
            if (r->size()<max_size)
                r=result.erase(r);
            else
                r++;

        }
    }
    
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = ";

    for (auto r:result)
    for (auto n:r)
    {
        cout << n << ",";
    }
    cout << endl;



    return 0;
}