// Author: Matt McGuiness

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Comments Section
1.)
If the player has a score of 18=A,7 and the dealer has a 9, you should hit. You have a better chance of winning if you hit.
If you hit, you have a 45% chance of winning whereas if you stand, you only have a 44% chance of winning. (11% chance you push).

2.)
If the player has a score of 18=A,7 then he should do the following depending on the dealer's card:
2  = Stand
3  = Stand
4  = Stand
5  = Stand
6  = Stand
7  = Stand
8  = Stand
9  = Hit
10 = Hit
A  = Stand

3.)
All of the possibilties for a players hand and a dealers hand are as follow:

    Matrix for Hard Totals
    2  3  4  5  6  7  8  9  10 A
________________________________
 4  h  h  h  h  h  h  h  h  h  h
 5  h  h  h  h  h  h  h  h  h  h
 6  h  h  h  h  h  h  h  h  h  h
 7  h  h  h  h  h  h  h  h  h  h
 8  h  h  h  h  h  h  h  h  h  h
 9  h  h  h  h  h  h  h  h  h  h
10  h  h  h  h  h  h  h  h  h  h
11  h  h  h  h  h  h  h  h  h  h
12  h  h  h  h  h  h  h  h  h  h
13  h  h  h  h  h  h  h  h  h  h
14  h  h  h  h  h  h  h  h  h  h
15  h  s  s  s  s  h  h  h  h  h
16  s  s  s  s  s  h  h  h  h  h
17  s  s  s  s  s  s  s  s  s  s
18  s  s  s  s  s  s  s  s  s  s
19  s  s  s  s  s  s  s  s  s  s
20  s  s  s  s  s  s  s  s  s  s

    Matrix for Soft Totals
    2  3  4  5  6  7  8  9  10 A
________________________________
13  h  h  h  h  h  h  h  h  h  h
14  h  h  h  h  h  h  h  h  h  h
15  h  h  h  h  h  h  h  h  h  h
16  h  h  h  h  h  h  h  h  h  h
17  h  h  h  h  h  h  h  h  h  h
18  s  s  s  s  s  s  s  h  h  s
19  s  s  s  s  s  s  s  s  s  s
20  s  s  s  s  s  s  s  s  s  s
21  s  s  s  s  s  s  s  s  s  s


4.)
If we were playing with two decks instead of one, then you would hit if your hand was A,7 when the dealer is showing an Ace instead of standing.
Other than that it would not really make much of a difference from what I saw in my simulations.

*/

struct pairs{
    int number;
    char value[3];
} values[14] = {{0,{'0'}},{1,{'A'}},{2,{'2'}},{3,{'3'}},{4,{'4'}},{5,{'5'}},{6,{'6'}},{7,{'7'}},{8,{'8'}},{9,{'9'}},{10,{"10"}},{11,{'J'}},{12,{'Q'}},{13,{'K'}}};

int deck[52];
int cardNumber;

int batchMode(int simulations, int card1, int card2, int dealersCard);
void initializeDeck();
void dealCards(int *player, int *dealer);
void dealBatchCards(int *dealerHand);
void hit(int *hand, int *card);
void batchHit(int *batchHand, int *batchCard);
int getCardValue(int card);
int checkSoftHand(int *hand, int *card, int *playerScore);
void initializeBatchModeDeck(int card1, int card2, int dealersCard);
int faceToInt(int card);
bool checkBlackJack(int *hand);
int checkDealerSoftHand(int *dealerHand, int *dealerCard, int *dealerScore);

