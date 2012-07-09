#include <iostream>
#include "../src/helloworld.h"

using namespace std;

int main(int argc, char *argv[]) {

    CHelloWorld hello(3);
    
    hello.print();

    //return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

