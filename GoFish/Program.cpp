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
* <файл, съдържащ програмата>
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
const short DRAW_A_CARD = 1;

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
	if (player.name == "computer")
	{
		return;
	}

	for (int i = 0; i < player.deckOfThePlayer.size(); i++)
	{
		cout << player.deckOfThePlayer[i].power << "[" << player.deckOfThePlayer[i].count << "] ";
	}
	cout << endl;
}

void printPlayersPacks(Player& player)
{
	cout << "Packs: ";

	for (int i = 0; i < player.packs.size(); i++)
	{
		cout << player.packs[i] << " ";
	}

	cout << endl;
}

short findCardsInPlayersCollection(string cardPower, Player& player, bool gamePartOne = true)
{
	short end = gamePartOne ? player.deckOfThePlayer.size() : player.packs.size();

	for (int i = 0; i < end; i++)
	{
		string power = gamePartOne ? player.deckOfThePlayer[i].power : player.packs[i];

		if (power == cardPower)
		{
			return i;
		}
	}

	return -1;
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

void addCardToPlayersDeck(Card card, Player& player)
{
	short index = findCardsInPlayersCollection(card.power, player);

	if (index == -1)
	{
		player.deckOfThePlayer.push_back(card);
		return;
	}

	player.deckOfThePlayer[index].count += card.count;
}

string draw(vector<Card>& deck, Player& player)
{
	int randomCard = rand() % deck.size();

	string power = deck[randomCard].power;

	addCardToPlayersDeck({power, DRAW_A_CARD}, player);

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

void addPackToPlayersCollection(Player& player)
{
	printPlayersDeck(player);

	for (int i = 0; i < player.deckOfThePlayer.size(); i++)
	{
		if (player.deckOfThePlayer[i].count == CARDS_IN_A_PACK)
		{
			string power;

			if (player.name == "player")
			{
				cout << "Put down a pack of ";
				cin >> power;
			}
			else
			{
				power = fullNameOfPower(player.deckOfThePlayer[i].power);
				cout << "The computer puts down a pack of " << power << endl;
			}

			player.packs.push_back(player.deckOfThePlayer[i].power);

			player.deckOfThePlayer.erase(player.deckOfThePlayer.begin() + i);

			cout << "\n";

			printPlayersDeck(player);
		}
	}
}

void outputWhenGivingCards(string power, Player& player, bool give = true)
{
	if (player.name == "computer")
	{
		cout << "The " << player.name;
		cout << (give ? " gives " : " doesn't have ");
		cout << fullNameOfPower(power) << endl;

		return;
	}

	cout << (give ? "Give " : "Don't have ");

	cin >> power;
}

bool givePower(string power, Player& to, Player& from, bool gamePartOne = true)
{
	short index = findCardsInPlayersCollection(power, from, gamePartOne);

	bool give = index != -1;

	if (give)
	{
		if (gamePartOne)
		{
			addCardToPlayersDeck(from.deckOfThePlayer[index], to);

			from.deckOfThePlayer.erase(from.deckOfThePlayer.begin() + index);
		}
		else 
		{
			to.packs.push_back(power);

			from.packs.erase(from.packs.begin() + index);
		}
	}

	outputWhenGivingCards(power, from, give);

	return give;
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

void getTheSignOfPower(string& power)
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
		power == fullNameOfPower("K") ? "K" :
		power == fullNameOfPower("A") ? "A" : "0";
}

void enteringPower(Player& player, string& power, bool gamePartOne = true)
{
	toLower(power);

	getTheSignOfPower(power);

	short index = 0;

	if (gamePartOne)
	{
		index = power != "0" ? findCardsInPlayersCollection(power, player) : 0;
	}

	if (power != "0" && index != -1)
	{
		return;
	}

	cout << "Incorrect card power! ";
	cout << (gamePartOne ? "Please enter card power which is in your collection!" : "Please try again!");
	cout << "\nAsk for ";
	cin >> power;

	enteringPower(player, power, gamePartOne);
}

void playerIsAskingCards(Player& player, string& power, bool gamePartOne = true)
{
	cout << "Ask for ";
	cin >> power;

	enteringPower(player, power, gamePartOne);
}

string askPower(Player& ask, Player& give, bool gamePartOne = true)
{
	string power;

	if (ask.name == "computer")
	{
		if (!gamePartOne)
		{
			printPlayersPacks(give);
		}

		int randomCard = gamePartOne ? rand() % ask.deckOfThePlayer.size() : rand() % ask.packs.size();

		power = gamePartOne ? ask.deckOfThePlayer[randomCard].power : ask.packs[randomCard];

		cout << "The computer asks for " << fullNameOfPower(power) << endl;
	}
	else
	{
		playerIsAskingCards(ask, power, gamePartOne);
	}

	return givePower(power, ask, give, gamePartOne) ? "true" : power;
}

void playerHasNoCardsInHisDeck(vector<Card>& deck, vector<Player>& players)
{
	if (players.front().deckOfThePlayer.empty())
	{
		deck.empty() ? draw(players.back().deckOfThePlayer, players.front()) : draw(deck, players.front());
		return;
	}

	deck.empty() ? draw(players.front().deckOfThePlayer, players.back()) : draw(deck, players.back());
}

void swapPlayers(vector<Player>& players)
{
	Player swap = players.front();
	players.front() = players.back();
	players.back() = swap;
}

void gamePartOne(vector<Card>& deck, vector<Player>& players)
{
	addPackToPlayersCollection(players.front());
	addPackToPlayersCollection(players.back());

	if (deck.empty() && players.front().deckOfThePlayer.empty() && players.back().deckOfThePlayer.empty())
	{
		cout << "\nEnd of part one of the game!\n";
		return;
	}

	if (players.front().deckOfThePlayer.empty() || players.back().deckOfThePlayer.empty())
	{
		playerHasNoCardsInHisDeck(deck, players);
	}

	string card;
	string get = askPower(players.front(), players.back());

	if (get != "true" && !deck.empty())
	{
		card = draw(deck, players.front());
	}

	if (!card.empty() && card != get)
	{
		swapPlayers(players);
	}

	cout << "\n";
	gamePartOne(deck, players);
}

void gamePartTwo(vector<Player>& players)
{
	if (players.front().packs.size() == PACKS_IN_THE_DECK || players.back().packs.size() == PACKS_IN_THE_DECK)
	{
		string winner = players.front().packs.size() == PACKS_IN_THE_DECK ? players.front().name : players.back().name;
		cout << "\nGame over!\nThe winner is " << winner << "!\n";

		return;
	}

	string get = askPower(players.front(), players.back(), false);
	
	if (get != "true")
	{
		swapPlayers(players);
	}

	cout << "\n";
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

	cout << "\n";

	gamePartOne(deck, players);

	if (players.front().name == "computer")
	{
		swapPlayers(players);
	}

	cout << "\n";

	gamePartTwo(players);

	return 0;
}