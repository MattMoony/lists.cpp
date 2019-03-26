#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

bool myFComp(float x, float y) {
    return x > y;
}

int main()
{
    struct List<int> l;
    l.append(8);
    l.append(10);
    l.append(12);
    l.add(8, 1);

    std::cout << l.get(1) << std::endl;
    std::cout << l.toString() << std::endl;

    l.remove(1);
    std::cout << l.toString() << std::endl;
    std::cout << l.get(1) << std::endl;

    struct List<float> lf;
    lf.append(8.0f);
    lf.append(2.5f);

    lf.sort(&myFComp);

    std::cout << lf.toString() << std::endl;

    lf.clear();
    std::cout << lf.toString() << std::endl;

    struct List<std::string> ls;
    ls.append("Hello World!");
    ls.append("Lorem Ipsum!");

    std::cout << ls.toString() << std::endl;
    
    return 0;
}
