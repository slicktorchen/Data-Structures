// File:         tennis.h
// Purpose: Declaration of the player class and associated functions to manipulate data

#ifndef __tennis_h_
#define __tennis_h_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Player {

public: 
	Player();
	Player(string name, string last_name, int match_wins, int match_loss, int game_wins, int game_loss, float percent_games_win, float percent_matches_win, int tb_wins, int tb_loss, float tb_percent);

	int getMatchWins() const { return match_wins_; }
	int getMatchLosses() const { return match_loss_; }
	int getGameWins() const { return game_wins_; }
	int getGameLosses() const { return game_loss_; }
	int getTbWins() const { return tb_wins_; }
	int getTbLosses() const { return tb_loss_; }

	float getPercentGames() const { return percent_games_win_; }
	float getPercentMatches() const { return percent_matches_win_; }
	float getTbPercent() const { return tb_percent_; }
	const string& getName() const { return name_; }
	const string& getLastName() const { return last_name_; }

	void addMatchWins();
	void addMatchLosses();
	void addGameWins(int game_wins);
	void addGameLosses(int game_lost);
	void addTbWins(int tb_wins);
	void addTbLosses(int tb_loss);
	void setName(string name, string last_name);
	void compute_percent();
	ostream& output_name(ostream& out_str) const;
	ostream& output_wins(ostream& out_str) const;

private:
	vector<int> games_won_;
	vector<int> games_lost_;
	int game_wins_;
	int game_loss_;
	int match_wins_;
	int match_loss_;
	int tb_wins_;
	int tb_loss_;
	string name_;
	string last_name_;
	float percent_games_win_;
	float percent_matches_win_;
	float tb_percent_;
};

void parse_set(std::string &set, int &games_won, int &games_lost);
bool sort_games(const Player& player1, const Player& player2);
bool sort_matches(const Player& player1, const Player& player2);
bool sort_tb(const Player& player1, const Player& player2);

#endif