// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "GLFrm.h"

#include "MainFrm.h"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//ON_WM_CREATE()
	ON_COMMAND(ID_HELP, &CMainFrame::OnHelp)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CMainFrame::functionChoice=0;
int CMainFrame::menuChoice=0;
// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	// TODO: �������Ҫ��������ͣ������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������




void CMainFrame::OnHelp()
{
	// TODO: �ڴ���������������
	CString helpInfo;
	helpInfo.Format(L"����˵��:\n\
�����������ܣ���ά��ͼ����ά��������ά���Σ�\n\
1:��ά��ͼ��\n\
  ����->��ά��ͼ�������ͼģʽ��\n\
  �Ҽ��˵��ӹ��ܣ�\n\
  a.ָ�룺\n\
    �϶�ͼ�Σ���굥��ͼ���϶�;һ��ѡ���ͼ��ü����ߣ���һֱ���ڸù��ߵ�״̬��ָ�빦�ܽ��˳����л�ͼ���ܺͲü����ܣ�\n\
  b.�㣺\n\
    �������ƣ�\n\
  c.�ߣ����Σ�Բ��\n\
    �϶�����;\n\
  d.����Σ�Bezier��\n\
    ������ͬ��λ�ã��γɶ���λ�Bezier���ߵĶ��㣬������һ���㣬�������ƣ�\n\
  e.��ά�任��\n\
    ѡ��ͬ�ı任��ʽ����ָ�빦��ѡ��ͼ�Σ����������֣�����ͼ�ν��м򵥼��α任��\n\
  f.��䣺\n\
    ���ø�����Ժ���Ƶķ��ͼ�λ�����䷽ʽ��ʾ��\n\
  g.�ü���\n\
    �϶���꣬ѡ��ü����򣬽���ѡ���ͼ�βü�����Ӱ����������ͼ�Σ�\n\
  �༭�˵��ӹ��ܣ�\n\
  ѡ��Ҫ������ͼ�Σ�ѡ���ƣ�ճ�������У�ɾ�������Ӧ�Ŀ�ݼ���ִ�б༭������\n\
  �ļ��˵��ӹ��ܣ�\n\
  ��ͼ��ɺ�ѡ�б��棬����ǰ��ͼ�α���Ϊ.gs��ʽ���ļ���ѡ�д򿪣�����ǰ������ļ���ѡ���˳����˳��ó���;\n\
2.��ά������\n\
  ����->��ά��ͼ�������ά����ģʽ��\n\
  �����ո����С����˶�����ͣ��\n\
3.��ά���Σ�\n\
  ����->��ά���Σ�������ά����ģʽ��\n\
  �ü��̻������Ƴ��������κͽ�����\n\
  ���ܼ����ܣ�\n\
  W,S,A,D��������ǰ������ƽ���ƶ�������ǰ�����������ˣ�������ת��������ת��Home��������End���½���PgUp�����ӣ�PgDn:���ӣ�\n\
  �ո񣺼������ֹ�����Ƴ��������֣����ų������һ������Ż�ԭ��\n");
	MessageBox(helpInfo,L"����");
}
