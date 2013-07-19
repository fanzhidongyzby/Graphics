// MainFrm.cpp : CMainFrame 类的实现
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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CMainFrame::functionChoice=0;
int CMainFrame::menuChoice=0;
// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	
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
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return TRUE;
}


// CMainFrame 诊断

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


// CMainFrame 消息处理程序




void CMainFrame::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
	CString helpInfo;
	helpInfo.Format(L"操作说明:\n\
本程序共三大功能：二维绘图，二维动画，三维漫游；\n\
1:二维绘图：\n\
  功能->二维绘图，进入绘图模式。\n\
  右键菜单子功能：\n\
  a.指针：\n\
    拖动图形，鼠标单击图形拖动;一旦选择绘图活裁剪工具，就一直处于该工具的状态，指针功能将退出所有绘图功能和裁剪功能；\n\
  b.点：\n\
    单击绘制；\n\
  c.线，矩形，圆：\n\
    拖动绘制;\n\
  d.多边形，Bezier：\n\
    单击不同的位置，形成多边形或Bezier曲线的顶点，单击第一个点，结束绘制；\n\
  e.二维变换：\n\
    选择不同的变换方式后，用指针功能选择图形，滚动鼠标滚轮，操作图形进行简单几何变换；\n\
  f.填充：\n\
    设置该项后，以后绘制的封闭图形会以填充方式显示；\n\
  g.裁剪：\n\
    拖动鼠标，选择裁剪区域，将被选择的图形裁剪，不影响矩形以外的图形；\n\
  编辑菜单子功能：\n\
  选中要操作的图形，选择复制，粘贴，剪切，删除，或对应的快捷键，执行编辑操作；\n\
  文件菜单子功能：\n\
  绘图完成后，选中保存，将当前的图形保存为.gs格式的文件；选中打开，打开以前保存的文件；选中退出，退出该程序;\n\
2.二维动画：\n\
  功能->二维绘图，进入二维动画模式；\n\
  单击空格控制小球的运动的暂停；\n\
3.三维漫游：\n\
  功能->三维漫游，进入三维漫游模式；\n\
  用键盘或鼠标控制场景的漫游和交互；\n\
  功能键介绍：\n\
  W,S,A,D控制人物前后左右平行移动，↑：前进；↓：后退；←：左转；→：右转；Home：上升；End：下降；PgUp：仰视；PgDn:俯视；\n\
  空格：激活或抑止鼠标控制场景；滚轮：缩放场景；右击：缩放还原；\n");
	MessageBox(helpInfo,L"帮助");
}
