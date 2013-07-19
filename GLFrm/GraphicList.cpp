#include "StdAfx.h"
#include "GraphicList.h"
#include "GLFrmView.h"
GraphicList::GraphicList(void)
{
	num=0;
}

GraphicList::~GraphicList(void)
{
}

void GraphicList::addGraphic(Graphic *g)
{
	gList[num]=g;
	num++;
	for(int i=0;i<num;i++)
		gList[i]->setSelect(false);//消除选择模式
	gList[num-1]->setSelect(true);
	CGLFrmView::selectG=gList[num-1];
}

void GraphicList::removeGraphic()
{
	delete gList[num-1];
	num--;
	if(num!=0)//还有图形
	{
		for(int i=0;i<num;i++)
			gList[i]->setSelect(false);//消除选择模式
	    gList[num-1]->setSelect(true);
		CGLFrmView::selectG=gList[num-1];
	}
	else
		CGLFrmView::selectG=NULL;
}

Graphic * GraphicList::selectGraphic(int x,int y)
{
	for(int i=0;i<num;i++)
		gList[i]->setSelect(false);//消除选择模式

	int selectIndex=-1;
	for(int i=num-1;i>=0;i--)
	{
		if(gList[i]->onGraphic(x,y))
		{
			selectIndex=i;
			break;
		}
	}
	if(selectIndex==-1)//没有选择图元
	{		
		return NULL;
	}

	Graphic *g=gList[selectIndex];//临时记录选择的图元对象

	for(int i=selectIndex;i<num-1;i++)
		gList[i]=gList[i+1];

	gList[num-1]=g;//移至最后

	g->setSelect(true);//设置选中
	return g;
}

void GraphicList::draw()
{
	if(num==0)
		return;

	for(int i=0;i<num;i++)//正常绘制
	{
		gList[i]->draw();
	}	
}

void GraphicList::clear()
{
	for(int i=0;i<num;i++)
	{
		delete gList[i];
	}
	num=0;
}

CArchive & operator<<(CArchive&ar,GraphicList & gl)
{
	ar<<gl.num;
	for(int i=0;i<gl.num;i++)
	{
		gl.gList[i]->write(ar);
	}
	return ar;
}

CArchive & operator>>(CArchive&ar,GraphicList & gl)
{
	gl.clear();
	ar>>gl.num;
	Graphic * g;
	for(int i=0;i<gl.num;i++)
	{
		int type;
		ar>>type;		
		switch(type)
		{
		case 0:
			g=new Point();
			break;
		case 1:
			g=new Line(0,0,0,0,RGB(0,0,0));
			break;
		case 2:
			g=new Circle(0,0,0,RGB(0,0,0),RGB(0,0,0),false);
			break;
		case 3:
			g=new Poly(RGB(0,0,0),RGB(0,0,0),false);
		case 4:
			g=new Bezier(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0),false);
		}
		g->read(ar);
		gl.gList[i]=g;
	}
	return ar;
}

bool GraphicList::clip(Rect *r)
{
	int get=0;
	for(int i=0;i<num;i++)//正常绘制
	{
		if(gList[i]->clip(r))
			get++;
	}
	return get>0;
}