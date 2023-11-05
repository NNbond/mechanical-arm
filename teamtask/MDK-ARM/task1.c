#include "can.h"
#include "pid.h"
#include "dji_motor.h"
#include "usart.h"
#include "angle.h"
#include "pan.h"
#include "calculate_angle.h"
#include "bezier.h"
#include "math.h"


extern float theta[2];
extern float x,y,z,r;
extern float set_point[2][20];
extern float target1[20];
extern float target2[20];
#define Ball_D 150
#define Barrel_H 160

void Task1()
{
    //设定xyz
    x=0;
    y=0;
    z=0;
    
    r=sqrt(x*x+y*y);
    
    bezier(r,z);  //规划路径
    pan_angle(3,30);  //控制云台角度
    HAL_Delay(500);
    for(int i=0;i<60;i++)
    {
       calculate_angle(set_point[0][i],set_point[1][i]);//set_point是贝塞尔曲线上的点
       dji_angle(1,2,theta[0],theta[1]);//控制电机1,2的角度，从而控制机械臂
    }
    
    
    //抓取动作
    
    
    
    
    
    
    
}

/*
任务三的实现
*/
void task3(float x_ball,float y_ball)
{
    int angle_PTZ;
    angle_PTZ=(int)sort(x_ball/y_ball);
    Change_dji_loc(3,angle_PTZ);
    USART_printf("angle_PTZ=%d/n",angle_PTZ);
    float r=0;
    r=pow(x_ball,2)+pow(y_ball,2);
    bezier(pow(r,0.5),Ball_D);
    translate();
       for(int i=0;i<20;i++)
      {
          USART_printf("theta1=%f  ,theta2=%f",target1[i],target2[i]);
          dji_angle(1,2,target1[i],target2[i]);
          USART_printf("theta1_now=%f  ,theta2_now=%f",Get_dji_information(1).total_angle,Get_dji_information(2).total_angle);
      }
}


/*
任务四的实现
*/
void task4(float x_ball,float y_ball,float x_barrel,float y_barrel)
{
    int angle_PTZ;          
    angle_PTZ=(int)sort(x_ball/y_ball);     //云台转到抓球的角度
    Change_dji_loc(3,angle_PTZ);
    float r=0;
    r=pow(x_ball,2)+pow(y_ball,2);          //球到原点距离
    bezier(pow(r,0.5),Ball_D);
    translate();
    for(int i=0;i<20;i++)                   //抓球
      {
          dji_angle(1,2,target1[i],target2[i]);
      }
    angle_PTZ=(int)sort(x_barrel/y_barrel)-(int)sort(x_ball/y_ball);
      Change_dji_loc(3,angle_PTZ);
      r=pow(x_barrel,2)+pow(y_barrel,2);        //桶到原点距离
      bezier(pow(r,0.5),Barrel_H);
      translate();
      for(int i=0;i<20;i++)                   //放球
      {
          dji_angle(1,2,target1[i],target2[i]);
      }
}
