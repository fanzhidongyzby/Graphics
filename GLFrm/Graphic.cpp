#include "StdAfx.h"
#include "Graphic.h"
#include <cmath>
Graphic::Graphic()
{
	select=false;
}

Graphic::~Graphic()
{
}
void Graphic::draw() 
{}

void Graphic ::setSelect(bool set)
{
	select=set;
}

bool Graphic::onGraphic(int x, int y)
{
	return false;
}

void Graphic::translate(int m, int n)
{}

void Graphic::rotate(int direct)
{}

void Graphic::rescale(double xs,double ys)
{}

Graphic* Graphic::copy()
{
	return NULL;
}

void Graphic::write(CArchive &ar)
{}

void Graphic::read(CArchive &ar)
{}

bool Graphic::clip(Rect*r)
{
	return false;
}

///////////////////////////////////////////////////////////////////

Point::Point(int x,int y,COLORREF color)
{
	this->x=x;
	this->y=y;
	this->color=color;
}

Point::~Point()
{
}

void Point::draw()
{
	glPointSize(3);
	if(select)
		glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
	else
		glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

bool Point::onGraphic(int x, int y)
{
	if(abs(x-this->x)<=2&&abs(y-this->y)<=2)
		return true;
	else
		return false;
}

void Point::translate(int m, int n)
{
	x+=m;
	y+=n;
}

void Point::rotate(int direct)
{}

void Point::rescale(double xs,double ys)
{}

Graphic* Point::copy()
{
	return new Point(this->x,this->y,this->color);
}

void Point::write(CArchive&ar)
{
	int type=0;
	ar<<type;//输入类型，供读是判别
	ar<<x<<y<<color;
}
void Point::read(CArchive&ar)
{
	ar>>x>>y>>color;
}

bool Point::clip(Rect*r)
{
	return false;
}
///////////////////////////////////////////////////////////////////


Line::Line(int x0,int y0,int x1,int y1,COLORREF color)
{
	this->x0=x0;
	this->y0=y0;
	this->x1=x1;
	this->y1=y1;
	this->color=color;
}

Line::~Line()
{}

void Line ::draw()
{
	if(select)
		glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
	else
		glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_LINES);
	glVertex2i(x0,y0);
	glVertex2i(x1,y1);
	glEnd();
}

bool Line::onGraphic(int x, int y)
{
	double x1, x2, y1, y2, d0, d1, d2, d3, x0, y0, ave;

	x1 = this->x0;
	y1 = this->y0;
	x2 = this->x1;
	y2 = this->y1;

	//点击坐标
	x0 = x;
	y0 = y;

	if ((x0 > x1 && x0 < x2) || (x0 > x2 && x0 < x1))//判断点击位置是否在范围以内
	{
		d1 = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));//点击位置到起点距离
		d2 = sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));//点击位置到终点距离
		d3 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));//直线距离

		ave = (d1 + d2 + d3) / 2;

		d0 = sqrt(ave * (ave - d1) * (ave - d2) * (ave - d3)) / d3;//点击位置到直线的距离

		if (d0 < 2)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

void Line::translate(int m, int n)
{
	x0+=m;
	y0+=n;
	x1+=m;
	y1+=n;
}

void Line::rotate(int direct)
{
	double midX=(x0+x1)/2;
	double midY=(y0+y1)/2;

	double pi=3.14159265358979323846;
	double a=pi/180*10;
	a=direct>0?a:-a;
	double xx1=(x1-midX)*cos(a)-(y1-midY)*sin(a)+midX;
	double yy1=(x1-midX)*sin(a)+(y1-midY)*cos(a)+midY;
	x1=xx1;
	y1=yy1;
	x0=2*midX-x1;
	y0=2*midY-y1;


}

void Line::rescale(double xs, double ys)
{
	double midX=(x0+x1)/2;
	double midY=(y0+y1)/2;

	double xx=xs>0?1.1:0.9;
	double yy=ys>0?1.1:0.9;
	double xx1=(x1-midX)*xx+midX;
	double yy1=(y1-midY)*yy+midY;

	x1=xx1;
	y1=yy1;
	x0=2*midX-x1;
	y0=2*midY-y1;
}

