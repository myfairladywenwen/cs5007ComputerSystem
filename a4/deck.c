/*
  deck.c created by Wen Xie
  Jan 31, 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include "a4.h"
#include <assert.h>
#include <time.h>
#define PRINT_DEBUG 1

//----------------------------------------
// Deck functions
//----------------------------------------
// Implement these functions in deck.c.
// Creates the deck to be used for NEUchre.
// Assume that the value of cards are:
// Nine=9; Ten=10; Jack=11; and so on, up to Ace=14.

// Creates the deck, initializing any fields necessary.
// Returns a pointer to the deck, which has been allocated on the heap.
Deck* CreateDeck() {
  Deck* deck = (Deck*) malloc(sizeof(Deck));
  for (int i = 0; i < kNumCardsInDeck; i++) {
    deck->cards[i] = NULL;
  }
  deck->top_card = -1;
  return deck;
}


// Adds a card to the top of the deck.
// Returns a pointer to the deck.
Deck* PushCardToDeck(Card* card, Deck* deck) {
  // check whether the deck is full
  if (deck->top_card == kNumCardsInDeck - 1) {
    return deck;
  }
  (deck->top_card)++;
  deck->cards[deck->top_card] = card;
  return deck;
}

// Shows the top card, but does not remove it from the stack.
Card* PeekAtTopCard(Deck* deck) {
  if (IsDeckEmpty(deck) == 1) {
    return NULL;
  }
  return deck->cards[deck->top_card];
}

// Removes the top card from the deck and returns it.
// The card should NOT be freed at this point; it is the
// responsibility of the caller to free the card at the
// appropriate time.
// Returns a pointer to the top card in the deck.
// If the deck is empty, return NULL.
Card* PopCardFromDeck(Deck* deck) {
  if (IsDeckEmpty(deck) == 1) {
    return NULL;
  }
  Card* card_to_pop = deck->cards[deck->top_card];
  deck->cards[deck->top_card] == NULL;
  deck->top_card -= 1;
  return card_to_pop;
}

// Determines if the deck is empty.
// Returns 1 if the Deck is empty, 0 otherwise.
int IsDeckEmpty(Deck* deck) {
  assert(deck);
  if (deck->top_card == -1) {
    return 1;
  }
  return 0;
}

// Destroys the deck, freeing any memory allocated
// for this deck (the cards and the deck).
// DestroyDeck should call DestroyCard on all of the
// cards in the deck.
void DestroyDeck(Deck* deck) {
  assert(deck);
  for (int i = 0; i < deck->top_card+1; i++) {
    if (deck->cards[i]) {
      DestroyCard(deck->cards[i]);
    }
  }
  free(deck);
}

//----------------------------------------
// Game functions
//----------------------------------------

// Create a Deck for this game, and add any
// needed cards to the deck.
// Return a pointer to the deck to be used for the game
Deck* PopulateDeck() {
  Deck* deck = CreateDeck();
  for (int suit = HEARTS; suit <= DIAMONDS; suit++) {
    for (int name = NINE; name <= ACE; name++) {
      deck->cards[++deck->top_card] = CreateCard(suit, name);
    }
  }
  return deck;
}

// Shuffle the deck.
// Put them in a random order.
void Shuffle(Deck *deck) {
  srand(time(0));
  for (int idx = kNumCardsInDeck - 1; idx > 0; idx--) {
    int k = rand()%(idx + 1);
    Card* card = (deck->cards)[idx];
    (deck->cards)[idx] = (deck->cards)[k];
    (deck->cards)[k] = card;
  }
}

// Given a deck (assume that it is already shuffled),
// take the top card from the deck and alternately give
// it to player 1 and player 2, until they both have
// kNumCardsInHand.
void Deal(Deck *aDeck, Hand *p1hand, Hand *p2hand) {
  for (int i = 0; i < kNumCardsInHand; i++) {
    Card* new_card1 = PopCardFromDeck(aDeck);
    AddCardToHand(new_card1, p1hand);
    Card* new_card2 = PopCardFromDeck(aDeck);
    AddCardToHand(new_card2, p2hand);
  }
}
