#pragma once
#include "Graphic.h"
#define MAXGRAPHICNUM 150
class GraphicList
{
public:
	Graphic * gList[MAXGRAPHICNUM];
	int num;
public:
	GraphicList(void);
	virtual ~GraphicList(void);

	void addGraphic(Graphic * g);
	void removeGraphic();
	Graphic * selectGraphic(int x,int y);
	void draw();
	void clear();

	friend CArchive & operator<<(CArchive&ar,GraphicList & gl);
	friend CArchive & operator>>(CArchive&ar,GraphicList & gl);

	bool clip(Rect *r);
};
