#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

typedef struct {
    char player[100];
    int turn;
    int hit;
    int blow;
    int predict[4];
}guess;

/* 回答を生成 */
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

void insert_guess(guess g[], char player_name[], int turn, int hit, int blow, int guess[4]) {
    if (turn < 1 || turn > 100) {
        return;
    }
    g[turn - 1].predict[0] = guess[0];
    g[turn - 1].predict[1] = guess[1];
    g[turn - 1].predict[2] = guess[2];
    g[turn - 1].predict[3] = guess[3];
    g[turn - 1].turn = turn;
    strcpy(g[turn - 1].player, player_name);
    g[turn - 1].hit = hit;
    g[turn - 1].blow = blow;
}


/* これまでの履歴を表示 */
void print_guess_history(guess g[]) {
    printf("-Guess History:---------------------------------\n");
    for (int i = 0; i < 100; i++) {
        if (g[i].player[0] != '\0') {
            int player_name_spaces = strlen(g[i].player);
            int num_spaces = 10 - player_name_spaces;
            printf("| Turn %d - guess %d %d %d %d, Hit: %d, Blow: %d", g[i].turn, g[i].predict[0], g[i].predict[1], g[i].predict[2], g[i].predict[3], g[i].hit, g[i].blow);
            for (int j = 0; j < num_spaces; j++) {
                printf(" ");
            }
            printf("|\n");
        }
    }
    printf("------------------------------------------------\n");
}

/* ASCIIアートで文字を表示（5行の高さ） */
void print_ascii_char(char c, int line) {
    c = toupper(c);
    
    const char *lines[5];
    switch(c) {
        case 'A':
            lines[0] = "  ▄▄▄   "; lines[1] = " ▀   ▀  "; lines[2] = " ▄▄▄▄▄  "; lines[3] = " ▀   ▀  "; lines[4] = " ▀   ▀  "; break;
        case 'B':
            lines[0] = " █████  "; lines[1] = " █   █  "; lines[2] = " █████  "; lines[3] = " █   █  "; lines[4] = " █████  "; break;
        case 'C':
            lines[0] = "  ▄▄▄▄  "; lines[1] = " █      "; lines[2] = " █      "; lines[3] = " █      "; lines[4] = "  ▀▀▀▀  "; break;
        case 'D':
            lines[0] = " █████  "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = " █   █  "; lines[4] = " █████  "; break;
        case 'E':
            lines[0] = " █████  "; lines[1] = " █      "; lines[2] = " █████  "; lines[3] = " █      "; lines[4] = " █████  "; break;
        case 'F':
            lines[0] = " █████  "; lines[1] = " █      "; lines[2] = " █████  "; lines[3] = " █      "; lines[4] = " █      "; break;
        case 'G':
            lines[0] = "  ▄▄▄▄  "; lines[1] = " █      "; lines[2] = " █  ███ "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀▀  "; break;
        case 'H':
            lines[0] = " █   █  "; lines[1] = " █   █  "; lines[2] = " █████  "; lines[3] = " █   █  "; lines[4] = " █   █  "; break;
        case 'I':
            lines[0] = " █████  "; lines[1] = "   █    "; lines[2] = "   █    "; lines[3] = "   █    "; lines[4] = " █████  "; break;
        case 'J':
            lines[0] = " █████  "; lines[1] = "    █   "; lines[2] = "    █   "; lines[3] = " █  █   "; lines[4] = "  ▀▀    "; break;
        case 'K':
            lines[0] = " █   █  "; lines[1] = " █  █   "; lines[2] = " ███    "; lines[3] = " █  █   "; lines[4] = " █   █  "; break;
        case 'L':
            lines[0] = " █      "; lines[1] = " █      "; lines[2] = " █      "; lines[3] = " █      "; lines[4] = " █████  "; break;
        case 'M':
            lines[0] = " █   █  "; lines[1] = " ██ ██  "; lines[2] = " █ ▀ █  "; lines[3] = " █   █  "; lines[4] = " █   █  "; break;
        case 'N':
            lines[0] = " █   █  "; lines[1] = " ██  █  "; lines[2] = " █ █ █  "; lines[3] = " █  ██  "; lines[4] = " █   █  "; break;
        case 'O':
            lines[0] = "  ▄▄▄   "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀   "; break;
        case 'P':
            lines[0] = " █████  "; lines[1] = " █   █  "; lines[2] = " █████  "; lines[3] = " █      "; lines[4] = " █      "; break;
        case 'Q':
            lines[0] = "  ▄▄▄   "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = " █  ██  "; lines[4] = "  ▀▀ █  "; break;
        case 'R':
            lines[0] = " █████  "; lines[1] = " █   █  "; lines[2] = " █████  "; lines[3] = " █  █   "; lines[4] = " █   █  "; break;
        case 'S':
            lines[0] = "  ▄▄▄▄  "; lines[1] = " █      "; lines[2] = "  ▀▀▀▄  "; lines[3] = "     █  "; lines[4] = " ▀▀▀▀   "; break;
        case 'T':
            lines[0] = " █████  "; lines[1] = "   █    "; lines[2] = "   █    "; lines[3] = "   █    "; lines[4] = "   █    "; break;
        case 'U':
            lines[0] = " █   █  "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀   "; break;
        case 'V':
            lines[0] = " █   █  "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = "  █ █   "; lines[4] = "   ▀    "; break;
        case 'W':
            lines[0] = " █   █  "; lines[1] = " █   █  "; lines[2] = " █ ▄ █  "; lines[3] = " ██ ██  "; lines[4] = " █   █  "; break;
        case 'X':
            lines[0] = " █   █  "; lines[1] = "  █ █   "; lines[2] = "   ▀    "; lines[3] = "  █ █   "; lines[4] = " █   █  "; break;
        case 'Y':
            lines[0] = " █   █  "; lines[1] = "  █ █   "; lines[2] = "   ▀    "; lines[3] = "   █    "; lines[4] = "   █    "; break;
        case 'Z':
            lines[0] = " █████  "; lines[1] = "    █   "; lines[2] = "   █    "; lines[3] = "  █     "; lines[4] = " █████  "; break;
        case '0':
            lines[0] = "  ▄▄▄   "; lines[1] = " █▄ ▄█  "; lines[2] = " █ █ █  "; lines[3] = " █▀ ▀█  "; lines[4] = "  ▀▀▀   "; break;
        case '1':
            lines[0] = "   ▄█   "; lines[1] = "  ▀ █   "; lines[2] = "    █   "; lines[3] = "    █   "; lines[4] = "  █████ "; break;
        case '2':
            lines[0] = "  ▄▄▄   "; lines[1] = " ▀   █  "; lines[2] = "   ▄▀   "; lines[3] = "  █     "; lines[4] = " █████  "; break;
        case '3':
            lines[0] = " █████  "; lines[1] = "     █  "; lines[2] = "  ▀▀▀   "; lines[3] = "     █  "; lines[4] = " █████  "; break;
        case '4':
            lines[0] = " █   █  "; lines[1] = " █   █  "; lines[2] = " █████  "; lines[3] = "     █  "; lines[4] = "     █  "; break;
        case '5':
            lines[0] = " █████  "; lines[1] = " █      "; lines[2] = " █████  "; lines[3] = "     █  "; lines[4] = " █████  "; break;
        case '6':
            lines[0] = "  ▄▄▄   "; lines[1] = " █      "; lines[2] = " █████  "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀   "; break;
        case '7':
            lines[0] = " █████  "; lines[1] = "     █  "; lines[2] = "    █   "; lines[3] = "   █    "; lines[4] = "  █     "; break;
        case '8':
            lines[0] = "  ▄▄▄   "; lines[1] = " █   █  "; lines[2] = "  ▀▀▀   "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀   "; break;
        case '9':
            lines[0] = "  ▄▄▄   "; lines[1] = " █   █  "; lines[2] = "  ▀▀▀█  "; lines[3] = "     █  "; lines[4] = "  ▀▀▀   "; break;
        case ' ':
            lines[0] = "    "; lines[1] = "    "; lines[2] = "    "; lines[3] = "    "; lines[4] = "    "; break;
        default:
            lines[0] = "  ▄▄▄   "; lines[1] = " █   █  "; lines[2] = " █   █  "; lines[3] = " █   █  "; lines[4] = "  ▀▀▀   "; break;
    }
    
    printf("%s", lines[line]);
}

