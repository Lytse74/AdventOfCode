#include <fstream>
#include <iostream>
using namespace std;

int score( char opponent, char player )
{

  int val = 0;

  switch ( opponent )
  {
    case 'A': // rock
      switch ( player )
      {
        case 'X':
          val = 1 + 3;
          break;
        case 'Y':
          val = 2 + 6;
          break;
        case 'Z':
          val = 3 + 0;
          break;
        default:
          break;
      }
      break;
    case 'B': // paper
      switch ( player )
      {
        case 'X':
          val = 1 + 0;
          break;
        case 'Y':
          val = 2 + 3;
          break;
        case 'Z':
          val = 3 + 6;
          break;
        default:
          break;
      }
      break;
    case 'C': // scissors
      switch ( player )
      {
        case 'X':
          val = 1 + 6;
          break;
        case 'Y':
          val = 2 + 0;
          break;
        case 'Z':
          val = 3 + 3;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
  return val;
}

int main() {
  // open the file
  ifstream is("day02.input");

  char opponent;
  char player;

  int total_score = 0;

  while ( is >> opponent >> player )
  {
    //cout << opponent << player << score( opponent, player ) << endl;
    total_score += score( opponent, player );
  }

  cout << "total_score: " << total_score << endl;

  //close the file
  is.close();
}
