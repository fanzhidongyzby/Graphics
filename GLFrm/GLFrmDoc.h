// GLFrmDoc.h : CGLFrmDoc ��Ľӿ�
//


#pragma once


class CGLFrmDoc : public CDocument
{
protected: // �������л�����
	CGLFrmDoc();
	DECLARE_DYNCREATE(CGLFrmDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGLFrmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};


