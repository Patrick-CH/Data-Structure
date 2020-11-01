#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITSIZE 200
#define INCREASEMENT 20

typedef char * Name;

typedef struct {
    Name * Names;
    int count;  //当前元素个数
    int size;   //size
} HashTable;

int SearchLength = 0;

int Hash(Name n);
void InputHashTable(HashTable*HT);
void SearchHash(HashTable* HT);

//读入文件
void InputHashTable(HashTable * HT){
    HT->Names = (Name*)malloc(INITSIZE * sizeof(Name));
    HT->size = INITSIZE;
    int m;
    for ( m = 0; m < HT->size; m++)
    {
        char a[] = "";
        *(HT->Names + m) = a;
    }
    HT->count = 0; 
    HT->size = INITSIZE;
    // char * ch = (char*)malloc(50*sizeof(char));
    char buf[100];      /*缓冲区*/
    FILE *fp;            /*文件指针*/
    int len;             /*行字符个数*/
    if((fp = fopen("Hash.txt","r")) == NULL)
    {
        perror("fail to read");
        exit (1);
    }
    while(fgets(buf,100,fp) != NULL)
    {
        len = strlen(buf);
        // printf("%s %d \n",buf,len - 1);s
    }
    int cnt = 0,i = 0,j = 0;
    Name n = (Name)malloc(100*sizeof(Name));
    while (i<len) {
        if(buf[i]!=' '){
            *(n+j) = buf[i];
            j++;
            i++;
        }
        else
        {
            *(n+j) = '\0';
            int index = Hash(n);
            while (*(HT->Names + index)[0]!='\0')
            {
                index++;
            }
            *(HT->Names + index) = n;
            cnt++;
            i++;
            j = 0;
            n+=sizeof(Name);
        }
    }
    while (cnt>HT->size)
    {
        Name* newbase = (Name*)realloc(HT->Names, (HT->size + INCREASEMENT)*sizeof(Name));
        if(!newbase) exit(-1);
        HT->size += INCREASEMENT;
    }
    HT->count = cnt;
}

//哈希函数
int Hash(Name n){
    char c = *n;
    return c;
}

//搜索函数
void SearchHash(HashTable* HT){
    int founded = 0;
    char s[10];
    printf("Please enter your text:\n");
    scanf("%s", s);
    int index = Hash(s);
    while (index<HT->size)
    {
        SearchLength++;
        if (strcmp(s,*(HT->Names + index))==0)
        {
            printf("Found!\n");
            printf("SearchLength=%d", SearchLength);
            founded = 1;
            return;
        }
        index++;
    }
    if (!founded)
    {
        printf("Search failed\n");
    }
    printf("SearchLength=%d", SearchLength);
}

int main(){
    HashTable * HT = (HashTable*)malloc(sizeof(HashTable));
    InputHashTable(HT);
    SearchHash(HT);
    system("pause");
    return 0;
}