Graphic* Line::copy()
{
	return new Line(this->x0,this->x1,this->y0,this->y1,this->color);
}

void Line::write(CArchive&ar)
{
	int type=1;
	ar<<type;//输入类型，供读是判别
	ar<<x0<<x1<<y0<<y1<<color;
}

void Line::read(CArchive&ar)
{
	ar>>x0>>x1>>y0>>y1>>color;
}

bool Line::clip(Rect *r)
{
	//修正
	double a,b,c,d;
	a=r->x0>r->x1?r->x1:r->x0;//xmin
	b=r->x0>r->x1?r->x0:r->x1;//xmax
	c=r->y0>r->y1?r->y1:r->y0;//ymin
	d=r->y0>r->y1?r->y0:r->y1;//ymax

	Rectangle rec;

	rec.xmin=a;
	rec.xmax=b;
	rec.ymin=c;
	rec.ymax=d;

	//裁剪
	return LineClip(&rec);
}
bool Line::LineClip(Rectangle *rect)
{
	int x0=this->x0;
	int y0=this->y0;
	int x1=this->x1;
	int y1=this->y1;

	bool accept=0,done=0;
	OutCode outCode0,outCode1;
	OutCode * outCodeOut;
	float x,y;

	CompOutCode(x0,y0,rect,&outCode0);
	CompOutCode(x1,y1,rect,&outCode1);


	do
	{
		if(outCode0.all==0&&outCode1.all==0) /*完全可见*/
		{
			accept=true;
			done=true;
		}
		else if((outCode0.top*outCode1.top+outCode0.bottom*outCode1.bottom
			+outCode0.right*outCode1.right+outCode0.left*outCode1.left) !=0) /*显然不可见*/
		{
			done=true;
		}else /*求交测试*/
		{
			if(outCode0.all!=0) outCodeOut=&outCode0; /*判断哪一点在窗口之外*/
			else outCodeOut=&outCode1;

			if(outCodeOut->left) /*与左边窗口求交*/
			{
				y=y0+(y1-y0)*(rect->xmin-x0)/(x1-x0);
				x=(float)rect->xmin;

			}else if(outCodeOut->top) /*与上边窗口求交*/
			{
				x=x0+(x1-x0)*(rect->ymax-y0)/(y1-y0);
				y=(float)rect->ymax;

			}else if(outCodeOut->right) /*与右边窗口求交*/
			{
				y=y0+(y1-y0)*(rect->xmax-x0)/(x1-x0);
				x=(float)rect->xmax;
			}else if(outCodeOut->bottom) /*与下边窗口求交*/
			{
				x=x0+(x1-x0)*(rect->ymin-y0)/(y1-y0);
				y=(float)rect->ymin;
			}

			if(outCodeOut->all==outCode0.all)  /*以交点为界,丢弃窗口之外的剩下的继续裁剪*/
			{
				x0=x;y0=y;
				CompOutCode(x0,y0,rect,&outCode0);
			}else
			{
				x1=x;y1=y;
				CompOutCode(x1,y1,rect,&outCode1);
			}
		}

	}while(!done);
	if(accept)
	{
		this->x0=x0;
		this->y0=y0;
		this->x1=x1;
		this->y1=y1;
	}

	return accept;//返回是否裁剪了
}
void Line::CompOutCode(float x,float y,Rectangle *rect,OutCode *outCode)
/*计算点(x,y)的编码*/
{
	outCode->all=0;

	outCode->top=outCode->bottom=0;
	if(y>float(rect->ymax))
	{
		outCode->top=1;
		outCode->all+=1;
	}
	else if(y<float(rect->ymin))
	{
		outCode->bottom=1;
		outCode->all+=1;
	}

	outCode->left=outCode->right=0;
	if(x>float(rect->xmax))
	{
		outCode->right=1;
		outCode->all+=1;
	}
	else if(x<float(rect->xmin))
	{
		outCode->left=1;
		outCode->all+=1;
	}
}/*end of CompOutCode*/
///////////////////////////////////////////////////////////////////
Circle::Circle(int x,int y,int r,COLORREF color,COLORREF fillColor,bool isFilled)
       :Poly(color,fillColor,isFilled)
{
	this->x=x;
	this->y=y;
	this->r=r;
	isProto=true;
	init();
}

