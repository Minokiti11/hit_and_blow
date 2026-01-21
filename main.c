#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char player[100];
    int turn;
    int hit;
    int blow;
}guess;

/* TODO: 回答を生成 */
void generate_randomAnswer(int answer[4]) {
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++) {
        int j = rand() % 9;
        int temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
    }
    for (int i = 0; i < 4; i++) {
        answer[i] = digits[i];
    }
}

/* ヒットの数を返す*/
int hit_count(int answer[], int guess[]) {
    int hit = 0;
    for (int i = 0; i < 4; i++) {
        if (answer[i] == guess[i]) {
            hit++;
        }
    }
    return hit;
}

/* ブローの数を返す*/
int blow_count(int answer[], int guess[]) {
    int blow = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j && answer[i] == guess[j]) {
                blow++;
            }
        }
    }
    return blow;
}

void insert_guess(guess *g[], char player_name[], int turn, int hit, int blow) {
    if (turn < 1 || turn > 100) {
        return;
    }
    if (g[turn - 1] == NULL) {
        g[turn - 1] = malloc(sizeof(guess));
        if (g[turn - 1] == NULL) {
            fprintf(stderr, "Failed to allocate guess history.\n");
            exit(1);
        }
    }
    g[turn - 1]->turn = turn;
    strcpy(g[turn - 1]->player, player_name);
    g[turn - 1]->hit = hit;
    g[turn - 1]->blow = blow;
}


/* これまでの履歴を表示*/
void print_guess_history(guess *g[]) {
    printf("-Guess History:---------------------------------\n");
    for (int i = 0; i < 100; i++) {
        if (g[i] != NULL) {
            int player_name_spaces = strlen(g[i]->player);
            int num_spaces = 11 - player_name_spaces;
            printf("| Turn %d - Player: %s, Hit: %d, Blow: %d", g[i]->turn, g[i]->player, g[i]->hit, g[i]->blow);
            for (int j = 0; j < num_spaces; j++) {
                printf(" ");
            }
            printf("|\n");
        }
    }
    printf("------------------------------------------------\n");
}

int main() {
    srand((unsigned)time(NULL));
    int current_turn = 1; /* odd: Player1, even: Player2 */
    guess *guesses[100]; /* 最大100ターン分の履歴を保存可能 */
    for (int i = 0; i < 100; i++) {
        guesses[i] = NULL;
    }

    char player1_name[100];
    char player2_name[100];
    char current_player_name[100];
    printf("Enter Player1's name(maximum 10 characters): ");
    scanf("%s", player1_name);/*p1の名前*/
    while (strlen(player1_name) > 10) {
        printf("Name too long. Please enter a name with a maximum of 10 characters: ");
        scanf("%s", player1_name);
    }
    printf("Enter Player2's name: ");
    scanf("%s", player2_name);/*p2の名前*/
    while (strlen(player2_name) > 10) {
        printf("Name too long. Please enter a name with a maximum of 10 characters: ");
        scanf("%s", player2_name);
    }

    printf("Generating Answer...\n");

    int answer[4] = {}; /* ４桁のランダムな数字を生成 （同じ数字の桁がないように） */
    generate_randomAnswer(answer);

    /* Game Loop */
    while (1) {
        if (current_turn % 2 == 1) {
            printf("%s's turn\n", player1_name);
            strcpy(current_player_name, player1_name);
        } else {
            printf("%s's turn\n", player2_name);
            strcpy(current_player_name, player2_name);
        }

        printf("Enter your guess(Example: 1 2 3 4): ");
        int guess[4];
        scanf("%d %d %d %d", &guess[0], &guess[1], &guess[2], &guess[3]);
        printf("Guess: %d%d%d%d\n", guess[0], guess[1], guess[2], guess[3]);

        insert_guess(guesses, current_player_name, current_turn, hit_count(answer, guess), blow_count(answer, guess));

        print_guess_history(guesses);

        if (guess[0] == answer[0] && guess[1] == answer[1] && guess[2] == answer[2] && guess[3] == answer[3]) {
            printf("You win!\n");
            break;
        }
        current_turn++;
    }

    for (int i = 0; i < 100; i++) {
        free(guesses[i]);
    }

    return 0;
}
