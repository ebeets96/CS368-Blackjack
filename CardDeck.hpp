#ifndef CARDDECK_HPP
#include <vector>
#include "Card.hpp"
class CardDeck {
	private:
		std::vector<Card> cards;
	public:
		CardDeck();
		void shuffle();
		Card getCard();
};
#endif
