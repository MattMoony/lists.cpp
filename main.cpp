#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lists.h"

bool myFComp(float x, float y) {
    return x < y;
}

int main()
{
    srand(time(NULL));

    struct LinkedList<int> l;
    l.append(8);
    l.append(10);
    l.append(12);
    l.add(8, 1);

    std::cout << l.get(1) << std::endl;
    std::cout << l.toString() << std::endl;

    l.remove(1);
    std::cout << l.toString() << std::endl;
    std::cout << l.get(1) << std::endl;

    struct LinkedList<float> lf;
    lf.append(0.25f);
    lf.append(8.0f);
    lf.append(7.9f);
    lf.append(2.0f);
    lf.append(10.0f);
    lf.append(0.5f);

    std::cout << lf.toString() << std::endl;
    lf.sort(&myFComp);
    std::cout << lf.toString() << std::endl;

    lf.clear();

    for(int i = 0; i < 10; i++) {
        lf.append(((float)rand()/RAND_MAX)*25);
    }

    lf.sort(&myFComp);
    std::cout << lf.toString() << std::endl;

    lf.clear();
    std::cout << lf.toString() << std::endl;

    struct LinkedList<std::string> ls;
    /*ls.append("Hello World!");
    ls.append("Lorem Ipsum!");

    std::cout << ls.toString() << std::endl;*/

    return 0;
}
