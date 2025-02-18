#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <algorithm> 
#include <cctype>
#include <locale>

#include <vector>
#include <bitset>
#include <cmath>
#include <map>
#include <set>
#include <list>
#include <iomanip>

using std::cout;
using std::endl;

using std::ifstream;
using std::string;
using std::vector;

using std::pair;
using std::istringstream;

using std::map;
using std::set;
using std::make_pair;
using std::list;
using std::tuple;
using std::make_tuple;
using std::get;



struct Reg 
{
    long long A;
    long long B;
    long long C;
    long long IP;
};

long long printCombo( long long op, Reg r )
{
    long long ret = -1;

    switch (op)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            ret = op;
            cout << op;
            break;
        case 4:
            ret = r.A;
            cout << "#A";
            break;
        case 5:
            ret = r.B;
            cout << "#B";
            break;
        case 6:
            ret = r.C;
            cout << "#C";
            break;
        case 7:
            cout << "#ERR";
            break;
        default:
            cout << "#ERR";
            break;
    }

    return ret;
}


void handle( Reg & r, vector<long long> & out, long long opcode, long long operand )
{
    cout << "3bit code: " << opcode << " " << operand << endl;


    switch(opcode)
    {
      case 0:
      { 
// The adv instruction (opcode 0) performs division.
//  The numerator is the value in the A register. 
//  The denominator is found by raising 2 to the power of the instruction's combo operand.
//  (So, an operand of 2 would divide A by 4 (2^2); an operand of 5 would divide A by 2^B.)
//  The result of the division operation is truncated to an integer and then written to the A register.
        cout << "asm: " << "adv ";
        long long combo = printCombo(operand,r);
        cout << endl;
        cout << "  numerator (#A): " << r.A << endl;
        cout << "  combo: " << combo << endl;
        cout << "  denominator: " << pow(2,combo) << endl;
        r.A /= pow(2,combo);
        cout << "  result: (#A) " << r.A << endl;
      }
      break;
      case 1:
      {
//The bxl instruction (opcode 1) calculates the bitwise XOR of register B and the instruction's literal operand, then stores the result in register B.
        cout << "asm: " << "bxl ";
        cout << operand;
        cout << endl;
        cout << "  #B: " << r.B << endl;
        cout << "  op: " << operand << endl;
        r.B ^= operand;
        cout << "  #B: " << r.B << endl;
      }
      break;
      case 2:
      {
//The bst instruction (opcode 2) calculates the value of its combo operand modulo 8 (thereby keeping only its lowest 3 bits), then writes that value to the B register.
        cout << "asm: " << "bst ";
        long long combo = printCombo(operand,r);
        cout << endl;
        cout << "  #B: " << r.B << endl;
        cout << "  combo: " << combo << endl;
        r.B = combo % 8;
        cout << "  #B: " << r.B << endl;
    }
        break;
      case 3:
      { 
//The jnz instruction (opcode 3) does nothing if the A register is 0. 
// However, if the A register is not zero, it jumps by setting the instruction pointer to the value of its literal operand;
// if this instruction jumps, the instruction pointer is not increased by 2 after this instruction.
        cout << "asm: " << "jnz" << endl;
        if (  r.A != 0 )
          r.IP = operand-2;
        cout << " #A: " << r.A << endl;
        cout << " #IP: " << r.IP+2 << endl;
      }
        break;
      case 4:
      {
//The bxc instruction (opcode 4) calculates the bitwise XOR of register B and register C, then stores the result in register B. (For legacy reasons, this instruction reads an operand but ignores it.)
        cout << "asm: " << "bxc" << endl;
        cout << "  #B: " << r.B << endl;
        cout << "  #C: " << r.C << endl;
        r.B ^= r.C;
        cout << "  #B: " << r.B << endl;
    }
        break;
      case 5:
      { 
//The out instruction (opcode 5) calculates the value of its combo operand modulo 8, then outputs that value. (If a program outputs multiple values, they are separated by commas.)
        cout << "asm: " << "out ";
        long long combo = printCombo(operand,r);
        cout << endl;
        cout << "  value: " << combo << endl;
        cout << "  mod8: " << combo%8 << endl;
        out.push_back(combo%8);
      }
        break;
      case 6:
      { 
//The bdv instruction (opcode 6) works exactly like the adv instruction except that the result is stored in the B register. (The numerator is still read from the A register.)
        cout << "asm: " << "bdv ";
        long  long combo = printCombo(operand,r);
        cout << endl;
        cout << "  numerator (#B): " << r.B << endl;
        cout << "  denominator: " << pow(2,combo) << endl;
        r.B = r.A / pow(2,combo);
        cout << "  result: " << r.B << endl;
      }
        break;
      case 7:
      { 
//The cdv instruction (opcode 7) works exactly like the adv instruction except that the result is stored in the C register. (The numerator is still read from the A register.)
        cout << "asm: " << "cdv ";
        long long combo = printCombo(operand,r);
        cout << endl;
        cout << "  numerator (#A): " << r.A << endl;
        cout << "  denominator: " << pow(2,combo) << endl;
        r.C = r.A / pow(2,combo);
        cout << "  result: " << r.C << endl;
      }
        break;
      default:
       
        break;
    }



    r.IP += 2;
}

