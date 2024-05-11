#include <iostream>
#include <string>
#include "String.h"
using namespace std;
int main()
{
    char ori[] = "123456789ABCDEF";
    std::string a(ori);
    String aa(ori);
    cout << "=====================================================" << endl;
    cout << "test constructor with type const char * => String a('123456789ABCDEF')" << endl;
    cout << "std::string : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cout << "  my String : " << aa << " size: " << aa.size() << ", capacity: " << aa.capacity() << endl << endl;
        
    cout << "=====================================================" << endl;
    cout << "test operator[]: add \\0 in index 10 => a[9] = '\\0'" << endl;
    a[9] = '\0';
    aa[9] = '\0';
    cout << "std::string : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cout << "  my String : " << aa << " size: " << aa.size() << ", capacity: " << aa.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test copy constructor => String b(a)" << endl;
    std::string b(a);
    String bb(aa);
    cout << "std::string : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "  my String : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;


    cout << "=====================================================" << endl;
    cout << "test default constructor => String c" << endl;
    std::string c;
    String cc;
    cout << "std::string : " << c << " size: " << c.size() << ", capacity: " << c.capacity() << endl;
    cout << "  my String : " << cc << " size: " << cc.size() << ", capacity: " << cc.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test c_str() => cout << a.c_str();" << endl;
    cout << "std::string : " << a.c_str() << endl;
    cout << "  my String : " << aa.c_str() << endl << endl;

    char add[] = "GHIJK";
    cout << "=====================================================" << endl;
    cout << "test operator +=: add 'GHIJK' with the type of string => String d('GHIJK'); b += d;" << endl;
    std::string d(add);
    String dd(add);
    b += d;
    bb += dd;
    cout << "std::string(b) : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "std::string(d) : " << d << " size: " << d.size() << ", capacity: " << d.capacity() << endl;
    cout << "  my String(b) : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl;
    cout << "  my String(d) : " << dd << " size: " << dd.size() << ", capacity: " << dd.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test operator =: with the type of String (copy and swap) => b = a" << endl;
    b = a;
    bb = aa;
    cout << "ori  std::string (a) : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cout << "after std::string(b) : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "    ori my String(a) : " << aa << " size: " << aa.size() << ", capacity: " << aa.capacity() << endl;
    cout << "  after my String(b) : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test clear() => b.clear()" << endl;
    b.clear();
    bb.clear();
    cout << "std::string : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "  my String : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test operator + and =: add 'GHIJK' with the type of string => b = a + d;" << endl;
    b = a + d;
    bb = aa + dd;
    cout << "std::string : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "  my String : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;

    cout << "=====================================================" << endl;
    cout << "test swap() => c.swap(b);" << endl;
    cout << "ori  std::string (c) : " << c << " size: " << c.size() << ", capacity: " << c.capacity() << endl;
    cout << "ori  std::string (b) : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "    ori my String(c) : " << cc << " size: " << cc.size() << ", capacity: " << cc.capacity() << endl;
    cout << "    ori my String(b) : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;
    c.swap(b);
    cc.swap(bb);
    cout << "after std::string(c) : " << c << " size: " << c.size() << ", capacity: " << c.capacity() << endl;
    cout << "after std::string(b) : " << b << " size: " << b.size() << ", capacity: " << b.capacity() << endl;
    cout << "  after my String(c) : " << cc << " size: " << cc.size() << ", capacity: " << cc.capacity() << endl;
    cout << "  after my String(b) : " << bb << " size: " << bb.size() << ", capacity: " << bb.capacity() << endl << endl;

    char compa[] = "ABCDEF";
    char compb[] = "BCDEFG";
    char compc[] = "ABCDEFG";
    std::string cmpa(compa);
    String cmpaa(compa);
    std::string cmpb(compb);
    String cmpbb(compb);
    std::string cmpc(compc);
    String cmpcc(compc);
    cout << "================== operator <, >, <=, ==, >=, != ===================================" << endl;
    cout << "=> String a('ABCDEF'); String b('BCDEF'); String('ABCDEFG')" << endl;
    cout << "test operator < => cout << (a < b) << (a < c)" << endl;
    cout << "std::string : " << (cmpa < cmpb) << (cmpa < cmpc) << endl;
    cout << "  my String : " << (cmpaa < cmpbb) << (cmpaa < cmpcc) << endl << endl;
    cout << "test operator == => cout << (a == b) << (a == c)" << endl;
    cout << "std::string : " << (cmpa == cmpb) << (cmpa == cmpc) << endl;
    cout << "  my String : " << (cmpaa == cmpbb) << (cmpaa == cmpcc) << endl << endl;
    cout << "test operator <= => cout << (a <= b) << (a <= c)" << endl;
    cout << "std::string : " << (cmpa <= cmpb) << (cmpa <= cmpc) << endl;
    cout << "  my String : " << (cmpaa <= cmpbb) << (cmpaa <= cmpcc) << endl << endl;
    cout << "test operator > => cout << (a > b) << (a > c)" << endl;
    cout << "std::string : " << (cmpa > cmpb) << (cmpa > cmpc) << endl;
    cout << "  my String : " << (cmpaa > cmpbb) << (cmpaa > cmpcc) << endl << endl;
    cout << "test operator >= => cout << (a >= b) << (a >= c)" << endl;
    cout << "std::string : " << (cmpa >= cmpb) << (cmpa >= cmpc) << endl;
    cout << "  my String : " << (cmpaa >= cmpbb) << (cmpaa >= cmpcc) << endl << endl;
    cout << "test operator != => cout << (a != b) << (a != c)" << endl;
    cout << "std::string : " << (cmpa != cmpb) << (cmpa != cmpc) << endl;
    cout << "  my String : " << (cmpaa != cmpbb) << (cmpaa != cmpcc) << endl << endl;

    cout << "test cin and cout without initial a new string" << endl;
    cout << "ori std::string : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cout << "  ori my String : " << aa << " size: " << aa.size() << ", capacity: " << aa.capacity() << endl;
    cout << "type something into std::string (if less then ori string size)" << endl;
    cin >> a;
    cin.ignore();
    cout << "after my string : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cout << "type something into std::string (if more then ori string size)" << endl;
    cin >> a;
    cout << "after my string : " << a << " size: " << a.size() << ", capacity: " << a.capacity() << endl;
    cin.ignore();
}