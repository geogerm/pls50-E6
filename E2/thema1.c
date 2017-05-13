//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε02 - Θέμα 1                ***
//***         Νέο σύστημα καταγραφής κρατημένων θέσεων      ***
//***                     Ακ.έτος 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>         // Λόγω της exit()
#include <string.h>         // Λόγω των strcpy(), strcat(), memcmp()

#define MAXTHESEIS 53       // Ορίζεται ως σταθερά το μέγιστο πλήθος θέσεων

// Ορισμός δόμής για την θέση του λεωφορείου
typedef struct theseis{
    char onomatepwnimo[40];         // Πίνακας αλφαριθμητικών (39 χαρακτήρες + '\0')
    unsigned short tilefwno[10];
    unsigned int arithmos;
} thesi;

// Συνάρτηση για την αρχικοποίηση του πίνακα των θέσεων του λεωφορείου
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

// Συνάρτηση για την ανάγνωση του αρχείου και την καταχώρηση των αρχικών δεδομένων
void readfile(thesi mainarray[], char plate[], int *seats){
    FILE *bus;      // Δήλωση δείκτη-μεταβλητή αρχείου
    // Τοπικές μεταβλητές για την εκτέλεση της συνάρτησης
    char nametemp1[20] = {0};
    char nametemp2[19] = {0};
    int seatstemp, i;
    double tilefwnotemp = 0;         // Έβαλα double γιατί ο long long int έδινε warnings

    bus = fopen ("bus.txt", "r");    // Ανοίγει το αρχείο bus.txt προς ανάγνωση

    // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }

    fscanf(bus, "%s %d\n", plate, seats);
    printf("Pinakida kikloforias:\t%s\nPlithos thesewn:\t%d\n\n", plate, *seats);

    while (!feof(bus)){                                                                    // Μέχρι το πέρας του αρχείου
        fscanf(bus, "%s %s %d %lf\n", nametemp1, nametemp2, &seatstemp, &tilefwnotemp);    // Ανάγνωση κάθε γραμμής του αρχείου που περιέχει εγγραφή
        // Καταχώρηση του τηλεφώνου
        for (i = 9; i >= 0 && tilefwnotemp != 0; i--){
            mainarray[seatstemp - 1].tilefwno[i] = (long long int)tilefwnotemp % 10;
            tilefwnotemp /= 10;
        }
        // Καταχώρηση του ονοματεπώνυμου
        strcpy(mainarray[seatstemp - 1].onomatepwnimo, nametemp1);
        strcat(mainarray[seatstemp - 1].onomatepwnimo, " ");
        strcat(mainarray[seatstemp - 1].onomatepwnimo, nametemp2);
    }
    fclose(bus);     // Κλείσιμο αρχείου για απελευθέρωση μνήμης
    return;
}

// Συνάρτηση για εκτύπωση μενού επιλογών
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

// Συνάρτηση για εκτύπωση κενών θέσεων
void kenestheseis(thesi mainarray[], int seats){
    int i;
    int counter = 0;
    for (i = 0; i < seats; i++){
        if (mainarray[i].onomatepwnimo[0] == '\0')
            counter++;
    }
    printf("Plithos kenwn thesewn:\n%d\n", counter);    // Εντοπίζονται οι κενές θέσεις και εκτυπώνονται οι αριθμοί τους με αύξουσα σειρά
    printf("\nArithmoi kenwn thesewn:\n");
    for (i = 0; i < seats; i++) {
        if (mainarray[i].onomatepwnimo[0] == '\0')
            printf("%d ", i + 1);
    }
    return;
}

