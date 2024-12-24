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

const short PACKS_IN_THE_DECK = 13;
const short CARDS_IN_A_PACK = 4;

struct Card
{
	char power;
	unsigned short count;
};



int main()
{
	Card deck[PACKS_IN_THE_DECK] =
	{
		{'2', CARDS_IN_A_PACK},
		{'3', CARDS_IN_A_PACK},
		{'4', CARDS_IN_A_PACK},
		{'5', CARDS_IN_A_PACK},
		{'6', CARDS_IN_A_PACK},
		{'7', CARDS_IN_A_PACK},
		{'8', CARDS_IN_A_PACK},
		{'9', CARDS_IN_A_PACK},
		{'10', CARDS_IN_A_PACK},
		{'J', CARDS_IN_A_PACK},
		{'Q', CARDS_IN_A_PACK},
		{'K', CARDS_IN_A_PACK},
		{'A', CARDS_IN_A_PACK}
	};

	return 0;
}