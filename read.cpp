#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

// int main(int argc, char** argv) {
//     ofstream outFile;
//     outFile.open("log.txt");
//     outFile << "Num Arguments: " << argc - 1 << endl;
//     for (int i = 0; i < (argc - 1); ++i) {
//         outFile << "arg " << i + 1 << ": " << argv[i+1] << endl;
//     }
//     this_thread::sleep_for(chrono::seconds(2));
//     outFile.close();
//     return 0;
// }

int main(int argc, char** argv) {
    ifstream inFile;
    long sensor_val = 9999;
    inFile.open("reading.txt");
    cout << "SENSOR ADDRESS: " << &sensor_val << endl;
    inFile >> sensor_val;
    inFile.close();
    cout << "SENSOR: " << sensor_val << endl;
    return 0;
}