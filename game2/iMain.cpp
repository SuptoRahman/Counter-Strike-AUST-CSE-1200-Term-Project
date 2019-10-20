




# include "iGraphics.h"
#include<stdlib.h>
#include<string.h>

#include "bullet.h"
#include "bomb.h"
#define SCREENWIDTH 1000
#define SCREENHEIGHT 600
#define JUMPLIMIT 110
#define ENEMYSNUMBER 3
#define HELICOPTERNUMBER 1
int mposx, mposy;


//images of Soldier,SoldierJump and SoldierStand 
char Soldier[6][15] = { "player\\1.bmp", "player\\2.bmp", "player\\3.bmp", "player\\4.bmp", "player\\5.bmp", "player\\6.bmp" };
char SoldierJump[2][15] = { "player\\j1.bmp", "player\\j2.bmp" };
char SoldierStand[15] = { "player\\11.bmp" };

//variables for soldier(player) 
int SoldierIndex = 0;
int SoldierCordinateX = 0;
int SoldierCordinateY = 0;
int SoldierWidth = 93;
int SoldierHeight = 113;
int standCounter = 0;
int SoldierCordinateJump = 0;

bool standPosition = true;
bool jump = false;
bool jumpUp = false;





//String variable terroristOne and HelicopterOne for enemy images
char terroristOne[12][20] = { "enemy\\1.bmp", "enemy\\2.bmp", "enemy\\3.bmp", "enemy\\4.bmp", "enemy\\5.bmp", "enemy\\6.bmp", "enemy\\7.bmp", "enemy\\8.bmp", "enemy\\9.bmp", "enemy\\10.bmp", "enemy\\11.bmp", "enemy\\12.bmp" };
char HelicopterOne[4][18] = { "helicopter\\h1.bmp", "helicopter\\h2.bmp", "helicopter\\h3.bmp", "helicopter\\h4.bmp" };



char BulletOne[15] = { "bullet\\b1.bmp" };//for bullet image
char BombOne[20] = { "bullet\\blast.bmp" };//for bomb image

//variables for health and score
//Intially Health of the player will be 3
int health = 3;
int score = 0;
char scoreArray[50];
char HealthArray[50];

char scoreStr[10];
FILE *fpp;




int gameState = -2;//intial state of the game(game loading page)
int save = 0;


//String variables for GUI
char startp[15] = "wall\\Start.bmp"; //for game loading page
char menu[15] = "wall\\Menu.bmp"; //for home menu
char credit[20] = "wall\\credit.bmp";// for credit page 
char highscoreOne[25] = "wall\\highscore.bmp";//for highscore page
char ins[15] = "wall\\help.bmp"; //for instruction page
char button[10][15] = { "wall\\s.bmp", "wall\\h.bmp", "wall\\sc.bmp", "wall\\c.bmp", "wall\\e.bmp" }; //for menu button
char gameover[16] = { "wall\\g.bmp" };//gameover page


bool showmenu = true;
bool musicOn = true;





/*
function iDraw() is called again and again by the system.
*/

// reset function is used for reset the value
void reset()
{
	
	SoldierIndex = 0;
	SoldierCordinateX = 0;
	SoldierCordinateY = 0;
	SoldierWidth = 93;
	SoldierHeight = 113;
	standCounter = 0;
	SoldierCordinateJump = 0;

	standPosition = true;
	jump = false;
	jumpUp = false;
	score = 0;
	health = 3;

	showmenu = true;
	musicOn = true;

	


}






//structure for menu buttons
//variables x and y indicates the X and Y co-ordinate position of menu buttons
struct buttonCordinate  
{
	int x;
	int y;
} bCordinate[5];


//structure terroristEntrance for enemy coming
//variables terror_x and terror_y indicates the X and Y co-ordinate position of the terrorist
//terroristShow variable will return true or false value. If true enemies will come on the screen
//Start() function ,has intial values.Whwn it is called enemies are generated

struct terroristEntrance  
{
	int terror_x;
	int terror_y;
	int terroristIndex;
	bool terroristShow;

	void Start()
	{
		terror_x = 1050;
		terror_y = 0;
		terroristShow = true;
	}
};
terroristEntrance enemy[ENEMYSNUMBER];