long long iterate ( long long expect, long long & a, long long &  b, long long & c )
{
    long long ret {-1};
    // #B = #A mod 8
    b = a % 8;
    // #B = #B ^ 5
    b = b ^ 5;
    // #C = #A / pow(2,#B)
    c = a / pow ( 2, b );
    // #B = #B ^ 6
    b = b ^ 6;
    // #B = #B ^ #C
    b = b ^ c;
    // out = #B mod 8
    //cout << b % 8 << ",";
    // #A = A# / 8
    ret = a;
    a = a / 8;
    // #IP = 0 IF #A > 0
    return (expect==(b%8)?ret:-1);
}

void iterate2( vector<long long> expect, long long n, long long  & res )
{
    for (long long m=(n*8); m<((n+1)*8);m++)
    {
        long long a,b {0},c {0};
        a = m;
        
        if ( expect.size() == 0 )
        {
            cout <<  "SOL?" << endl;
            return;
        }

        long long p = iterate( expect.back(),a,b,c );

        if (p>=0 && expect.size()>0 )
        {
            if ( expect.size()<2)
            {
                cout << expect.size() <<":m=" << m << ",a=" << a << ",b=" << b << "(mod 8)" << b%8 << ",c=" << c << ",p=" << p  << endl;
                res = m;
            }
          
          vector<long long> exp2 = expect;
          exp2.pop_back();
          iterate2( exp2,p,res);
        }
    
        else if (p>=0)
        {
            cout << "SOL=" << a << endl;
            res = m;
        }

        if (res >0)
            break;
    }

    return;
}

int main()
{
    // first read the pairs of page ordering rule
    ifstream is("day17.input");
    string str;
    string answer1;
    long long answer2 {0};

    Reg reg {0,0,0,0};
    vector<long long> code;
    vector<long long> out;
    int line {0};

    while ( getline( is, str  ))
    {
        istringstream iss(str);
        string sstr;
        line++;
        while ( getline(iss, sstr,':'))
        {
            if( *(sstr.begin()) == ' ' && line == 1 )
                reg.A = stoll(sstr);
            if( *(sstr.begin()) == ' ' && line == 2 )
                reg.B = stoll(sstr);
            if( *(sstr.begin()) == ' ' && line == 3 )
                reg.C = stoll(sstr);
            if( *(sstr.begin()) == ' ' && line == 5 )
            {
                istringstream iscode(sstr);
                string strop;

                while ( getline ( iscode, strop, ',') )
                {
                    code.push_back(stoll(strop));
                }

            }
        }

    }
    is.close();

    while (reg.IP <code.size())
    {
        handle(reg, out, code[reg.IP],code[reg.IP+1] );
    }

    iterate2(code,0,answer2);

    bool first = true;
    for ( auto o: out)
    {
        if (!first)
            answer1.append(",");
        answer1.append( std::to_string(o) ); 
        first = false;
    }

    cout << endl;
    cout << "#A " << reg.A << " #B " << reg.B << " #C " << reg.C << endl;

    cout << "answer1 = " << answer1 << endl;
    cout << "answer2 = " << answer2 << endl;

/*
    for ( long long n = 0; n<64; n++)
    {
        long long a,b,c;
        a = n;
        long long res =  iterate(0,a,b,c);
        if (res>=0)
        cout << " n=" << n << " bool=" << res << " a=" << a << " b=" << b << " c=" << c << endl;
    }
*/
 
    return 0;
}
