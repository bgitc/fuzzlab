#include <stdio.h>
#include <string.h>

#define MAX_ENTRY_SIZE 16
#define MAX_LINE 256

void add_expense(char *line) {
    char entry[MAX_ENTRY_SIZE];
    
    strcpy(entry, line);
    
    printf("Added expense: %s\n", entry);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <ledger_file>\n", argv[0]);
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Cannot open %s\n", argv[1]);
        return 1;
    }
    
    char line[MAX_LINE] = {0};
    if (fgets(line, MAX_LINE, fp)) {
        line[strcspn(line, "\n")] = 0;
        add_expense(line);
    }
    
    fclose(fp);
    return 0;
}
