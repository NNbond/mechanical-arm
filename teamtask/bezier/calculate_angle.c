#include "math.h"
#include "main.h"
#include "get_abs.h"
#define ARRAY_SIZE 60

float theta[2];
float  l1=0,l2=0;

extern float data[ARRAY_SIZE];


//������sort
//�������ã�ͨ���������atan(x)
//xΪ����ͨ�����ת����ֵ

float sort(float x)
{
    float t=0;
    int i=0;
    int aim_subscript=0;    //���ؽǱ�
    if(x<=1)
    {
        t=x/0.02;
        for(i=0;i<50;i++)
        {
            if(get_abs(t-i)<get_abs(t-aim_subscript))
            {
                aim_subscript=i;
            }
        }
        return data[i];
    }
    else
    {
        t=(x-0.5)/0.01;
        aim_subscript=50;
        for(i=50;i<ARRAY_SIZE;i++)
        {
            if(get_abs(t-i)<get_abs(t-aim_subscript))
            {
                aim_subscript=i;
            }
        }
        return data[i];
    }
}


//calculate_angle���ã�(x,y)Ϊƽ���ϸ���һ�㣬�ú�����������ʹ�����˵㵽��(x,y)�������ת���ĽǶ� 
void calculate_angle(float x,float y)//x,yΪ�������
{
    float a1=0,a2=0,a3=0,a4=0,a5=0;
    float value1=0,value2=0;
    a1=pow(x,2)+2*x*l2+pow(y,2)-pow(l1,2)+pow(l2,2);
    a2=pow(x,2)+2*x*l1+pow(y,2)+pow(l1,2)-pow(l2,2);
    a5=pow(((-pow(x,2)-pow(y,2)+pow(l1,2)+2*l1*l2+pow(l2,2))*(pow(x,2)+pow(y,2)-pow(l1,2)+2*l1*l2)-pow(l2,2)),0.5);
    a3=2*y*l2-a5;
    a4=2*y*l2+a5;

    value1=pow(x,2)*a4/a1-2*y*l1+pow(y,2)*a4/a1-pow(l1,2)*a4/a1+pow(l2,2)*a4/a1+2*x*l2*a4/a1;
    value2=(2*y*l2+a1)/(pow(x,2)+2*x*l2+pow(y,2)-l1*l1+l2*l2);
    theta[0]=-2*sort(value1);
    theta[1]=2*sort(value2);

}