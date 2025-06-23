/*
============================================
STUDENT GRADES ANALYZER

This C program allows you to:
- Input student names, IDs, and exam grades
- Save the data in a CSV file
- Read student data from an existing CSV
- Calculate average grades per student and overall
- Categorize students as above or below average

============================================
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "Students_Grades.csv"
#define MAX_NAME_LENGTH 20
#define ID_LENGTH 15

// Structure to hold individual student data
typedef struct {
	char Name[MAX_NAME_LENGTH];
	char ID[ID_LENGTH];
	int Exams_Taken;
	int* Grades;
} StudentData;

typedef struct {
	char Name[MAX_NAME_LENGTH];
	char ID[ID_LENGTH];
	float ave;
} StudentSummarizedData;

// Structure to hold overall statistics
typedef struct {
	StudentSummarizedData* above_ave;
	StudentSummarizedData* below_ave;
	int above_ave_size;
	int below_ave_size;
	double overall_ave;
} Statistics;

//Allows user to enter student information via console.
StudentData* InputData(int stdnt_num) {
	StudentData* students = (StudentData*)malloc(stdnt_num * sizeof(StudentData));
	if (!students) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	for (int i = 0; i < stdnt_num; i++) {
		printf("Student %d Name: ",i+1);
		scanf("%s", students[i].Name);

		printf("Student %d ID: ",i+1);
		scanf("%s", students[i].ID);

		printf("Number of exams Taken by student %d: ", i + 1);
		scanf("%d", &students[i].Exams_Taken);

		students[i].Grades = (int*)malloc(students[i].Exams_Taken * sizeof(int));
		if (!students[i].Grades) {
			printf("Memory allocation failed for grades.\n");
			exit(1);
		}

		for (int exam = 0; exam < students[i].Exams_Taken; exam++) {
			printf("Student %d exam %d grade: ", i + 1, exam+1);
			scanf("%d", &students[i].Grades[exam]);
		}
		printf("\n");
	}
	return students;
}

//Writes student data into a CSV file.
int WriteCSV(StudentData* students, int stdnt_num){
	FILE* fp = fopen(FILE_NAME, "w");
	if (!fp) {
		printf("Error: Could not open file %s\n", FILE_NAME);
		return;
	}
	fprintf(fp, "Name,ID,Exam Taken,Exam Number,Grade\n");
	for (int i = 0; i < stdnt_num; i++) {
		for (int exam = 0; exam < students[i].Exams_Taken; exam++) {
			fprintf(fp, "%s,'%s',%d, %d, %d\n",
				students[i].Name,
				students[i].ID,
				students[i].Exams_Taken,
				exam+1,
				students[i].Grades[exam]);
		}
	}

	fclose(fp);
	return stdnt_num;
}

//Reads student data from a CSV file.
StudentData* ReadCSV(int* stdnt_num) {
	FILE* fp = fopen(FILE_NAME, "r");
	if (!fp) {
		printf("Error: Could not open file %s\n", FILE_NAME);
		return NULL;
	}

	char temp_name[MAX_NAME_LENGTH];
	char temp_id[ID_LENGTH];
	int temp_exams_taken, temp_exam_num, temp_grade;

	*stdnt_num = 0;
	fscanf(fp, "%*[^\n]\n"); // Skip header line

	while (fscanf(fp, "%[^,],%[^,],%d,%d,%d\n",
		temp_name, temp_id,
		&temp_exams_taken, &temp_exam_num,
		&temp_grade)==5) {
		if (temp_exam_num == 1) (*stdnt_num)++;
	}
	fclose(fp);

	fp = fopen(FILE_NAME, "r");
	fscanf(fp, "%*[^\n]\n"); // Skip header line

	StudentData* students = (StudentData*)malloc(*stdnt_num * sizeof(StudentData));
	for (int i = 0; i < *stdnt_num;i++) {
		fscanf(fp, "%[^,],%[^,],%d,%d,%d\n",
			students[i].Name, 
			students[i].ID,
			&students[i].Exams_Taken,
			&temp_exam_num,
			&temp_grade);

		students[i].Grades= (int*)malloc(students[i].Exams_Taken * sizeof(int));
		students[i].Grades[0] = temp_grade;

		for (int exam = 1; exam < students[i].Exams_Taken; exam++) {
			fscanf(fp, "%[^,],%[^,],%d,%d,%d\n",
				temp_name, temp_id,
				&temp_exams_taken, &temp_exam_num,
				&students[i].Grades[exam]);
		}
	}
	fclose(fp);
	return students;
}

//Calculates average grades and categorizes students into above/below average.
Statistics GradesStatistic(StudentData* students, int stdnt_num) {
	Statistics stat;
	double* averages = (double*)malloc(stdnt_num * sizeof(double));
	int total_exams = 0;
	double total_sum = 0;

	stat.overall_ave = 0;
	int overall_exam_number = 0;
	for (int i = 0; i < stdnt_num; i++) {
		averages[i] = 0;
		for (int exam = 0; exam < students[i].Exams_Taken; exam++) {
			averages[i] += students[i].Grades[exam];
			total_sum += students[i].Grades[exam];
			total_exams++;
		}
		averages[i] /= (double)students[i].Exams_Taken;
	}
	stat.overall_ave = (double)total_sum / total_exams;

	stat.above_ave_size = stat.below_ave_size = 0;
	for (int i = 0; i < stdnt_num; i++) {
		if (averages[i] >= stat.overall_ave) stat.above_ave_size++;
		else stat.below_ave_size++;
	}

	stat.above_ave = (StudentSummarizedData*)malloc(stat.above_ave_size * sizeof(StudentSummarizedData));
	stat.below_ave = (StudentSummarizedData*)malloc(stat.below_ave_size * sizeof(StudentSummarizedData));

	int above_idx = 0, below_idx = 0;
	for (int i = 0; i < stdnt_num; i++) {
		if (averages[i] >= stat.overall_ave) {
			stat.above_ave[above_idx].ave = averages[i];
			strncpy(stat.above_ave[above_idx].Name, students[i].Name, MAX_NAME_LENGTH);
			strncpy(stat.above_ave[above_idx].ID, students[i].ID, ID_LENGTH);
			above_idx++;
		}

		else{
			stat.below_ave[below_idx].ave = averages[i];
			strncpy(stat.below_ave[below_idx].Name, students[i].Name, MAX_NAME_LENGTH);
			strncpy(stat.below_ave[below_idx].ID, students[i].ID, ID_LENGTH);
			below_idx++;
		}
	}
	free(averages);
	return stat;
}


int main() {
	char choice;
	StudentData* students;
	Statistics stat;
	int stdnt_num;

	printf("Does the file %s already exist?(Y/N) ", FILE_NAME);
	do {
		scanf(" %c", &choice);
		if (choice != 'Y' && choice != 'N') 
			printf("Please enter Y/N: ");
	} while (choice != 'Y' && choice != 'N');
	

	if (choice == 'Y') {
		printf("Number of students: ");
		scanf("%d", &stdnt_num);
		students = InputData(stdnt_num);
		WriteCSV(students, stdnt_num);
	}
	else {
		students = ReadCSV(&stdnt_num);
	}

	stat=GradesStatistic(students, stdnt_num);

	printf("\n== Detailed Statistics ==\n");
	printf("Total students: %d\n", stdnt_num);
	printf("Overall average grade: %.2f\n", stat.overall_ave);

	printf("\n--- %d Students Above Average ---\n",stat.above_ave_size);
	for (int i = 0; i < stat.above_ave_size; i++) {
		printf("Name: %-20s | ID: %-15s | Average: %.2f\n",
			stat.above_ave[i].Name,
			stat.above_ave[i].ID,
			stat.above_ave[i].ave);
	}

	printf("\n--- %d Students Below Average ---\n", stat.below_ave_size);
	for (int i = 0; i < stat.below_ave_size; i++) {
		printf("Name: %-20s | ID: %-15s | Average: %.2f\n",
			stat.below_ave[i].Name,
			stat.below_ave[i].ID,
			stat.below_ave[i].ave);
	}

	for (int i = 0; i < stdnt_num; i++) {
		free(students[i].Grades);
	}
	free(students);
	free(stat.above_ave);
	free(stat.below_ave);

	return 0;
}