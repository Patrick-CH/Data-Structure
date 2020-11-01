#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _DATA_SIZE_ 30000  //数据总数

void ReadData(float * data);
void InsertSort(float * data);
void BubbleSort(float * data);
int Partition(float * data, int low, int high);
void QuickSort(float * data, int low, int high);
void QuickSortBox(float * data);
void SelectionSort(float * data);
void HeapSort(float * data);
void HeapAdjust(float * data, int s, int m);

int compare_time_qs = 0, move_time_qs = 0;//记录快速排序比较和移动的次数
int compare_time_hs = 0, move_time_hs = 0;//记录比较和移动的次数

void ReadData(float * data){
	int i;
	FILE *file = fopen("data.dat", "rb");  //data.dat文件存有10000个浮点数
	if (file==NULL){  //检测是否成功打开
		printf("Open failed\n");
        return;
    }
	for (i = 0; i<_DATA_SIZE_; i++)
	{
        fread(data+i, sizeof(float), 1, file);   //读入data.dat数据给数组data[]
	}
	fclose(file);//释放指针
}

/*
直接插入排序
*/
void InsertSort(float * data){
    clock_t start,end;
    start = clock();//计时开始
    int i;
    float x;
    int compare_time = 0, move_time = 0;//记录比较和移动的次数
    for ( i = 1; i < _DATA_SIZE_; i++)
    {
        compare_time++;
        if(data[i] < data[i-1]){
            x = data[i];
            data[i] = data[i-1];
            int j;
            for ( j = i-2; x<data[j]; --j)
            {
                move_time++;
                data[j+1] = data[j];
            }
            move_time++;
            data[j+1] = x;
        }
    }
    end = clock();//计时结束
    printf("InserSort compare_time : %d , move_time : %d time : %f ms\n", compare_time, move_time, (double)(end-start)/CLK_TCK);
}

/*
冒泡排序
*/
void BubbleSort(float * data){
    clock_t start,end;
    start = clock();//计时开始
    int i,j;
    float x;
    int compare_time = 0, move_time = 0;//记录比较和移动的次数
    for ( j = 0; j < _DATA_SIZE_; j++)
    {
        for ( i = 0; i < _DATA_SIZE_-1; i++)
        {
            compare_time++;
            if(data[i] < data[i+1]){
                move_time++;
                x = data[i];
                data[i] = data[i+1];
                data[i+1] = x;
            }
        }
    }
    end = clock();//计时结束
    printf("BubbleSort compare_time : %d , move_time : %d time : %f ms\n", compare_time, move_time, (double)(end-start)/CLK_TCK);
}

/*
快速排序
*/
void QuickSort(float * data, int low, int high){
    clock_t start,end;
    start = clock();//计时开始
    compare_time_qs++;
    if (low<high)
    {
        int pivotloc = Partition(data, low, high);
        QuickSort(data, low, pivotloc - 1);
        QuickSort(data, pivotloc + 1, high);
    }

}

/*
快速排序中求枢轴
*/
int Partition(float * data, int low, int high){
    int i,j;
    float x = data[low];
    float pivotkey = data[low];
    while (low < high)
    {
        compare_time_qs++;
        while (low<high&&data[high]>=pivotkey)
        {
            compare_time_qs++;
            --high;
            data[low] = data[high];
            move_time_qs++;
        }
        while (low<high&&data[low]<=pivotkey)
        {
            compare_time_qs++;   
            ++low;
            data[high] = data[low];
            move_time_qs++;
        }
    }
    move_time_qs++;
    data[low] = x;
    return low;
}

/*
封装快速排序，方便计数
*/
void QuickSortBox(float * data){
    clock_t start,end;
    start = clock();//计时开始
    QuickSort(data, 0, _DATA_SIZE_-1);
    end = clock();//计时结束
    printf("QuickSort compare_time : %d , move_time : %d time : %f ms\n", compare_time_qs, move_time_qs, (double)(end-start)/CLK_TCK);
}

/*
简单选择排序
*/
void SelectionSort(float * data){
    clock_t start,end;
    int compare_time = 0, move_time = 0;//记录比较和移动的次数
    start = clock();//计时开始
    int i,j;
    for ( i = 0; i < _DATA_SIZE_; i++)
    {
        int min = i;
        for ( j = i+1; j < _DATA_SIZE_; j++)
        {
            compare_time++;
            if (data[j]<data[min])
            {
                min = j;
            }
        }
        move_time++;
        float x = data[i];
        data[i] = data[min];
        data[min] = x;
    }
    end = clock();//计时结束
    printf("SelectionSort compare_time : %d , move_time : %d time : %f ms\n", compare_time, move_time, (double)(end-start)/CLK_TCK);
}

/*
堆排序
*/
void HeapSort(float * data){
    clock_t start,end;
    start = clock();//计时开始
    int i;
    for ( i = _DATA_SIZE_/2-1; i >= 0; --i)
    {
        HeapAdjust(data, i, _DATA_SIZE_-1);
    }
    for ( i = _DATA_SIZE_-1; i >= 1; --i)
    {
        move_time_hs++;
        float x = data[0];
        data[0] = data[i];
        data[i] = x;
        HeapAdjust(data,0,i-1);
    }   
    end = clock();//计时结束
    printf("HeapSort compare_time : %d , move_time : %d time : %f ms\n", compare_time_hs, move_time_hs, (double)(end-start)/CLK_TCK);
}

/*
堆排序调整
*/
void HeapAdjust(float * data, int s, int m){
    float x = data[s];
    int j;
    for ( j = 2*s; j <= m; j*=2)
    {
        compare_time_hs++;
        if (j<m&&data[j]<data[j+1])
        {
            ++j;
        }
        compare_time_hs++;
        if (x>=data[j])
        {
            break;
        }
        move_time_hs++;
        data[s] = data[j];
        s = j;      
    }
    data[s] = x;   
}

int main(){
    /*
    读入文件 data.dat到data[]
    */
    float * data = (float*)malloc(_DATA_SIZE_ * sizeof(float)); //自定义二维数组大小

    ReadData(data);
    InsertSort(data);

    ReadData(data);
    BubbleSort(data);

    ReadData(data);
    QuickSortBox(data);

    ReadData(data);
    SelectionSort(data);

    ReadData(data);
    HeapSort(data);

    // int i;
    // for ( i = 0; i < _DATA_SIZE_; i++)
    // {
    //     printf("%f ", data[i]);
    // }

    system("pause");
    return 0;
}
