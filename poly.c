#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    float coef;
    int expn;
}Elem;

typedef struct node{
	Elem elem;
	struct node *next;
}Node; 

typedef struct _poly{
    Node * head;
}LinkList_poly;

void add(LinkList_poly *linkList_poly, Elem elem);
void CreatPoly(LinkList_poly* linkList_poly, int m);
void PrintPoly(LinkList_poly linkList_poly);
void Polylenth(LinkList_poly linkList_poly);
void DelNode(Node *head, Node *cur);
void AddPoly(LinkList_poly * pa, LinkList_poly * pb);
int cmp(int a, int b);
void Polylenth(LinkList_poly linkList_poly);
void PolyMuti(LinkList_poly * pa, LinkList_poly * pb, LinkList_poly * pc);

int main(){
    LinkList_poly l1;
    l1.head=(Node*)malloc(sizeof(Node));
    l1.head->next = NULL;
    LinkList_poly l2;
    l2.head=(Node*)malloc(sizeof(Node));
    l2.head->next = NULL;
    LinkList_poly l3;
    l3.head=(Node*)malloc(sizeof(Node));
    l3.head->next = NULL;
    CreatPoly(&l1, 2);
    CreatPoly(&l2, 2);
    printf("l1:\n");
    PrintPoly(l1);
    printf("l2:\n");
    PrintPoly(l2);
    PolyMuti(&l1, &l2, &l3);
    AddPoly(&l1, &l2);
    printf("result of add:\n");
    PrintPoly(l1);
    printf("result of multiply:\n");
    PrintPoly(l3);
    printf("----end----\n");
    system("pause");
    return 0;
}

/*
创造一个多项式链表
*/
void CreatPoly(LinkList_poly* linkList_poly, int m){
    int i,expn;
    float coef;
    for(i=0;i<m;i++){
        scanf("%f %d",&coef, &expn);
        Elem elem;
        elem.coef=coef;
        elem.expn=expn;
        add(linkList_poly, elem);
    }
}

/*
向链表中添加节点
*/
void add(LinkList_poly *linkList_poly, Elem elem)
{
	Node *p=(Node*)malloc(sizeof(Node));
		p->elem=elem;
		p->next=NULL; 
		//find the last
		Node *last=linkList_poly->head;
		if(last){
			while(last->next){
			last=last->next;
			}
		    last->next=p;
		}else{
		    linkList_poly->head->next=p;
        }
}

/*
打印多项式
*/
void PrintPoly(LinkList_poly linkList_poly){
    Node* p = linkList_poly.head;
    p = p->next;
    while( p ){
        printf("%.2f X^%d ", p->elem.coef, p->elem.expn);
		p = p->next;
    }
    printf("\n");
}

/*
求多项式的项数
*/
void Polylenth(LinkList_poly linkList_poly){
    Node* p = linkList_poly.head;
    int i = 0;
    while( p ){
        printf("%f X%d\n", p->elem.coef, p->elem.expn);
		p = p->next;
        i++;
    }
}

/*
a>b返回1，a<b返回-1，a==b返回0
*/
int cmp(int a, int b){
    if(a>b) return 1;
    else if(a==b) return 0;
    else return -1;
}

/*
删除节点
*/
void DelNode(Node *head, Node *cur){
	Node* q = head;
	Node* p = q->next;
	while( p ){
		if( p == cur ){
			q->next = p->next;
			free(p);
		}
		q = p;
		p = p->next;
	}
}

/*
多项式相加，结果保存在前一个链表
*/
void AddPoly(LinkList_poly * pa, LinkList_poly * pb){
    Node *ha = pa->head;
    Node *hb = pb->head;
    Node *qa = ha->next;
    Node *qb = hb->next;
    while (qa&&qb)
    {
        int a = qa->elem.expn;
        int b = qb->elem.expn;
        float sum = 0.0;
        switch (cmp(a,b))
        {
        case 0:
            sum = qa->elem.coef + qb->elem.coef;
            if(sum!=0.0){
                qa->elem.coef=sum;
                ha = qa;
            }else
            {
                DelNode(ha, qa);
                free(qa);
            }
            DelNode(hb,qb);
            free(qb);
            qb = hb->next;
            qa = ha->next;
            break;
        case -1:
            ha = qa;
            qa = qa->next;
            break;
        case 1:
            DelNode(ha, qb);
            ha->next = qb;
            qb = qb->next;
            qa = qa->next;
            break;
        }
    }
    if(hb->next){
        Node *p = pa->head;
        while (p->next)
        {
            p=p->next;
        }
        p->next = hb->next;
        free(hb);
    }   
}


/*
多项式相乘
*/
void PolyMuti(LinkList_poly * pa, LinkList_poly * pb, LinkList_poly * pc){
    Node *qa = pa->head->next;
    Node *qb = pb->head->next;
    LinkList_poly l2;
    while (qa)
    {

        LinkList_poly l;
        l.head=(Node*)malloc(sizeof(Node));
        l.head->next = NULL;
        while ( qb )
        {
            Elem x;
            x.coef = (qa->elem.coef) * (qb->elem.coef);
            x.expn = qa->elem.expn + qb->elem.expn;
            add(&l, x);
            qb = qb->next;
        } 
        AddPoly(pc, &l);
        qa = qa->next;
        qb = pb->head->next;
    }
}