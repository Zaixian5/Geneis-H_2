/***********************************
   ��� �ҽ������� �����ϴ� ������� 
************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>

/*��ũ�� ����*/
#define FIELD_WIDTH 40 // 2���� ���� ��
#define FIELD_HEIGHT 20 // 2���� ���� ��
#define LEFT_CORNER 1 // ���� ���� ��
#define RIGHT_CORNER (FIELD_WIDTH - 2) // ���� ������ ��
#define UP_CORNER 1 // ���� ���� ��
#define DOWN_CORNER (FIELD_HEIGHT - 2) // ���� �Ʒ��� ��

#define RAND_WALL_CNT (int)(DOWN_CORNER * RIGHT_CORNER * 0.1) // ���� ���� ����(���� ������ �����̾�� �ϹǷ� int�� ��ȯ)

#define MAP_WALL '#' // ��
#define MAP_PLAYER '@' // �÷��̾� ĳ����
#define MAP_ENEMY '$' // �� ĳ����
#define MAP_EMPTY ' ' // ���� ����

#define DIR_LEFT -1 // ĳ���Ͱ� �������� �̵��� �� ��ǥ����� �̿�
#define DIR_RIGHT 1 // ĳ���Ͱ� ���������� �̵��� �� ��ǥ����� �̿�
#define DIR_UP -1 // ĳ���Ͱ� ���� �̵��� �� ��ǥ����� �̿�
#define DIR_DOWN 1 // ĳ���Ͱ� �Ʒ��� �̵��� �� ��ǥ����� �̿�

#define K_ARROW 224 // ����Ű �ƽ�Ű�ڵ�
#define K_UP 72 // �� ����Ű
#define K_DOWN 80 // �Ʒ� ����Ű
#define K_LEFT 75 // ���� ����Ű
#define K_RIGHT 77 // ������ ����Ű
#define K_QUIT 'q' // ��������
#define K_NONE 0 // Ű �Է��� ���� �� ��ȯ ��

#define SKILL_EFFECT '!' // ��ų ����Ʈ
#define SKILL_KEY_HORIZONTAL 'z' // ���� ��ų Ű
#define SKILL_KEY_VERTICAL 'x' // ���� ��ų Ű

#define STAGE 20 // �ִ� ���������� 20���� ����

/*����ü ����*/
typedef struct
{
	int row[RAND_WALL_CNT];
	int column[RAND_WALL_CNT];
} RAND_WALL; // ���� ���� ��ǥ�� �����ϴ� ����ü

typedef struct
{
	int row; // �÷��̾��� ���� ��ǥ
	int column; // �÷��̾��� ���� ��ǥ
	bool horizontal_skill_column[RIGHT_CORNER + 1]; // ���� ��ų(z)�� ���� ��ǥ�� ����
	bool vertical_skill_row[DOWN_CORNER + 1]; // ���� ��ų(x)�� ���� ��ǥ�� ����
	/*
		��ų�� ���� ���� ���ؼ� �߻�Ǿ�� ��
		��ǥ�� ���� ���� ��ġ�� ��� FALSE, ��ġ���� ���� ��� TRUE�� ������
		�ε������� ��ǥ�� �����Ͽ� �迭 ���� TRUE�� ��� �ε��� ������ �̵��Ͽ� ��ų�� ����ϴ� �˰���
	*/
} PLAYER_INFO; // �÷��̾� ���� ����ü

typedef struct
{
	int row[STAGE + 1]; // ���� ���� ��ǥ
	int column[STAGE + 1]; // ���� ���� ��ǥ
	/*
		������ �迭���� ���� ��ǥ ���� ����ǰ�
		�ε������� ���� ���̵�ƼƼ �ѹ�(�������� ���� ����)�� ����
	*/
	int regen_row; // ���� ���� ���� ��ǥ
	int regen_column; // ���� ���� ���� ��ǥ
} ENEMY_INFO; // �� ���� ����ü

#endif