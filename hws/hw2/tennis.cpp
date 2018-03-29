// File:         tennis.cpp
// Purpose:      implementation of the class Player

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "tennis.h"
using namespace std;

// For some reason this default operator does not work when called in main
Player::Player() {
	name_ = "UNKNOWN";
	last_name_ = "UNKNOWN";
	match_wins_ = 0;
	match_loss_ = 0;
	game_wins_ = 0;
	game_loss_ = 0;
	percent_games_win_ = 0.0;
	percent_matches_win_ = 0.0;
	tb_wins_ = 0;
	tb_loss_ = 0;
	tb_percent_ = 0.0;
}

Player::Player(string name, string last_name, int match_wins, int match_loss, int game_wins, int game_loss, float percent_games_win, float percent_matches_win, int tb_wins, int tb_loss, float tb_percent) {
	name_ = "UNKNOWN";
	last_name_ = "UNKNOWN";
	match_wins_ = 0;
	match_loss_ = 0;
	game_wins_ = 0;
	game_loss_ = 0;
	percent_games_win_ = 0.0;
	percent_matches_win_ = 0.0;
	tb_wins_ = 0;
	tb_loss_ = 0;
	tb_percent_ = 0.0;
	/*name_ = name;
	match_wins_ = match_wins;
	match_loss_ = match_loss;
	game_wins_ = game_wins;
	game_loss_ = game_loss;
	percent_games_win_ = percent_games_win;
	percent_matches_win_ = percent_matches_win;*/
}

void Player::addGameWins(int game_wins) {
	game_wins_ += game_wins;
}

void Player::addGameLosses(int game_lost) {
	game_loss_ += game_lost;
}

void Player::addMatchWins()  {
	match_wins_ += 1;
}

void Player::addMatchLosses() {
	match_loss_ += 1;
}

void Player::addTbWins(int tb_wins) {
	tb_wins_ += tb_wins;
}

void Player::addTbLosses(int tb_loss) {
	tb_loss_ += tb_loss;
}

void Player::setName(string name,string last_name) {
	name_ = name;
	last_name_ = last_name;
}

void Player::compute_percent() {
	percent_games_win_ = (float)game_wins_/(float)(game_wins_ + game_loss_);
	percent_matches_win_ = (float)match_wins_/(float)(match_wins_ + match_loss_);
	if (tb_wins_ == 0 && tb_loss_ == 0) {
		tb_percent_ = -1;
	} else {
		tb_percent_ = (float)tb_wins_/(float)(tb_wins_ + tb_loss_);
	}
}

void parse_set(std::string &set, int &games_won, int &games_lost) {
	int i = set.find('-');
	games_won = atoi(set.substr(0,i).c_str());
	games_lost = atoi(set.substr(i+1,set.size()-i-1).c_str());
}

bool sort_games(const Player &player1, const Player &player2) {
	if (player1.getPercentGames() > player2.getPercentGames()) {
		return true;
	} else if (player1.getPercentGames() < player2.getPercentGames()) {
		return false;
	} else {
		if (player1.getLastName() > player2.getLastName()) {
			return false;
		} else {
			return true;
		}
	}
}

bool sort_matches(const Player &player1, const Player &player2) {
	if (player1.getPercentMatches() > player2.getPercentMatches()) {
		return true;
	} else if (player1.getPercentMatches() < player2.getPercentMatches()) {
		return false;
	} else { 
		if (player1.getLastName() > player2.getLastName()) {
			return false;
		} else {
			return true;
		}
	}
}

bool sort_tb(const Player& player1, const Player& player2) {
	if (player1.getTbPercent() > player2.getTbPercent()) {
		return true;
	} else if (player1.getTbPercent() < player2.getTbPercent()) {
		return false;
	} else { 
		if (player1.getLastName() > player2.getLastName()) {
			return false;
		} else {
			return true;
		}
	}
}