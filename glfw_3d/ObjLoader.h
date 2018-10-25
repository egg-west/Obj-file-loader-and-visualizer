#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm_include.h"
using namespace std;

class ObjLoader {
public:
	bool load(string fp);
	bool draw();
private:

	vector<vector<GLfloat>> V;
	vector<vector<GLint>> F;
};