// GLFrmView.cpp : CGLFrmView ���ʵ��
//

#include "stdafx.h"
#include "GLFrm.h"


#include "GLFrmView.h"
#include "MainFrm.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLFrmView

IMPLEMENT_DYNCREATE(CGLFrmView, CView)

BEGIN_MESSAGE_MAP(CGLFrmView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_SELECT, &CGLFrmView::OnSelect)
	ON_COMMAND(ID_POINT, &CGLFrmView::OnPoint)
	ON_COMMAND(ID_LINE, &CGLFrmView::OnLine)
	ON_COMMAND(ID_CIRCLE, &CGLFrmView::OnCircle)
	ON_COMMAND(ID_POLY, &CGLFrmView::OnPoly)
	ON_COMMAND(ID_FILL_AGREE, &CGLFrmView::OnFillAgree)
	ON_COMMAND(ID_FILL_REFUSE, &CGLFrmView::OnFillRefuse)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ROTATE, &CGLFrmView::OnRotate)
	ON_COMMAND(ID_RESCALE, &CGLFrmView::OnRescale)
	ON_COMMAND(ID_TRANSLATE, &CGLFrmView::OnTranslate)
	ON_COMMAND(ID_G_DEL, &CGLFrmView::OnGDel)
	ON_COMMAND(ID_EDIT_CUT, &CGLFrmView::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CGLFrmView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CGLFrmView::OnEditPaste)
	ON_COMMAND(ID_FILE_OPEN, &CGLFrmView::OnFileOpen)
	ON_WM_TIMER()
	ON_COMMAND(ID_TIMERCTRL, &CGLFrmView::OnTimerctrl)
	ON_COMMAND(ID_FILE_SAVE, &CGLFrmView::OnFileSave)
	ON_COMMAND(ID_CLIP, &CGLFrmView::OnClip)
	ON_COMMAND(ID__RECT, &CGLFrmView::OnRect)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DRAW, &CGLFrmView::OnDraw2D)
	ON_COMMAND(ID_ANIMATION, &CGLFrmView::OnAnimation2D)
	ON_COMMAND(ID_ROVER, &CGLFrmView::OnRover3D)
	ON_WM_KEYUP()
	ON_COMMAND(ID_BEZIER, &CGLFrmView::OnBezier)
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

//�ļ�������Է���
//FILE *f;
//f=fopen("debug.txt","w+");
//fprintf(f,"U-L\n");
//fflush(f);
//FILE * CGLFrmView::f =fopen("debug.txt","w+");


Graphic * CGLFrmView::selectG=NULL;
Rect* CGLFrmView::clipRect=new Rect(-1,-1,-1,-1,RGB(255,255,255),RGB(0,0,0),false);
// CGLFrmView ����/����

CGLFrmView::CGLFrmView()
{
	// TODO: �ڴ˴���ӹ������
	initialize();
	ballInit();
}

void CGLFrmView::ballInit()
{
	//��0
	Ball c0(0,0,12,RGB(255,0,0),RGB(255,0,0),true);
	animationBall[0]=new MovingBall(c0,1,-200,0,200,0);
	//animationBall[0]=new MovingBall(c0,1,-200,200,200,-200);
	animationBall[0]->init();
	animationBall[0]->start();

	//��1
	Ball c1(0,0,9,RGB(0,255,0),RGB(0,255,0),true);
	animationBall[1]=new MovingBall(c1,1,0,200,200,0);
	//animationBall[1]=new MovingBall(c1,1,-200,200,200,-200);
	animationBall[1]->init();
	animationBall[1]->start();

	//��2
	Ball c2(0,0,6,RGB(255,255,0),RGB(255,255,0),true);
	animationBall[2]=new MovingBall(c2,1,0,200,0,-200);
	//animationBall[2]=new MovingBall(c2,1,-200,200,200,-200);
	animationBall[2]->init();
	animationBall[2]->start();

	//��3
	Ball c3(0,0,3,RGB(0,255,255),RGB(0,255,255),true);
	animationBall[3]=new MovingBall(c3,1,-200,0,0,-200);
	//animationBall[3]=new MovingBall(c3,1,-200,200,200,-200);
	animationBall[3]->init();
	animationBall[3]->start();
}