// Συνάρτηση για κράτηση θέσης
void kratisithesis(thesi *mainarray, int seatnumber, int seats){
    double tilefwnotemp = 0;         // Έβαλα double γιατί ο long long int έδινε warnings
    int i = 0;

    if (seatnumber <= 0 || seatnumber > seats)                           // Έλεγχος αν είναι υπαρκτή η θέση που δηλώθηκε (αν όχι εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού)
        printf("\nH thesi pou epelekses den iparxei!\n");
    else if (mainarray->onomatepwnimo[0] != '\0')                        // Αν η θέση είναι κρατημένη εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
        printf("\nH thesi pou epelekses einai idi kratimeni!\n");
    else {                                                               // Αν είναι κενή, κράτηση της με εισαγωγή στοιχείων, εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
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

// Συνάρτηση για έλεγχο κράτησης με ονοματεπώνυμο ή τηλέφωνο
void elegxoskratisis(thesi mainarray[], int seats){
    // Τοπικές μεταβλητές για την εκτέλεση της συνάρτησης
    int i;
	int count = 0;
    char choice = 0;
    char nametemp[40] = {0};
    double tilefwnotemp = 0;         // Έβαλα double γιατί ο long long int έδινε warnings
    unsigned short tilefwnot[10];

    printf("Pliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n");
    printf("1. Anazitisi kratisis me onomatepwnimo\n");
    printf("2. Anazitisi kratisis me arithmo tilefwnou\n");
    scanf(" %c", &choice);
    fflush(stdin);                  // Καθάρισμα του χαρακτήρα που έμεινε στο buffer από την scanf()
    printf("\n");

    switch(choice){
        case '1':                   // Αναζήτηση με ονοματεπώνυμο
            printf("Dwse onomatepwnimo (stin morfi 'Epwnymo Onoma') kai pata 'Enter':\n");
            gets(nametemp);
            for (i = 0; i < seats; i++){            // Αρχικός έλεγχος αν υπάρχει έστω και μία κράτηση
                if (strcmp(mainarray[i].onomatepwnimo, nametemp) == 0 && count == 0){
                    printf("\nIparxei sxetiki kratisi stin akolouthi thesi i theseis:   ");
                    count++;
                    break;
                }
            }
            for (i = 0; i < seats; i++){            // Εμφάνιση της θέσης ή των θέσεων που έχουν κρατηθεί
                if (strcmp(mainarray[i].onomatepwnimo, nametemp) == 0 && count != 0){
                    printf(" %d ", i + 1);
                }
            }
            if (count == 0)                         // Αν δεν υπάρχει κράτηση
                printf("\nDen exei ginei kratisi sto onomatepwnimo %s.\n", nametemp);
            break;
        case '2':                   // Αναζήτηση με τηλέφωνο
            printf("Dwse 10psifio arithmo tilefwnou kai pata 'Enter':\n");
            scanf(" %lf", &tilefwnotemp);
            // Καταχώρηση του τηλεφώνου στο προσωρινό array που θα χρησιμοποιηθεί για την σύγκριση.
            for (i = 9; i >= 0 && tilefwnotemp != 0; i--){
                tilefwnot[i] = (long long int)tilefwnotemp % 10;
                tilefwnotemp /= 10;
            }
            for (i = 0; i < seats; i++){            // Αρχικός έλεγχος αν υπάρχει έστω και μία κράτηση
                if (memcmp(mainarray[i].tilefwno, tilefwnot, sizeof(mainarray[i].tilefwno)) == 0 && mainarray[i].onomatepwnimo[0] != '\0' && count == 0){
                    printf("\nIparxei sxetiki kratisi stin akolouthi thesi i theseis:   ");
                    count++;
                    break;
                }
            }
            for (i = 0; i < seats; i++){            // Εμφάνιση της θέσης ή των θέσεων που έχουν κρατηθεί
                if (memcmp(mainarray[i].tilefwno, tilefwnot, sizeof(mainarray[i].tilefwno)) == 0 && count != 0){
                    printf(" %d ", i + 1);
                }
            }
            if (count == 0){                         // Αν δεν υπάρχει κράτηση
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

// Συνάρτηση για ακύρωση κράτησης θέσης
void akirwsikratisis(thesi *mainarray, int seatnumber, int seats){

    if (seatnumber <= 0 || seatnumber > seats)                           // Έλεγχος αν είναι υπαρκτή η θέση που δηλώθηκε (αν όχι εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού)
        printf("\nH thesi pou epelekses den iparxei!\n");
    else if (mainarray->onomatepwnimo[0] == '\0')                        // Αν η θέση είναι ελεύθερη εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
        printf("\nH thesi pou epelekses den eixe kratithei!\n");
    else {                                                               // Αν υπάρχει κράτηση, ακύρωση της, εκτύπωση κατάλληλου μηνύματος και επιστροφή στο αρχικό μενού
        mainarray->onomatepwnimo[0] = '\0';
        printf("\nH kratisi akirwthike me epitixia.\n");
    }
    return;
}

// Συνάρτηση για εκτύπωση λίστας των κρατημένων θέσεων
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

// Συνάρτηση για update του αρχείου και έξοδος από το πρόγραμμα
void swsimokaieksodos(thesi mainarray[], char plate[], int seats){
    FILE *bus;      // Δήλωση δείκτη-μεταβλητή αρχείου
    int i, j;

    bus = fopen ("bus.txt", "w");    // Ανοίγει το αρχείο bus.txt προς εγγραφή
    // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }
    fprintf(bus, "%s %d\n", plate, seats);          // Εκτύπωση της πρώτης γραμμής στο αρχείο
    // Εκτύπωση των επόμενων γραμμών στο αρχείο (που αφορούν τις κρατημένες θέσεις)
    for (i = 0; i < seats; i++){
        if (mainarray[i].onomatepwnimo[0] != '\0'){
            fprintf(bus, "%s %d ", mainarray[i].onomatepwnimo, i + 1);
            for (j = 0; j < 10; j++){
                fprintf(bus, "%hu", mainarray[i].tilefwno[j]);
            }
            fprintf(bus, "\n");
        }
    }
    fclose(bus);                            // Κλείσιμο αρχείου για απελευθέρωση μνήμης
    printf("Ta dedomena apothikeftikan sto arxeio bus.txt me epitixia!\n");
    return;
}

// Κυρίως πρόγραμμα
int main(){
    // Δήλωση μεταβλητών
    thesi lewforeio[MAXTHESEIS];        // Μονοδιάστατος πίνακας όλων των θέσεων
    char pinakida[8] = {0};             // Πίνακας αλφαριθμητικών για την πινακίδα του λεωφορείου (7 χαρακτήρες + '\0')
    int theseis = 0;
    int arithmosthesis = 0;
    char epilogi = 0;

    // Αρχικοποίηση πίνακα και ανάγνωση δεδομένων από αρχείο
    initializebus(lewforeio);
    readfile(lewforeio, pinakida, &theseis);

    while (1){          //Infinite loop που θα διακοπεί μόνο με την επιλογή 0 (λόγω του return)
        menuepilogwn();
        scanf(" %c", &epilogi);
        printf("\n");
        switch(epilogi){
            case '1':                                   // Εκτύπωση κενών θέσεων
                kenestheseis(lewforeio, theseis);
                break;
            case '2':                                   // Κράτηση συγκεκριμένης θέσης
                printf("Dwse arithmo thesis pros kratisi:\n");
                scanf(" %d", &arithmosthesis);
                fflush(stdin);                  // Καθάρισμα του χαρακτήρα που έμεινε στο buffer από την scanf()
                kratisithesis(&lewforeio[arithmosthesis - 1], arithmosthesis, theseis);
                break;
            case '3':                                   // Έλεγχος κράτησης θέσης με όνομα ή τηλέφωνο
                elegxoskratisis(lewforeio, theseis);
                break;
            case '4':                                   // Ακύρωση κράτησης συγκεκριμένης θέσης
                printf("Dwse arithmo thesis pros akirwsi kratisis:\n");
                scanf(" %d", &arithmosthesis);
                fflush(stdin);                  // Καθάρισμα του χαρακτήρα που έμεινε στο buffer από την scanf()
                akirwsikratisis(&lewforeio[arithmosthesis - 1], arithmosthesis, theseis);
                break;
            case '5':                                   // Εκτύπωση λίστας κρατημένων θέσεων
                ektipwsikratisewn(lewforeio, theseis);
                break;
            case '0':                                   // Update του αρχείου και έξοδος από το πρόγραμμα
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

// Σύνοψη αποτελεσμάτων εξόδου:
// 0:   Kανένα σφάλμα. Το πρόγραμμα εκτελέστηκε με επιτυχία.
//-1:   Δεν ήταν δυνατό να αναγνωστεί το αρχείο.
