#include <string>
#include <vector>
#include <iostream>
#include "Card.hpp"

Card::Card(int suit, int rank): suit(suit), rank(rank) {

}

const int Card::getSuit() const {
	return suit;
}

const int Card::getRank() const {
	return rank;
}

// This code does not take into account that aces can be 11.
// Use the calculateHandValue function for this
const int Card::getValue() const {
	if(rank < Card::JACK)
		return rank;
	else
		return 10;
}

// Algorithm courtesy of http://stackoverflow.com/questions/2402483/calculating-hand-values-in-blackjack
const int Card::calculateHandValue(std::vector<Card> hand) {
	int numberOfAces = 0;
	int handValue = 0;
	// We will first add all of the non-aces
	std::vector<Card>::iterator it = hand.begin();
	while(it != hand.end()) {
		if(it->getRank() != Card::ACE) {
			handValue += it->getValue();
			it = hand.erase(it);
		} else {
			++handValue;
			++numberOfAces;
			++it;
		}
	}
	
	// If the hand is <= 11, and there were aces in the
	// hand.  Convert an ace to have a value of 11 by adding 10.
	while(handValue <= 11 && numberOfAces > 0) {
		handValue += 10;
		--numberOfAces;
	}
	
	return handValue;
}

const std::string Card::getSuitString() const {
	std::string suits[4];
	suits[SPADE] = "Spade";
	suits[CLUB] = "Club";
	suits[DIAMOND] = "Diamond";
	suits[HEART] = "Heart";
	return suits[suit];
}

const std::string Card::getRankString() const {
	std::string ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	return ranks[rank - 1];
}
