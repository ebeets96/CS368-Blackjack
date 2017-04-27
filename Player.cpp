#include "Player.hpp"
#include <string>

Player::Player(std::string name, int bankroll): name(name), bankroll(bankroll) {

}

std::string Player::getName(){
	return name;
}

int Player::getBankroll(){
	return bankroll;	
}

void Player::setBankroll(int value){
	bankroll = value;
}

