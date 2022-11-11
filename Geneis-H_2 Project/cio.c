/********************************************
   �ܼ� ����� ���� �Լ����� ���ִ� �ҽ����� 
*********************************************/

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

/*��������*/
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
RAND_WALL rd_wall = { { 0 }, { 0 } }; // ���� ���� ��ǥ�� ����
PLAYER_INFO player = { UP_CORNER, LEFT_CORNER, { 0 }, { 0 }, { 0 } }; // �÷��̾� ��ǥ�� ��ų, ��ź ��ǥ�� ����
ENEMY_INFO enemy = { { 0 }, { 0 }, 0, 0, 0 }; // �� ��ǥ, ���� ��ǥ, óġ�� ���� ���� ����
int stage_num = 1; // �������� ��ȣ�� ����
int save_score = 1; // ������ ����

void gotoxy(int row, int column) // ��ǥ�� �̵��ϴ� �Լ�. ������ǥ�� ������ǥ�� �ݴ�� �Ǿ��ִ�.
{
	COORD pos = { column, row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int get_key(void) // Ű �Է��� ó���ϴ� �Լ�
{
	while (true)
	{
		if (_kbhit())
		{
			return _getch(); // Ű �Է��� ���� ��� �Է� ���� ��ȯ
		}
		else
		{
			return K_NONE; // Ű �Է��� ���� ��� 0�� ��ȯ
		}
	}
}
void print_map(void)
{
	int i;

	for (i = 0; i < FIELD_HEIGHT; i++) // ���� �ٱ��� ���� �ʱ� �÷��̾�, �ʱ� ���� ��ġ�� ���
	{
		printf("%s\n", board[i]);
	}

	srand((unsigned int)time(NULL));

	for (i = 0; i < RAND_WALL_CNT; i++) // ���� ���� ��ǥ�� �����Ͽ� ����
	{
		rd_wall.row[i] = (rand() % DOWN_CORNER) + UP_CORNER; // 1 ~ 18 ������ ������ ���� ��ǥ�� ����
		rd_wall.column[i] = (rand() % RIGHT_CORNER) + LEFT_CORNER; // 1 ~ 38 ������ ������ ���� ��ǥ�� ����

		if ((rd_wall.row[i] == UP_CORNER) && (rd_wall.column[i] == LEFT_CORNER)) // �»�� ��ǥ���� ���� �������� ���ϰ� ��
		{
			i--; // continue�� �ص� ���� ������ �����Ǿ�� �ϹǷ� i�� 1 ����
			continue;
		}
		if ((rd_wall.row[i] == DOWN_CORNER) && (rd_wall.column[i] == RIGHT_CORNER)) // ���ϴ� ��ǥ���� ���� �������� ���ϰ� ��
		{
			i--; // continue�� �ص� ���� ������ �����Ǿ�� �ϹǷ� i�� 1 ����
			continue;
		}
	}

	for (i = 0; i < RAND_WALL_CNT; i++) // ���� ���� ���
	{
		gotoxy(rd_wall.row[i], rd_wall.column[i]);
		printf("%c", MAP_WALL);
	}

	// ���� ���� ���
	gotoxy(0, 42);
	printf("<���ӹ��>");

	gotoxy(2, 43);
	printf("@: �÷��̾� $: ��");

	gotoxy(4, 42);
	printf(" - �÷��̾�� ����Ű�� ������ �� �ֽ��ϴ�.");
	
	gotoxy(6, 42);
	printf(" - �÷��̾�� ���� �ε����ų� ���� ��ų�� ������ ������ ������");

	gotoxy(7, 42);
	printf("   ���� �ٸ� ��ġ�� �ٽ� �����˴ϴ�.");

	gotoxy(9, 42);
	printf(" - �÷��̾�� z, xŰ�� ��ų�� ����� �� �ֽ��ϴ�.");

	gotoxy(10, 42);
	printf("   -> z: ���� ��ų, x: ���� ��ų");

	gotoxy(12, 42);
	printf(" - ������ 10�� ���� �� ���� ���������� �ö󰩴ϴ�.");

	gotoxy(14, 42);
	printf(" - ���������� ���� ���� ���� ���� �������� �ִ� ���������� 20�Դϴ�.");

	gotoxy(16, 42);
	printf(" - ������ 10�� ����� �� �� ���� ��ź�� �����ϴ�.");

	gotoxy(17, 42);
	printf("   -> ��ź: �ʿ� �����ϴ� ��� ���� óġ�Ѵ�.");

	gotoxy(19, 42);
	printf(" - ��� �ð��� 10�ʰ� �� �� ���� ���� ���� 10���� �ο��˴ϴ�.");

	gotoxy(21, 43);
	printf("q: ��������");

	gotoxy(21, 0);
	printf("����: %d", save_score); // �ʱ� ���� ���

	gotoxy(21, 12);
	printf("��������: %d", stage_num); // �ʱ� �������� ���

	gotoxy(21, 28);
	printf("�ð�(��): ");
}
void intro(void)
{
	printf("Welcome!\n");
	printf("�ƹ�Ű�� ��������");
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
	printf("����: %d\n", save_score);
	printf("óġ�� ��: %d\n", enemy.captured);
	printf("���� �������� : %d\n", stage_num);
	printf("���� �ð�(��) : %d\n\n", tick / 100);
	printf("Bye!\n");
}
void initialize(void) 
{
	int enemy_num;
	int bomb_row, bomb_column;
	int i;

	// �� ��ǥ�� ��� ���� ��ġ�� �ʱ�ȭ
	for (enemy_num = 1; enemy_num < STAGE + 1; enemy_num++)
	{
		enemy.row[enemy_num] = DOWN_CORNER;
		enemy.column[enemy_num] = RIGHT_CORNER;
	}

	// ��ź ȿ�� ��ǥ�� ���� ���� ���ؼ� �ʱ�ȭ
	for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
	{
		for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
		{
			player.bomb_effect[bomb_row][bomb_column] = TRUE; // ����, �迭 ��ü�� TRUE�� �ʱ�ȭ �Ѵ�.
		}
	}
	for (i = 0; i < RAND_WALL_CNT; i++)
	{
		player.bomb_effect[rd_wall.row[i]][rd_wall.column[i]] = FALSE; // ��������, ��ǥ�� ���� ���� ��ġ �ϴ� ��� FALSE�� �����Ѵ�.
	}
}
void stage(void) // �������� ���� �Լ�
{	
	if (save_score % 10 == 0) // ������ 10�� ������ �� ���� ���������� �ö�
	{
		if (stage_num < STAGE) 
		{
			stage_num++;

			gotoxy(21, 22);
			printf("%d", stage_num);
		}
	}
}
void turn_player(void) // Ű �Է��� ���� �� �÷��̾��� ��ǥ�� �����ϴ� �Լ�.
{
	int arrow = _getch(); // ����Ű �ƽ�Ű�ڵ� �ι�° ��ȯ ���� ����
	int i;

	gotoxy(player.row, player.column); // ���� �÷��̾��� ��ġ�� ����
	printf("%c", MAP_EMPTY);

	switch (arrow)
	{
	case K_LEFT: // ���� ����Ű �Է½�
		player.column += DIR_LEFT; // �÷��̾��� ��ǥ�� �������� 1 �̵�
		if (player.column < LEFT_CORNER) // �÷��̾��� ��ġ�� ���� ���� ���� ���ϰ� �ϱ� ����
		{
			player.column = LEFT_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // �÷��̾��� ��ġ�� ���� ���� ħ������ ���ϰ� ��
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.column = rd_wall.column[i] + DIR_RIGHT;
			}
		}
		break;

	case K_RIGHT: // ������ ����Ű �Է½�
		player.column += DIR_RIGHT; // �÷��̾��� ��ǥ�� ���������� 1 �̵�
		if (player.column > RIGHT_CORNER) // �÷��̾��� ��ġ�� ������ ���� ���� ���ϰ� �ϱ� ����
		{
			player.column = RIGHT_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // �÷��̾��� ��ġ�� ���� ���� ħ������ ���ϰ� ��
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.column = rd_wall.column[i] + DIR_LEFT;
			}
		}
		break;

	case K_UP: // ���� ����Ű �Է½�
		player.row += DIR_UP; // �÷��̾��� ��ǥ�� �������� 1 �̵�
		if (player.row < UP_CORNER) // ���� ��ġ�� ���� ���� ���� ���ϰ� �ϱ� ����
		{
			player.row = UP_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // �÷��̾��� ��ġ�� ���� ���� ħ������ ���ϰ� ��
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.row = rd_wall.row[i] + DIR_DOWN;
			}
		}
		break;

	case K_DOWN: // �Ʒ��� ����Ű �Է½�
		player.row += DIR_DOWN; // �÷��̾��� ��ǥ�� �Ʒ������� 1 �̵�
		if (player.row > DOWN_CORNER) // ���� ��ġ�� �Ʒ��� ���� ���� ���ϰ� �ϱ� ����
		{
			player.row = DOWN_CORNER;
		}
		for (i = 0; i < RAND_WALL_CNT; i++) // �÷��̾��� ��ġ�� ���� ���� ħ������ ���ϰ� ��
		{
			if ((player.row == rd_wall.row[i]) && (player.column == rd_wall.column[i]))
			{
				player.row = rd_wall.row[i] + DIR_UP;
			}
		}
		break;
	}
}
void turn_enemy(void) // ���� ��ġ�� �������� �����¿� �� �� �������� ��ĭ �����̵��� ��
{	
	int i;
	int enemy_num;
	int rand_dir = 0;

	srand((unsigned int)time(NULL));

	for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
	{
		gotoxy(enemy.row[enemy_num], enemy.column[enemy_num]); // ���� ���� ��ġ�� ����
		printf("%c", MAP_EMPTY);

		rand_dir = (rand() % 4); // 0 ~ 3 ������ ������ ����
		
		switch (rand_dir) // 0 ~ 3 �� � ���� ��� ������ �ǹ��ϴ� ���� ���Ƿ� ���Ͽ���
		{
		case 0: // 0�� ������ ���� ��ǥ�� ���ʷ� ��ĭ �̵�
			enemy.row[enemy_num] += DIR_UP;
			if (enemy.row[enemy_num] < UP_CORNER) // ���� ��ġ�� ���� ���� ���� ���ϰ� �ϱ� ����
			{
				enemy.row[enemy_num] = UP_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // ���� ��ġ�� ���� ���� ħ������ ���ϰ� ��
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.row[enemy_num] = rd_wall.row[i] + DIR_DOWN;
				}
			}
			break;

		case 1: // 1�� ������ ���� ��ǥ�� �Ʒ������� ��ĭ �̵�
			enemy.row[enemy_num] += DIR_DOWN;
			if (enemy.row[enemy_num] > DOWN_CORNER) // ���� ��ġ�� �Ʒ��� ���� ���� ���ϰ� �ϱ� ����
			{
				enemy.row[enemy_num] = DOWN_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // ���� ��ġ�� ���� ���� ħ������ ���ϰ� ��
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.row[enemy_num] = rd_wall.row[i] + DIR_UP;
				}
			}
			break;

		case 2: // 2�� ������ ���� ��ǥ�� ���������� ��ĭ �̵�
			enemy.column[enemy_num] += DIR_RIGHT;
			if (enemy.column[enemy_num] > RIGHT_CORNER) // ���� ��ġ�� ������ ���� ���� ���ϰ� �ϱ� ����
			{
				enemy.column[enemy_num] = RIGHT_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // ���� ��ġ�� ���� ���� ħ������ ���ϰ� ��
			{
				if ((enemy.row[enemy_num] == rd_wall.row[i]) && (enemy.column[enemy_num] == rd_wall.column[i]))
				{
					enemy.column[enemy_num] = rd_wall.column[i] + DIR_LEFT;
				}
			}
			break;

		case 3: // 3�� ������ ���� ��ǥ�� �������� ��ĭ �̵�
			enemy.column[enemy_num] += DIR_LEFT;
			if (enemy.column[enemy_num] < LEFT_CORNER) // ���� ��ġ�� ���� ���� ���� ���ϰ� �ϱ� ����
			{
				enemy.column[enemy_num] = LEFT_CORNER;
			}
			for (i = 0; i < RAND_WALL_CNT; i++) // ���� ��ġ�� ���� ���� ħ������ ���ϰ� ��
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

	enemy.captured++; // óġ�� ���� �� 1 ����
	save_score++; // ������ 1 �ø��� ���

	gotoxy(21, 6);
	printf("%d", save_score);

	stage(); // ���������� ���

	while (TRUE)
	{
		duplicated = 0;

		enemy.regen_row = (rand() % DOWN_CORNER) + UP_CORNER; // 1 ~ 18 ������ ���� �ϳ��� ������ ���� ���� ��ǥ�� ����
		enemy.regen_column = (rand() % RIGHT_CORNER) + LEFT_CORNER; // 1 ~ 38 ������ ���� �ϳ��� ������ ���� ���� ��ǥ�� ����

		for (i = 0; i < RAND_WALL_CNT; i++)
		{
			if ((enemy.regen_row == rd_wall.row[i]) && (enemy.regen_column == rd_wall.column[i]))
			{
				duplicated++; // ���� �� ��ǥ�� ���� ��ǥ�� �ߺ��� ī��Ʈ
			}
		}
		if (duplicated == 0)
		{
			break; // ���� �� ��ǥ�� ���� ��ǥ�� �ߺ����� �ʾҴٸ� while�� Ż��
		}
	}

	// �ش� ���� ��ǥ�� ���� ��ǥ�� ����
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
			crash_effect(enemy_num); // �÷��̾�� ���� �ε����� �浹 ����Ʈ �Լ� ȣ��
		}
	}
}
void skill_effect(int skill_key)
{
	// z: ���� ���� ���������� !�� �߻�
	// x: ���� ���� ���������� !�� �߻�
	
	int coordinates;
	int enemy_num;
	int i;

	// ��ų ����ü �迭�� ��� TRUE�� �ʱ�ȭ
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
	case SKILL_KEY_HORIZONTAL: // zŰ �Է½�
		for (coordinates = LEFT_CORNER; coordinates <= RIGHT_CORNER; coordinates++)
		{
			for (i = 0; i < RAND_WALL_CNT; i++)
			{
				if ((rd_wall.row[i] == player.row) && (rd_wall.column[i] == coordinates))
				{
					player.horizontal_skill_column[coordinates] = FALSE; // ��ǥ�� ���� ���� ��ġ �� FALSE�� ���� 
				}
			}
			if (player.horizontal_skill_column[coordinates]) // TRUE�� ��� ��ǥ�� �̵��� ��ų ���
			{
				gotoxy(player.row, coordinates);
				printf("%c", SKILL_EFFECT);

				for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
				{
					if ((enemy.row[enemy_num] == player.row) && (enemy.column[enemy_num] == coordinates))
					{
						crash_effect(enemy_num); // ���� ��ų�� �´´ٸ� �浹 ����Ʈ �Լ� ȣ��
					}
				}
			}
		}
		Sleep(500); // ������ 0.5�ʰ� �Ͻ����� �� ��ų�� �����

		for (coordinates = LEFT_CORNER; coordinates <= RIGHT_CORNER; coordinates++)
		{
			if (player.horizontal_skill_column[coordinates])
			{
				gotoxy(player.row, coordinates);
				printf("%c", MAP_EMPTY);
			}
		}
		break;
    
	case SKILL_KEY_VERTICAL: // xŰ �Է½�
		for (coordinates = UP_CORNER; coordinates <= DOWN_CORNER; coordinates++)
		{
			for (i = 0; i < RAND_WALL_CNT; i++)
			{
				if ((rd_wall.row[i] == coordinates) && (rd_wall.column[i] == player.column))
				{
					player.vertical_skill_row[coordinates] = FALSE; // ��ǥ�� ���� ���� ��ġ �� FALSE�� ���� 
				}
			}
			if (player.vertical_skill_row[coordinates]) // TRUE�� ��� ��ǥ�� �̵��� ��ų ���
			{
				gotoxy(coordinates, player.column);
				printf("%c", SKILL_EFFECT);

				for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
				{
					if ((enemy.row[enemy_num] == coordinates) && (enemy.column[enemy_num] == player.column))
					{
						crash_effect(enemy_num); // ���� ��ų�� �´´ٸ� �浹 ����Ʈ �Լ� ȣ��
					}
				}
			}
		}
		Sleep(500); // ������ 0.5�ʰ� �Ͻ����� �� ��ų�� �����

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
	
	if (save_score % 10 == 0) // ������ 10�� ����� �� �� ���� ��ź �۵�
	{
		gotoxy(23, 0);
		printf("��ź!"); // �޼��� ���

		for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
		{
			for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
			{
				if (player.bomb_effect[bomb_row][bomb_column]) // TRUE�� ��� ��ǥ�� �̵��� ��ź ���
				{
					gotoxy(bomb_row, bomb_column);
					printf("%c", MAP_BOMB); 

					for (enemy_num = 1; enemy_num <= stage_num; enemy_num++)
					{
						if ((enemy.row[enemy_num] == bomb_row) && (enemy.column[enemy_num] == bomb_column))
						{
							crash_effect(enemy_num); // ���� ��ź�� �´´ٸ� �浹 ����Ʈ �Լ� ȣ��
						}
					}
				}
			}
		}
		Sleep(500); // ������ 0.5�ʰ� �Ͻ����� �� ��ź�� �޼����� �����

		gotoxy(23, 0);
		for (i = 0; i < 5; i++)
		{
			printf("%c", MAP_EMPTY); // �޼��� �����
		}

		for (bomb_row = UP_CORNER; bomb_row <= DOWN_CORNER; bomb_row++)
		{
			for (bomb_column = LEFT_CORNER; bomb_column <= RIGHT_CORNER; bomb_column++)
			{
				if (player.bomb_effect[bomb_row][bomb_column])
				{
					gotoxy(bomb_row, bomb_column);
					printf("%c", MAP_EMPTY); // ��ź �����
				}
			}
		}
	}
}
void score_service(int tick)
{
	static int tick_last = 0; // ���ӽð��� ����Ͽ� ���� �ð� �� �޼����� ����� ���� �뵵
	int i;
	
	if (tick % 1000 == 0) // 10�ʰ� ����� �� ���� ���� ���� �߻�
	{
		tick_last = tick; // ���� ���񽺰� �߻� ���� ���� �ð� ����

		for (i = 0; i < 10; i++) // ������ �ѹ��� ���� ��Ű�� ������ 10n�� �ʰ� ���� �� ���������� ������ �����Ƿ� 1�� ���� ��Ų��.
		{
			save_score++;
			stage();
		}

		gotoxy(21, 6);
		printf("%d", save_score); // ���� ���

		gotoxy(24, 0);
		printf("���� ����!"); // �޼��� ���
	}
	if (tick == tick_last + 100) // �޼��� ��� �� 1�ʰ� ������ �޼����� ����� 
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
	if (tick % 100 == 0) // �ð��� �� ������ ���
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