//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �01 - ���� 2                ***
//***                 ����������� �����������               ***
//***                     ��.���� 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <math.h>                       // ��� ��� ����� ��� sqrt ��� pow
#define PI 3.14159265358979323846       // ������� ��� �������� PI

// ��������� ��� 4 ����������� ����������� ��� ���������� �� ��������� ����������� ���� �� ������� �� �������� �� ����������� ���� ��� main
double pertetr(double a);               // ���������         :   ����� 1 ���������� ���� � = 4 * ������
double perparal(double b, double c);    // ���������������   :   ������ 2 ���������� ���� � = 2 * (����� + ������)
double pertrig(double d, double e);     // ��������� ������� :   ������ 2 ���������� ���� � = �������1 + �������2 + ����������� (��� � ����������� ������������ ����� �����������)
double perkikl(double f);               // ������            :   ����� 1 ���������� ���� � = 2 * � * ������

int main()
{
    char choice;                // ������ ���������� ��������� ��� ��� ������� ��� ������
    double number1, number2;     // ������ ����������� ���������� (������ 2)

    do {                        // �������������� loop do-while ��� ��� ��������� ��� ������� ��� ��������� ��� ������������
        // ����������� ���� ����� ��������� ������ ��� �� �������� � ������� �� �������� �� ����� �� ���������
        printf("\nYpologismos perimetrou gewmetrikwn sximatwn. Epelekse sxima pou se endiaferei:\n1. Tetragwno\n2. Parallilogrammo\n3. Orthogwnio Trigwno\n4. Kiklos\n0. Eksodos\n");
        scanf(" %c", &choice);                  // �������� �������� ������ (�� ���� ��� ��� %c ������� ��� �� ��� ����������� ����� ����� ����������)

        // �������� ��� ���������� ��������� ������� �� ��� ������� ��� ������
        if (choice == '1') {                                                                                // ��� ������� ����������
            printf("Dwse mikos plevras tetragwnou:\n");
            scanf("%lf", &number1);
            printf("\nH perimetros tou Tetragwnou einai: %.4lf\n", pertetr(number1));                       // �������� ������������� (�� 4 ��������) �� ����� ��� ���������� ����������
        }
        if (choice == '2') {                                                                                // ��� ������� ����������������
            printf("Dwse mikos parallilogrammou:\n");
            scanf("%lf", &number1);
            printf("Dwse platos parallilogrammou:\n");
            scanf("%lf", &number2);
            printf("\nH perimetros tou Parallilogramou einai: %.4lf\n", perparal(number1, number2));        // �������� ������������� (�� 4 ��������) �� ����� ��� ���������� ����������
        }
        if (choice == '3') {                                                                                // ��� ������� ���������� ��������
            printf("Dwse mikos prwtis kathetis plevras:\n");
            scanf("%lf", &number1);
            printf("Dwse mikos defteris kathetis plevras:\n");
            scanf("%lf", &number2);
            printf("\nH perimetros tou Orthogwnioy Trigwnou einai: %.4lf\n", pertrig(number1, number2));    // �������� ������������� (�� 4 ��������) �� ����� ��� ���������� ����������
        }
        if (choice == '4') {                                                                                // ��� ������� ������
            printf("Dwse aktina kiklou:\n");
            scanf("%lf", &number1);
            printf("\nH perimetros tou Kiklou einai: %.4lf\n", perkikl(number1));                           // �������� ������������� (�� 4 ��������) �� ����� ��� ���������� ����������
        }
    } while(choice != '0');     // �� ��������� �� ���������� ��� ���� ��� �� ��������������� � �������� ��� ����� � ������� �� �������� ��� �����, ����� ��� �� ����������� ��������

    return 0;
}

// ������� ��� ����������� ��� ��� ���������� ��� ���������� �� ����� ��� ����������� �����. �� ������� ��� ���������� ��� ���������� �� ��������� �� �� ��������� ��� �����������
double pertetr(double plevra)
{
    double tetr;
    tetr = 4 * plevra;
    return tetr;                                                                // ��������� ��� ����� ��� tetr ���� ��� ����� ��� ����������
}

double perparal(double mikos, double platos)
{
    double paral;
    paral = 2 * (mikos + platos);
    return paral;                                                               // ��������� ��� ����� ��� paral ���� ��� ����� ��� ����������
}

double pertrig(double katheti1, double katheti2)
{
    double trig;
    trig = katheti1 + katheti2 + sqrt(pow(katheti1, 2) + pow(katheti2, 2));     // ����������� ���������� (�� ���������� ���������� ��� ��� ������������)
    return trig;                                                                // ��������� ��� ����� ��� trig ���� ��� ����� ��� ����������
}

double perkikl(double aktina)
{
    double kikl;
    kikl = 2 * PI * aktina;
    return kikl;                                                                // ��������� ��� ����� ��� kikl ���� ��� ����� ��� ����������
}
