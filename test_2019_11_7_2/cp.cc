#include <iostream>
#include <pthread.h>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
class BlockQueue
{
    private:
        queue<int> q;
        int cap;//容量
        pthread_mutex_t lock;
        pthread_cond_t c_cond;//消费者条件变量，使用条件变量来判断是空还是满
        pthread_cond_t p_cond;//生产者条件变量
    private:
        void LockQueue()
        {
            pthread_mutex_lock(&lock);
        }
        void UnlockQueue()
        {
            pthread_mutex_unlock(&lock);
        }
        void ProducterWait()
        {
            cout<<"Producter wait"<<endl;
            pthread_cond_wait(&p_cond,&lock);
        }
        void ConsumerWait()
        {
            cout<<"Consumer wait"<<endl;
            pthread_cond_wait(&c_cond,&lock);
        }
        void SignalProducter()
        {
            cout<<"signal producter"<<endl;
            pthread_cond_signal(&p_cond);
        }
        void SignalConsumer()
        {
            cout<<"signal consumer"<<endl;
            pthread_cond_signal(&c_cond);
        }
        bool QueueIsFull()
        {
            return (q.size()==cap ? true:false);
        }
        bool QueueIsEmpty()
        {
            return (q.size()==0 ? true:false);
        }
    public:
        BlockQueue(int _cap =32)//构造函数
            :cap(_cap)
        {
            pthread_mutex_init(&lock,NULL);
            pthread_cond_init(&c_cond,NULL);
            pthread_cond_init(&p_cond,NULL);
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&c_cond);
            pthread_cond_destroy(&p_cond);
        }
        void PushData(const int& data)//生产者
        {
            LockQueue();//进行锁住
            if(QueueIsFull())//如果队列满，通知消费者，生产者进行等待
            {
                cout<<"queue is full"<<endl;
                SignalConsumer();
                ProducterWait();
            }
            q.push(data);//生产
            UnlockQueue();//解锁
        }
        void PopData(int &out)//消费者
        {
            LockQueue();
            if(QueueIsEmpty())
            {
                cout<<"queue is empty"<<endl;
                SignalProducter();
                ConsumerWait();
            }
            out=q.front();
            q.pop();
            UnlockQueue();
        }
};
void* Consumer(void* arg)
{
    int data;
    BlockQueue* bq=(BlockQueue*)arg;
    while(1)
    {
        bq->PopData(data);
        cout<<"consum data is :"<<data<<endl;
        sleep(1);//消费者慢
    }
}
void* Producter(void* arg)
{
    BlockQueue* bq=(BlockQueue*)arg;
    while(1)
    {
        int data=rand()%100+1;

        bq->PushData(data);
        cout<<"product data is :"<<data<<endl;
        //sleep(1);//生产的慢一点
    }
}
int main()
{
    srand((unsigned long)time(NULL));
    BlockQueue *bq=new BlockQueue(4);
    pthread_t c,p;

    pthread_create(&p,NULL,Producter,(void*)bq);
    pthread_create(&c,NULL,Consumer,(void*)bq);

    pthread_join(p,NULL);
    pthread_join(c,NULL);
    delete bq;
}
