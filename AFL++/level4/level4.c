#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFFER_SIZE 32
#define LOG_FILE "log_level4.txt"
#define MAX_LOG_MSG 256
#define MAX_INPUT_SIZE 1024

typedef struct {
    int initialized;
    char system_name[50];
    time_t start_time;
    int operation_count;
    int error_count;
} SystemState;

typedef struct {
    int alpha_count;
    int digit_count;
    int special_count;
    int total_length;
} InputStats;

void write_log(const char *message) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp) {
        fprintf(fp, "[%ld] %s\n", time(NULL), message);
        fclose(fp);
    }
}

void init_system_state(SystemState *state) {
    state->initialized = 1;
    strcpy(state->system_name, "level4System");
    state->start_time = time(NULL);
    state->operation_count = 0;
    state->error_count = 0;
    printf("System initialized: %s at %ld\n", state->system_name, state->start_time);
    write_log("System initialized");
}

int check_input_length(char *input) {
    int len = strlen(input);
    char log_msg[MAX_LOG_MSG];
    snprintf(log_msg, MAX_LOG_MSG, "Input length: %d", len);
    write_log(log_msg);
    printf("Input length: %d\n", len);
    return len;
}

void analyze_first_char(char *input) {
    char log_msg[MAX_LOG_MSG];
    if (input[0] == '\0') {
        snprintf(log_msg, MAX_LOG_MSG, "Empty input detected");
        write_log(log_msg);
        printf("Empty input detected\n");
        return;
    }
    if (isalpha(input[0])) {
        snprintf(log_msg, MAX_LOG_MSG, "First char is alphabetic: %c", input[0]);
        write_log(log_msg);
        printf("First char is alphabetic: %c\n", input[0]);
    } else if (isdigit(input[0])) {
        snprintf(log_msg, MAX_LOG_MSG, "First char is numeric: %c", input[0]);
        write_log(log_msg);
        printf("First char is numeric: %c\n", input[0]);
    } else {
        snprintf(log_msg, MAX_LOG_MSG, "First char is special: %c", input[0]);
        write_log(log_msg);
        printf("First char is special: %c\n", input[0]);
    }
}

void calculate_input_stats(char *input, InputStats *stats) {
    int i;
    stats->alpha_count = 0;
    stats->digit_count = 0;
    stats->special_count = 0;
    stats->total_length = strlen(input);
    
    for (i = 0; i < stats->total_length; i++) {
        if (isalpha(input[i])) stats->alpha_count++;
        else if (isdigit(input[i])) stats->digit_count++;
        else stats->special_count++;
    }
    
    printf("Input Stats - Alpha: %d, Digit: %d, Special: %d, Length: %d\n",
           stats->alpha_count, stats->digit_count, stats->special_count, stats->total_length);
    char log_msg[MAX_LOG_MSG];
    snprintf(log_msg, MAX_LOG_MSG, "Stats - Alpha: %d, Digit: %d, Special: %d, Length: %d",
             stats->alpha_count, stats->digit_count, stats->special_count, stats->total_length);
    write_log(log_msg);
}

void transform_input(char *input) {
    int i;
    for (i = 0; i < strlen(input); i++) {
        if (islower(input[i])) {
            input[i] = toupper(input[i]);
        }
    }
    printf("Transformed input: %s\n", input);
    write_log("Input transformed to uppercase");
}

void analyze_pattern(char *input) {
    int i;
    for (i = 0; i < strlen(input) - 1; i++) {
        if (input[i] == input[i + 1]) {
            printf("Repeated char at position %d: %c\n", i, input[i]);
            char log_msg[MAX_LOG_MSG];
            snprintf(log_msg, MAX_LOG_MSG, "Repeated char at %d: %c", i, input[i]);
            write_log(log_msg);
        }
    }
}

int compute_hash(char *input) {
    int hash = 0, i;
    for (i = 0; i < strlen(input); i++) {
        hash += input[i];
    }
    printf("Computed hash: %d\n", hash % 100);
    char log_msg[MAX_LOG_MSG];
    snprintf(log_msg, MAX_LOG_MSG, "Hash computed: %d", hash % 100);
    write_log(log_msg);
    return hash % 100;
}

