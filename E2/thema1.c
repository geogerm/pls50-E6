//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �02 - ���� 1                ***
//***         ��� ������� ���������� ���������� ������      ***
//***                     ��.���� 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>         // ���� ��� exit()
#include <string.h>         // ���� ��� strcpy(), strcat(), memcmp()

#define MAXTHESEIS 53       // �������� �� ������� �� ������� ������ ������

// ������� ����� ��� ��� ���� ��� ����������
typedef struct theseis{
    char onomatepwnimo[40];         // ������� �������������� (39 ���������� + '\0')
    unsigned short tilefwno[10];
    unsigned int arithmos;
} thesi;

// ��������� ��� ��� ������������ ��� ������ ��� ������ ��� ����������
void initializebus(thesi mainarray[]){
    int i, j;

    for (i = 0; i < MAXTHESEIS; i++){
        mainarray[i].onomatepwnimo[0] = '\0';
        mainarray[i].arithmos = i + 1;
        for (j = 0; j < 10; j++){
            mainarray[i].tilefwno[j] = 0;
        }
    }
    return;
}

// ��������� ��� ��� �������� ��� ������� ��� ��� ���������� ��� ������� ���������
void readfile(thesi mainarray[], char plate[], int *seats){
    FILE *bus;      // ������ ������-��������� �������
    // ������� ���������� ��� ��� �������� ��� ����������
    char nametemp1[20] = {0};
    char nametemp2[19] = {0};
    int seatstemp, i;
    double tilefwnotemp = 0;         // ����� double ����� � long long int ����� warnings

    bus = fopen ("bus.txt", "r");    // ������� �� ������ bus.txt ���� ��������

    // �� ��������� ����������� ���� �� ������� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }

    fscanf(bus, "%s %d\n", plate, seats);
    printf("Pinakida kikloforias:\t%s\nPlithos thesewn:\t%d\n\n", plate, *seats);

    while (!feof(bus)){                                                                    // ����� �� ����� ��� �������
        fscanf(bus, "%s %s %d %lf\n", nametemp1, nametemp2, &seatstemp, &tilefwnotemp);    // �������� ���� ������� ��� ������� ��� �������� �������
        // ���������� ��� ���������
        for (i = 9; i >= 0 && tilefwnotemp != 0; i--){
            mainarray[seatstemp - 1].tilefwno[i] = (long long int)tilefwnotemp % 10;
            tilefwnotemp /= 10;
        }
        // ���������� ��� ��������������
        strcpy(mainarray[seatstemp - 1].onomatepwnimo, nametemp1);
        strcat(mainarray[seatstemp - 1].onomatepwnimo, " ");
        strcat(mainarray[seatstemp - 1].onomatepwnimo, nametemp2);
    }
    fclose(bus);     // �������� ������� ��� ������������ ������
    return;
}

// ��������� ��� �������� ����� ��������
void menuepilogwn(){
    printf("Pliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n");
    printf("1. Emfanisi plithous kenwn thesewn kai arithmoi aftwn (kata afksousa seira)\n");
    printf("2. Kratisi sigkekrimenis thesis\n");
    printf("3. Anazitisi kratisis me onomatepwnimo i tilefwno\n");
    printf("4. Akirwsi kratisis thesis\n");
    printf("5. Emfanisi listas kratimenwn thesewn kata afksonta arithmo thesis\n");
    printf("0. Eksodos apo to programma\n");
    return;
}

// ��������� ��� �������� ����� ������
void kenestheseis(thesi mainarray[], int seats){
    int i;
    int counter = 0;
    for (i = 0; i < seats; i++){
        if (mainarray[i].onomatepwnimo[0] == '\0')
            counter++;
    }
    printf("Plithos kenwn thesewn:\n%d\n", counter);    // ������������ �� ����� ������ ��� ������������ �� ������� ���� �� ������� �����
    printf("\nArithmoi kenwn thesewn:\n");
    for (i = 0; i < seats; i++) {
        if (mainarray[i].onomatepwnimo[0] == '\0')
            printf("%d ", i + 1);
    }
    return;
}

