//#define N_EDGE 4
//typedef enum {Left,Right,Bottom,Top} Edge;
//struct dcPt 
//{
//	int x;
//	int y;
//};
//
//struct wcPt2
//{
//	int x;
//	int y;
//};


#include "math.h"

typedef struct
{
	float x,y;
}Vertex;

typedef Vertex Edge[2];
typedef Vertex VertexArray[100];


class SutherlandHodgeman
{
public:
	void Intersect(Vertex *s,Vertex *p,Edge  clipBoudary,Vertex *I)
	{/*�����εı�sp��ü��ߵĽ���I*/
		if(clipBoudary[0].y==clipBoudary[1].y) /*ˮƽ�ü���*/
		{
			I->y=clipBoudary[0].y;
			I->x=s->x+(clipBoudary[0].y-s->y)*(p->x-s->x)/(p->y-s->y);//����Ϊ0��ô����

		}
		else /*��ֱ�ü���*/
		{
			I->x=clipBoudary[0].x;
			I->y=s->y+(clipBoudary[0].x-s->x)*(p->y-s->y)/(p->x-s->x);
		}
	}

	bool Inside(Vertex *testVertex,Edge clipBoudary)//���ܿ�ȫ�ֵ��ڲ����ڲ���ֻ�Ǵ�ţ�ȫ���жϷ��ڲü�֮ǰ
	{ /*����testVertex��ü��ߵĹ�ϵ*/
		if(clipBoudary[1].x>clipBoudary[0].x) /*�±�*/
		{
			if(testVertex->y>=clipBoudary[0].y)
				return true;
		}
		else if(clipBoudary[1].x<clipBoudary[0].x)
		{
			if(testVertex->y<=clipBoudary[0].y)
				return true;
		}
		else if(clipBoudary[1].y>clipBoudary[0].y)
		{
			if(testVertex->x <=clipBoudary[0].x)
				return true;
		}
		else if(clipBoudary[1].y<clipBoudary[0].y)
		{
			if(testVertex->x>=clipBoudary[0].x)
				return true;
		}
		return false;

	}
	void Output(Vertex *newVertex,int *outLength,VertexArray outVertexArray)
	{
		/*��newVertex���뵽�������ζ����*/
		outVertexArray[*outLength].x=newVertex->x;
		outVertexArray[*outLength].y=newVertex->y;
		(*outLength)++;
	}

	void PolygonClip(int inLength,VertexArray  inVertexArray,
		int * outLength,VertexArray outVertexArray,Edge clipBoundary)
	{
		/*clipBoudaryΪ�ü���*/
		Vertex *s,*p,I;
		int j;
		*outLength=0;
		s=&(inVertexArray[inLength-1]);
		for(j=0;j<inLength;j++)
		{
			p=&(inVertexArray[j]);
			if(Inside(p,clipBoundary))
			{
				if(Inside(s,clipBoundary))
					Output(p,outLength,outVertexArray);
				else
				{
					Intersect(s,p,clipBoundary,&I);
					Output(&I,outLength,outVertexArray);
					Output(p,outLength,outVertexArray);
				}
			}
			else if(Inside(s,clipBoundary)) 
			{
				Intersect(s,p,clipBoundary,&I);
				Output(&I,outLength,outVertexArray);

			}
			s=p;
		}
	}
	
	

	//int inside(wcPt2 p,Edge b,dcPt wMin,dcPt wMax)//�жϵ�����λ��
	//{
	//	switch(b)
	//	{
	//	case Left: if(p.x<wMin.x) return (false);break;
	//	case Right: if(p.x>wMax.x) return (false);break;
	//	case Bottom: if(p.y<wMin.y) return (false);break;
	//	case Top: if(p.y>wMax.y) return (false);break; 
	//	}
	//	return (true);
	//}

