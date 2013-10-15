#include "primative.h"

void primative::drawPrimative(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform){
	vector<float> vertices = vbo;
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	
	vector<float> colors = cbo;
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STREAM_DRAW);	//the color is going to change every frame

	vector<float> normals = nbo;
	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW); //the square normals don't need to change, ever,

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	vector<unsigned short> indices = ibo;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &transform[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, indices.size() * sizeof(unsigned short), GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

//####################################################################################################################
//    v7----- v6
//   /|      /|
//  v3------v2|
//  | |     | |
//  | |v4---|-|v5
//  |/      |/
//  v0------v1
cube::cube() {
	origin  = glm::vec4(0.f,0.f,0.f,1.0);
	color = glm::vec3(1.f,1.f,0.f);

	glm::vec4 p0 = glm::vec4(-0.5f,-0.5f,0.5,1.f);
	glm::vec4 p1 = glm::vec4(0.5f,-0.5f,0.5,1.f);
	glm::vec4 p2 = glm::vec4(0.5f,0.5f,0.5,1.f);
	glm::vec4 p3 = glm::vec4(-0.5f,0.5f,0.5,1.f);
	glm::vec4 p4 = glm::vec4(-0.5f,-0.5f,-0.5,1.f);
	glm::vec4 p5 = glm::vec4(0.5f,-0.5f,-0.5,1.f);
	glm::vec4 p6 = glm::vec4(0.5f,0.5f,-0.5,1.f);
	glm::vec4 p7 = glm::vec4(-0.5f,0.5f,-0.5,1.f);

	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

	points.push_back(p1);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p2);

	points.push_back(p5);
	points.push_back(p4);
	points.push_back(p7);
	points.push_back(p6);

	points.push_back(p4);
	points.push_back(p0);
	points.push_back(p3);
	points.push_back(p7);

	points.push_back(p3);
	points.push_back(p2);
	points.push_back(p6);
	points.push_back(p7);

	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p5);
	points.push_back(p4);
	constructBuffers();
}


//    v7----- v6
//   /|      /|
//  v3------v2|
//  | |     | |
//  | |v4---|-|v5
//  |/      |/
//  v0------v1
cube::cube(glm::vec3 _origin, glm::vec3 _color, glm::vec3 dimensions) {
	float width = dimensions.x;
	float height = dimensions.y;
	float depth = dimensions.z;
	origin = glm::vec4(_origin,1.0);
	color = _color;

	glm::vec4 p0 = glm::vec4(-0.5f * width,-0.5f * height,0.5 * depth,1.f) + origin;
	glm::vec4 p1 = glm::vec4(0.5f * width,-0.5f * height,0.5 * depth,1.f) + origin;
	glm::vec4 p2 = glm::vec4(0.5f * width,0.5f * height,0.5 * depth,1.f) + origin;
	glm::vec4 p3 = glm::vec4(-0.5f * width,0.5f * height,0.5 * depth,1.f) + origin;
	glm::vec4 p4 = glm::vec4(-0.5f * width,-0.5f * height,-0.5 * depth,1.f) + origin;
	glm::vec4 p5 = glm::vec4(0.5f * width,-0.5f * height,-0.5 * depth,1.f) + origin;
	glm::vec4 p6 = glm::vec4(0.5f * width,0.5f * height,-0.5 * depth,1.f) + origin;
	glm::vec4 p7 = glm::vec4(-0.5f * width,0.5f * height,-0.5 * depth,1.f) + origin;

	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);

	points.push_back(p1);
	points.push_back(p5);
	points.push_back(p6);
	points.push_back(p2);

	points.push_back(p5);
	points.push_back(p4);
	points.push_back(p7);
	points.push_back(p6);

	points.push_back(p4);
	points.push_back(p0);
	points.push_back(p3);
	points.push_back(p7);

	points.push_back(p3);
	points.push_back(p2);
	points.push_back(p6);
	points.push_back(p7);

	points.push_back(p0);
	points.push_back(p1);
	points.push_back(p5);
	points.push_back(p4);
	constructBuffers();
}

