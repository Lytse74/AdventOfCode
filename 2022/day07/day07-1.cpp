#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <list>
using namespace std;


map<string,int> my_map;
list<string> my_list;

int main() {
  // open the file
  ifstream is("day07.input");
  string str;
  string cur_dir = "";
  int cur_lvl = 0;
  
  while ( getline ( is , str ) )
  {
    istringstream iss(str);
    string str2;

    if ( str[0] == '$')
    { 
      //cout << "C:" << str << endl;
      // skip $
      iss >> str2;

      // take cmd
      iss >> str2;

      if ( str2.compare("cd") == 0 )
      { 
        iss >> str2;
        if ( str2.compare("..") == 0 )
        {
          cur_dir = my_list.back(); my_list.pop_back();
          cur_lvl -= 1;
        }
        else
        {
          my_list.push_back( cur_dir );
          cur_dir = str2;
          cur_lvl += 1;
          string mtp;
          list<string>::iterator it;
          for (it = my_list.begin(); it != my_list.end(); it++)
          {
            mtp = mtp + *it + '/';
          }
          mtp = mtp + cur_dir + '/';
          my_map.insert( make_pair( mtp, 0) );
          cout << mtp << endl;
        }

        //cout << "lvl:" << cur_lvl << " ";
        //cout << "path:" ;
        for ( string& s: my_list )
        {
          //cout << s << ",";
        }
        //cout << cur_dir << endl;
      }
    }
    else
    {
      //cout << "D:" << str << endl;
      if ( iss.peek() != 'd' )
      {
        int size;
        iss >> size;
        cout << "size: " << size << endl;

        // add the size to the curr dir in the map
        string mtp;
        list<string>::iterator it2;
        map<string,int>::iterator it;
        for (it2 = my_list.begin(); it2 != my_list.end(); it2++)
        {
          mtp = mtp + *it2 + '/';
          if ( mtp.compare("/") != 0 )
          {
            cout << mtp << endl;
            it = my_map.find(mtp); 
            if (it != my_map.end())
              it->second += size;
          }
        }
        mtp = mtp + cur_dir + '/';
        
        it = my_map.find(mtp); 
        if (it != my_map.end())
          it->second += size;
      }
    }
  }

  map<string, int>::iterator it;
  int val = 0;
  int tsize = 0;
  int mindir = 70000000;

  for (it = my_map.begin(); it != my_map.end(); it++)
  {
    cout <<   (it->first)
              << ':'
              << it->second   // string's value 
              << std::endl;

    if ( it->second <= 100000 )
      val += it->second;

    if ( (it->first).compare("///") == 0 )
      tsize = it->second;
    
    if ( it->second >= (30000000 - (70000000-tsize)) 
      && it->second <= mindir )
      mindir = it->second;
    
  }

  cout << "val: " << val << endl;
  cout << "tofree: " <<  (30000000 - (70000000-tsize) ) << " mindir: " << mindir << endl;

  //close the file
  is.close();
 }
