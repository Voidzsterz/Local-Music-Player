#pragma once
#include <X11/Xlib.h>
#include <string>

// Loads an image file and returns an OpenGL texture ID
// Returns 0 if loading failed
unsigned int loadTexture(const std::string& filePath);