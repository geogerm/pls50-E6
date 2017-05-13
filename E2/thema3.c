//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε02 - Θέμα 3                ***
//***            Υλοποίηση Παραλλαγής Παιχνιδιού SET        ***
//***                     Ακ.έτος 2016-17                   ***
//***                                                       ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>     // Λόγω των srand(), rand(), exit()
#include <string.h>     // Λόγω της strncpy()
#include <time.h>       // Λόγω της time()

// Δομή για τους παίχτες
typedef struct paixtis{
    char name[17];
    unsigned char score;    // Για οικονομία μνήμης αφού θέλουμε τιμή 0-255
    char id;
} player;

// Δομή για τις κάρτες
typedef struct karta{
    char idiotites[5];      // 4 ιδιότητες και το \0
    char used;              // Ελέγχει αν χρησιμοποιήθηκε ή όχι η κάρτα. Για οικονομία μνήμης το char αφού θέλουμε τιμή 0-255
} card;

// Ορισμός μεταβλητών δομών των τριών παιχτών ως global variables και ανάθεση τιμών
player a = {"Marina Andreou", 0, 'a'};
player g = {"Kostas Grammenos", 0, 'g'};
player p = {"Maria Perdika", 0, 'p'};

// Συνάρτηση για "γέμισμα" της τράπουλας με όλους τους δυνατούς συνδυασμούς καρτών
void initializeFullDeck(card fulldeck[]){
    int i, j, k, l;
    int count = 0;

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            for (k = 0; k < 3; k++){
                for (l = 0; l < 3; l++){
                    // Χρώμα (θέση 0)
                    if (i == 0) fulldeck[count].idiotites[0] = 'r';
                    if (i == 1) fulldeck[count].idiotites[0] = 'g';
                    if (i == 2) fulldeck[count].idiotites[0] = 'b';
                    // Σχήμα (θέση 1)
                    if (j == 0) fulldeck[count].idiotites[1] = 'c';
                    if (j == 1) fulldeck[count].idiotites[1] = 't';
                    if (j == 2) fulldeck[count].idiotites[1] = 'r';
                    // Αριθμός (θέση 2)
                    if (k == 0) fulldeck[count].idiotites[2] = '1';
                    if (k == 1) fulldeck[count].idiotites[2] = '2';
                    if (k == 2) fulldeck[count].idiotites[2] = '3';
                    // Υφή (θέση 3)
                    if (l == 0) fulldeck[count].idiotites[3] = 'b';
                    if (l == 1) fulldeck[count].idiotites[3] = 'h';
                    if (l == 2) fulldeck[count].idiotites[3] = 'e';
                    fulldeck[count].idiotites[4] = '\0';     // Ανάθεση του '\0' στην τελευταία θέση του string
                    fulldeck[count].used = 0;                // Χαρακτηρισμός της κάρτας ως μη επιλεγμένη
                    count++;                                 // Επόμενη κάρτα
                }
            }
        }
    }
    return;
}

// Συνάρτηση για επιλογή της επόμενης μη επιλεγμένης κάρτας
int getNextCard(card fulldeck[]){
    int i = 0;
    do {
        i = 80 * rand() / RAND_MAX;      // Παίρνει τυχαίες τιμές από 0 έως 80 (καλύπτει όλες τις κάρτες της τράπουλας)
    } while (fulldeck[i].used == 1);     // Ο βρόγχος τρέχει μέχρι να βρεθεί κάρτα που να μην έχει ήδη επιλεχθή
    fulldeck[i].used = 1;                // Η κάρτα αποκτά πλέον σήμανση επιλεγμένης
    return i;
}

