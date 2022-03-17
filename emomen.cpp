// File: emomen.cpp
// Author: Evan Momen
// Date: 2022
// 
// This file defines the implementation of the Emomen class and
// instantiates it.

#include <iostream>
#include "emomen.h"

class Emomen em; // instantiation without parameters
// class Emomen em(10); // instantiation with parameters

// Constructors
Emomen::Emomen()
{
    test_var = 0;
}

Emomen::Emomen(int num)
{
    test_var = num;
}

// test function to print name
void Emomen::print_name()
{
    std::cout << "Game starting..." << std::endl;
    std::cout << "Evan Momen" << std::endl;
}
