#pragma once
#include <GL/glut.h>

class BasicObject
{
public:
	void cubic(double x,double y,double z,double size);
	void pillar (double x,double y,double z,double r,double h);
	void tetrahedron(double x,double y,double z,double size);
	void bezierLine();
	void bezierSurface();
};