// Συνάρτηση για "γέμισμα" του πλέγματος των 12 καρτών με κάρτες
void getNextPlaydeck(card fulldeck[], card gamedeck[][4]){
    int i, j = 0;
    // Βρόγχος για "Γέμισμα" του πλέγματος
    for (i = 0; i < 3; i++){
        for (j = 0; j < 4; j++){
            strcpy(gamedeck[i][j].idiotites, fulldeck[getNextCard(fulldeck)].idiotites);    //  Αντιγράφει στο στοιχείο του πλέγματος την κάρτα που μας έδωσε η getNextCard()
        }
    }
    // Βρόγχος για επαναφορά όλων των καρτλων της τράπουλας σε κατάσταση μη επιλεγμένης
    for (i = 0; i < 81; i++){
        fulldeck[i].used = 0;
    }
    return;
}

// Συνάρτηση για εμφάνιση του πλέγματος των καρτών που "παίζουν" στην οθόνη
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

// Συνάρτηση για ανάγνωση σωστών συντεταγμένων
void checkcoordinates(int *x, int *y){
    do {                                //Βρόγχος που επαναλαμβάνεται μέχρι να δωθούν τιμές εντός ορίων
        printf("Dwse to x (tin grammi pou vrisketai i karta) apo 0 ews kai 2:\n");
        scanf(" %d", x);
        printf("Dwse to y (tin stili pou vrisketai i karta) apo 0 ews kai 3:\n");
        scanf(" %d", y);
        if (*x < 0 || *x > 2 || *y < 0 || *y > 3)
            printf("Exeis eisagei times ektos twn oriwn tou plegmatos. Dwse ksana syntetagmenes:\n");
    } while (*x < 0 || *x > 2 || *y < 0 || *y > 3);
    return;
}
// Συνάρτηση για έλεγχο αν έχει γίνει SET
int checkSet(card gamedeck[][4], int x1, int y1, int x2, int y2, int x3, int y3){
    int i;
    int count = 0;

    // Έλεγχος για κάθεμια ιδιότητα από τις 4 με βρόγχο
    for (i = 0; i < 4; i++){
        // Έλεγχος αν είναι όλα τα στοιχεία όμοια ή όλα διαφορετικά
        if ((gamedeck[x1][y1].idiotites[i] == gamedeck[x2][y2].idiotites[i] && gamedeck[x1][y1].idiotites[i] == gamedeck[x3][y3].idiotites[i]) ||
        (gamedeck[x1][y1].idiotites[i] != gamedeck[x2][y2].idiotites[i] && gamedeck[x1][y1].idiotites[i] != gamedeck[x3][y3].idiotites[i] && gamedeck[x2][y2].idiotites[i] != gamedeck[x3][y3].idiotites[i])){
            count++;        // Για κάθε ιδιότητα που πληρεί τις συνθήκες αυξάνεται κατά 1 το count
        }
    }
    if (count == 4)         // Αν και οι 4 ιδιότητες των τριών καρτών πληρούν τις συνθήκες έχουμε SET και επιστρέφεται τιμή 1
        return 1;
    else                    // Αλλιώς δεν έχουμε SET και επιστρέφεται τιμή 0
        return 0;
}

