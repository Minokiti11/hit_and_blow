#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char player[100];
    int turn;
    int hit;
    int blow;
}guess;


int main() {
    guess g1, g2;
    char player1[100];
    char player2[100];
    printf("Enter Player1's name: ");
    scanf("%s", player1);
    printf("Enter Player2's name: ");
    scanf("%s", player2);

    printf("Generating Answer...\n");
    int answer[] = {1, 2, 3, 4}; /* ４桁のランダムな数字を生成 （同じ数字の桁がないように） */
    printf("Answer generated: %d%d%d%d\n", answer[0], answer[1], answer[2], answer[3]);

    return 0;
}
