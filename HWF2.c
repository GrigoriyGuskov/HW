//-----------------------------------------------------------------------------------------
// Программа принимает на стандартный ввод n - количество троек в фигуре
// Затем перебирает все возможные перестановки и печатает, отсортировав лексикографически
// (Сложность перебора 2n!)
// 
// Пример для n = 3:
//		4
//		 \
//		  3
//		 / \
//		1---2--6
//	   /
//	  5
//-----------------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct {
	int N;
	int size;
	int ** arrarr;
}Answers;

int is_circle(int *arr1, int *arr2, int n);

int is_equal(int *arr1, int *arr2, int n);

void circle(int *arr, int n);

void norm(int *arr, int n);

void print(int *arr, int n);

int is_correct(int *arr, int n);

int * copy(int *arr, int n);

void swap(int * arr, int i, int j);

int NextSet(int *arr, int n);

Answers * ans_init();

void ans_free(Answers * pa);

void resize(Answers * pa);

void enumer(int n, Answers * pa);

int cmp_n(const void * a, const void * b, void * size);

int cmp(int a, int b);

int main() {
	
	int n;
	
	int res = scanf("%d", &n);
	assert(res == 1);
	
	int start, end;
	start = time(NULL);
	
	Answers * pa;
	
	pa = ans_init();
	
	enumer(n, pa);
	
	//sort
	qsort_r(pa->arrarr, pa->size, sizeof(int*), cmp_n, (void*)&n);
	
	for(int i = 0; i < pa->size; i++) {
		print((pa->arrarr)[i], n);
	}

	ans_free(pa);
	
	end = time(NULL);
	printf("%d\n", end - start);
	return 0;
}

Answers * ans_init() {
	Answers * ret = calloc(1, sizeof(Answers));
	ret->arrarr = NULL;
	ret->N = 0;
	ret->size = 0;
	return ret;
}

void ans_free(Answers * pa){
	for(int i = 0; i < pa->size; i++)
		free((pa->arrarr)[i]);
	free((pa->arrarr));
	free(pa);
}


void resize(Answers * pa) {
	assert(pa != NULL);
	
	if(pa->size > pa->N){
		pa->N = pa->N * 2;
		if(pa->N == 0)
			pa->N = 1;
		(pa->arrarr) = realloc((pa->arrarr), pa->N * sizeof(int*));
	}
}


void enumer(int n, Answers * pa) {
	assert(pa != NULL);
	assert(n > 2);
	
	int * a = NULL;
	int * arr = calloc(2 * n, sizeof(int));
	for(int i = 0; i < 2 * n; i++)
		arr[i] = i + 1;
	
	int res = 1;
	for(; res; ) {
		if(is_correct(arr, n)){
			a = copy(arr, n);
			norm(a, n);
			int f = 0;
			for(int i = 0; i < pa->size; i++) {
				if(is_equal((pa->arrarr)[i], a, n))
					f = 1;
			}
				
			if(f == 0) {//
				pa->size = pa->size + 1;
				resize(pa);
				(pa->arrarr)[pa->size - 1] = copy(a, n);
			}
			free(a);
		}
		res = NextSet(arr, n);
	}
	
	free(arr);
	

}

int NextSet(int *arr, int n) {
	n = 2 * n;
	int j = n - 2;
	for(; j != -1 && arr[j] >= arr[j + 1]; j--);

	if (j == -1)
		return 0;
	
	int k = n - 1;
	for(; arr[j] >= arr[k]; k--);
	
	swap(arr, j, k);
	int l = j + 1;
	int r = n - 1;
	for(; l < r; l++, r--)
		swap(arr, l, r);

	return 1;
}

void swap(int * arr, int i, int j) {
	assert(arr != NULL);
	assert(i >= 0);
	assert(j >= 0);
	
	if(i != j) {
		int c = arr[i];
		arr[i] = arr[j];
		arr[j] = c;
	}
}

int is_equal(int *arr1, int *arr2, int n) {
	assert(arr1 != NULL);
	assert(arr2 != NULL);
	assert(n > 2);
	
	for(int i = 0; i < 2 * n; i++)
		if(arr1[i] != arr2[i])
			return 0;
	return 1;
}

int is_correct(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	int sum;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i != j && arr[i] == arr[j])
				return 0;
	sum = arr[n] + arr[0] + arr[1];
	for(int i = 1; i < n; i++)
		if(arr[n + i] + arr[i] + arr[(i + 1) % n] != sum)
			return 0;
	return 1;
}

void circle(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	int c = arr[0];
	for(int i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];
	arr[n - 1] = c;
	
	c = arr[n];
	for(int i = n; i < 2 * n - 1; i++)
		arr[i] = arr[i + 1];
	arr[2 * n - 1] = c;
}

void norm(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	int c = n;
	for(int i = n; i < 2 * n; i++)
		if(arr[i] < arr[c])
			c = i;
	for(int i = n; i < c; i++)
		circle(arr, n);
}

int is_circle(int *arr1, int *arr2, int n) {
	assert(arr1 != NULL);
	assert(arr2 != NULL);
	assert(n > 2);
	
	norm(arr1, n);
	norm(arr2, n);
	return is_equal(arr1, arr2, n);
}

int * copy(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	int * ret = calloc(2 * n, sizeof(int));
	
	assert(ret != NULL);
	
	for(int i = 0; i < 2 * n; i++)
		ret[i] = arr[i];
	return ret;
}

void print(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	for(int i = n; i < 2 * n; i++) {
		printf("%d,%d,%d;", arr[i], arr[i - n], arr[(i - n + 1) % n]);
	}
	printf("\n");
}

int cmp_n(const void * a, const void * b, void * size) {
	int * first = *((int**)a);
	int * second = *((int**)b);
	int n = *((int*)size);
	int ret = 0;
	for(int i = 0; i < n; i++) {
		ret = cmp(first[n + i], second[n + i]);
		if(ret)
			return ret;
		ret = cmp(first[i], second[i]);
		if(ret)
			return ret;
		ret = cmp(first[(i + 1) % n], second[(i + 1) % n]);
		if(ret)
			return ret;
	}
	return ret;
}

int cmp(int a, int b) {
	if(a < b)
		return -1;
	if(a > b)
		return 1;
	return 0;
}
