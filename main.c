#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char player[100];
    int turn;
    int hit;
    int blow;
}guess;

int main() {
    int current_turn = 1; /* odd: Player1, even: Player2 */
    guess g1, g2; /*p1とp2の構造体の配列*/
    guess *P1 = &g1;/*g1のポインタ*/
    guess *P2 = &g2;/*g2のポインタ*/

    char player1_name[100];
    char player2_name[100];
    printf("Enter Player1's name: ");
    scanf("%s", player1_name);/*p1の名前*/
    printf("Enter Player2's name: ");
    scanf("%s", player2_name);/*p2の名前*/

  
    printf("Generating Answer...\n");

    int answer[] = {}; /* ４桁のランダムな数字を生成 （同じ数字の桁がないように） */
    printf("Answer generated: %d%d%d%d\n", answer[0], answer[1], answer[2], answer[3]);

    /* Game Loop */
    while (1) {
        if (current_turn % 2 == 1) {
            printf("%s's turn\n", player1_name);
        } else {
            printf("%s's turn\n", player2_name);
        }

        printf("Enter your guess: ");
        int guess[4];
        scanf("%d%d%d%d", &guess[0], &guess[1], &guess[2], &guess[3]);
        printf("Guess: %d%d%d%d\n", guess[0], guess[1], guess[2], guess[3]);

        if (guess[0] == answer[0] && guess[1] == answer[1] && guess[2] == answer[2] && guess[3] == answer[3]) {
            printf("You win!\n");
            break;
        }


    }



    return 0;
}
