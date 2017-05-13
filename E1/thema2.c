//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε01 - Θέμα 2                ***
//***                 Γεωμετρικοί υπολογισμοί               ***
//***                     Ακ.έτος 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <math.h>                       // Για την χρήση των sqrt και pow
#define PI 3.14159265358979323846       // Ορισμός της σταθεράς PI

// Δηλώνουμε τις 4 συναρτήσεις υπολογισμού των περιμέτρων ως πρωτότυπα συναρτήσεων ώστε να μπορούν να οριστούν οι συναρτήσεις μετά την main
double pertetr(double a);               // Τετράγωνο         :   Αρκεί 1 παράμετρος αφού Π = 4 * Πλευρά
double perparal(double b, double c);    // Παραλληλόγραμμο   :   Αρκούν 2 παραμέτροι αφού Π = 2 * (Μήκος + Πλάτος)
double pertrig(double d, double e);     // Ορθογώνιο τρίγωνο :   Αρκούν 2 παραμέτροι αφού Π = Κάθετος1 + Κάθετος2 + Υποτείνουσα (και η υποτείνουσα υπολογίζεται βάσει Πυθαγορείου)
double perkikl(double f);               // Κύκλος            :   Αρκεί 1 παράμετρος αφού Π = 2 * π * Ακτίνα

int main()
{
    char choice;                // Δήλωση μεταβλητής χαρακτήρα για την επιλογή του χρήστη
    double number1, number2;     // Δήλωση αριθμητικών μεταβλητών (αρκούν 2)

    do {                        // Χρησιμοποιούμε loop do-while για την επανάληψη υπό συνθήκη της εκτέλεσης του προγράμματος
        // Εκτυπώνεται στην οθόνη κατάλληλο μήνυμα για να επιλέξει ο χρήστης τι επιθυμεί να κάνει το πρόγραμμα
        printf("\nYpologismos perimetrou gewmetrikwn sximatwn. Epelekse sxima pou se endiaferei:\n1. Tetragwno\n2. Parallilogrammo\n3. Orthogwnio Trigwno\n4. Kiklos\n0. Eksodos\n");
        scanf(" %c", &choice);                  // Ανάγνωση επιλογής χρήστη (το κενό προ του %c υπάρχει για να μην αναγνωστούν τυχόν κενοί χαρακτήρες)

        // Εκτέλεση της αιτούμενης ενέργειας ανάλογα με την επιλογή του χρήστη
        if (choice == '1') {                                                                                // Για επιλογή τετραγώνου
            printf("Dwse mikos plevras tetragwnou:\n");
            scanf("%lf", &number1);
            printf("\nH perimetros tou Tetragwnou einai: %.4lf\n", pertetr(number1));                       // Εκτύπωση αποτελέσματος (με 4 δεκαδικά) με κλήση της κατάλληλης συνάρτησης
        }
        if (choice == '2') {                                                                                // Για επιλογή παραλληλογράμμου
            printf("Dwse mikos parallilogrammou:\n");
            scanf("%lf", &number1);
            printf("Dwse platos parallilogrammou:\n");
            scanf("%lf", &number2);
            printf("\nH perimetros tou Parallilogramou einai: %.4lf\n", perparal(number1, number2));        // Εκτύπωση αποτελέσματος (με 4 δεκαδικά) με κλήση της κατάλληλης συνάρτησης
        }
        if (choice == '3') {                                                                                // Για επιλογή ορθογωνίου τριγώνου
            printf("Dwse mikos prwtis kathetis plevras:\n");
            scanf("%lf", &number1);
            printf("Dwse mikos defteris kathetis plevras:\n");
            scanf("%lf", &number2);
            printf("\nH perimetros tou Orthogwnioy Trigwnou einai: %.4lf\n", pertrig(number1, number2));    // Εκτύπωση αποτελέσματος (με 4 δεκαδικά) με κλήση της κατάλληλης συνάρτησης
        }
        if (choice == '4') {                                                                                // Για επιλογή κύκλου
            printf("Dwse aktina kiklou:\n");
            scanf("%lf", &number1);
            printf("\nH perimetros tou Kiklou einai: %.4lf\n", perkikl(number1));                           // Εκτύπωση αποτελέσματος (με 4 δεκαδικά) με κλήση της κατάλληλης συνάρτησης
        }
    } while(choice != '0');     // Το πρόγραμμα θα εκτελεστεί μια φορά και θα επαναλαμβάνεται η εκτέλεση του μέχρι ο χρήστης να επιλέξει την έξοδο, οπότε και θα τερματιστεί επιτυχώς

    return 0;
}

// Ορισμός των συναρτήσεων για των υπολογισμό των περιμέτρων με χρήση των γεωμετρικών τύπων. Τα ονόματα των παραμέτρων δεν χρειάζεται να συμφωνούν με τα πρωτότυπα των συναρτήσεων
double pertetr(double plevra)
{
    double tetr;
    tetr = 4 * plevra;
    return tetr;                                                                // Επιστροφή της τιμής της tetr κατά την κλήση της συνάρτησης
}

double perparal(double mikos, double platos)
{
    double paral;
    paral = 2 * (mikos + platos);
    return paral;                                                               // Επιστροφή της τιμής της paral κατά την κλήση της συνάρτησης
}

double pertrig(double katheti1, double katheti2)
{
    double trig;
    trig = katheti1 + katheti2 + sqrt(pow(katheti1, 2) + pow(katheti2, 2));     // Υπολογισμός περιμέτρου (με ταυτόχρονο υπολογισμό και της υποτείνουσας)
    return trig;                                                                // Επιστροφή της τιμής της trig κατά την κλήση της συνάρτησης
}

double perkikl(double aktina)
{
    double kikl;
    kikl = 2 * PI * aktina;
    return kikl;                                                                // Επιστροφή της τιμής της kikl κατά την κλήση της συνάρτησης
}