void CGLFrmView::initialize()//��ʼ������
{	
	lbdown=false;
	tempG=NULL;
	polyNum=0;
	drawing=false;
	fillOrNot=false;
	TRR=2;	
	clipBoard=NULL;
	go=true;	
	w=a=s=d=up=down=left=right=home=end=pgup=pgdn=false;
	cursorCtrlEnable=false;
	exagrate=60.0;
}

CGLFrmView::~CGLFrmView()
{
	finalize();
	delete animationBall[0];
}

void CGLFrmView::finalize()//������
{
	list.clear();
	if(clipBoard!=NULL)//��ռ��а�
		delete clipBoard;
	delete clipRect;//��ղü�����
}

BOOL CGLFrmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CGLFrmView ����

void CGLFrmView::OnDraw(CDC* pDC)//���������m_pDC�к����𣿣�����������������
{
	CGLFrmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );// Clear out the color & depth buffers	
	RenderScene(); //����Ļ�ͼ��������RC �л���	
	glFinish();
	::SwapBuffers( m_pDC->GetSafeHdc());// Now Swap the buffers
}

//��Ⱦ����

void CGLFrmView::RenderScene()
{	
	if(CMainFrame::functionChoice==0)//��ά��ͼ
	{
		//��ʼ��ͶӰ
		::glViewport(0, 0, width, height); // select the full client area
		// select the projection matrix and clear it
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		gluOrtho2D(-width/2, width/2, -height/2, height/2); // select the viewing volume
		// switch back to the modelview matrix and clear it
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		/////////////////////////////////////////////////background
		glLogicOp(GL_COPY);
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_LINES);
		glVertex2i(-width/2,0);
		glVertex2i(width/2,0);
		glVertex2i(0,-height/2);
		glVertex2i(0,height/2);
		glEnd();
		///////////////////////////////////////////////////all graphics
		list.draw();
		if(tempG!=NULL)
		{
			if(CMainFrame::menuChoice==4)//���ƶ����ʱ������߶λ��ƣ������ǿ������
			{
				Poly *p=(Poly *)tempG;
				p->drawLines();
			}
			else
				tempG->draw();
		}
		/////////////////////////////////////////////////////clip rectangle
		if(this->lbdown==true&&CMainFrame::menuChoice==6)//���ڲü�
		{		
			clipRect->draw();
		}
	}

	if(CMainFrame::functionChoice==1)//��ά����
	{
		//��ʼ��ͶӰ
		::glViewport(0, 0, width, height); // select the full client area
		// select the projection matrix and clear it
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		gluOrtho2D(-width/2, width/2, -height/2, height/2); // select the viewing volume
		// switch back to the modelview matrix and clear it
		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		///////////////////////////////////////////////////small balls
		glLogicOp(GL_COPY);
		animationBall[0]->draw();
		animationBall[1]->draw();
		animationBall[2]->draw();
		animationBall[3]->draw();
	}	
	if(CMainFrame::functionChoice==2)//��ά����
	{
		glViewport(0,0,width,height);			// ����OpenGL�ӿڴ�С��	
		glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
		glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
		gluPerspective							// ����͸��ͼ
			( exagrate,							// ͸�ӽ�����Ϊ 60 ��
			(GLfloat)width/(GLfloat)height,	// ���ڵĿ���߱�
			0.1f,								// ��Ұ͸�����:����1.0f
			1000.0f							// ��Ұ͸�����:ʼ��0.1fԶ��1000.0f
			);
		// �������������ƣ���һ���������þ�ͷ��Ƕȣ��ڶ��������ǳ���ȣ�������Զ�����С�
		glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
		glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT0);
		keyRespond();
		viewer.lookAt();

		glLogicOp(GL_COPY);
        ////////////////////////////////////////////////net
		glColor3f(0.5,0.5,0.5);
		glPushMatrix();
		glBegin(GL_LINES);
		for(int i=0;i<=100;i+=2)
		{
			glVertex3f(-50+i,0.5,-50);
			glVertex3f(-50+i,0.5,50);
		}
		for(int i=0;i<=100;i+=2)
		{
			glVertex3f(-50,0.5,-50+i);
			glVertex3f(50,0.5,-50+i);
		}
		glEnd();
		glPopMatrix();

         //////////////////////////////////////////////ground
		glColor3f(0,1.0,0);
		glPushMatrix();
		glBegin(GL_POLYGON);		
			glVertex3f(-50,0,-50);
			glVertex3f(50,0,-50);
			glVertex3f(50,0,50);
			glVertex3f(-50,0,50);
		glEnd();
		glPopMatrix();

		///////////////////////////////////////////////coordinate
		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(1,1,0);
		glVertex3f(-10,0.1,0);
		glVertex3f(10,0.1,0);
        glColor3f(0,1,1);
		glVertex3f(0,-10,0);
		glVertex3f(0,10,0);
		glColor3f(1,0,1);
		glVertex3f(0,0.1,-10);
		glVertex3f(0,0.1,10);
		glEnd();
		glPopMatrix();
		///////////////////////////////////////////////objects
		bo.cubic(10,0,-10,5);
		bo.pillar(10,0,-10,1,15);
		bo.tetrahedron(10,15,-10,10);
		bo.bezierLine();
		bo.bezierSurface();
	}
}

