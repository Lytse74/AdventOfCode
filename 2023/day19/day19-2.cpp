#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <map>
#include <climits>

using std::cout;
using std::endl;
using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;
using std::vector;
using std::map;
using std::string;

long long handleWf( vector<tuple<char,char,int,string>> wf, tuple<int,int,int,int,int,int,int,int> mp,
  vector<vector<tuple<char,char,int,string>>> workflows,
  map<string,int> mapper )
{

  map<char,int> aMap;
  aMap['x'] = 0;
  aMap['y'] = -1;
  aMap['m'] = 0;
  aMap['n'] = -1;
  aMap['a'] = 0;
  aMap['b'] = -1;
  aMap['s'] = 0;
  aMap['t'] = -1;
  tie( aMap['x'], aMap['y'], aMap['m'], aMap['n'], aMap['a'], aMap['b'], aMap['s'], aMap['t']) = mp;

  string ret;

  long long acceptedRange = 0;


      for ( auto r: wf )
      {
        char ch; char op; int  val; string nrule;
        tie (ch,op,val,nrule) = r;

        if ( op == '<' )
        {
          if ( aMap[ch] < val && aMap[ch+1] >= val )
          {
            ret = nrule;
            cout << nrule << endl;                                                 
            // start new wf with new range
            if (!(nrule == "A" || nrule == "R"))
            {
              auto wf = workflows[mapper[nrule]];
              auto cMap =  aMap;
              cMap[ch+1] = val -1;
              
              cout << "x[" << cMap['x'] << ".." << cMap['y'] << "] ";
              cout << "m[" << cMap['m'] << ".." << cMap['n'] << "] ";
              cout << "a[" << cMap['a'] << ".." << cMap['b'] << "] ";
              cout << "s[" << cMap['s'] << ".." << cMap['t'] << "] ";
              cout << nrule << endl;

              acceptedRange += handleWf( wf, make_tuple( cMap['x'], cMap['y'], cMap['m'], cMap['n'], cMap['a'], cMap['b'], cMap['s'], cMap['t']  ), workflows, mapper );
            }
            else
            {
              auto cMap =  aMap;
              cMap[ch+1] = val -1;
              
              cout << "x[" << cMap['x'] << ".." << cMap['y'] << "] ";
              cout << "m[" << cMap['m'] << ".." << cMap['n'] << "] ";
              cout << "a[" << cMap['a'] << ".." << cMap['b'] << "] ";
              cout << "s[" << cMap['s'] << ".." << cMap['t'] << "] ";
              cout << nrule << endl;

              if ( nrule == "A" )
              {
                long long add = ( cMap['y'] - cMap['x'] +1 );
                add *= ( cMap['n'] - cMap['m'] +1 );
                add *= ( cMap['b'] - cMap['a'] +1 );
                add *= ( cMap['t'] - cMap['s'] +1 );
                acceptedRange += add;
              }
            }
            // change current range
            aMap[ch] = val;
            //break;
          }
          else
          {
            cout << ch << ":" << val <<  " not in " << aMap[ch] << ".." << aMap[ch+1] << endl;
          }
        }  
        else
        if ( op == '>' )
        {
          if ( aMap[ch] < val && aMap[ch+1] >= val )
          {
            ret = nrule;
            cout << nrule << endl;
            // start new wf with new range
            if (!(nrule == "A" || nrule == "R"))
            {
              auto wf = workflows[mapper[nrule]];
              auto cMap =  aMap;
              cMap[ch] = val +1;
              
              cout << "x[" << cMap['x'] << ".." << cMap['y'] << "] ";
              cout << "m[" << cMap['m'] << ".." << cMap['n'] << "] ";
              cout << "a[" << cMap['a'] << ".." << cMap['b'] << "] ";
              cout << "s[" << cMap['s'] << ".." << cMap['t'] << "] ";
              cout << nrule << endl;

              acceptedRange += handleWf( wf, make_tuple( cMap['x'], cMap['y'], cMap['m'], cMap['n'], cMap['a'], cMap['b'], cMap['s'], cMap['t']  ), workflows, mapper );
            }
            else
            {
              auto cMap =  aMap;
              cMap[ch] = val +1;
              
              cout << "x[" << cMap['x'] << ".." << cMap['y'] << "] ";
              cout << "m[" << cMap['m'] << ".." << cMap['n'] << "] ";
              cout << "a[" << cMap['a'] << ".." << cMap['b'] << "] ";
              cout << "s[" << cMap['s'] << ".." << cMap['t'] << "] ";
              cout << nrule << endl;

              if ( nrule == "A" )
              {
                long long add = ( cMap['y'] - cMap['x'] +1 );
                add *= ( cMap['n'] - cMap['m'] +1 );
                add *= ( cMap['b'] - cMap['a'] +1 );
                add *= ( cMap['t'] - cMap['s'] +1 );
                acceptedRange += add;
              }
            }
            // change current range
            aMap[ch+1] = val;
            //break;
          }
          else
          {
            cout << ch << ":" << val <<  " not in " << aMap[ch] << ".." << aMap[ch+1] << endl;
          }
        }
        else
        if  ( op == '\0' )
        {
          ret = nrule;
          cout << nrule << endl;
          // start new wf with new range
          if (!(nrule == "A" || nrule == "R"))
          {
            auto wf = workflows[mapper[nrule]];
            
            cout << "x[" << aMap['x'] << ".." << aMap['y'] << "] ";
            cout << "m[" << aMap['m'] << ".." << aMap['n'] << "] ";
            cout << "a[" << aMap['a'] << ".." << aMap['b'] << "] ";
            cout << "s[" << aMap['s'] << ".." << aMap['t'] << "] ";
            cout << nrule << endl;

            acceptedRange += handleWf( wf, make_tuple( aMap['x'], aMap['y'], aMap['m'], aMap['n'], aMap['a'], aMap['b'], aMap['s'], aMap['t']  ), workflows, mapper );
          }
          else
          {
            cout << "x[" << aMap['x'] << ".." << aMap['y'] << "] ";
            cout << "m[" << aMap['m'] << ".." << aMap['n'] << "] ";
            cout << "a[" << aMap['a'] << ".." << aMap['b'] << "] ";
            cout << "s[" << aMap['s'] << ".." << aMap['t'] << "] ";
            cout << nrule << endl;

            if ( nrule == "A" )
            {
              long long add = ( aMap['y'] - aMap['x'] +1 );
              add *= ( aMap['n'] - aMap['m'] +1 );
              add *= ( aMap['b'] - aMap['a'] +1 );
              add *= ( aMap['t'] - aMap['s'] +1 );
              acceptedRange += add;
            }
          }
          //break;
        } 
      }
  return acceptedRange;
}


