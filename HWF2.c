#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int is_circle(int *arr1, int *arr2, int n);

int is_equal(int *arr1, int *arr2, int n);

void circle(int *arr, int n);

void norm(int *arr, int n);

void print(int *arr, int n);

int is_correct(int *arr, int n);

int main() {
	int arr[] = {3,2,1,4,6,5};
	print(arr, 3);
	printf("%d\n", is_correct(arr, 3));
	return 0;
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
	
	for(int i = n; i < 2 * n; i++)
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

void print(int *arr, int n) {
	assert(arr != NULL);
	assert(n > 2);
	
	for(int i = n; i < 2 * n; i++) {
		printf("%d,%d,%d;", arr[i], arr[i - n], arr[(i - n + 1) % n]);
	}
	printf("\n");
}
