#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void *malloc(size_t size);
char cardDeck[52];
int deckSize = 52;
char input[50];
char file[30];
char message[5];
char *cardsPointer = cardDeck;
bool hasPlayerWon = false;
FILE *filePointer;


void defaultBoard();
void QQ();
void setupDeck();
void LD(char file[]);
void SW();
void userInput();
void SD(char file[], char *cardDeck);
void SR();

typedef struct node{
    char value;
    char suits;
    struct node* next;
    struct node* prev;
} node;

struct node* head = NULL;
struct node* prevNode = NULL;
struct node* C1head = NULL;
struct node* C1tail = NULL;
struct node* C2head = NULL;
struct node* C2tail = NULL;
struct node* C3head = NULL;
struct node* C3tail = NULL;
struct node* C4head = NULL;
struct node* C4tail = NULL;
struct node* C5head = NULL;
struct node* C5tail = NULL;
struct node* C6head = NULL;
struct node* C6tail = NULL;
struct node* C7head = NULL;
struct node* C7tail = NULL;


struct node* tableCollumns[7] = {NULL, NULL, NULL,NULL,NULL,NULL,NULL};
struct node* tableFoundations[4] = {NULL, NULL, NULL,NULL};
struct node *ShuffleDeckHead = NULL;

struct node *addFirst(char value, char suits){

    node * newNode = malloc(sizeof (node));
    newNode -> value = value;
    newNode -> suits = suits;
    newNode -> next = NULL;
    newNode -> prev = NULL;
    head = newNode;
    prevNode = newNode;
    return newNode;

}
struct node *addNext(char value, char suits){

    node * newNode = malloc(sizeof (node));
    prevNode -> next = newNode;
    newNode -> value = value;
    newNode -> suits = suits;
    newNode -> next = NULL;
    newNode -> prev = prevNode;
    prevNode = newNode;
    return newNode;
}

void defaultBoard(){
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
    printf("\n");
    printf("\t\t\t\t\t\t\t\t[]\tF1");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t\t[]\tF2");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t\t[]\tF3");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t\t[]\tF4");
}

void QQ() {
    printf("hej");
    _Exit(0);
}

void setupDeck(){
    printf("\nWhich file would you like to load: ");
    scanf("%s",&file);
    FILE *filePointer;
    filePointer = fopen (file,"r");

    while(!filePointer){
        printf("Invalid File Name, try again\n");
        printf("\nWhich file would you like to load: ");
        scanf("%s",&file);
        filePointer = fopen (file,"r");
    }

    for (int i = 0; i < deckSize*2 ; ++i) {

        fscanf(filePointer,"%c\n",&cardDeck[i]);
        //printf("%c\n", cardDeck[i]);

    }
    //printf("setupDeck Works\n");
    //printf(cardDeck);


}

void HELP(){
    printf("The Following commands are valid: LD, SW, QQ, PP, HELP");
}

void LD(char file[]) {

    if(filePointer != NULL){
        printf("\nYou have already loaded this file, Try another function: ");
        return;
    }

    setupDeck(file);
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7");
    printf("\n");
    int a = 0;
    int b = 1;

    for (int i = 0; i < deckSize * 2; i += 2) {

        if (head == NULL) {
            head = addFirst(cardDeck[i], cardDeck[i + 1]);
        } else {
            addNext(cardDeck[i], cardDeck[i + 1]);
        }
    }
    for (int i = 0; i < deckSize; i++) {
        printf("[]");
        printf("\t");
        a++;

        if (a % 7 == 0) {
            if (b == 1) {
                printf("\t[]\tF1");
            }
            if (b == 3) {
                printf("\t[]\tF2");
            }
            if (b == 5) {
                printf("\t[]\tF3");
            }
            if (b == 7) {
                printf("\t[]\tF4");
            }
            printf("\n");
            b++;
        }
        //userInput(); DEN FUCKER ALT
    }
    //printf("\nLD Works\n");
}

void SW() {
    int incrementer = 0;
    node *currentNode = head;
    int b = 1;

    if(filePointer == NULL){
        printf("\nNo File has been loaded yet, try LD first: ");
        return;
    }

    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7");
    printf("\n");

    while ( currentNode != NULL ) {
        incrementer++;
        if(incrementer > 7) {
            printf("\n%c%c\t", currentNode->value, currentNode->suits);
            currentNode = currentNode->next;
            b++;
            incrementer=1;
        }
        else{
            printf("%c%c\t", currentNode->value, currentNode->suits);
            currentNode = currentNode->next;
            if(incrementer == 7){
                if (b == 1) {
                    printf("\t[]\tF1");
                }
                if (b == 3) {
                    printf("\t[]\tF2");
                }
                if (b == 5) {
                    printf("\t[]\tF3");
                }
                if (b == 7) {
                    printf("\t[]\tF4");
                }
            }
        }
    }
    //printf("\nSW Works");
}

