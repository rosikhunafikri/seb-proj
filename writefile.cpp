#include <iostream>
#include <fstream>
using namespace std;

int main() {
  // Create and open a text file
  ofstream MyFile("filename123.txt");

  // Write to the file
  int a = 4;
  int b = 2;

  MyFile << "Files can be tricky, but it is fun enough!";

  cout << "cout between lines" << endl;

  MyFile << "second liiiineee!";

  MyFile << "a plus b is " << a+b;


  // Close the file
  MyFile.close();
}