#include "CardDeck.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>


CardDeck::CardDeck() {
	for(int rank = Card::ACE; rank <= Card::KING; ++rank) {
		for(int suit = 0; suit <= 3; ++suit) {
			Card temp(suit, rank);
			cards.push_back(temp);
		}
	}
}

void CardDeck::shuffle() {
	std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle(cards.begin(), cards.end(), g);
}

Card CardDeck::getCard() {
	Card tempCard = cards.back();
	cards.pop_back();
	return tempCard;
}
