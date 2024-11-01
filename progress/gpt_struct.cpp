#include <iostream>
using namespace std;

struct Person {
    string name;
    int age;
};

void modifyPerson(Person* p) {  // Passed by pointer
    p->age = 30; // This will affect the original struct
}

int main() {
    Person person1 = {"John", 25};
    modifyPerson(&person1); // Pass address of struct
    cout << "Age after function call: " << person1.age << endl; // Will be 30
    cout << "11/8: " << 11/8 << endl;
    return 0;
}
