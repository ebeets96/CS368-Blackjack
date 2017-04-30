#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "IO.hpp"
#include "Card.hpp"

using namespace std;

void startGame(){
	
	printWelcome();	
	printFrame(1);
	printMenu();
	printFrame(1);

}

void printMenu(){
	printFrameWithText("Main Menu:", 0);
	printFrame(1);
	printFrameWithText("1. New Game", 0);
	printFrameWithText("2. Load Game", 0);
	printFrameWithText("3. Statistics", 0);
	printFrameWithText("4. Help", 0);
	printFrameWithText("5. Quit", 0);
}

void printWelcome() {	

	string welcomeMsg = "Think you can beat the house?";
	string welcomeMsg2 = "Welcome to the Blackjack table.";

	printDashes();
	printFrame(2);
	
	for (int i = 0; i < 8; i++) {
		printFrameWithText(blackjack[i], 0);
	}
	
	printFrameWithText(welcomeMsg2, 1);
	printDashes();
	
	printFrameWithText(welcomeMsg, 1);
	printDashes();	
}

void printBusted(){
	for (int i = 0; i < 4; i++) {
		printFrameWithText(busted[i], 0);
	}
}

void printDashes() {
	cout << "+";
	for (int i = 0; i < WINDOW_SIZE - 2; i++){
		cout << "-";
	}
	cout << "+" << endl;
}

void printSpaces(int numSpaces) {
	for (int i = 0; i < numSpaces; i++){
		cout << " ";
	}
}

void printFrame(int numLines) {
	for (int j = 0; j < numLines; j++){
		cout << "|";
		printSpaces(WINDOW_SIZE - 2);
		cout << "|" << endl;
	}
}

void printFrameWithText(string text, int spacing){
	
	int spaceBetweenText = (WINDOW_SIZE - text.length() - 1) / 2;
	
	printFrame(spacing);
	cout << "|";
	
	if (text.length() % 2 == 0){
		spaceBetweenText--;
		cout << " ";
	}	
	printSpaces(spaceBetweenText);
	cout << text;
	printSpaces(spaceBetweenText);
	cout << "|" << endl;
	printFrame(spacing);
}

void printFrameWithTextLeft(string text, int spacing) {

	int spaceAfterText = (WINDOW_SIZE - text.length() - 5);
	
	printFrame(spacing);

	cout << "|   " << text;
	printSpaces(spaceAfterText);
	cout << "|" << endl;
	
}

string getUserInput() {
	string input;

	cout << "          => ";
	getline(cin, input);	

	return input;
}

string getUserInput(std::string prompt) {
	string input;

	cout << prompt;
	getline(cin, input);	

	return input;
}

int verifyNumber(string line) {

    int number;     // the (valid) number to be returned
    bool done;      // loop condition variable

    // The following do-while loop gets input from the user, then checks if
    // the input stream is a number. If it is, it goes on to check if there
    // are any characters past the number. If both conditions are met, done
    // is set to true and the loop exits.
    do{
        done = true;
        istringstream stream(line);

        if (!(stream >> number)) {
            //ERROR: Input is not a number - display error message and update done
            // to continue the loop
            printFrameWithText("Invalid input - please try again", 0);
            done = false;
        }

        char endCharacter;
        if (stream >> endCharacter) {
            //ERROR: There is something past the number. Display error msg
            printFrameWithText("Invalid input - please try again", 0);
            done = false;
        }

        if (!done) {
			line = getUserInput();
        }

    } while (!done);

    // Valid int value
    return number;

}

std::vector<std::string> createCardGraphic(Card card, bool faceUp){
	
	std::vector<std::string> tempCard;	
	std::string cardVal;
	int value = card.getRank();
	int suit = card.getSuit();
	
	if (value > Card::ACE && value < Card::JACK){
		cardVal = std::to_string(value);
	}
	else {
		switch(value) {
			case Card::ACE:
				cardVal = "A";
				break;
			case Card::JACK:
				cardVal	= "J";
				break;
			case Card::QUEEN:
				cardVal = "Q";
				break;
			case Card::KING:
				cardVal = "K";
				break;
		}
	}

	if (value != Card::TEN && faceUp){
		if (suit == Card::HEART) {
			std::string line1 = "|" + cardVal + "     |";
			std::string line2 = "|     " + cardVal + "|";
		
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back(line1);
		    tempCard.push_back("| (\\/) |");
		    tempCard.push_back("|  \\/  |");
		    tempCard.push_back(line2);
		    tempCard.push_back("'------'");
		    
		}
	
		else if (suit == Card::DIAMOND){
			std::string line1 = "|" + cardVal + "     |";
			std::string line2 = "|     " + cardVal + "|";
		
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back(line1);
		    tempCard.push_back("|  /\\  |");
		    tempCard.push_back("|  \\/  |");
		    tempCard.push_back(line2);
		    tempCard.push_back("'------'");
		}

		else if (suit == Card::SPADE){
			std::string line1 = "|" + cardVal + "     |";
			std::string line2 = "|  /\\ " + cardVal + "|";
		
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back(line1);
		    tempCard.push_back("|  /\\  |");
		    tempCard.push_back("| (__) |");
		    tempCard.push_back(line2);
		    tempCard.push_back("'------'");
		}

		else if (suit == Card::CLUB){
			std::string line1 = "|" + cardVal + "     |";
			std::string line2 = "|  '' " + cardVal + "|";
		
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back(line1);
		    tempCard.push_back("|  ()  |");
		    tempCard.push_back("| (..) |");
		    tempCard.push_back(line2);
		    tempCard.push_back("'------'");
		}
	}
	
	else if (value == Card::TEN && faceUp) {
		if (suit == Card::HEART) {
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back("|10    |");
		    tempCard.push_back("| (\\/) |");
		    tempCard.push_back("|  \\/  |");
		    tempCard.push_back("|    10|");
		    tempCard.push_back("'------'");
		    
		}
	
		else if (suit == Card::DIAMOND){
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back("|10    |");
		    tempCard.push_back("|  /\\  |");
		    tempCard.push_back("|  \\/  |");
		    tempCard.push_back("|    10|");
		    tempCard.push_back("'------'");
		}

		else if (suit == Card::SPADE){
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back("|10    |");
		    tempCard.push_back("|  /\\  |");
		    tempCard.push_back("| (__) |");
		    tempCard.push_back("|  /\\10|");
		    tempCard.push_back("'------'");
		}

		else if (suit == Card::CLUB){
		  	tempCard.push_back(" ______ ");
		    tempCard.push_back("|10    |");
		    tempCard.push_back("|  ()  |");
		    tempCard.push_back("| (..) |");
		    tempCard.push_back("|  ^^10|");
		    tempCard.push_back("'------'");
		}
	}

	else {
		tempCard.push_back(" ______ ");
        tempCard.push_back("|$$$$$$|");
        tempCard.push_back("|$$$$$$|");
        tempCard.push_back("|$$$$$$|");
        tempCard.push_back("|$$$$$$|");
        tempCard.push_back("'------'");

	}

	return tempCard;
}

void printCards(std::vector<std::vector<std::string>> cards){
	 for(int i = 0; i < 6; i++) {
        for (int j = 0; j < cards.size(); j++){
			if (j == 0)
            	std::cout << "    ";
			std::cout << cards[j][i] << "    ";
            if (j == (cards.size() - 1))
                std::cout << std::endl;
        }
    }
}






















