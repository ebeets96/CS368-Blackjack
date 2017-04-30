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

CardDeck deck(6);
Player player;
int bet;
std::vector<Card> dealerCards;
std::vector<Card> playerCards;
std::vector<std::vector<std::string>> dealersCardGraphics;
std::vector<std::vector<std::string>> playerCardGraphics;

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
			return 0;
			break;
	}
}

void clearScreen() {

	// USED FOR CLEARING THE CONSOLE
	std::cout << "\033[2J\033[1;1H";
	printWelcome();

}

void mainGameLoop() {
	
	// INITIALIZES CARDS Using 6 Decks
	deck.shuffle();

	bool handIsOver = false;

	std::string input;
	
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
			dealerCards.push_back(deck.getCard());
			playerCards.push_back(deck.getCard());
		}
	
		int playerHandValue = 0;
		int dealerCount = 0;
		bool playerHasAce;
		bool dealerHasAce;

		while (!handIsOver) {
			clearScreen();
			playerCardGraphics.clear();
			dealersCardGraphics.clear();
			
			printFrameWithText("You bet: $" + std::to_string(bet) + " ($" + 
				std::to_string(player.getBankroll()) +  + " remaining)", 1);
	
			// PRINTS DEALERS CARDS
			printFrameWithTextLeft("Dealers hand:", 0);
		
			for (int i = 0; i < dealerCards.size(); i++) {
				Card temp = dealerCards[i];
				dealersCardGraphics.push_back(createCardGraphic(temp, i != 0));
			}
			
			printCards(dealersCardGraphics);

			// PRINTS PLAYERS CARDS
			printFrameWithTextLeft("Your hand:", 1);

			for (int i = 0; i < playerCards.size(); i++) {
				Card temp = playerCards[i];
				playerCardGraphics.push_back(createCardGraphic(temp, true));
			}
			
			playerHandValue = Card::calculateHandValue(playerCards);

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
		}
		
		playerCards.clear();
		dealerCards.clear();
		handIsOver = false;
	}
	
	printFrameWithText("You ran out of money, thanks for playing!", 1);
	
}

void dealersTurn() {
	bool firstIteration = true;
	int dealersValue;
	int playersValue = Card::calculateHandValue(playerCards);
	do {
		clearScreen();
		playerCardGraphics.clear();
		dealersCardGraphics.clear();
		
		if(firstIteration) {
			firstIteration = false;
		} else {
			dealerCards.push_back(deck.getCard());
		}
	
		// PRINTS DEALERS CARDS
		printFrameWithTextLeft("Dealers hand:", 0);
	
		for (Card c : dealerCards) {
			dealersCardGraphics.push_back(createCardGraphic(c, true));
		}
			
		printCards(dealersCardGraphics);

		// PRINTS PLAYERS CARDS
		printFrameWithTextLeft("Your hand:", 1);

		for (Card c : playerCards) {
			playerCardGraphics.push_back(createCardGraphic(c, true));
		}
	
		printCards(playerCardGraphics);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		dealersValue = Card::calculateHandValue(dealerCards);
	} while(dealersValue < 17);
	
	if(dealersValue > 21) {
		player.setBankroll(player.getBankroll() + 2 * bet);
		printFrameWithText("The dealer busted, and you won $"
			+ std::to_string(bet) + ".  To play another hand press <ENTER>.", 1);
	} else if(playersValue > dealersValue) {
		player.setBankroll(player.getBankroll() + 2 * bet);
		printFrameWithText("You beat the dealer and won $"
			+ std::to_string(bet) + ".  To play another hand press <ENTER>.", 1);
	} else if (playersValue == dealersValue) {
		player.setBankroll(player.getBankroll() + bet);
		printFrameWithText("You tied the dealer, so no money was paid out.  To play another hand press <ENTER>.", 1);
	} else {
		printFrameWithText("You lost to the dealer and lost $"
			+ std::to_string(bet) + ".  To play another hand press <ENTER>.", 1);
	}
	
	getUserInput();
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

	player = Player(name, bankroll);
	
	mainGameLoop();
}