//����豸

bool CGLFrmView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1, // version number
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL // support window | support OpenGL|
		| PFD_DOUBLEBUFFER , //double buffered
		PFD_TYPE_RGBA, // RGBA type
		24, // 24-bit color depth
		0, 0, 0, 0, 0, 0, // color bits ignored
		0, 0, // no alpha buffer // shift bit ignored
		0, // no accumulation buffer
		0, 0, 0, 0, // accum bits ignored
		16, 0, // 16-bit z-buffer // no stencil buffer
		0, PFD_MAIN_PLANE, 0, // no auxiliary buffer // main layer// reserved
		0, 0, 0 // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if ( m_nPixelFormat == 0 ) 
		return FALSE;
	if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE) 
		return FALSE;
	return true;
}

//��ʼ��OpenGL

bool CGLFrmView::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if(m_pDC == NULL)
	{
		MessageBox(L"Error Obtaining DC");
		return FALSE;
	}
	//Failure to set the pixel format
	if(!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());
	//Failure to Create Rendering Context
	if(m_hRC == 0)
	{
		MessageBox(L"Error Creating RC");
		return FALSE;
	}
	//Make the RC Current
	if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
	{
		MessageBox(L"Error making RC Current");
		return FALSE;
	}
	//Specify Black as the clear color
	::glClearColor(0.1f,0.1f,0.4f,1.0f);
	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);
	//Enable Depth Testing
	//	::glEnable(GL_DEPTH_TEST);
	return true;
}

//��дCreate
BOOL CGLFrmView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//Initialize OpenGL Here
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
// CGLFrmView ��ӡ

BOOL CGLFrmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGLFrmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	
}

void CGLFrmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CGLFrmView ���

#ifdef _DEBUG
void CGLFrmView::AssertValid() const
{
	CView::AssertValid();
}

void CGLFrmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLFrmDoc* CGLFrmView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLFrmDoc)));
	return (CGLFrmDoc*)m_pDocument;
}
#endif //_DEBUG


// CGLFrmView ��Ϣ�������
int CGLFrmView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	InitializeOpenGL();	//��ʼ��OpenGL

	return 0;
}

BOOL CGLFrmView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);
	//����仰ע�͵�������Window ���ð�ɫ������ˢ��,���»�����˸
	return TRUE; //ֻҪ�շ��ؼ��ɡ�
}

void CGLFrmView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if ( 0 >= cx || 0 >= cy ) return;
	//::glViewport(0, 0, cx, cy); // select the full client area
	//// select the projection matrix and clear it
	//::glMatrixMode(GL_PROJECTION);
	//::glLoadIdentity();
	//gluOrtho2D(-cx/2, cx/2, -cy/2, cy/2); // select the viewing volume
	//// switch back to the modelview matrix and clear it
	//::glMatrixMode(GL_MODELVIEW);
	//::glLoadIdentity();

	width = cx;
	height = cy;
}

void CGLFrmView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	wglMakeCurrent(m_pDC->m_hDC,NULL); //�ͷ���m_hDC ��Ӧ��RC
	wglDeleteContext(m_hRC); //ɾ��RC if (m_pDC)
	delete m_pDC; //ɾ����ǰView ӵ�е�DC
}

//���豸����ת��Ϊʵ��OpenGL����
void CGLFrmView::getRealCoordinate(int x,int y,CPoint * p)
{
	//���λ�õ�����VS2005��VS2008������𣿣���
	p->x=x-width/2+3;
	p->y=height/2-y-3;	
}

