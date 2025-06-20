/*
 ============================================================================
 Description :
   A C program that reads and analyzes the contents of a text file ("sample.txt").
   It performs the following operations:
	 - Counts the number of words in the file
	 - Counts the number of sentences (based on '.', '!', or '?')
	 - Counts the frequency of each letter (A–Z, case-insensitive)
	 - Counts the frequency of each digit (0–9)

   Notes:
	 - Words are separated by any non-letter/non-digit characters.
	 - Sentences are counted only when a word starts after a sentence-ending punctuation.
	 - Sequences like "!!!", "...", or "??!!" do not count as words and only count as one sentence (if followed by a new word).
	 - The file must be in the same folder as the executable.
 ============================================================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "sample.txt"
#define ALPHABET_LEN 26
#define NUMBERS_LEN 10


// Analyzes a text file: counts words, sentences, letters (case-insensitive), and digits.
void text_analyzer(FILE* file, int* sentences_counter, int* words_counter, int* letter_counter, int *number_counter) {
	// Initialize counters
	*sentences_counter = *words_counter = 0;
	for (int i = 0; i < ALPHABET_LEN; i++) {
		letter_counter[i] = 0;
	}
	for (int i = 0; i < NUMBERS_LEN; i++) {
		number_counter[i] = 0;
	}

	int c;
	int word_finished_flag = 1;
	int sentence_finished_flag=1;

	while ((c = fgetc(file)) != EOF) {
		// If current char is a letter or digit (not punctuation or whitespace)
		if (!((c >= 32 && c <= 47) || (c >= 58 && c <= 64) ||
			(c >= 91 && c <= 96) || (c >= 123 && c <= 126)||c==10)) {

			// If the last word ended, this starts a new word
			if (word_finished_flag) {
				(*words_counter)++;	
				
				// If the last sentence ended, this starts a new sentence
				if ((sentence_finished_flag))  (*sentences_counter)++;
				word_finished_flag = sentence_finished_flag = 0;
			}

			// Count digits
			if (c >= '0' && c <= '9') number_counter[c - '0']++;

			// Count letters (case-insensitive)
			if (c >= 'A' && c <= 'Z') letter_counter[c - 'A']++; // uppercase letter (A–Z)
			if (c >= 'a' && c <= 'z') letter_counter[c - 'a']++; // lowercase letter (a–z)
		}
		else {
			word_finished_flag = 1;

			// If current character ends a sentence
			if (c == '!' || c == '.' || c == '?') sentence_finished_flag = 1;
		}
	}
}

int main() {
	FILE* file = fopen(FILE_NAME, "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}
	int sentences_counter, words_counter;
	int letter_counter[ALPHABET_LEN];
	int number_counter[NUMBERS_LEN];
	text_analyzer(file, &sentences_counter, &words_counter, letter_counter, number_counter);
	
	printf("=== Letter Frequencies ===\n");
	for (int i = 0; i < ALPHABET_LEN; i++) 
		printf("%c: %d\n", i + 65, letter_counter[i]);

	printf("\n=== Number Frequencies ===\n");
	for (int i = 0; i < NUMBERS_LEN; i++)
		printf("%d: %d\n", i, number_counter[i]);

	printf("\n=== Summary ===\n");
	printf("Total words: %d\n", words_counter);
	printf("Total sentences: %d\n", sentences_counter);

	fclose(file);
	return 0;
}