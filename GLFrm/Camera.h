#pragma once
#define DEFAULT_SPEED 1
#define DEFUALT_ROTATE_SPEED 1
#define DEFAULT_ELEV_SPEED 1
class Camera  
{	
public:
	double	 g_eye[3];		//�ӵ�
	double	 g_look[3];		//����


	double      speed;           //����
	double      rotateSpeed;    //ת�Ƿ���
	double		elevSpeed;			//

	double		g_Angle;		//����ת�ܽǶ�(�Ƕ�Ϊ��λ)
	double      g_elev;         //�����ܷ���(����Ϊ��λ)
	
public:
	Camera();	
	virtual ~Camera();
	void  lookAt();

	void  forward_back(bool cmd);//ǰ���ƶ�
	void  left_right(bool cmd);//�����ƶ�
	void  up_down(bool cmd);//�����ƶ�

	void  horizontal(bool cmd);//ˮƽת��
	void  vertical(bool cmd);//��ֱת��

	void  cursorCtrl();//������
	
};
