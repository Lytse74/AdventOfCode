#include <fstream>
#include <iostream>
#include <set>
using namespace std;

char move( pair<int,int> & h, pair<int,int> & t, char cmd )
{
  char moved = ' ';
  pair<int,int> diff = make_pair( h.first - t.first, h.second - t.second );

  switch ( ( diff.first + 1 ) * 3 + diff.second + 1 )
  {
    case 4: // ( 0, 0 )
      moved = ' ';
      break;

    case 2: // (-1, 1 )
      switch ( cmd ) 
      {
        case 'U':
        case 'L':
        case 'A':
          moved = 'A';
          break;
        case 'E':
          moved = 'U';
          break;
        case 'B':
          moved = 'L';
          break;
        default:
          break;
      }
      break;
    case 5: // ( 0, 1 )
      switch ( cmd ) 
      {
        case 'U':
        case 'A':
        case 'E':
          moved = cmd;
          break;
        default:
          break;
      }
      break;
    case 8: // ( 1, 1 )
      switch ( cmd ) 
      {
        case 'U':
        case 'R':
        case 'E':
          moved = 'E';
          break;
        case 'A':
          moved = 'U';
          break;
        case 'C':
          moved = 'R';
          break;
        default:
          break;
      }
      break;
    case 1: // ( -1, 0 )
      switch ( cmd ) 
      {
        case 'L':
        case 'A':
        case 'B':
          moved = cmd;
          break;
        default:
          break;
      }
      break;
    case 7: // ( 1, 0 )
      switch ( cmd ) 
      {
        case 'R':
        case 'E':
        case 'C':
          moved = cmd;
          break;
        default:
          break;
      }
      break;
    case 0: // ( -1, -1 )
      switch ( cmd ) 
      {
        case 'L':
        case 'D':
        case 'B':
          moved = 'B';
          break;
        case 'A':
          moved = 'L';
          break;
        case 'C':
          moved = 'D';
          break;
        default:
          break;
      }
      break;
    case 3: // ( 0, -1 )
      switch ( cmd ) 
      {
        case 'D':
        case 'B':
        case 'C':
          moved = cmd;
          break;
        default:
          break;
      }
      break;
    case 6: // ( 1, -1 )
      switch ( cmd ) 
      {
        case 'R':
        case 'D':
        case 'C':
          moved = 'C';
          break;
        case 'E':
          moved = 'R';
          break;
        case 'B':
          moved = 'D';
          break;
        default:
          break;
      }
      break;
    default:
      cout << "ERROR" << endl;
      break;
  }

  switch ( cmd )
  {
    case 'U':
      h.second = h.second + 1;     
      break;
    case 'D':
      h.second = h.second - 1;     
      break;
    case 'L':
      h.first = h.first - 1;     
      break;
    case 'R':
      h.first = h.first + 1;     
      break;
    case 'A':
      h.first = h.first - 1;     
      h.second = h.second + 1;     
      break;
    case 'B':
      h.first = h.first - 1;     
      h.second = h.second - 1;     
      break;
    case 'C':
      h.first = h.first + 1;     
      h.second = h.second - 1;     
      break;
    case 'E':
      h.first = h.first + 1;     
      h.second = h.second + 1;     
      break;
    default:
      cout << "ERROR: " << cmd << endl;
  }

  return moved;
}


int main() {
  // open the file
  ifstream is("day09.input");

  pair<int,int> head = { 0, 0 };
  pair<int,int> tail1 = { 0, 0 };
  pair<int,int> tail2 = { 0, 0 };
  pair<int,int> tail3 = { 0, 0 };
  pair<int,int> tail4 = { 0, 0 };
  pair<int,int> tail5 = { 0, 0 };
  pair<int,int> tail6 = { 0, 0 };
  pair<int,int> tail7 = { 0, 0 };
  pair<int,int> tail8 = { 0, 0 };
  pair<int,int> tail9 = { 0, 0 };
  set<pair<int,int>> cover1;
  set<pair<int,int>> cover2;
  cover2.insert( tail9 );
  cover1.insert( tail1 );

  char command = ' ';
  int repeat = 0;

  while ( is >> command >> repeat )
  {
    //cout << command << ' ' << repeat << endl; 
    while ( repeat-- > 0 )
    {
      char ch1 = move( head, tail1, command );
      if ( ch1 == ' ' )
        continue;
        
      char ch2 = move( tail1, tail2, ch1 );
      cover1.insert(tail1);

      if ( ch2 == ' ' )
        continue;
      
      char ch3 = move( tail2, tail3, ch2 );
      if ( ch3 == ' ' )
        continue;
      
      char ch4 = move( tail3, tail4, ch3 );
      if ( ch4 == ' ' )
        continue;
      
      char ch5 = move( tail4, tail5, ch4 );
      if ( ch5 == ' ' )
        continue;
      
      char ch6 = move( tail5, tail6, ch5 );
      if ( ch6 == ' ' )
        continue;
      
      char ch7 = move( tail6, tail7, ch6 );
      if ( ch7 == ' ' )
        continue;
      
      char ch8 = move( tail7, tail8, ch7 );
      if ( ch8 == ' ' )
        continue;
      
      char ch9 = move( tail8, tail9, ch8 );
      if ( ch9 == ' ' )
        continue;
      
      move( tail9, tail9, ch9 );
      cover2.insert( tail9 );
    }
  }

  cout << "HEAD (" << head.first << ',' << head.second << ')' << endl;
  cout << "TAIL1 (" << tail1.first << ',' << tail1.second << ')' << endl;
  cout << "TAIL3 (" << tail3.first << ',' << tail3.second << ')' << endl;
  cout << "TAIL4 (" << tail4.first << ',' << tail4.second << ')' << endl;
  cout << "TAIL5 (" << tail5.first << ',' << tail5.second << ')' << endl;
  cout << "TAIL6 (" << tail6.first << ',' << tail6.second << ')' << endl;
  cout << "TAIL7 (" << tail7.first << ',' << tail7.second << ')' << endl;
  cout << "TAIL8 (" << tail8.first << ',' << tail8.second << ')' << endl;
  cout << "TAIL9 (" << tail9.first << ',' << tail9.second << ')' << endl;

  cout << "P1:" << cover1.size() << endl;
  cout << "P2:" << cover2.size() << endl;

  //close the file
  is.close();
}