void dealCards(struct node* headerDeck) {


    int row = 1;
    struct node *tempNextHolder;
    struct node *temp = headerDeck;

    while (row < 8 ) {

        tempNextHolder = temp;


        for (int i = 0; i < row; i++) {

            if (tableCollumns[row] == NULL) {
                //start med et linkedlist
                tableCollumns[row] = temp;
                temp = temp->next;

                tempNextHolder->next = NULL;
                tempNextHolder->prev = NULL;

                //printf("CHECK - Value: %c | Suit: %c is Header for Collumn %d\n", tempNextHolder->value,
                //tempNextHolder->suits, row);
                printf("%c%c\t",tempNextHolder->value,tempNextHolder->suits);



            } else {

                //tilføj tl loinkedlist
                tempNextHolder = temp;
                temp = temp->next;

                tempNextHolder->prev->next = tempNextHolder;
                tempNextHolder->next = NULL;

                //printf("CHECK - Value: %c | Suit: %c is in succesion of Value: %c | Suit: %c for Collumn %d\n",
                //tempNextHolder->value, tempNextHolder->suits, tempNextHolder->prev->value,
                //tempNextHolder->prev->suits, row);

                printf("%c%c\t",tempNextHolder->value,tempNextHolder->suits);
            }


        }


        row++;


    }
}

void SD(char file[], char *cardDeck) {
    FILE *filePointer;
    if (strlen(file) == 0) {
        filePointer = fopen("cards.txt", "w");
    } else {
        filePointer = fopen(file, "w");
    }
    for (int i = 0; i < 104; i+= 2) {
        fprintf(filePointer, "%c", cardDeck[i]);
        fprintf(filePointer, "%c\n", cardDeck[i + 1]);
    }
    fclose(filePointer);
}

void printfun(){
    dealCards(head);
    printf("\n\n\n\n\n");
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n");

    //Linje 1 START
    struct node *tempC1 = tableCollumns[1];
    printf("%c%c\t", tempC1->value,tempC1->suits);

    struct node *tempC2 = tableCollumns[2];
    printf("%c%c\t", tempC2->value,tempC2->suits);

    struct node *tempC3 = tableCollumns[3];
    printf("%c%c\t", tempC3->value,
           tempC3->suits);

    struct node *tempC4 = tableCollumns[4];
    printf("%c%c\t", tempC4->value,
           tempC4->suits);

    struct node *tempC5 = tableCollumns[5];
    printf("%c%c\t", tempC5->value,
           tempC5->suits);

    struct node *tempC6 = tableCollumns[6];
    printf("%c%c\t", tempC6->value,
           tempC6->suits);

    struct node *tempC7 = tableCollumns[7];
    printf("%c%c", tempC7->value,
           tempC7->suits);

    printf("\t []\tF1\n");

    //Linje 2 START
    if(tempC1->next == NULL){
        printf("  \t");
    }

    if(tempC2->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC2->next->value,tempC2->next->suits);
    }

    if(tempC3->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC3->next->value,tempC3->next->suits);
    }

    if(tempC4->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC4->next->value,tempC4->next->suits);
    }
    if(tempC5->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC5->next->value,tempC5->next->suits);
    }
    if(tempC6->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC6->next->value,tempC6->next->suits);
    }
    if(tempC7->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\n", tempC7->next->value,tempC7->next->suits);
    }

    //Linje 3 START
    if(tempC1->next == NULL){
        printf("  \t");
    }

    if(tempC2->next->next == NULL){
        printf("  \t");
    }

    if(tempC3->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC3->next->next->value,tempC3->next->next->suits);
    }

    if(tempC4->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC4->next->next->value,tempC4->next->next->suits);
    }

    if(tempC5->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC5->next->next->value,tempC5->next->next->suits);
    }

    if(tempC6->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC6->next->next->value,tempC6->next->next->suits);
    }

    if(tempC7->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c", tempC7->next->next->value,tempC7->next->next->suits);
    }
    printf("\t []\tF2\n");

    //Linje 4 Start
    if(tempC1->next == NULL){
        printf("  \t");
    }

    if(tempC2->next->next == NULL){
        printf("  \t");
    }

    if(tempC3->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC3->next->next->value,tempC3->next->next->suits);
    }

    if(tempC4->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC4->next->next->next->value,tempC4->next->next->next->suits);
    }

    if(tempC5->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC5->next->next->next->value,tempC5->next->next->next->suits);
    }

    if(tempC6->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC6->next->next->next->value,tempC6->next->next->next->suits);
    }

    if(tempC7->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\n", tempC7->next->next->next->value,tempC7->next->next->next->suits);
    }

    //Linje 5 START
    if(tempC1->next == NULL){
        printf("  \t");
    }

    if(tempC2->next->next == NULL){
        printf("  \t");
    }

    if(tempC3->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC4->next->next->next->next == NULL){
        printf("  \t");
    }

    if(tempC5->next->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC5->next->next->next->next->value,tempC5->next->next->next->next->suits);
    }

    if(tempC6->next->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c\t", tempC6->next->next->next->next->value,tempC6->next->next->next->next->suits);
    }

    if(tempC7->next->next->next->next == NULL){
        printf("  \t");
    }
    else{
        printf("%c%c", tempC7->next->next->next->next->value,tempC7->next->next->next->next->suits);
    }
    printf("\t []\tF3\n");

    //Linje 6 Start
    if(tempC1->next == NULL){
        printf("  \t");
    }
    if(tempC2->next->next == NULL){
        printf("  \t");
    }
    if(tempC3->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC4->next->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC5->next->next->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC6->next->next->next->next->next == NULL){
        printf("  \t");
    }
    else {
        printf("%c%c\t", tempC6->next->next->next->next->next->value, tempC6->next->next->next->next->next->suits);
    }

    if(tempC7->next->next->next->next->next == NULL){
        printf("  \t");
    }
    else {
        printf("%c%c\n", tempC7->next->next->next->next->next->value, tempC7->next->next->next->next->next->suits);
    }

    //Linje 7 START
    if(tempC1->next == NULL){
        printf("  \t");
    }
    if(tempC2->next->next == NULL){
        printf("  \t");
    }
    if(tempC3->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC4->next->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC5->next->next->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC6->next->next->next->next->next->next == NULL){
        printf("  \t");
    }
    if(tempC7->next->next->next->next->next->next == NULL){
        printf("  \t");
    }
    else {
        printf("%c%c", tempC7->next->next->next->next->next->next->value, tempC7->next->next->next->next->next->next->suits);
    }
    printf("\t []\tF4\n");

}

