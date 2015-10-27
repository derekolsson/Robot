

#include "simpletools.h"                      // incluir simpletools para controladores de la placa
#include "abdrive.h"                          // Incluir abdrive para encoders y servos
#include "ping.h"                             // Incluir ping para sensor

//Advance = 1, go back = 0
int advance;                               

/*
	map[count][direction]
	directions:	0 = forward, the direction AB entered from
				1 = left
				2 = right
*/				
int map[500][2];							  
//which "section" we are in
int count;

//will check for openings (0 open, 1 closed)
int checkWall();
//checks straight, left then right
void checkSpace();

//turn left, right or 180 degrees upon itself
void turnLeft();
void turnRight();
void turnAround();

//go straight forward or straight back
void goForward();
void goBack();


int main()                                  // main 
{
	count = 0;
	advance = 1;

	  for(;;){									//endless loop
		while (advance == 1){					//if advancing
			checkSpace();						//first check the space
			
			//priority to go: Right, Straight, Left
			//after, increment counter
			
			if (map[count][2]== 0){				
				goForward();
				count = count + 1;
			}
			
			else if (map[count][0] == 0){
				turnLeft();
				goForward();
				count = count + 1;
			}
			
			else if (map[count][1] == 0){
				turnAround();
				goForward();
				count = count + 1;
			}
			
			//if nothing, face "forward", return to last square, begin backwards routine
			else{
				turnLeft();
				count = count - 1;
				goBack();
				advance = 0;
			}
		}
		
		//backwards routine 
		while (advance == 0){
			
			//decrement count to see prior space
			count = count - 1;
			//check in order: Right, Forward, Left from last space
			//turn so back facing opening, then go backwards
			//"close" direction you came from
			
			//Right
			if (map[count][2] == 0){
				turnLeft();			//face opening
				goBack();			//go backwards
				turnLeft();			//face "forward"
				map[count][2] == 1;	//close right
			}
			//Forward
			else if (map[count][0] == 0){
				goBack();
				map[count][0] == 1;
			}
			//Left
			else if (map[count][1] == 0){
				turnRight();
				goBack();
				turnRight;
				map[count][1] == 1;
			}
			
			//if no openings left, it's basically stuck, so break routine
			else{
				advance = 4;
			}
			
			//restart advance
			//tries right, then straight, then left
			if (map[count][2] == 0){
				turnRight();				//face right
				goForward();				//go forward
				count = count + 1;			//increment count
				advance = 1;				//restart advance loop
			}
			
			//straight
			else if (map[count][0] == 0){
				goForward();
				count = count + 1;
				advance = 1;
			}
			//left
			else if (map[count][1] == 0){
				turnRight();
				goForward();
				count = count + 1;
				advance = 1;
			}
			
			
	  }
	}
	return 0;
}
	int			
	checkWall(){		//If there's a wall within 5cm, return 1, else 0

		if (ping_cm(8) < 5){
			return 1;
		}
		else{
			return 0;
		}
	}

void
checkSpace(){		//Check each space for straight, left then right
	map[count][0] = checkWall();
	
	turnLeft();
	
	map[count][1] = checkWall();
	
	turnAround();
	
	map[count][2]= checkWall();
	
	return;
	}
	
void 
turnLeft(){
	drive_goto(-26, 25);
    pause(250);
	return;
}
	
void 
turnRight(){
	drive_goto(26, -25);
    pause(250);
	return;
}

void 
turnAround(){
	drive_goto(-51,50);
	pause(250);
	return;
}

void 
goForward(){
	drive_goto(65,64);
	pause(250);
	return;
}

void 
goBack(){
	drive_goto(-65,-64);
	pause(250);
	return;
}