// ��������� ��� ������� �����
void kratisithesis(thesi *mainarray, int seatnumber, int seats){
    double tilefwnotemp = 0;         // ����� double ����� � long long int ����� warnings
    int i = 0;

    if (seatnumber <= 0 || seatnumber > seats)                           // ������� �� ����� ������� � ���� ��� �������� (�� ��� �������� ���������� ��������� ��� ��������� ��� ������ �����)
        printf("\nH thesi pou epelekses den iparxei!\n");
    else if (mainarray->onomatepwnimo[0] != '\0')                        // �� � ���� ����� ��������� �������� ���������� ��������� ��� ��������� ��� ������ �����
        printf("\nH thesi pou epelekses einai idi kratimeni!\n");
    else {                                                               // �� ����� ����, ������� ��� �� �������� ���������, �������� ���������� ��������� ��� ��������� ��� ������ �����
        printf("\nDwse onomatepwnimo gia ti kratisi (stin morfi 'Epwnymo Onoma') kai pata 'Enter':\n");
        gets(mainarray->onomatepwnimo);

        printf("\nDwse enan 10psifio arithmo tilefwnou kai pata 'Enter':\n");
        scanf(" %lf", &tilefwnotemp);
        for (i = 9; i >= 0 && tilefwnotemp != 0; i--){
            mainarray->tilefwno[i] = (long long int)tilefwnotemp % 10;
            tilefwnotemp /= 10;
        }
        printf("\nH kratisi sou kataxwrithike me epitixia.\n");
    }
    return;
}

// ��������� ��� ������ �������� �� ������������� � ��������
void elegxoskratisis(thesi mainarray[], int seats){
    // ������� ���������� ��� ��� �������� ��� ����������
    int i;
	int count = 0;
    char choice = 0;
    char nametemp[40] = {0};
    double tilefwnotemp = 0;         // ����� double ����� � long long int ����� warnings
    unsigned short tilefwnot[10];

    printf("Pliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n");
    printf("1. Anazitisi kratisis me onomatepwnimo\n");
    printf("2. Anazitisi kratisis me arithmo tilefwnou\n");
    scanf(" %c", &choice);
    fflush(stdin);                  // ��������� ��� ��������� ��� ������ ��� buffer ��� ��� scanf()
    printf("\n");

    switch(choice){
        case '1':                   // ��������� �� �������������
            printf("Dwse onomatepwnimo (stin morfi 'Epwnymo Onoma') kai pata 'Enter':\n");
            gets(nametemp);
            for (i = 0; i < seats; i++){            // ������� ������� �� ������� ���� ��� ��� �������
                if (strcmp(mainarray[i].onomatepwnimo, nametemp) == 0 && count == 0){
                    printf("\nIparxei sxetiki kratisi stin akolouthi thesi i theseis:   ");
                    count++;
                    break;
                }
            }
            for (i = 0; i < seats; i++){            // �������� ��� ����� � ��� ������ ��� ����� ��������
                if (strcmp(mainarray[i].onomatepwnimo, nametemp) == 0 && count != 0){
                    printf(" %d ", i + 1);
                }
            }
            if (count == 0)                         // �� ��� ������� �������
                printf("\nDen exei ginei kratisi sto onomatepwnimo %s.\n", nametemp);
            break;
        case '2':                   // ��������� �� ��������
            printf("Dwse 10psifio arithmo tilefwnou kai pata 'Enter':\n");
            scanf(" %lf", &tilefwnotemp);
            // ���������� ��� ��������� ��� ��������� array ��� �� �������������� ��� ��� ��������.
            for (i = 9; i >= 0 && tilefwnotemp != 0; i--){
                tilefwnot[i] = (long long int)tilefwnotemp % 10;
                tilefwnotemp /= 10;
            }
            for (i = 0; i < seats; i++){            // ������� ������� �� ������� ���� ��� ��� �������
                if (memcmp(mainarray[i].tilefwno, tilefwnot, sizeof(mainarray[i].tilefwno)) == 0 && mainarray[i].onomatepwnimo[0] != '\0' && count == 0){
                    printf("\nIparxei sxetiki kratisi stin akolouthi thesi i theseis:   ");
                    count++;
                    break;
                }
            }
            for (i = 0; i < seats; i++){            // �������� ��� ����� � ��� ������ ��� ����� ��������
                if (memcmp(mainarray[i].tilefwno, tilefwnot, sizeof(mainarray[i].tilefwno)) == 0 && count != 0){
                    printf(" %d ", i + 1);
                }
            }
            if (count == 0){                         // �� ��� ������� �������
                printf("\nDen exei ginei kratisi me arithmo tilefwnou ");
                for (i = 0; i < 10; i++){
                    printf("%hu", tilefwnot[i]);
                }
                printf(".\n");
            }
            break;
        default:
            break;
    }
    return;
}

