//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε02 - Θέμα 2                ***
//***    Επέκταση συστήματος καταγραφής κρατημένων θέσεων   ***
//***                     Ακ.έτος 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>         // Λόγω της exit()
#include <string.h>         // Λόγω των strcpy(), strcmp(), strcat(), memcmp()

// Ορισμός δόμής για την θέση του λεωφορείου
typedef struct theseis{
    char onomatepwnimo[40];         // Πίνακας αλφαριθμητικών (39 χαρακτήρες + '\0')
    unsigned short tilefwno[10];
    unsigned int arithmos;
} thesi;

// Δομή της συνδεδεμένης λίστας
struct node{
    thesi seatdata;                 // Data
    struct node *next;              // Address
};
struct node *head = NULL;

// Συνάρτηση για την ανάγνωση του αρχείου και την καταχώρηση των αρχικών δεδομένων
void readfileopen(char plate[], int *seats){
    FILE *bus;      // Δήλωση δείκτη-μεταβλητή αρχείου

    bus = fopen ("bus.txt", "r");    // Ανοίγει το αρχείο bus.txt προς ανάγνωση

    // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }

    fscanf(bus, "%s %d\n", plate, seats);
    printf("Pinakida kikloforias:\t%s\nPlithos thesewn:\t%d\n\n", plate, *seats);
    fclose(bus);     // Κλείσιμο αρχείου για απελευθέρωση μνήμης
    return;
}

// Συνάρτηση για την αρχικοποίηση του πίνακα των θέσεων του λεωφορείου
void initializebus(thesi mainarray[], int seats){
    int i, j;

    for (i = 0; i < seats; i++){
        mainarray[i].onomatepwnimo[0] = '\0';
        mainarray[i].arithmos = i+1;
        for (j = 0; j < 10; j++){
            mainarray[i].tilefwno[j] = 0;
        }
    }
    return;
}

// Συνάρτηση για την ανάγνωση και καταχώρηση των κρατημένων θέσεων από το αρχείο και το κλείσιμο του
void readfileclose(thesi mainarray[]){
    FILE *bus;      // Δήλωση δείκτη-μεταβλητή αρχείου
    // Τοπικές μεταβλητές για την εκτέλεση της συνάρτησης
    char nametemp1[20] = {0};
    char nametemp2[19] = {0};
    int seatstemp, i;
    double tilefwnotemp = 0;         // Έβαλα double γιατί ο long long int έδινε warnings
    char buffer[100];

    bus = fopen ("bus.txt", "r");    // Ανοίγει το αρχείο bus.txt προς ανάγνωση
    // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }
    fgets(buffer, 100, bus);        //Προσπερνάει την πρώτη ήδη διαβασμένη γραμμή

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
    printf("5. Emfanisi listas kratimenwn thesewn kata afksonta arithmo thesis i taksinomemini kata onomatepwnimo\n");
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

// Συνάρτηση για εκτύπωση λίστας των κρατημένων θέσεων κατά αριθμό θέσης ή ονοματεπώνυμο
void ektipwsikratisewn(thesi mainarray[], int seats){
     // Τοπικές μεταβλητές για την εκτέλεση της συνάρτησης
    int i, j;
    int count = 1;
    char choice = 0;
    thesi swap;

    // Τοπικές μεταβλητές για την εκτέλεση της συνάρτησης

    printf("Pliktrologise ton arithmo tis leitourgias pou se endiaferei kai pata 'Enter':\n");
    printf("1. Emfanisi listas kata afksonta arithmo thesis\n");
    printf("2. Emfanisi listas taksinomemini kata onomatepwnimo\n");
    scanf(" %c", &choice);
    printf("\n");

    switch(choice){
        case '1':                   // Εκτύπωση λίστας κατά αριθμό θέσης
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
            break;
        case '2':                  // Εκτύπωση λίστας κατά ονοματεπώνυμο
            //Χρήση αλγορίθμου bubblesort για ταξινόμηση κατά ονοματεπώνυμο
            for (i = 0 ; i < ( seats - 1 ); i++){
                for (j = 0 ; j < seats - i - 1; j++){
                    if (strcmp(mainarray[j].onomatepwnimo, mainarray[j+1].onomatepwnimo) > 0){
                        swap = mainarray[j];
                        mainarray[j] = mainarray[j+1];
                        mainarray[j+1] = swap;
                    }
                }
            }
            // Εκτύπωση της λίστας
            for (i = 0; i < seats; i++){
                if (mainarray[i].onomatepwnimo[0] != '\0'){
                    printf("%d. %-40s   ", count, mainarray[i].onomatepwnimo);
                    for (j = 0; j < 10; j++){
                        printf("%hu", mainarray[i].tilefwno[j]);
                    }
                    printf("        %2d\n", mainarray[i].arithmos);
                    count++;
                }
            }
            //Χρήση bubblesort για επαναφορά σε ταξινόμηση κατά αριθμό θέσης
            for (i = 0 ; i < ( seats - 1 ); i++){
                for (j = 0 ; j < seats - i - 1; j++){
                    if (mainarray[j].arithmos > mainarray[j+1].arithmos){
                        swap = mainarray[j];
                        mainarray[j] = mainarray[j+1];
                        mainarray[j+1] = swap;
                    }
                }
            }
            break;
        default:
            break;
    }
    return;
}

// Συνάρτηση που κάνει χρήση αλγορίθμου bubblesort για ταξινόμηση κατά ονοματεπώνυμο για τις τελευταίες λειτουργίες πριν την έξοδο από το πρόγραμμα
void lastsorting(thesi mainarray[], int seats){
    int i, j = 0;
    thesi swap;

    for (i = 0 ; i < ( seats - 1 ); i++){
        for (j = 0 ; j < seats - i - 1; j++){
            if (strcmp(mainarray[j].onomatepwnimo, mainarray[j+1].onomatepwnimo) > 0){
                swap = mainarray[j];
                mainarray[j] = mainarray[j+1];
                mainarray[j+1] = swap;
            }
        }
    }
    return;
}

// Εισαγωγή με αναδρομή κάθε στοιχείου του πίνακα που αφορά κράτηση στο τέλος της linked list
void insertarraytolist(thesi mainarray[], int start, int seats){
    struct node *newNode, *temp;

    newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Den itan dinati i paraxwrisi mnimis!");
        exit(-2);
    }
    if (start >= seats)         //Συνθήκη εξόδου από την αναδρομή
        return;

    if (mainarray[start].onomatepwnimo[0] != '\0'){
        newNode->seatdata = mainarray[start];           // Συνδέονται τα δεδομένα

        newNode->next = NULL;

        // Αν είναι ο πρώτος κόμβος
        if(head == NULL)
            head = newNode;                             // Συνδέεται η διέυθυνση (1η περίπτωση)

        // Αν δεν είναι ο πρώτος κόμβος
        else{

        temp = head;

        //Διάσχιση στον τελευταίο κόμβο
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;                           // Συνδέεται η διέυθυνση (2η περίπτωση)
        }
    }
    insertarraytolist(mainarray, start + 1, seats);     // Αναδρομική κλήση
}

