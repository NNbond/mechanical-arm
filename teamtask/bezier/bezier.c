#include "math.h"
#include "main.h"
#include "calculate_angle.h"

float set_point[2][20];
extern float target1[20],target2[20];
extern float theta[2];


void bezier(float x,float y)
{
    int i=0;
    float t=0;
    float xt1=0,yt1=0,xt2=0,yt2=0;        //中间迭代点坐标
    float x0=0,y0=0;        //起始点坐标
    float x_control=0,y_control=0;
    x_control=(x+x0)/2;
    y_control=y0;
    for(i=0;i<20;i++)
    {
        xt1=t*x0+(1-t)*x_control;
        yt1=t*x0+(1-t)*y_control;
        xt2=t*x_control+(1-t)*x;
        yt2=t*y_control+(1-t)*y;
        set_point[0][i]=t*xt1+(1-t)*xt2;
        set_point[1][i]=t*yt1+(1-t)*yt2;
        t=t+0.05;
    }
}    

void translate()
{
    for (int i=0;i<20;i++)
    {
        calculate_angle(set_point[0][i],set_point[1][i]);
        target1[i]=theta[0];
        target2[i]=theta[1];
    }
}