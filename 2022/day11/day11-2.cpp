#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

struct MonkeyS
{
  int nr;
  list<long> items;
  int cmd;
  int cmd_op;
  int test;
  int tst_true;
  int tst_false;
  int throws=0;
};

int main() {
  // open the file
  ifstream is("day11.input");
  string str;

  MonkeyS my_monks[8];
  int idx=-1;
  size_t found;
  
  // Get the monkeys
  while ( getline ( is , str ) )
  {
    if ( str.find("Monkey " ) != string::npos )
    {
      ++idx;
      str.erase(0,7);
      istringstream iss(str);
      iss >> my_monks[idx].nr;
    }
    else if ( str.find("Starting items: " ) != string::npos )
    {
      str.erase(0,18);
      istringstream iss(str);
      int tmp;
      char skip;
      while ( iss >> tmp )
      {
        my_monks[idx].items.push_back( tmp );
        if ( iss.peek() == ',' )
          iss >> skip;
      }
    }
    else if ( str.find("Operation:" ) != string::npos )
    {
      //cout << str <<endl;
      str.erase(0,23);
      //cout << str <<endl;
      if ( str.compare(0,1,"+") == 0 ) 
        my_monks[idx].cmd = 0;
      if ( str[0] == '*' )
        my_monks[idx].cmd = 1;

      str.erase(0,2);
      istringstream iss(str);
      if ( iss.peek() == 'o' )
        my_monks[idx].cmd = 2;
      else
        iss >> my_monks[idx].cmd_op;
    }
    else if ( str.find("Test:" ) != string::npos )
    {
      str.erase(0,21);
      istringstream iss(str);
      iss >> my_monks[idx].test;
    }
    else if ( str.find("If true:" ) != string::npos )
    {
      str.erase(0,29);
      istringstream iss(str);
      iss >> my_monks[idx].tst_true;
    }
    else if ( str.find("If false:" ) != string::npos )
    {
      str.erase(0,30);
      istringstream iss(str);
      iss >> my_monks[idx].tst_false;
    }
  }

/*
  for ( auto i=0; i<4; ++i )
  {
    cout << my_monks[i].nr << endl;
    for ( int& j : my_monks[i].items )
      cout << j << endl;
    cout << my_monks[i].cmd << endl;
    cout << my_monks[i].cmd_op << endl;
    cout << my_monks[i].test << endl;
    cout << my_monks[i].tst_true << endl;
    cout << my_monks[i].tst_false << endl;
    cout << str << endl;
  }
*/
  for ( auto turn=0; turn<10000; ++turn )
  {
    for ( auto monk=0; monk<8; ++ monk )
    {
      for ( long& nr: my_monks[monk].items)
      {
        // do the math
        if ( my_monks[monk].cmd == 0)
          nr = nr + my_monks[monk].cmd_op;
        if ( my_monks[monk].cmd == 1)
          nr = nr * my_monks[monk].cmd_op;
        if ( my_monks[monk].cmd == 2)
          nr = nr * nr;
        nr %= 9699690;
        //nr = nr / 3;

        // throw
        if ( ( nr % my_monks[monk].test ) == 0 )
          my_monks[my_monks[monk].tst_true].items.push_back(nr);
        else
          my_monks[my_monks[monk].tst_false].items.push_back(nr);
        my_monks[monk].throws++;
      }
      int cnt = my_monks[monk].items.size();
      for ( auto i=0; i<cnt;++i)
        my_monks[monk].items.pop_front();
    }
  }

  long max1=0,max2=0;

  for ( auto i=0; i<8; ++i )
  {
    cout << "throws: " << my_monks[i].throws << endl;
    if ( my_monks[i].throws > max2 )
      max2 = my_monks[i].throws;

    if ( max2 > max1 )
    {
      int t=max1; max1=max2; max2=t;
    }
  }

  cout << "P1:" << max1 *  max2  << endl;


  //close the file
  is.close();
 }