Circle::~Circle()
{}

void Circle::init()
{
	this->clear();
	for(int i=0;i<360;i+=10)
	{
		float p=(float)(i*3.14/180);
		this->addPoint(sin(p)*r+x,cos(p)*r+y);
	}
}
void Circle::draw()
{
	if(isProto)
		init();
	Poly::draw();
}

void Circle::rotate(int direct)
{}


///////////////////////////////////////////////////////////////////
Poly::Poly(COLORREF color,COLORREF fillColor,bool isFilled)
{
	points=new Point[MAXPOINTSOFPOLYNUM];
	num=0;
	this->color=color;
	this->fillColor=fillColor;
	this->isFilled=isFilled;
}

Poly::~Poly()
{
	delete [] points;
}

void Poly::addPoint(int x,int y)
{
	points[num].x=x;
	points[num].y=y;
	points[num].color=color;
	num++;
}
void Poly::draw()
{
	if(isFilled&&num>=3)//填充
	{
		if(select)
			glColor3f(1-GetRValue(fillColor)/255.0,1-GetGValue(fillColor)/255.0,1-GetBValue(fillColor)/255.0);
		else
			glColor3f(GetRValue(fillColor)/255.0,GetGValue(fillColor)/255.0,GetBValue(fillColor)/255.0);
		glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串(POLYGON也可以)
		for(int i=0;i<num;i++)
		{
			glVertex2f(points[i].x,points[i].y);
		}
		glEnd();
	}
	//只画边界
	if(select)
		glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
	else
		glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<num;i++)
	{
		glVertex2f(points[i].x,points[i].y);
	}
	glEnd();
}

void Poly::drawLines()
{
	glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i<num;i++)
	{
		glVertex2f(points[i].x,points[i].y);
	}
	glEnd();
}

bool Poly::onGraphic(int x, int y)
{
	return (pt_in_poly(points,num,new Point(x,y,color))!=0);	
}

void Poly::translate(int m, int n)
{
	for(int i=0;i<num;i++)
	{
		points[i].x+=m;
		points[i].y+=n;
	}
}

void Poly::rotate(int direct)
{
	double xMax=points[0].x;
	double xMin=points[0].x;
	double yMax=points[0].y;
	double yMin=points[0].y;
	for(int i=0;i<num;i++)
	{
		xMax=xMax>points[i].x?xMax:points[i].x;
		xMin=xMin<points[i].x?xMin:points[i].x;
		yMax=yMax>points[i].y?yMax:points[i].y;
		yMin=yMin<points[i].y?yMin:points[i].y;
	}
	double midX=(xMax+xMin)/2;
	double midY=(yMax+yMin)/2;
	double pi=3.14159265358979323846;
	double a=pi/180*10;
	a=direct>0?a:-a;
	double x1,y1;
	for(int i=0;i<num;i++)
	{
		x1=points[i].x;
		y1=points[i].y;
		points[i].x=(x1-midX)*cos(a)-(y1-midY)*sin(a)+midX;
		points[i].y=(x1-midX)*sin(a)+(y1-midY)*cos(a)+midY;
	}
}