/* 名前をASCIIアートで表示 */
void print_name_ascii(const char *name, int offset) {
    for (int line = 0; line < 5; line++) {
        /* オフセット分の空行を追加（上下アニメーション用） */
        if (line == 0 && offset > 0) {
            for (int i = 0; i < offset; i++) {
                printf("\n");
            }
        }
        
        printf("            ");
        for (int i = 0; i < strlen(name) && i < 10; i++) {
            print_ascii_char(name[i], line);
        }
        printf("\n");
        
        /* 最後の行の後にオフセット分の空行を追加 */
        if (line == 4 && offset > 0) {
            for (int i = 0; i < offset; i++) {
                printf("\n");
            }
        }
    }
}

/* 勝者の名前を表示 */
void display_winner_result(const char *winner_name) {
    system("clear");
    
    printf("\n");
    printf("  ____                             _         _       _   _                 _ \n");
    printf(" / ___|___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_(_) ___  _ __  ___| |\n");
    printf("| |   / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __| |\n");
    printf("| |__| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\__ \\_|\n");
    printf(" \\____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___(_)\n");
    printf("                  |___/                                                       \n");
    printf("\n\n");

    
    print_name_ascii(winner_name, 0);
    
    printf("\n");
    printf("                🎉 🎊 🏆 VICTORY! 🏆 🎊 🎉\n");
}

int main() {
    srand((unsigned)time(NULL));
    int current_turn = 1; /* odd: Player1, even: Player2 */
    guess guesses[100]; /* 最大100ターン分の履歴を保存可能 */
    for (int i = 0; i < 100; i++) {
        guesses[i].player[0] = '\0';
    }

    char player1_name[100];
    char player2_name[100];
    char current_player_name[100];
    printf("Enter Player1's name(maximum 10 characters): ");
    scanf("%s", player1_name);/*Player1の名前*/
    while (strlen(player1_name) > 10) {
        printf("Name too long. Please enter a name with a maximum of 10 characters: ");
        scanf("%s", player1_name);
    }
    printf("Enter Player2's name: ");
    scanf("%s", player2_name);/*Player2の名前*/
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

        printf("Enter your guess(Example: 0 1 2 3): ");
        int guess[4];
        scanf("%d %d %d %d", &guess[0], &guess[1], &guess[2], &guess[3]);
        printf("Guess: %d%d%d%d\n", guess[0], guess[1], guess[2], guess[3]);

        insert_guess(guesses, current_player_name, current_turn, hit_count(answer, guess), blow_count(answer, guess), guess);

        print_guess_history(guesses);

        if (guess[0] == answer[0] && guess[1] == answer[1] && guess[2] == answer[2] && guess[3] == answer[3]) {
            display_winner_result(current_player_name);
            printf("\n");
            printf("              Answer: %d%d%d%d | Turns taken: %d\n", answer[0], answer[1], answer[2], answer[3], current_turn);
            printf("\n");
            break;
        }
        current_turn++;
    }

    return 0;
}