int main(int argc, char *argv[]) {
    
    if (argc >2) {
        srand(time(NULL));
        int card1, card2, dealersCard;

        // Convert input to ints
        card1 = atoi(argv[2]) == 0 ? faceToInt(argv[2][0]) : atoi(argv[2]);
        card2 = atoi(argv[3]) == 0 ? faceToInt(argv[3][0]) : atoi(argv[3]);
        dealersCard = atoi(argv[4]) == 0 ? faceToInt(argv[4][0]) : atoi(argv[4]);

        int hit = batchMode(atoi(argv[1]), card1, card2, dealersCard);
        if (hit == 1) {
            printf("You should hit in this scenario.\n");
        } else if (hit == 0) {
            printf("You should stand in this scenario.\n");            
        }
        return 0;
    } else if (argc == 2) {
        srand(time(NULL));   
        printf("    Matrix for Hard Totals\n");     
        printf("    2  3  4  5  6  7  8  9  10 A\n");
        printf("________________________________\n");
        int k = 2;
        for (int j = 2; j < 11; j++) {
            
            char decisionArray[10];
            for (int i = 1; i < 11; i++) {
                int hit = batchMode(atoi(argv[1]), j, k ,i);
                if (hit == 1) decisionArray[i-1] = 'h';
                if (hit == 0) decisionArray[i-1] = 's';
            }
            printf("%2d  ", j+k);
            for(int i = 1; i < 10; i++) printf("%c  ", decisionArray[i]);
            printf("%c  ", decisionArray[0]);
            printf("\n");
            
        }
        k = 10;
        for (int j = 3; j < 11; j++) {
            
            char decisionArray[10];
            for (int i = 1; i < 11; i++) {
                int hit = batchMode(atoi(argv[1]), j, k ,i);
                if (hit == 1) decisionArray[i-1] = 'h';
                if (hit == 0) decisionArray[i-1] = 's';
            }
            printf("%2d  ", j+k);
            for(int i = 1; i < 10; i++) printf("%c  ", decisionArray[i]);
            printf("%c  ", decisionArray[0]);
            printf("\n");
            
        }
        
        printf("\n\n    Matrix for Soft Totals\n");     
        printf("    2  3  4  5  6  7  8  9  10 A\n");
        printf("________________________________\n");
        k = 1;
        for (int j = 2; j < 11; j++) {
            
            char decisionArray[10];
            for (int i = 1; i < 11; i++) {
                int hit = batchMode(atoi(argv[1]), j, k ,i);
                if (hit == 1) decisionArray[i-1] = 'h';
                if (hit == 0) decisionArray[i-1] = 's';
            }
            printf("%2d  ", j+11);
            for(int i = 1; i < 10; i++) printf("%c  ", decisionArray[i]);
            printf("%c  ", decisionArray[0]);
            printf("\n");
            
        }
        
        return 0;
    } else {
        srand(time(NULL));
        // Interactive Mode Beginning
        printf("Welcome to Blackjack!\n\n");

        // Runs two games
        for (int i = 0; i < 2; i++) {            
            initializeDeck();
            bool bust = false, playerBlackJack = false, dealerBlackJack = false;
            int playerScore = 0, dealerScore = 0, playerCard = 2, dealerCard = 2;
            int playerHand[10], dealerHand[10];
            printf("The game is starting.\n");
            dealCards(playerHand, dealerHand);
            playerBlackJack = checkBlackJack(playerHand);
            dealerBlackJack = checkBlackJack(dealerHand);
            playerScore = getCardValue(playerHand[0]) + getCardValue(playerHand[1]);
            dealerScore = getCardValue(dealerHand[0]) + getCardValue(dealerHand[1]);
            printf("Your Hand: %s %s\n", values[playerHand[0]].value, values[playerHand[1]].value);
            printf("The Dealers Hand: %s ?\n\n", values[dealerHand[0]].value);
            
            char response[6];  
            printf("Your score is: %d\n", playerScore);
            if (playerBlackJack == true && dealerBlackJack == false) {
                printf("\nCONGRATULATIONS! YOU HAVE BLACKJACK!\n");
            } else if (playerBlackJack == false && dealerBlackJack == true) {
                printf("\nTHE DEALER HAS BLACK JACK! YOU LOSE!\n");                
            } else if (playerBlackJack == true && dealerBlackJack == true) {
                printf("\nYOU AND THE DEALER BOTH HAVE BLACKJACK! IT'S A PUSH!\n");
            } else {          
                do {
                    printf("What do you want to do?('hit' or 'stand') ");
                    scanf("%s", response);

                    if (strcmp("hit",response) == 0) {
                        hit(playerHand, &playerCard);
                        playerScore += getCardValue(playerHand[playerCard-1]);
                        if (playerScore > 21 && checkSoftHand(playerHand, &playerCard, &playerScore) != 1) {
                            strncpy(response, "stand", 6);
                            printf("BUST!\n");
                            bust = true;
                        }
                        printf("Your hand is now: ");
                        for (int j = 0; j < playerCard; j++) printf(" %s", values[playerHand[j]].value);
                        printf("\nYour current score is: %d\n", playerScore);
                        
                    }

                } while (strcmp("hit", response) == 0 || strcmp("stand", response) != 0);
        
                if (bust == false) {
                    printf("\n\nThe Dealers' hand is: ");
                    for (int j = 0; j < dealerCard; j++) printf(" %s", values[dealerHand[j]].value);
                    printf("\n");

                    do {
                        if (dealerScore < 17) {
                            hit(dealerHand, &dealerCard);
                            dealerScore += getCardValue(dealerHand[dealerCard-1]);
                            if (dealerScore > 21) {
                                checkSoftHand(dealerHand, &dealerCard, &dealerScore);
                            }
                            printf("The dealers' hand is now: ");
                            for (int j = 0; j < dealerCard; j++) printf(" %s", values[dealerHand[j]].value);
                            printf("\nThe dealers' score is: %d\n", dealerScore);
                        }              
                        if (dealerScore == 17) {
                            int softHand = checkDealerSoftHand(dealerHand, &dealerCard, &dealerScore);
                            if (softHand == 1) {
                                hit(dealerHand, &dealerCard);
                                if (dealerScore > 21) {
                                    checkSoftHand(dealerHand, &dealerCard, &dealerScore);
                                    printf("The dealers' hand is now: ");
                                    for (int j = 0; j < dealerCard; j++) printf(" %s", values[dealerHand[j]].value);
                                    printf("\nThe dealers' score is: %d\n", dealerScore);
                                }
                            }
                        }
                    } while (dealerScore < 17 && dealerScore <= playerScore);
                }

                if ((dealerScore > playerScore && dealerScore < 22) || playerScore > 21) {
                    printf("The dealer beat you!\n\n");
                } else if ((dealerScore < playerScore && playerScore < 22) || dealerScore > 21) {
                    printf("Congratulations! You won!\n\n");
                } else {
                    printf("The game was a push!\n\n");
                }
            }
        }
        
        return 0;
    }
} 