void Poly::rescale(double xs, double ys)
{
	double xMax=points[0].x;
	double xMin=points[0].x;
	double yMax=points[0].y;
	double yMin=points[0].y;
	for(int i=0;i<num;i++)
	{
		xMax=xMax>points[i].x?xMax:points[i].x;
		xMin=xMin<points[i].x?xMin:points[i].x;
		yMax=yMax>points[i].y?yMax:points[i].y;
		yMin=yMin<points[i].y?yMin:points[i].y;
	}
	double midX=(xMax+xMin)/2;
	double midY=(yMax+yMin)/2;

	double xx=xs>0?1.1:0.9;
	double yy=ys>0?1.1:0.9;

	double x1 ,y1;
	for(int i=0;i<num;i++)
	{
		x1=points[i].x;
		y1=points[i].y;
		points[i].x=(x1-midX)*xx+midX;
		points[i].y=(y1-midY)*yy+midY;
	}
}

Graphic* Poly::copy()
{
	Poly *d=new Poly(this->color,this->fillColor,this->isFilled);
	d->num=this->num;
	d->points=new Point[d->num];
	for(int i=0;i<d->num;i++)
	{
		d->points[i].x=points[i].x;
		d->points[i].y=points[i].y;
		d->points[i].color=points[i].color;
	}
	return d;
}

void Poly::write(CArchive&ar)
{
	int type=3;
	ar<<type;//输入类型，供读是判别
	ar<<color<<fillColor<<isFilled<<num;
	for(int i=0;i<num;i++)
	{
		ar<<points[i].x<<points[i].y;
	}
}

void Poly::read(CArchive&ar)
{
	ar>>color>>fillColor>>isFilled>>num;
	for(int i=0;i<num;i++)
	{
		ar>>points[i].x>>points[i].y;
	}
}

bool Poly::clip(Rect * r)
{
	SutherlandHodgeman su;
	//修正
	double a,b,c,d;
	a=r->x0>r->x1?r->x1:r->x0;//xmin
	b=r->x0>r->x1?r->x0:r->x1;//xmax
	c=r->y0>r->y1?r->y1:r->y0;//ymin
	d=r->y0>r->y1?r->y0:r->y1;//ymax


	VertexArray pointsIn;
	VertexArray pointsOut;

	Edge e[4];
	//下
	e[0][0].x=a;
	e[0][0].y=c;
	e[0][1].x=b;
	e[0][1].y=c;
	//右
	e[1][0].x=b;
	e[1][0].y=c;
	e[1][1].x=b;
	e[1][1].y=d;
	//上
	e[2][0].x=b;
	e[2][0].y=d;
	e[2][1].x=a;
	e[2][1].y=d;
	//左
	e[3][0].x=a;
	e[3][0].y=d;
	e[3][1].x=a;
	e[3][1].y=c;



	//首先判断最快
	bool poliPointInRect=false;
	for(int i=0;i<num;i++)//多边形点在矩形内部
	{
		if(points[i].x>=a&&points[i].x<=b
			&&points[i].y>=c&&points[i].y<=d)
		{
			poliPointInRect=true;
			break;
		}
	}

	bool rectPointInPoly=false;
	if(!poliPointInRect)
	{		
		for(int i=0;i<num;i++)//矩形点在多边形内部
		{
			if(this->onGraphic(e[i][0].x,e[i][0].y))
			{
				rectPointInPoly=true;
				break;
			}
		}
	}

	bool hasRealInteract=false;//有交点
	if(!rectPointInPoly)
	{
		Vertex inte,s,p;
		
		for(int i=0;i<num;i++)
		{
			s.x=points[i].x;
			s.y=points[i].y;
			p.x=points[(i+1)%num].x;
			p.y=points[(i+1)%num].y;

			for(int j=0;j<4;j++)
			{			
				su.Intersect(&s,&p,e[j],&inte);//求交点，求交点的算法不可靠！？？？

				if(inte.x>=a&&inte.x<=b&&inte.y>=c&&inte.y<=d)//交点位置在矩形内部，有效
				{
					Line l(s.x,s.y,p.x,p.y,RGB(0,0,0));
					if(l.onGraphic(inte.x,inte.y))//而且在两端点之间！！！
					{
						hasRealInteract=true;
					    break;
					}				
					
				}
			}
			if(hasRealInteract)
				break;

		}
		if(!hasRealInteract)//最可靠的算法也不在矩形范围
			return false;
	}


	bool clipComp=false;

	for(int j=0;j<4;j++)
	{
		for(int i=0;i<num;i++)
		{
			pointsIn[i].x=points[i].x;
			pointsIn[i].y=points[i].y;
		}

		int m=0;
		su.PolygonClip(num,pointsIn,&m,pointsOut,e[j]);
		if(m>3)
		{
			clipComp=true;
			num=0;
			for(int i=0;i<m;i++)
			{
				points[i].x=pointsOut[i].x;
				points[i].y=pointsOut[i].y;
				points[i].color=color;
				num++;
			}
		}
	}


	return clipComp;
}
//针对两个点以上的Poly！！！
bool Poly::tailHitHead(int x,int y)
{
	if(num==0)//无意义
	{
		MessageBox(NULL,L"警告",L"无效操作！",0);
		return false;
	}
	return points[0].onGraphic(x,y);//在第一个点的有效区域
}