int main() {
  // open the file
  std::ifstream is("day19.input");
  std::string str;

  vector<tuple<int,int,int,int>> machine_parts;
  vector<vector<tuple<char,char,int,string>>> workflows;
  map<string,int> mapper;
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;

    if ( str == "" )
      break;

    while ( getline( iss, sstr, '{' ) )
    {
      std::string name;
      name = sstr;
      cout << sstr << " ";
      
      vector<tuple<char,char,int,string>> rules;
      int wfs = workflows.size();
      mapper[name] = wfs;
      
      while ( getline( iss, sstr, ',') )
      {
        if (sstr.back() == '}') sstr.pop_back();

        std::istringstream issrule(sstr);

        char ch { '\0' };
        char op { '\0' };
        char dm { '\0' };
        int val {};
        std::string nrule;


        if ( sstr.find_first_of(":") != std::string::npos )
        {
          issrule.get(ch);
          issrule.get(op);
          issrule >> val;
          issrule.get(dm);
        }
        issrule >> nrule;
        cout << nrule << " ";

        rules.push_back( make_tuple( ch, op, val, nrule ));
      } 
      workflows.push_back( rules );
    }
    cout << endl;
  }
  cout << endl;
  is.close();

  long long count {};

    cout << "product..." << endl;
    bool controlled = false;
    auto mp = make_tuple(1,4000,1,4000,1,4000,1,4000);
    
    
    auto wf = workflows[mapper["in"]];
    {
      //if ( controlled ) break;

      count = handleWf( wf, mp, workflows, mapper );

      //while ( !controlled )
      //{
      //  auto wf2 = workflows[mapper[str]];
      //  controlled = handleWf( wf2, mp, workflows, mapper );
      //}
    }

  cout << "count = " << count << endl;
}
