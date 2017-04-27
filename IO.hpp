#ifndef IO_HPP
#define IO_HPP
#include <vector>
#include <string>
#include "Card.hpp"

		static std::string const blackjack[8] = {
		    "  ____   _               _     _               _     ",
		    " |  _ \\ | |             | |   (_)             | |    ",
		    " | |_) || |  __ _   ___ | | __ _   __ _   ___ | | __ ",
		    " |  _ < | | / _` | / __|| |/ /| | / _` | / __|| |/ / ",
		    " | |_) || || (_| || (__ |   < | || (_| || (__ |   <  ",
		    " |____/ |_| \\__,_| \\___||_|\\_\\| | \\__,_| \\___||_|\\_\\ ",
		    "                             _/ |                    ",
		    "                            |__/                     "
		};

		static std::string busted[4] = {
		"  ___ _   _ ___ _____ ___ ___  _ ",
		" | _ ) | | / __|_   _| __|   \\| |",
		" | _ \\ |_| \\__ \\ | | | _|| |) |_|",
		" |___/\\___/|___/ |_| |___|___/(_)"
		};


		static int const WINDOW_SIZE = 83;

		void printWelcome();
		void printMenu();
		void printBusted();
		void printDashes();
		void printSpaces(int numSpaces);
		void printFrame(int numLines);
		void printFrameWithText(std::string text, int spacing);
		void printFrameWithTextLeft(std::string text, int spacing);
		void startGame();
		std::string getUserInput();
		std::string getUserInput(std::string prompt);
		std::vector<std::string> createCardGraphic(Card card, bool faceUp);
		int verifyNumber(std::string line);
		void printCards(std::vector<std::vector<std::string>> cards);		

#endif //CARD_HPP
