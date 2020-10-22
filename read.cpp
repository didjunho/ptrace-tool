#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

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

int main2(int argc, char** argv) {
  int fd = open("reading.txt", O_RDONLY);
  char sensor_val[8192];
  printf("%d\n",read(fd, (void*)&sensor_val, 8191));
  write(0, sensor_val, 4);
  return 0;
}
