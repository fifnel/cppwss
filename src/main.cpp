#include <iostream>
#include "helloworld.h"

using namespace std;

int main(int argc, char *argv[]) {

    CHelloWorld hello(3);
    
    hello.print();

    return EXIT_SUCCESS;
}
