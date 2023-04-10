#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

struct ExprS 
{
  char operation;
  string operand1;
  string operand2;
};

struct ValueS
{
  bool hasValue;
  long long value;
  ExprS expression;
};

map<string,ValueS> values;

long long calculate( string str )
{
  long long value=0;
  long long val1=0;
  long long val2=0;

  ValueS tmp;

  tmp = values[str];

  if ( tmp.hasValue )
  {
    value = tmp.value;
  }
  else
  {
    val1 = calculate( tmp.expression.operand1 );
    val2 = calculate( tmp.expression.operand2 );

    switch ( tmp.expression.operation )
    {
      case '+':
        value = val1 + val2;
        break;
      case '-':
        value = val1 - val2;
        break;
      case '/':
        value = val1 / val2;
        break;
      case '*':
        value = val1 * val2;
        break;
      default:
        break;
    }

    //tmp.value = value;
    //tmp.hasValue = true;

    //cout << tmp.expression.operand1 << tmp.expression.operation << tmp.expression.operand2 << "=" << str << ":" << val1 << tmp.expression.operation << val2 << "=" << value << endl;

    //values[str] = tmp;
  }

  return value;
}

long long calculateHumn()
{
  long long val1=0;
  long long val2=0;

  int incr = 0;
  
  ValueS tmp1 = values["root"];
  ValueS tmp2 = values["humn"];

  // This is the hand tweaked answer
  //tmp2.value = 3441198826073;

  // should do this another way
  //values["humn"] = tmp2;

  val1 = calculate( tmp1.expression.operand1 );
  val2 = calculate( tmp1.expression.operand2 );

  long long distance = val1 - val2;

  //
  for ( long long inc = 1; inc<=20000; ++inc)
  {
    tmp2.value += 1;
    values["humn"] = tmp2;

    val1 = calculate( tmp1.expression.operand1 );
    val2 = calculate( tmp1.expression.operand2 );

    long long ddis = distance - val1 + val2;

    cout << inc << ":" << ddis << endl;
  }

  // Try once
  long long inc = 19995* distance / 673032 ;// - 1163; initial value of humn

  tmp2.value += (inc-20000);
  values["humn"] = tmp2;
  
  val1 = calculate( tmp1.expression.operand1 );
  val2 = calculate( tmp1.expression.operand2 );

  // Second try
  long long distance2 = val1 - val2;

  inc = 19995* distance2 / 673032 ;// - 1163; initial value of humn

  tmp2.value += inc;
  values["humn"] = tmp2;
  
  val1 = calculate( tmp1.expression.operand1 );
  val2 = calculate( tmp1.expression.operand2 );
  
  // Try a third time?
  long long distance3 = val1 - val2;

  inc = 19995* distance3 / 673032 ;// - 1163; initial value of humn

  // Because inc < 5000 wee can approach the correct answer

  while ( distance3 > 0)
  {
    tmp2.value += 1;
    values["humn"] = tmp2;
    
    val1 = calculate( tmp1.expression.operand1 );
    val2 = calculate( tmp1.expression.operand2 );

    distance3 = val1 - val2;
  }


  return tmp2.value;
}

int main() {
  // open the file
  ifstream is("day21.input");
  string str;

  while ( getline( is, str ) )
  {
    istringstream iss(str);
    string sstr;
    string key;
    ValueS val={ false, 0, { 0, "", "" } };
    int idx=0;

    while ( getline( iss, sstr, ' ' ) )
    {
      switch ( idx )
      {
        case 0:
          sstr.pop_back();
          key = sstr;
          break;
        case 1:
          // str s either a value or not
          if ( isdigit( sstr[0] ) )
          {  
            val.hasValue = true;
            val.value = stoi(sstr);
          }
          else
          {
            val.expression.operand1 = sstr;
          }
          break;
        case 2:
          val.expression.operation = sstr[0];
          break;
        case 3: 
          val.expression.operand2 = sstr;
          break;
        default:
          break;
      }
      cout << sstr << '|' << idx << '|';
      idx++;
    }
    cout << endl;

    values[key]=val;
  }

  //close the file
  is.close();
  long long result = calculateHumn();
  cout << "result: " << result;
}
