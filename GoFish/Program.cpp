/*
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Mariela Belcheva
* @idnumber 1MI0600413
* @compiler VC
*
* <предназначение на файла>
*
*/

#include <iostream>;
#include <string>;
#include <cstdlib>;
#include <ctime>;
#include <vector>;

using namespace std;

const short CARDS_IN_A_PACK = 4;
const short CARDS_IN_THE_BEGINNING = 6;

struct Card
{
	string power;
	unsigned short count;
};

struct Player
{
	string name;
	vector<Card> deckOfThePlayer;
};

void deckInitialization(vector<Card> &deck)
{
	deck.push_back({ "2", CARDS_IN_A_PACK });
	deck.push_back({ "3", CARDS_IN_A_PACK });
	deck.push_back({ "4", CARDS_IN_A_PACK });
	deck.push_back({ "5", CARDS_IN_A_PACK });
	deck.push_back({ "6", CARDS_IN_A_PACK });
	deck.push_back({ "7", CARDS_IN_A_PACK });
	deck.push_back({ "8", CARDS_IN_A_PACK });
	deck.push_back({ "9", CARDS_IN_A_PACK });
	deck.push_back({ "10", CARDS_IN_A_PACK });
	deck.push_back({ "J", CARDS_IN_A_PACK });
	deck.push_back({ "Q", CARDS_IN_A_PACK });
	deck.push_back({ "K", CARDS_IN_A_PACK });
	deck.push_back({ "A", CARDS_IN_A_PACK });
}

void playersInitialization(vector<Player> &players)
{
	players.push_back({ "player"});
	players.push_back({ "computer" });
}

short findCardInPlayersDeck(string cardPower, Player &player)
{
	for (int i = 0; i < player.deckOfThePlayer.size(); i++)
	{
		if (player.deckOfThePlayer[i].power == cardPower)
		{
			return i;
		}
	}

	return -1;
}

void addCardToPlayersDeck(string cardPower, Player &player)
{
	short index = findCardInPlayersDeck(cardPower, player);

	if (index >= 0)
	{
		player.deckOfThePlayer[index].count++;
	}
	else
	{
		player.deckOfThePlayer.push_back({ cardPower, 1 });
	}
}

void draw(vector<Card> &deck, Player &player)
{
	srand(time(0));

	int randomCard = rand() % deck.size();

	string cardpower = deck[randomCard].power;
	addCardToPlayersDeck(cardpower, player);

	deck[randomCard].count--;

	if (!deck[randomCard].count)
	{
		deck.erase(deck.begin() + randomCard);
	}
}

void deal(vector<Card> &deck, Player &player)
{
	for (int i = 0; i < CARDS_IN_THE_BEGINNING; i++)
	{
		draw(deck, player);
	}
}

int main()
{
	vector<Card> deck;
	vector<Player> players;

	deckInitialization(deck);
	playersInitialization(players);

	deal(deck, players.front());
	deal(deck, players.back());

	return 0;
}