void cube::constructBuffers() {
	vector<float> vertices;
	vector<float> normals;
	vector<float> colors;
	vector<unsigned short> index;
	

	for (int i = 0; i < points.size(); i++ ) {
		vertices.push_back(points[i].x);
		vertices.push_back(points[i].y);
		vertices.push_back(points[i].z);
		vertices.push_back(1.f);
	}

	vbo = vertices;

	for (int i = 0; i < points.size(); i++) {
		colors.push_back(color.r);
		colors.push_back(color.g);
		colors.push_back(color.b);
	}

	cbo = colors;

	index.push_back(0); index.push_back(1); index.push_back(2);
	index.push_back(0); index.push_back(2); index.push_back(3);

	index.push_back(4); index.push_back(5); index.push_back(6);
	index.push_back(4); index.push_back(6); index.push_back(7);

	index.push_back(8); index.push_back(9); index.push_back(10);
	index.push_back(8); index.push_back(10); index.push_back(11);

	index.push_back(12); index.push_back(13); index.push_back(14);
	index.push_back(12); index.push_back(14); index.push_back(15);

	index.push_back(16); index.push_back(17); index.push_back(18);
	index.push_back(16); index.push_back(18); index.push_back(19);

	index.push_back(20); index.push_back(21); index.push_back(22);
	index.push_back(20); index.push_back(22); index.push_back(23);

	ibo = index;

	//    v7----- v6
	//   /|      /|
	//  v3------v2|
	//  | |     | |
	//  | |v4---|-|v5
	//  |/      |/
	//  v0------v1
	for (int i = 0; i < 4; i++) {
		glm::vec4 a1 = points[4*i+1] - points[4*i];
		glm::vec4 a2 = points[4*i+3] - points[4*i];
		glm::vec3 a3 = glm::cross(glm::vec3(a1.x,a1.y,a1.z),glm::vec3(a2.x,a2.y,a2.z));
		for (int j = 0; j < 4; j++) {
			normals.push_back(a3.x); normals.push_back(a3.y);  normals.push_back(a3.z);  normals.push_back(0.f);
		}
	}

	/*
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(1.f);  normals.push_back(0.f);
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(1.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(1.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(1.f);  normals.push_back(0.f);

	normals.push_back(1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f);
	normals.push_back(1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f);

	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(-1.f);  normals.push_back(0.f);
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(-1.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(-1.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(0.f);  normals.push_back(-1.f);  normals.push_back(0.f);

	normals.push_back(-1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f);
	normals.push_back(-1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(-1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(-1.f); normals.push_back(0.f);  normals.push_back(0.f);  normals.push_back(0.f);
	*/
	normals.push_back(0.f); normals.push_back(1.f);  normals.push_back(0.f);  normals.push_back(0.f);
	normals.push_back(0.f); normals.push_back(1.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(1.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(1.f);  normals.push_back(0.f);  normals.push_back(0.f);

	normals.push_back(0.f); normals.push_back(-1.f);  normals.push_back(0.f);  normals.push_back(0.f);
	normals.push_back(0.f); normals.push_back(-1.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(-1.f);  normals.push_back(0.f);  normals.push_back(0.f); 
	normals.push_back(0.f); normals.push_back(-1.f);  normals.push_back(0.f);  normals.push_back(0.f);

	nbo = normals;
}

//################################################################################################################################
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

sphere::sphere() {
	origin  = glm::vec4(0.f,1.f,0.f,1.0);
	color = glm::vec3(0.f,1.f,0.f);
	float t = (1.f + glm::sqrt(5.0)) / 2.f;

	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(-1.f,  t,0.f)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3( 1.f,  t,0.f)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(-1.f, -t,0.f)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3( 1.f, -t,0.f)),1.f));

	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(0.f, -1.f,  t)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(0.f,  1.f,  t)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(0.f, -1.f, -t)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(0.f,  1.f, -t)),1.f));

	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3( t, 0.f, -1)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3( t, 0.f,  1)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(-t, 0.f, -1)),1.f));
	icoPoints.push_back(glm::vec4(glm::normalize(glm::vec3(-t, 0.f,  1)),1.f));

	// faces around point 0
	vector<face> faces;
	faces.push_back(face(0,11,5));
	faces.push_back(face(0,5,1));
	faces.push_back(face(0,1,7));
	faces.push_back(face(0,7,10));
	faces.push_back(face(0,10,11));

	faces.push_back(face(1,5,9));
	faces.push_back(face(5,11,4));
	faces.push_back(face(11,10,2));
	faces.push_back(face(10,7,6));
	faces.push_back(face(7,1,8));

	faces.push_back(face(3,9,4));
	faces.push_back(face(3,4,2));
	faces.push_back(face(3,2,6));
	faces.push_back(face(3,6,8));
	faces.push_back(face(3,8,9));

	faces.push_back(face(4,9,5));
	faces.push_back(face(2,4,11));
	faces.push_back(face(6,2,10));
	faces.push_back(face(8,6,7));
	faces.push_back(face(9,8,1));

	vector<face> faces2;

	for (int i = 0; i < 6; i++) {
		for (int i = 0; i < faces.size(); i++) {
			int a = getMidPoint(faces[i].ind1,faces[i].ind2);
			int b = getMidPoint(faces[i].ind2,faces[i].ind3);
			int c = getMidPoint(faces[i].ind3,faces[i].ind1);

			faces2.push_back(face(faces[i].ind1,a,c));
			faces2.push_back(face(faces[i].ind2,b,a));
			faces2.push_back(face(faces[i].ind3,c,b));
			faces2.push_back(face(a,b,c));
		}	
	}
	
	for(int i = 0; i < icoPoints.size(); i++) {
		points.push_back(icoPoints[i]);
	}

	vector<float> vertices;
	for (int i = 0; i < icoPoints.size(); i++ ) {
		vertices.push_back(icoPoints[i].x);
		vertices.push_back(icoPoints[i].y);
		vertices.push_back(icoPoints[i].z);
		vertices.push_back(1.f);

	}
	vbo = vertices;

	vector<unsigned short> index;
	for (int i = 0; i < faces2.size(); i++) {
		index.push_back(faces2[i].ind1);
		index.push_back(faces2[i].ind2);
		index.push_back(faces2[i].ind3);
	}
	ibo = index;
	constructBuffers();
}

