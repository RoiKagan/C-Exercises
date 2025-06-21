## 🧩 Bit Pattern Matcher

This C program checks whether a given binary **pattern** appears in a given **number**, and returns a **bitmask** marking all matching positions (indexed from the least significant bit).

### Example Output

Number : 101101101
Pattern : 101
Pattern Positions (LSB): 0 2

### Key Functions
- `Pattern_Check(num, pat)` – returns bitmask of all match positions
- `BinaryDisplay(num)` – prints a number in binary

## How to run

1. Compile the program:
```bash
gcc -o BinaryPatternSearch BinaryPatternSearch.c
```
2. Run the program:
```bash
./BinaryPatternSearch
```
