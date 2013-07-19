#include "Graphic.h"

class Ball :public Graphic
{
public :
	double x,y;
	double r;
	COLORREF fillColor;
	bool isFilled;
public :
	Ball(int x,int y,int r,COLORREF color,COLORREF fillColor,bool isFilled);
	virtual ~Ball();

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
//专门用于动画的类
class MovingBall
{
private:
	int mode ;//运动模式	
	double left,right,top,bottom;//边界的值

	bool move;//是否运动

	Ball *pc;//小球

	double direct;//运动方向
	double v;//速度

private:
	double random(double start,double end);
	int collideBound();//碰到边界,f返回碰到的边的代号，0-无碰撞
	//1-左边；2-右边；3-上边；4-下边；
	void rectCollision();
public:

	MovingBall(Ball c,int mode,double left,double right,double top,double bottom);
	virtual ~MovingBall();

	void init();
	void start();
	void pause();

	void draw();

	void run();//每次执行的动作
};