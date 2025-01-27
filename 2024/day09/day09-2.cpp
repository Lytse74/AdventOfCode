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

int main()
{
    // first read the pairs of page ordering rules
    ifstream is("day09.input");
    string str;
    long long answer1 {0};
    long long answer2 {0};

    vector<int> filespace;
    int fid = 0;

    while ( getline( is, str ))
    {
        bool file = true;
        cout << str.length() << endl;
        for ( auto c: str)
        {
            int cnt = c - '0';
            while (cnt--)
            {
                if (file)
                    filespace.push_back(fid);
                else
                    filespace.push_back(-1);    
            }
            if (file)
                file = !file;
            else
            {
                file = !file;
                fid++;
            }
        }
    }
    is.close();

    cout << "fid = " << fid << endl;

    int fsptrb = filespace.size()-1;    
    int fsptrf = filespace.size()-1;
    int frptrf = 0;
    int frptrb = 0;
    
    while ( fid >= 0)
    {
        // find the fid on filespace
        while(filespace[fsptrb]>fid || filespace[fsptrb]==-1)
            fsptrb--;
        fsptrf = fsptrb;
        while(filespace[fsptrf]==fid)
            fsptrf--;

        // find a freespace that is large enough
        while(frptrf < fsptrf)
        {
            while(filespace[frptrf]>=0)
                frptrf++;
            frptrb = frptrf;
            while(filespace[frptrb]<0)
                frptrb++;

            if ( frptrb - frptrf < fsptrb - fsptrf || frptrf >= fsptrf )
            {
                frptrf = frptrb;
                continue;
            }

            // move the block
            for ( int m = 0; m< fsptrb - fsptrf; m++ )
            {
                filespace[frptrf+m] = filespace[fsptrf+1+m];
                filespace[fsptrf+1+m] = -1;
            } 
            fsptrb = fsptrf;
            while ( fsptrb < 0) fsptrb--;
            while ( fsptrf < 0) fsptrf--;

            break;
        }

        frptrf = 0;
        frptrb = 0;
        fid--;    
    }

    int idx2 =0;
    for ( auto i: filespace)
    {
        if (i>=0)
            answer2 += ( idx2*i );
        idx2++;
    }
    
    cout << "answer1 = " << answer1 << endl;;
    cout << "answer2 = " << answer2 << endl;

    return 0;
}