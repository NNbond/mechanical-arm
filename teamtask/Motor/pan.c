#include "dji_motor.h"
#include "can_database.h"
#include "can.h"
#include "pid.h"
#include "basic.h"
#include "usart.h"

float target_angle3;
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


void pan_angle(int motor_id_3, float target3)
{
    while (1)
    {
    target_angle3=(target3*80/20)/360*8192;
    Change_dji_loc(3,target_angle3);
    motor_inf[2]= Get_dji_information(2);//
    if (-80<(motor_inf[3].total_angle-target_angle3)&&(motor_inf[3].total_angle-target_angle3)<80)
        {
            break;
        }
    else
        {
             USART_printf("pan error!");
        }
     }
}