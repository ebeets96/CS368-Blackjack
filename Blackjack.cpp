#include "Blackjack.hpp"
#include "CardDeck.hpp"
#include "Card.hpp"
#include "IO.hpp"
#include "Player.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

//Sleep includes
#include <chrono>
#include <thread>


int main() {
	
	// USED FOR CLEARING THE CONSOLE
	std::cout << "\033[2J\033[1;1H";	
	
	std::string input;
	int menuChoice;
	
	// PRINTS THE WELCOME MESSAGE / MENU
	startGame();

	// GETS MAIN MENU OPTION FROM USER
	input = getUserInput();
	menuChoice = verifyNumber(input);

	switch (menuChoice) {
		// NEW GAME			
		case 1: 
			startNewGame();
			break;

		// LOAD GAME
		case 2:
			break;

		// STATS
		case 3:
			break;

		// HELP
		case 4:
			break;

		// QUIT
		case 5:
			break;
	}

/*
	std::vector<std::vector<std::string>> dealer;

	for (int i = 0; i < 6; i++){
		Card tempDraw = deck.getCard();
		dealer.push_back(createCardGraphic(tempDraw, false));
	}

	printCards(dealer);



	std::cout << std::endl; 
	
	input = getUserInput();
	verifyNumber(input);

	printMargin();
	printFrameWithText("What is your name?");
	printFrame(1);
	getUserInput();
	std::cout << "\033[2J\033[1;1H";

	
	mainGameLoop();
*/
}

void clearScreen() {

	// USED FOR CLEARING THE CONSOLE
	std::cout << "\033[2J\033[1;1H";
	printWelcome();

}

int convertRank(int rank) {

	if (rank <= 0) {
		return 11;
	}
	
	else if (rank < 9) {
		return ++rank;	
	}
	
	else {
		return 10;	
	}
}

void mainGameLoop(Player player) {
	
	// INITIALIZES CARDS Using 6 Decks
	CardDeck deck(6);
	deck.shuffle();

	bool handIsOver = false;

	std::vector<Card> dealer;
	std::vector<Card> playerCards;
	std::vector<std::vector<std::string>> dealersCardGraphics;
	std::vector<std::vector<std::string>> playerCardGraphics;

	std::string input;	
	int bet;	
	
	while (player.getBankroll() > 0) {
		clearScreen();
		printFrameWithText("Place your bets. ($" + 
			std::to_string(player.getBankroll()) +  + " remaining)", 1);
	
		std::string betInput = "          => $";
		do {
			input = getUserInput(betInput);
			bet = verifyNumber(input);
			betInput = "          You do not have sufficient funds.\n          => $";
		} while (bet > player.getBankroll());
		
		player.setBankroll(player.getBankroll() - bet);
	
		// DRAWS CARDS FROM THE DECK TO DEAL
		for (int i = 0; i < 2; i++) {
			dealer.push_back(deck.getCard());
			playerCards.push_back(deck.getCard());
		}
	
		int playerHandValue = 0;
		int dealerCount = 0;
		bool playerHasAce;
		bool dealerHasAce;

		while (!handIsOver) {
			clearScreen();
			printFrameWithText("You bet: $" + std::to_string(bet) + " ($" + 
				std::to_string(player.getBankroll()) +  + " remaining)", 1);
	
			// PRINTS DEALERS CARDS
			printFrameWithTextLeft("Dealers hand:", 0);
		
			for (int i = 0; i < dealer.size(); i++) {
				Card temp = dealer[i];
				dealersCardGraphics.push_back(createCardGraphic(temp, !(i%2 == 0)));
			}
			
			printCards(dealersCardGraphics);

			// PRINTS PLAYERS CARDS
			printFrameWithTextLeft("Your hand:", 1);

			for (int i = 0; i < playerCards.size(); i++) {
				Card temp = playerCards[i];
				playerCardGraphics.push_back(createCardGraphic(temp, true));
			}
			
			playerHandValue = Card::calculateHandValue(playerCards);
			
			std::cout << playerHandValue;

			printCards(playerCardGraphics);
		
			if (playerHandValue < 21){
				printFrameWithText("Would you like to Hit (H), Double (D), or Stay (S)?", 1);
				std::string choice = getUserInput();
				
				//Make input lowercase
				std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		
				// CLEARS VECTORS TO PREP FOR HIt		
				if(choice == "h") {
						playerCards.push_back(deck.getCard());
				} else if(choice == "d") {
					//Check if player has sufficient funds
					if(player.getBankroll() >= bet) {
						player.setBankroll(player.getBankroll() - bet);
						bet *= 2;
					} else {
						printFrameWithText("You do not have sufficient funds.", 1);
					}
				
				} else if(choice == "s") {
					//Done dealing
					dealersTurn();
				}
				
			} else if (playerHandValue == 21) {
				//Player Wins
				handIsOver = true;
				printFrameWithText("You got 21! To play another hand press <ENTER>.", 1);
				getUserInput();
			} else {
				printBusted();
				handIsOver = true;
				printFrameWithText("To play another hand press <ENTER>.", 1);
				getUserInput();
			}
			
			playerCardGraphics.clear();
			dealersCardGraphics.clear();
		}
		
		playerCards.clear();
		dealer.clear();
		handIsOver = false;
	}
	
	printFrameWithText("You ran out of money, thanks for playing!", 1);
	
}

void dealersTurn() {
	
}

void startNewGame() {
	
	// Player variables
	std::string input;
	std::string name;
	int bankroll = 0;

	clearScreen();
	
	printFrameWithText("Please enter your name.", 1);
	name = getUserInput();

	clearScreen();

	printFrameWithText("Please deposit money into your bankroll.", 1);
	input = getUserInput("          => $");
	bankroll = verifyNumber(input);

	Player player(name, bankroll);
	
	mainGameLoop(player);
}