int batchMode(int simulations, int card1, int card2, int dealersCard) {
    float standWins = 0;
    float hitWins = 0;
    float hitPushes = 0;
    float standPushes = 0;
    // printf("%d\n", simulations);
    for (int i = 0; i < simulations; i++) {
        
        initializeBatchModeDeck(card1, card2, dealersCard);
        bool bust = false;
        int dealerHand[5];
        int playerHand[5];
        playerHand[0] = card1, playerHand[1] = card2;        
        int dealerCard = 2;
        int playerCard = 2;
        dealerHand[0] = dealersCard;
        int playerScore = getCardValue(card1) + getCardValue(card2);
        dealBatchCards(dealerHand);
        int dealerScore = getCardValue(dealerHand[0]) + getCardValue(dealerHand[1]);

        // printf("%d %d\n", playerScore, dealerScore);
        int action = rand() % 2;
        // printf("%d\n", action);

        if (action == 1) {
            batchHit(playerHand, &playerCard);
            playerScore += getCardValue(playerHand[playerCard-1]);
            if (playerScore > 21 && checkSoftHand(playerHand, &playerCard, &playerScore) != 1) bust = true;
            // printf("%d\n", playerScore);
            cardNumber++;
        }

        if (bust == false) {
            do {
                if (dealerScore < 17) {
                    batchHit(dealerHand, &dealerCard);
                    // printf("%d + %d\n", dealerScore, getCardValue(dealerHand[dealerCard-1]));
                    dealerScore += getCardValue(dealerHand[dealerCard-1]);
                    // printf("%d\n", dealerScore);
                    if (dealerScore > 21) {
                        int softHand = checkDealerSoftHand(dealerHand, &dealerCard, &dealerScore);
                        // printf("%d\n", softHand);
                        if (softHand == 1) {
                            //printf("%d\n", dealerScore);
                            dealerScore -= 10;
                        }
                    }
                }              
                if (dealerScore == 17) {
                    int softHand = checkDealerSoftHand(dealerHand, &dealerCard, &dealerScore);
                    if (softHand == 1) {
                        batchHit(dealerHand, &dealerCard);
                        if (dealerScore > 21) {
                            checkSoftHand(dealerHand, &dealerCard, &dealerScore);
                        }
                    }
                }
            } while (dealerScore < 17 && dealerScore <= playerScore);
        }

        // printf("%d %d\n", dealerScore, playerScore);
        if (action == 1) {
            if ((dealerScore > playerScore && dealerScore < 22) || playerScore > 21) {
                // printf("Dealer won when you hit\n");
                standWins++;
            } else if ((dealerScore < playerScore && playerScore < 22) || dealerScore > 21) {
                // printf("Dealer lost when you hit\n");                
                hitWins++;
            } else {
                hitPushes++;
            }
        } else if (action == 0) {
            if ((dealerScore > playerScore && dealerScore < 22) || playerScore > 21) {
                // printf("Dealer won when you stood\n");                
                hitWins++;
            } else if ((dealerScore < playerScore && playerScore < 22) || dealerScore > 21) {
                // printf("Dealer lost when you stood\n");                
                standWins++;
            } else {
                standPushes++;
            }
        }
    }
    
    float total = float(simulations);
    float standWinPercentage = standWins / total;
    float hitWinPercentage = hitWins / total;
    
    printf("%f %f\n", standWinPercentage, hitWinPercentage);
    if (standWinPercentage > hitWinPercentage) {
        return 0;
    } else if (standWinPercentage < hitWinPercentage) {
        return 1;
    } else {
        return 0;
    }
}

