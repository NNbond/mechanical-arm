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
    //�趨xyz
    x=0;
    y=0;
    z=0;
    
    r=sqrt(x*x+y*y);
    
    bezier(r,z);  //�滮·��
    pan_angle(3,30);  //������̨�Ƕ�
    HAL_Delay(500);
    for(int i=0;i<60;i++)
    {
       calculate_angle(set_point[0][i],set_point[1][i]);//set_point�Ǳ����������ϵĵ�
       dji_angle(1,2,theta[0],theta[1]);//���Ƶ��1,2�ĽǶȣ��Ӷ����ƻ�е��
    }
    
    
    //ץȡ����
    
    
    
    
    
    
    
}

/*
��������ʵ��
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
�����ĵ�ʵ��
*/
void task4(float x_ball,float y_ball,float x_barrel,float y_barrel)
{
    int angle_PTZ;          
    angle_PTZ=(int)sort(x_ball/y_ball);     //��̨ת��ץ��ĽǶ�
    Change_dji_loc(3,angle_PTZ);
    float r=0;
    r=pow(x_ball,2)+pow(y_ball,2);          //��ԭ�����
    bezier(pow(r,0.5),Ball_D);
    translate();
    for(int i=0;i<20;i++)                   //ץ��
      {
          dji_angle(1,2,target1[i],target2[i]);
      }
    angle_PTZ=(int)sort(x_barrel/y_barrel)-(int)sort(x_ball/y_ball);
      Change_dji_loc(3,angle_PTZ);
      r=pow(x_barrel,2)+pow(y_barrel,2);        //Ͱ��ԭ�����
      bezier(pow(r,0.5),Barrel_H);
      translate();
      for(int i=0;i<20;i++)                   //����
      {
          dji_angle(1,2,target1[i],target2[i]);
      }
}
