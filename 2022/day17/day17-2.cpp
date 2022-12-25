#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void init_stack( short stack[130000] )
{
  for ( auto i=0; i<130000; ++i )
  {
    stack[i] = 0x101;
  }
  stack[0] = 0x1ff;
}

struct BlockS 
{
  short top;
  short midt;
  short midb;
  short bot;
};

void print_stack( short stack[130000], int floor, int ceiling, BlockS blk, int blk_pos )
{
  for ( auto i = ceiling; i>= floor; --i )
  {
    short tmp = 0x100;
    while (tmp)
    {
      if ( stack[i] & tmp )
        cout << '#';
      else
      {
        // also check falling block
        if ( i == blk_pos && ( blk.bot & tmp )
          || i == blk_pos + 1 && ( blk.midb & tmp )
          || i == blk_pos + 2 && ( blk.midt & tmp )
          || i == blk_pos + 3 && ( blk.top & tmp ) )
        {
          cout << '@';
        }
        else
          cout << '.';
      }
      tmp = tmp >> 1;
    }
    cout << " row:" << i;
    if ( i == blk_pos )
      cout << " <<<< blk_pos";

    cout << endl;
  }
}

const BlockS blocks[6] = { { 0x00, 0x00, 0x00 ,0x3c }
                         , { 0x00, 0x10, 0x38 ,0x10 }
                         , { 0x00, 0x08, 0x08, 0x38 }
                         , { 0x20, 0x20, 0x20, 0x20 }
                         , { 0x00, 0x00, 0x30, 0x30 } 
                         , { 0x00, 0x00, 0x00, 0x00 } };

int main() {
  // open the file
  ifstream is("day17.input");
  string str;

  short stack[130000];
  int floor=0;
  int ceiling=floor;
  
  BlockS block;
  int blk_pos;
  
  init_stack( stack );

  while ( getline( is, str ) )
  {
    istringstream iss(str);
    char wind = '^';
    vector<char> windl;
    vector<char>::iterator windl_it;

    while ( iss >> wind )
      windl.push_back(wind);

    windl_it = windl.begin();
    
    // drop the blocks
    for ( auto i=0; i<3325; ++i)
    {
      // let each block fall
      block = blocks[i%5];
      blk_pos = ceiling+4;
       
      //print_stack( stack, ceiling-12 , blk_pos+4, block, blk_pos );

      // make it apear 
      while ( ( block.bot & stack[blk_pos] ) == 0
           && ( block.midb & stack[blk_pos+1] ) == 0 )
      {
        // apply the wind
        wind = '^';
        wind = *windl_it;
        windl_it++;
        if ( windl_it == windl.end() )
        {
          windl_it = windl.begin();
          cout << "i:" << i%5 << " block:" << i << " blk_pos:" << blk_pos << endl;
          //print_stack( stack, ceiling-12 , blk_pos+4, block, blk_pos );
        }
        //cout << wind << " " << windl_it - windl.begin() << endl;
        if ( wind == '>' )
        {
          // only move if allowed
          if ( ( ( block.bot >> 1 ) & stack[blk_pos] ) == 0
            && ( ( block.midb >> 1 ) & stack[blk_pos+1] ) == 0
            && ( ( block.midt >> 1 ) & stack[blk_pos+2] ) == 0
            && ( ( block.top >> 1 ) & stack[blk_pos+3] ) == 0 )
          {
            block.top = block.top >> 1;
            block.midt = block.midt >> 1;
            block.midb = block.midb >> 1;
            block.bot = block.bot >> 1;
          }
        }
        else if ( wind == '<' )
        {
          // only move if allowed
          if ( ( ( block.bot << 1 ) & stack[blk_pos] ) == 0 
            && ( ( block.midb << 1 ) & stack[blk_pos+1] ) == 0
            && ( ( block.midt << 1 ) & stack[blk_pos+2] ) == 0
            && ( ( block.top << 1 ) & stack[blk_pos+3] ) == 0 )
          {
            block.top = block.top << 1;
            block.midt = block.midt << 1;
            block.midb = block.midb << 1;
            block.bot = block.bot << 1;
          }
        }

        //print_stack( stack, ceiling-12 , blk_pos+4, block, blk_pos );
        // see if it can drop
        blk_pos--;
      }

      // fix the block and move the ceiling
      stack[blk_pos+1] |= block.bot;
      stack[blk_pos+2] |= block.midb;
      stack[blk_pos+3] |= block.midt;
      stack[blk_pos+4] |= block.top;

      int tmp = (blk_pos - ceiling) + (block.bot ? 1 : 0) + (block.midb ? 1 : 0) + (block.midt ? 1 : 0) + (block.top ? 1 : 0);
      ceiling += ( tmp > 0 ) ? tmp : 0;
    }
  }

  block = blocks[5];

  print_stack( stack, ceiling-30 , ceiling+8, block, blk_pos );

  // P2 test: pattern repeats every 35 blocks stacking 53 rows starting at 14 blocks
  // calc 2022 / 35 * 53 + 22 + 25 (27 blocks) = 3068
  // calc 1.000.000.000.000 / 35 * 53 + 25 (15 blocks) = 1514285714288

  // P2 input: pattern repeats every 1725 blocks stacking 2685 rows starting at 1722 blocks
  // calc (1.000.000.000.000 / 1725 -1) * 2685 + 5184 ( 1600 + 1725 blocks) = 1556521739139

  //close the file
  is.close();
 }
