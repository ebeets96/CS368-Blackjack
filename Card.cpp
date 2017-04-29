#include <string>
#include "Card.hpp"

Card::Card(int suit, int rank): suit(suit), rank(rank) {

}

const int Card::getSuit() const {
	return suit;
}

const int Card::getRank() const {
	return rank;
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
