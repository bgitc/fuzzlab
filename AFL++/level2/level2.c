#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTS 10

typedef struct {
    int type;
    union {
        int int_value;
        char *str_value;
        float float_value;
    } data;
} Element;

int parse_elements(FILE *file, Element *elements, int max_count) {
    int count = 0;
    unsigned char type;

    while (count < max_count && fread(&type, 1, 1, file) == 1) {
        elements[count].type = type & 0x0F;

        switch (elements[count].type) {
            case 1:
                fread(&elements[count].data.int_value, sizeof(int), 1, file);
                break;

            case 2: {
                unsigned char len;
                fread(&len, 1, 1, file);
                elements[count].data.str_value = (char *)malloc(len + 1);
                if (elements[count].data.str_value && len > 0) {
                    fread(elements[count].data.str_value, 1, len, file);
                    elements[count].data.str_value[len] = '\0';
                } else {
                    if (elements[count].data.str_value) elements[count].data.str_value[0] = '\0';
                }
                break;
            }

            case 3:
                fread(&elements[count].data.float_value, sizeof(float), 1, file);
                break;

            default:
                if ((type >> 4) > 0) {
                    int special_len = (type >> 4) * 10;
                    char *special_buffer = (char *)malloc(special_len);
                    elements[count].data.str_value = (char *)malloc(20); // fixed size buffer
                    if (special_buffer && elements[count].data.str_value) {
                        fread(special_buffer, 1, special_len, file);
                        memcpy(elements[count].data.str_value, special_buffer,
                               special_len);  // overflows fixed 20-byte heap buffer
                        free(special_buffer);
                    }
                }
                break;
        }

        count++;
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        printf("Failed to open file.\n");
        return 1;
    }

    Element elements[MAX_ELEMENTS];
    int count = parse_elements(input, elements, MAX_ELEMENTS);

    for (int i = 0; i < count; i++) {
        switch (elements[i].type) {
            case 1:
                printf("INT: %d\n", elements[i].data.int_value);
                break;
            case 2:
            default:
                printf("STR: %s\n", elements[i].data.str_value ? elements[i].data.str_value : "(null)");
                if (elements[i].data.str_value) free(elements[i].data.str_value);
                break;
            case 3:
                printf("FLOAT: %f\n", elements[i].data.float_value);
                break;
        }
    }

    fclose(input);
    return 0;
}
