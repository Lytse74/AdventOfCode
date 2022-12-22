#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int recurse( int cur_val, int d, int trn_a, int start_a, int trn_b, int start_b, map<int,int> flw, int rd[60][60] )
{
  cout << "d:" << d << " cur_val:" << cur_val << endl;
  
  // check for negative trn
  if ( trn_a <= 2 && trn_b <= 2)
    return 0;


  // iterate map and find best move
  map<int,int>::iterator it1;

  // find the 'best' room
  int best_val=0;
  int best_room=-1;

  for (it1 = flw.begin(); it1 != flw.end(); it1++ )
  {
    // calcualte value of one of the flows
    int val;
    int cost;
    if ( trn_a >= trn_b )
    {
      cost = rd[start_a][it1->first] +1;
      if ( cost >= trn_a )
        val = 0;
      else
        val = (trn_a - cost )*it1->second;
    }
    else
    {
      cost = rd[start_b][it1->first] +1;
      if ( cost >= trn_b )
        val = 0;
      else
      val = (trn_b - cost )*it1->second;
    }

    // make a new map
    map<int,int> flw_cp(flw);
    flw_cp.erase(it1->first);

    // add to val take right one
    if ( val > 0 )
    {
      if ( trn_a >= trn_b )
        val += recurse(cur_val+val,d+1, trn_a - rd[start_a][it1->first]-1,it1->first, trn_b, start_b, flw_cp, rd);
      else
        val += recurse(cur_val+val,d+1, trn_a, start_a, trn_b -rd[start_b][it1->first]-1, it1->first, flw_cp, rd);
    }

    if ( val >= best_val ) 
    { 
      best_val=val; 
      best_room=it1->first;
    }
  }

  //if ( trn_a >= trn_b )
  //  cout << "d:" << d << " A trn:" << trn_a << " start:" << start_a << " best:" << best_room << " best_val:" << best_val << endl;
  //else
  //  cout << "d:" << d << " B trn:" << trn_b << " start:" << start_b << " best:" << best_room << " best_val:" << best_val << endl;

  return best_val;
}

int main() {
  // open the file
  ifstream is("day16.input");
  string str;

  map<string,int> room_number;
  int nrof_room=-1;

  map<int,int> roomnr_flow;
  int room_dist[60][60];

  for ( auto i=0; i<60; ++i )
    for ( auto j=0; j<60; ++j )
      room_dist[i][j] = -1;

  while ( getline( is, str ) )
  {
    istringstream iss(str);

    string str2;
    string curr_room;

    int strindx=0;

    while ( iss >> str2 )
    {
        istringstream iss2(str2);

        // get the start rooms
        if ( strindx == 1 )
        {
          curr_room = str2;
          if ( room_number.find(curr_room) == room_number.end())
          {
            room_number.insert( make_pair( curr_room,++nrof_room));
          }
          int tmp = room_number[ curr_room ];
          room_dist[tmp][tmp] = 0;
        }

        // get the flows
        if ( strindx == 4)
        {
          int tmp = stoi(str2.substr(5));
          if ( tmp > 0 )
          {
            roomnr_flow.insert( make_pair( room_number[curr_room], tmp ));
          }
        }

        // get the paths   
        if ( strindx >= 9)
        {
          string conn_room = str2.substr( 0, 2 );
          if ( room_number.find( conn_room ) == room_number.end() )
          {
            room_number.insert( make_pair( conn_room, ++nrof_room));
          }
          int tmp = room_number[ curr_room ];
          int tmp2 = room_number[ conn_room ];
          room_dist[tmp][tmp2] = 1;
        }

        cout << str2 << "|";
        strindx++;
    }
    cout << endl;
  }

  // calculate the distances
  for ( auto dist=2; dist<60; ++dist)
  {
    for ( auto i=0; i<60; ++i )
    {
      for ( auto j=0; j<60; ++j )
      {
        int val=0;
        for ( auto t=0; t<60; ++t )
        {
          if ( room_dist[i][t] == 1 && room_dist[t][j] >= dist - 1 && room_dist[t][j] < dist ) 
          {
            if ( room_dist[i][j]<0 )
            {
              room_dist[i][j] = dist;
              room_dist[j][i] = dist;
            }
          }
        }
      }
    }
  }

  int start = room_number["AA"];
  int best = recurse( 0, 0, 30, start, 0, start, roomnr_flow, room_dist );
  cout << "P1 best:" << best << endl;

  start = room_number["AA"];
  best = recurse( 0, 0, 26, start, 26, start, roomnr_flow, room_dist );
  cout << "P2 best:" << best << endl;

  //close the file
  is.close();
 }
