#ifndef SCENEGRAPH
#define SCENEGRAPH
#include "node.h"
#include <iostream>
#include <fstream>
#include <stack>

class sceneGraph {
private:
	enum objTypes {
		CHAIR, LAMP, TABLE, FILECABINET
	};
public:
	vector<objTypes> objectTypes;
	vector<glm::vec3> objectColors;
	vector<glm::vec2> objectPositions;
	vector<float> objectRotations;
	vector<glm::vec3> objectsScales;

	std::stack<node*> childStack;

	float xSize;
	float zSize;
	int numObjects;
	node* root;
	node* currentNode;
	sceneGraph(char* filename);
	void selectNextNode();

	char* readNextCharToken();
	int readNextIntToken();
	float readNextFloatToken();
	glm::vec3 readNextVecToken();
	void readObjBlock(char* line1, char* line2, char* line3, char* line4, char* line5);

	void goToNextNode();
	void setFalse(node* in);
};

#endif