void initializeDeck() {
    cardNumber = 0;
    int value = 1;
    for (int i = 0; i < 52; i++) {
        if (value == 14) value = 1;
        deck[i] = value;
        value++;     
    }
    for (int i = 0; i < 52; i++) {
        int copy = deck[i];
        int rand1 = rand() % 52;
        deck[i] = deck[rand1];
        deck[rand1] = copy;
    } 
    // for (int i = 0; i < 52; i++) printf("%d\n", deck[i]);

}

void dealCards(int *player, int *dealer) {
    for (int i = 0; i < 2; i++) {
        player[i] = deck[cardNumber];
        cardNumber++;
        dealer[i] = deck[cardNumber];
        cardNumber++;
    }
}

void dealBatchCards(int *dealerHand) {
    dealerHand[1] = deck[cardNumber];
    cardNumber++;
}

void hit(int *hand, int *card) {
    hand[*card] = deck[cardNumber];
    printf("\nNew Card: %s\n\n", values[hand[*card]].value);
    cardNumber++;
    *card = *card + 1;
}

void batchHit(int *batchHand, int *batchCard) {
    batchHand[*batchCard] = deck[cardNumber];
    cardNumber++;
    *batchCard = *batchCard + 1;
}

int getCardValue(int card) {
    if (card == 1) {
        return 11;
    } else if (card > 10) {
        return 10;
    } else {
        return card;
    }
}

int checkSoftHand(int *hand, int *card, int *playerScore) {
    for (int i = 0; i < *card; i++) {
        if (hand[i] == 1) {
            *playerScore = *playerScore - 10;
            return 1;
        }
    }
    return 0;
}

int checkDealerSoftHand(int *dealerHand, int *dealerCard, int *dealerScore) {
    for (int i = 0; i < *dealerCard; i++) {
        if (dealerHand[i] == 1) {
            dealerHand[i] = 0;
            return 1;
        }
    }
    return 0;
}


bool checkBlackJack(int *hand){
    if (getCardValue(hand[0]) + getCardValue(hand[1]) == 21) {
        return true;
    }
    return false;
}

void initializeBatchModeDeck(int card1, int card2, int dealersCard) {
    cardNumber = 0;
    int value = 1;
    int index = 0;
    for (int i = 1; i <= 52; i++) {
        if (value == 14) value = 1;
        if (i <= 13 && value == card1) {
            value++;
        } else if (13 < i && i <= 26 && value == card2) {
            value++;
        } else if (26 < i && i <= 39 && value == dealersCard) {
            value++;
        } else {
            deck[index] = value;
            index++;
            value++; 
        }
                
    }

    for (int i = 0; i < 49; i++) {
        int copy = deck[i];
        int rand1 = rand() % 52;
        deck[i] = deck[rand1];
        deck[rand1] = copy;
    } 
}

int faceToInt(int card) {
    if (card == 65) {
        return 1;
    } else if(card == 75) {
        return 13;
    } else if(card == 81) {
        return 12;
    } else if(card == 74) {
        return 11;
    } else {
        return card;
    }
}
