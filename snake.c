#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include "function.h"
int score,v,dif,hscore,boolhscore = 0;

int main()
{
	choose(&dif,&v);
	initial();
	highest(&hscore);
	int *px1, *px2, *py1, *py2;
	px1 = (int*)malloc(sizeof(int));
	px2 = (int*)malloc(sizeof(int));
	py1 = (int*)malloc(sizeof(int));
	py2 = (int*)malloc(sizeof(int));
	*px2 = 21 + (COLS-mainscr_col)/4*2;
	*py2 = 14 + (LINES-mainscr_line)/2;
	random_x(px1,px2);
	random_y(py1,py2);
	struct snack* pHead;
	struct snack* pLast;
	pLast = &Snack;
	pHead = creat(pLast,4);
	int key, checkNum, direction = 'd';
	
	while(direction != 113)
	{	
		if(checkNum != 1)
			walk(pLast, direction);
		addfood(*py1,*px1);
		addScore(dif,score,&hscore,&boolhscore);
		refresh();
		usleep(v);
		key = getch();
		switch(key)
		{
			case KEY_UP:
				if(direction != 'w' && direction !='s')
					direction = 'w';
				break;
			case KEY_DOWN:
				if(direction != 's' && direction !='w')
					direction = 's';
				break;
			case KEY_RIGHT:
				if(direction != 'd' && direction !='a')
					direction = 'd';
				break;
			case KEY_LEFT:
				if(direction != 'a' && direction !='d')
					direction = 'a';
				break;
			case 'w':
				if(direction != 'w' && direction !='s')
					direction = 'w';
				break;
			case 's':
				if(direction != 's' && direction !='w')
					direction = 's';
				break;
			case 'd':
				if(direction != 'd' && direction !='a')
					direction = 'd';
				break;
			case 'a':
				if(direction != 'a' && direction !='d')
					direction = 'a';
				break;
			case 113:
				direction = 113; break;
			case 'p':
				timeout(-1);
				move(LINES/2,COLS/2-12);
				addstr("PAUSE! Enter <p> to continue!");
				refresh();
				while(getch() != 'p');
				timeout(0);
			default:
				break;
		}
		checkNum = check(pLast,pHead,*py1,*px1,direction);
		if(checkNum == 1)
		{
			score ++;
			pHead = add(pHead,*py1,*px1);
			random_x(px1,px2);
			random_y(py1,py2);
		}
		else if(checkNum == 0 || checkNum == 2)
		{
			break;
		}
	}
	gameover(dif,&score,hscore,boolhscore);
	endwin();
	return 0;
}
