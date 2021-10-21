/*******************************************************************************
 * File        solitaire.c
 * Author      Ian Elsbree (ianelsbree@gmail.com)
 * Date        2021-10-20
 * Description:
 *   A text-based game of Klondike Solitaire
 *
 ******************************************************************************/

#include <stdio.h>

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

struct card
{
  int suit;
  int rank;
};

int isBlack(struct card c);
int isRed(struct card c);
int isOtherColor(struct card first, struct card second);
int isNextRank(struct card higher, struct card lower);
int canBePlacedOnTableau(struct card parent, struct card child);
int isSameSuit(struct card first, struct card second);
int canBePlacedOnFoundation(struct card parent, struct card child);
char suitf();
char rankf();

struct card initializeCard(int s, int r);
void initializeDeck(struct card *deck);

void printCard(struct card c)
{
  printf("%c%c", suitf(c), rankf(c));
}

int main(void)
{
  struct card cAC = {SUIT_DIAMOND, RANK_A};

  printf("Card is black: %i", RANK_5);

  return 0;
}

/*******************************************************************************
 * @brief  Determines if the card is black.
 *
 * @param  c
 * @return int
 *******************************************************************************/
int isBlack(struct card c)
{
  return c.suit == SUIT_CLUB || c.suit == SUIT_SPADE;
}

/*******************************************************************************
 * @brief  Determines if the card is red.
 *
 * @param  c
 * @return int
 *******************************************************************************/
int isRed(struct card c)
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
int isOtherColor(struct card first, struct card second)
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
int isNextRank(struct card higher, struct card lower)
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
int canBePlacedOnTableau(struct card parent, struct card child)
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
int isSameSuit(struct card first, struct card second)
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
int canBePlacedOnFoundation(struct card parent, struct card child)
{
  return isSameSuit(parent, child) && isNextRank(child, parent);
}

struct card initializeCard(int s, int r)
{
  struct card c =
      {
          s,
          r};
  return c;
}

void initializeDeck(struct card *deck)
{
  for (int i = 0; i < 52; i++)
  {
    deck[i] = initializeCard(i / 13, i % 13);
  }
}

char suitf(struct card c)
{
  int s = c.suit;
  if (s == 0)
  {
    return '♣';
  }
  else if (s == 1)
  {
    return '♥';
  }
  else if (s == 2)
  {
    return '♠';
  }
  else
  {
    return '♦';
  }
}

char rankf(struct card c)
{
  int r = c.rank;
  if (r == 0)
  {
    return 'A';
  }
  else if (r == 11)
  {
    return 'J';
  }
  else if (r == 12)
  {
    return 'Q';
  }
  else if (r == 13)
  {
    return 'K';
  }
  else
  {
    return r + 49;
  }
}