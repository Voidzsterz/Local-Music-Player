#include "app/App.h"
#include <iostream>

/*
This project is filled with alot of seemingly random documentation of different C++ methods.
This is because I'm relatively new to C++ and using this project as a learning tool.
This isn't a proper Music Player for daily usage as of right now, I hope in the future it can be however.
*/

int main()
{
    App app(1080, 720);
    std::cout << "main.cpp, getting everything ready" << std::endl;
    app.run();
}
