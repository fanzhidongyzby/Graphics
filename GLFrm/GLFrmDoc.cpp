// GLFrmDoc.cpp : CGLFrmDoc ���ʵ��
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


// CGLFrmDoc ����/����

CGLFrmDoc::CGLFrmDoc()
{
	// TODO: �ڴ����һ���Թ������	

}

CGLFrmDoc::~CGLFrmDoc()
{
}

BOOL CGLFrmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGLFrmDoc ���л�

void CGLFrmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGLFrmDoc ���

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


// CGLFrmDoc ����

void CGLFrmDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���

	CDocument::SetTitle (L"GraphicSystem");
}
