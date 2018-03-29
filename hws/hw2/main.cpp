//File:      main.cpp
//Purpose:   Parse data and store in class objects for easy output
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include "tennis.h"
using namespace std;


int main(int argc, char* argv[]) {

	// Opens files and checks if they are good
	ifstream in_str(argv[1]);
	ofstream out_str(argv[2]);
	if (!in_str.good()) {
		cerr << "Can't open " << argv[1] << " to read." << endl;
		return 1;
	} if (!out_str.good()) {
		cerr << "Can't open " << argv[2] << " to write." << endl;
		return 1;
	}
	
	// Initialized values
	string first_name1, last_name1, useless, first_name2, last_name2, name1, name2, set;
	int games_won = 0 , games_lost = 0;
	int matches_won = 0, matches_lost = 0;
	float percent_games_win = 0.0, percent_matches_win = 0.0, tb_percent = 0;

	// This vector will collect all of the players
	vector<Player> players;  
	
////////////////////////// Parsing Data /////////////////////////////

	// First while loop parses the first 5 sections of the line and puts them together as names

	while(in_str >> first_name1 >> last_name1 >> useless >> first_name2 >> last_name2) {
		int set_wins = 0,set_lost = 0;
		unsigned int i = 0, j = 0;
		int tb_wins = 0, tb_loss = 0;
		int total_games_won = 0, total_games_lost = 0, total_tb_won = 0, total_tb_lost = 0;
		bool found1 = false, found2 = false;
		name1 = first_name1 + " " + last_name1;
		name2 = first_name2 + " " + last_name2;

		/* Second while loop parses the sets on the same line and parses the set strings for data
		   including games won, games lost, tiebreaks won, tiebreaks lost, sets won, and sets lost */
		while (in_str >> set && isdigit(set[0]) ) {

			parse_set(set,games_won,games_lost);
			total_games_won += games_won;
			total_games_lost += games_lost;
			if (games_won == 6 && games_lost == 7) {
				total_tb_lost += 1;
			} else if (games_won == 7 && games_lost == 7) {
				total_tb_won += 1;
			}
			if (games_won > games_lost) {
				set_wins += 1;
			} else {
				set_lost += 1;
			}
			if (set_wins == 3 || set_lost == 3) {     // MISSING THIS CAUSED A LOT OF ISSUES FOR ME
				break;
			}
		}

		/* Checks if the first player already exists in the players vector. 
		   If player already exists the loop exits. */
		for (i = 0 ; i < players.size() ; ++i) {
			if (players[i].getName() == name1) {
				found1 = true;
				break;
			}
		}
		if (found1 == false) {
			// Creates a new player object if the first player is not found and inputs data
			Player player1(name1,last_name1,matches_won,matches_lost,games_won,games_lost,percent_games_win,percent_matches_win,tb_wins,tb_loss,tb_percent);
			player1.setName(name1,last_name1);
			player1.addGameWins(total_games_won);
			player1.addGameLosses(total_games_lost);
			player1.addTbWins(total_tb_won);
			player1.addTbLosses(total_tb_lost);
			if (set_wins == 3) {
				player1.addMatchWins();
			} else if (set_lost == 3) {
				player1.addMatchLosses();
			}
			players.push_back(player1);
		} else {
			// If player already exists, the player's data will simply be edited
			players[i].addGameWins(total_games_won);
			players[i].addGameLosses(total_games_lost);
			players[i].addTbWins(total_tb_won);
			players[i].addTbLosses(total_tb_lost);
			if (set_wins == 3) {
				players[i].addMatchWins();
			} else if (set_lost == 3) {
				players[i].addMatchLosses();
			}
		}

		/* Checks if the second player already exists in the players vector. 
		   If player already exists the loop exits. */
		for (j = 0 ; j < players.size() ; ++j) {
			if (players[j].getName() == name2) {
				found2 = true;
				break;
			}
		}
		if (found2 == false) {
			// Creates a new player object if the second player is not found and inputs data
			Player player2(name2,last_name2,matches_won,matches_lost,games_won,games_lost,percent_games_win,percent_matches_win,tb_wins,tb_loss,tb_percent); 
			player2.setName(name2,last_name2);
			player2.addGameWins(total_games_lost);
			player2.addGameLosses(total_games_won);
			player2.addTbWins(total_tb_lost);
			player2.addTbLosses(total_tb_won);
			if (set_wins == 3) {
				player2.addMatchLosses();
			} else if (set_lost == 3) {
				player2.addMatchWins();
			}
			players.push_back(player2);
		} else {
			// If player already exists, the player's data will simply be edited
			players[j].addGameWins(total_games_lost);
			players[j].addGameLosses(total_games_won);
			players[j].addTbWins(total_tb_lost);
			players[j].addTbLosses(total_tb_won);
			if (set_wins == 3) {
				players[j].addMatchLosses();
			} else if (set_lost == 3) {
				players[j].addMatchWins();
			}
		}
		
	}

///////////////////// Output ////////////////////////

	unsigned int i;
	unsigned int max_length = 0;
	// Calculates amount of spacing needed for the names & also computes percentages
	for (i = 0; i < players.size(); ++i) {
		players[i].compute_percent();
		unsigned int tmp_length;
		tmp_length = players[i].getName().size();
		max_length = max(max_length, tmp_length);
	}
	max_length += 4;

	// Prints out match statistics
	out_str << "MATCH STATISTICS" << endl;
	string header = "Player" + string(max_length-6, ' ') + "W" + string(4,' ') + "L" + string(3,' ') + "percentage";
	out_str << header << endl;


	sort(players.begin(),players.end(),sort_matches);  // Sorts based on percentage of matches won
	for (i = 0; i < players.size(); ++i) {
		out_str << players[i].getName() << string(max_length-players[i].getName().size(),' ') << players[i].getMatchWins() << string(4,' ') << players[i].getMatchLosses() << string(8,' ');
		out_str << fixed << setprecision(3) << players[i].getPercentMatches() << endl;
	}

	// Prints out game statistics
	sort(players.begin(),players.end(),sort_games);    // Sorts based on percentage of games won
	out_str << endl << "GAME STATISTICS" << endl << header << endl;
	for (i = 0; i < players.size(); ++i) {
		out_str << players[i].getName();
		// Prints number of wins
		if (players[i].getGameWins() >= 100) {       // Adjusts spacing for length of number
			out_str << string(max_length-players[i].getName().size()-2,' ');
		} else if (players[i].getGameWins() >= 10 && players[i].getGameWins() < 100) {
			out_str << string(max_length-players[i].getName().size()-1,' ');
		} else if (players[i].getGameWins() < 10) {
			out_str << string(max_length-players[i].getName().size(),' ');
		}
		out_str << players[i].getGameWins();

		// Prints number of losses
		if (players[i].getGameLosses() >= 100) {     // Adjusts spacing for length of numbers
			out_str << "  ";
		} else if (players[i].getGameLosses() >= 10 && players[i].getGameWins() < 100) {
			out_str << "   ";
		} else if (players[i].getGameLosses() < 10) {
			out_str << "    ";
		}
		out_str << players[i].getGameLosses() << string(8,' ');

		// Prints percentage
		out_str << fixed << setprecision(3) << players[i].getPercentGames() << endl;
	}
	
	// Calculates tiebreak statistics
	sort(players.begin(),players.end(),sort_tb);    // Sorts based on percentage of tiebreaks won
	out_str << endl << "TIEBREAK STATISTICS" << endl << header << endl;
	for (i = 0; i < players.size(); ++i) {     // Adjusts spacing for length of numbers
		out_str << players[i].getName();

		// Prints number of tiebreak wins
		if (players[i].getTbWins() >= 10) {
			out_str << string(max_length-players[i].getName().size()-1,' ');
		} else if (players[i].getTbWins() < 10) {
			out_str << string(max_length-players[i].getName().size(),' ');
		}
		out_str << players[i].getTbWins();

		// Prints number of tiebreak losses
		if (players[i].getTbLosses() >= 10) {
			out_str << "   ";
		} else if (players[i].getTbLosses() < 10) {
			out_str << "    ";
		}
		out_str << players[i].getTbLosses() << string(8,' ');

		// Prints percentage of tiebreak wins, prints N/A if player has not played in any tiebreaks
		if (players[i].getTbPercent() == -1) {
			out_str << "  N/A" << endl;
		} else {
			out_str << fixed << setprecision(3) << players[i].getTbPercent() << endl;
		}
	}

	return 0;
}