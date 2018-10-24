#define MAXSIZE 100
#define ERROR 0x0001
#define OK  0
# stack & queue
typedef int SElemType;
typedef struct
{
    SElemType data[MAXSIZE];
    int top;
}sqStack;

Status Push()
{

}

Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
    if(stackNumber == 1)
    {
        if (S->top1 == -1)            
            return ERROR;
        *e = S->data[S->top1--];
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
            return ERROR;
        *e = S->data[S->top2++];
    }   
    return OK;

}

##  9+(3-1) *3 +10/2
/*
后缀表达式：9 3 1 - 3 * + 10 2 / +
*/
typedef struct
{

}

// 循环队列的顺序存储结构
typedef struct
{
  QElemType data[MAXSIZE];
  int front;
  int rear;
}SqQueue;

/*初始化一个空队列Q*/
Status InitQueue(SqQueue *Q)
{
  Q->front = 0;
  Q->rear = 0;
  return OK;
}

/*返回Q的元素个数，也就是队列的当前长度*/
int QueueLength(SqQueue Q）
{
  return (Q.rear - Q.front + MAXSIZE)% MAXSIZE;
}

/*若队列未满，则插入元素e为新的队尾元素*/
Status EnQueue(SqQueue *Q,, QElemType e)
{
  if ((Q->rear + 1) % MAXSIZE == Q->front)
      return ERROR;
  Q->data[Q->rear] = e;  /*将元素e赋值给队尾*/
  Q->rear=(Q->rear+1)%MAXSIZE;/*rear指针向后移一位置*/
  return OK;
}
                
/*若队列不空，则删除Q中对头元素，用e返回其值*/
Status Dequeue(SqQueue *Q, QElemType *e)
{
  if (Q->front == Q->rear)
      return ERROR;
  *e = Q->data[Q->front];
  Q->front=(Q->front+1) % MAXSIZE;
  return OK;
}

//链队列的结构
typedef int QElemType;
typedef struct QNode  /*节点结构*/
{
  QElemType data;
  struct QNode *next;
}QNode, *QueuePtr;

typedef struct    /*队列的链表结构*/
{
  QueuePtr front,rear;
}LinkQueue;
# 队列的链式存储结构一一入队操作
/*插入元素e为Q的新的队尾元素*/
Status EnQueue(LinkQueue *Q, QElemType e)
{
  QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
  if (!s)
      exit(OVERFLOW);
  s->data = e;
  s->next = NULL;
  Q->rear->next = s;
  Q->rear = s;

  return OK;
}

# 队列的链式存储结构一一出队操作
Status DeQueue(LinkQueue *Q, QElemType *e)
{
  QueuePtr p;
  if(Q->front == Q->rear)
      return ERROR;
  p = Q->front->next;  
  *e = p->data;
  Q->front->next = p->next;
    
  if (Q->rear == p)      /*若队头是队尾，则倒自最后将 rear指向头结点，几上图中③*/
      Q->rear = Q->front;
  free(p);
  return OK;
  
}



# ch5 串
                
/* T为非空串。若主串S中第pos个字符之后存在与T相等的字串，*/
/* 则返回第一个这样的子串在S中的位置，否则返回0 */
int Index(String S, String T, int pos)
{
  int n, m, i;
  String sub;
  if (pos > 0)
  {
    n = StrLength(S);
    m = StrLength(T);
    i = pos;
    while (i <= n-m+1)
    {
      SubString(sub, S, i, m);
      if (StrCompare(sub, T) != 0)
        ++i;
      else
        return i;    
    }  
  }
  return 0;
}

/*通过计算返回子串T的next数组*/
void get_next(String T, int *next)
{
  int i, j;
  i = 1;
  j = 0;
  next[1] = 0;
  while (i < T[0])         /*此处T[0]表示T的长度*/
  {
    if (j == 0 || T[i] == T[j])  /*T[i] 表示后缀的单个字符，*/
    {                   /*T[j] 表示前缀的单个字符*/
      ++i;
      ++j;
      next[i] = j;
    }
    else
    {
      j = next[j];       /*若字符不相同，则j值回溯*/
    }
  }
}

/**/
int Index_KMP(String S, String T, int pos)
{
  int i = pos;
  int j = 1;
  int next[255];
  get_next(T, next);
  while (i <= S[0] && j <= T[0])
  {
    if (j ==0 || S[i] == T[j])
    {
        ++i;
        ++j;
    }
    else
    {
        j = next[j];
    }
  }
  if  (j > T[0])
  {

    return i - T[0];
  }
  else
    return 0;
}


/*求模式串T的next函数修正值并存入数组nextval*/
void get_nextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j ==0 || T[i] == T[j])
        {
            ++i;
            ++j;
            if (T[i] != T[j])
            {
                nextval[i] = j;
            }
            else
            {
                nextval[i] = nextval[j];
            }
        }
        else
        {
            j = nextval[j];
        }
    }
}