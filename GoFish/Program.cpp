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
	vector<Card> packs;
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

void addCardToPlayersDeck(Card card, Player &player)
{
	short index = findCardInPlayersDeck(card.power, player);

	if (index == -1)
	{
		player.deckOfThePlayer.push_back(card);
		return;
	}
	
	player.deckOfThePlayer[index].count += card.count;

	if (player.deckOfThePlayer[index].count == CARDS_IN_A_PACK)
	{
		player.packs.push_back(player.deckOfThePlayer[index]);

		player.deckOfThePlayer.erase(player.deckOfThePlayer.begin() + index);
	}
}

string draw(vector<Card> &deck, Player &player)
{
	srand(time(0));

	int randomCard = rand() % deck.size();

	addCardToPlayersDeck(deck[randomCard], player);

	string power = deck[randomCard].power;

	deck[randomCard].count--;

	if (!deck[randomCard].count)
	{
		deck.erase(deck.begin() + randomCard);
	}

	if (player.name == "player")
	{
		cout << "Drawed card is : " << power << endl;
	}

	return power;
}

void deal(vector<Card> &deck, Player &player)
{
	for (int i = 0; i < CARDS_IN_THE_BEGINNING; i++)
	{
		draw(deck, player);
	}
}

void printPlayersDeck(Player &player)
{
	for (int i = 0; i < player.deckOfThePlayer.size(); i++)
	{
		cout << player.deckOfThePlayer[i].count << player.deckOfThePlayer[i].power << ", ";
	}
	cout << endl;
}

string fullNameOfPower(string power)
{
	return power == "2" ? "twoes" :
		power == "3" ? "threes" :
		power == "4" ? "fours" :
		power == "5" ? "fives" :
		power == "6" ? "sixes" :
		power == "7" ? "sevens" :
		power == "8" ? "eights" :
		power == "9" ? "nines" :
		power == "10" ? "tens" :
		power == "J" ? "jacks" :
		power == "Q" ? "queens" :
		power == "K" ? "kings" : "aces";
}

bool givePower(string power, Player &to, Player &from)
{
	short index = findCardInPlayersDeck(power, from);
	
	if (index != -1)
	{
		addCardToPlayersDeck(from.deckOfThePlayer[index], to);

		from.deckOfThePlayer.erase(from.deckOfThePlayer.begin() + index);

		if (from.name == "computer")
		{
			cout << "The computer gives " << fullNameOfPower(power) << endl;
		}
		else
		{
			cout << "Give ";
			cin >> power;
			cout << endl;
		}

		return true;
	}

	cout << "The " << from.name << "doesn't have " << fullNameOfPower(power) << endl;
	return false;
}

void toLower(string &power)
{
	int index = 0;

	while (power[index])
	{
		if (power[index] < 'a')
		{
			power[index] += 'a' - 'A';
		}

		index++;
	}
}

void correctCard(string &power)
{
	toLower(power);

	bool result = power == fullNameOfPower("2") ? true :
		power == fullNameOfPower("3") ? true :
		power == fullNameOfPower("4") ? true :
		power == fullNameOfPower("5") ? true :
		power == fullNameOfPower("6") ? true :
		power == fullNameOfPower("7") ? true :
		power == fullNameOfPower("8") ? true :
		power == fullNameOfPower("9") ? true :
		power == fullNameOfPower("10") ? true :
		power == fullNameOfPower("J") ? true :
		power == fullNameOfPower("Q") ? true :
		power == fullNameOfPower("K") ? true :
		power == fullNameOfPower("A") ? true : false;

	while (!result)
	{
		cout << "Incorrect card power! Please try again!" << endl << "Ask for ";
		cin >> power;
	}
}

void symbolOfCard(string& power)
{
	power = power == fullNameOfPower("2") ? "2" :
		power == fullNameOfPower("3") ? "3" :
		power == fullNameOfPower("4") ? "4" :
		power == fullNameOfPower("5") ? "5" :
		power == fullNameOfPower("6") ? "6" :
		power == fullNameOfPower("7") ? "7" :
		power == fullNameOfPower("8") ? "8" :
		power == fullNameOfPower("9") ? "9" :
		power == fullNameOfPower("10") ? "10" :
		power == fullNameOfPower("J") ? "J" :
		power == fullNameOfPower("Q") ? "Q" :
		power == fullNameOfPower("K") ? "K" : "A";
}

string askPower(Player &ask, Player &give, vector<Card> &deck)
{
	string power;

	if (ask.name == "computer")
	{
		srand(time(0));

		int randomCard = rand() % ask.deckOfThePlayer.size();

		power = ask.deckOfThePlayer[randomCard].power;

		cout << "The computer asks for " << fullNameOfPower(power) << endl;
	}
	else
	{
		printPlayersDeck(ask);

		cout << "Ask for ";
		cin >> power;

		correctCard(power);

		symbolOfCard(power);
	}

	return givePower(power, ask, give) ? "true" : "false" + power;
}

void gamePartOne(vector<Card> &deck, vector<Player> players)
{
	while (!deck.empty())
	{
		string get = askPower(players.front(), players.back(), deck);

		while (get == "true")
		{
			get = askPower(players.front(), players.back(), deck);
		}

		string card = draw(deck, players.front());

		get.erase(0, 4);

		if (card == get)
		{
			askPower(players.front(), players.back(), deck);
		}



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

	gamePartOne(deck, players);

	return 0;
}