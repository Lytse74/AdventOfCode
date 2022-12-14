#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void readCard( int bingo_card[5][5], ifstream& is )
{
  for( int i=0; i<5; ++i )
  {
    for( int j=0; j<5; ++j )
    {
      is >> (bingo_card[i][j]);
    }
  }
}

void printCard( int bingo_card[5][5], vector<int> bingo_nr, int& turn, int& rest, int& last )
{
  int win[5][5];

  cout << "-=| BINGOCARD |=-" << endl;
  for( int i=0; i<5; ++i )
  {
    for( int j=0; j<5; ++j )
    {
      win[i][j] = bingo_nr[bingo_card[i][j]];
      cout << (bingo_card[i][j]) << " ";
    }
    cout << endl;
  }

  // check the min win
  int minb = 100;

  // check the rows
  for( int i=0; i<5; ++i )
  {
    // check max win
    int maxb = 0;
    for( int j=0; j<5; ++j )
    {
      if (win[i][j] > maxb)
        maxb = win[i][j];
    }
    cout << "row: " << i << " wins in " << maxb+1 << " turns" << endl;
    if ( maxb < minb )
      minb = maxb;
  }

  // check the colums
  for( int j=0; j<5; ++j )
  {
    // check max win
    int maxb = 0;
    for( int i=0; i<5; ++i )
    {
      if (win[i][j] > maxb)
        maxb = win[i][j];
    }
    cout << "col: " << j << " wins in " << maxb+1 << " turns" << endl;
    if ( maxb < minb )
      minb = maxb;
  }

  // determine last
  last = 0;
  for (int i=0; i<100; ++i)
  {
    if ( bingo_nr[i] == minb )
      last = i;
  }
  cout << "card wins in " << minb+1 << " when number " << last << " is called" << endl;

  // detrmine rest
  rest = 0;
  for( int i=0; i<5; ++i )
  {
    for( int j=0; j<5; ++j )
    {
      if ( win[i][j] > minb )
        rest += bingo_card[i][j];
    }
  }

  cout << "rest is " << rest << endl;

  turn = minb+1;

}

int main() {
  // open the file
  ifstream is("day04.input");

  vector<int> bingo_nr(100);

  // read the bingo numbers
  char ch=',';
  int bingo;
  int cnt = 0;

  is >> bingo;
  bingo_nr[bingo] = cnt++;

  while ( ch==',' && is >> ch >> bingo )
  { 
    bingo_nr[bingo] = cnt++;
    ch = is.peek();
  }

  for(int i : bingo_nr) 
    cout << "i = " << i << endl;

  // read a bingo card
  int bingo_card[5][5] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; 
  int turn, maxturn=100;
  int rest,keeprest=1000;
  int last,keeplast=1000;

  while ( is.peek() != EOF )
  {
    readCard( bingo_card, is );
    
    // print the card
    printCard( bingo_card, bingo_nr, turn, rest, last );

    if ( turn < maxturn )
    { 
      maxturn = turn;
      keeprest = rest;
      keeplast = last;
    }
  }
    
  //close the file
  is.close();

  cout << "winning number is: " << keeplast * keeprest << " in " << maxturn << " turns with " << keeplast << " last called and " << keeprest << " as rest" << endl;
}