#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;
#define hu unsigned short

int main() {
  map<hu, map<hu, hu> > a;
  auto b = &a[2];
  (*b)[3] = 5;
  cout << a[2][3];
}

