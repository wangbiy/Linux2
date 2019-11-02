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
* FileName:pthread.c
* Author  :Daisy
* Created :2019-11-02
* Purpose :
* ==============================================================================
*/
#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
void* rout(void* arg)
{
    while(1)
    {
        srand((unsigned long)time(NULL));
        printf("I am thread 1:%d\n",getpid());
        int time=rand()%10;
        sleep(1);
        int a=10/0;
    }
}
int main()
{
    pthread_t tid;
    int ret;
    pthread_create(&tid,NULL,rout,(void*)"thread 1");
    pthread_create(&tid,NULL,rout,(void*)"thread 2");
    pthread_create(&tid,NULL,rout,(void*)"thread 3");
    pthread_create(&tid,NULL,rout,(void*)"thread 4");
    pthread_create(&tid,NULL,rout,(void*)"thread 5");
    while(1)
    {
        printf("I am main thread:%d\n",getpid());
        sleep(1);
    }
    return 0;
}
