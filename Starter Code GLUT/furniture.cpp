#include "furniture.h"

void furniture::draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform) {
	for (int i = 0; i < primatives.size(); i++) {
		primatives[i]->drawPrimative(_vbo, _cbo, _ibo, _nbo, positionLocation, colorLocation, normalLocation, u_modelMatrixLocation, transform);
	}
}

ffloor::ffloor() {
	cube* c = new cube(glm::vec3(0.f,-0.1f,0.f),glm::vec3(0.9f,0.9f,0.9f),glm::vec3(10.f,0.1f,10.f));
	primatives.push_back(c);
}

chair::chair() {
	cylinder* c1 = new cylinder(glm::vec3(0.5f,0.f,-0.5f),glm::vec3(0.3f,0.3f,0.3f),glm::vec2(0.1f,1.f));
	cylinder* c2 = new cylinder(glm::vec3(0.5f,0.f,0.5f),glm::vec3(0.3f,0.3f,0.3f),glm::vec2(0.1f,1.f));
	cylinder* c3 = new cylinder(glm::vec3(-0.5f,0.f,-0.5f),glm::vec3(0.3f,0.3f,0.3f),glm::vec2(0.1f,1.f));
	cylinder* c4 = new cylinder(glm::vec3(-0.5f,0.f,0.5f),glm::vec3(0.3f,0.3f,0.3f),glm::vec2(0.1f,1.f));
	primatives.push_back(c1);
	primatives.push_back(c2);
	primatives.push_back(c3);
	primatives.push_back(c4);

	cube* cb1 = new cube(glm::vec3(0.f,1.f,0.f),glm::vec3(0.f,0.4f,0.8f),glm::vec3(1.2f,0.2,1.2f));
	primatives.push_back(cb1);

	cylinder* c5 = new cylinder(glm::vec3(0.f,1.f,-0.5f),glm::vec3(0.3f,0.3f,0.3f),glm::vec2(0.1f,0.5f));
	primatives.push_back(c5);

	cube* cb2 = new cube(glm::vec3(0.f,1.8f,-0.5f),glm::vec3(0.f,0.4f,0.8f),glm::vec3(1.2f,0.8f,0.2f));
	primatives.push_back(cb2);
}

table::table() {
}

fileCabinet::fileCabinet() {
}

lamp::lamp() {
}