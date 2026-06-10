#pragma once

#include "../../files/Directories.h"

class SongsUI
{
public:
    SongsUI(Directories& directories);
    void render();
private:
    Directories& m_directories;
};