/*
               #########                       
               #########                       
              ############                     
              #############                    
             ##  ###########                   
            ###  ###### #####                  
            ### #######   ####                 
           ###  ########## ####                
          ####  ########### ####               
        ####   ###########  #####              
       #####   ### ########   #####            
      #####   ###   ########   ######          
     ######   ###  ###########   ######        
    ######   #### ##############  ######       
   #######  #####################  ######      
   #######  ######################  ######     
  #######  ###### #################  ######    
  #######  ###### ###### #########   ######    
  #######    ##  ######   ######     ######    
  #######        ######    #####     #####     
   ######        #####     #####     ####      
    #####        ####      #####     ###       
     #####       ###        ###      #         
       ###       ###        ###                
        ##       ###        ###                
_________#_______####_______####______________ 
               我们的未来没有BUG               
* ==============================================================================
* FileName:ticket.c
* Author  :Daisy
* Created :2019-11-06
* Purpose :
* ==============================================================================
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>
int tickets=200;
pthread_mutex_t lock;//创建锁
void *GetTicket(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        if(tickets>0)//说明有票
        {
            usleep(100000);//以微秒来睡眠
            printf(" get a ticket no is : %d\n",tickets--);
            pthread_mutex_unlock(&lock);//解锁
        }
        else
        {
            printf("%s............quit\n",(char*)arg);
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    pthread_exit((void*)0);
}
int main()
{
    pthread_mutex_init(&lock,NULL);//初始化互斥量
    pthread_t tid1,tid2,tid3,tid4;
    pthread_create(&tid1,NULL,GetTicket,"thread 1");
    pthread_create(&tid1,NULL,GetTicket,"thread 2");
    pthread_create(&tid1,NULL,GetTicket,"thread 3");
    pthread_create(&tid1,NULL,GetTicket,"thread 4");

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    pthread_mutex_destroy(&lock);//销毁互斥量
}