node *pop(node *head) {
    node *temp;
    if (head->next != NULL) {
        temp = head;
        head = head->next;
        temp->next = NULL;
        temp->prev = NULL;
        head->prev = NULL;
        return temp;

    } else {
        return NULL;
    }
}


void SR() {
    node *temp;
    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        temp = pop(head);


        node *current;

        if (ShuffleDeckHead == NULL) {
            ShuffleDeckHead = temp;
        }

        for (int i = 0; i < rand() % 52; i++) {
            current = current->next;
        }

        node *temp = current->next;
        current->next = temp;
        temp->next = temp;
        temp->prev = current;
        temp->next->prev = temp;

    }

}




void userInput() {
    printf("\n\nLAST COMMAND: %c%c", input[0], input[1]);
    printf("\nMessage: %c%c", message[0], message[1]);
    printf("\nINPUT > ");
    scanf("%s", input);
    switch (input[0]) {
        case 'Q':
        case 'q':
            if ((input[1] == 'Q' || input[1] == 'q') && (input[2] == '\0')) {
                message[0] = 'O';
                message[1] = 'K';
                QQ();
            } else if (input[1] == '\0') {
                break;
            }

        case 'L':
        case 'l':
            if ((input[0] == 'L' || input[0] == 'l') && (input[1] == 'D' || input[1] == 'd')) {
                message[0] = 'O';
                message[1] = 'K';
                LD(file);
                break;
            } else if (input[1] == '\0') {
                break;
            }

        case 'S':
        case 's':
            if ((input[0] == 'S' || input[0] == 's') && (input[1] == 'W' || input[1] == 'w')) {
           /* if (input[1] == 'W' || input[1] == 'w') {*/
                message[0] = 'O';
                message[1] = 'K';
                SW();
                break;
            } else if (input[1] == '\0') {
                break;
            }

            if ((input[0] == 'S' || input[0] == 's') && (input[1] == 'D' || input[1] == 'd')) {
                message[0] = 'O';
                message[1] = 'K';
                SD("cards.txt",cardsPointer);
                break;
            } else if (input[1] == '\0') {
                break;
            }

            if ((input[0] == 'S' || input[0] == 's') && (input[1] == 'R' || input[1] == 'r')) {
                message[0] = 'O';
                message[1] = 'K';
                SR();
                break;
            } else if (input[1] == '\0') {
                break;
            }

        case 'P':
        case 'p':
            if ((input[0] == 'P' || input[0] == 'p') && (input[1] == 'P' || input[1] == 'p')) {
                message[0] = 'O';
                message[1] = 'K';
                printfun();
                break;
            } else if (input[1] == '\0') {
                break;

                default:
                    printf("Invalid Command, Try Again: ");
                message[0] = 'E';
                message[1] = 'R';
                break;
            }


    }
}

int main() {
    defaultBoard();
    while (hasPlayerWon == false) {
        userInput();
    }
    SR();
    SD("cards.txt",cardsPointer);
}

