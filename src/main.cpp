#include "app/App.h"
#include <iostream>

/*
This project is filled with alot of seemingly random documentation of different C++ methods.
This is because I'm relatively new to C++ and using this project as a learning tool.
This isn't intended to be a proper Music Player for daily usage (atleast not at it's current scale).
*/

int main()
{
    App app(1080, 720);
    std::cout << "main.cpp, getting everything ready" << std::endl;
    app.run();
}
