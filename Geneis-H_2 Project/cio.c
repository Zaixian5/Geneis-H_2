/********************************************
   콘솔 입출력 관련 함수들이 모여있는 소스파일 
*********************************************/

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

/*전역변수*/
char board[FIELD_HEIGHT][FIELD_WIDTH + 1] = {

	"########################################",
	"#@                                     #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                     $#",
	"########################################"
};
RAND_WALL rd_wall = { { 0 }, { 0 } }; // 랜덤 벽의 좌표를 저장
PLAYER_INFO player = { UP_CORNER, LEFT_CORNER, { 0 }, { 0 }, { 0 } }; // 플레이어 좌표와 스킬, 폭탄 좌표를 저장
ENEMY_INFO enemy = { { 0 }, { 0 }, 0, 0, 0 }; // 적 좌표, 리젠 좌표, 처치된 적의 수를 저장
int stage_num = 1; // 스테이지 번호를 저장
int save_score = 1; // 점수를 저장

void gotoxy(int row, int column) // 좌표를 이동하는 함수. 가로좌표와 세로좌표가 반대로 되어있다.
{
	COORD pos = { column, row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int get_key(void) // 키 입력을 처리하는 함수
{
	while (true)
	{
		if (_kbhit())
		{
			return _getch(); // 키 입력이 있을 경우 입력 값을 반환
		}
		else
		{
			return K_NONE; // 키 입력이 없을 경우 0을 반환
		}
	}
}
void print_map(void)
{
	int i;

	for (i = 0; i < FIELD_HEIGHT; i++) // 맵의 바깥쪽 벽과 초기 플레이어, 초기 적의 위치를 출력
	{
		printf("%s\n", board[i]);
	}

	srand((unsigned int)time(NULL));

	for (i = 0; i < RAND_WALL_CNT; i++) // 랜덤 벽의 좌표를 생성하여 저장
	{
		rd_wall.row[i] = (rand() % DOWN_CORNER) + UP_CORNER; // 1 ~ 18 사이의 난수를 세로 좌표에 저장
		rd_wall.column[i] = (rand() % RIGHT_CORNER) + LEFT_CORNER; // 1 ~ 38 사이의 난수를 가로 좌표에 저장

		if ((rd_wall.row[i] == UP_CORNER) && (rd_wall.column[i] == LEFT_CORNER)) // 좌상단 좌표에는 벽을 생성하지 못하게 함
		{
			i--; // continue를 해도 벽의 개수는 유지되어야 하므로 i를 1 감소
			continue;
		}
		if ((rd_wall.row[i] == DOWN_CORNER) && (rd_wall.column[i] == RIGHT_CORNER)) // 우하단 좌표에는 벽을 생성하지 못하게 함
		{
			i--; // continue를 해도 벽의 개수는 유지되어야 하므로 i를 1 감소
			continue;
		}
	}

	for (i = 0; i < RAND_WALL_CNT; i++) // 랜덤 벽을 출력
	{
		gotoxy(rd_wall.row[i], rd_wall.column[i]);
		printf("%c", MAP_WALL);
	}

	// 게임 정보 출력
	gotoxy(0, 42);
	printf("<게임방법>");

	gotoxy(2, 43);
	printf("@: 플레이어 $: 적");

	gotoxy(4, 42);
	printf(" - 플레이어는 방향키로 움직일 수 있습니다.");
	
	gotoxy(6, 42);
	printf(" - 플레이어와 적이 부딪히거나 적이 스킬에 맞으면 점수가 오르고");

	gotoxy(7, 42);
	printf("   적이 다른 위치에 다시 생성됩니다.");

	gotoxy(9, 42);
	printf(" - 플레이어는 z, x키로 스킬을 사용할 수 있습니다.");

	gotoxy(10, 42);
	printf("   -> z: 수평 스킬, x: 수직 스킬");

	gotoxy(12, 42);
	printf(" - 점수가 10씩 오를 때 마다 스테이지가 올라갑니다.");

	gotoxy(14, 42);
	printf(" - 스테이지가 오를 수록 적의 수가 많아지며 최대 스테이지는 20입니다.");

	gotoxy(16, 42);
	printf(" - 점수가 10의 배수가 될 때 마다 폭탄이 터집니다.");

	gotoxy(17, 42);
	printf("   -> 폭탄: 맵에 존재하는 모든 적을 처치한다.");

	gotoxy(19, 42);
	printf(" - 경과 시간이 10초가 될 때 마다 서비스 점수 10점이 부여됩니다.");

	gotoxy(21, 43);
	printf("q: 게임종료");

	gotoxy(21, 0);
	printf("점수: %d", save_score); // 초기 점수 출력

	gotoxy(21, 12);
	printf("스테이지: %d", stage_num); // 초기 스테이지 출력

	gotoxy(21, 28);
	printf("시간(초): ");
}
void intro(void)
{
	printf("Welcome!\n");
	printf("아무키나 누르세요");
	while (true)
	{
		if (_kbhit())
		{
			system("cls");
			break;
		}
	}
}
void outro(int tick)
{
	system("cls");
	printf("<STATISTICS>\n");
	printf("점수: %d\n", save_score);
	printf("처치한 적: %d\n", enemy.captured);
	printf("최종 스테이지 : %d\n", stage_num);
	printf("게임 시간(초) : %d\n\n", tick / 100);
	printf("Bye!\n");
}
void initialize(void) 
{
	int enemy_num;
	int bomb_row, bomb_column;
	int i;

	// 적 좌표를 모두 시작 위치로 초기화
	for (enemy_num = 1; enemy_num < STAGE + 1; enemy_num++)
	{
		enemy.row[enemy_num] = DOWN_CORNER;
		enemy.column[enemy_num] = RIGHT_CORNER;
	}

	// 폭탄 효과 좌표를 랜덤 벽을 피해서 초기화
	for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
	{
		for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
		{
			player.bomb_effect[bomb_row][bomb_column] = TRUE; // 먼저, 배열 전체를 TRUE로 초기화 한다.
		}
	}
	for (i = 0; i < RAND_WALL_CNT; i++)
	{
		player.bomb_effect[rd_wall.row[i]][rd_wall.column[i]] = FALSE; // 다음으로, 좌표가 랜덤 벽과 일치 하는 경우 FALSE를 저장한다.
	}
}
void stage(void) // 스테이지 정보 함수
{	
	if (save_score % 10 == 0) // 점수가 10씩 증가할 떄 마다 스테이지가 올라감
	{
		if (stage_num < STAGE) 
		{
			stage_num++;

			gotoxy(21, 22);
			printf("%d", stage_num);
		}
	}
}
void turn_player(void) // 키 입력이 있을 시 플레이어의 좌표를 변경하는 함수.
{
	int arrow = _getch(); // 방향키 아스키코드 두번째 반환 값을 저장
	int i;

	gotoxy(player.row, player.column); // 이전 플레이어의 위치를 지움
	printf("%c", MAP_EMPTY);

	switch (arrow)
	{
	case K_LEFT: // 왼쪽 방향키 입력시
		player.column += DIR_LEFT; // 플레이어의 좌표를 왼쪽으로 1 이동
		if (player.column < LEFT_CORNER) // 플레이어의 위치가 왼쪽 벽을 뚫지 못하게 하기 위함
		{
			player.column = LEFT_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // 플레이어의 위치가 랜덤 벽을 침범하지 못하게 함
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.column = rd_wall.column[i] + DIR_RIGHT;
			}
		}
		break;

	case K_RIGHT: // 오른쪽 방향키 입력시
		player.column += DIR_RIGHT; // 플레이어의 좌표를 오른쪽으로 1 이동
		if (player.column > RIGHT_CORNER) // 플레이어의 위치가 오른쪽 벽을 뚫지 못하게 하기 위함
		{
			player.column = RIGHT_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // 플레이어의 위치가 랜덤 벽을 침범하지 못하게 함
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.column = rd_wall.column[i] + DIR_LEFT;
			}
		}
		break;

	case K_UP: // 위쪽 방향키 입력시
		player.row += DIR_UP; // 플레이어의 좌표를 위쪽으로 1 이동
		if (player.row < UP_CORNER) // 적의 위치가 위쪽 벽을 뚫지 못하게 하기 위함
		{
			player.row = UP_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // 플레이어의 위치가 랜덤 벽을 침범하지 못하게 함
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.row = rd_wall.row[i] + DIR_DOWN;
			}
		}
		break;

	case K_DOWN: // 아래쪽 방향키 입력시
		player.row += DIR_DOWN; // 플레이어의 좌표를 아래쪽으로 1 이동
		if (player.row > DOWN_CORNER) // 적의 위치가 아래쪽 벽을 뚫지 못하게 하기 위함
		{
			player.row = DOWN_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // 플레이어의 위치가 랜덤 벽을 침범하지 못하게 함
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.row = rd_wall.row[i] + DIR_UP;
			}
		}
		break;
	}
}
void turn_enemy(void) // 적의 위치가 랜덤으로 상하좌우 중 한 방향으로 한칸 움직이도록 함
{	
	int i;
	int enemy_num;
	int rand_dir = 0;

	srand((unsigned int)time(NULL));

	for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
	{
		gotoxy(enemy.row[enemy_num], enemy.column[enemy_num]); // 이전 적의 위치를 지움
		printf("%c", MAP_EMPTY);

		rand_dir = (rand() % 4); // 0 ~ 3 사이의 난수를 저장
		
		switch (rand_dir) // 0 ~ 3 중 어떤 수가 어느 방향을 의미하는 지는 임의로 정하였음
		{
		case 0: // 0이 나오면 적의 좌표를 위쪽로 한칸 이동
			enemy.row[enemy_num] += DIR_UP;
			if (enemy.row[enemy_num] < UP_CORNER) // 적의 위치가 위쪽 벽을 뚫지 못하게 하기 위함
			{
				enemy.row[enemy_num] = UP_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // 적의 위치가 랜덤 벽을 침범하지 못하게 함
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.row[enemy_num] = rd_wall.row[i] + DIR_DOWN;
				}
			}
			break;

		case 1: // 1이 나오면 적의 좌표를 아래쪽으로 한칸 이동
			enemy.row[enemy_num] += DIR_DOWN;
			if (enemy.row[enemy_num] > DOWN_CORNER) // 적의 위치가 아래쪽 벽을 뚫지 못하게 하기 위함
			{
				enemy.row[enemy_num] = DOWN_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // 적의 위치가 랜덤 벽을 침범하지 못하게 함
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.row[enemy_num] = rd_wall.row[i] + DIR_UP;
				}
			}
			break;

		case 2: // 2가 나오면 적의 좌표를 오른쪽으로 한칸 이동
			enemy.column[enemy_num] += DIR_RIGHT;
			if (enemy.column[enemy_num] > RIGHT_CORNER) // 적의 위치가 오른쪽 벽을 뚫지 못하게 하기 위함
			{
				enemy.column[enemy_num] = RIGHT_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // 적의 위치가 랜덤 벽을 침범하지 못하게 함
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.column[enemy_num] = rd_wall.column[i] + DIR_LEFT;
				}
			}
			break;

		case 3: // 3이 나오면 적의 좌표를 왼쪽으로 한칸 이동
			enemy.column[enemy_num] += DIR_LEFT;
			if (enemy.column[enemy_num] < LEFT_CORNER) // 적의 위치가 왼쪽 벽을 뚫지 못하게 하기 위함
			{
				enemy.column[enemy_num] = LEFT_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // 적의 위치가 랜덤 벽을 침범하지 못하게 함
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.column[enemy_num] = rd_wall.column[i] + DIR_RIGHT;
				}
			}
			break;
		}
	}
}
void crash_effect(int enemy_num)
{
	int i;
	int duplicated = 0;

	enemy.captured++; // 처치된 적의 수 1 증가
	save_score++; // 점수를 1 늘리고 출력

	gotoxy(21, 6);
	printf("%d", save_score);

	stage(); // 스테이지를 출력

	while (TRUE)
	{
		duplicated = 0;

		enemy.regen_row = (rand() % DOWN_CORNER) + UP_CORNER; // 1 ~ 18 사이의 난수 하나를 생성해 리젠 세로 좌표에 저장
		enemy.regen_column = (rand() % RIGHT_CORNER) + LEFT_CORNER; // 1 ~ 38 사이의 난수 하나를 생성해 리젠 가로 좌표에 저장

		for (i = 0; i < RAND_WALL_CNT; i++)
		{
			if ((enemy.regen_row == rd_wall.row[i]) && (enemy.regen_column == rd_wall.column[i]))
			{
				duplicated++; // 랜덤 벽 좌표와 리젠 좌표가 중복시 카운트
			}
		}
		if (duplicated == 0)
		{
			break; // 랜덤 벽 좌표와 리젠 좌표가 중복되지 않았다면 while문 탈출
		}
	}

	// 해당 적의 좌표를 리젠 좌표로 변경
	enemy.row[enemy_num] = enemy.regen_row;
	enemy.column[enemy_num] = enemy.regen_column;
}
void player_enemy_crash(void)
{
	int enemy_num;

	for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
	{
		if ((player.row == enemy.row[enemy_num]) && (player.column == enemy.column[enemy_num]))
		{
			crash_effect(enemy_num); // 플레이어와 적이 부딪히면 충돌 이펙트 함수 호출
		}
	}
}
void skill_effect(int skill_key)
{
	// z: 수평 방향 일직선으로 !를 발사
	// x: 수직 방향 일직선으로 !를 발사
	
	int coordinates;
	int enemy_num;
	int i;

	// 스킬 구조체 배열을 모두 TRUE로 초기화
	for (coordinates = LEFT_CORNER; coordinates <= RIGHT_CORNER; coordinates++)
	{
		player.horizontal_skill_column[coordinates] = TRUE;
	}
	for (coordinates = UP_CORNER; coordinates <= DOWN_CORNER; coordinates++)
	{
		player.vertical_skill_row[coordinates] = TRUE;
	}

	switch (skill_key)
	{
	case SKILL_KEY_HORIZONTAL: // z키 입력시
		for (coordinates = LEFT_CORNER; coordinates <= RIGHT_CORNER; coordinates++)
		{
			for (i = 0; i < RAND_WALL_CNT; i++)
			{
				if ((rd_wall.row[i] == player.row) && (rd_wall.column[i] == coordinates))
				{
					player.horizontal_skill_column[coordinates] = FALSE; // 좌표가 랜덤 벽과 일치 시 FALSE를 저장 
				}
			}
			if (player.horizontal_skill_column[coordinates]) // TRUE일 경우 좌표로 이동해 스킬 출력
			{
				gotoxy(player.row, coordinates);
				printf("%c", SKILL_EFFECT);

				for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
				{
					if ((enemy.row[enemy_num] == player.row) && (enemy.column[enemy_num] == coordinates))
					{
						crash_effect(enemy_num); // 적이 스킬에 맞는다면 충돌 이펙트 함수 호출
					}
				}
			}
		}
		Sleep(500); // 게임을 0.5초간 일시정지 후 스킬을 지운다

		for (coordinates = LEFT_CORNER; coordinates <= RIGHT_CORNER; coordinates++)
		{
			if (player.horizontal_skill_column[coordinates])
			{
				gotoxy(player.row, coordinates);
				printf("%c", MAP_EMPTY);
			}
		}
		break;
    
	case SKILL_KEY_VERTICAL: // x키 입력시
		for (coordinates = UP_CORNER; coordinates <= DOWN_CORNER; coordinates++)
		{
			for (i = 0; i < RAND_WALL_CNT; i++)
			{
				if ((rd_wall.row[i] == coordinates) && (rd_wall.column[i] == player.column))
				{
					player.vertical_skill_row[coordinates] = FALSE; // 좌표가 랜덤 벽과 일치 시 FALSE를 저장 
				}
			}
			if (player.vertical_skill_row[coordinates]) // TRUE일 경우 좌표로 이동해 스킬 출력
			{
				gotoxy(coordinates, player.column);
				printf("%c", SKILL_EFFECT);

				for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
				{
					if ((enemy.row[enemy_num] == coordinates) && (enemy.column[enemy_num] == player.column))
					{
						crash_effect(enemy_num); // 적이 스킬에 맞는다면 충돌 이펙트 함수 호출
					}
				}
			}
		}
		Sleep(500); // 게임을 0.5초간 일시정지 후 스킬을 지운다

		for (coordinates = UP_CORNER; coordinates <= DOWN_CORNER; coordinates++)
		{
			if (player.vertical_skill_row[coordinates])
			{
				gotoxy(coordinates, player.column);
				printf("%c", MAP_EMPTY);
			}
		}
		break;
	}
}
void bomb_effect(void)
{
	int bomb_row, bomb_column; 
	int enemy_num;
	int i;
	
	if (save_score % 10 == 0) // 점수가 10의 배수가 될 때 마다 폭탄 작동
	{
		gotoxy(23, 0);
		printf("폭탄!"); // 메세지 출력

		for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
		{
			for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
			{
				if (player.bomb_effect[bomb_row][bomb_column]) // TRUE일 경우 좌표로 이동해 폭탄 출력
				{
					gotoxy(bomb_row, bomb_column);
					printf("%c", MAP_BOMB); 

					for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
					{
						if ((enemy.row[enemy_num] == bomb_row) && (enemy.column[enemy_num] == bomb_column))
						{
							crash_effect(enemy_num); // 적이 폭탄에 맞는다면 충돌 이펙트 함수 호출
						}
					}
				}
			}
		}
		Sleep(500); // 게임을 0.5초간 일시정지 후 폭탄과 메세지를 지운다

		gotoxy(23, 0);
		for (i = 0; i < 5; i++)
		{
			printf("%c", MAP_EMPTY); // 메세지 지우기
		}

		for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
		{
			for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
			{
				if (player.bomb_effect[bomb_row][bomb_column])
				{
					gotoxy(bomb_row, bomb_column);
					printf("%c", MAP_EMPTY); // 폭탄 지우기
				}
			}
		}
	}
}
void score_service(int tick)
{
	static int tick_last = 0; // 지속시간을 계산하여 일정 시간 후 메세지를 지우기 위한 용도
	int i;
	
	if (tick % 1000 == 0) // 10초가 경과할 때 마다 점수 서비스 발생
	{
		tick_last = tick; // 점수 서비스가 발생 했을 때의 시간 저장

		for (i = 0; i < 10; i++) // 점수를 한번에 증가 시키면 점수가 10n을 초과 했을 때 스테이지가 오르지 않으므로 1씩 증가 시킨다.
		{
			save_score++;
			stage();
		}

		gotoxy(21, 6);
		printf("%d", save_score); // 점수 출력

		gotoxy(24, 0);
		printf("점수 서비스!"); // 메세지 출력
	}
	if (tick == tick_last + 100) // 메세지 출력 후 1초가 지나면 메세지를 지운다 
	{
		gotoxy(24, 0);
		for (i = 0; i < 12; i++)
		{
			printf("%c", MAP_EMPTY);
		}
	}
}
void print_time(int tick)
{
	if (tick % 100 == 0) // 시간은 초 단위로 출력
	{
		gotoxy(21, 38);
		printf("%d", tick / 100);
	}
}
void player_display(void)
{
	gotoxy(player.row, player.column); 
	printf("%c", MAP_PLAYER); 
}
void enemy_display(void)
{
	int enemy_num;

	for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
	{
		gotoxy(enemy.row[enemy_num], enemy.column[enemy_num]);
		printf("%c", MAP_ENEMY);
	}
}