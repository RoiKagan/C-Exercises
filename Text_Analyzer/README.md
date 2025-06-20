# 📊 Text Analyzer in C

This program reads a text file and analyzes it by:

- Counting total **words** and **sentences**
- Tracking the frequency of **each letter** (A–Z, case-insensitive)
- Tracking the frequency of **each digit** (0–9)

## 🔧 Features

- Ignores punctuation and symbol typos (e.g., `!!!`, `$$$`, `@#%`)
- Handles contractions and missing spaces after punctuation
- Case-insensitive letter analysis (e.g., `A` and `a` are the same)

## 📂 Usage

1. Create a `sample.txt` file in the same directory, or use the one provided.
2. Compile and run the program using a C compiler:
   ```bash
   gcc Text_Analyzer.c -o Text_Analyzer
   ./Text_Analyzer