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
//ר�����ڶ�������
class MovingBall
{
private:
	int mode ;//�˶�ģʽ	
	double left,right,top,bottom;//�߽��ֵ

	bool move;//�Ƿ��˶�

	Ball *pc;//С��

	double direct;//�˶�����
	double v;//�ٶ�

private:
	double random(double start,double end);
	int collideBound();//�����߽�,f���������ıߵĴ��ţ�0-����ײ
	//1-��ߣ�2-�ұߣ�3-�ϱߣ�4-�±ߣ�
	void rectCollision();
public:

	MovingBall(Ball c,int mode,double left,double right,double top,double bottom);
	virtual ~MovingBall();

	void init();
	void start();
	void pause();

	void draw();

	void run();//ÿ��ִ�еĶ���
};