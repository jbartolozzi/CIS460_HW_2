#include "sceneGraph.h"

sceneGraph::sceneGraph(char* filename) {
	ifstream file(filename);
	while (!file.good()) {
		cout << "Invalid File Name Please Try Again: ";
		char* filename = new char[25];
		cin >> filename;
		file.open(filename);
	}

	while(!file.eof()) {
		char line[100];
		file.getline(line,10);
		char* in1 = strtok(line, " ");
		char* in2 = strtok(NULL," ");
		char* in3 = strtok(NULL," ");

		xSize = atof(in1);
		zSize = atof(in2);
		numObjects = atoi(in3);

		char space[10];
		char line2[100];
		char line3[100];
		char line4[10];
		char line5[10];
		char line6[100];
		file.getline(space,10);
		file.getline(line2,100);
		file.getline(line3,100);
		file.getline(line4,10);
		file.getline(line5,10);
		file.getline(line6,100);
		readObjBlock(line2,line3,line4,line5,line6);
		for (int i = 1; i < numObjects; i++) {
			char space[10];
			char line2[100];
			char line3[100];
			char line4[10];
			char line5[10];
			char line6[100];
			file.getline(space,10);
			file.getline(line2,100);
			file.getline(line3,100);
			file.getline(line4,10);
			file.getline(line5,10);
			file.getline(line6,100);
			readObjBlock(line2,line3,line4,line5,line6);
		}
	}

	chair* chair1 = new chair(glm::vec3(0.f,0.6,0.8));
	lamp* lamp1 = new lamp(glm::vec3(0.f,0.6,0.8));
	table* table1 = new table(glm::vec3(0.f,0.6,0.8));
	fileCabinet* fc1 = new fileCabinet(glm::vec3(0.f,0.6,0.8));

	ffloor *floor1 = new ffloor(xSize,zSize);
	node* rootFloor = new node(NULL,NULL,floor1,0.f,glm::vec3(1.f,1.f,1.f),glm::vec3(3.f,0.f,0.f),glm::vec3(0.7,0.7,0.7));
	root = rootFloor;
	vector<node*>* newChildren = new vector<node*>;
	for (int i = 0; i < numObjects; i++) {
		if (objectTypes[i] == CHAIR) {
			node* newNode = new node(rootFloor,NULL,chair1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
			newChildren->push_back(newNode);
		}
		else if(objectTypes[i] == LAMP) {
			node* newNode = new node(rootFloor,NULL,lamp1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
			newChildren->push_back(newNode);
		}
		else if(objectTypes[i] == TABLE) {
			node* newNode = new node(rootFloor,NULL,table1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
			newChildren->push_back(newNode);
		}
		else if(objectTypes[i] == FILECABINET) {
			node* newNode = new node(rootFloor,NULL,fc1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
			newChildren->push_back(newNode);
		}
	}

	rootFloor->children = newChildren;
	rootFloor->selected = true;
	currentNode = root;

}

void sceneGraph::readObjBlock(char* line1, char* line2, char* line3, char* line4, char* line5) {
	if (strcmp(line1, "table") == 0) {
		objectTypes.push_back(objTypes::TABLE);
	}
	else if (strcmp(line1, "chair") == 0) {
		objectTypes.push_back(objTypes::CHAIR);
	}
	else if (strcmp(line1, "filecabinet") == 0) {
		objectTypes.push_back(objTypes::FILECABINET);
	}
	else if (strcmp(line1, "lamp") == 0) {
		objectTypes.push_back(objTypes::LAMP);
	}

	char* r = strtok(line2, " ");
	char* g = strtok(NULL, " ");
	char* b = strtok(NULL, " ");

	objectColors.push_back(glm::vec3(atof(r),atof(g),atof(b)));

	char* xInd = strtok(line3, " ");
	char* zInd = strtok(NULL, " ");

	objectPositions.push_back(glm::vec2(atof(xInd),atof(zInd)));

	char* rot = strtok(line4, " ");

	objectRotations.push_back(atof(rot));

	char* xSca = strtok(line5, " ");
	char* ySca = strtok(NULL," ");
	char* zSca = strtok(NULL," ");

	objectsScales.push_back(glm::vec3(atof(xSca),atof(ySca),atof(zSca)));
}

char* sceneGraph::readNextCharToken() {
	char* token = strtok(NULL, " ");
	return token;
}

int sceneGraph::readNextIntToken(){
	return atoi(readNextCharToken());
}

float sceneGraph::readNextFloatToken(){
	return (float) atof(readNextCharToken());
}

glm::vec3 sceneGraph::readNextVecToken() {
	glm::vec3 newVec;
	newVec.x = readNextFloatToken();
	newVec.y = readNextFloatToken();
	newVec.z = readNextFloatToken();
	return newVec;
}

void sceneGraph::goToNextNode() {
	currentNode->selected = false;
	if (currentNode->children != NULL) {
		for(int i = 0; i < currentNode->children->size(); i++) {
			childStack.push(currentNode->children->at(i));
		}
		currentNode = childStack.top();
		currentNode->selected = true;
		childStack.pop();
	}
	else if (!childStack.empty()) {
		currentNode = childStack.top();
		currentNode->selected = true;
		childStack.pop();
	}
	else {
		currentNode = root;
		currentNode->selected = true;
	}
}

