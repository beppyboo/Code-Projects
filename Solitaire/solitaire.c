/*******************************************************************************
 * File        solitaire.c
 * Author      Ian Elsbree (ianelsbree@gmail.com)
 * Date        2021-10-20
 * Description:
 *   A text-based game of Klondike Solitaire
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
  SUIT_CLUB,
  SUIT_HEART,
  SUIT_SPADE,
  SUIT_DIAMOND
};

enum
{
  RANK_A,
  RANK_2,
  RANK_3,
  RANK_4,
  RANK_5,
  RANK_6,
  RANK_7,
  RANK_8,
  RANK_9,
  RANK_10,
  RANK_J,
  RANK_Q,
  RANK_K,
};

typedef struct Card
{
  int suit;
  int rank;
} Card;

// Card Checks
int isBlack(Card c);
int isRed(Card c);
int isOtherColor(Card first, Card second);
int isNextRank(Card higher, Card lower);
int canBePlacedTableau(Card parent, Card child);
int isSameSuit(Card first, Card second);
int canBePlacedFoundation(Card parent, Card child);

// Printing
char *suitf();
char *rankf();
void printCard(Card c);

// Deck Manipulation
Card initializeCard(int s, int r);
void initializeDeck(Card *deck);
void shuffleDeck(Card *deck);

// -----------------------------------------------------------------------------
int main(void)
{
  Card deck[52];
  initializeDeck(deck);
  shuffleDeck(deck);

  for (int i = 0; i < 52; i++)
  {
    printCard(deck[i]);
    printf(" ");
    if (i % 4 == 3)
    {
      printf("\n");
    }
  }

  return 0;
}
// -----------------------------------------------------------------------------

/*******************************************************************************
 * @brief  Determines if the card is black.
 *
 * @param  c
 * @return int
 *******************************************************************************/
int isBlack(Card c)
{
  return c.suit == SUIT_CLUB || c.suit == SUIT_SPADE;
}

/*******************************************************************************
 * @brief  Determines if the card is red.
 *
 * @param  c
 * @return int
 *******************************************************************************/
int isRed(Card c)
{
  return c.suit == SUIT_HEART || c.suit == SUIT_DIAMOND;
}

/*******************************************************************************
 * @brief  Determines if two cards are different colors than each other.
 *
 * @param  first
 * @param  second
 * @return int
 *******************************************************************************/
int isOtherColor(Card first, Card second)
{
  return isBlack(first) != isBlack(second);
}

/*******************************************************************************
 * @brief  Determines if the higher card's rank is one above the lower card's.
 *
 * @param  higher
 * @param  lower
 * @return int
 *******************************************************************************/
int isNextRank(Card higher, Card lower)
{
  return higher.rank == lower.rank + 1;
}

/*******************************************************************************
 * @brief  Determines if the child card can be placed on the parent card on the
 *          tableau.
 *
 * @param  parent
 * @param  child
 * @return int
 *******************************************************************************/
int canBePlacedTableau(Card parent, Card child)
{
  return isOtherColor(parent, child) && isNextRank(parent, child);
}

/*******************************************************************************
 * @brief  Determines if two cards have the same suit.
 *
 * @param  first
 * @param  second
 * @return int
 *******************************************************************************/
int isSameSuit(Card first, Card second)
{
  return first.suit == second.suit;
}

/*******************************************************************************
 * @brief  Determines if the child card can be placed on the parent card on the
 *          foundation.
 *
 * @param  parent
 * @param  child
 * @return int
 *******************************************************************************/
int canBePlacedFoundation(Card parent, Card child)
{
  return isSameSuit(parent, child) && isNextRank(child, parent);
}

/*******************************************************************************
 * @brief  Returns a symbol representing the suit of a card.
 *
 * @param  c
 * @return char
 *******************************************************************************/
char *suitf(Card c)
{
  switch (c.suit)
  {
  case SUIT_CLUB:
    return "\u2663";
  case SUIT_HEART:
    return "\u2665";
  case SUIT_SPADE:
    return "\u2660";
  case SUIT_DIAMOND:
    return "\u2666";
  }
}

/*******************************************************************************
 * @brief  Returns a symbol representing the rank of a card.
 *
 * @param  c
 * @return char
 *******************************************************************************/
char *rankf(Card c)
{
  switch (c.rank)
  {
  case RANK_A:
    return "A";
  case RANK_2:
    return "2";
  case RANK_3:
    return "3";
  case RANK_4:
    return "4";
  case RANK_5:
    return "5";
  case RANK_6:
    return "6";
  case RANK_7:
    return "7";
  case RANK_8:
    return "8";
  case RANK_9:
    return "9";
  case RANK_10:
    return "10";
  case RANK_J:
    return "J";
  case RANK_Q:
    return "Q";
  case RANK_K:
    return "K";
  }
}

/*******************************************************************************
 * @brief  Prints the symbols that represent a card.
 *
 * @param  c
 *******************************************************************************/
void printCard(Card c)
{
  printf("%2s%s", rankf(c), suitf(c));
}

/*******************************************************************************
 * @brief  Initializes a card struct with a suit and rank.
 *
 * @param  s
 * @param  r
 * @return Card
 *******************************************************************************/
Card initializeCard(int s, int r)
{
  Card c =
      {
          s,
          r};
  return c;
}

/*******************************************************************************
 * @brief  Initializes a deck of 52 cards.
 *
 * @param  deck
 *******************************************************************************/
void initializeDeck(Card *deck)
{
  for (int i = 0; i < 52; i++)
  {
    deck[i] = initializeCard(i / 13, i % 13);
  }
}

void shuffleDeck(Card *deck)
{
  for (int i = 51; i > 0; i--)
  {
    srand(time(NULL));
    int j = rand() % (i + 1);
    Card temp = deck[i];
    deck[i] = deck[j];
    deck[j] = temp;
  }
}