#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::tuple;
using std::make_tuple;
using std::get;
using std::tie;
using std::vector;
using std::map;
using std::string;

string handleWf( bool & controlled, vector<tuple<char,char,int,string>> wf, tuple<int,int,int,int> mp )
{

  map<char,int> aMap;
  aMap['x'] = 0;
  aMap['m'] = 0;
  aMap['a'] = 0;
  aMap['s'] = 0;
  tie( aMap['x'], aMap['m'], aMap['a'], aMap['s']) = mp;

  string ret;


      for ( auto r: wf )
      {
        char ch; char op; int  val; string nrule;
        tie (ch,op,val,nrule) = r;
        if ( op == '<' )
        {
          if ( aMap[ch] < val )
          {
            ret = nrule;
            cout << nrule << endl;
            if (nrule == "A" || nrule == "R") controlled = true;
            break;
          }
        }  
        else
        if ( op == '>' )
        {
          if ( aMap[ch] > val )
          {
            ret = nrule;
            cout << nrule << endl;
            if (nrule == "A" || nrule == "R") controlled = true;
            break;
          }
        }
        else
        if  ( op == '\0' )
        {
          ret = nrule;
          cout << nrule << endl;
          if (nrule == "A" || nrule == "R") controlled = true;
          break;
        } 
      }
return ret;
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

  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    std::string sstr;
    union XmaS
    {
      int xmas[4];
      struct SantA  {
      int x; int m; int a; int s;
      } claus;
    };
    int idx = 0;
    XmaS my;
    while ( getline( iss, sstr, '=' ) )
    {
      getline( iss, sstr, ',' );
      my.xmas[idx] = std::stoi(sstr);
      idx++;
    }
    machine_parts.push_back( make_tuple( my.claus.x, my.claus.m, my.claus.a, my.claus.s ) );
    cout << endl;
  }
  cout << endl;
  is.close();

  long long count {};

  for ( auto mp : machine_parts )
  {
    cout << "product..." << endl;
    bool controlled = false;
    string str;
    //for ( auto wf: workflows )
    auto wf = workflows[mapper["in"]];
    {
      if ( controlled ) break;

      str = handleWf( controlled, wf, mp);

      while ( !controlled )
      {
        auto wf2 = workflows[mapper[str]];
        str = handleWf( controlled, wf2, mp);
      }

    }
    if ( str == "A" )
    {
      count += (get<0>(mp) + get<1>(mp) + get<2>(mp) + get<3>(mp));
    }
  }

  cout << "count = " << count << endl;
}
