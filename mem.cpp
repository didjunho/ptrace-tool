#include <iostream>

using namespace std;

struct Mem {
    bool one;
    int8_t three[3];
    int two;
};

int main() {
    cout << sizeof(Mem) << endl;
    return 0;
}