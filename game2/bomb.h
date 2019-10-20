#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED

//structure for bomb
//BombX and BombY are the X and Y co-ordinate of the bomb position
typedef struct Bomb Bomb;
struct Bomb{
	int BombX = 0;
	int BombY = 0;
	bool shootBomb = false;


};
Bomb v[20];
int BombIndex = 0;
int BOMBNUMBER = 10;

//goBomb() function controls the bomb movement
void goBomb()
{
	
	

		for (int k = 0; k<BOMBNUMBER; k++)
		{

			if (v[k].shootBomb)
			{
				v[k].BombY += 10;
				v[k].BombX += 7;

			}

			if (v[k].BombY>600) v[k].shootBomb = false;

		}
	
}
#endif
