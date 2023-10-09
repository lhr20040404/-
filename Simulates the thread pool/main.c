/*

线程池依据不同的业务场景有不同的设计方式。
本节实践课程是在大家还未学习操作系统多线程概念的情况下，以最小必要数据结构来进行简单模拟。
1.运行状态线程监控表：
我们为运行的线程模拟一个运行状态线程监控表（我们用简单的数组来模拟，然而实际上linux内核里应该是一个双链表list_head或者散列表hlist_head）
2.线程池：
使用循环队列模拟，
等待状态的线程入队。遇到新任务使用等待状态线程，则出队变成运行状态的线程。任务运行结束后，线程入队。
3. 任务等待队列
使用链式队列模拟 。当新来任务发现 线程池内已经没有等待状态线程了，就进入任务等待队列

流程：
模拟创建线程监控表thread_info 并启动 CorePoolMaxSize个线程
定义循环队列 采用顺序队列实现
初始化循环队列，线程进入循环队列 ,均处于等待状态 线程 ，
pid模拟系统指定为28007 28008 28009 28010完成构建线程池
定义任务等待队列 采用链式队列实现

循环读取任务数据 格式：任务字符串 持续单位时间（可以键盘输入，也可以是读文件），
假设每读取一行数据 系统过了一个单位时间。
判断新任务是否能获取线程池中的等待线程，如果可以使用线程


*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int CorePoolMaxSize = 4;//线程池内最大线程数量
const int WaitQueueMaxSize = 8;//等待任务队列的最大任务上限
enum Thread_State //线程状态枚举，简化版假设只有两种状态。
{
    TASK_RUNNING = 1, //执行状态
    TASK_INTERRUPTIBLE = 2, //等待状态
};

typedef struct task_info //任务信息
{
    char url[100];//请求随便写写就行 比如t1,t2,t3,t4,t5等等
    int lifecycle;//我们模拟用的这个任务所需要的执行单位时间（比如1毫秒，1微秒等等）
} Task_Info;

typedef struct thread_task_struct //线程描述符 描述一个线程
{
    int state;//线程状态  简化版假设只有两种状态。TASK_RUNNING TASK_INTERRUPTIBLE
    int pid;//线程号
    Task_Info *task;//任务结构体类型指针
} Thread_Task_Struct;

typedef struct thread_pool_cycle //线程池 顺序队列
{
    unsigned front, rear;//队头和队尾
    unsigned size;//循环队列里当前元素个数
    unsigned capacity;//当前已分配存储单元个数
    struct thread_task_struct **array;//指向存储单元的指针 ,这里选择保存线程信息的地址而不是下标是因为真正实现时不是数组而是链表。
} Queue_Thread_Pool_Cycle;

typedef struct N //链式队列节点
{
    Task_Info *data;//任务结构体类型指针
    struct N *next;
} Node;
typedef struct //链式队列管理结构体类型
{
    Node *head, *tail;
    unsigned size;
} Wait_Queue_Struct;

/////////////////循环队列代码区  start //////////////////////////
int init_qtpc(Queue_Thread_Pool_Cycle *p) {
    p->front = p->rear = p->size = 0;
    p->capacity = CorePoolMaxSize;
    p->array = (Thread_Task_Struct **) malloc(sizeof(Thread_Task_Struct *) * p->capacity);
    if (NULL == p->array) return -1;
    return 0;
}

int destroy_qtpc(Queue_Thread_Pool_Cycle *p) {
    free(p->array);
    return 0;
}

int is_empty_qtpc(Queue_Thread_Pool_Cycle *p) {
    return p->size == 0;
}

int is_full_qtpc(Queue_Thread_Pool_Cycle *p) {
    return p->capacity == p->size;
}

//入队操作
int push_qtpc(Queue_Thread_Pool_Cycle *p, Thread_Task_Struct *pthread_info) {
p->array[p->rear]=pthread_info;
p->rear=(p->rear+1)%p->capacity;
++p->size;
return (int) p;
}

//出队操作
int pop_qtpc(Queue_Thread_Pool_Cycle *p) {
if(p->size==0)
    return (int) NULL;
p->front=(p->front+1)%p->capacity;
--p->size;
    return (int) p;
}

//读取队头元素操作
Thread_Task_Struct *front_q(const Queue_Thread_Pool_Cycle *p) {
/*-------------你来完成---------------
	a.返回front位置元素
*/
if(p->size==0)
    return  NULL;
return p->array[p->front];
}
/////////////////循环队列代码区  end //////////////////////////


/////////////////任务等待队列代码区 start //////////////////////////
int init_work_queue(Wait_Queue_Struct *lp) {
    lp->head = lp->tail = NULL;
    lp->size = 0;
    return 0;

}

Node *make_node(Task_Info *d) {
    Node *np = (Node *) malloc(sizeof(Node));
    if (!np)
        return NULL;
    np->data = d;
    np->next = NULL;
    return np;
}

