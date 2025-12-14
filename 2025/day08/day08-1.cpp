#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>


using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;
using std::to_string;
using std::tuple;
using std::set;
using std::make_tuple;
using std::tie;
using std::map;
using std::vector;
using std::get;

int main()
{
    ifstream is("day08.input");
    string str;

    long long answer1 {0};
    long long answer2 {0};
    int mx {1000000},my {1000000},mz {1000000};

    set<tuple<int,int,int>> points;
    while ( getline( is, str ))
    {
        cout << str << endl;
        istringstream iss(str);
        int x,y,z;
        char c;

        iss >> x;
        iss >> c;
        iss >> y;
        iss >> c;
        iss >> z;

        if ( x < mx )
            mx = x;
        if ( y < my )
            my = y;
        if ( z < mz )
            mz = z;

        points.insert( make_tuple(x,y,z));
    }

    is.close();

    cout << "mx = " << mx << " my = " << my << " mz = " << mz << endl;

    set<tuple<long long,int,int>> shortest;

    int i=0;
    for ( auto s:points)
    {
        int x1,y1,z1;
        long long dminsq {1000000000000};

        tie(x1,y1,z1) = s;

        int dx,dy,dz;
        tuple<int,int,int> dr;

        int j=0;
        int dj=0;
        for( auto t:points)
        {
            if ( t  == s )
            {
                ++j; 
                continue;
            }

            long long x2,y2,z2;
            tie(x2,y2,z2) = t;
            long long x1x2_2 = (x1-x2)*(x1-x2);
            long long y1y2_2 = (y1-y2)*(y1-y2);
            long long z1z2_2 = (z1-z2)*(z1-z2);
            long long dsq = (long long) (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2);

//            if ( dsq < dminsq )
//            {
//                dminsq = dsq;
//                dr = t;
//                dj = j;
//            }
            if (j>i)
                shortest.insert( make_tuple(  dsq, i, j));
            ++j;
        }
    
        ++i;
    }

    vector<set<int>> network; 
 
    int count {0};

    for (auto s:shortest)
    {

        if ( count == 1000 )
        {
            std::sort(network.begin(), network.end(), [](auto lhs, auto rhs) {
                    return lhs.size() >= rhs.size();
                });
            
            answer1 = network[0].size()*network[1].size()*network[2].size();
        }
        

        long long dummy;
        int v,w;
        
        tie(dummy,v,w)=s;

        cout << dummy << endl;
        cout << "v=" << v << " w=" << w << endl;
        
        int fv {-1}, fw {-1};

        for (int n=0; n<network.size(); n++ )
        {
            set<int>::iterator ns_it;
            ns_it = network[n].find(v);
            if ( ns_it != network[n].end())
                fv = n;
            ns_it = network[n].find(w);
            if ( ns_it != network[n].end())
                fw = n;

            }

        //cout << "fv = " << fv << ", fw = " << fw << endl;

        if( fv == -1 && fw == -1 )
        {
            set<int> nw;
            nw.insert(v);
            nw.insert(w);
            network.push_back(nw);
        }
        if (fv == -1 && fw != -1)
        {
            network[fw].insert(v);
        }
        if (fv != -1 && fw == -1)
        {
            network[fv].insert(w);
        }
        if (fv != -1 && fw != -1 && fv != fw)
        {
            for( auto f :network[fw] )
            {
                network[fv].insert(f);
            }
            network[fw].clear();
            network.erase(network.begin()+fw);
        }
       
        if ( network.size()==1 && network[0].size() == points.size()  )
        {
            answer2 = count+1;
            answer2 = get<0>(*std::next(points.begin(), v));
            answer2 *= get<0>(*std::next(points.begin(), w));
            break;
        }
        ++count;
    }
    
    std::sort(network.begin(), network.end(), [](auto lhs, auto rhs) {
            return lhs.size() >= rhs.size();
        });
    
    //answer1 = network[0].size()*network[1].size()*network[2].size();
       
    
    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

}