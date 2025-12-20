#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

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

void echo (Token_list *cmd) {
    for (int i = 1; i < cmd->token_count; i++) {      
        printf("%s", cmd->tokens[i]);         
        if (i < cmd->token_count - 1) printf(" ");
    }
    printf("\n");
}

void cwd() {
    char path[BUFFER_SIZE];
    if (getcwd(path, sizeof(path)) != NULL) {
        printf("\033[32m%s\033[0m\n", path);
    } else {
        printf("cannot get path!");
    }
}

void ls(char* flag) {
    DIR *dir;
    struct dirent *ent;

    dir = opendir(".");
    if (strcmp(flag, "-a") == 0) {
        while((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent -> d_name);
        }
    }
    if (strcmp(flag, "*.c") == 0) {
        while ((ent = readdir(dir)) != NULL) {
            if ((strcmp(ent -> d_name + strlen(ent -> d_name) - strlen(".c"), ".c")) == 0) {
                printf("%s\n", ent -> d_name);
            }
        }
    } else if (strcmp(flag, "*.exe") == 0) {
        while ((ent = readdir(dir)) != NULL) {
            if ((strcmp(ent -> d_name + strlen(ent -> d_name) - strlen(".exe"), ".exe")) == 0) {
                printf("%s\n", ent -> d_name);
            }
        }
    }
    closedir(dir);
}

void touch(Token_list *cmd) {
    FILE *file_ptr = NULL;
    file_ptr = fopen(cmd->tokens[1], "w");
    if (file_ptr == NULL) {
        printf("\033[31mFile cannot be created\033[0m\n");
    } else {
        printf("File created successfully!\n");
    }
    fclose(file_ptr);
}

void rm(char* file_name) {
    int status = remove(file_name);
    if (status == 0) {
        printf("File successfully deleted.\n");
    } else {
        printf("\033[31mNo such file exists.\033[0m\n");
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

        if (strcmp(parsed_cmd.tokens[0], "echo") == 0) {
            echo(&parsed_cmd);
        } else if (strcmp(parsed_cmd.tokens[0], "cwd") == 0) {
            if (parsed_cmd.token_count != 1) {
                printf("\033[31mERROR\033[0m\n");
            } else {
                cwd();
            }
        } else if (strcmp(parsed_cmd.tokens[0], "ls") == 0) { 
            if (strcmp(parsed_cmd.tokens[1], "-a") == 0) {
                ls("-a");
            } else if (strcmp(parsed_cmd.tokens[1], "*.c") == 0) {
                ls("*.c");
            } else if (strcmp(parsed_cmd.tokens[1], "*.exe") == 0) {
                ls("*.exe");
            } else if (parsed_cmd.token_count == 1) {
                printf("\033[31mNO FLAG SPECIFIED\033[0m\n");
            } else {
                printf("\033[31mINVALID FLAG\033[0m\n");
            }
        } else if (strcmp(parsed_cmd.tokens[0], "touch") == 0) {
            if (parsed_cmd.token_count == 2) {
                touch(&parsed_cmd);
            } else {
                printf("\033[31mMention name of the file\033[0m\n");
            }
        } else if (strcmp(parsed_cmd.tokens[0], "rm") == 0) {
            rm(parsed_cmd.tokens[1]);
        } else {
            printf("\033[31mINVALID COMMAND\033[0m\n");
        }
    }

    return 0;
}