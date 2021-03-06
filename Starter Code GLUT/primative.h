#ifndef PRIMATIVE
#define PRIMATIVE
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../freeglut/include/GL/glut.h"
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

class primative {
public:
	bool isSelected;
	glm::vec4 origin;
	glm::vec3 color;

	vector<float> vbo;
	vector<unsigned short> ibo;
	vector<float> cbo;
	vector<float> nbo;
	vector<glm::vec4> points;
	virtual void constructBuffers();
	void drawPrimative(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 modelView);
};

class cube : public primative {
public:
	// construct unit cube at origin
	cube();
	// construct specified cube at x,y,z with r,g,b values
	cube(glm::vec3 _origin, glm::vec3 _color,glm::vec3 dimensions);
	// Constructs the buffers to be passed out
	void constructBuffers();
};

class sphere : public primative {
private:
	struct face {
		int ind1;
		int ind2;
		int ind3;
		face(int i1, int i2, int i3) {
			ind1 = i1;
			ind2 = i2;
			ind3 = i3;
		}
	};
	int getMidPoint(int a, int b);
	vector<glm::vec4> icoPoints;
	vector<face> faces2;
public:
	int rings;
	int sectors;
	float radius;
	sphere();
	sphere(glm::vec3 _origin, glm::vec3 _color,float radius);
	// Constructs the buffers to be passed out
	void constructBuffers();

};

class cylinder : public primative {
public:
	float height;
	int numSegments;
	cylinder();
	cylinder(glm::vec3 _origin, glm::vec3 _color, glm::vec2 dimensions);
	// Constructs the buffers to be passed out
	void constructBuffers();
};



#endif