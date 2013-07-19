// GLFrmView.h : CGLFrmView ��Ľӿ�
//


#pragma once

#include <GL/glut.h>
#include "Graphic.h"
#include "GraphicList.h"
#include "MovingBall.h"
#include "Camera.h"
#include "BasicObject.h"
#include "GLFrmDoc.h"//ע�⣡����Frame����Viewʱ�����ԭ������ΪFrameû�а���Doc

#define ANIMATION_BALL_NUM 4//С���Ĭ������
class CGLFrmView : public CView
{
protected: // �������л�����
	CGLFrmView();
	DECLARE_DYNCREATE(CGLFrmView)

// ����
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
	
	GraphicList list;//ͼ������

	Graphic * tempG;//��ʱͼ�Σ���¼���ڻ��Ƶ�ͼ��

	bool lbdown;//�������

	int polyNum;//����ζ�����

	bool drawing;//���ڻ���,�����Ҽ��˵�

	bool fillOrNot;//�Ƿ����

	int TRR;//��¼��ת�����ţ�ƽ�Ƶ�ѡ��

	Point prePos;//��һ��λ��

	static Graphic *selectG;//ѡ���ͼ��

	Graphic *clipBoard;//���а�

	MovingBall *animationBall[ANIMATION_BALL_NUM];//����С��

	static Rect *clipRect;//�ü�����
	
	bool go;//��ʱ������

	Camera viewer;//�������

    //��¼������״ֵ̬
	bool w,a,s,d,up,down,left,right,home,end,pgup,pgdn;

	bool cursorCtrlEnable;//�����Ƴ���

	double exagrate;//�Ŵ�����С

	BasicObject bo;//��������
// ����
public:
	//###########################################
	bool InitializeOpenGL();
	//###########################################
	bool SetupPixelFormat();
	//###########################################
	void RenderScene();

	void initialize();
	void finalize();

	static FILE *f;//�����ļ�ָ��

	void ballInit();//С��ĳ�ʼ��

	void keyRespond();//������Ӧ
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    //��д�ĺ���###########################################
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
// ʵ��
public:
	virtual ~CGLFrmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // GLFrmView.cpp �еĵ��԰汾
inline CGLFrmDoc* CGLFrmView::GetDocument() const
   { return reinterpret_cast<CGLFrmDoc*>(m_pDocument); }
#endif

