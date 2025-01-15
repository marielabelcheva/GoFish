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
const short PACKS_IN_THE_DECK = 13;
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
	vector<string> packs;
};

void deckInitialization(vector<Card>& deck)
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

void playersInitialization(vector<Player>& players)
{
	players.push_back({ "player" });
	players.push_back({ "computer" });
}

void printPlayersDeck(Player& player)
{
	for (int i = 0; i < player.deckOfThePlayer.size(); i++)
	{
		cout << player.deckOfThePlayer[i].power << "[" << player.deckOfThePlayer[i].count << "] ";
	}
	cout << endl;
}

void printPlayersPacks(Player& player)
{
	for (int i = 0; i < player.packs.size(); i++)
	{
		cout << player.packs[i] << " ";
	}
	cout << endl;
}

short findCardInPlayersDeck(string cardPower, Player& player)
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

short findAPackInPlayersCollection(string power, Player& player)
{
	for (int i = 0; i < player.packs.size(); i++)
	{
		if (player.packs[i] == power)
		{
			return i;
		}
	}

	return -1;
}

void addCardToPlayersDeck(Card card, Player& player)
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
		string power;

		if (player.name == "player")
		{
			printPlayersDeck(player);

			cout << "\nPut down a pack of ";
			cin >> power;
			cout << endl;
		}
		else
		{
			power = fullNameOfPower(player.deckOfThePlayer[index].power);
			cout << "The computer puts down a pack of " << power << endl;
		}

		player.packs.push_back(player.deckOfThePlayer[index].power);

		player.deckOfThePlayer.erase(player.deckOfThePlayer.begin() + index);
	}
}

string draw(vector<Card>& deck, Player& player)
{
	int randomCard = rand() % deck.size();

	string power = deck[randomCard].power;

	addCardToPlayersDeck({power, 1}, player);

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

void deal(vector<Card>& deck, Player& player)
{
	for (int i = 0; i < CARDS_IN_THE_BEGINNING; i++)
	{
		draw(deck, player);
	}
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

void outputWhenCardsAreGiven(string power, Player& player)
{
	if (player.name == "computer")
	{
		cout << "The computer gives " << fullNameOfPower(power) << endl;
		return;
	}

	cout << "Give ";
	cin >> power;
	cout << endl;
}

bool givePower(string power, Player& to, Player& from, short gamePart = 1)
{
	short index = gamePart == 1 ? findCardInPlayersDeck(power, from) : findAPackInPlayersCollection(power, from);

	if (index != -1)
	{
		if (gamePart == 1)
		{
			addCardToPlayersDeck(from.deckOfThePlayer[index], to);

			from.deckOfThePlayer.erase(from.deckOfThePlayer.begin() + index);
		}
		else 
		{
			to.packs.push_back(power);

			from.packs.erase(from.packs.begin() + index);
		}

		outputWhenCardsAreGiven(power, from);

		return true;
	}

	cout << "The " << from.name << " doesn't have " << fullNameOfPower(power) << endl;
	return false;
}

void toLower(string& power)
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

void correctCard(string& power)
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

void playerIsAskingCards(Player& player, string& power, short gamePart = 1)
{
	cout << endl;

	gamePart == 1 ? printPlayersDeck(player) : printPlayersPacks(player);

	cout << "\nAsk for ";
	cin >> power;

	correctCard(power);

	// if the asked card is in the deck || packs of the player

	symbolOfCard(power);
}

string askPower(Player& ask, Player& give, short gamePart = 1)
{
	string power;

	if (ask.name == "computer")
	{
		int randomCard = gamePart == 1 ? rand() % ask.deckOfThePlayer.size() : rand() % ask.packs.size();

		power = gamePart == 1 ? ask.deckOfThePlayer[randomCard].power : ask.packs[randomCard];

		cout << "The computer asks for " << fullNameOfPower(power) << endl;
	}
	else
	{
		playerIsAskingCards(ask, power, gamePart);
	}

	return givePower(power, ask, give, gamePart) ? "true" : power;
}

void gamePartOne(vector<Card>& deck, vector<Player>& players)
{
	if (deck.empty() && players.front().deckOfThePlayer.empty() && players.back().deckOfThePlayer.empty())
	{
		cout << "End of part one of the game!" << endl;
		return;
	}

	string card;
	string get = askPower(players.front(), players.back());

	if (get != "true")
	{
		card = draw(deck, players.front());
	}

	if (!card.empty() && card != get)
	{
		reverse(players.begin(), players.end());
	}

	gamePartOne(deck, players);
}

void gamePartTwo(vector<Player>& players)
{
	if (players.front().packs.size() == PACKS_IN_THE_DECK || players.back().packs.size() == PACKS_IN_THE_DECK)
	{
		string winner = players.front().packs.size() == PACKS_IN_THE_DECK ? players.front().name : players.back().name;
		cout << "Game over!\n The winner is " << winner << "!\n";

		return;
	}

	string get = askPower(players.front(), players.back(), 2);
	
	if (get != "true")
	{
		reverse(players.begin(), players.end());
	}

	gamePartTwo(players);
}

int main()
{
	vector<Card> deck;
	vector<Player> players;

	deckInitialization(deck);
	playersInitialization(players);

	srand(time(0));

	deal(deck, players.front());
	deal(deck, players.back());

	//cout << endl;

	gamePartOne(deck, players);

	// if the user is in second place - reverse the vector

	gamePartTwo(players);

	return 0;
}