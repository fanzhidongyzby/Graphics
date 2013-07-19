// GLFrmDoc.cpp : CGLFrmDoc 类的实现
//

#include "stdafx.h"
#include "GLFrm.h"

#include "GLFrmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLFrmDoc

IMPLEMENT_DYNCREATE(CGLFrmDoc, CDocument)

BEGIN_MESSAGE_MAP(CGLFrmDoc, CDocument)
END_MESSAGE_MAP()


// CGLFrmDoc 构造/析构

CGLFrmDoc::CGLFrmDoc()
{
	// TODO: 在此添加一次性构造代码	

}

CGLFrmDoc::~CGLFrmDoc()
{
}

BOOL CGLFrmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGLFrmDoc 序列化

void CGLFrmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGLFrmDoc 诊断

#ifdef _DEBUG
void CGLFrmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGLFrmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGLFrmDoc 命令

void CGLFrmDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: 在此添加专用代码和/或调用基类

	CDocument::SetTitle (L"GraphicSystem");
}