//enemyMovement() function which is called in iDraw() ,for enemy movement
void enemyMoveMent()
{
	for (int i = 0; i<ENEMYSNUMBER; i++)
	{
		if (enemy[i].terroristShow)
		{
			iShowBMP2(enemy[i].terror_x, enemy[i].terror_y, terroristOne[enemy[i].terroristIndex], 0xffffff);
		}
	}

}
//structure PlaneEntrance for helicopter
//variables plane_x and plane_y indicates the X and Y co-ordinate position of the helicopter
//planeShow variable will return true or false value. If true helicopters will come on the screen
//Start() function ,has intial values.Whwn it is called helicopters are generated
struct PlaneEntrance   
{
	int plane_x;
	int plane_y;
	int planeIndex;
	bool planeShow;

	void Start()
	{
		plane_x = 1020;
		plane_y = 450;
		planeShow = true;
	}
};
PlaneEntrance plane[HELICOPTERNUMBER];


//planemovement() function which is called in iDraw() ,for helicopter movement
void planemoveMent()
{
	for (int i = 0; i<HELICOPTERNUMBER; i++)
	{
		if (plane[i].planeShow)
		{
			iShowBMP2(plane[i].plane_x, plane[i].plane_y = 450, HelicopterOne[plane[i].planeIndex], 0xffffff);
		}
	}

}