	//int cross(wcPt2 p1,wcPt2 p2,Edge b,dcPt wMin,dcPt wMax)//�жϲû��ǲ���
	//{
	//	if(inside(p1,b,wMin,wMax)==inside(p2,b,wMin,wMax))
	//		return (false);
	//	else return (true);
	//}

	//wcPt2 intersect(wcPt2 p1,wcPt2 p2,Edge b,dcPt wMin,dcPt wMax)//���㽻��
	//{
	//	wcPt2 iPt;
	//	float m;
	//	float dx,dy;

	//	if(p1.x!=p2.x) 
	//	{
	//		dy=float(p1.y-p2.y);
	//		dx=float(p1.x-p2.x);
	//		m=dy/dx;
	//	}
	//	switch(b)
	//	{
	//	case Left:
	//		iPt.x=wMin.x;
	//		iPt.y=int(p2.y+(wMin.x-p2.x)*m);
	//		break;
	//	case Right:
	//		iPt.x=wMax.x;
	//		iPt.y=int(p2.y+(wMax.x-p2.x)*m);
	//		break;
	//	case Bottom:
	//		iPt.y=wMin.y;
	//		if(p1.x!=p2.x) iPt.x=int(p2.x+(wMin.y-p2.y)/m);
	//		else iPt.x=p2.x;
	//		break;
	//	case Top:
	//		iPt.y=wMax.y;
	//		if(p1.x!=p2.x) iPt.x=int(p2.x+(wMax.y-p2.y)/m);
	//		else iPt.x=p2.x;
	//		break;
	//	}
	//	return(iPt);
	//}

	//void clipPoint(wcPt2 p,Edge b,dcPt wMin,dcPt wMax,wcPt2 *pOut,int *cnt,wcPt2 *first[],wcPt2 *s)//�����ü��������������һ�ü��߻����ն����
	//{
	//	wcPt2 iPt;

	//	if(! first[b])
	//		first[b]=&p;
	//	else
	//		if(cross(p,s[b],b,wMin,wMax))
	//		{
	//			iPt=intersect(p,s[b],b,wMin,wMax);
	//			if(b<Top)
	//				clipPoint(iPt,Edge(b+1),wMin,wMax,pOut,cnt,first,s);
	//			else
	//			{
	//				pOut[*cnt]=iPt;
	//				(*cnt)++;
	//			}
	//		}
	//		s[b]=p;

	//		if(inside(p,b,wMin,wMax))
	//			if(b<Top)
	//				clipPoint(p,Edge(b+1),wMin,wMax,pOut,cnt,first,s);
	//			else
	//			{
	//				pOut[*cnt]=p;
	//				(*cnt)++;
	//			}
	//}

	//void closeClip(dcPt wMin,dcPt wMax,wcPt2 *pOut,int *cnt,wcPt2 *first[],wcPt2 *s)//��ɶ���βü�
	//{
	//	wcPt2 i;
	//	Edge b;

	//	for(b=Left;b<=Top;)
	//	{
	//		if(cross(s[b],*first[b],b,wMin,wMax))
	//		{
	//			i=intersect(s[b],*first[b],b,wMin,wMax);
	//			if(b<Top)
	//			{
	//				clipPoint(i,Edge(b+1),wMin,wMax,pOut,cnt,first,s);
	//			}
	//			else
	//			{
	//				pOut[*cnt]=i;
	//				(*cnt)++;
	//			}
	//		}
	//		b=Edge(b+1);
	//	}
	//}

	//int clipPolygon(dcPt wMin,dcPt wMax,int n,wcPt2 *pIn,wcPt2 *pOut)
	//{
	//	wcPt2 *first[N_EDGE]={0,0,0,0},s[N_EDGE];
	//	int i,cnt=0;

	//	for(i=0;i<n;i++)
	//		clipPoint(pIn[i],Left,wMin,wMax,pOut,&cnt,first,s);
	//	closeClip(wMin,wMax,pOut,&cnt,first,s);
	//	return (cnt);
	//}
};

