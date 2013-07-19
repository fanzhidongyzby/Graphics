#pragma once
#include <GL/glut.h>
#include "SutherlandHodgeman.h"
#define DBL_EPSILON 1
#define MAXPOINTSOFPOLYNUM 100
class Rect;
class Graphic
{
public :
	bool select;
	COLORREF color;
public:
	Graphic();
	virtual ~Graphic();

	void setSelect(bool set);

	virtual void draw();
	virtual bool onGraphic(int x,int y);
	virtual void translate(int m,int n);
	virtual void rotate(int direct);
	virtual void rescale(double xs,double ys);

	virtual Graphic*copy();
	virtual void write(CArchive&ar);
	virtual void read(CArchive&ar);

	virtual bool clip(Rect * r);

};

class Point :public Graphic
{
public:
	double x,y;
public:
	Point(){}//无参构造函数，为new操作准备
	Point(int x,int y,COLORREF color);
	virtual ~Point();

	void draw();
	bool onGraphic(int x,int y);
	void translate(int m,int n);
	void rotate(int direct);
	void rescale(double xs,double ys);

	Graphic*copy();
	void write(CArchive&ar);
	void read(CArchive&ar);

	bool clip(Rect * r);
};


class Line:public Graphic
{
public:
	double x0,x1,y0,y1;
public:
	Line(int x0,int y0,int x1,int y1,COLORREF color);
	virtual ~Line();

	void draw();
	bool onGraphic(int x,int y);
	void translate(int m,int n);
	void rotate(int direct);
	void rescale(double xs,double ys);

	Graphic*copy();
	void write(CArchive&ar);
	void read(CArchive&ar);

	bool clip(Rect * r);
private:
    typedef struct 
	{
		int all;
		int left,right,top,bottom;
	}OutCode;

	typedef struct 
	{
		float xmin,xmax,ymin,ymax;
	}Rectangle;
	
	bool LineClip(Rectangle *rect);
	void CompOutCode(float x,float y,Rectangle *rect,OutCode *outCode);
};


class Poly:public Graphic
{
public :
	Point * points;
	int num;
	COLORREF fillColor;
	bool isFilled;
public :
	Poly(COLORREF color,COLORREF fillColor,bool isFilled);
	virtual ~Poly();

	void addPoint(int x,int y);
	bool tailHitHead(int x,int y);//首位相连
	void clear();
	void drawLines();

	void draw();
	bool onGraphic(int x,int y);	
	void translate(int m,int n);
	void rotate(int direct);
	void rescale(double xs,double ys);

	Graphic*copy();
	void write(CArchive&ar);
	void read(CArchive&ar);

	bool clip(Rect * r);
private:
	//命中算法需要的结构体
	typedef struct 
	{ 
		double min_x, min_y, max_x, max_y;
	} rect_t;
	//求边界
	void vertices_get_extent (const Point* vl, int np, /* in vertices */ rect_t* rc /* out extent*/ ) ;
	//判断p,q是否在同一个直线上
	static int is_same(const Point* l_start, const Point* l_end, /* line l */ const Point* p, const Point* q) ;
	//判断两个直线是否相交
	static int is_intersect(const Point* s1_start, const Point* s1_end, const Point* s2_start, const Point* s2_end);
	//下面的函数pt_in_poly就是判断点(v)是(1)否(0)在多边形(vl：np)内的程序
	int pt_in_poly ( const Point* vl, int np, /* polygon vl with np vertices */ const Point* v);
};


class Circle:public Poly
{
public :
	double x,y;
	double r;
	bool isProto;//是否是原型
public :
	Circle(int x,int y,int r,COLORREF color,COLORREF fillColor,bool isFilled);
	virtual ~Circle();

	void draw();
	void rotate(int direct);//避免转动时的抖动
private :
	void init();
};

class Rect:public Poly
{	
public:
	double x0,x1,y0,y1;
	bool isProto;//是否是原型
public:
	Rect(int x0,int y0,int x1,int y1,COLORREF color,COLORREF fillColor,bool isFilled);
	virtual ~Rect();
	void draw();

private:
	void init();
};


class Bezier:public Poly
{
public:
	COLORREF ctrlPtrColor;
	Bezier(COLORREF lineColor,COLORREF bezierColor,COLORREF ptrColor,bool isCtrled);
	virtual ~Bezier();
	void draw();
	void write(CArchive&ar);
	void read(CArchive&ar);
};