//iDraw() function is called again and again by the system
void iDraw()
{
	//place your drawing codes here
	iClear();

	

	if (gameState == -2)  // for startpage pic
	{
		iShowBMP(0, 0, startp);
		iSetColor(255, 0, 0);
		iText(380, 50, "Press Home to continue", GLUT_BITMAP_TIMES_ROMAN_24);
		
	}
	if (showmenu)
	{




		if (gameState == -1)    //for home menu pic
		{
			
			iShowBMP(0, 0, menu);

			for (int i = 0; i < 5; i++)
			{

				iShowBMP(bCordinate[i].x, bCordinate[i].y, button[i]); //for button position
			}
		}

		 if (gameState == 0)  //for gameplay
		{
			
			 
			
			 iShowBMP(0, 0, "wall//background.bmp");
			enemyMoveMent();
			planemoveMent();
			if (jump)
			{
				if (jumpUp)
				{
					iShowBMP2(SoldierCordinateX, SoldierCordinateY + SoldierCordinateJump, SoldierJump[0], 0);
				}
				else
				{

					iShowBMP2(SoldierCordinateX, SoldierCordinateY + SoldierCordinateJump, SoldierJump[1], 0);
				}
			}
			else
			{


				if (!standPosition)
				{
					iShowBMP2(SoldierCordinateX, SoldierCordinateY, Soldier[SoldierIndex], 0);
					standCounter++;
					if (standCounter >= 20)
					{
						standCounter = 0;
						SoldierIndex = 0;
						standPosition = true;
					}
				}
				else
				{
					iShowBMP2(SoldierCordinateX, SoldierCordinateY, SoldierStand, 0);
				}

			}
			for (int j = 0; j < BULLETNUMBER; j++)
			{
				if (b[j].shootBullet)
				{
					iShowBMP2(b[j].BulletX, b[j].BulletY, BulletOne, 0);
				}

			}
			for (int k = 0; k < BOMBNUMBER; k++)
			{
				if (v[k].shootBomb)
				{
					iShowBMP2(v[k].BombX, v[k].BombY, BombOne, 0);
				}

			}

			iText(15, 560, "SCORE:", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(100, 560, _itoa(score,scoreArray,10), GLUT_BITMAP_TIMES_ROMAN_24);
			
			iSetColor(255, 0, 0);
			iText(800, 560, "HEALTH:", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(920, 560, _itoa(health,HealthArray,10), GLUT_BITMAP_TIMES_ROMAN_24);
			iShowBMP2(940, 556, "wall//life.bmp", 0);



			iShowBMP2(141, 305, "wall//fire.bmp", 0);
			iShowBMP2(210, 260, "wall//fire.bmp", 0);
			iShowBMP2(330, 265, "wall//fire.bmp", 0);
			iShowBMP2(400, 190, "wall//fire.bmp", 0);
			iShowBMP2(680, 386, "wall//fire.bmp", 0);
			iShowBMP2(680, 250, "wall//fire.bmp", 0);
			iShowBMP2(755, 260, "wall//fire.bmp", 0);
			iShowBMP2(830, 250, "wall//fire.bmp", 0);
			iShowBMP2(895, 210, "wall//fire.bmp", 0);
			iShowBMP2(940, 170, "wall//fire.bmp", 0);

			


		}
		else if (gameState == 1) //for instruction page
		{
			iShowBMP(0, 0, ins);
		}
		else if (gameState == 2) //for highscore page and highscore
			
		{
			
			iShowBMP(0, 0, highscoreOne);
			iSetColor(rand() % 255, rand() % 255, rand() % 255);
			iText(430, 500, "HIGHSCORE", GLUT_BITMAP_TIMES_ROMAN_24);

			fpp = fopen("highscore.txt", "r");
			int highScorearray[1000];
			for (int i = 0; i < 1000; i++)
			{
				highScorearray[i] = -1;

			}
			for (int i = 0; fscanf(fpp, "%d", &highScorearray[i]) != EOF; i++)
			{

			}
			int temp = 0;
			for (int i = 0; i < 1000; i++)
			{
				for (int j = i; j < 1000; j++)
				{

					if (highScorearray[i] < highScorearray[j])
					{
						temp = highScorearray[i];
						highScorearray[i] = highScorearray[j];
						highScorearray[j] = temp;
					}
				}
			}
			fclose(fpp);
			fpp = fopen("highscore.txt", "w");
			for (int i = 0; i < 10; i++)
			{
				fprintf(fpp, "%d\n", highScorearray[i]);
			}
			fclose(fpp);

			fpp = fopen("highscore.txt", "r");
			int highscore[3];
			fscanf(fpp, "%d%d%d", &highscore[0], &highscore[1], &highscore[2]);
			
			iSetColor(255, 0, 0);
			_itoa(highscore[0], scoreStr, 10);
			iText(500, 400, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(470, 400, "1.", GLUT_BITMAP_TIMES_ROMAN_24);

			_itoa(highscore[1], scoreStr, 10);
			iText(500, 300, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(470, 300, "2.", GLUT_BITMAP_TIMES_ROMAN_24);

			_itoa(highscore[2], scoreStr, 10);
			iText(500, 200, scoreStr, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(470, 200, "3.", GLUT_BITMAP_TIMES_ROMAN_24);

			fclose(fpp);



		}
		else if (gameState == 3) //for credit page
		{
			iShowBMP(0, 0, credit);

		}
		else if (gameState == 4)
		{

			exit(0);
		}
		else if (gameState == 5)
		{
			iShowBMP(0, 0, gameover);
			
			iText(400, 200, "YOUR SCORE IS :  ", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(600, 200,scoreArray, GLUT_BITMAP_TIMES_ROMAN_24);
		
			static int file = 0;
			if (file == 0)
			{
				fpp = fopen("highscore.txt", "a");
				fprintf(fpp, "%d\n", score);
				fclose(fpp);
				file++;
			}
			

		}


	}


	









	//for sava and load game
	
	if (save == 1 && gameState == 0)
	{
		//write part
		FILE *fp = fopen("Save&Load.txt", "w");

		fprintf(fp, "%d\n", SoldierIndex);
		fprintf(fp, "%d\n", SoldierCordinateX);
		fprintf(fp, "%d\n", SoldierCordinateY);
		fprintf(fp, "%d\n", SoldierCordinateJump);
		fprintf(fp, "%d\n", standCounter);

		fprintf(fp, "%d\n", score);
		fprintf(fp, "%d\n", health);

		for (int j = 0; j < BULLETNUMBER; j++)
		{

			fprintf(fp, "%d\n", b[j].BulletX);

			fprintf(fp, "%d\n", b[j].BulletY);
		}
		for (int k = 0; k < BOMBNUMBER; k++)
		{

			fprintf(fp, "%d\n", v[k].BombX);
			fprintf(fp, "%d\n", v[k].BombY);
		}
		

		for (int i = 0; i < ENEMYSNUMBER; i++)
		{
			fprintf(fp, "%d\n", enemy[i].terror_x);
			fprintf(fp, "%d\n", enemy[i].terror_y);
			fprintf(fp, "%d\n", enemy[i].terroristIndex);
		}

		for (int i = 0; i < HELICOPTERNUMBER; i++)
		{

			fprintf(fp, "%d\n", plane[i].plane_x);
			fprintf(fp, "%d\n", plane[i].plane_y);
			fprintf(fp, "%d\n", plane[i].planeShow);
		}

		fclose(fp);
		save = 3;
		
	}


	if (save == 2 && gameState == -1)
	{
		gameState = 0;
		//read part(load game)
		
		FILE *fp = fopen("Save&Load.txt", "r");

		fscanf(fp, "%d", &SoldierIndex);
		fscanf(fp, "%d", &SoldierCordinateX);
		fscanf(fp, "%d", &SoldierCordinateY);
		fscanf(fp, "%d", &SoldierCordinateJump);
		fscanf(fp, "%d", &standCounter);


		fscanf(fp, "%d", &score);
		fscanf(fp, "%d", &health);

		for (int j = 0; j < BULLETNUMBER; j++)
		{

			fscanf(fp, "%d", &b[j].BulletX);

			fscanf(fp, "%d", &b[j].BulletY);
		}
		for (int k = 0; k < BOMBNUMBER; k++)
		{

			fscanf(fp, "%d", &v[k].BombX);
			fscanf(fp, "%d", &v[k].BombY);
		}

		for (int i = 0; i < ENEMYSNUMBER; i++)
		{
			fscanf(fp, "%d", &enemy[i].terror_x);
			fscanf(fp, "%d", &enemy[i].terror_y);
			fscanf(fp, "%d", &enemy[i].terroristIndex);
		}

		for (int i = 0; i < HELICOPTERNUMBER; i++)
		{


			fscanf(fp, "%d", &plane[i].plane_x);
			fscanf(fp, "%d", &plane[i].plane_y);
			fscanf(fp, "%d", &plane[i].planeShow);
		}

		fclose(fp);
		save = 4;
		


	}





}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/


//iMouse() , used for buttons.By clicking the menu buttons you can go to the desired page
void iMouse(int button, int state, int mx, int my)
{


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (gameState == -1)
		{
			for (int i = 0; i < 5; i++)
			{
				if (mx >= bCordinate[i].x && mx <= bCordinate[i].x + 240 && my >= bCordinate[i].y && my <= bCordinate[i].y + 70)
				{

					
						
					gameState = i;
					if (i==0)
					{
						if (musicOn)
						{
							musicOn = false;
							PlaySound(0, 0, 0);
						}

					}
					else if (i == 1) PlaySound("Dragon Age.wav", NULL, SND_LOOP | SND_ASYNC);
					else if (i == 2) PlaySound("Dragon Age.wav", NULL, SND_LOOP | SND_ASYNC);
					else if (i == 3) PlaySound("Dragon Age.wav", NULL, SND_LOOP | SND_ASYNC);


				}
			}
		}
	}






}
/*iPassiveMouseMove is called to detect and use
the mouse point without pressing any button */

void iPassiveMouseMove(int mx, int my)
{
	//place your code here

	mposx = mx;
	mposy = my;
	if (mx == 2) {}       /*Something to do with mx*/
	else if (my == 2) {}  /*Something to do with my*/

}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


//By pressing space key the character will jump
//By pressing b or B the character will shoot a bullet
//By pressing n the gamestate will return to main menu
void iKeyboard(unsigned char key)
{
	
	if (key == 's' &&  gameState == 0)
	{

		save = 1;
		
	}


	
	if (key == 'l' && gameState == -1)
	{
		save = 2;
	
		//printf("l pressed");


	}

	
	if (gameState == -1)
	{
		if (key == 'n')
		{
			exit(0);
		}
	}
	if (gameState == 1)
	{
		if (key == 'n'|| key =='N')
		{
			gameState = -1;
			//iShowBMP(0, 0, homemenu);
		}
	}
	if (gameState == 2)
	{
		if (key == 'n')
		{
			gameState = -1;
			//iShowBMP(0, 0, homemenu);
		}
	}
	if (gameState == 3)
	{
		if (key == 'n')
		{
			gameState = -1;
			//iShowBMP(0, 0, homemenu);
		}
	}
	if (gameState == 5)
	{
		if (key == 'n')
		{
			gameState = -1;
			reset();
			//iShowBMP(0,0,homemenu);
		}
	}
	if (gameState == 0)
	{	

		if (key == 'n') // for back button
		{
			gameState = -1;
			reset();
			PlaySound("Dragon Age.wav", NULL, SND_LOOP | SND_ASYNC);

		}

		if (key == ' ')
		{
			if (!jump)
			{
				jump = true;
				jumpUp = true;

			}
		}

		if (key == 'b' || key == 'B') // used for bullet
		{
			if (jump == false)
			{
				PlaySound("Bullet.wav ", NULL, SND_ASYNC);
				b[BulletIndex].BulletX = SoldierCordinateX + 90;
				b[BulletIndex].BulletY = SoldierCordinateY + 70;
				b[BulletIndex].shootBullet = true;

				BulletIndex++;
				
				if (BulletIndex > BULLETNUMBER)
				{

					BulletIndex = 0;

				}


			}
		}
		if (key == 'v' || key == 'V') //used for blast
		{
			if (jump == false)
			{
				PlaySound("Blast.wav", NULL, SND_ASYNC);
				v[BombIndex].BombX = SoldierCordinateX + 90;
				v[BombIndex].BombY = SoldierCordinateY + 70;
				v[BombIndex].shootBomb = true;

				BombIndex++;

				if (BombIndex>BOMBNUMBER)
				{
					BombIndex = 0;
				}
			}
		}
	}
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/


//By pressing Left key the character will move to backward
//By pressing Right key the character will move forward
void iSpecialKeyboard(unsigned char key)
{
	if(key==GLUT_KEY_UP)
	{

		
	}
	
	if (gameState == 0)
	{

		if (key == GLUT_KEY_LEFT)
		{
			SoldierCordinateX -= 10;
			SoldierIndex++;
			if (SoldierIndex >= 6)
			{
				SoldierIndex = 0;

			}
			if (SoldierCordinateX <= 0)
			{
				SoldierCordinateX = 0;
			}
		}
		else if (key == GLUT_KEY_RIGHT)
		{
			SoldierCordinateX += 10;
			SoldierIndex++;
			if (SoldierIndex >= 6)
				 SoldierIndex = 0;
			

			standPosition = false;
			if (SoldierCordinateX + SoldierWidth >= SCREENWIDTH)
			{
				SoldierCordinateX = SCREENWIDTH - SoldierWidth;
				SoldierCordinateX = 0;
			}
		}
	}
	if (gameState == -1)

	{

		if (key == GLUT_KEY_HOME)
		{
			gameState = -1;
			iShowBMP(0, 0, menu);
		}

	}

	if (gameState == -2)
	{

		if (key == GLUT_KEY_HOME)
		{
			gameState = -1;
			iShowBMP(0, 0, menu);
		}
		if (key == GLUT_KEY_END)
		{
			gameState = -1;
			exit(0);
		}

	}




}

//void change() function to make the character jump
void change()
{
	if (gameState == 0)
	{

		if (jump)
		{
			if (jumpUp)
			{
				SoldierCordinateJump += 5;
				if (SoldierCordinateJump >= JUMPLIMIT)
				{
					jumpUp = false;
				}
			}
			else
			{
				SoldierCordinateJump -= 5;
				if (SoldierCordinateJump < 0)
				{
					jump = false;
					SoldierCordinateJump = 0;
				}
			}
		}
	}
}

void changeEnemy()
{
	if (gameState == 0)
	{

		for (int i = 0; i < ENEMYSNUMBER; i++)
		{
			enemy[i].terror_x -= 12;
			if (enemy[i].terror_x <= 0)
			{

				enemy[i].terror_x = rand() % 1700;
			}
			enemy[i].terroristIndex++;
			if (enemy[i].terroristIndex >= 12)
			{
				enemy[i].terroristIndex = 0;
			}
			/*************************terrorist and bullet collision ,score inceasing part for shooting terrorists*********************************/
			for (int j = 0; j<BULLETNUMBER; j++)
			{
				if (b[j].BulletY > enemy[i].terror_y && b[j].BulletY < enemy[i].terror_y + 100 && b[j].BulletX > enemy[i].terror_x && b[j].BulletX < enemy[i].terror_x + 100 && b[j].shootBullet == true)
				{
					enemy[i].terroristShow = false;
					b[j].shootBullet = false;
					score=score+1;
					
					enemy[i].Start();
					b[j].BulletX = SoldierCordinateX + 90;
					b[j].BulletY = SoldierCordinateY + 70;
				
				}
			}
			/***********************Soldier and Terrorist collision ,player(soldier) health decreasing part************************/
			if (SoldierCordinateX <= enemy[i].terror_x && SoldierCordinateX + 100 >= enemy[i].terror_x && enemy[i].terroristShow)//heroCordinateY > enimy[i].enimy_y && heroCordinateY < enimy[i].enimy_y +100  && heroCordinateX > enimy[i].enimy_x && heroCordinateX < enimy[i].enimy_x +100 && shootBullet == true)
			{
				health = health--;
			
				enemy[i].Start();
				if (health == 0)
				{
					gameState = 5;
				}

			}
		}

	}
}

//changePlane() function for helicopter movement
void changePlane()
{
	if (gameState == 0)
	{


		for (int i = 0; i < HELICOPTERNUMBER; i++)
		{
			plane[i].plane_x -= 4;
			if (plane[i].plane_x <= 0)
			{

				plane[i].plane_x = rand() % 1500;
				plane[i].plane_y = rand() % 300;
			}
			plane[i].planeIndex++;
			if (plane[i].planeIndex >= 4)
			{
				plane[i].planeIndex = 0;
			}
			/*********************helicopter and bomb collision , score increasing part for shooting helicopters**************************/
			for (int k = 0; k<BOMBNUMBER; k++)
			{
				if (v[k].BombY> plane[i].plane_y && v[k].BombY < plane[i].plane_y + 100 && v[k].BombX > plane[i].plane_x && v[k].BombX < plane[i].plane_x + 100 && v[k].shootBomb == true)
				{
					plane[i].planeShow = false;
					v[k].shootBomb = false;
					score = score + 5;
					
					plane[i].Start();
					v[k].BombX = SoldierCordinateX + 90;
					v[k].BombY = SoldierCordinateY + 63;
				}
			}
		}
	}
}

//setEnemyVariable() function defines from where the enemies will come,enemies are generated automatically by this function
//rand() function to generate random number of enemies

void setEnemyVariable()
{
	for (int i = 0; i<ENEMYSNUMBER; i++)
	{
		enemy[i].terror_x = 1500 + rand() % 1200;
		enemy[i].terroristIndex = rand() % 12;
		enemy[i].terroristShow = true;
	}

}

//setPlaneVariable() function defines from where the helicopters will come, helicopters are generated automatically by this function
//rand() function to generate random number of helicopters
void setPlaneVariable()
{
	for (int i = 0; i<HELICOPTERNUMBER; i++)
	{
		plane[i].plane_x = 1500 + rand() % 1500;
		plane[i].plane_y = 400 + rand() % 300;
		plane[i].planeIndex = rand() % 4;
		plane[i].planeShow = true;
	}

}


	



//main function
//call setBackground(),setEnemyVariable() and setPlaneVariable()
int main()
{
	//place your own initialization codes here.
	int sum = 20;
	for (int i = 4; i >= 0; i--)
	{
		bCordinate[i].x = 100;
		bCordinate[i].y = sum;
		sum += 120;

	}
	
	setEnemyVariable();
	setPlaneVariable();
	iSetTimer(25, change);//timer for jump
	iSetTimer(100, goBullet);//timer for bullet movement
	iSetTimer(100, goBomb);//timer for bomb(for shooting plane) movement
	iSetTimer(150, changeEnemy);//timer for enemy controls
	iSetTimer(80, changePlane);//timer for plane controls
	if (musicOn)
	{

		PlaySound("Dragon Age.wav", NULL,SND_LOOP | SND_ASYNC);
	}
	iInitialize(SCREENWIDTH, SCREENHEIGHT, "Counter Strike");
	return 0;
}
