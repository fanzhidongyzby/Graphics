#pragma once
#define DEFAULT_SPEED 1
#define DEFUALT_ROTATE_SPEED 1
#define DEFAULT_ELEV_SPEED 1
class Camera  
{	
public:
	double	 g_eye[3];		//视点
	double	 g_look[3];		//焦点


	double      speed;           //步长
	double      rotateSpeed;    //转角幅度
	double		elevSpeed;			//

	double		g_Angle;		//左右转总角度(角度为单位)
	double      g_elev;         //仰俯总幅度(距离为单位)
	
public:
	Camera();	
	virtual ~Camera();
	void  lookAt();

	void  forward_back(bool cmd);//前后移动
	void  left_right(bool cmd);//左右移动
	void  up_down(bool cmd);//上下移动

	void  horizontal(bool cmd);//水平转向
	void  vertical(bool cmd);//垂直转向

	void  cursorCtrl();//鼠标控制
	
};
