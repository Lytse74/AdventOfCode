#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void rotate( char & rot, char cmd )
{
  if ( rot == 'R' && cmd == 'R' )
    rot = 'D';
  else if ( rot == 'R' && cmd == 'L' )
    rot = 'U';
  else if ( rot == 'L' && cmd == 'R' )
    rot = 'U';
  else if ( rot == 'L' && cmd == 'L' )
    rot = 'D';
  else if ( rot == 'D' && cmd == 'R' )
    rot = 'L';
  else if ( rot == 'D' && cmd == 'L' )
    rot = 'R';
  else if ( rot == 'U' && cmd == 'R' )
    rot = 'R';
  else if ( rot == 'U' && cmd == 'L' )
    rot = 'L';
}

void move( vector<string> map, int & row, int & col, char & rot, int cmd )
{
  switch ( rot )
  {
    case 'R':
    {
      int idx=col;
      
      // last col check first
      if ( idx == map[row-1].size() )
        idx = 0;

      // skip white
      while ( map[row-1][idx] == ' ' )
      {
        idx++;
        if ( idx == map[row-1].size() )
          idx = 0;
      }

      while ( cmd && map[row-1][idx] != '#' )
      {
        // move made 
        cmd--;
        col = idx+1;
        
        // next tile
        idx++;

        // last col check first
        if ( idx == map[row-1].size() )
          idx = 0;

        // skip white
        while ( map[row-1][idx] == ' ' )
        {
          idx++;
          if ( idx == map[row-1].size() )
            idx = 0;
        }
      }
    }
      break;
    case 'L':
    {
      int idx = col-2;

      // first col check first
      if ( idx < 0)
        idx = map[row-1].size() -1;
      
      // skip white
      while  ( map[row-1][idx] == ' ' )
      {
        idx--;
        if ( idx < 0)
          idx = map[row-1].size() -1;
      }

      while ( cmd && map[row-1][idx] != '#' )
      {
        // move made
        cmd--;
        col = idx+1;

        // next tile
        idx--;

        // first col check first
        if ( idx < 0)
          idx = map[row-1].size() -1;
        
        // skip white
        while  ( map[row-1][idx] == ' ' )
        {
          idx--;
          if ( idx < 0)
            idx = map[row-1].size() -1;
        }
      }
    }
      break;
    case 'D':
    {
      int idx = row;

      // last row check first
      if ( idx == map.size() )
        idx = 0;

      // skip white
      while ( map[idx][col-1] == ' ' )
      {
        idx++;
        if ( idx == map.size() )
          idx = 0;
      }

      while ( cmd && map[idx][col-1] != '#' )
      {
        // move made
        cmd--;
        row = idx+1;

        // next tile
        idx++;

        // last row check first
        if ( idx == map.size() )
          idx = 0;

        // skip white
        while ( map[idx][col-1] == ' ' )
        {
          idx++;
          if ( idx == map.size() )
            idx = 0;
        }
      }
    }
      break;
    case 'U':
    {
      int idx = row-2;

      // first row check first
      if ( idx < 0 )
        idx = map.size() -1;

      // skip white
      while ( map[idx][col-1] == ' ' )
      {
        idx--;
        if ( idx < 0 )
          idx = map.size() -1;
      }

      while ( cmd && map[idx][col-1] != '#' )
      {
        // move made
        cmd--;
        row = idx+1;

        // next tile
        idx--;

        // first row check first
        if ( idx < 0 )
          idx = map.size() -1;

        // skip white
        while ( map[idx][col-1] == ' ' )
        {
          idx--;
          if ( idx < 0 )
            idx = map.size() -1;
        }
      }
    }
      break;
    default:
      break;
  }

}

int main() {
  // open the file
  ifstream is("day22.input");
  string str;

  vector<string> map;
  string cmds;

  char rot = 'R';
  int row = 1;
  int col = 1;

  while ( getline( is, str ) && str.size() ) {
    map.push_back(str);
  }

  getline( is, cmds );

  for ( auto str : map )
  {
    cout << str << endl;
  }

  cout << cmds << endl;

  //close the file
  is.close();
    
  // find the first position
  col = map[0].find('.') + 1;

  istringstream icmds(cmds);
  int maxcmd = 0;
  while ( icmds )
  {
    if ( icmds.peek() == 'L' || icmds.peek() == 'R' )
    {
      // Rotate
      char cmd;
      icmds >> cmd;
      cout << "rotate: " << cmd << endl;
      rotate( rot, cmd );
    } 
    else if ( icmds.peek() != EOF )
    {
      // Move
      int cmd;
      icmds >> cmd;
      cout << "move: " << cmd << endl;
      if (cmd > maxcmd) maxcmd = cmd;
      move( map, row, col, rot, cmd );
    }
  }

  cout << "row: " << row << ", col: " << col << ", rot: " << rot << endl;
  int result = 0;

  switch ( rot )
  {
    case 'R':
      result += 0;
      break;
    case 'D':
      result += 1;
      break;
    case 'L':
      result += 2;
      break;
    case 'U':
      result += 3;
      break;
    default:
      break;
  }

  result += 1000*row;
  result += 4*col;
  cout << "maxcmd: " << maxcmd << endl;
  cout << "result: " << result << endl;
}
