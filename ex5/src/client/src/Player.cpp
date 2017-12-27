
#include "Player.h"

bool Player::operator ==(const Player& comparePlayer) const {
	return (this->getPlayerIdChar() == comparePlayer.getPlayerIdChar());
}

char Player::getPlayerIdChar() const {
	return this->playerIdChar;
}

bool Player::operator <(const Player &comparePlayer) const {
	return (this->getPlayerIdChar() < comparePlayer.getPlayerIdChar());
}

void Player::setPlayerId(char value) {
	this->playerIdChar = value;
}


