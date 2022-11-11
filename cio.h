/*********************
   cio.c�� �������̽� 
**********************/

#ifndef __CIO_H__
#define __CIO_H__

/*�Լ� extern ����*/
extern void gotoxy(int, int); 

extern int get_key(void); 

extern void print_map(void);

extern void intro(void); 
extern void outro(void); 

void enemy_initialize(void);

extern void turn_player(void); 
extern void turn_enemy(void);

extern void player_display(void);
extern void enemy_display(void);

extern void player_enemy_crash(void);
extern void crash_effect(int);
extern void skill_effect(int);

extern void stage(void);

#endif