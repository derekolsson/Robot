

#include "simpletools.h"                      // incluir simpletools para controladores de la placa
#include "abdrive.h"                          // Incluir abdrive para encoders y servos
#include "ping.h"                             // Incluir ping para sensor

//Advance = 1, go back = 0
int advance;                               

/*
	map[cont][direction]
	directions:	0 = forward, the direction ActivityBot entered from
				1 = left (relative)
				2 = right (relative)
*/				
int map[1000][3];							  

//which "section" we are in
int cont;

//will check for openings (0 open, 1 closed)
int checkWall();
int checkLeft();
int checkRight();

//checks straight, left then right
void checkSpace(int i, int x[][3]);

//turn left, right or 180 degrees upon itself
void turnLeft();
void turnRight();
void turnAround();

//go straight forward or straight back
void goForward();
void goBack();


int main()                                  // main 
{
  //int map[1000][3]={{0},{0}};
	cont = 0;
	advance = 1;

	  while(1){									//endless loop
		while (advance == 1){					//if advancing
        checkSpace(cont, map);						//first check the space
			
			//priority to go: Right, Straight, Left
			//after, increment counter
			
			if (map[cont][0]== 0){				
				goForward();
				cont = cont + 1;
			}
			
			else if (map[cont][1] == 0){
				turnLeft();
				goForward();
				cont = cont + 1;
			}
			
			else if (map[cont][2] == 0){
				turnRight();
				goForward();
				cont = cont + 1;
			}
			
			//if nothing, face "forward", return to last square, begin backwards routine
			else{
				cont = cont - 1;
				goBack();
				advance = 0;
			}
		}
		
		//backwards routine 
		while (advance == 0){
			
			//decrement cont to see prior space
			cont = cont - 1;
			//check in order: Right, Forward, Left from last space
			//turn so back facing opening, then go backwards
			//"close" direction you came from
			
			//Forward
			if (map[cont][0] == 0){
				goBack();			//go backwards
				map[cont][0] == 1;	//close right
			}
			//Left
			else if (map[cont][1] == 0){
				goBack();
				turnRight();
				map[cont][1] == 1;
			}
			//Right
			else if (map[cont][2] == 0){
				goBack();
				turnLeft();
				map[cont][2] == 1;
			}
			
			//if no openings left, it's basically stuck, so break routine
			else{
				advance = 4;
			}
			
			//restart advance
			//tries Straight, Left, Right
			if (map[cont][0] == 0){
				goForward();				//go forward
				cont = cont + 1;			//increment cont
				advance = 1;				//restart advance loop
			}
			
			//left
			else if (map[cont][1] == 0){
				turnLeft();
				goForward();
				cont = cont + 1;
				advance = 1;
			}
			//right
			else if (map[cont][2] == 0){
				turnRight();
				goForward();
				cont = cont + 1;
				advance = 1;
			}
			
			
	  }
	}
	return 0;
}

int			
checkWall(){		//If there's a wall within 7cm, return 1, else 0

	if (ping_cm(8) < 15){
		return 1;
	}
	else{
		return 0;
	}
}

int
checkRight(){
	int right;
	freqout(0,1,38000);
	right = input(1);
	return right;
}

int
checkLeft(){
	int left;
	freqout(13,1,38000);
	left = input(11);
	return left;
}

void
checkSpace(int i, int x[][3]){		//Check each space for straight, left then right
	x[i][0] = checkWall();
	
	//turnLeft();
	
	
	x[i][1] = checkLeft();
	
	//turnAround();
	
	x[i][2]= checkRight();
	
	return;
	}
	
void 
turnLeft(){
	drive_goto(-26, 25);
    //pause(250);
	return;
}
	
void 
turnRight(){
	drive_goto(26, -25);
    //pause(250);
	return;
}

void 
turnAround(){
	drive_goto(-53,52);
	//pause(250);
	return;
}

void 
goForward(){
	drive_goto(25,25);
	//pause(250);
	return;
}

void 
goBack(){
	drive_goto(-25,-25);
	//pause(100);
	return;
}





