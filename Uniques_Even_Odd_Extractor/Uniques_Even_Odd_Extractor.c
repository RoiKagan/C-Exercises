/* 
 Demonstrates the generation and analysis of a random array of integers.
 The program generates an array with intentional duplicates, extracts unique values,
 and separates them into even and odd arrays using merge sort and modular logic.
 */

#define _CRT_SECURE_NO_WARNINGS
#define ORG_SZ 20
#define MAX_VAL 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates an array with random integers between 1 and max, including intentional duplicates
int* generate_random_array(int sz, int max) {
	int* array = (int*)malloc(sizeof(int) * sz);
	if (array == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < sz; i++) {
		array[i] = rand() % max +1;
	}

	// Randomly duplicate some values to create non-uniqueness
	for (int i = 0; i < sz; i+=sz/(rand()%10+1)) {
		array[i] = array[rand() % sz];
	}

	return array;
}

// Prints an array
void array_print(int* arr, int sz) {
	for (int i = 0; i < sz - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d\n", arr[sz-1]);
}

// Merge two sorted halves
void merge(int* arr, int left_indx, int middle_indx, int right_indx) {
	int left_sz = middle_indx - left_indx + 1;
	int right_sz = right_indx - middle_indx;

	int* left_half = malloc(sizeof(int) * left_sz);
	int* right_half = malloc(sizeof(int) * right_sz);

	for (int i = 0; i < left_sz; i++) left_half[i] = arr[left_indx + i];
	for (int i = 0; i < right_sz; i++) right_half[i] = arr[middle_indx + 1 + i];

	
	int i = 0, j = 0,k = left_indx;
	while (i < left_sz && j < right_sz) {
		if (left_half[i] <= right_half[j])
			arr[k++] = left_half[i++];
		else
			arr[k++] = right_half[j++];
	}
	while (i < left_sz) arr[k++] = left_half[i++];
	while (j < right_sz) arr[k++] = right_half[j++];

	free(left_half);
	free(right_half);
}

// Recursive merge sort
void merge_sort(int* arr, int left_indx, int right_indx) {
	if (left_indx < right_indx) {
		int middle_indx = left_indx + (right_indx - left_indx) / 2;
		merge_sort(arr, left_indx, middle_indx);
		merge_sort(arr, middle_indx + 1, right_indx);
		merge(arr, left_indx, middle_indx, right_indx);
	}
}

// Extract unique elements from array
int* extract_uniques(int* arr, int sz, int* unique_count) {
	int* sorted_arr = (int*)malloc(sizeof(int) * sz);
	for (int i = 0; i < sz; i++) sorted_arr[i] = arr[i];

	merge_sort(sorted_arr,0, sz-1);

	*unique_count = 1;
	for (int i = 1; i < sz; i++) {
		if (sorted_arr[i] != sorted_arr[i - 1])
			(*unique_count)++;
	}

	int* uniques_arr = (int*)malloc(sizeof(int) * (*unique_count));
	uniques_arr[0] = sorted_arr[0];
	int j=1;
	for (int i = 1; i < sz; i++) {
		if (sorted_arr[i] != sorted_arr[i - 1]) {
			uniques_arr[j++] = sorted_arr[i];
		}
	}

	free(sorted_arr);
	return uniques_arr;
}

// Split array into even and odd arrays
void split_even_odd(int* arr, int sz,int** even_arr,int *even_count,int** odd_arr,int *odd_count) {
	*even_count = *odd_count = 0;
	for (int i = 0; i < sz; i++) {
		if (arr[i] % 2 == 0) 
			(*even_count)++;
		else
			(*odd_count)++;
	}

	*even_arr = (int*)malloc(sizeof(int) * (*even_count));
	*odd_arr = (int*)malloc(sizeof(int) * (*odd_count));

	int even_indx = 0, odd_indx = 0;
	for (int i = 0; i < sz; i++) {
		if (arr[i] % 2 == 0) 
			(*even_arr)[even_indx++] = arr[i];
		else 
			(*odd_arr)[odd_indx++] = arr[i];
	}
}

int main() {
	int *arr= generate_random_array(ORG_SZ, MAX_VAL);
	int* unique_arr, unique_count;
	int* even_arr, even_count;
	int *odd_arr,odd_count;
	
	printf("Original array:\n");
	array_print(arr, ORG_SZ);
	printf("\n");

	unique_arr = extract_uniques(arr, ORG_SZ,&unique_count);
	printf("Uniques values:\n");
	array_print(unique_arr, unique_count);
	printf("\n");

	split_even_odd(unique_arr, unique_count, &even_arr, &even_count, &odd_arr, &odd_count);
	printf("Even numbers:\n");
	array_print(even_arr, even_count);
	printf("Odd numbers:\n");
	array_print(odd_arr, odd_count);
	
	// Clean up
	free(arr);
	free(unique_arr);
	free(even_arr);
	free(odd_arr);

	return 0;
}