void check_system_status(SystemState *state) {
    printf("Checking system status...\n");
    if (state->initialized) {
        printf("System is initialized, operations: %d, errors: %d\n",
               state->operation_count, state->error_count);
        write_log("System status: Initialized");
    } else {
        printf("System not initialized!\n");
        write_log("System status: Not initialized");
    }
}

void process_data(char *input) {
    char buffer[MAX_BUFFER_SIZE];
    int i, j, hash = 0;

    if (!input || input[0] == '\0') {
        printf("Invalid input, skipping processing\n");
        write_log("Invalid input detected in process_data");
        return;
    }
    
    for (i = 0; i < strlen(input); i++) {
        hash += input[i];
        for (j = 0; j < 5; j++) {
            hash ^= (input[i] << j);
        }
    }
    
    if (strncmp(input, "secret", 6) == 0 && strlen(input) > 40) {
        memcpy(buffer, input, strlen(input));
        printf("Processed secret data: %s\n", buffer);
        write_log("Secret data processed (vulnerable path)");
    } else {
        strncpy(buffer, input, MAX_BUFFER_SIZE - 1);
        buffer[MAX_BUFFER_SIZE - 1] = '\0';
        printf("Processed safe data: %s\n", buffer);
        write_log("Safe data processed");
    }
}

int validate_input(char *input, SystemState *state) {
    if (!input || input[0] == '\0') {
        printf("Error: Empty or null input detected.\n");
        write_log("Empty or null input detected");
        state->error_count++;
        return 0;
    }
    write_log("Input validated successfully");
    return 1;
}

void simulate_load() {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("Simulating load %d-%d\n", i, j);
            write_log("Load simulation step");
        }
    }
}

void detailed_analysis(char *input) {
    int i;
    for (i = 0; i < strlen(input); i++) {
        printf("Detailed char %d: %c (ASCII %d)\n", i, input[i], input[i]);
        char log_msg[MAX_LOG_MSG];
        snprintf(log_msg, MAX_LOG_MSG, "Detailed char %d: %c (ASCII %d)", i, input[i], input[i]);
        write_log(log_msg);
    }
}


void process_file(char *filename, SystemState *state, InputStats *stats) {
    FILE *fp = fopen(filename, "r");
    char input[MAX_INPUT_SIZE] = {0};
    
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        write_log("File open failed");
        return;
    }
    
    if (fgets(input, MAX_INPUT_SIZE, fp)) {
        input[strcspn(input, "\n")] = 0;
        state->operation_count++;
        printf("Read from file: %s\n", input);
        write_log("File read successful");
        
        if (validate_input(input, state)) {
            check_input_length(input);
            calculate_input_stats(input, stats);
            analyze_first_char(input);
            analyze_pattern(input);
            compute_hash(input);
            detailed_analysis(input);
            process_data(input);
            simulate_load();
        }
    } else {
        printf("Error: Failed to read file content\n");
        write_log("File read failed");
        state->error_count++;
    }
    
    fclose(fp);
}

void process_input_wrapper(char *filename, SystemState *state, InputStats *stats) {
    printf("Starting input processing...\n");
    write_log("Input processing started");
    check_system_status(state);
    process_file(filename, state, stats);
}

void initialize_system(SystemState *state) {
    printf("Initializing system...\n");
    init_system_state(state);
    write_log("System initialization complete");
    printf("System ready to process input.\n");
}

void shutdown_system(SystemState *state) {
    printf("Shutting down system...\n");
    printf("Operations: %d, Errors: %d\n", state->operation_count, state->error_count);
    write_log("System shutdown initiated");
    state->initialized = 0;
    printf("System shutdown complete.\n");
}

int main(int argc, char *argv[]) {
    SystemState state = {0};
    InputStats stats = {0};
    
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        write_log("No filename provided");
        return 1;
    }
    
    initialize_system(&state);
    process_input_wrapper(argv[1], &state, &stats);
    shutdown_system(&state);
    return 0;
}
