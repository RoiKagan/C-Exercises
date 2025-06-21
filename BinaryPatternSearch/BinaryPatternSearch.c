/*
===========================================================
  Bit Pattern Matcher
  --------------------
  This program searches for all occurrences of a binary
  pattern inside a given number and returns a bitmask
  indicating the positions (by LSB index) where the pattern
  appears. Positions are zero-indexed from the right (LSB).

===========================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// Calculates the number of bits required to represent a number in binary.
int GetBitLength(int num) {
	if (num == 0) return 1;
	
	int len = 0;
	while (num) {
		num >>= 1;
		len++;
	}
	return len;
}

// Prints the binary representation of an unsigned integer,
void BinaryDisplay(unsigned int num) {
	int len = GetBitLength(num);
	for (int i = len-1; i >= 0; i--) {
		printf("%d", (num>>i)&1);
	}
	printf("\n");
}

/*
* Searches for a binary pattern inside a number.
* Returns a bitmask with 1s at all positions (by LSB index)
* where the pattern is found.
*/
unsigned int Pattern_Check(unsigned int num, unsigned int pat) {
	int num_len = GetBitLength(num);
	int pat_len = GetBitLength(pat);

	if (pat_len > num_len) return 0;

	unsigned int positions = 0;
	unsigned int mask = (1U << pat_len) - 1;

	for (int i = 0; i < num_len - pat_len+1; i++) {
		unsigned int extracted = (num >> i) & mask;
		if (extracted == pat) {
			positions |= (1U << i);
		}
	}
	return positions;
}

// Runs one test case: displays the number, pattern, and all match positions.
void RunExample(unsigned int num, unsigned int pat, int index) {
	printf("=== Example %d ===\n", index);
	printf("Number:  ");
	BinaryDisplay(num);
	printf("Pattern: ");
	BinaryDisplay(pat);

	unsigned int matches = Pattern_Check(num, pat);
	printf("Pattern Positions (LSB): ");
	if (matches) {
		for (int i = 0; i < GetBitLength(num); i++) {
			if (matches & (1U << i)) printf("%d ", i);
		}
		printf("\n");
	}
	else {
		printf("Not Found.\n");
	}
	printf("\n");
}

// Entry point: runs multiple test cases.
int main() {
	unsigned int num[]= { 0b100100, 0b101101101, 0b11111111, 0b10000001 ,0b0 ,0b10101010 };
	unsigned int pat[] = { 0b100 ,0b101 ,0b11 ,0b1 ,0b1, 0b1010 };
	int examples_count = sizeof(num) / sizeof(unsigned int);
	unsigned int matches;
	
	for (int i = 0; i < examples_count; i++) {
		RunExample(num[i], pat[i], i + 1);
	}

	return 0;
}