int push_work_queue(Wait_Queue_Struct *lp, Task_Info *d) {
Node *new_node= make_node(d);
if(!new_node)
    return (int) NULL;
if(lp->tail)
    lp->tail->next=new_node;
else
    lp->head=new_node;
lp->tail=new_node;
++lp->size;
    return (int) lp;
}

int pop_work_queue(Wait_Queue_Struct *lp, Task_Info **pp) {
    if (lp->size==0)
    return (int) NULL;
    Node * del =lp->head;
    lp-> head= del->next;
    free(del);
    --lp ->size;
    if(lp->size==0)
    lp->tail=(void * )0;
    return (int) lp;
}

int print_work_queue(const Wait_Queue_Struct *lp) {
    Node *cur = lp->head;
    if (cur) {
        printf("当前任务等待队列排队个数%d，详情%s", lp->size, cur->data->url);
        cur = cur->next;
        while (cur) {
            printf("->%s", cur->data->url);
            cur = cur->next;
        }
        printf("\n");
    } else
        printf("当前任务等待队列排队个数0\n");
}

/////////////////任务等待队列代码区 end //////////////////////////


int show_state(Thread_Task_Struct *thin, Wait_Queue_Struct *lp) {
    printf("|  pid  | 状态 | 剩余时间 | 任务名 |\n");
    for (int i = 0; i < CorePoolMaxSize; ++i) {
        printf("| %d |", thin[i].pid);
        if (thin[i].state == TASK_RUNNING) {
            printf(" 运行 | %7ds |  %s |\n", thin[i].task->lifecycle, thin[i].task->url);
        } else if (thin[i].state == TASK_INTERRUPTIBLE) {
            printf(" 等待 |       0s |  null  |\n");
        }
    }
    printf("------------\n");
    print_work_queue(lp);

}

int update_time(Thread_Task_Struct *thin, Queue_Thread_Pool_Cycle *p, Wait_Queue_Struct *lp) {

    printf("又流逝了1个单位时间\n");

    for (int i = 0; i < CorePoolMaxSize; ++i) {
        if (thin[i].state == TASK_RUNNING) {
            thin[i].task->lifecycle--;
            if (0 == thin[i].task->lifecycle) {
                thin[i].state = TASK_INTERRUPTIBLE;
                free(thin[i].task);
                thin[i].task = NULL;

                if (!is_full_qtpc(p))
                    push_qtpc(p, thin + i);
            }
        }
    }

}

int main() {
    {
        system("chcp 65001");
        //模拟创建线程监控表thread_info 并启动 CorePoolMaxSize个线程
        Thread_Task_Struct thread_info[CorePoolMaxSize];
        for (int i = 0; i < CorePoolMaxSize; ++i) {
            thread_info[i].pid = 28007 + i;
            thread_info[i].state = TASK_INTERRUPTIBLE;
            thread_info[i].task = NULL;
        }
        //定义循环队列 采用顺序队列实现
        Queue_Thread_Pool_Cycle qtpc;
        //初始化循环队列，线程进入循环队列 ,完成构建线程池
        init_qtpc(&qtpc);
        for (int i = 0; i < CorePoolMaxSize; ++i) {
            if (!is_full_qtpc(&qtpc))
                push_qtpc(&qtpc, thread_info + i);
        }
        //定义任务等待队列 采用链式队列实现
        Wait_Queue_Struct workq;
        init_work_queue(&workq);
        show_state(thread_info, &workq);
        //读取任务
        Task_Info *p_task_info;
        Thread_Task_Struct *cur_thread;
        while (1) {
            p_task_info = (Task_Info *) malloc(sizeof(Task_Info));
            scanf("%s%d", p_task_info->url, &p_task_info->lifecycle);
            if (p_task_info->lifecycle <= 0) {
                free(p_task_info);
                break;
            }

            if (!is_empty_qtpc(&qtpc)) {
                cur_thread = front_q(&qtpc);
                pop_qtpc(&qtpc);
                cur_thread->state = TASK_RUNNING;
                cur_thread->task = p_task_info;
            } else if (workq.size < WaitQueueMaxSize) {
                push_work_queue(&workq, p_task_info);
            } else {
                printf("任务等待队列已满，拒绝新的请求任务\n");
            }
            show_state(thread_info, &workq);
            update_time(thread_info, &qtpc, &workq);

            while (!is_empty_qtpc(&qtpc) && workq.size > 0) {
                pop_work_queue(&workq, &p_task_info);
                cur_thread = front_q(&qtpc);
                pop_qtpc(&qtpc);
                cur_thread->state = TASK_RUNNING;
                cur_thread->task = p_task_info;
            }
        }

        while (!is_full_qtpc(&qtpc)) {
            show_state(thread_info, &workq);
            update_time(thread_info, &qtpc, &workq);
            while (!is_empty_qtpc(&qtpc) && workq.size > 0)
                pop_work_queue(&workq, &p_task_info);
            cur_thread = front_q(&qtpc);
            pop_qtpc(&qtpc);
            cur_thread->state = TASK_RUNNING;
            cur_thread->task = p_task_info;
        }
    }
    Queue_Thread_Pool_Cycle qtpc;
    destroy_qtpc(&qtpc);
    return 0;
}





