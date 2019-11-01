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
 * FileName:SIGCHLD.cpp
 * Author  :Daisy
 * Created :2019-11-01
 * Purpose :进行SIGCHLD信号的应用
 * ==============================================================================
 */
#include<iostream>
using namespace std;
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void handler(int signo)
{
    pid_t id;
    while((id=waitpid(-1,NULL,WNOHANG))>0)
    {
        cout<<"wait child sucess!"<<id<<endl;
    }
    cout<<"child is quit!"<<getpid()<<endl;
    //   cout<<"pid is"<<getpid()<<endl;
    //   cout<<" signo is"<<signo<<endl;
}
int main()
{
    signal(SIGCHLD,handler);
    pid_t id=fork();
    if(id==0)//child
    {
        cout<<"child id"<<getpid()<<endl;
        sleep(3);
        exit(1);
    }
    while(1)
    {
        cout<<"father is doing some thing"<<endl;
        sleep(1);
    }
    return 0;
}
