#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

unsigned int * arr_init() {
	int i;

	unsigned int * arr;
	
	arr = calloc(48, sizeof(unsigned int));		//48 - максимальное число фибоначи,которое влезает в unsigned
	
	arr[0] = 0;
	arr[1] = 1;
	for(i = 2; i < 48; i++){
		arr[i] = arr[i-1] + arr[i-2];
	}
	return arr;
}


unsigned int fib_part (unsigned int * arr, unsigned x) {	// const unsigned int*
	unsigned res = 0;
	
	int i;

	
	for(i = 47; i > 1;i--){
		if( x / arr[i]){
			x -= arr[i];
			res++;
		} 
			res = res * 2;
	}
	
	return res / 2 ;
}


int next_turn(unsigned int * arr, int total, int possible) {	// const unsigned int*
	int res;
	if(possible >= total)
		res = total;
	else {
		unsigned part = 0;
		
		int i;
		int min_i = 0;
		
		for(i = 47; i > 1;i--){
			if( total / arr[i]){
				min_i = i;
				total -= arr[i];
				part++;
			} 
				part = part * 2;
		}
		part = part / 2;
		
		if((unsigned)possible >= arr[min_i])
			res = arr[min_i];
		else
			res = 1;
		
	}
	
	
	return res;	
}

int rand_next_turn(int total, int possible) {
	srand(time(NULL));
	int res;
	if(possible >= total)
		res = total;
	else {
		res = rand() % possible + 1;
	}
	return res;
}


int main() {
	unsigned total, possible, turn;
	turn = 0;
	
	scanf ("%d", &total);
	assert(total > 1);
	possible = total - 1;
	
	srand(time(NULL));
	
	unsigned int * fib_arr = arr_init();
	int n = 10 + rand() % 90;
	int sum = 0;
	
	for(int i = 0; i < n; i++){
		sum += rand() % 2;
	}
	
	
	if(sum % 2) {
		printf("First move is random\n");
		turn = rand_next_turn(total, possible);
		printf("%d\n", turn);
		total -= turn;
		possible = 2 * turn;
	} else 
		printf("First move is not random\n");
	
	for(;total > 0;){
		turn = next_turn(fib_arr, total, possible);
		printf("%d\n", turn);
		total -= turn;
		possible = 2 * turn;
		if(total == 0) {
			printf("Smart player win\n");
		} else {
			turn = rand_next_turn(total, possible);
			printf("%d\n", turn);
			total -= turn;
			possible = 2 * turn;
			if(total == 0)
				printf("Ramdom player win\n");
		}
	}

	free(fib_arr);
	return 0;
}