// Print and create csv file of prime numbers

#define _CRT_SECURE_NO_WARNINGS
#define CELL_WIDTH 6 // Width of each cell in the table

#include <stdio.h>
#include <stdlib.h>

//user input
int get_positive_number() {
	int n;
	while (1) {
		printf("Enter how many prime numbers you want to generate: ");
		if (scanf("%d", &n) != 1 || n <= 0) {
			printf("Invalid input. Please enter a positive number.\n");
			// Clear invalid input from stdin buffer
			while (getchar() != '\n');
		}
		else {
			// Clear leftover characters in the input buffer
			while (getchar() != '\n');
			return n;
		}
	}
}

// Check if a number is prime
int is_prime(num) { 
	if (num < 2) return 0;
	if (num == 2) return 1;
	if (num % 2 == 0) return 0;
	
	for (int i = 3; i * i <= num; i += 2) {
		if (num % i == 0) return 0;
	}
	return 1;
}

// Count number of digits
int count_digits(int num) {
	int digits = 1;
	while (num /= 10) digits++;
	return digits;
}

// Center a number in a table cell
void print_cell(int num) {
	int digits = count_digits(num);
	int right_pad = (CELL_WIDTH - digits) / 2;
	int left_pad = CELL_WIDTH - digits - right_pad;
	
	printf("|");
	for (int i = 0; i < left_pad; i++) printf(" ");
	printf("%d",num);
	for (int i = 0; i < right_pad; i++) printf(" ");
}

// Generate primes into dynamically allocated array
void generate_primes(int* primes, int count) {
	int num = 2;
	int found = 0;

	while (found < count) {
		if (is_prime(num)) {
			primes[found++] = num;
		}
		num++;
	}
}

// Print primes as table
void print_primes_table(int* primes, int count) {

	// Table top border
	printf(" ");
	for (int i = 0; i < CELL_WIDTH*2+1; i++) printf("_");
	printf(" \n");

	printf("|Index |Prime |\n");

	printf("|");
	for (int i = 0; i < CELL_WIDTH; i++) printf("-");
	printf("|");
	for (int i = 0; i < CELL_WIDTH; i++) printf("-");
	printf("|\n");

	// Data
	for (int i = 0; i < count; i++) {
		print_cell(i + 1);
		print_cell(primes[i]);
		printf("|\n");
	}
	

	// Table buttom border
	printf(" ");
	for (int i = 0; i < CELL_WIDTH * 2 + 1; i++) printf("-");
	printf(" \n");
}

// Save to CSV
void write_primes_to_csv(const char* filename, int* primes, int count) {
	FILE* fp = fopen(filename, "w");
	if (!fp) {
		printf("Error: Could not open file %s\n", filename);
		return;
	}

	fprintf(fp, "Index,Prime\n");
	for (int i = 0; i < count; i++) {
		fprintf(fp, "%d,%d\n", i + 1, primes[i]);
	}

	fclose(fp);
	printf("Primes saved to primes.csv\n");
}

int main(void) {
	int n = get_positive_number();;
	int* primes = (int*)malloc(n * sizeof(int));
	if (primes == NULL) {
		printf("Memory allocation failed\n");
		return 1;
	}
	generate_primes(primes, n);
    printf("The first %d prime numbers:\n", n);
	print_primes_table(primes, n);
	write_primes_to_csv("primes.csv", primes, n);
	free(primes);
	return 0;
}