//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε01 - Θέμα 4                ***
//***           Σύστημα καταγραφής κρατημένων θέσεων        ***
//***                     Ακ.έτος 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>         // Λόγω της exit()

#define MAXTHESEIS 53       // Ορίζεται ως σταθερά το μέγιστο πλήθος θέσεων

int main()
{
    FILE *fp, *fp1;                 // Μεταβλητές δείκτες σε αρχείο
    char pinakida[8];               // Πίνακας αλφαριθμητικών για την πινακίδα του λεωφορείου (7 χαρακτήρες + '\0')
    int theseis, i, count, num1;    // Δήλωση ακέραιων μεταβλητών
    int layout[MAXTHESEIS];         // Πίνακας ακεραίων για την διάταξη των θέσεων (με πλήθος στοιχείων ίσο με το μέγιστο πλήθος θέσεων)
    char choice;                    // Δήλωση μεταβλητής χαρακτήρα για την επιλογή του χρήστη

    fp = fopen("bus.txt", "r");     // Ανοίγει το αρχείο bus.txt προς ανάγνωση

    if(fp == NULL) {                // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
        printf("To arxeio bus.txt den mporese na anagnwstei.\n");
        exit(1);
    }

    fp1 = fopen("layout.txt", "w"); // Ανοίγει το αρχείο layout.txt προς εγγραφή

    if(fp1 == NULL) {               // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
        printf("To arxeio layout.txt den mporese na anoixtei.\n");
        exit(1);
    }

    fscanf(fp,"%s %d", pinakida, &theseis);     // Ανάγνωση της πινακίδας και του πλήθους των θέσεων από το αρχείο εισόδου και εκτύπωση τους στην οθόνη
    printf("Pinakida kikloforias:\t%s\nPlithos thesewn:\t%d\n", pinakida, theseis);

    if(theseis > MAXTHESEIS) {                   // Αν οι θέσεις είναι > 53 τότε εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
        printf("\nTo plithos thesewn tou lewforeiou kseperna to megisto epitrepomeno.\n");
        exit(1);
    }

    if((theseis - 5) % 4 != 0) {                // Αν οι θέσεις δεν είναι συμβατές με την επιτρεπόμενη διάταξη τότε εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
        printf("\nTo plithos thesewn tou lewforeiou den simvadizei me tin provlepomeni katanomi.\n");
        exit(1);
    }

    for (i = 0; i < theseis; i++)     // Αρχικοποίηση του μέρους του πίνακα της διάταξης των θέσεων που θα χρησιμοποιηθεί (αρχικά θεωρούνται όλες οι θέσεις με τιμή 0, δηλαδή κενές)
        layout[i] = 0;

    do {            // Χρησιμοποιούμε loop do-while για την επανάληψη υπό συνθήκη της εκτέλεσης του προγράμματος (όσο εκτελείται το πρόγραμμα τα εισηγμένα δεδομένα διατηρούνται)
        // Εκτύπωση του μενού επιλογών
        printf("\n\nPliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n1. Emfanisi sinolikou plithous kenwn thesewn kai twn arithmwn tous\n");
        printf("2. Kratisi sigkekrimenis thesis\n3. Kratisi tis prwtis kenis thesis dipla se parathiro\n4. Akirwsi kratisis thesis\n5. Elegxos diathesimotitas sigkekrimenis thesis\n");
        printf("6. Emfanisi listas kratimenwn thesewn kata arithmo thesis\n7. Emfanisi pinakidas kikloforias kai diagrammatos thesewn ('_' keni thesi, '*' kateilimmeni, ' ' diadromos)\n");
        printf("8. Apothikesfsi pinakidas kai diagrammatos thesewn sto arxeio 'layout.txt'\n0. Eksodos apo to programma\n");
        scanf(" %c", &choice);
        // Εκτέλεση της επιλογής του χρήστη σύμφωνα με το μενού επιλογών
        if (choice == '1') {                                    // Επιλογή εμφάνισης πλήθους κενών θέσεων και αριθμών αυτών
            count = 0;
            for (i = 0; i < theseis; i++) {                     // Καταμετρούνται οι κενές θέσεις και εκτυπώνεται το πλήθος τους
                if (layout[i] == 0)
                    count++;
            }
            printf("\nPlithos kenwn thesewn:\n%d\n", count);    // Εντοπίζονται οι κενές θέσεις και εκτυπώνονται οι αριθμοί τους με αύξουσα σειρά
            printf("\nArithmoi kenwn thesewn:\n");
            for (i = 0; i < theseis; i++) {
                if (layout[i] == 0)
                    printf("%d ", i + 1);
            }
        }
        if (choice == '2') {                                                // Επιλογή κράτησης συγκεκριμένης θέσης
            printf("\nDwse arithmo thesis pros kratisi:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                // Έλεγχος αν είναι υπαρκτή η θέση που δηλώθηκε (αν όχι εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 1)                                 // Αν η θέση είναι κρατημένη εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
                printf("\nH thesi pou epelekses einai idi kratimeni!\n");
            else {                                                          // Αν είναι κενή, κράτηση της (αλλαγή τιμής της σε 1), εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
                layout[num1 - 1] = 1;
                printf("\nH kratisi sou kataxwrithike me epitixia.\n");
            }
        }
        if (choice == '3') {                                                // Επιλογή κράτησης της πρώτης κενής θέσης σε παράθυρο
            num1 = 0;                                                       // Μεταβλητή που εξασφαλίζει ότι δεν θα κρατηθούν πολλαπλές θέσεις μαζί (όταν κρατηθεί θέση παίρνει τιμή 1)
            for (i = 0; i < (theseis - 5); i += 4) {                        // Έλεγχος από την πρώτη μέχρι την τελευταία τετράδα θέσεων για την πρώτη κενή θέση σε παράθυρο (αν υπάρχει)
                if (layout[i] == 0) {                                       // Έλεγχος της πρώτης θέσης στην τετράδα (αν είναι κενή γίνεται κράτηση και έξοδος από τον βρόγχο)
                    layout[i] = 1;
                    printf("\nEgine kratisi stin thesi '%d'.\n", i + 1);
                    num1++;
                    break;
                }
                else if (layout[i + 3] == 0) {                              // Έλεγχος της τελευταίας θέσης στην τετράδα (αν είναι κενή γίνεται κράτηση και έξοδος από τον βρόγχο)
                    layout[i + 3] = 1;
                    printf("\nEgine kratisi stin thesi '%d'.\n", i + 4);
                    num1++;
                    break;
                }
            }
            if (num1 == 0 && layout[theseis - 5] == 0) {                    // Έλεγχος (εφόσον δεν βρέθηκε κενή θέση σε παράθυρο πιο μπροστά) της πρώτης θέσης στην τελευταία πεντάδα θέσων
                layout[theseis - 5] = 1;
                printf("\nEgine kratisi stin thesi '%d'.\n", theseis - 4);
                num1++;
            }
            else if (num1 == 0 && layout[theseis - 1] == 0) {               // Έλεγχος της τελευταίας θέσης στην τελευταία πεντάδα θέσων
                layout[theseis - 1] = 1;
                printf("\nEgine kratisi stin thesi '%d'.\n", theseis);
                num1++;
            }
            else if (num1 == 0)                                                         // Εκτύπωση μηνύματος αν δεν υπάρχουν κενές θέσης σε παράθυρο
                printf("\nDen iparxei alli diathesimi thesi dipla se parathiro.\n");
        }
        if (choice == '4') {                                                            // Επιλογή ακύρωσης κράτησης συγκεκριμένης θέσης
            printf("\nDwse arithmo thesis gia akirwsi kratisis:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                            // Έλεγχος αν είναι υπαρκτή η θέση (αν όχι εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 0)                                             // Αν η θέση είναι κενή εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
                printf("\nGia tin thesi pou epelekses den eixe ginei kratisi!\n");
            else {                                                                      // Αν είναι κρατημένη, ακύρωση (αλλαγή τιμής σε 0), εκτύπωση μηνύματος και επιστροφή στο αρχικό μενού
                layout[num1 - 1] = 0;
                printf("\nH akirwsi tis kratisis kataxwrithike me epitixia.\n");
            }
        }
        if (choice == '5') {                                                            // Επιλογή ελέγχου διαθεσιμότητας θέσης
            printf("\nDwse arithmo thesis gia elegxo diathesimotitas:\n");
            scanf("%d", &num1);
            if (num1 <= 0 || num1 > theseis)                                            // Έλεγχος αν είναι υπαρκτή η θέση (αν όχι εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού)
                printf("\nH thesi pou epelekses den iparxei!\n");
            else if (layout[num1 - 1] == 0)                                             // Αν η θέση είναι κενή εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
                printf("\nH thesi pou epelekses einai diathesimi.\n");
            else printf("\nYparxei kratisi gia tin sugkekrimeni thesi.\n");             // Αλλιώς αν η θέση είναι κρατημένη εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
        }
        if (choice == '6') {                                        // Επιλογή εμφάνισης λίστα κρατημένων θέσεων
            printf("\nArithmoi kratimenwn thesewn:\n");
            for (i = 0; i < theseis; i++) {                         // Εντοπίζονται οι κρατημένες θέσεις και εκτυπώνονται οι αριθμοί τους με αύξουσα σειρά
                if (layout[i] == 1)
                    printf("%d ", i + 1);
            }
        }
        if (choice == '7') {                                                // Επιλογή εμφάνισης πινακίδας λεωφορείου και διάταξης θέσεων στην οθόνη (με "_" οι κενές με "*" οι κρατημένες)
            printf("\n%s\n", pinakida);                                     // Εκτυπώνεται η πινακίδα στην οθόνη
            for (i = 0; i < (theseis - 5); i += 4) {                        // Εκτύπωση της διάταξης των θέσεων για κάθε τετράδα θέσεων διαδοχικά
                layout[i] == 0 ? printf("_") : printf("*");
                layout[i + 1] == 0 ? printf("_ ") : printf("* ");
                layout[i + 2] == 0 ? printf("_") : printf("*");
                layout[i + 3] == 0 ? printf("_\n") : printf("*\n");
            }
            for (i = (theseis - 5); i < theseis; i++)                       // Εκτύπωση της διάταξης των θέσεων για την τελευταία πεντάδα θέσεων του λεωφορείου
                layout[i] == 0 ? printf("_") : printf("*");
                printf("\n");
        }
        if (choice == '8') {                                                        // Επιλογή εξαγωγής πινακίδας λεωφορείου και διάταξης θέσεων στο layout.txt (με "_" οι κενές με "*" οι κρατημένες)
            fprintf(fp1,"%s\n", pinakida);                                          // Εξάγεται η πινακίδα στο αρχείο
            for (i = 0; i < (theseis - 5); i += 4) {                                // Εξαγωγή στο αρχείο της διάταξης των θέσεων για κάθε τετράδα θέσεων διαδοχικά
                layout[i] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
                layout[i + 1] == 0 ? fprintf(fp1, "_ ") : fprintf(fp1, "* ");
                layout[i + 2] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
                layout[i + 3] == 0 ? fprintf(fp1, "_\n") : fprintf(fp1, "*\n");
            }
            for (i = (theseis - 5); i < theseis; i++)                               // Εξαγωγή στο αρχείο της διάταξης των θέσεων για την τελευταία πεντάδα θέσεων του λεωφορείου
                layout[i] == 0 ? fprintf(fp1, "_") : fprintf(fp1, "*");
            printf("\nH pinakida kai to diagramma thesewn apothikeftikan sto arxeio 'layout.txt'.\n");      // Εκτύπωση στην οθόνη μηνύματος επιτυχούς εξαγωγής των δεδομένων στο αρχείο
        }
    } while(choice != '0');     // Το πρόγραμμα θα εκτελεστεί μια φορά και θα επαναλαμβάνεται η εκτέλεση του μέχρι ο χρήστης να επιλέξει την έξοδο, οπότε και θα τερματιστεί επιτυχώς

    fclose(fp);     // Κλείνει το αρχείο εισόδου
    fclose(fp1);    // Κλείνει το αρχείο εξόδου

    return 0;
}
