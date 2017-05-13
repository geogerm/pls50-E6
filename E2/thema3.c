//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �02 - ���� 3                ***
//***            ��������� ���������� ���������� SET        ***
//***                     ��.���� 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>     // ���� ��� srand(), rand(), exit()
#include <string.h>     // ���� ��� strncpy()
#include <time.h>       // ���� ��� time()

// ���� ��� ���� �������
typedef struct paixtis{
    char name[17];
    unsigned char score;    // ��� ��������� ������ ���� ������� ���� 0-255
    char id;
} player;

// ���� ��� ��� ������
typedef struct karta{
    char idiotites[5];      // 4 ��������� ��� �� \0
    char used;              // ������� �� ��������������� � ��� � �����. ��� ��������� ������ �� char ���� ������� ���� 0-255
} card;

// ������� ���������� ����� ��� ����� ������� �� global variables ��� ������� �����
player a = {"Marina Andreou", 0, 'a'};
player g = {"Kostas Grammenos", 0, 'g'};
player p = {"Maria Perdika", 0, 'p'};

// ��������� ��� "�������" ��� ��������� �� ����� ���� �������� ����������� ������
void initializeFullDeck(card fulldeck[]){
    int i, j, k, l;
    int count = 0;

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            for (k = 0; k < 3; k++){
                for (l = 0; l < 3; l++){
                    // ����� (���� 0)
                    if (i == 0) fulldeck[count].idiotites[0] = 'r';
                    if (i == 1) fulldeck[count].idiotites[0] = 'g';
                    if (i == 2) fulldeck[count].idiotites[0] = 'b';
                    // ����� (���� 1)
                    if (j == 0) fulldeck[count].idiotites[1] = 'c';
                    if (j == 1) fulldeck[count].idiotites[1] = 't';
                    if (j == 2) fulldeck[count].idiotites[1] = 'r';
                    // ������� (���� 2)
                    if (k == 0) fulldeck[count].idiotites[2] = '1';
                    if (k == 1) fulldeck[count].idiotites[2] = '2';
                    if (k == 2) fulldeck[count].idiotites[2] = '3';
                    // ��� (���� 3)
                    if (l == 0) fulldeck[count].idiotites[3] = 'b';
                    if (l == 1) fulldeck[count].idiotites[3] = 'h';
                    if (l == 2) fulldeck[count].idiotites[3] = 'e';
                    fulldeck[count].idiotites[4] = '\0';     // ������� ��� '\0' ���� ��������� ���� ��� string
                    fulldeck[count].used = 0;                // ������������� ��� ������ �� �� ����������
                    count++;                                 // ������� �����
                }
            }
        }
    }
    return;
}

// ��������� ��� ������� ��� �������� �� ����������� ������
int getNextCard(card fulldeck[]){
    int i = 0;
    do {
        i = 80 * rand() / RAND_MAX;      // ������� ������� ����� ��� 0 ��� 80 (�������� ���� ��� ������ ��� ���������)
    } while (fulldeck[i].used == 1);     // � ������� ������ ����� �� ������ ����� ��� �� ��� ���� ��� ��������
    fulldeck[i].used = 1;                // � ����� ������ ����� ������� �����������
    return i;
}

// ��������� ��� "�������" ��� ��������� ��� 12 ������ �� ������
void getNextPlaydeck(card fulldeck[], card gamedeck[][4]){
    int i, j = 0;
    // ������� ��� "�������" ��� ���������
    for (i = 0; i < 3; i++){
        for (j = 0; j < 4; j++){
            strcpy(gamedeck[i][j].idiotites, fulldeck[getNextCard(fulldeck)].idiotites);    //  ���������� ��� �������� ��� ��������� ��� ����� ��� ��� ����� � getNextCard()
        }
    }
    // ������� ��� ��������� ���� ��� ������� ��� ��������� �� ��������� �� �����������
    for (i = 0; i < 81; i++){
        fulldeck[i].used = 0;
    }
    return;
}

// ��������� ��� �������� ��� ��������� ��� ������ ��� "�������" ���� �����
void viewPlaydeck(card gamedeck[][4]){
    int i, j = 0;
        for (i = 0; i < 3; i++){
            printf("            ");
            for (j = 0; j < 4; j++)
                printf("[%c, %c, %c, %c]  ", gamedeck[i][j].idiotites[0], gamedeck[i][j].idiotites[1], gamedeck[i][j].idiotites[2], gamedeck[i][j].idiotites[3]);
            printf("\n");
        }
        printf("\n");
    return;
}

// ��������� ��� �������� ������ �������������
void checkcoordinates(int *x, int *y){
    do {                                //������� ��� ��������������� ����� �� ������ ����� ����� �����
        printf("Dwse to x (tin grammi pou vrisketai i karta) apo 0 ews kai 2:\n");
        scanf(" %d", x);
        printf("Dwse to y (tin stili pou vrisketai i karta) apo 0 ews kai 3:\n");
        scanf(" %d", y);
        if (*x < 0 || *x > 2 || *y < 0 || *y > 3)
            printf("Exeis eisagei times ektos twn oriwn tou plegmatos. Dwse ksana syntetagmenes:\n");
    } while (*x < 0 || *x > 2 || *y < 0 || *y > 3);
    return;
}
// ��������� ��� ������ �� ���� ����� SET
int checkSet(card gamedeck[][4], int x1, int y1, int x2, int y2, int x3, int y3){
    int i;
    int count = 0;

    // ������� ��� ������� �������� ��� ��� 4 �� ������
    for (i = 0; i < 4; i++){
        // ������� �� ����� ��� �� �������� ����� � ��� �����������
        if ((gamedeck[x1][y1].idiotites[i] == gamedeck[x2][y2].idiotites[i] && gamedeck[x1][y1].idiotites[i] == gamedeck[x3][y3].idiotites[i]) ||
        (gamedeck[x1][y1].idiotites[i] != gamedeck[x2][y2].idiotites[i] && gamedeck[x1][y1].idiotites[i] != gamedeck[x3][y3].idiotites[i] && gamedeck[x2][y2].idiotites[i] != gamedeck[x3][y3].idiotites[i])){
            count++;        // ��� ���� �������� ��� ������ ��� �������� ��������� ���� 1 �� count
        }
    }
    if (count == 4)         // �� ��� �� 4 ��������� ��� ����� ������ ������� ��� �������� ������ SET ��� ������������ ���� 1
        return 1;
    else                    // ������ ��� ������ SET ��� ������������ ���� 0
        return 0;
}

