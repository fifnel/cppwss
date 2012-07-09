#include "helloworld.h"

#include <iostream>

using namespace std;

CHelloWorld::CHelloWorld(int count)
    : count_(count)
{
}

CHelloWorld::~CHelloWorld()
{
}

void CHelloWorld::print() {
    for (int i=0; i<count_; i++) {
        cout << "Hello, World!" << endl;
    }
}

