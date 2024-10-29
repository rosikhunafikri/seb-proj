// Online C++ compiler to run C++ program online
#include <iostream>
#include <string.h>
#include "arithmetic.h"

using namespace std;

class Player {
    public:
    string name;
    double hp;
    double attack;
    
    Player(string name_, double hp_, double attack_){
        name = name_;
        hp = hp_;
        attack = attack_;
    }
    
    void kill(Player enemy){
        enemy.hp = enemy.hp - attack;
        cout << "killing...." << endl;
    }
};

void subfive(int* apoint){
    cout << "pointer: " << apoint << endl;
    cout << "value: " << *apoint << endl; //dereference
    
    *apoint = 5;
}

void swap(int* x, int* y){
    int z = *x;
    *x = *y;
    *y = z;
}


int main() {
    Player p1 = Player("qwer", 100, 10);
    Player p2 = Player("zxc", 90, 25);
    p1.kill(p2);

    
    int a = 10;
    int* apoint = &a; //get address of a;
    subfive(apoint);
    cout << "a is: " << a << endl;

    return 0;
}