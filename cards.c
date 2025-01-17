#define _DEFAULT_SOURCE // needed to use srandom() and random()
#include <cs50.h>       // functions: get_string(), get_int(); also string datatype
#include <ctype.h>      // functions: toupper(), tolower(), isalpha(), isdigit(), isalnum()
#include <math.h>       // functions: floor(), ceiling(), round(), power(), sqrt()
#include <stdio.h>      // functions: printf()
#include <stdlib.h>     // functions: srandom() and random()
#include <string.h>     // functions: strcomp(), strcopy(), strlen()
#include <time.h>       // functions: time()  [to seed srandom()]

// define Constants
const int SIZE = 52; // define size of deck - used in declaring and looping through deck (array of 52 cards)

// create datatype (card)
typedef struct
{
    char faceValue;  // use: 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A
    char suit;       // use: S, H, D, C
    int blkJkPoints; // used to store value for game Black Jack
} card;

// prototype functions here
int shuffleDeck(card d[], int s);    // not yet defined - your job!
int initializeDeck(card d[], int s); // loads regular deck of playing cards
void printDeck(card d[], int s);     // used for testing only - you won't use in your game
void printCard(card c);              // prints one card
string printSuit(char s);            // returns emoji for suit instead of  char
string printBlank(void);             // returns rectangle to represent face down card
void dealCards(card d[], int s);

card deck[SIZE];
card dealer[5];
card player[5];

int main(void)
{
    // call intialize
    initializeDeck(deck, SIZE);
    shuffleDeck(deck, SIZE);
   // intDeck(deck, SIZE); // call printDeck to test that initialize works as intended

    // example of printing a face-down card and then a face-up card
    dealCards(deck,2);


    //**TO DO**  shuffle - you write a function to shuffle
    //    then call printDeck again to test your sufffle

    // call function to execute playing the game - these will include
    // things like...
    //   1) dealing a hand to all players
    //   2) taking turns
    //   3) checking for winner/loser
}

// Functions Needed to create a card game
//  1 - initialize deck (load all 52 cards)
//  2 - shuffle deck
//  3 - deal
//  4 - one or more functions to "play" your game/taking turns/checking winner or loser etc.
//  another big challenge will be how will you have your program keep track of each players
//  hand of cards?  this starts with how you will "move cards from the deck to player hands"
//  during your dealing process - there's a few ways to solve this - but you will need to
//  really think it through.

int shuffleDeck(card d[], int s)
{
    int randNum;
    card temp;
    srand(time(NULL));
    // printf("printing random\n\n");

    for (int i = 0; i <= SIZE - 1; i++)
    {

        randNum = ((random() / (double) RAND_MAX) * SIZE - 1) + 1;
        temp = d[i];
        d[i] = d[randNum];

        d[randNum] = temp;
    }
    printf("\n");
    return 0;
}

int initializeDeck(card d[], int s)
{
    char fv[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int bjP[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    char st[] = {'S', 'H', 'C', 'D'};
    int ci = 0;
    for (int si = 0; si < 4; si++)
    {
        for (int fi = 0; fi < 13; fi++)
        {
            ci = ((si * 13) + fi);
            if (ci > s)
            {
                return -99;
            }
            d[ci].faceValue = fv[fi];
            d[ci].suit = st[si];
            d[ci].blkJkPoints = bjP[fi];
        }
    }
    return 0;
} // end funciton

void printDeck(card d[], int s) // prints out the face value & suit of a deck of s cards
{
    for (int i = 0; i < s; i++)
    {
        // printf("%s%s, ",d[i].faceValue, printSuit(d[i].suit));
        printCard(d[i]);
        if (i > 0 && ((i + 1) % 13) == 0)
        {
            printf("\n");
        }
    }
    return;
}

void printCard(card c)
{
    if (c.faceValue != 'X') // don't print blank cards
    {
        printf("%c%s ", c.faceValue, printSuit(c.suit));
    }

}

string printSuit(char s)
{
    if (s == 'S')
    {
        return "\U00002660";
    }
    else if (s == 'H')
    {
        return "\U00002665";
    }
    else if (s == 'D')
    {
        return "\U00002666";
    }
    else if (s == 'C')
    {
        return "\U00002663";
    }
    else
    {
        return "X";
    }
}

string printBlank(void)
{
    return "\U00002593 "; // returns unicode of solid rectangle (face down card)
}

void dealCards(card d[], int s)
{
    // TODO: deal card
    // printf("suit %c, facevalue: %c", d[0].suit, d[0].faceValue);

    int foo = 0;
    int bar = 1;

    for (int i = 0; i < 2; i++)
    {
        foo = foo + 2;
        bar = bar + 2;
        dealer[i] = d[foo];
        player[i] = d[bar];

    }


    printf("\n");
    printf("Players cards: ");
    printCard(player[0]);
    printCard(player[1]);
    printf("\n");
    printf("dealers cards: ");
    printf("%s", printBlank());
    printCard(dealer[1]);
    printf("\n");
}
