#include <cassert>
#include "superhero.h"
#include "team.h"

using namespace std;

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0)
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (unsigned int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

void Team::operator+=(const Superhero &hero) {
	superheroes.push_back(hero);
}

void Team::operator-=(const Superhero &hero) {
	for (list<Superhero>::iterator itr = superheroes.begin(); itr != superheroes.end(); ++itr) {
		if (hero.getName() == itr->getName()) {
			superheroes.erase(itr);
			break;
		}
	}
}

Team operator+(const Team &a,const Team &b) {
	Team newTeam;
	for (list<Superhero>::const_iterator itr = a.superheroes.begin(); itr != a.superheroes.end(); ++itr) {
		newTeam += *itr;
	}
	for (list<Superhero>::const_iterator itr = b.superheroes.begin(); itr != b.superheroes.end(); ++itr) {
		newTeam += *itr;
	}
	return newTeam;
}

Team operator+(const Team &a, const Superhero &b) {
	Team newTeam;
	for (list<Superhero>::const_iterator itr = a.superheroes.begin(); itr != a.superheroes.end(); ++itr) {
		newTeam += *itr;
	}
	newTeam += b;
	return newTeam;
}

Team operator+(const Superhero &a, const Superhero &b) {
	Team newTeam;
	newTeam += a;
	newTeam += b;
	return newTeam;
}