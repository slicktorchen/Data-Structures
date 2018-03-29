	//vector<string> names;
	//vector<int> data;

	//while(in_str >> first_name1 >> last_name1 >> useless >> first_name2 >> last_name2) {
	//	int set_wins = 0, set_lost = 0,match_win = 0, match_lost = 0;
	//	name1 = first_name1 + " " + last_name1;
	//	name2 = first_name2 + " " + last_name2;
	//	names.push_back(name1);
	//	names.push_back(name2);
	//	while (in_str >> set && isdigit(set[0]) ) {
	//		parse_set(set,games_won,games_lost);
	//		total_games_
	//		if (games_won > games_lost) {
	//			set_wins += 1;
	//		} else {
	//			set_lost += 1;
	//		}
	//		if (set_wins == 3) {
	//			match_win += 1;
	//			break;
	//		}
	//		if (set_lost == 3) {
	//			match_lost += 1;
	//			break;
	//		}
	//	}

	//	data.push_back();

	//	names.clear();

	//}



	while(in_str >> first_name1 >> last_name1 >> useless >> first_name2 >> last_name2) {
		int set_wins = 0,set_lost = 0;
		unsigned int i = 0, j = 0;
		bool found1 = false, found2 = false;
		Player newPlayer1(name1,matches_won,matches_lost,games_won,games_lost,percent_win);
		Player newPlayer2(name1,matches_won,matches_lost,games_won,games_lost,percent_win); 
		name1 = first_name1 + " " + last_name1;
		name2 = first_name2 + " " + last_name2;
		//cout << name1 << " " << name2 << endl;
		for (i = 0 ; i < players.size() ; ++i) {
			if (players[i].getName() == name1) {
				found1 = true;
				break;
			}
		}
		if (found1 == false) {
			//cout << name1 << endl;
			
			newPlayer1.setName(name1);
		}
		for (j = 0 ; j < players.size() ; ++j) {
			if (players[j].getName() == name2) {
				found2 = true;
				break;
			}
		}
		if (found2 == false) {
			//cout << name2 << endl;
			
			newPlayer2.setName(name2);
		}

		while (in_str >> set && isdigit(set[0]) ) {
			//cout << set << endl;
			games_won = 0;
			games_lost = 0;
			parse_set(set,games_won,games_lost);
			cout << "GAMES: " << games_won << " " << games_lost << endl;
			//cout << "PLAYER 1: " << player1.getGameWins() << " " << player1.getGameLosses() << endl;
			if (found1 == false) {
				newPlayer1.addGameWins(games_won);
				newPlayer1.addGameLosses(games_lost);
			} else {
				players[i].addGameWins(games_won);
				players[i].addGameLosses(games_lost);
			if (found2 == false) {
				newPlayer2.addGameWins(games_lost);
				newPlayer2.addGameLosses(games_won);
			} else {
				players[j].addGameWins(games_lost);
				players[j].addGameLosses(games_won);
			}
			//player1.addGameWins(games_won);
			//player2.addGameWins(games_lost);
			//player1.addGameLosses(games_lost);
			//player2.addGameLosses(games_won);
			cout << "PLAYER 2: " << player2.getGameWins() << " " << player2.getGameLosses() << endl;
			if (games_won > games_lost) {
				set_wins += 1;
			} else {
				set_lost += 1;
			}
			if (set_wins == 3 || set_wins == 3) {
				break;
			}
		}
		//cout << set_wins << " " << set_lost;
		if (set_wins > set_lost) {
			if (found1 == false) {
				newPlayer1.addMatchWins();
				players.push_back(newPlayer1);
			} else {
				players[i].addMatchWins();
			}
			if (found2 == false) {
				newPlayer2.addMatchLosses();
				players.push_back(newPlayer2);
			} else {
				players[j].addMatchLosses();
			}
		} else {
			if (found1 == false) {
				newPlayer1.addMatchLosses();
				players.push_back(newPlayer1);
			} else {
				players[i].addMatchLosses();
			}
			if (found2 == false) {
				newPlayer2.addMatchWins();
				players.push_back(newPlayer2);
			} else {
				players[j].addMatchWins();
			}
		}
	}