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
	if(isFilled)//填充
	{
		if(select)
			glColor3f(1-GetRValue(fillColor)/255.0,1-GetGValue(fillColor)/255.0,1-GetBValue(fillColor)/255.0);
		else
			glColor3f(GetRValue(fillColor)/255.0,GetGValue(fillColor)/255.0,GetBValue(fillColor)/255.0);
		glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
		glVertex2f(x,y);
		for(int i=0;i<=370;i+=10)
		{
			float p=(float)(i*3.14/180);
			glVertex2f((float)sin(p)*r+x,(float)cos(p)*r+y);// 圆轨迹
		}
		glEnd();
	}	
	//画边界
	if(select)
		glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
	else
		glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_LINE_LOOP);//扇形连续填充三角形串
	for(int i=0;i<=370;i+=10)
	{
		float p=(float)(i*3.14/180);
		glVertex2f((float)sin(p)*r+x,(float)cos(p)*r+y);// 圆轨迹
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
	ar<<type;//输入类型，供读是判别
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
	pc=(Ball*)c.copy();//复制对象
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

//重绘制
void MovingBall::draw()
{
	//画边届
	glColor3i(150,150,150);
	glBegin(GL_LINE_LOOP);
	glVertex2i(left,top);
	glVertex2i(left,bottom);
	glVertex2i(right,bottom);
	glVertex2i(right,top);			
	glEnd();
	//画小球
	pc->draw();
}

//刷新执行函数
void MovingBall::run()
{
	int i=0;
	if(!move)//进行运动的控制
		return;
	switch(mode)//依照模式进行运动方式的选择
	{
	case 1://矩形碰撞运动		
		rectCollision();
		break;
	}
}

//边界检测
int MovingBall::collideBound()
{
	double d=direct/180.0*3.14;
	double x=pc->x+v*cos(d);
	double y=pc->y+v*sin(d);//计算下一运动的坐标
	if(x<left+pc->r)//左
		return 1;
	else if(x>right-pc->r)//右
		return 2;
	else//x没有碰撞
	{
		if(y>top-pc->r)//上
			return 3;
		else if(y<bottom+pc->r)//下
			return 4;
		else//y没有碰撞
			return 0;
	}
}

//碰撞运动
void MovingBall::rectCollision()
{
	double d=direct/180.0*3.14;

	int n=collideBound();//记录碰撞的边

	switch(n)
	{
	case 0://无碰撞
		pc->x+=v*cos(d);
		pc->y+=v*sin(d);
		break;
	case 1://左		
		pc->y=pc->y+tan(d)*(left+pc->r-pc->x);//计算边界坐标值
		pc->x=left+pc->r;//重新定位x,y至边界
		//重新拿定向，反射定律
		direct=180-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 2://右
		pc->y=pc->y+tan(d)*(right-pc->r-pc->x);//计算边界坐标值
		pc->x=right-pc->r;//重新定位x,y至边界
		//重新拿定向，反射定律
		direct=180-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 3://上
		pc->x=pc->x+(top-pc->r-pc->y)/tan(d);//计算边界坐标值
		pc->y=top-pc->r;//重新定位x,y至边界
		//重新拿定向，反射定律
		direct=-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	case 4://下
		pc->x=pc->x+(bottom+pc->r-pc->y)/tan(d);//计算边界坐标值
		pc->y=bottom+pc->r;//重新定位x,y至边界
		//重新拿定向，反射定律
		direct=-direct;
		if(fabs(direct)>360)
			direct-=360;
		break;
	};

}

//随机数产生函数
double MovingBall::random(double start, double end)//返回一个介于start和end之间的随机浮点数
{
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}
