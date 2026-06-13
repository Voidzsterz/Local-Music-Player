#pragma once

#include "../../files/Directories.h"

class Renderer;

class SongsUI
{
public:
    SongsUI(Renderer& renderer, Directories& directories);
    void render();
private:
    Renderer& m_renderer;
    Directories& m_directories;

    void renderTopbar();
};