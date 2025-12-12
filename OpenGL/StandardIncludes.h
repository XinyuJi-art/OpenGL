#pragma once

#ifndef _STANDARDINCLUDES_H_
#define _STANDARDINCLUDES_H_

#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>

//Window specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg)\
	if(!(_cond)){OutputDebugStringA(_msg); std::abort(); glfwTerminate();} 
#endif

//FreeType headers
#include <ft2build.h>
#include FT_FREETYPE_H

//Open GL/Helper headers
#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include <glm/glm.hpp> //Include GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <glm/ext.hpp>

#include "Resolution.h"
#include "json.hpp"


inline json::JSON LoadJSON(const std::string & filename)
{
    std::ifstream file(filename);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return json::JSON::Load(str);
}

#endif //!_STANDARDINCLUDES_H_