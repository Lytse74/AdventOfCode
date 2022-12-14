#include <fstream>
#include <iostream>
using namespace std;


int main() {
  // open the file
  ifstream is("day01.input");

  int x=0;
  int max_food1=0;
  int max_food2=0;
  int max_food3=0;

  int elve_food=0;
  int curr_elve=1;

  while ( is >> x )
  {
    //cout << "food: " << x << endl;
    elve_food += x;

    char c1 = is.get();
    char c2 = is.peek();

    if (c2 == '\n')
    {
      if ( elve_food > max_food3 )
      {
        max_food3 = elve_food;
        cout << "[" << curr_elve << "] food: " << max_food3 << endl;

        // bubble sort
        if ( max_food3 > max_food2 )
        {
          int t=max_food2; max_food2=max_food3; max_food3=t;
        }
        if ( max_food2 > max_food1 )
        {
          int t=max_food1; max_food1=max_food2; max_food2=t;
        }

      }
      elve_food = 0;
      curr_elve++;

      //cout << "Next elve" << endl;
    }
  }

  cout << "TOP3" << endl;
  cout << max_food1 << endl << max_food2 << endl << max_food3  << endl << "SUM: " << max_food1+max_food2+max_food3 << endl;

  //close the file
  is.close();
}
