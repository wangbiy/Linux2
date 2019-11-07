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
* FileName:test.cpp
* Author  :Daisy
* Created :2019-11-07
* Purpose :实现条件变量函数
* ==============================================================================
*/
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t lock;
pthread_cond_t cond;
void *Wait(void* arg)
{
    while(1)
    {
        pthread_cond_wait(&cond,&lock);//没有被唤醒，就阻塞
        printf("active.......");
    }
}
void *Signal(void* arg)
{
    pthread_cond_signal(&cond);//唤醒等待，通知在该条件变量下等待的线程
    sleep(1);
}
int main()
{    
    pthread_t t1,t2;
    pthread_cond_init(&cond,NULL);//初始化条件变量
    pthread_mutex_init(&lock,NULL);//初始化互斥量;
    pthread_create(&t1,NULL,Wait,NULL);
    pthread_create(&t2,NULL,Signal,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}
