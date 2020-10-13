#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    unsigned int weight;
    unsigned int parent,lchirld,rchirld;
}HTNode, * HuffmanTree; //动态分配数组储存赫夫曼树

typedef char **HuffmanCode;//动态分配数组储存赫夫曼编码表
        
void ReadChar(int * w, int * pn, char * chars);
void Select(HuffmanTree *HT, int n , int * s1, int * s2);
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int * w, int n);

int main(){
    int n,i;
    int w[128]={0};
    char chars[20];
    ReadChar(w, &n, chars);
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanCoding(&HT, &HC, w, n);
    printf("Huffman Code:\n");
    for(i=1; i<=n; i++){
        printf("%c HUFFMANCODE: %s\n",chars[i], HC[i]);
    }
    system("pause");
}

/*
读入字符串将weight存在w中,字符存在chars中
*/
void ReadChar(int * w, int * pn, char * chars){
    int i,n=0;
    int wi[218] = {0};
    char * ch = (char*)malloc(50*sizeof(char));
    char buf[100];      /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if((fp = fopen("D:\\file\\a.txt","r")) == NULL)
    {
        perror("fail to read");
        exit (1);
    }
    printf("File are as followed:\n");
    while(fgets(buf,100,fp) != NULL)
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        //printf("%s %d \n",buf,len - 1);
        for(i=0; i<len; i++){
            char c = buf[i];
            *(wi+int(c)) += 1;
            printf("%c", c);
        }
    }
    printf("\n");
    for(i=0; i<128; i++){
        if(wi[i]!=0){
          chars[n] = (char)i;
          w[n] = wi[i];
          n++;
        } 
    }
    chars[n] = '\0';
    printf("There is %d chars in total\n", n);
    *pn = n;
}

/*
w存放n个字符的权值，构造赫夫曼数HT，并求出n个字符的赫夫曼编码HC
*/
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int * w, int n){
    if(n<=1) return;
    int m = 2 * n - 1;
    int i;
    *HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));
    HTNode * p;
    for(p=*HT+1, i=1; i<=n; ++i,++p,++w){
        p->weight = *w;
        p->lchirld = 0;
        p->parent = 0;
        p->rchirld = 0;
    } 
    for(; i<=m; ++i,++p){
        int s1, s2;
        Select(HT, i-1, &s1, &s2);
        (*HT+s1)->parent = i; (*HT+s2)->parent = i;
        (*HT+i)->lchirld = s1; (*HT+i)->rchirld = s2;
        (*HT+i)->weight = (*HT+s1)->weight + (*HT+s2)->weight;
        (*HT+i)->parent = 0;
    }
    printf("This is Huffman table:\n");
    for(p=*HT+1, i=1; i<=m; ++i,++p){
        printf("%d %d %d %d\n",p->weight,p->lchirld,p->parent,p->rchirld);
    }
    //------从叶子节点到根逆向求每个字符的赫夫曼编码------
    *HC = (HuffmanCode)malloc((n+1) * sizeof(char*));
    char * cd = (char*)malloc(n * sizeof(char));
    cd[n-1] = '\0';
    for(i=1;i<=n;i++){
        int start = n - 1;
        int c,f;
        for(c=i, f = (*HT+i)->parent; f != 0; c=f,f=(*HT+f)->parent){
            if((*HT+f)->lchirld == c) cd[--start] = '0';
            else cd[--start] = '1';
        }
        *(*HC + i) = (char *)malloc((n-start) * sizeof(char));
        strcpy(*(*HC + i), &cd[start]);
    }
    free(cd);
}

/*
在HT[1...i-1]选择parent==0且weight最小的两个节点，其序号分别为s1,s2
*/
void Select(HuffmanTree *HT, int n , int * s1, int * s2){
    int i;
    int min=1,min1=1;
    HTNode *p = *HT+1; 
    while (p->parent!=0)
    {
        p++;
        min++;
    }
    p = *HT+1; 
    for(i=1; i<=n; i++, p++){
        if((*HT+i)->weight < p->weight&&(p->parent != 0)){
            p++;
            min = i;
        }
    }
    p = *HT+1; 
    while (p->parent!=0||min1==min)
    {
        p++;
        min1++;
    }
    p = *HT+1; 
    for(i=1; i<=n; i++, p++){
        if(i==min) i++;
        if((*HT+i)->weight<p->weight&&(p->parent != 0)){
            min1 = i;
        }
    }
    *s1 = min;
    *s2 = min1;
}