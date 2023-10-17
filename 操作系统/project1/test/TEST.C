#include "includes.h"
#define  TASK_STK_SIZE   512            
OS_STK   MyTaskStk[TASK_STK_SIZE];       
OS_STK   YouTaskStk[TASK_STK_SIZE];
INT16S   key;                    
INT8U    x=0,y=0;               
void MyTask(void * data);
void YouTask(void * data);
void  main (void)
{
    char* s_M2="LIUHAORUI";              
    char* s_M1="22001010705";
    OSInit();                   
    PC_DOSSaveReturn();             
    PC_VectSet(uCOS, OSCtxSw);          
    OSTaskCreate(MyTask,            
        s_M1,              
        &MyTaskStk[TASK_STK_SIZE - 1],
        1);            
    OSTaskCreate(YouTask,           
        s_M2,             
        &YouTaskStk[TASK_STK_SIZE - 1],
        2);             
    OSStart();                  
}
void  MyTask (void *pdata)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif
    pdata = pdata; 
    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);    
    PC_SetTickRate(OS_TICKS_PER_SEC);   
    OS_EXIT_CRITICAL();
    OSStatInit();           
    for (;;) 
    {        
        if (x>1)
        {   x=0;
           y+=1; 
        }
        PC_DispStr(x,y,pdata,DISP_BGND_BLACK+DISP_FGND_YELLOW);
        y += 1;
         if (PC_GetKey(&key) == TRUE) {
         if (key == 0x1B) {     
         PC_DOSReturn();      
            }
        }
        OSTimeDlyHMSM(0, 0, 3, 0);  
    }
}
void  YouTask (void *pdata)
{
#if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
#endif
    pdata = pdata; 
    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);    
    PC_SetTickRate(OS_TICKS_PER_SEC);   
    OS_EXIT_CRITICAL();
    OSStatInit();           
    for (;;) 
    {        
        PC_DispStr(x,y,pdata,DISP_BGND_BLACK+DISP_FGND_YELLOW);
        y += 1; 
         if (PC_GetKey(&key) == TRUE) {
         if (key == 0x1B) {    
         PC_DOSReturn();      
            }
        }
        OSTimeDlyHMSM(0, 0, 1, 0);  
    }
}
