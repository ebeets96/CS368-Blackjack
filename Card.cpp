#include <string>
#include "Card.hpp"

Card::Card(int suit, int rank): suit(suit), rank(rank) {

}

int Card::getSuit() {
	return suit;
}

int Card::getRank() {
	return rank;
}

std::string Card::getSuitString() {
	std::string suits[4];
	suits[SPADE] = "Spade";
	suits[CLUB] = "Club";
	suits[DIAMOND] = "Diamond";
	suits[HEART] = "Heart";
	return suits[suit];
}

std::string Card::getRankString() {
	std::string ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	return ranks[rank - 1];
}
