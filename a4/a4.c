/*
  a4.c created by Wen Xie
  Jan 31, 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a4.h"

#include <assert.h>

#define kPrintDebug 1

// Implement the Hand and other functions in here
//----------------------------------------
// Card functions
//----------------------------------------
// Creates a card, initializing the suit and name to that specified.
// Returns a pointer to the new card, which has been allocated on the heap.
// It is the responsibility of the caller to call destroyCard()
// when it is done with the Card.
Card* CreateCard(Suit suit, Name name) {
  Card* card = (Card*) malloc(sizeof(Card));
  assert(card);
  card->suit = suit;
  card->name = name;
  // card->value
  return card;
}

// Destroys the card, freeing any memory allocated for the card.
void DestroyCard(Card* card) {
  assert(card);
  free(card);
}

//----------------------------------------
// Hand functions
//----------------------------------------

// Creates a Hand struct and initializes any necessary fields.
// Returns a pointer to the new Hand, which has been allocated on the heap.
Hand* CreateHand() {
  Hand* hand = (Hand*)malloc(sizeof(Hand));
  assert(hand);
  hand->first_card = NULL;
  hand->num_cards_in_hand = 0;
}

// Adds a card to the hand.
void AddCardToHand(Card *card, Hand *hand) {
  assert(card);
  assert(hand);
  if (hand->num_cards_in_hand == kNumCardsInHand) {
    return;
  }
  CardNode* new_card_node= (CardNode*) malloc(sizeof(CardNode));
  assert(new_card_node);
  if (hand->first_card) {
    new_card_node->next_card = hand->first_card;
    hand->first_card->prev_card = new_card_node;
    new_card_node->prev_card = NULL;
  } else {
    new_card_node->prev_card = NULL;
    new_card_node->next_card = NULL;
  }
  hand->first_card = new_card_node;
  new_card_node->this_card = card;
  hand->num_cards_in_hand++;
}

// Removes a card from the hand.
// Does not free the card; it is the responsibility
// of the caller to free the card at the appropriate
// time.
// Returns a pointer to the card that is no longer in the hand.
Card* RemoveCardFromHand(Card *card, Hand *hand) {
  assert(card);
  assert(hand);
// locate the card
  CardNode* curr = hand->first_card;
  Card* returnCard;
  while (curr) {
    if (curr->this_card == card) {
      if (curr == hand->first_card) {  // if it is the first node
        if (curr->next_card) {  // if it is not the only node left
          curr->next_card->prev_card = NULL;
          hand->first_card = curr->next_card;
        } else {
          hand->first_card = NULL;
        }
      } else if (curr->next_card == NULL) {  // if it is the last node
        curr->prev_card->next_card = NULL;
      } else {
        curr->prev_card->next_card = curr->next_card;
        curr->next_card->prev_card = curr->prev_card;
      }
    hand->num_cards_in_hand -= 1;
    returnCard = curr->this_card;
    free(curr);
    return returnCard;
    }
    curr = curr->next_card;
  }
  return NULL;
}

// Determines if there are any cards in the hand.
// Return 1 if the hand is empty; 0 otherwise.
int IsHandEmpty(Hand* hand) {
  assert(hand);
  if (hand->first_card) {
    return 0;
  }
  return 1;
}

// Destroys the hand, freeing any memory allocated for it.
void DestroyHand(Hand* hand) {
  assert(hand);
  CardNode* curr = hand->first_card;
  while (curr) {
    if (curr->next_card) {
      CardNode* node_to_free = curr->next_card;
      curr->next_card = curr->next_card->next_card;
      curr->next_card->prev_card = curr;
      free(node_to_free);
      curr = curr->next_card;
    }
    // free the first node
    free(hand->first_card);
  }
  free(hand);
}

//----------------------------------------
// Game functions
//----------------------------------------

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the ledCard, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
// Returns 1 if the move is legal; 0 otherwise.
int IsLegalMove(Hand *hand, Card *lead_card, Card *played_card) {
  if (hasSuit(hand, lead_card)) {
    if (played_card->suit == lead_card->suit) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 1;
  }
}

// A helper function to determine whether a hand has the lead suit
// return 1 if it has, otherwise return 0
int hasSuit(Hand *hand, Card *lead_card) {
  Suit lead_suit = lead_card->suit;
  CardNode* currNode = hand->first_card;
  while (currNode) {
    if (currNode->this_card->suit == lead_suit) {
      return 1;
    }
    currNode = currNode->next_card;
  }
  return 0;
}

// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card name wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int WhoWon(Card *lead_card, Card *followed_card, Suit trump) {
  if (lead_card->suit == followed_card->suit) {
    return (lead_card->name > followed_card->name);
  } else {
    if (followed_card->suit == trump) {
      return 0;
    }
    return 1;
  }
}

// Take all the cards out of a given hand, and put them
// back into the deck.
void ReturnHandToDeck(Hand *hand, Deck *deck) {
  while (IsHandEmpty(hand) == 0) {
    Card* removed_card = RemoveCardFromHand(hand->first_card->this_card, hand);
    deck = PushCardToDeck(removed_card, deck);
  }
}
