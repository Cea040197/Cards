#define _DEFAULT_SOURCE // needed to use srandom() and random()
#include <cs50.h>       // functions: get_string(), get_int(); also string datatype
#include <ctype.h>      // functions: toupper(), tolower(), isalpha(), isdigit(), isalnum()
#include <math.h>       // functions: floor(), ceil(), round(), pow(), sqrt()
#include <stdio.h>      // functions: printf()
#include <stdlib.h>     // functions: srandom() and random()
#include <string.h>     // functions: strcmp(), strcpy(), strlen()
#include <time.h>       // functions: time()  [to seed srandom()]


// define Constants
const int SIZE = 52; // size of the deck


// create datatype (card)
typedef struct
{
    char faceValue;  // 2,3,4,5,6,7,8,9,T,J,Q,K,A
    char suit;       // S,H,D,C
    int blkJkPoints; // used for blackjack value
} card;


// prototypes
int shuffleDeck(card d[], int s);
int initializeDeck(card d[], int s);
void printDeck(card d[], int s);
void printCard(card c);
string printSuit(char s);
string printBlank(void);
void dealCards(card d[], int s);
string playBlackJack(void);
int getHandValue(card d[]);
void hitCards(void);


// global variables
card deck[SIZE];
card dealer[5];
card player[5];
int handSize = 2;      // player starts with 2 cards
int dealerHandSize = 2;
int deckPlacement = 4; // after dealing 2+2, next card is deck[4]


// main function
int main(void)
{
    // runs the blackjack game and prints outcome
    string outcome = playBlackJack();
    printf("%s\n", outcome);
}


// shuffles deck by swapping each card with a random position
int shuffleDeck(card d[], int s)
{
    int randNum;
    card temp;
    srand(time(NULL));


    for (int i = 0; i < s; i++)
    {
        randNum = ((random() / (double) RAND_MAX) * s - 1) + 1;
        temp = d[i];
        d[i] = d[randNum];
        d[randNum] = temp;
    }
    printf("\n");
    return 0;
}


// initializes deck with standard cards
int initializeDeck(card d[], int s)
{
    char fv[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int bjP[] = {1,2,3,4,5,6,7,8,9,10,10,10,10};
    char st[] = {'S','H','C','D'};
    int ci = 0;


    for (int si = 0; si < 4; si++)
    {
        for (int fi = 0; fi < 13; fi++)
        {
            ci = (si * 13) + fi;
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
}


// prints a single card
void printCard(card c)
{
    if (c.faceValue != 'X')
    {
        printf("%c%s ", c.faceValue, printSuit(c.suit));
    }
}


// returns suit as unicode
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


// returns a blank (face-down) card
string printBlank(void)
{
    return "\U00002593 ";
}


// deals two cards each to dealer and player
void dealCards(card d[], int s)
{
    int foo = 0;
    int bar = 1;


    for (int i = 0; i < 2; i++)
    {
        dealer[i] = d[foo];
        player[i] = d[bar];
        foo += 2;
        bar += 2;
    }


    printf("\nPlayers cards: ");
    printCard(player[0]);
    printCard(player[1]);
    printf("\nDealers cards: ");
    // first card hidden
    printf("%s", printBlank());
    printCard(dealer[1]);
    printf("\n");
}


// calculates hand value for either player or dealer
int getHandValue(card d[])
{
    int total = 0;


    if (d == player)
    {
        for (int i = 0; i < handSize; i++)
        {
            total += d[i].blkJkPoints;
        }
    }
    else if (d == dealer)
    {
        for (int i = 0; i < dealerHandSize; i++)
        {
            total += d[i].blkJkPoints;
        }
    }
    return total;
}


// adds a card to the player's hand and checks if it's an ace
void hitCards(void)
{
    handSize++;
    deckPlacement++;


    player[handSize - 1] = deck[deckPlacement];


    printf("\nYou drew: ");
    printCard(player[handSize - 1]);
    printf("\n");


    if (player[handSize - 1].faceValue == 'A')
    {
        int aceChoice = get_int("You've drawn an Ace! Do you want it to count as 1 or 11? ");
        if (aceChoice == 1)
        {
            player[handSize - 1].blkJkPoints = 1;
        }
        else if (aceChoice == 11)
        {
            player[handSize - 1].blkJkPoints = 11;
        }
    }


    printf("Your hand now: ");
    for (int i = 0; i < handSize; i++)
    {
        printCard(player[i]);
    }
    printf("\n");


    int newTotal = getHandValue(player);
    printf("Your new hand value is: %i\n", newTotal);
}


// runs the blackjack game
string playBlackJack(void)
{
    initializeDeck(deck, SIZE);
    shuffleDeck(deck, SIZE);
    dealCards(deck, 2);


    int playerTotal = getHandValue(player);
    printf("Your current hand value is: %i\n", playerTotal);


    string choice = get_string("Would you like to hit? (y/n) ");
    while (choice[0] == 'y' || choice[0] == 'Y')
    {
        hitCards();
        playerTotal = getHandValue(player);
        if (playerTotal > 21)
        {
            return "You busted! You lose.";
        }
        choice = get_string("Would you like to hit again? (y/n) ");
    }


    while (getHandValue(dealer) < 17)
    {
        dealerHandSize++;
        deckPlacement++;
        dealer[dealerHandSize - 1] = deck[deckPlacement];


        if (dealer[dealerHandSize - 1].faceValue == 'A')
        {
            dealer[dealerHandSize - 1].blkJkPoints = 11;
            if (getHandValue(dealer) > 21)
            {
                dealer[dealerHandSize - 1].blkJkPoints = 1;
            }
        }


        printf("\nDealer draws: ");
        printCard(dealer[dealerHandSize - 1]);
        printf("\nDealer's hand is now: ");
        for (int i = 0; i < dealerHandSize; i++)
        {
            printCard(dealer[i]);
        }
        printf("\n");
    }


    int dealerTotal = getHandValue(dealer);
    if (dealerTotal > 21)
    {
        return "Dealer busted! You win.";
    }


    playerTotal = getHandValue(player);
    if (playerTotal > dealerTotal)
    {
        return "You win!";
    }
    else if (playerTotal < dealerTotal)
    {
        return "You lose!";
    }
    else
    {
        return "It's a tie!";
    }
}


// prints the entire deck
void printDeck(card d[], int s)
{
    for (int i = 0; i < s; i++)
    {
        printCard(d[i]);
        if (i > 0 && ((i + 1) % 13) == 0)
        {
            printf("\n");
        }
    }
    return;
}
