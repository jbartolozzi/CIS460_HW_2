#ifndef FURNITURE
#define FURNITURE
#include "primative.h"

class furniture {
public:
	vector<primative*> primatives;
	void draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform);
};

class ffloor : public furniture {
public:
	ffloor();
};

class chair : public furniture {
public:
	chair();
};

class table : public furniture {
public:
	table();
};

class fileCabinet : public furniture {
public:
	fileCabinet();
};

class lamp : public furniture {
public:
	lamp();
};


#endif