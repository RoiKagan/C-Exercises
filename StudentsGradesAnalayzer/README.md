#  Student Grades Analyzer

This program allows you to:

-  Input student names, IDs, and exam grades  
-  Save all data into a structured **CSV file**  
-  Load student records from the file  
-  Calculate **per-student averages** and an **overall average**  
-  Identify students **above** or **below** the overall average  

---

##  How to Use

### 1. Compile the Program

Using GCC:

```bash
gcc -o StudentGradesAnalyzer StudentGradesAnalyzer.c
```

2. Run the Program
```bash
./StudentGradesAnalyzer
```

- Choose whether to enter new data (Y) or load from the file (N).

- **If you choese Y:** Follow the prompts to enter student information.

- **If you choese N:** You can use the provided sample file (Students_Grades.csv) in this folder to test the program without entering new data manually, or create a file according to the format described in the **CSV Input Format** section below.



## CSV Input Format
### File Name:
 Students_Grades.csv

### Each row format:

| Name       | ID        | Exam Taken | Exam Number | Grade |
|------------|-----------|------------|--------------|-------|

### Example:

| Name       | ID        | Exam Taken | Exam Number | Grade |
|------------|-----------|------------|--------------|-------|
| John       | '1234567' | 2          | 1            | 88    |
| John        | '1234567' | 2          | 2            | 92    |
| Paul      | '2468101' | 1          | 1            | 100    |