#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lists.h"

bool myFComp(float x, float y) {
    return x < y;
}

bool myIFilter(int v) {
    return v%2==0;
}

int myIMap(int v) {
    return v*2;
}

int myISum(int a, int b) {
    return a+b;
}

int myIPro(int a, int b) {
    return a*b;
}

int main()
{
    srand(time(NULL));

    struct LinkedList<int> l;
    l.append(8);
    l.append(10);
    l.append(12);
    l.add(8, 1);

    std::cout << "Get: \t\t" << l.get(1) << std::endl;
    std::cout << "String: \t" << l.toString() << std::endl;

    l.remove(1);
    std::cout << "Removed: \t" << l.toString() << std::endl;
    std::cout << "Get: \t\t" << l.get(1) << std::endl;

    l.add(2, 0);
    l.add(12, 2);
    l.append(12);
    std::cout << "Before: \t" << l.toString() << std::endl;

    l.removeValue(12);
    std::cout << "Removed v: \t" << l.toString() << std::endl;

    l.clear();
    std::cout << std::endl;

    for (int i = 1; i <= 10; i++)
        l.append(i);

    l.filter(&myIFilter);
    std::cout << "Filtered: \t" << l.toString() << std::endl;

    l.map(&myIMap);
    std::cout << "Mapped: \t" << l.toString() << std::endl;

    std::cout << "Sum: \t\t" << l.reduce(&myISum) << std::endl;
    std::cout << "Product: \t" << l.reduce(&myIPro) << std::endl;

    std::cout << std::endl << std::endl;

    struct LinkedList<float> lf;
    lf.append(0.25f);
    lf.append(8.0f);
    lf.append(7.9f);
    lf.append(2.0f);
    lf.append(10.0f);
    lf.append(0.5f);

    std::cout << "Original: \t" << lf.toString() << std::endl;
    lf.sort(&myFComp);
    std::cout << "Sorted: \t" << lf.toString() << std::endl;

    lf.clear();

    for(int i = 0; i < 10; i++) {
        lf.append(((float)rand()/RAND_MAX)*25);
    }

    std::cout << "Random: \t" << lf.toString() << std::endl;
    lf.sort(&myFComp);
    std::cout << "Sorted: \t" << lf.toString() << std::endl;

    lf.clear();
    std::cout << "Cleared: \t" << lf.toString() << std::endl;

    std::cout << std::endl << std::endl;

    struct LinkedList<double> df;
    double arr[10];

    for (int i = 0; i < 10; i++) {
        arr[i] = ((double)rand()/RAND_MAX)*25;
    }

    df.appendAll(arr, 10);
    std::cout << "Added all: \t" << df.toString() << std::endl;
    std::cout << "Length: \t" << df.size() << std::endl;

    for (int i = 0; i < 10; i++) {
        arr[i] = ((double)rand()/RAND_MAX)*50+25;
    }

    df.addAll(arr, 10, 4);
    std::cout << "Added all: \t" << df.toString() << std::endl;
    std::cout << "Length: \t" << df.size() << std::endl;

//    struct LinkedList<std::string> ls;
//    ls.append("Hello World!");
//    ls.append("Lorem Ipsum!");

//    std::cout << ls.toString() << std::endl;

    return 0;
}