// ��������� ��� ������� �����
void playgame(card fulldeck[], card gamedeck[][4], player *pl){
    int x1, y1, x2, y2, x3, y3;       // ���������� ��� ������������� ������
    // �������� ��� ������� ������������� ������
    printf("%s dwse tis syntetagmenes tis prwtis kartas kai pata 'Enter'.\n", pl->name);
    checkcoordinates(&x1, &y1);
    printf("Dwse tis syntetagmenes tis defteris kartas kai pata 'Enter'.\n");
    checkcoordinates(&x2, &y2);
    printf("Dwse tis syntetagmenes tis tritis kartas kai pata 'Enter'.\n");
    checkcoordinates(&x3, &y3);
    printf("\n");
    // ������� ��� ��� ���� �������� 2 � 3 ����� � ���� ����� ��� �� ������
    if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)){
        printf("Exeis epileksei 2 i 3 fores tin idia karta apo to plegma. Epanepilogi paixti.\n\n");
        viewPlaydeck(gamedeck);
        return;
    }
    // �� �� ������ ��������� SET
    if (checkSet(gamedeck, x1, y1, x2, y2, x3, y3) == 1){
        printf("%s oi kartes poy epelekses apoteloun SET!\n", pl->name);
        printf("Kerdises 2 pontous!!\n");
        pl->score += 2;
        if (pl->score >= 10){       // �� � ������� ������� ������ ���� 10 ������� ������ ���������� ��� ������������
            printf("\nTelos paixnidiou. Exoume nikhth!\n\n");
            printf("            Name                Score      ID\n");
            printf("            ---------------------------------\n");
            printf("            %-16s       %2hu       %c\n", a.name, a.score, a.id);
            printf("            %-16s       %2hu       %c\n", g.name, g.score, g.id);
            printf("            %-16s       %2hu       %c\n", p.name, p.score, p.id);
            printf("\n\nO nikhths einai o/h %s!!\n", pl->name);
            exit(0);        // ������� ������ ��� �� ��������� �� ������� ������������ ���������
        }
        printf("\nNeos gyros paixnidiou. Oi kartes anakateftikan.\n\n");
        getNextPlaydeck(fulldeck, gamedeck);
        viewPlaydeck(gamedeck);
    }
    // �� �� ������ ��� ��������� SET
    else {
        printf("%s oi kartes poy epelekses den apoteloun SET.\n", pl->name);
        printf("Xaneis 1 ponto!!\n");
        if (pl->score >= 1){       // �� � ������� ���� ����������� 1 ����� ���������� 1 ������
            pl->score -= 1;
        }
        printf("\nTo paixnidi synexizetai.\n\n");
        viewPlaydeck(gamedeck);
    }
    return;
}

// ������ ���������
int main(){
    // ������� ����������
    card deck[81];          // ������� ����� �� ��� ��������� ������ (��������)
    card playdeck[3][4];    // ������������ ������� ����� �� ��� ����������� ��� ��� ������� ������. ������ ������� �� �������� used ���� � ����� ����� ���������� �������� ��� ���������
    char epilogi = 0;

    srand(time(NULL));      // ������������ ��� rand()

    initializeFullDeck(deck);           // "�������" ��� ��������� �� ����� ���� �������� ����������� ������
    getNextPlaydeck(deck, playdeck);    // "�������" ��� ��������� ��� 12 ������ �� ������
    printf("\nTo paixnidi ksekinise! Kali epityxia!\n\n");
    viewPlaydeck(playdeck);             // �������� ��� ������ ��� "�������" ���� �����


    while (1){          //Infinite loop ��� �� �������� ���� �� ��� ������� 0 (���� ��� return)
        printf("Dwse to ID tou paixti (ena ek twn a, g, p) i to 0 gia eksodo kai pata 'Enter':\n");
        scanf(" %c", &epilogi);
        printf("\n");
        switch(epilogi){
            case 'a':                                   // ������ � ������
                playgame(deck, playdeck, &a);
                break;
            case 'g':                                   // ������ � ������
                playgame(deck, playdeck, &g);
                break;
            case 'p':                                   // ������ � �����
                playgame(deck, playdeck, &p);
                break;
            case '0':                                   // �������� ��� ��������� ��� ������� ��� ������ ��� �� ���������
                printf("            Name                Score      ID\n");
                printf("            ---------------------------------\n");
                printf("            %-16s       %2hu       %c\n", a.name, a.score, a.id);
                printf("            %-16s       %2hu       %c\n", g.name, g.score, g.id);
                printf("            %-16s       %2hu       %c\n", p.name, p.score, p.id);
                return 0;
            default:
                printf("Parakalw epilekse ksana mia egkiri epilogi.\n\n");
                getNextPlaydeck(deck, playdeck);
                viewPlaydeck(playdeck);
                break;
        }
    }
    return 0;
}

// ������ ������������� ������:
// 0:   K����� ������. �� ��������� ����������� �� ��������.