//���
void CGLFrmView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	lbdown=true;

	

	CPoint p;
	this->getRealCoordinate(point.x,point.y,&p);
	int x=p.x;
	int y=p.y;

	prePos.x=x;
	prePos.y=y;//��¼����λ��

	//fprintf(f,"��굥����(%d,%d) ��ȣ�%d,�߶ȣ�%d",point.x,point.y,width,height);
	//fflush(f);
	//fprintf(f,"ʵ�����꣺(%d,%d)\n",x,y);
	//fflush(f);

	if(CMainFrame::functionChoice==0)
	{
		int choice=CMainFrame::menuChoice;
		//���ò˵�������
	    drawing=true;
		selectG=list.selectGraphic(x,y);
		switch(choice)
		{
		case 0://select		
			drawing=false;		
			break;
		case 2://Line
			if(tempG!=NULL)
			{
				delete tempG;
				tempG=NULL;
			}
			tempG=new Line(x,y,x,y,RGB(255,0,0));
			break;
		case 3://Circle
			if(tempG!=NULL)
			{
				delete tempG;
				tempG=NULL;
			}
			tempG=new Circle(x,y,0,RGB(255,0,0),RGB(255,255,0),fillOrNot);
			break;
		case 5://rect
			if(tempG!=NULL)
			{
				delete tempG;
				tempG=NULL;
			}
			tempG=new Rect(x,y,x,y,RGB(255,0,0),RGB(255,255,0),fillOrNot);
			break;
		case 6://clip
			clipRect->x0=clipRect->x1=x;
			clipRect->y0=clipRect->y1=y;
		}
		Invalidate();
	}
	CView::OnLButtonDown(nFlags,point);
}

void CGLFrmView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
   
	if(!lbdown)
		return;
	
	CPoint p;
	this->getRealCoordinate(point.x,point.y,&p);
	int x=p.x;
	int y=p.y;

	if(CMainFrame::functionChoice==0)
	{
		int choice=CMainFrame::menuChoice;
        drawing=true;
		Line *l;
		Circle *c;
		Rect*r;

		switch(choice)
		{
		case 0://Move
			if(selectG!=NULL)
			{
				selectG->translate(x-prePos.x,y-prePos.y);
				prePos.x=x;
				prePos.y=y;
			}
			//list.selectGraphic(x,y);
			break;
		case 2://DrawLine
			l=(Line*)tempG;
			l->x1=x;
			l->y1=y;		
			break;
		case 3://DrawCircle
			c=(Circle*)tempG;
			c->r=sqrt(float((x-c->x)*(x-c->x)+(y-c->y)*(y-c->y)));
			break;
		case 5://DrawRect
			r=(Rect*)tempG;
			r->x1=x;
			r->y1=y;
			break;
		case 6://clipRect
			clipRect->x1=x;
			clipRect->y1=y;
			break;
		}
		Invalidate();
	}
	if(CMainFrame::functionChoice==2)
	{		
		//viewer.cursorCtrl(640,400,point.x,point.y);
		//Invalidate();
	}
	CView::OnMouseMove(nFlags, point);	
}

