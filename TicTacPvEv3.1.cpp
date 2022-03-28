#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int back = 0;
char playingField [9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int turns = 0;
int games = 1;
int compChoise = 10;
int comp = 'k';
int hum = 'k';


void clue();
void showGame();
bool win(char player);
int computerChoice(char player);
void newGame();
void peopleTurn(char player);
void computerTurn(char player);
void congratulations(char charOfPlayer);
bool draw();
int isWin(char player);
int myTurn();
int opTurn();
int myBestTurn();

/*This version (v3.0) never loses punishes the opponent for every mistake. Play 4 different debits*/

int main()
{
	char human = 'h';	
	char computer = 'c';
	char playerOne = 'x';
	char playerTwo = '0';
	int playerChoice = 0;
			
	while (true){
		system("cls");
		cout << "Choose a symbol " << endl;
		cout << "1 - x" << endl;
		cout << "2 - 0" << endl << endl;
		cout << "Your choise: ";
		cin >> playerChoice;
		
		if (playerChoice == 1){
			comp = '0';
			hum = 'x';
			break;
		}
			
		else if (playerChoice == 2){
			comp = 'x';
			hum = '0';
			break;
		}				
		else {
			cout << "Input [1..2], please" << endl << endl;			
			cout << "Enter any number to return: ";
			cin >> back;
		}
	}	
			
	if (playerChoice == 1)
	{
		while (true)
		{		
			peopleTurn(playerOne);
		
			if (win(playerOne)){
				congratulations(human);					
				continue;
			}
			
			if (draw())					
				continue;									
				
			computerTurn(playerTwo);
				
			if (win(playerTwo)){
				congratulations(computer);					
				continue;
			}		
		}	
	}
		
	if (playerChoice == 2)
	{
		while (true)
		{			
			computerTurn(playerOne);
		
			if (win(playerOne)){
				congratulations(computer);					
				continue;
			}
				
			if (draw())
				continue;
								
			peopleTurn(playerTwo);
				
			if (win(playerTwo)){
				congratulations(human);					
				continue;
			}		
		}				
	}
	
	return 0;
}

void clue()
{
	cout << "Clue:" << endl << endl;
	cout << " 1 | 2 | 3 " << endl;
	cout << "-----------" << endl;
	cout << " 4 | 5 | 6 " << endl;
	cout << "-----------" << endl;
	cout << " 7 | 8 | 9 " << endl;	
	cout << endl;
	cout << endl;
}

void showGame()
{
	int counter = 0;
	
	cout << "Playing field:" << endl << endl;
	
	for (int i = 0; i < 9; i++){
		cout << " " << playingField [i] << " ";
		if (i == 8)
			break;
		counter++;
		if (counter < 3)
			cout << "|";
		else{
			cout << endl;
			cout << "-----------" << endl;
			counter = 0;
		}	
	}
	
	cout << endl;
	cout << endl;
	cout << "Game " << games << " Turn " << turns << endl;
	cout << endl;	
}

bool win(char player)
{
	bool win = false;	
	
	if (playingField[0] == player and playingField[0] == playingField[1] and playingField[1] == playingField[2])
		win = true;
	if (playingField[3] == player and playingField[3] == playingField[4] and playingField[4] == playingField[5])
		win = true;
	if (playingField[6] == player and playingField[6] == playingField[7] and playingField[7] == playingField[8])
		win = true;
	if (playingField[0] == player and playingField[0] == playingField[3] and playingField[3] == playingField[6])
		win = true;
	if (playingField[1] == player and playingField[1] == playingField[4] and playingField[4] == playingField[7])
		win = true;
	if (playingField[2] == player and playingField[2] == playingField[5] and playingField[5] == playingField[8])
		win = true;
	if (playingField[0] == player and playingField[0] == playingField[4] and playingField[4] == playingField[8])
		win = true;
	if (playingField[2] == player and playingField[2] == playingField[4] and playingField[4] == playingField[6])
		win = true;	
		
	return win;							
}

int computerChoice(char player)
{
	int randomNum = 0;
	srand( time(0) );
	
	if (isWin(player))
		return isWin(player); 
	
	while (true)
	{
		randomNum = 1 + rand() % 9;
						
		if (playingField [randomNum - 1] == ' ')
			break;		
	}
	
	cout << "My turn is " << randomNum << endl;
	
	return randomNum;	
}

void newGame()
{
	turns = 0;
	compChoise = 10;
	
	for (int i = 0; i < 9; i++)
		playingField [i] = ' ';
}

void peopleTurn(char player)
{
	while (true)
	{			
		int humanChoice = 9;
		system("cls");		
		clue();
		showGame();
		
		if (compChoise != 10 and player == 'x')
			cout << "Computer put 0 on cell " << compChoise << endl << endl;
		if (compChoise != 10 and player == '0')
			cout << "Computer put x on cell " << compChoise << endl << endl;		
					
		cout << "Choose a cell please: ";
		cin >> humanChoice;
					
		if (playingField [humanChoice - 1] == ' '){
			playingField [humanChoice - 1] = player;
			turns++;
			break;
		}						
		else{
			cout << "Impossible move, choose a free cell please" << endl;
			cout << "Enter any number to return: ";
			cin >> back; 
		}
	}
}

void computerTurn(char player)
{
	compChoise = myBestTurn();	
	
	playingField [compChoise - 1] = player;	
	turns++;	 	
}

void congratulations(char charOfPlayer)
{
	system("cls");
	clue();
	showGame();
	newGame();
	games++;
	if (charOfPlayer == 'h')
		cout << "Human won!" << endl << endl;
	if (charOfPlayer == 'c')
		cout << "Computer won!" << endl << endl;	
	cout << "Enter any number to return: ";
	cin >> back;
}

bool draw()
{
	if (turns == 9){
		newGame();
		games++;
		system("cls");
		clue();
		showGame();
		cout << endl;
		cout << "Draw" << endl << endl;
		cout << "Enter any number to return: ";
		cin >> back;
		return true;
	}else
		return false;		
}

int isWin(char player)
{
	for (int i = 1; i < 10; i ++){
		if (playingField [i - 1] == ' ')
		{
			playingField [i - 1] = player;
			if (win(player)){
				playingField [i - 1] = ' ';
				return i;
			}
			else
				playingField [i - 1] = ' '; 
		} 
	}
	
	return 0;	
}

int myTurn()
{
	int result = 1;
	int maxResult = -1;
	
	turns++;
			
	if(isWin(comp)){
		turns--;
		return 1;
	}
	
	if (turns == 9){
		turns--;
		return 0;
	}
			
	for (int i = 1; i < 10; i++){
		if (playingField[i - 1] == ' '){
			playingField[i - 1] = comp;
			
			result = 1;			
			
			if (opTurn() < result)
				result = opTurn();;
									
			playingField[i - 1] = ' ';	
			
			if (result == 1){
				turns--;
				return 1;
			}				
			
			if (result > maxResult)
				maxResult = result;									
		}		
	}
	
	turns--;
	return maxResult;
}

int opTurn()
{
	int result = -1;
	int minResult = 1;
	
	turns++;
	
	if(isWin(hum)){
		turns--;
		return -1;
	}
	
	if (turns == 9){
		turns--;
		return 0;
	}	
	
	for (int i = 1; i < 10; i++){
		if (playingField[i - 1] == ' '){
			playingField[i - 1] = hum;
			
			result = -1;
			
			if (myTurn() > result)
				result = myTurn();
					
			playingField[i - 1] = ' ';	
			
			if (result == -1){
				turns--;
				return result;
			}				
				
			if (result < minResult)
				minResult = result;
		}			
	}
	
	turns--;
	return minResult;
}

int myBestTurn()
{
	int result = 1;
	int maxResult = -1;
	int bestTurn = 10;
	
	if (turns == 0 and (games % 4) == 0)
		return 1;
	else if (turns == 0 and (games % 4) == 1)
		return 2;
	else if (turns == 0 and (games % 4) == 2)
		return 3;
	else if (turns == 0 and (games % 4) == 3)
		return 5;			
	else{
		
		turns++;
				
		if(isWin(comp)){
			turns--;
			return isWin(comp);
		}
		
		if (turns == 9){
			for (int i = 1; i < 10; i++){
				if (playingField[i - 1] == ' '){
					turns--;
					return i;
				}				
			}		
		}
				
		for (int i = 1; i < 10; i++){
			if (playingField[i - 1] == ' '){
				playingField[i - 1] = comp;
				
				result = 1;			
				
				if (opTurn() < result)
					result = opTurn();;
										
				playingField[i - 1] = ' ';	
				
				if (result == 1){
					turns--;
					return i;
				}				
				
				if (result > maxResult){
					maxResult = result;
					bestTurn = i;
				}
														
			}		
		}
		
		turns--;
		return bestTurn;
	}
}

