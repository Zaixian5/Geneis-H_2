/***********************************
   모든 소스파일이 공유하는 헤더파일 
************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>

/*매크로 정의*/
#define FIELD_WIDTH 40 // 2차원 맵의 열
#define FIELD_HEIGHT 20 // 2차원 맵의 행
#define LEFT_CORNER 1 // 맵의 왼쪽 끝
#define RIGHT_CORNER (FIELD_WIDTH - 2) // 맵의 오른쪽 끝
#define UP_CORNER 1 // 맵의 위쪽 끝
#define DOWN_CORNER (FIELD_HEIGHT - 2) // 맵의 아래쪽 끝

#define RAND_WALL_CNT (int)(DOWN_CORNER * RIGHT_CORNER * 0.1) // 랜덤 벽의 개수(벽의 개수는 정수이어야 하므로 int형 변환)

#define MAP_WALL '#' // 벽
#define MAP_PLAYER '@' // 플레이어 캐릭터
#define MAP_ENEMY '$' // 적 캐릭터
#define MAP_EMPTY ' ' // 맵의 공백

#define DIR_LEFT -1 // 캐릭터가 왼쪽으로 이동할 때 좌표변경시 이용
#define DIR_RIGHT 1 // 캐릭터가 오른쪽으로 이동할 때 좌표변경시 이용
#define DIR_UP -1 // 캐릭터가 위로 이동할 때 좌표변경시 이용
#define DIR_DOWN 1 // 캐릭터가 아래로 이동할 때 좌표변경시 이용

#define K_ARROW 224 // 방향키 아스키코드
#define K_UP 72 // 윗 방향키
#define K_DOWN 80 // 아래 방향키
#define K_LEFT 75 // 왼쪽 방향키
#define K_RIGHT 77 // 오른쪽 방향키
#define K_QUIT 'q' // 게임종료
#define K_NONE 0 // 키 입력이 없을 시 반환 값

#define SKILL_EFFECT '!' // 스킬 이펙트
#define SKILL_KEY_HORIZONTAL 'z' // 수평 스킬 키
#define SKILL_KEY_VERTICAL 'x' // 수직 스킬 키

#define STAGE 20 // 최대 스테이지는 20으로 설정

/*구조체 정의*/
typedef struct
{
	int row[RAND_WALL_CNT];
	int column[RAND_WALL_CNT];
} RAND_WALL; // 랜덤 벽의 좌표를 저장하는 구조체

typedef struct
{
	int row; // 플레이어의 세로 좌표
	int column; // 플레이어의 가로 좌표
	bool horizontal_skill_column[RIGHT_CORNER + 1]; // 수평 스킬(z)의 세로 좌표를 저장
	bool vertical_skill_row[DOWN_CORNER + 1]; // 수직 스킬(x)의 가로 좌표를 저장
	/*
		스킬은 랜덤 벽을 피해서 발사되어야 함
		좌표가 랜덤 벽과 일치할 경우 FALSE, 일치하지 않을 경우 TRUE를 저장함
		인덱스에는 좌표를 저장하여 배열 값이 TRUE일 경우 인덱스 값으로 이동하여 스킬을 출력하는 알고리즘
	*/
} PLAYER_INFO; // 플레이어 정보 구조체

typedef struct
{
	int row[STAGE + 1]; // 적의 세로 좌표
	int column[STAGE + 1]; // 적의 가로 좌표
	/*
		각각의 배열에는 적의 좌표 값이 저장되고
		인덱스에는 적의 아이덴티티 넘버(스테이지 값과 동일)가 들어간다
	*/
	int regen_row; // 적의 세로 리젠 좌표
	int regen_column; // 적의 가로 리젠 좌표
} ENEMY_INFO; // 적 정보 구조체

#endif