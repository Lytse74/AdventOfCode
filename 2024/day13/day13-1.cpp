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


int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day13.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    long long bax {0};
    long long bay {0};
    
    long long bbx {0};
    long long bby {0};

    long long px {0};
    long long py {0};

    while ( getline( is, str ))
    {
        istringstream iss(str);
        string sstr;

        int idx = 0;
        while( getline( iss,sstr, '+') )
        {
            if ( 0 == idx )
              ;
            if ( 1 == idx ) {
                istringstream iss2(sstr);
                iss2 >> bax;
            }
            if ( 2 == idx ) {
                istringstream iss2(sstr);
                iss2 >> bay;
            }
            idx++;
        }
        getline( is, str );
        iss.clear();
        iss.str(str);
        idx = 0;
        while( getline( iss,sstr, '+') )
        {
            if ( 0 == idx )
              ;
            if ( 1 == idx ) {
                istringstream iss2(sstr);
                iss2 >> bbx;
            }
            if ( 2 == idx ) {
                istringstream iss2(sstr);
                iss2 >> bby;
            }
            idx++;
        }
        getline( is, str );
        iss.clear();
        iss.str(str);
        idx = 0;
        while( getline( iss,sstr, '=') )
        {
            if ( 0 == idx )
              ;
            if ( 1 == idx ) {
                istringstream iss2(sstr);
                iss2 >> px;
            }
            if ( 2 == idx ) {
                istringstream iss2(sstr);
                iss2 >> py;
            }
            idx++;
        }
        cout << "Q:" <<bax << " " << bbx << " " << bay << " " << bby << " " << px << " " << py << endl;
        long long bay_bbx = bay * bbx;
        long long bax_bby = bax * bby;
        long long db = bax_bby - bay_bbx;
       
        long long bax_py = bax * py;
        long long bax_py2 = bax * (py+10000000000000);
        long long bay_px = bay * px;
        long long bay_px2 = bay * (px+10000000000000);
        long long dpa = bax_py - bay_px;
        long long dpa2 = bax_py2 - bay_px2;
       
        long long bbx_py = bbx * py;
        long long bbx_py2 = bbx * (py+10000000000000);
        long long bby_px = bby * px;
        long long bby_px2 = bby * (px+10000000000000);
        long long dpb = bbx_py - bby_px;
        long long dpb2 = bbx_py2 - bby_px2;
       
        long long div_pb2 = dpa2 / db;
        long long rem_pb2 = dpa2 % db;
        
        long long div_pb = dpa / db;
        long long rem_pb = dpa % db;

        long long div_pa= -dpb / db;
        long long rem_pa = dpb % db;

        long long div_pa2= -dpb2 / db;
        long long rem_pa2 = dpb2 % db;

        cout << "A:" << div_pa <<"|"<<rem_pa<< " "<<div_pb<<"|"<<rem_pb<<endl;
        cout << "A:" << div_pa2 <<"|"<<rem_pa2<< " "<<div_pb2<<"|"<<rem_pb2<<endl;

        if ( rem_pa == 0 && rem_pb ==0 )
            answer1 += div_pa*3+div_pb;

        if ( rem_pa2 == 0 && rem_pb2 ==0 )
            answer2 += div_pa2*3+div_pb2;

        getline( is, str );
    } 
    is.close();

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;
 
    return 0;
}
