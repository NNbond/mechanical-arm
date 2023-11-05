#include "dji_motor.h"
#include "main.h"
#include "can_database.h"
#include "can.h"
#include "pid.h"
#include "basic.h"
#include "usart.h"

extern float target_angle1,target_angle2;
extern float target1[20],target2[20];
//3508电流范围   -16384-16384
//2006电流范围   -10000-10000

/**************内部宏定义与重命名begin**************/

//#define ALL_Send_Flag //收到所有电机报文后发送一条报文的标志

/**************内部宏定义与重命名end**************/

/**************内部变量与函数begin**************/
static int set_spd_s[8]={0,0,0,0,0,0,0,0};
static int set_loc_s[8]={0,0,0,0,0,0,0,0};
static int mode_s[8]={	LOC_MODE,
												LOC_MODE,
												LOC_MODE,
												LOC_MODE,
												LOC_MODE,
												LOC_MODE,
												LOC_MODE,
												LOC_MODE  };
static motor_measure_t motor_inf[8]={0};/*3508电机参数*/
static void Get_total_angle(motor_measure_t *p);
static void Can_cmd_first_four_motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
static void Can_cmd_last_four_motor(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8);
/**************内部变量与函数end**************/


/**************外部接口begin**************/
void Dji_motor_control(CAN_RxHeaderTypeDef rx_header,uint8_t rx_data[8]);
void Change_dji_speed(int motor_id,int target_spd);
void Change_dji_loc(int motor_id,int target_loc);
motor_measure_t Get_dji_information(int motor_id);
/**************外部接口end**************/

void dji_angle(){
    for(int i=0;i<20;i++)
              {
                  target_angle1=target1[i]/360*8192;
                  target_angle2=target2[i]/360*8192;//换算角度
                  Change_dji_loc(1,target_angle1);
                  Change_dji_loc(2,target_angle2);//转动电机
                  motor_inf[1]= Get_dji_information(1);
                  motor_inf[2]= Get_dji_information(2);//
                  if (-80<(motor_inf[1].total_angle-target_angle1)&&(motor_inf[1].total_angle-target_angle1)<80&&-80<(motor_inf[2].total_angle-target_angle1)&&(motor_inf[2].total_angle-target_angle1)<80)
                  {
                      break;//检测误差
                  }
                  else
                  {
                      USART_printf("error!");
                  }
              }
}