void CGLFrmView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�ָ��˵�������



	lbdown=false;

	

	CPoint p;
	this->getRealCoordinate(point.x,point.y,&p);
	int x=p.x;
	int y=p.y;

	if(CMainFrame::functionChoice==0)
	{
		int choice=CMainFrame::menuChoice;
        drawing=false;
		Line *l;
		Circle *c;
		Rect*r;
		Poly *po;
		Bezier *be;
		bool polyEnd=false;//����λ��ƽ�����־

		switch(choice)
		{
		case 0://StopMove
			break;
		case 1://DrawPoint


			if(tempG!=NULL)
			{
				delete tempG;
				tempG=NULL;
			}
			tempG=new Point(x,y,RGB(255,0,0));
			break;
		case 2://DrawLine//�������������
			if (tempG==NULL) return;//���⵱�����������ʱ���ֵ���������Ӧ
			//LBDown�¼��Ӷ�����tempG==NULL ��bug��
			l=(Line*)tempG;
			l->x1=x;
			l->y1=y;
			if(l->x0==l->x1&&l->y0==l->y1)//������Чֱ��
			{
				delete tempG;
				tempG=NULL;
			}
			break;
		case 3://DrawCircle
			if (tempG==NULL) return;
			c=(Circle*)tempG;
			c->r=sqrt(float((x-c->x)*(x-c->x)+(y-c->y)*(y-c->y)));
			c->isProto=false;//��ʼ���ɹ�
			if(c->r==0)//������ЧԲ
			{
				delete tempG;
				tempG=NULL;
			}
			break;
		case 5://DrawRect
			if (tempG==NULL) return;
			r=(Rect*)tempG;
			r->x1=x;
			r->y1=y;
			r->isProto=false;//��ʼ���ɹ�
			if(r->x0==r->x1&&r->y0==r->y1)//������Ч����
			{
				delete tempG;
				tempG=NULL;
			}
			break;
		case 6://DrawClipRect
			clipRect->x1=x;
			clipRect->y1=y;

			if(clipRect->x0==clipRect->x1&&clipRect->y0==clipRect->y1)//��Ч�ü�����
				break;
			if(IDOK==MessageBox(L"��ȷ���Ը�������вü���",L"��ʾ",1))
			{			
				if(!list.clip(clipRect))
					MessageBox(L"�޲ü����������²ü�!");
				else
					MessageBox(L"�ü��ɹ�!");
			}
			break;
		case 7://DrawBezier
			if(polyNum==0)//��һ�ε���
			{
				//���ò˵�������
				drawing=true;

				if(tempG!=NULL)
				{
					delete tempG;
					tempG=NULL;
				}
				tempG=new Bezier(RGB(0,255,0),RGB(0,0,255),RGB(255,0,0),fillOrNot);
				be=(Bezier*)tempG;
				be->addPoint(x,y);
				polyNum++;
			}
			else 
			{
				drawing=true;
				be=(Bezier*)tempG;
				if(be->tailHitHead(x,y))//��������Bezier����
				{
					if(polyNum<3)//��ЧBezier����
					{
						delete tempG;
						tempG=NULL;
						polyNum=0;
						polyEnd=false;
					}
					else
						polyEnd=true;
					//�����˵�
					drawing=false;
				}
				else
				{
					be->addPoint(x,y);
					polyNum++;
				}
			}

			break;
		case 4://DrawPoly
			if(polyNum==0)//��һ�ε���
			{
				//���ò˵�������
				drawing=true;

				if(tempG!=NULL)
				{
					delete tempG;
					tempG=NULL;
				}
				tempG=new Poly(RGB(255,0,0),RGB(255,255,255),fillOrNot);
				po=(Poly*)tempG;
				po->addPoint(x,y);
				polyNum++;
			}
			else 
			{
				drawing=true;
				po=(Poly*)tempG;
				if(po->tailHitHead(x,y))//�������ƶ����
				{
					if(polyNum<3)//��Ч�����
					{
						delete tempG;
						tempG=NULL;
						polyNum=0;
						polyEnd=false;
					}
					else
						polyEnd=true;
					//�����˵�
					drawing=false;
				}
				else
				{
					po->addPoint(x,y);
					polyNum++;
				}
			}

			break;
		}

		if(tempG!=NULL)
		{
			if(choice!=4&&choice!=7)//���Ƕ���κ�Bezier����
			{
				list.addGraphic(tempG);
				tempG=NULL;
			}
			else
			{
				if(polyEnd)//���ƽ���
				{
					list.addGraphic(tempG);
					tempG=NULL;
					polyNum=0;
					polyEnd=false;
				}
			}

		}	
		Invalidate();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CGLFrmView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(CMainFrame::functionChoice==2)
	{
		exagrate=60;
		Invalidate();
	}
	CView::OnRButtonDown(nFlags, point);
}

BOOL CGLFrmView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(CMainFrame::functionChoice==0)
	{
		if(selectG!=NULL)
		{
			int xx;
			switch(TRR)
			{
			case 1://ƽ��
				xx=1-2*(zDelta>0?1:0);
				selectG->translate(2*xx,0);
				break;
			case 2://��ת
				selectG->rotate(zDelta);
				break;
			case 3://����
				selectG->rescale(zDelta,zDelta);
				break;
			}
			Invalidate();
		}

	}
	if(CMainFrame::functionChoice==2)
	{
		if(zDelta>0)
		{
			exagrate+=1;
			if(exagrate>90)
				exagrate=90;
		}
		else
		{
			exagrate-=1;
			if(exagrate<10)
				exagrate=10;
		}
		Invalidate();
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CGLFrmView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CView::OnMButtonUp(nFlags, point);
}