// ��������� ��� ������� �������� �����
void akirwsikratisis(thesi *mainarray, int seatnumber, int seats){

    if (seatnumber <= 0 || seatnumber > seats)                           // ������� �� ����� ������� � ���� ��� �������� (�� ��� �������� ���������� ��������� ��� ��������� ��� ������ �����)
        printf("\nH thesi pou epelekses den iparxei!\n");
    else if (mainarray->onomatepwnimo[0] == '\0')                        // �� � ���� ����� �������� �������� ���������� ��������� ��� ��������� ��� ������ �����
        printf("\nH thesi pou epelekses den eixe kratithei!\n");
    else {                                                               // �� ������� �������, ������� ���, �������� ���������� ��������� ��� ��������� ��� ������ �����
        mainarray->onomatepwnimo[0] = '\0';
        printf("\nH kratisi akirwthike me epitixia.\n");
    }
    return;
}

// ��������� ��� �������� ������ ��� ���������� ������
void ektipwsikratisewn(thesi mainarray[], int seats){
    int i, j = 0;
    int count = 1;

    for (i = 0; i < seats; i++){
        if (mainarray[i].onomatepwnimo[0] != '\0'){
            printf("%d. %-40s   ", count, mainarray[i].onomatepwnimo);
            for (j = 0; j < 10; j++){
                printf("%hu", mainarray[i].tilefwno[j]);
            }
            printf("        %2d\n", i + 1);
            count++;
        }
    }
    return;
}

// ��������� ��� update ��� ������� ��� ������ ��� �� ���������
void swsimokaieksodos(thesi mainarray[], char plate[], int seats){
    FILE *bus;      // ������ ������-��������� �������
    int i, j;

    bus = fopen ("bus.txt", "w");    // ������� �� ������ bus.txt ���� �������
    // �� ��������� ����������� ���� �� ������� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }
    fprintf(bus, "%s %d\n", plate, seats);          // �������� ��� ������ ������� ��� ������
    // �������� ��� �������� ������� ��� ������ (��� ������� ��� ���������� ������)
    for (i = 0; i < seats; i++){
        if (mainarray[i].onomatepwnimo[0] != '\0'){
            fprintf(bus, "%s %d ", mainarray[i].onomatepwnimo, i + 1);
            for (j = 0; j < 10; j++){
                fprintf(bus, "%hu", mainarray[i].tilefwno[j]);
            }
            fprintf(bus, "\n");
        }
    }
    fclose(bus);                            // �������� ������� ��� ������������ ������
    printf("Ta dedomena apothikeftikan sto arxeio bus.txt me epitixia!\n");
    return;
}

// ������ ���������
int main(){
    // ������ ����������
    thesi lewforeio[MAXTHESEIS];        // ������������� ������� ���� ��� ������
    char pinakida[8] = {0};             // ������� �������������� ��� ��� �������� ��� ���������� (7 ���������� + '\0')
    int theseis = 0;
    int arithmosthesis = 0;
    char epilogi = 0;

    // ������������ ������ ��� �������� ��������� ��� ������
    initializebus(lewforeio);
    readfile(lewforeio, pinakida, &theseis);

    while (1){          //Infinite loop ��� �� �������� ���� �� ��� ������� 0 (���� ��� return)
        menuepilogwn();
        scanf(" %c", &epilogi);
        printf("\n");
        switch(epilogi){
            case '1':                                   // �������� ����� ������
                kenestheseis(lewforeio, theseis);
                break;
            case '2':                                   // ������� ������������� �����
                printf("Dwse arithmo thesis pros kratisi:\n");
                scanf(" %d", &arithmosthesis);
                fflush(stdin);                  // ��������� ��� ��������� ��� ������ ��� buffer ��� ��� scanf()
                kratisithesis(&lewforeio[arithmosthesis - 1], arithmosthesis, theseis);
                break;
            case '3':                                   // ������� �������� ����� �� ����� � ��������
                elegxoskratisis(lewforeio, theseis);
                break;
            case '4':                                   // ������� �������� ������������� �����
                printf("Dwse arithmo thesis pros akirwsi kratisis:\n");
                scanf(" %d", &arithmosthesis);
                fflush(stdin);                  // ��������� ��� ��������� ��� ������ ��� buffer ��� ��� scanf()
                akirwsikratisis(&lewforeio[arithmosthesis - 1], arithmosthesis, theseis);
                break;
            case '5':                                   // �������� ������ ���������� ������
                ektipwsikratisewn(lewforeio, theseis);
                break;
            case '0':                                   // Update ��� ������� ��� ������ ��� �� ���������
                swsimokaieksodos(lewforeio, pinakida, theseis);
                return 0;
            default:
                printf("Parakalw epilekse ksana mia egkiri leitourgia.");
                break;
        }
        printf("\n\n");
    }
    return 0;
}

// ������ ������������� ������:
// 0:   K����� ������. �� ��������� ����������� �� ��������.
//-1:   ��� ���� ������ �� ���������� �� ������.
