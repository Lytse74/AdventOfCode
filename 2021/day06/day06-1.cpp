#include <fstream>
#include <iostream>
#include <array>
#include <string>

using namespace std;

void AnotherDay( array<long long,9> & arr )
{
  long long tmp = arr[0];

  for ( int i=0; i<8; ++i )
  {
    arr[i] = arr[i+1];
  }
  arr[8] = tmp;
  arr[6] += tmp;
}

void Print( const array<long long,9> & arr )
{
  long long total=0;

  for ( const auto& a : arr )
  {
    cout << a << ',';
    total += a;
  }
  cout << total << endl;
}

int main() {
  // open the file
  ifstream is("day06.input");
   
  int cnt=0;
  int lanternfish=-1;
  char ch;

  array<long long,9> arr = { 0,0,0,0,0,0,0,0,0 };

  while ( is >> lanternfish )
  {
    is >> ch;
    cout << lanternfish << endl;
    arr[lanternfish]++;
    ++cnt;
  }
  cout << "cnt: " << cnt << endl;

  Print( arr );
  for ( int i=0; i<18; ++i )
    AnotherDay( arr );
  Print( arr );
  for ( int i=18; i<80; ++i )
    AnotherDay( arr );
  Print( arr );
  for ( int i=80; i<256; ++i )
    AnotherDay( arr );
  Print( arr );

  //close the file
  is.close();


}