int sphere::getMidPoint(int a, int b) {
	glm::vec3 a1(icoPoints[a].x,icoPoints[a].y,icoPoints[a].z);
	glm::vec3 a2(icoPoints[b].x,icoPoints[b].y,icoPoints[b].z);
	glm::vec3 a3 = glm::normalize((a1 + a2) / 2.f);
	glm::vec4 out(a3,1.f);
	icoPoints.push_back(out);
	int oop = icoPoints.size() - 1;
	return (oop);
}

sphere::sphere(glm::vec3 _origin, glm::vec3 _color, glm::vec2 dimensions) {
}



void sphere::constructBuffers() {
	
	vector<float> normals;
	vector<float> colors;
	vector<unsigned short> index;

	
	for (int i = 0; i < points.size(); i++) {
		colors.push_back(color.r);
		colors.push_back(color.g);
		colors.push_back(color.b);
	}
	cbo = colors;
	
	for (int i = 0; i < points.size(); i++) {
		normals.push_back(points[i].x);
		normals.push_back(points[i].y);
		normals.push_back(points[i].z);
		normals.push_back(0.f);
	}

	nbo = normals;
}

//###############################################################################################################################

cylinder::cylinder() {
	height = 2;
	numSegments = 24;
	float radius = 1;
	origin  = glm::vec4(0.f,0.f,0.f,1.0);
	color = glm::vec3(0.f,1.f,0.f);
	
	//sides
	for (int i = 0; i <= numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = radius * cosf(theta);//calculate the x component 
		float z = radius * sinf(theta);//calculate the y component 

		points.push_back(glm::vec4(x,0.f,z,1.f));
		points.push_back(glm::vec4(x,height,z,1.f));
	}

	// bottom
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = radius * cosf(theta);//calculate the x component 
		float z = radius * sinf(theta);//calculate the y component 

		points.push_back(glm::vec4(x,0.f,z,1.f));
	}

	//top
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = radius * cosf(theta);//calculate the x component 
		float z = radius * sinf(theta);//calculate the y component

		points.push_back(glm::vec4(x,height,z,1.f));
	}
	constructBuffers();
}

