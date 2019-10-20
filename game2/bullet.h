#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

//structure for bullet
//BulletX and BulletY are the X and Y co=ordinate of the bullet position
typedef struct Bullet Bullet;
struct Bullet{
	int BulletX = 0;
	int BulletY = 0;
	bool shootBullet = false;


};
Bullet b[20];
int BulletIndex = 0;
int BULLETNUMBER = 10;

//goBullet() function controls the bullet movement
void goBullet()
{
	

		for (int j = 0; j < BULLETNUMBER; j++)
		{

			if (b[j].shootBullet)b[j].BulletX += 30;

			if (b[j].BulletX >= 1000)b[j].shootBullet = false;

		}
	
}
#endif