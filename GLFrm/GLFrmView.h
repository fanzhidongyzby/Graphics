// GLFrmView.h : CGLFrmView 类的接口
//


#pragma once

#include <GL/glut.h>
#include "Graphic.h"
#include "GraphicList.h"
#include "MovingBall.h"
#include "Camera.h"
#include "BasicObject.h"
#include "GLFrmDoc.h"//注意！！！Frame包含View时出错的原因，是因为Frame没有包含Doc

#define ANIMATION_BALL_NUM 4//小球的默认数量
class CGLFrmView : public CView
{
protected: // 仅从序列化创建
	CGLFrmView();
	DECLARE_DYNCREATE(CGLFrmView)

// 属性
public:
	CGLFrmDoc* GetDocument() const;
	//******************************************
	HGLRC m_hRC; //Rendering Context
	//******************************************
	CDC* m_pDC; //Device Context
	//******************************************
	int width;
	//******************************************
	int height;
	
	GraphicList list;//图形数组

	Graphic * tempG;//临时图形，记录正在绘制的图形

	bool lbdown;//左键按下

	int polyNum;//多边形顶点数

	bool drawing;//正在绘制,控制右键菜单

	bool fillOrNot;//是否填充

	int TRR;//记录旋转，缩放，平移的选择

	Point prePos;//上一个位置

	static Graphic *selectG;//选择的图形

	Graphic *clipBoard;//剪切板

	MovingBall *animationBall[ANIMATION_BALL_NUM];//动画小球

	static Rect *clipRect;//裁剪矩形
	
	bool go;//定时器开关

	Camera viewer;//创建相机

    //记录按键的状态值
	bool w,a,s,d,up,down,left,right,home,end,pgup,pgdn;

	bool cursorCtrlEnable;//鼠标控制场景

	double exagrate;//放大与缩小

	BasicObject bo;//基本物体
// 操作
public:
	//###########################################
	bool InitializeOpenGL();
	//###########################################
	bool SetupPixelFormat();
	//###########################################
	void RenderScene();

	void initialize();
	void finalize();

	static FILE *f;//调试文件指针

	void ballInit();//小球的初始化

	void keyRespond();//按键反应
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    //重写的函数###########################################
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
// 实现
public:
	virtual ~CGLFrmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	//###########################################
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	//###########################################
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	//###########################################
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	//###########################################
	afx_msg void OnDestroy();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	void getRealCoordinate(int x,int y,CPoint * p);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
public:
	afx_msg void OnSelect();
public:
	afx_msg void OnPoint();
public:
	afx_msg void OnLine();
public:
	afx_msg void OnCircle();
public:
	afx_msg void OnPoly();
public:
	afx_msg void OnFillAgree();
public:
	afx_msg void OnFillRefuse();
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnRotate();
public:
	afx_msg void OnRescale();
public:
	afx_msg void OnTranslate();
public:
	afx_msg void OnGDel();
public:
	afx_msg void OnEditCut();
public:
	afx_msg void OnEditCopy();
public:
	afx_msg void OnEditPaste();
public:
	afx_msg void OnFileOpen();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimerctrl();
	afx_msg void OnFileSave();
	afx_msg void OnClip();
	afx_msg void OnRect();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnDraw2D();
	afx_msg void OnAnimation2D();
	afx_msg void OnRover3D();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBezier();
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // GLFrmView.cpp 中的调试版本
inline CGLFrmDoc* CGLFrmView::GetDocument() const
   { return reinterpret_cast<CGLFrmDoc*>(m_pDocument); }
#endif