cylinder::cylinder(glm::vec3 _origin, glm::vec3 _color, glm::vec2 dimensions) {
	float height = dimensions.y;
	numSegments = 24;
	float radius = dimensions.x;
	origin = glm::vec4(_origin,1.0);
	color = _color;
	
	//sides
	for (int i = 0; i <= numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = origin.x + radius * cosf(theta);//calculate the x component 
		float z = origin.z + radius * sinf(theta);//calculate the y component 

		points.push_back(glm::vec4(x,origin.y,z,1.f));
		points.push_back(glm::vec4(x,height + origin.y,z,1.f));
	}

	// bottom
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = origin.x + radius * cosf(theta);//calculate the x component 
		float z = origin.z + radius * sinf(theta);//calculate the y component 

		points.push_back(glm::vec4(x,origin.y,z,1.f));
	}

	//top
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);//get the current angle 

		float x = origin.x + radius * cosf(theta);//calculate the x component 
		float z = origin.z + radius * sinf(theta);//calculate the y component

		points.push_back(glm::vec4(x,origin.y + height,z,1.f));
	}
	constructBuffers();
}

void cylinder::constructBuffers() {
	vector<float> vertices;
	vector<float> normals;
	vector<float> colors;
	vector<unsigned short> index;

	for (int i = 0; i < points.size(); i++ ) {
		vertices.push_back(points[i].x);
		vertices.push_back(points[i].y);
		vertices.push_back(points[i].z);
		vertices.push_back(1.f);
	}
	vbo = vertices;

	for (int i = 0; i < points.size(); i++) {
		colors.push_back(color.r);
		colors.push_back(color.g);
		colors.push_back(color.b);
	}

	cbo = colors;

	/*for (int i = 0; i <= numSegments * 2;) {
		glm::vec4 a1 = points[i] - origin;
		a1 = glm::normalize(a1);
		glm::vec4 a2 = points[i+1] - glm::vec4(origin.x,origin.y + height,origin.z,1.f);
		a2 = glm::normalize(a2);
		
		normals.push_back(a1.x);
		normals.push_back(a1.y);
		normals.push_back(a1.z);
		normals.push_back(0.f);

		normals.push_back(a2.x);
		normals.push_back(a2.y);
		normals.push_back(a2.z);
		normals.push_back(0.f);

		i+=2;
	}*/

	// mid section normals
	for (int i = 0; i <= numSegments*2;) {
		glm::vec4 a1;
		glm::vec4 a2;
		a1 = points[i+1] - points[i];
		a2 = points[i+3] - points[i+1];

		glm::vec3 a3 = glm::cross(glm::vec3(a1.x,a1.y,a1.z),glm::vec3(a2.x,a2.y,a2.z));

		a3 = glm::normalize(a3);
		
		normals.push_back(a3.x);
		normals.push_back(a3.y);
		normals.push_back(a3.z);
		normals.push_back(0.f);

		normals.push_back(a3.x);
		normals.push_back(a3.y);
		normals.push_back(a3.z);
		normals.push_back(0.f);
		i+=2;
	}
	// bottom normals
	for (int i = 0; i < numSegments; i++) {
		normals.push_back(0.f); normals.push_back(-1.f);  normals.push_back(0.f);  normals.push_back(0.f);
	}

	// top normals
	for (int i = 0; i < numSegments; i++) {
		normals.push_back(0.f); normals.push_back(1.f);  normals.push_back(0.f);  normals.push_back(0.f);
	}

	nbo = normals;

	for (int i = 0; i < numSegments*2;i++) {
		index.push_back(i);
		index.push_back(i+1);
		index.push_back(i+2);
	}

	int startindex = numSegments*2 + 2;
	for (int i = 1; i <= numSegments - 2;i++) {
		index.push_back(startindex);
		index.push_back(startindex + i);
		index.push_back(startindex + i + 1);
	}

	startindex = numSegments*3 + 2;
	for (int i = 1; i <= numSegments - 2;i++) {
		index.push_back(startindex);
		index.push_back(startindex + i);
		index.push_back(startindex + i + 1);
	}

	ibo = index;
}

//###############################################################################################################################