void Poly::clear()
{
	num=0;
}
void Poly::vertices_get_extent (const Point* vl, int np, /* in vertices */ rect_t* rc /* out extent*/ ) 
{ 
	int i; 
	if (np > 0){ 
		rc->min_x = rc->max_x = vl[0].x; rc->min_y = rc->max_y = vl[0].y; 
	}else{ 
		rc->min_x = rc->min_y = rc->max_x = rc->max_y = 0; /* =0 ? no vertices at all */ 
	} 
	for(i=1; i<np;i++)
	{ 
		if(vl[i].x < rc->min_x) rc->min_x = vl[i].x; 
		if(vl[i].y < rc->min_y) rc->min_y = vl[i].y; 
		if(vl[i].x > rc->max_x) rc->max_x = vl[i].x; 
		if(vl[i].y > rc->max_y) rc->max_y = vl[i].y; 
	} 
}

/* p, q is on the same of line l */ 
int Poly::is_same(const Point* l_start, const Point* l_end, /* line l */ const Point* p, const Point* q) 
{ 
	double dx = l_end->x - l_start->x; 
	double dy = l_end->y - l_start->y; 
	double dx1= p->x - l_start->x; 
	double dy1= p->y - l_start->y; 
	double dx2= q->x - l_end->x; 
	double dy2= q->y - l_end->y; 
	return ((dx*dy1-dy*dx1)*(dx*dy2-dy*dx2) > 0? 1 : 0); 
} 
/* 2 line segments (s1, s2) are intersect? */ 
int Poly::is_intersect(const Point* s1_start, const Point* s1_end, const Point* s2_start, const Point* s2_end) 
{ 
	return (is_same(s1_start, s1_end, s2_start, s2_end)==0 && 
		is_same(s2_start, s2_end, s1_start, s1_end)==0)? 1: 0; 
}

int Poly::pt_in_poly ( const Point* vl, int np, /* polygon vl with np vertices */ const Point* v) 
{ 
	int i, j, k1, k2, c; 
	rect_t rc; 
	Point w; 
	if (np < 3) 
		return 0; 
	vertices_get_extent(vl, np, &rc); 
	if (v->x < rc.min_x || v->x > rc.max_x || v->y < rc.min_y || v->y > rc.max_y) 
		return 0; 
	/* Set a horizontal beam l(*v, w) from v to the ultra right */ 
	w.x = rc.max_x + DBL_EPSILON; 
	w.y = v->y; 
	c = 0; /* Intersection points counter */ 
	for(i=0; i<np;i++)
	{ 
		j = (i+1) % np; 
		if(is_intersect(vl+i, vl+j, v, &w)) 
		{ 
			c++; 
		} 
		else if(vl[i].y==w.y) 
		{ 
			k1 = (np+i-1)%np; 
			while(k1!=i && vl[k1].y==w.y) 
				k1 = (np+k1-1)%np; 
			k2 = (i+1)%np; 
			while(k2!=i && vl[k2].y==w.y) 
				k2 = (k2+1)%np; 
			if(k1 != k2 && is_same(v, &w, vl+k1, vl+k2)==0) 
				c++; 
			if(k2 <= i) 
				break; 
			i = k2; 
		} 
	} 
	return c%2; 
}


