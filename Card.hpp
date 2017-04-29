#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
	private:
		int suit;
		int rank;
	
	public:	
		// Rank Constants
		static int const ACE = 1;
		static int const TWO = 2;
		static int const THREE = 3;
		static int const FOUR = 4;
		static int const FIVE = 5;
		static int const SIX = 6;
		static int const SEVEN = 7;
		static int const EIGHT = 8;
		static int const NINE = 9;
		static int const TEN = 10;
		static int const JACK = 11;
		static int const QUEEN = 12;
		static int const KING = 12;

		// Suit Constants
		static int const HEART = 0;
		static int const DIAMOND = 1;
		static int const CLUB = 2;
		static int const SPADE = 3;
		
		// Public Functions
		Card(int suit, int rank);
		const int getSuit() const;
		const int getRank() const;
		const std::string getSuitString() const;
		const std::string getRankString() const;
};
#endif //CARD_HPP
