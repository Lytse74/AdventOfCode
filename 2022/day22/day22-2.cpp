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

void move( vector<string> map, int & row, int & col, char & rot, int & cmd )
{
  cout << "rot: " << rot << ", cmd: " << cmd << endl;
  
  switch ( rot )
  {
    case 'R':
    {
      while ( cmd )
      {
        int idx=col;
      
        // last col check first
        // four situations
        // A1
        if ( idx == 150 && row>0 && row<=50 )
        {
          if ( cmd && map[150-row][col-51] != '#')
          {
            cmd--;
            row = 151 - row;
            col = col - 50;
            rotate(rot,'R');
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // B1
        if ( idx == 100 && row>50 && row<=100 )
        {
          if ( cmd && map[50-1][row+50-1] != '#')
          {
            cmd--;
            col = row + 50;
            row = 50;
            rotate(rot,'L');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // A2
        if ( idx == 100 && row>100 && row<=150 )
        {
          if ( cmd && map[150-row][col+49] != '#')
          {
            cmd--;
            row = 151 - row;
            col = col + 50;
            rotate(rot,'R');
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // E1 
        if ( idx == 50  && row>150 && row<=200 )
        {
          if ( cmd && map[150-1][row-100-1] != '#')
          {
            cmd--;
            col = row - 100;
            row = 150;
            rotate(rot,'L');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }

        if ( cmd && map[row-1][idx] == '.' )
        {
          // move made 
          cmd--;
          col = idx+1;
          
          // next tile
          idx++;
        }

        else if ( cmd && map[row-1][idx] == '#' )
        {
          cmd = 0;
        }
      }
    }
      break;
    case 'L':
    {
      while ( cmd )
      {
        int idx = col-2;

        // first col check first
        // four situations
        // C1
        if ( idx == 49 && row>0 && row<=50 )
        {
          if ( cmd && map[150-row][col-51] != '#' )
          {
            cmd--;
            row = 151 - row;
            col = col - 50;
            rotate(rot,'L');
            rotate(rot,'L');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // D1
        if ( idx == 49 && row>50 && row<=100 )
        {
          if ( cmd && map[100][row-50-1] != '#' )
          {
            cmd--;
            col = row - 50;
            row = 101;
            rotate(rot,'L');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // C2
        if ( idx == -1 && row>100 && row<=150 )
        {
          if ( cmd && map[150-row][col+49] != '#' )
          {
            cmd--;
            row = 151 - row;
            col = col + 50;
            rotate(rot,'R');
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }
        // F1
        if ( idx == -1 && row>150 && row<=200 )
        {
          if ( cmd && map[0][row-100-1] != '#' )
          {
            cmd--;
            col = row - 100;
            row = 1;
            rotate(rot,'L');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd = 0;
        }

        if ( cmd && map[row-1][idx] == '.' )
        {
          // move made
          cmd--;
          col = idx+1;

          // next tile
          idx--;
        }

        else if ( cmd && map[row-1][idx] == '#' )
        { 
          cmd = 0;
        }
      }
    }
      break;
    case 'D':
    {
      while ( cmd )
      {
        int idx = row;

        // last row check first
        // three sutuations
        // G1
        if ( idx == 200 && col>0 && col<=50 )
        {
          if ( cmd && map[0][col+100-1] != '#' )
          {
            cmd--;
            col = col+100;
            row = 1;
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;
        }
        // E2
        if ( idx == 150 && col>50 && col<=100 )
        {
          if ( cmd && map[col+100-1][idx-100-1] != '#' )
          {
            cmd--;
            row = col + 100;
            col = 50;
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;
        }
        // B2
        if ( idx == 50 && col>100 && col<=150 )
        {
          if ( cmd && map[col-50-1][idx+50-1] != '#' )
          {
            cmd--;
            row = col - 50;
            col = 100;
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;
        }

        if ( cmd && map[idx][col-1] == '.' )
        {
          // move made
          cmd--;
          row = idx+1;

          // next tile
          idx++;
        }

        else if ( cmd && map[idx][col-1] == '#' )
        {
          cmd = 0;
        }
      }
    }
      break;
    case 'U':
    {
      while ( cmd )
      {
        int idx = row-2;

        // first row check first
        // three situations
        // D2
        if ( idx == 99 && col > 0 && col <= 50 )
        {
          if ( cmd && map[col+50-1][50] != '#' )
          {
            cmd--;
            row = col + 50;
            col = 51;
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;

        }
        // F2
        if ( idx == -1 && col > 50 && col <= 100 )
        {
          if ( cmd && map[col+100-1][0] != '#' )
          {
            cmd--;
            row = col + 100;
            col = 1;
            rotate(rot,'R');
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;
        }
        // G2
        if ( idx == -1 && col > 100 && col <= 150 )
        {
          if ( cmd && map[199][col-100-1] != '#' )
          {
            cmd--;
            col = col-100;
            row = 200;
            if ( cmd )
              move( map, row, col, rot, cmd );
          }
          else
            cmd=0;
        }

        if ( cmd && map[idx][col-1] == '.' )
        {
          // move made
          cmd--;
          row = idx+1;

          // next tile
          idx--;
        }

        else if ( cmd && map[idx][col-1] == '#' )
        {
          cmd = 0;
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
  //col = 50;
  //row = 101;
  //rot = 'U';
  cout << "position: (" << row << "," << col << ")" << endl;

  istringstream icmds(cmds);
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
      move( map, row, col, rot, cmd );
      cout << "position: (" << row << "," << col << ")" << endl;
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
  cout << "result: " << result << endl;
}
