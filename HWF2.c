#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int is_circle(int *arr1, int *arr2, int n);

int is_equal(int *arr1, int *arr2, int n);

void circle(int *arr, int n);

void norm(int *arr, int n);

void print(int *arr, int n);

int is_correct(int *arr, int n);

int * copy(int *arr, int n);

void swap(int * arr, int i, int j);

int NextSet(int *arr, int n);

int main() {
	int start, end;
	start = time(NULL);
	
	int n;
	
	int res = scanf("%d", &n);
	assert(res == 1);
	
	int N = 0;
	int ** arrarr = NULL;
	int * arr = calloc(2 * n, sizeof(int));
	int * a;
	for(int i = 0; i < 2 * n; i++)
		arr[i] = i + 1;

	for(; res; ) {
		if(is_correct(arr, n)){
			a = copy(arr, n);
			norm(a, n);
			int f = 0;
			for(int i = 0; i < N; i++) {
				if(is_equal(arrarr[i], a, n))
					f = 1;
			}
				
			if(f == 0) {
				N++;
				arrarr = realloc(arrarr, N * sizeof(int*));
				arrarr[N - 1] = copy(a, n);
			}
			free(a);
		}
		res = NextSet(arr, n);
	}
	
	for(int i = 0; i < N; i++) {
		print(arrarr[i], n);
	}
	free(arr);
	for(int i = 0; i < N; i++)
		free(arrarr[i]);
	free(arrarr);
	
	end = time(NULL);
	printf("%d\n", end - start);
	return 0;
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
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(i != j && arr[i] == arr[j])
				return 0;
	
	for(int i = n; i < 2 * n - 1; i++)
		if(arr[i] + arr[i - n] + arr[(i - n + 1) % n] != arr[(i + 1) % n + n] + arr[(i + 1 - n) % n] + arr[(i + 1 - n + 1) % n])
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
