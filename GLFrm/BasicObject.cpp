#include "StdAfx.h"
#include "BasicObject.h"
#include <cmath>
/////////////////////////////////////////////////////////////////////////////////
void BasicObject::cubic(double x,double y,double z,double size)
{
	glPushMatrix();
	glTranslatef(x-size/2,y,z+size/2);
	glScalef(size,size,size);
	glBegin(GL_QUAD_STRIP);//填充凸多边形
	glColor3f(1,0,0);
    glVertex3f(0.0f,0.0f ,0.0f);//a0点
    glVertex3f(0.0f,1.0f ,0.0f);//a1点
	glColor3f(1,1,0);
    glVertex3f(1.0f,0.0f, 0.0f);//b0点
    glVertex3f(1.0f,1.0f, 0.0f);//b1点
	glColor3f(0,1,0);
    glVertex3f(1.0f,0.0f,-1.0f);//c0点
    glVertex3f(1.0f,1.0f,-1.0f);//c1点
	glColor3f(0,1,1);
    glVertex3f(0.0f,0.0f,-1.0f);//d0点
    glVertex3f(0.0f,1.0f,-1.0f);//d1点
	glColor3f(0,0,1);
    glVertex3f(0.0f,0.0f ,0.0f);//a0点
    glVertex3f(0.0f,1.0f ,0.0f);//a1点
    glEnd();
    //现在这个正方体还缺上下两个面。应该补上。
    glBegin(GL_QUADS);//填充凸多边形
	glColor3f(0,0,1);
	glVertex3f(0.0f,0.0f ,0.0f);//a0点
	glVertex3f(1.0f,0.0f, 0.0f);//b0点
	glVertex3f(1.0f,0.0f,-1.0f);//c0点
	glVertex3f(0.0f,0.0f,-1.0f);//d0点
	glColor3f(0,0,1);
	glVertex3f(0.0f,1.0f ,0.0f);//a1点
	glVertex3f(1.0f,1.0f, 0.0f);//b1点
	glVertex3f(1.0f,1.0f,-1.0f);//c1点
	glVertex3f(0.0f,1.0f,-1.0f);//d1点
    glEnd();
	glPopMatrix();
}

void BasicObject::pillar (double x,double y,double z,double r,double h) //园柱
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(r,h,r);
	
	glBegin(GL_QUAD_STRIP);// 连续填充四边形串
	for(int i=0;i<=390;i+=30)
	{
		glColor3f(i/390.0f,0,1);
		float p=(float)(i*3.14/180);		
		glVertex3f((float)sin(p)/2,1.0f,(float)cos(p)/2 );// 前园 
		glVertex3f((float)sin(p)/2,0.0f,(float)cos(p)/2 );// 后园 
	}
	glEnd();
	glPopMatrix();
}

void BasicObject::tetrahedron(double x,double y,double z,double size)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(size,size,size);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(0,0,1);
	glVertex3f(0.5,0,-0.5);
	glColor3f(1,0,0);
	glVertex3f(0,1,0);
	glColor3f(0,1,0);
	glVertex3f(-0.5,0,-0.5);
	glColor3f(0,0,1);
	glVertex3f(0,0,1);
	glColor3f(1,1,0);
	glVertex3f(0.5,0,-0.5);
	glEnd();
	glPopMatrix();
}

void BasicObject::bezierLine()
{
	GLfloat ctrlPts [4][3] = { {-50.0, 40.0, 0.0}, {-10.0, 70.0, 0.0},{10.0, -70.0, 0.0}, {80.0, 40.0, 0.0} };
	glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlPts);
    glEnable (GL_MAP1_VERTEX_3);
    GLint k;
    glColor3f (0.0, 0.0, 1.0);           
    glBegin (GL_LINE_STRIP); //绘制Bezier  曲线          
        for (k = 0; k <= 50; k++)     glEvalCoord1f (GLfloat (k) / 50.0);
    glEnd ();

    glColor3f (1.0, 0.0, 0.0); glPointSize (5.0); //绘制控制点
    glBegin (GL_POINTS);                 
       for (k = 0; k < 4; k++)    glVertex3fv (ctrlPts [k]);
    glEnd ();
    //绘制控制多边形
    glColor3f (0.0, 1.0, 0.0);  glLineWidth (2.0);                   
    glBegin (GL_LINE_STRIP);                 
         for (k = 0; k < 4; k++)  glVertex3fv (&ctrlPts [k][0]);
    glEnd ();
	glLineWidth (1.0);
}

void BasicObject::bezierSurface()
{
	GLfloat ctrlPts [4][4][3] = {
       { {-1.5, -1.5,  4.0}, {-0.5, -1.5,  2.0}, {-0.5, -1.5, -1.0}, { 1.5, -1.5,  2.0} },
       { {-1.5, -0.5,  1.0}, {-0.5, -0.5,  3.0}, { 0.5, -0.5,  0.0}, { 1.5, -0.5, -1.0} },
       { {-1.5,  0.5,  4.0}, {-0.5,  0.5,  0.0},  { 0.5,  0.5,  3.0}, { 1.5,  0.5,  4.0} },
       { {-1.5,  1.5, -2.0}, {-0.5,  1.5, -2.0}, { 0.5,  1.5,  0.0}, { 1.5,  1.5, -1.0} }
    };
    glPushMatrix();    
	glRotatef(35.0, 1.0, 1.0, 1.0);
	glTranslatef(0,40,0);
    glScalef(10,10,10);	
	glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4,
                     0.0, 1.0, 12, 4, &ctrlPts[0][0][0]);
    glEnable (GL_MAP2_VERTEX_3);
    GLint k, j;

    glColor3f (0.0, 1.0, 1.0);
    for (k = 0; k <= 8; k++)
    {
        glBegin (GL_LINE_STRIP);  
            for (j = 0; j <= 40; j++)
            glEvalCoord2f (GLfloat (j) / 40.0, GLfloat (k) / 8.0);
        glEnd ( );
        glBegin (GL_LINE_STRIP);
          for (j = 0; j <= 40; j++)
            glEvalCoord2f (GLfloat (k) / 8.0, GLfloat (j) / 40.0);
        glEnd ( );
    }

    glColor3f (1.0, 0.0, 0.0);             
    glPointSize (5.0);                   
    glBegin (GL_POINTS);                 
      for (k = 0; k < 4; k++)
      for (j = 0; j < 4; j++)
        glVertex3fv (&ctrlPts [k][j][0]);
    glEnd ();
    glPopMatrix();    
}