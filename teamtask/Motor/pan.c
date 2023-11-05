#include "dji_motor.h"
#include "can_database.h"
#include "can.h"
#include "pid.h"
#include "basic.h"
#include "usart.h"

float target_angle3;
//3508������Χ   -16384-16384
//2006������Χ   -10000-10000

/**************�ڲ��궨����������begin**************/

//#define ALL_Send_Flag //�յ����е�����ĺ���һ�����ĵı�־

/**************�ڲ��궨����������end**************/

/**************�ڲ������뺯��begin**************/
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
static motor_measure_t motor_inf[8]={0};/*3508�������*/
static void Get_total_angle(motor_measure_t *p);
static void Can_cmd_first_four_motor(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
static void Can_cmd_last_four_motor(int16_t motor5, int16_t motor6, int16_t motor7, int16_t motor8);
/**************�ڲ������뺯��end**************/


/**************�ⲿ�ӿ�begin**************/
void Dji_motor_control(CAN_RxHeaderTypeDef rx_header,uint8_t rx_data[8]);
void Change_dji_speed(int motor_id,int target_spd);
void Change_dji_loc(int motor_id,int target_loc);
motor_measure_t Get_dji_information(int motor_id);
/**************�ⲿ�ӿ�end**************/


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