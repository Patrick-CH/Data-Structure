#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100
#define STACKINREASEMENT 10
#define OVERFLOW -1

typedef struct{
    int From;
    int To;
}ArcInfo;

typedef struct ArcNode{
    ArcInfo arcinfo;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct{
    int index;
    ArcNode * firstarc;
}VNode;

typedef struct{
    int vexnum;
    VNode * vertices;
}Graphic;

typedef struct{
    int *base;
    int * top;
    int stacksize;
}SqStack;

void InitStack(SqStack * pSqStack);
int Gettop(SqStack * S);
void Push(SqStack * S, int e);
int Pop(SqStack * S);
int StackEmpty(SqStack S);
void GrapicCreate(Graphic* pG, int vexnum);
void VNodeCreate(VNode* pv, int index);
void ArcNodeCreate(ArcNode* parc ,int from, int to);
void ArcNodeAdd(ArcNode * first, ArcNode * arc);
void Indegree(int* indegree, Graphic G);
void TopoLogicalSort(Graphic G);

int main(){
    Graphic * pG = (Graphic*)malloc(sizeof(Graphic));
    GrapicCreate(pG, 12);//12为节点数量
    TopoLogicalSort(*pG);
    system("pause");
    return 0;
}

//创建一个空栈S
void InitStack(SqStack * pSqStack){
    pSqStack->base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    if(!pSqStack->base) exit(OVERFLOW);
    pSqStack->top=pSqStack->base;
    pSqStack->stacksize = STACK_INIT_SIZE;
}

//若栈不空则返回S的栈顶元素，否则返回-1并报错。
int Gettop(SqStack * S){
    if(S->top == S->base) {
        printf("%s", "STACK_EMPTY_ERROR");
        return -1;
    }
    int e = *(S->top - 1);
    return e;
}

//插入e为新的栈顶元素
void Push(SqStack * S, int e){
    if(S->top - S->base >= S->stacksize){
        S->base = (int*)realloc(S->base, (S->stacksize + STACKINREASEMENT)*sizeof(int));
        if(!S->base) exit(OVERFLOW);
        S->stacksize += STACKINREASEMENT;
    }
    *S->top = e;
    S->top += sizeof(int);
}

//若栈不空则删除栈顶元素，并返回其值，否则返回-1并报错。
int Pop(SqStack * S){
    if(S->top == S->base){
        printf("%s", "STACK_EMPTY_ERROR");
        return -1;
    }
    S->top -= sizeof(int);
    char e = *S->top;
    return e;
}

//判断s是否为空，是则返回1否则返回0
int StackEmpty(SqStack S){
    return S.base==S.top? 1:0;
}

//创建图
void GrapicCreate(Graphic* pG, int vexnum){
    pG->vexnum = vexnum;
    pG->vertices = (VNode*)malloc(vexnum * sizeof(VNode));
    int i;
    for(i=0; i<vexnum; i++){
        VNode * p = (VNode*)malloc(sizeof(VNode));
        VNodeCreate(p,i);
        pG->vertices[i] = *p;
    }
}

//创建节点
void VNodeCreate(VNode* pv, int index){
    //读入         
    char s[20]; 
    sprintf(s,"D:\\file\\%d.txt",index);
    char buf[50];      /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len = 0;             /*行字符个数*/
    if((fp = fopen(s,"r")) == NULL)
    {
        perror("fail to read");
        exit (1);
    }
    while(fgets(buf,100,fp) != NULL)
    {
        len = strlen(buf);
        buf[len] = '\0';  /*去掉换行符*/
    }
    int to = buf[0] - 66;
    if(len!=0){
        ArcNode* arc0 = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNodeCreate(arc0, index, to);
        pv->firstarc = arc0;
    }else{
        pv->firstarc = NULL;
        pv->index = index;
        return;
    }
    pv->index = index;
    int i = 0;
    for (i = 1; i < len; i++)
    {
        int to = buf[i] - 66;
        ArcNode* arc = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNodeCreate(arc, index, to);
        ArcNodeAdd(pv->firstarc, arc);
    }
}

//创建弧
void ArcNodeCreate(ArcNode* parc ,int from, int to ){
    parc->arcinfo.From = from;
    parc->arcinfo.To = to;   
    parc->nextarc = NULL;
}

//向节点添加弧
void ArcNodeAdd(ArcNode * first, ArcNode * arc){
    ArcNode * p = first;
    if(p){
        while (p->nextarc)
        {
            p = p->nextarc;
        }
        p->nextarc = arc;
    }else
    {
        p = arc;
    }
}

//计算每个点的入度并存入indegree
void  Indegree(int* indegree, Graphic G){
    int i = 0;
    for(i=0; i<G.vexnum; i++){
        ArcNode * p = G.vertices[i].firstarc;
        while (p)
        {
            printf("from C%d to C%d\n",p->arcinfo.From+1, p->arcinfo.To+1);
            indegree[p->arcinfo.To]++;
            p = p->nextarc;
        }
    }
}

//计算G的一个拓扑序列并输出
void TopoLogicalSort(Graphic G){
    int indegree[G.vexnum] = {0};
    Indegree(indegree, G);
    SqStack stack;
    InitStack(&stack);
    int i;
    for ( i = 0; i < G.vexnum; i++)
    {
        //printf("%d indegree %d\n", i, indegree[i]);
        if(indegree[i] == 0) Push(&stack, i);
    }
    int cnt = 0;
    while (!StackEmpty(stack))
    {
        int index = Pop(&stack);
        printf("Node C%d\n", index+1);
        cnt++;
        ArcNode * p;
        for(p = G.vertices[index].firstarc; p; p = p->nextarc){
            int k = p->arcinfo.To;
            indegree[k]--;
            if(indegree[k]==0) Push(&stack, k);
        }
    }
    if(cnt<G.vexnum) printf("Not AOV!");
}