#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void show_board(char *gameboard) {
    printf("\nCurrent Board:");
    printf("\n %c | %c | %c\n", gameboard[0], gameboard[1], gameboard[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gameboard[3], gameboard[4], gameboard[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n\n", gameboard[6], gameboard[7], gameboard[8]);
}

void player_move(int player_choice, char *gameboard, char player_mark) {
    gameboard[player_choice] = player_mark;
}

void computer_move(char *gameboard, char computer_mark) {
    int status = 0;
    int computer_pos;

    do {
        computer_pos = rand() % 9;
    } while (gameboard[computer_pos] != ' ');

    gameboard[computer_pos] = computer_mark;
}

int is_board_full(char *gameboard) {
    for (int i = 0; i < 9; i++) {
        if (gameboard[i] == ' ') {
            return 1; // not full
        }
    }
    return 0; // full
}

char check_win(char *gameboard) {
    // Rows
    if (gameboard[0] == gameboard[1] && gameboard[1] == gameboard[2] && gameboard[0] != ' ') return gameboard[0];
    if (gameboard[3] == gameboard[4] && gameboard[4] == gameboard[5] && gameboard[3] != ' ') return gameboard[3];
    if (gameboard[6] == gameboard[7] && gameboard[7] == gameboard[8] && gameboard[6] != ' ') return gameboard[6];

    // Columns
    if (gameboard[0] == gameboard[3] && gameboard[3] == gameboard[6] && gameboard[0] != ' ') return gameboard[0];
    if (gameboard[1] == gameboard[4] && gameboard[4] == gameboard[7] && gameboard[1] != ' ') return gameboard[1];
    if (gameboard[2] == gameboard[5] && gameboard[5] == gameboard[8] && gameboard[2] != ' ') return gameboard[2];

    // Diagonals
    if (gameboard[0] == gameboard[4] && gameboard[4] == gameboard[8] && gameboard[0] != ' ') return gameboard[0];
    if (gameboard[2] == gameboard[4] && gameboard[4] == gameboard[6] && gameboard[2] != ' ') return gameboard[2];

    return ' ';
}

int main() {
    srand(time(NULL));
    int player_choice;
    char gameboard[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player_mark;
    char computer_mark;
    char winner = check_win(gameboard);

    printf("Choose your marker (o/x): ");
    scanf(" %c", &player_mark);
    if (player_mark == 'x') {
        computer_mark = 'o';
    } else if (player_mark == 'o') {
        computer_mark = 'x';
    } else {
        printf("INVALID MARKER!!");
        return 1;
    }
    show_board(gameboard);
    do {
        if(is_board_full(gameboard) == 0) {
            printf("\nIT'S A DRAW!!\n");
            break;
        }

        printf("Choose your position (1-9): ");
        scanf("%d", &player_choice);

        if (player_choice < 1 || player_choice > 9) {
            printf("INVALID MOVE!! Try again\n");
            continue;
        } 

        player_choice--;

        if (gameboard[player_choice] != ' ') {
            printf("INVALID MOVE!! Try again\n");
            continue;
        }

        player_move(player_choice, gameboard, player_mark);
        winner = check_win(gameboard);
        if (winner == player_mark) {
            show_board(gameboard);
            printf("\nYOU WIN!!\n");
            break;
        }

        computer_move(gameboard, computer_mark);
        winner = check_win(gameboard);
        if (winner == computer_mark) {
            show_board(gameboard);
            printf("\nYOU LOSE!!\n");
            break;
        }
        
        show_board(gameboard);
    } while (winner == ' ');

    return 0;
}

