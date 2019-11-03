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
* FileName:mythread.c
* Author  :Daisy
* Created :2019-11-03
* Purpose :
* ==============================================================================
*/
#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//pthread_t main_id;
void* thread_run(void* arg)
{
//    pthread_detach(pthread_self());//线程分离
    int count=5;
    while(count--)
    {
        printf("I am a new thread,tid is %p\n",pthread_self());//pthread_self用来获取当前线程的线程ID
        sleep(1);
       // pthread_cancel(pthread_self());//取消当前线程，但是一般不这么做
  //     int ret=pthread_cancel(main_id);//能不能让新线程取消主线程
    //   printf("ret:%d,string:%s\n",ret,strerror(ret));//使用ret获得返回码，使用strerror打印错误信息
    }
   // pthread_exit((void*)111);
}

int main()
{
    //main_id=pthread_self();//获取主线程ID
    pthread_t tid;
    int num=1;
    pthread_create(&tid,NULL,thread_run,(void*)&num);
    pthread_detach(tid);//由主线程分离新线程
  //  sleep(1);
//    pthread_cancel(tid);//取消新线程
    printf("main thread get a new thread tid:%p\n",tid);
   // void *ret;
   int ret= pthread_join(tid,NULL);
    printf("ret:%d,%s\n",ret,strerror(ret));
    return 0;

}