///////////////////////////////////////////////////////////////////


Rect::Rect(int x0,int y0,int x1,int y1,COLORREF color,COLORREF fillColor,bool isFilled)
:Poly(color,fillColor,isFilled)
{
	this->x0=x0;
	this->y0=y0;
	this->x1=x1;
	this->y1=y1;
	isProto=true;
	init();
}

Rect::~Rect()
{}

void Rect::init()
{
	num=0;
	this->addPoint(x0,y0);
	this->addPoint(x1,y0);
	this->addPoint(x1,y1);
	this->addPoint(x0,y1);	
}

void Rect::draw()
{
	if(isProto)//还是原型
	{
		init();//重新初始化
	}
	Poly::draw();
}


Bezier::Bezier(COLORREF lineColor,COLORREF bezierColor,COLORREF ptrColor,bool isCtrled):Poly(lineColor,bezierColor,isCtrled)
{
	ctrlPtrColor=ptrColor;
}
Bezier::~Bezier()
{}
void Bezier::draw()
{
	float (*ctrlPts)[3]=new float[num][3];
	for(int i=0;i<num;i++)
	{
		ctrlPts[i][0]=points[i].x;
		ctrlPts[i][1]=points[i].y;
		ctrlPts[i][2]=0;
	}
	
	glMap1f (GL_MAP1_VERTEX_3, 0.0, 1.0, 3, num, *ctrlPts);
    glEnable (GL_MAP1_VERTEX_3);
    GLint k;

	//if(isFilled)//画控制点
	{
		if(select)
			glColor3f(1-GetRValue(ctrlPtrColor)/255.0,1-GetGValue(ctrlPtrColor)/255.0,1-GetBValue(ctrlPtrColor)/255.0);
		else
			glColor3f(GetRValue(ctrlPtrColor)/255.0,GetGValue(ctrlPtrColor)/255.0,GetBValue(ctrlPtrColor)/255.0);
		glPointSize (3.0);
		glBegin (GL_POINTS);                 
		for (k = 0; k < num; k++)   
			glVertex3fv (ctrlPts [k]);
		glEnd ();
		glPointSize (1.0);
	}

    if(isFilled)//画控制边
	{
		if(select)
			glColor3f(1-GetRValue(color)/255.0,1-GetGValue(color)/255.0,1-GetBValue(color)/255.0);
		else
			glColor3f(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0);
		glBegin (GL_LINE_STRIP);                 
		for (k = 0; k < num; k++)  
			glVertex3fv (&ctrlPts [k][0]);
		glEnd ();
	}             
    

	if(num>=3)//绘制Bezier  曲线 
	{
		if(select)
			glColor3f(1-GetRValue(fillColor)/255.0,1-GetGValue(fillColor)/255.0,1-GetBValue(fillColor)/255.0);
		else
			glColor3f(GetRValue(fillColor)/255.0,GetGValue(fillColor)/255.0,GetBValue(fillColor)/255.0);
		glLineWidth (2.0);
		glBegin (GL_LINE_STRIP);          
		for (k = 0; k <= 50; k++)     
			glEvalCoord1f (GLfloat (k) / 50.0);
		glEnd ();
		glLineWidth (1.0);
	}

	
    
}

void Bezier::write(CArchive &ar)
{
	int type=4;
	ar<<type;//输入类型，供读是判别
	ar<<color<<ctrlPtrColor<<fillColor<<isFilled<<num;
	for(int i=0;i<num;i++)
	{
		ar<<points[i].x<<points[i].y;
	}
}

void Bezier::read(CArchive &ar)
{
	ar>>color>>ctrlPtrColor>>fillColor>>isFilled>>num;
	for(int i=0;i<num;i++)
	{
		ar>>points[i].x>>points[i].y;
	}
}
