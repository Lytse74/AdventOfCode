#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;

void HandleSignal( tuple<char,vector<string>,map<string,bool>,bool> & node, bool signal,string sender, string orig,vector<tuple<string,bool,string>> & signals )
{
  //cout << get<0>(signals[0]) << " <=" << get<1>(signals[0]) << "==" << get<0>(node) << "= " << get<2>(signals[0]) << endl;
  cout 
  << get<0>(node) << ')'
  << get<2>(signals[0]) << " -"
  << get<1>(signals[0]) << "-> "
  << get<0>(signals[0]) 
  << endl;
  if ( get<0>(node) == 'b' )
  {
    for ( auto out : get<1>(node) )
    {
      signals.push_back(make_tuple(out,signal,orig));
    }
  }
  if ( get<0>(node) == '%' && !signal )
  {
    // toggle state
    get<3>(node) = !get<3>(node);
    for ( auto out : get<1>(node) )
    {
      signals.push_back(make_tuple(out,get<3>(node),orig));
    }

  }
  if ( get<0>(node) == '&' )
  { 
    // remember input
    get<2>(node)[get<2>(signals[0])] = get<1>(signals[0]); //!get<2>(node)[get<2>(signals[0])];

    auto m_it = get<2>(node).begin();
    while ( m_it->second && m_it != get<2>(node).end() )
      m_it++;

    bool result = (m_it != get<2>(node).end());
    
    for ( auto out : get<1>(node) )
    {
      signals.push_back(make_tuple(out,result,orig));
      if ( out == "rx" && result == false)
        cout << ">>>>" << result << endl;
    }
  }
}


void PushButton( map<string,tuple<char,vector<string>,map<string,bool>,bool>> & nodes, vector<tuple<string,bool,string>> & signals, int & hpulse, int & lpulse )
{
  signals.push_back( make_tuple( "broadcaster", false, "button" ));

  auto it = signals.begin();
  while ( it != signals.end() )
  {
    if ( get<1>(*it) )
      ++hpulse;
    else
      ++lpulse;

    string recv;
    bool val;
    string send;

    std::tie( recv, val, send ) = *it;
    HandleSignal( nodes[recv],val,send,recv, signals);
    it = signals.begin();
    it = signals.erase(it);
  }

  return;
}

void FillInputs( map<string,tuple<char,vector<string>,map<string,bool>,bool>> & nodes )
{
  for ( auto it= nodes.begin(); it != nodes.end(); it++ )
  {
    for( auto it_o = get<1>(it->second).begin(); it_o != get<1>(it->second).end(); it_o++ )
    {
      cout << *it_o << endl;
      cout << get<0>(nodes[*it_o]) << endl;
      get<2>(nodes[*it_o] )[it->first]=false;
    }
  }

}

int main() {
  // open the file
  std::ifstream is("day20.input");
  std::string str;

  map<string,tuple<char,vector<string>,map<string,bool>,bool>> nodes;
  vector<tuple<string,bool,string>> signals;

  int hpulse {};
  int lpulse {};
  
  while ( getline( is, str ) )
  {
    std::istringstream iss(str);
    char ch;
    string label;
    vector<string> outputs;
    map<string,bool> inputs;
    bool state = false;

    if ( iss.peek() == '%' || iss.peek() == '&' )
      iss.get(ch);
    else
      ch = 'b';
    
    iss >> label;

    std::string sstr;
    getline(iss,sstr, ' ');
    getline(iss,sstr, ' ');
    while ( getline(iss,sstr, ','))
    {
      if ( std::isspace(sstr[0]) )
        sstr = sstr.substr(1);

      outputs.push_back(sstr);
    }

    nodes[label] = make_tuple( ch, outputs, inputs, state );
  }
  cout << endl;

  is.close();

  FillInputs( nodes );

  long long answer1 = hpulse * lpulse;
  for ( auto i=0; i<1000; ++i )
  {
    PushButton( nodes, signals, hpulse, lpulse );
    answer1 = hpulse * lpulse;
    //cout << "h=" << hpulse << ",l=" << lpulse << ",a=" << answer1 << endl;
  }

  cout << "answer1  = " << answer1 << endl;
}