void CGLFrmView::keyRespond()
{
	if(CMainFrame::functionChoice==2)
	{
		if(w||up)
			viewer.forward_back(true);
		if(s||down)
			viewer.forward_back(false);
		if(a)
			viewer.left_right(true);
		if(d)
			viewer.left_right(false);
		if(left)
			viewer.horizontal(true);
		if(right)
			viewer.horizontal(false);
		if(pgup)
			viewer.vertical(true);
		if(pgdn)
			viewer.vertical(false);
		if(home)
			viewer.up_down(true);
		if(end)
			viewer.up_down(false);
		if(cursorCtrlEnable)
			viewer.cursorCtrl();
	}
}

//����
void CGLFrmView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	

	if(CMainFrame::functionChoice==2)
	{
		switch(nChar)
		{
		case 'W':
			w=true;
			Invalidate();
			break;
		case 'S':
			s=true;
			break;
		case 'A':
			a=true;
			break;
		case 'D':
			d=true;
			break;
		case VK_UP:
			up=true;
			break;
		case VK_DOWN:
			down=true;
			break;
		case VK_LEFT:
			left=true;
			break;
		case VK_RIGHT:
			right=true;
			break;
		case VK_HOME:
		    home=true;
			break;
		case VK_END:
			end=true;
			break;
		case VK_PRIOR:
			pgup=true;
			break;
		case VK_NEXT:
			pgdn=true;
			break;
		}
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGLFrmView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(CMainFrame::functionChoice==2)
	{
		switch(nChar)
		{
		case 'W':
			w=false;
			break;
		case 'S':
			s=false;
			break;
		case 'A':
			a=false;
			break;
		case 'D':
			d=false;
			break;
		case VK_UP:
			up=false;
			break;
		case VK_DOWN:
			down=false;
			break;
		case VK_LEFT:
			left=false;
			break;
		case VK_RIGHT:
			right=false;
			break;
		case VK_HOME:
		    home=false;
			break;
		case VK_END:
			end=false;
			break;
		case VK_PRIOR:
			pgup=false;
			break;
		case VK_NEXT:
			pgdn=false;
			break;
		}
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}



//�����Ĳ˵�
void CGLFrmView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	if(CMainFrame::functionChoice==0)
	{
		if(drawing)
			return;
		CMenu mainMenu;
		mainMenu.LoadMenuW(IDR_MENU2);
		CMenu*pSubMenu=mainMenu.GetSubMenu(0);
		if(fillOrNot)
		{
			pSubMenu->EnableMenuItem(ID_FILL_AGREE,MF_GRAYED);
			pSubMenu->EnableMenuItem(ID_FILL_REFUSE,MF_ENABLED);
		}
		else
		{
			pSubMenu->EnableMenuItem(ID_FILL_AGREE,MF_ENABLED);
			pSubMenu->EnableMenuItem(ID_FILL_REFUSE,MF_GRAYED);
		}
		pSubMenu->TrackPopupMenu (TPM_LEFTALIGN,point.x,point.y,pWnd);
	}

}

//ѡ��
void CGLFrmView::OnSelect()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=0;
}

//ͼ��
void CGLFrmView::OnPoint()
{
	// TODO: �ڴ���������������	
	CMainFrame::menuChoice=1;
}

void CGLFrmView::OnLine()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=2;
}

void CGLFrmView::OnCircle()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=3;
}

void CGLFrmView::OnPoly()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=4;
}

void CGLFrmView::OnRect()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=5;
}
//�ü�
void CGLFrmView::OnClip()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=6;
}
//Bezier����
void CGLFrmView::OnBezier()
{
	// TODO: �ڴ���������������
	CMainFrame::menuChoice=7;
}
//���
void CGLFrmView::OnFillAgree()
{
	// TODO: �ڴ���������������
	fillOrNot=true;
}

void CGLFrmView::OnFillRefuse()
{
	// TODO: �ڴ���������������
	fillOrNot=false;
}

//�任
void CGLFrmView::OnTranslate()
{
	// TODO: �ڴ���������������
	TRR=1;
}

void CGLFrmView::OnRotate()
{
	// TODO: �ڴ���������������
	TRR=2;
}

