#include <stdio.h>

void *malloc(size_t size);
char cardDeck[52];
int deckSize = 52;

typedef struct node{
    char value;
    char suits;
    struct node* next;
    struct node* prev;
} node;
struct node* head = NULL;
struct node* prevNode = NULL;


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
    newNode -> value = value;
    newNode -> suits = suits;
    newNode -> next = NULL;
    newNode -> prev = prevNode;
    return newNode;
}


void arrayDeck(char file[]){

    FILE *filePointer;
    filePointer = fopen (file,"r");

    if(!filePointer){
        printf("Wrong file\n");
    }

    for (int i = 0; i < deckSize*2 ; ++i) {

        fscanf(filePointer,"%c\n",&cardDeck[i]);
        printf("%c\n", cardDeck[i]);

    }
    printf(cardDeck);

}

void LD(char file[]){

    arrayDeck(file);

    for (int i = 0; i < deckSize*2 ; ++i) {

        if(head == NULL){
            addFirst(cardDeck[i],cardDeck[i+1]);
        }

        if(!head == NULL){
            addNext(cardDeck[i],cardDeck[i+1]);
        }
        i++;
    }

    printf("\n%s\n", addFirst(cardDeck[0],cardDeck[1]));
    printf("%c%c",cardDeck[0],cardDeck[1]);

}
void main() {

    LD("CardDeck.txt");
    // hej

}
