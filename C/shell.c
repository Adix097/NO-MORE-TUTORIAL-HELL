#include <stdio.h>
#include <direct.h>
#include <string.h>

#define MAX_TOKENS 10
#define MAX_TOKEN_LEN 50
#define BUFFER_SIZE 1024

typedef struct {
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int token_count;
} Token_list;

Token_list parse_cmd(char *cmd) {
    Token_list list;
    list.token_count = 0;
    char *token = strtok(cmd, " ");
    while (token != NULL && list.token_count < MAX_TOKENS) {
        strncpy(list.tokens[list.token_count], token, MAX_TOKEN_LEN - 1);
        list.tokens[list.token_count][MAX_TOKEN_LEN - 1] = '\0';
        list.token_count++;
        token = strtok(NULL, " ");
    }
    return list;
}

char* remove_quotes(char *string) {
    int read = 0;
    int write = 0;
    while(string[read] != '\0') {
        if(string[read] != '"') {
            string[write++] = string[read];
        }
        read++;
    }
    string[write] = '\0';
    return string;
}


// echo command needs error handling
void echo (Token_list *cmd) {
    for (int i = 1; i < cmd->token_count; i++) {
        remove_quotes(cmd->tokens[i]);        
        printf("%s", cmd->tokens[i]);         
        if (i < cmd->token_count - 1) printf(" ");
    }
    printf("\n");
}

void cwd() {
    char path[BUFFER_SIZE];
    if (getcwd(path, sizeof(path)) != NULL) {
        printf("%s\n", path);
    } else {
        printf("cannot get path!");
    }
}

int main() {
    char cmd[BUFFER_SIZE];

    while (1) {
        printf("\n> ");
        fflush(stdout);
        if (!fgets(cmd, sizeof(cmd), stdin)) {
            clearerr(stdin);
            continue;
        }

        // loop conditions
        cmd[strcspn(cmd, "\n")] = 0;
        if (cmd[0] == '\0') continue;
        if (strcmp(cmd, "quit") == 0) break;

        Token_list parsed_cmd = parse_cmd(cmd);

        // adding echo command
        if (strcmp(parsed_cmd.tokens[0], "echo") == 0) {
            echo(&parsed_cmd);
        }

        // adding cwd command
        if (strcmp(parsed_cmd.tokens[0], "cwd") == 0) {
            if (parsed_cmd.token_count != 1) {
                printf("ERROR!");
            }
            cwd();
        }
    }

    return 0;
}