#ifndef CARDDECK_HPP
#include <vector>
#include "Card.hpp"
class CardDeck {
	private:
		std::vector<Card> cards;
	public:
		CardDeck();
		CardDeck(const int numberOfDecks);
		void shuffle();
		Card getCard();
};
#endif