// Συνάρτηση για αποθήκευση των δεδομένων της συνδεδεμένης λίστας στο αρχείο και έξοδος από το αρχείο
void swsimokaieksodos(char plate[], int seats){
    FILE *bus;      // Δήλωση δείκτη-μεταβλητή αρχείου
    struct node *temp;
    int i = 0;

    bus = fopen ("bus.txt", "w");    // Ανοίγει το αρχείο bus.txt προς εγγραφή
    // Σε περίπτωση προβλήματος κατά το άνοιγμα εκτυπώνεται μήνυμα λάθους και το πρόγραμμα τερματίζεται με ένδειξη αποτυχίας
    if (bus == NULL){
        printf("To arxeio bus.txt den itan dinato na anagnwstei.");
        exit(-1);
    }

    fprintf(bus, "%s %d\n", plate, seats);          // Εκτύπωση της πρώτης γραμμής στο αρχείο
    // Εκτύπωση των επόμενων γραμμών στο αρχείο (που αφορούν τις κρατημένες θέσεις) μέσω διασχίσεως της λίστας.
    temp = head;
    while(temp != NULL){
        fprintf(bus, "%s %d ", temp->seatdata.onomatepwnimo, temp->seatdata.arithmos);
        for (i = 0; i < 10; i++){
            fprintf(bus, "%hu", temp->seatdata.tilefwno[i]);
        }
        fprintf(bus, "\n");
        temp = temp->next;                    // Προχωρά στον επόμενο κόμβο
    }
    fclose(bus);                            // Κλείσιμο αρχείου για απελευθέρωση μνήμης
    printf("Ta dedomena apothikeftikan sto arxeio bus.txt me epitixia!\n");
    return;
}

// Κυρίως πρόγραμμα
int main(){
    // Δήλωση μεταβλητών
    thesi *lewforeio;                   // Δείκτης προς την επιθυμητή δομή
    char pinakida[8] = {0};             // Πίνακας αλφαριθμητικών για την πινακίδα του λεωφορείου (7 χαρακτήρες + '\0')
    int theseis;
    int arithmosthesis = 0;
    char epilogi = 0;

    readfileopen(pinakida, &theseis);                        // Άνοιγμα του αρχείου και διάβασμα των αρχικών στοιχείων (πινακίδα, πλήθος θέσεων)
    lewforeio = (thesi *)malloc(theseis * sizeof(thesi));    // Παραχώρηση μνήμης για όλες τις θέσεις του λεωφορείου
    if (lewforeio == NULL){
        printf("Den itan dinati i paraxwrisi mnimis!");
        exit(-2);
    }

    initializebus(lewforeio, theseis);      // Αρχικοποίηση πίνακα
    readfileclose(lewforeio);               // Καταχώρηση των δεδομένωn για τις υφιστάμενες κρατήσεις από το αρχείο και κλείσιμο του

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
            case '5':                                   // Εκτύπωση λίστας κρατημένων θέσεων κατά αριθμό θέσης ή ονοματεπώνυμο
                ektipwsikratisewn(lewforeio, theseis);
                break;
            case '0':                                               // Update του αρχείου και έξοδος από το πρόγραμμα
                lastsorting(lewforeio, theseis);                    // Τελευταία ταξινόμηση κατά ονοματεπώνυμο
                insertarraytolist(lewforeio, 0, theseis);           // Αναδρομική εισαγωγή όλων των στοιχείων που αφορόυν κρατήσεις στο τέλος της συνδεδεμένης λίστας
                swsimokaieksodos(pinakida, theseis);                // Αποθήκευση των δεδομένων στο αρχείο από την συνδεδεμένη λίστα και έξοδος από το αρχείο
                free(lewforeio);                                    // Απελευθερώνουμε την μνήμη που είχαμε δεσμεύσει
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
//-2:   Δεν ήταν δυνατή η παραχώρηση μνήμης.
