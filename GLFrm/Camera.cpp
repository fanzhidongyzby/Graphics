#include "stdafx.h"
#include "Camera.h"
#include <GL/glut.h>
#include <cmath>
//#define  EYE_TO_CENTER 100
Camera::Camera()
{
	g_eye[0]=10;//
	g_eye[1]=10;
	g_eye[2]=10;//
	g_look[0]=0;
	g_look[1]=0;
	g_look[2]=0;

	g_Angle=-135;//��λ��
	g_elev=-10;//��ֱƫ��

	speed =DEFAULT_SPEED;
	rotateSpeed=DEFUALT_ROTATE_SPEED;
	elevSpeed=DEFAULT_ELEV_SPEED;
}

Camera::~Camera()
{

}

void Camera::forward_back(bool cmd)
{
	double rad_xz =3.13149* g_Angle/180.0;	//����������ת���ĽǶ�,��ת�Ǹ�ֵ
	if(cmd)//ǰ
	{
		g_eye[0]+=cos(rad_xz)*speed;
		g_eye[2]+=sin(rad_xz)*speed;	
		g_look[0]+=cos(rad_xz)*speed;
		g_look[2]+=sin(rad_xz)*speed;	
		//g_look[0] = float(g_eye[0] + EYE_TO_CENTER*cos(rad_xz));
	    //g_look[2] = float(g_eye[2] + EYE_TO_CENTER*sin(rad_xz));
	}
	else //��
	{
		g_eye[0]-=cos(rad_xz)*speed;
		g_eye[2]-=sin(rad_xz)*speed;
		g_look[0]-=cos(rad_xz)*speed;
		g_look[2]-=sin(rad_xz)*speed;
		//g_look[0] = float(g_eye[0] + EYE_TO_CENTER*cos(rad_xz));
	    //g_look[2] = float(g_eye[2] + EYE_TO_CENTER*sin(rad_xz));
	}
}

void Camera::left_right(bool cmd)
{
	double rad_xz =3.13149* g_Angle/180.0;	//����������ת���ĽǶ�,��ת�Ǹ�ֵ
	if(cmd)//��
	{
		g_eye[0]+=sin(rad_xz)*speed;		//�ӵ��x����
		g_eye[2]-=cos(rad_xz)*speed;		//�ӵ��z����	
		g_look[0]+=sin(rad_xz)*speed;
		g_look[2]-=cos(rad_xz)*speed;	
		//g_look[0] = float(g_eye[0] + EYE_TO_CENTER*cos(rad_xz));
	    //g_look[2] = float(g_eye[2] + EYE_TO_CENTER*sin(rad_xz));
	}
	else //��
	{
		g_eye[0]-=sin(rad_xz)*speed;		//�ӵ��x����
		g_eye[2]+=cos(rad_xz)*speed;		//�ӵ��z����
		g_look[0]-=sin(rad_xz)*speed;
		g_look[2]+=cos(rad_xz)*speed;
		//g_look[0] = float(g_eye[0] + EYE_TO_CENTER*cos(rad_xz));
	    //g_look[2] = float(g_eye[2] + EYE_TO_CENTER*sin(rad_xz));
	}
}

void Camera::up_down(bool cmd)
{
	if(cmd)//��
	{
		g_eye[1]+=speed;
		g_look[1] +=speed;
	}
	else//��
	{
		g_eye[1]-=speed;
		g_look[1] -=speed;
	}
}

void Camera::horizontal(bool cmd)
{
	double d_rad_xz=3.13149* rotateSpeed/180.0;
	if(cmd)//��
	{
		g_Angle-=rotateSpeed;//��¼��ת��	
		if(g_Angle<=-360)
			g_Angle=0;
		g_look[2]=cos(d_rad_xz)*(g_look[2]-g_eye[2])-sin(d_rad_xz)*(g_look[0]-g_eye[0])+g_eye[2];
		g_look[0]=sin(d_rad_xz)*(g_look[2]-g_eye[2])+cos(d_rad_xz)*(g_look[0]-g_eye[0])+g_eye[0];
	}
	else//��
	{
		g_Angle+=rotateSpeed;
		if(g_Angle>=360)
			g_Angle=0;
		g_look[2]=cos(-d_rad_xz)*(g_look[2]-g_eye[2])-sin(-d_rad_xz)*(g_look[0]-g_eye[0])+g_eye[2];
		g_look[0]=sin(-d_rad_xz)*(g_look[2]-g_eye[2])+cos(-d_rad_xz)*(g_look[0]-g_eye[0])+g_eye[0];
	}
	
}
void Camera::vertical(bool cmd)
{
	if(cmd)//����
	{
		 g_elev +=elevSpeed;	
	     if (g_elev>100)
			 g_elev=100;	//�������ȼ���ֵ
	}
	else//�¸�
	{
		g_elev -=elevSpeed;	
	     if (g_elev<-100)
			 g_elev=-100;	//�������ȼ���ֵ
	}
	g_look[1]=g_eye[1]+g_elev;//�޸Ľ���y
}

void Camera:: lookAt()
{
	gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1],g_look[2],0.0,1.0,0.0);
}


void Camera::cursorCtrl()//������
{
	int midX=640;
	int midY=400;
	POINT p;
	GetCursorPos(&p);
	rotateSpeed=2;
	elevSpeed=0.1;
	if(p.x>midX)
		horizontal(false);
	else if(p.x<midX)
		horizontal(true);
	if(p.y>midY)
		vertical(false);
	else if(p.y<midY)
		vertical(true);
	rotateSpeed=DEFUALT_ROTATE_SPEED;
	elevSpeed=DEFAULT_ELEV_SPEED;
	SetCursorPos(midX,midY);
}