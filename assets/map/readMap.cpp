#include <iostream>
#include <fstream>
using namespace std;

int a;

int& refa() {
    return a;
}

int main() {
    int x, y, z;
    char c;

    // ifstream file("tileMap.txt", ifstream::in);
    // while(file) {
    //     file >> x >> c >> y >>c >> z >> c;
    //     cout << x << c << y <<c << z << c << endl;
    // }
    cin >> refa(); 
    cout << a << endl;
    refa() = 12345;
    cout << a << endl;

}