//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "MovingBall.h"

Ball::Ball(int x,int y,int r,COLORREF color,COLORREF fillColor,bool isFilled)
{
	this->x=x;
	this->y=y;
	this->r=r;
	this->color=color;
	this->fillColor=fillColor;
	this->isFilled=isFilled;
}

Ball::~Ball()
{}

void Ball::draw()
{
	if(isFilled)//���
	{
		if(select)
			glColor3f(1-GetRValue(fillColor)/255.0,1-GetGValue(fillColor)/255.0,1-GetBValue(fillColor)/255.0);
		else
			glColor3f(GetRValue(fillColor)/255.0,GetGValue(fillColor)/255.0,GetBValue(fillColor)/255.0);
		glBegin(GL_TRIANGLE_FAN);//����������������δ�
		glVertex2f(x,y);
		for(int i=0;i<=370;i+=10)
		{
			float p=(float)(i*3.14/180);
			glVertex2f((float)sin(p)*r+x,(float)cos(p)*r+y);// Բ�켣
		}
		glEnd();
	}	
	//���߽�
	if(select)
		glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
	else
		glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_LINE_LOOP);//����������������δ�
	for(int i=0;i<=370;i+=10)
	{
		float p=(float)(i*3.14/180);
		glVertex2f((float)sin(p)*r+x,(float)cos(p)*r+y);// Բ�켣
	}
	glEnd();


}

bool Ball::onGraphic(int x,int y)
{
	double rr=sqrt(double((x-this->x)*(x-this->x)+(y-this->y)*(y-this->y)));
	if(rr<=r)
		return true;
	else
		return false;
}

void Ball::translate(int m, int n)
{
	x+=m;
	y+=n;
}

void Ball::rotate(int direct)
{}

void Ball::rescale(double xs, double ys)
{
	double rr=xs>0?1.1:0.9;
	r=r*rr;
}

Graphic* Ball::copy()
{
	return new Ball(this->x,this->y,this->r,this->color,this->fillColor,this->isFilled);
}

void Ball::write(CArchive&ar)
{
	int type=2;
	ar<<type;//�������ͣ��������б�
	ar<<x<<y<<r<<color<<fillColor<<isFilled;
}

void Ball::read(CArchive&ar)
{
	ar>>x>>y>>r>>color>>fillColor>>isFilled;
}

bool Ball::clip(Rect *r)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
MovingBall::MovingBall(Ball c,int mode,double left,double right,double top,double bottom)
{
	this->mode=mode;
	pc=(Ball*)c.copy();//���ƶ���
	this->left=left;
	this->right=right;
	this->top=top;
	this->bottom=bottom;
}
MovingBall::~MovingBall()
{
	delete pc;
}

void MovingBall::init()
{
	move=false;
	switch(mode)
	{
	case 1:
		pc->x=left+pc->r;	
		pc->y=bottom+pc->r;	
		direct=random(10,80);
		v=random(3,10);
		break;
	}

}

void MovingBall::start()
{
	move=true;
}

void MovingBall::pause()
{
	move=false;
}

//�ػ���
void MovingBall::draw()
{
	//���߽�
	glColor3i(150,150,150);
	glBegin(GL_LINE_LOOP);
	glVertex2i(left,top);
	glVertex2i(left,bottom);
	glVertex2i(right,bottom);
	glVertex2i(right,top);			
	glEnd();
	//��С��
	pc->draw();
}

//ˢ��ִ�к���
void MovingBall::run()
{
	int i=0;
	if(!move)//�����˶��Ŀ���
		return;
	switch(mode)//����ģʽ�����˶���ʽ��ѡ��
	{
	case 1://������ײ�˶�		
		rectCollision();
		break;
	}
}

//�߽���
int MovingBall::collideBound()
{
	double d=direct/180.0*3.14;
	double x=pc->x+v*cos(d);
	double y=pc->y+v*sin(d);//������һ�˶�������
	if(x<left+pc->r)//��
		return 1;
	else if(x>right-pc->r)//��
		return 2;
	else//xû����ײ
	{
		if(y>top-pc->r)//��
			return 3;
		else if(y<bottom+pc->r)//��
			return 4;
		else//yû����ײ
			return 0;
	}
}

//��ײ�˶�
void MovingBall::rectCollision()
{
	double d=direct/180.0*3.14;

	int n=collideBound();//��¼��ײ�ı�

	switch(n)
	{
	case 0://����ײ
		pc->x+=v*cos(d);
		pc->y+=v*sin(d);
		break;
	case 1://��		
		pc->y=pc->y+tan(d)*(left+pc->r-pc->x);//����߽�����ֵ
		pc->x=left+pc->r;//���¶�λx,y���߽�
		//�����ö��򣬷��䶨��
		direct=180-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 2://��
		pc->y=pc->y+tan(d)*(right-pc->r-pc->x);//����߽�����ֵ
		pc->x=right-pc->r;//���¶�λx,y���߽�
		//�����ö��򣬷��䶨��
		direct=180-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 3://��
		pc->x=pc->x+(top-pc->r-pc->y)/tan(d);//����߽�����ֵ
		pc->y=top-pc->r;//���¶�λx,y���߽�
		//�����ö��򣬷��䶨��
		direct=-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 4://��
		pc->x=pc->x+(bottom+pc->r-pc->y)/tan(d);//����߽�����ֵ
		pc->y=bottom+pc->r;//���¶�λx,y���߽�
		//�����ö��򣬷��䶨��
		direct=-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	};

}

//�������������
double MovingBall::random(double start, double end)//����һ������start��end֮������������
{
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