// Συνάρτηση για παίξιμο γύρου
void playgame(card fulldeck[], card gamedeck[][4], player *pl){
    int x1, y1, x2, y2, x3, y3;       // Μεταβλητές για συντεταγμένες καρτών
    // Εισαγωγή και έλεγχος συντεταγμένων καρτών
    printf("%s dwse tis syntetagmenes tis prwtis kartas kai pata 'Enter'.\n", pl->name);
    checkcoordinates(&x1, &y1);
    printf("Dwse tis syntetagmenes tis defteris kartas kai pata 'Enter'.\n");
    checkcoordinates(&x2, &y2);
    printf("Dwse tis syntetagmenes tis tritis kartas kai pata 'Enter'.\n");
    checkcoordinates(&x3, &y3);
    printf("\n");
    // Έλεγχος ότι δεν έχει επιλεγεί 2 ή 3 φορές η ίδια κάρτα από το πλέγμα
    if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)){
        printf("Exeis epileksei 2 i 3 fores tin idia karta apo to plegma. Epanepilogi paixti.\n\n");
        viewPlaydeck(gamedeck);
        return;
    }
    // Αν οι κάρτες αποτελούν SET
    if (checkSet(gamedeck, x1, y1, x2, y2, x3, y3) == 1){
        printf("%s oi kartes poy epelekses apoteloun SET!\n", pl->name);
        printf("Kerdises 2 pontous!!\n");
        pl->score += 2;
        if (pl->score >= 10){       // Αν ο ενεργός παίχτης έφτασε τους 10 πόντους έχουμε τερματισμό του προγράμματος
            printf("\nTelos paixnidiou. Exoume nikhth!\n\n");
            printf("            Name                Score      ID\n");
            printf("            ---------------------------------\n");
            printf("            %-16s       %2hu       %c\n", a.name, a.score, a.id);
            printf("            %-16s       %2hu       %c\n", g.name, g.score, g.id);
            printf("            %-16s       %2hu       %c\n", p.name, p.score, p.id);
            printf("\n\nO nikhths einai o/h %s!!\n", pl->name);
            exit(0);        // Γίνεται έξοδος από το πρόγραμμα με ένδειξη επιτυχημένης εκτέλεσης
        }
        printf("\nNeos gyros paixnidiou. Oi kartes anakateftikan.\n\n");
        getNextPlaydeck(fulldeck, gamedeck);
        viewPlaydeck(gamedeck);
    }
    // Αν οι κάρτες δεν αποτελούν SET
    else {
        printf("%s oi kartes poy epelekses den apoteloun SET.\n", pl->name);
        printf("Xaneis 1 ponto!!\n");
        if (pl->score >= 1){       // Αν ο παίχτης έχει τουλάχιστον 1 πόντο αφαιρείται 1 πόντος
            pl->score -= 1;
        }
        printf("\nTo paixnidi synexizetai.\n\n");
        viewPlaydeck(gamedeck);
    }
    return;
}

// Κυρίως πρόγραμμα
int main(){
    // Ορισμός μεταβλητών
    card deck[81];          // Πίνακας δομών με τις συνολικές κάρτες (τράπουλα)
    card playdeck[3][4];    // Δισδιάστατος πίνακας δομών με τις επιλεγμένες για την παρτίδα κάρτες. Έχουμε άχρηστο το στοιχείο used αλλά η χρήση δομής εξυπηρετεί καλύτερα την υλοποίηση
    char epilogi = 0;

    srand(time(NULL));      // Αρχικοποίηση της rand()

    initializeFullDeck(deck);           // "Γέμισμα" της τράπουλας με όλους τους δυνατούς συνδυασμούς καρτών
    getNextPlaydeck(deck, playdeck);    // "Γέμισμα" του πλέγματος των 12 καρτών με κάρτες
    printf("\nTo paixnidi ksekinise! Kali epityxia!\n\n");
    viewPlaydeck(playdeck);             // Εμφάνιση των καρτών που "παίζουν" στην οθόνη


    while (1){          //Infinite loop που θα διακοπεί μόνο με την επιλογή 0 (λόγω του return)
        printf("Dwse to ID tou paixti (ena ek twn a, g, p) i to 0 gia eksodo kai pata 'Enter':\n");
        scanf(" %c", &epilogi);
        printf("\n");
        switch(epilogi){
            case 'a':                                   // Παίζει η Μαρίνα
                playgame(deck, playdeck, &a);
                break;
            case 'g':                                   // Παίζει ο Κώστας
                playgame(deck, playdeck, &g);
                break;
            case 'p':                                   // Παίζει η Μαρία
                playgame(deck, playdeck, &p);
                break;
            case '0':                                   // Εκτύπωση των στοιχείων των παιχτών και έξοδος από το πρόγραμμα
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

// Σύνοψη αποτελεσμάτων εξόδου:
// 0:   Kανένα σφάλμα. Το πρόγραμμα εκτελέστηκε με επιτυχία.
