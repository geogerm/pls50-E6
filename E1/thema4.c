//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �01 - ���� 4                ***
//***           ������� ���������� ���������� ������        ***
//***                     ��.���� 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>         // ���� ��� exit()

#define MAXTHESEIS 53       // �������� �� ������� �� ������� ������ ������

int main()
{
    FILE *fp, *fp1;                 // ���������� ������� �� ������
    char pinakida[8];               // ������� �������������� ��� ��� �������� ��� ���������� (7 ���������� + '\0')
    int theseis, i, count, num1;    // ������ �������� ����������
    int layout[MAXTHESEIS];         // ������� �������� ��� ��� ������� ��� ������ (�� ������ ��������� ��� �� �� ������� ������ ������)
    char choice;                    // ������ ���������� ��������� ��� ��� ������� ��� ������

    fp = fopen("bus.txt", "r");     // ������� �� ������ bus.txt ���� ��������

    if(fp == NULL) {                // �� ��������� ����������� ���� �� ������� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
        printf("To arxeio bus.txt den mporese na anagnwstei.\n");
        exit(1);
    }

    fp1 = fopen("layout.txt", "w"); // ������� �� ������ layout.txt ���� �������

    if(fp1 == NULL) {               // �� ��������� ����������� ���� �� ������� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
        printf("To arxeio layout.txt den mporese na anoixtei.\n");
        exit(1);
    }

    fscanf(fp,"%s %d", pinakida, &theseis);     // �������� ��� ��������� ��� ��� ������� ��� ������ ��� �� ������ ������� ��� �������� ���� ���� �����
    printf("Pinakida kikloforias:\t%s\nPlithos thesewn:\t%d\n", pinakida, theseis);

    if(theseis > MAXTHESEIS) {                   // �� �� ������ ����� > 53 ���� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
        printf("\nTo plithos thesewn tou lewforeiou kseperna to megisto epitrepomeno.\n");
        exit(1);
    }

    if((theseis - 5) % 4 != 0) {                // �� �� ������ ��� ����� �������� �� ��� ������������ ������� ���� ����������� ������ ������ ��� �� ��������� ������������ �� ������� ���������
        printf("\nTo plithos thesewn tou lewforeiou den simvadizei me tin provlepomeni katanomi.\n");
        exit(1);
    }

    for (i = 0; i < theseis; i++)     // ������������ ��� ������ ��� ������ ��� �������� ��� ������ ��� �� �������������� (������ ���������� ���� �� ������ �� ���� 0, ������ �����)
        layout[i] = 0;

    do {            // �������������� loop do-while ��� ��� ��������� ��� ������� ��� ��������� ��� ������������ (��� ���������� �� ��������� �� ��������� �������� ������������)
        // �������� ��� ����� ��������
        printf("\n\nPliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n1. Emfanisi sinolikou plithous kenwn thesewn kai twn arithmwn tous\n");
        printf("2. Kratisi sigkekrimenis thesis\n3. Kratisi tis prwtis kenis thesis dipla se parathiro\n4. Akirwsi kratisis thesis\n5. Elegxos diathesimotitas sigkekrimenis thesis\n");
        printf("6. Emfanisi listas kratimenwn thesewn kata arithmo thesis\n7. Emfanisi pinakidas kikloforias kai diagrammatos thesewn ('_' keni thesi, '*' kateilimmeni, ' ' diadromos)\n");
        printf("8. Apothikesfsi pinakidas kai diagrammatos thesewn sto arxeio 'layout.txt'\n0. Eksodos apo to programma\n");
        scanf(" %c", &choice);
        // �������� ��� �������� ��� ������ ������� �� �� ����� ��������
        if (choice == '1') {                                    // ������� ��������� ������� ����� ������ ��� ������� �����
            count = 0;
            for (i = 0; i < theseis; i++) {                     // �������������� �� ����� ������ ��� ����������� �� ������ ����
                if (layout[i] == 0)
                    count++;
            }
            printf("\nPlithos kenwn thesewn:\n%d\n", count);    // ������������ �� ����� ������ ��� ������������ �� ������� ���� �� ������� �����
            printf("\nArithmoi kenwn thesewn:\n");
            for (i = 0; i < theseis; i++) {
                if (layout[i] == 0)
                    printf("%d ", i + 1);
            }
        }
        if (choice == '2') {                                                // ������� �������� ������������� �����
            printf("\nDwse arithmo thesis pros kratisi:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                // ������� �� ����� ������� � ���� ��� �������� (�� ��� �������� ���������� ��������� ��� ��������� ��� ������ �����)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 1)                                 // �� � ���� ����� ��������� �������� ���������� ��������� ��� ��������� ��� ������ �����
                printf("\nH thesi pou epelekses einai idi kratimeni!\n");
            else {                                                          // �� ����� ����, ������� ��� (������ ����� ��� �� 1), �������� ���������� ��������� ��� ��������� ��� ������ �����
                layout[num1 - 1] = 1;
                printf("\nH kratisi sou kataxwrithike me epitixia.\n");
            }
        }
        if (choice == '3') {                                                // ������� �������� ��� ������ ����� ����� �� ��������
            num1 = 0;                                                       // ��������� ��� ����������� ��� ��� �� ��������� ��������� ������ ���� (���� �������� ���� ������� ���� 1)
            for (i = 0; i < (theseis - 5); i += 4) {                        // ������� ��� ��� ����� ����� ��� ��������� ������� ������ ��� ��� ����� ���� ���� �� �������� (�� �������)
                if (layout[i] == 0) {                                       // ������� ��� ������ ����� ���� ������� (�� ����� ���� ������� ������� ��� ������ ��� ��� ������)
                    layout[i] = 1;
                    printf("\nEgine kratisi stin thesi '%d'.\n", i + 1);
                    num1++;
                    break;
                }
                else if (layout[i + 3] == 0) {                              // ������� ��� ���������� ����� ���� ������� (�� ����� ���� ������� ������� ��� ������ ��� ��� ������)
                    layout[i + 3] = 1;
                    printf("\nEgine kratisi stin thesi '%d'.\n", i + 4);
                    num1++;
                    break;
                }
            }
            if (num1 == 0 && layout[theseis - 5] == 0) {                    // ������� (������ ��� ������� ���� ���� �� �������� ��� �������) ��� ������ ����� ���� ��������� ������� �����
                layout[theseis - 5] = 1;
                printf("\nEgine kratisi stin thesi '%d'.\n", theseis - 4);
                num1++;
            }
            else if (num1 == 0 && layout[theseis - 1] == 0) {               // ������� ��� ���������� ����� ���� ��������� ������� �����
                layout[theseis - 1] = 1;
                printf("\nEgine kratisi stin thesi '%d'.\n", theseis);
                num1++;
            }
            else if (num1 == 0)                                                         // �������� ��������� �� ��� �������� ����� ����� �� ��������
                printf("\nDen iparxei alli diathesimi thesi dipla se parathiro.\n");
        }
        if (choice == '4') {                                                            // ������� �������� �������� ������������� �����
            printf("\nDwse arithmo thesis gia akirwsi kratisis:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                            // ������� �� ����� ������� � ���� (�� ��� �������� ���������� ��������� ��� ��������� ��� ������ �����)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 0)                                             // �� � ���� ����� ���� �������� ���������� ��������� ��� ��������� ��� ������ �����
                printf("\nGia tin thesi pou epelekses den eixe ginei kratisi!\n");
            else {                                                                      // �� ����� ���������, ������� (������ ����� �� 0), �������� ��������� ��� ��������� ��� ������ �����
                layout[num1 - 1] = 0;
                printf("\nH akirwsi tis kratisis kataxwrithike me epitixia.\n");
            }
        }
        if (choice == '5') {                                                            // ������� ������� �������������� �����
            printf("\nDwse arithmo thesis gia elegxo diathesimotitas:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                            // ������� �� ����� ������� � ���� (�� ��� �������� ���������� ��������� ��� ��������� ��� ������ �����)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 0)                                             // �� � ���� ����� ���� �������� ���������� ��������� ��� ��������� ��� ������ �����
                printf("\nH thesi pou epelekses einai diathesimi.\n");
            else printf("\nYparxei kratisi gia tin sugkekrimeni thesi.\n");             // ������ �� � ���� ����� ��������� �������� ���������� ��������� ��� ��������� ��� ������ �����
        }
        if (choice == '6') {                                        // ������� ��������� ����� ���������� ������
            printf("\nArithmoi kratimenwn thesewn:\n");
            for (i = 0; i < theseis; i++) {                         // ������������ �� ���������� ������ ��� ������������ �� ������� ���� �� ������� �����
                if (layout[i] == 1)
                    printf("%d ", i + 1);
            }
        }
        if (choice == '7') {                                                // ������� ��������� ��������� ���������� ��� �������� ������ ���� ����� (�� "_" �� ����� �� "*" �� ����������)
            printf("\n%s\n", pinakida);                                     // ����������� � �������� ���� �����
            for (i = 0; i < (theseis - 5); i += 4) {                        // �������� ��� �������� ��� ������ ��� ���� ������� ������ ���������
                layout[i] == 0 ? printf("_") : printf("*");
                layout[i + 1] == 0 ? printf("_ ") : printf("* ");
                layout[i + 2] == 0 ? printf("_") : printf("*");
                layout[i + 3] == 0 ? printf("_\n") : printf("*\n");
            }
            for (i = (theseis - 5); i < theseis; i++)                       // �������� ��� �������� ��� ������ ��� ��� ��������� ������� ������ ��� ����������
                layout[i] == 0 ? printf("_") : printf("*");
                printf("\n");
        }
        if (choice == '8') {                                                        // ������� �������� ��������� ���������� ��� �������� ������ ��� layout.txt (�� "_" �� ����� �� "*" �� ����������)
            fprintf(fp1,"%s\n", pinakida);                                          // �������� � �������� ��� ������
            for (i = 0; i < (theseis - 5); i += 4) {                                // ������� ��� ������ ��� �������� ��� ������ ��� ���� ������� ������ ���������
                layout[i] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
                layout[i + 1] == 0 ? fprintf(fp1, "_ ") : fprintf(fp1, "* ");
                layout[i + 2] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
                layout[i + 3] == 0 ? fprintf(fp1, "_\n") : fprintf(fp1, "*\n");
            }
            for (i = (theseis - 5); i < theseis; i++)                               // ������� ��� ������ ��� �������� ��� ������ ��� ��� ��������� ������� ������ ��� ����������
                layout[i] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
            printf("\nH pinakida kai to diagramma thesewn apothikeftikan sto arxeio 'layout.txt'.\n");      // �������� ���� ����� ��������� ��������� �������� ��� ��������� ��� ������
        }
    } while(choice != '0');     // �� ��������� �� ���������� ��� ���� ��� �� ��������������� � �������� ��� ����� � ������� �� �������� ��� �����, ����� ��� �� ����������� ��������

    fclose(fp);     // ������� �� ������ �������
    fclose(fp1);    // ������� �� ������ ������

    return 0;
}