void CGLFrmView::OnRescale()
{
	// TODO: �ڴ���������������
	TRR=3;

}


//�༭
void CGLFrmView::OnGDel()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==0)
	{
		if(selectG!=NULL)
		{
			list.removeGraphic();
			Invalidate();
		}
	}

}

void CGLFrmView::OnEditCut()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==0)
	{
		if(selectG!=NULL)
		{
			if(clipBoard!=NULL)//��ռ��а�
			{
				delete clipBoard;
				clipBoard=NULL;
			}
			clipBoard=selectG->copy();
			list.removeGraphic();
			Invalidate();
		}
	}
	
}

void CGLFrmView::OnEditCopy()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==0)
	{ 
		if(selectG!=NULL)
		{
			if(clipBoard!=NULL)//��ռ��а�
			{
				delete clipBoard;
				clipBoard=NULL;
			}
			clipBoard=selectG->copy();
			Invalidate();
		}
	}


}


void CGLFrmView::OnEditPaste()
{
	// TODO: �ڴ���������������

	if(CMainFrame::functionChoice==0)
	{
		if(clipBoard!=NULL)
		{
			Graphic * another=clipBoard->copy();
			another->translate(5,5);
			list.addGraphic(another);
			Invalidate();
		}	
	}

}




//�ļ�����
void CGLFrmView::OnFileOpen()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==0)
	{
		CFileDialog fileDlg(TRUE);//ϵͳ�Դ��ĶԻ���
		fileDlg.m_ofn.lpstrTitle=L"��";
		fileDlg.m_ofn.lpstrFilter=L"ͼ��ϵͳ(*.gs)\0\0";
		fileDlg.m_ofn.lpstrDefExt=L"gs";//�Լ������ �ļ���ʽ
		if(IDOK==fileDlg.DoModal())//���ok��ʱ�� ִ���ļ���
		{
			this->finalize();
			this->initialize();
			CFile file(fileDlg.GetPathName(),CFile::modeRead);
			CArchive ar(&file,CArchive::load);
			ar>>this->list;
			Invalidate();
		}
	}
	
}

void CGLFrmView::OnFileSave()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==0)
	{
		CFileDialog fileDlg(FALSE);//���� �Ի���
		fileDlg.m_ofn.lpstrTitle= L"���Ϊ";//������
		fileDlg.m_ofn.lpstrFilter=L"ͼ��ϵͳ(*.gs)\0\0";
		fileDlg.m_ofn.lpstrDefExt=L"gs";//�����ļ���ʽ
		if(IDOK==fileDlg.DoModal())
		{
			CFile file(fileDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite|CFile::shareDenyNone);
			CArchive ar(&file,CArchive::store);
			ar<<this->list;
		}
	}

}

//��ʱ��
void CGLFrmView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(CMainFrame::functionChoice==1)
	{
		if(nIDEvent==11)
		{
			animationBall[0]->run();
			animationBall[1]->run();
			animationBall[2]->run();
			animationBall[3]->run();
			Invalidate();
		}
	}
	if(CMainFrame::functionChoice==2)
	{
		if(nIDEvent==12)
		{
			Invalidate();
		}
	}
	
	CView::OnTimer(nIDEvent);
}


//��ʱ�����ؿ�ݼ�
void CGLFrmView::OnTimerctrl()
{
	// TODO: �ڴ���������������
	if(CMainFrame::functionChoice==1)
	{
		if(go)
		{
			CWnd::SetTimer(11,10,NULL);
		}
		else
		{
			CWnd::KillTimer(11);
		}
		go=!go;
	}
	if(CMainFrame::functionChoice==2)
	{
		cursorCtrlEnable=!cursorCtrlEnable;
	}

}


void CGLFrmView::OnDraw2D()
{
	// TODO: �ڴ���������������
	CMainFrame::functionChoice=0;
	CWnd::KillTimer(12);
	Invalidate();
}

void CGLFrmView::OnAnimation2D()
{
	// TODO: �ڴ���������������
	CMainFrame::functionChoice=1;
	CWnd::KillTimer(12);
	Invalidate();
}

void CGLFrmView::OnRover3D()
{
	// TODO: �ڴ���������������
	CMainFrame::functionChoice=2;
	CWnd::SetTimer(12,10,NULL);
	Invalidate();
}

