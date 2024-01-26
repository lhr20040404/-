#include <stdio.h>
const int N = 10;//N种商品 
const int M = 5;//销量最多的前M种 
typedef struct brand{
	int total;
	char cname[100];
}BRAND;
typedef struct {
	int target;
	struct brand* p;
}ADT;
void swap(ADT *a, ADT *b)
{
	if(a->target!=b->target)
	{
		ADT t;
		t.target = a->target;
		t.p = a->p;
		a->target = b->target;
		a->p = b->p;
		b->target = t.target;
		b->p = t.p;
	}
}
void adjust_heap(ADT arr[], unsigned len, unsigned hole)
{
	unsigned left=2*hole+1;  
	unsigned right=2*hole+2;  
	ADT t;
	t.target = arr[hole].target;  
	t.p = arr[hole].p;
	while(left<len && t.target > arr[left].target || right <len && t.target > arr[right].target) 
	{
		if(right<len && arr[left].target > arr[right].target)
		{
		  	arr[hole].target = arr[right].target;
		  	arr[hole].p = arr[right].p;
		  	hole = right;
		}
		else
		{
			arr[hole].target = arr[left].target;
		  	arr[hole].p = arr[left].p;
			hole=left;
		}
		left=hole*2+1;  
		right=hole*2+2;
	} 
	arr[hole].target = t.target;
	arr[hole].p = t.p;
	
}
void make_heap2(ADT arr[], unsigned len)
{
	int i;
	for(i=len/2-1; i>=0; --i)
		adjust_heap(arr, len, i);
}
void pop_heap1(ADT arr[], unsigned len)
{
	swap(&arr[0], &arr[len-1]);
	adjust_heap(arr, len-1, 0);
}
void sort_heap(ADT arr[], unsigned len)
{
	int i;
	for(i=len; i>1; --i)
		pop_heap1(arr, i);
}
void partial_sort(ADT arr[], unsigned len, unsigned k)
{
	int i;
	make_heap2(arr,k);
	for(i=k; i<len; ++i)
		if(arr[i].target > arr[0].target)
		{
			swap(&arr[i],&arr[0]);
			adjust_heap(arr,k,0);			
		}
	sort_heap(arr,k);
}

int main()
{
	BRAND data_in[N]= {29000,"LG",124000,"XIAOMI",296000,"APPLE",119000,"OPPO",113000,"VIVO",
	                    238000,"HUAWEI",25000,"REALME",39000,"LENOVO",196000,"SAMSUNG",66000,"ONEPLUS"};
	ADT array[N];
	unsigned i;	
	for(i=0; i <N; ++i)
	{
		array[i].target = data_in[i].total;
		array[i].p = &data_in[i];
	}	
	partial_sort(array, N, M);	
	for(i=0; i < M; ++i)
		printf("%s %d\n",(array[i].p)->cname,(array[i].p)->total);	
	return 0;
}

