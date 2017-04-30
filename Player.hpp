#ifndef Player_HPP
#define Player_HPP

#include <string>

class Player {
	private:
		std::string name;
		int bankroll;

	public:
		Player();
		Player(std::string name, int bankroll);
		std::string getName();
		int getBankroll();
		void setBankroll(int value);
		
};

#endif //Player_HPP
