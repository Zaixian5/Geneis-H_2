/*
	20202844 사재헌
	과제2 창세기존-H(2)

	2-1) 분할 컴파일 (O)
	2-2) 맵 만들기 (O)
	2-3) 오브젝트 만들기 - PLAYER (O)
	2-4) 오브젝트 만들기 - ENEMY (O)
	2-5) 충돌 이벤트 (O)
	2-6) 스킬 이펙트 (O)
	2-7) 상태 표시 (O)
	2-8) 스테이지 (O)
	2-9) 추가기능 만들기
*/
/*
	<TODO..>
	
	추가 기능 만들기
	- 추가 기능은 각자 개성에 맞게 3개 이상
	- 플레이어, 적 구조체에 멤버가 5개 이상 되도록 디자인
	- main.c 주석에 어떤 추가기능을 구현했는지 작성
	- 예) 적이 사용하는 스킬, 보스, 스킬 쿨타임, 공격력, HP/MP, 레벨업, 스킬 종류와 정보

	<PLAN..>

	보스
	- 보스 스테이지는 마지막 20 스테이지로 정한다.
	- 보스 스테이지에서는 보스 스킬을 피해서 적을 공격해야 한다.
	- 보스 스킬에 3번 부딪히면 보스전을 다시 시작해야 한다.
	- 보스전까지 클리어하면 게임이 종료된다.

	추가할 구조체
	- 플레이어 구조체
		-> 보스 스킬에 몇번 부딪혔는지를 저장하는 변수
	- 적 구조체
		-> 보스 스킬 좌표

	추가기능에 작성할 것
	- 보스 캐릭터
	- 보스 스킬
	- 보스전 HP(적에 부딪힌 횟수)
*/

#include <stdbool.h>
#include <Windows.h>

#include "cio.h"
#include "common.h"

int main(void)
{
	int key = 0; // key 입력을 저장
	int tick = 0; // 1 tick = 10 ms
	
	intro(); // intro 화면 출력
	print_map(); // 맵 출력
	enemy_initialize(); // 모든 적 좌표 배열을 시작위치로 초기화

	while (true)
	{
		Sleep(10); // 프로그램의 진행을 10ms 마다 일시정지
		tick++;
		
		key = get_key(); // 키 입력 값(혹은 입력하지 않았을 때의 값)을 저장
		if (key == K_QUIT) // q를 누르면 게임이 종료된다
		{
			break;
		}
		else if (key == K_ARROW) // 방향키 입력시
		{
			turn_player(); // 플레이어의 좌표를 변경
			player_display(); // 플레이어의 위치를 출력
		}
		else if (key == SKILL_KEY_HORIZONTAL || key == SKILL_KEY_VERTICAL) // z, x 키 입력시
		{
			skill_effect(key); // 스킬 이펙트 출력 및 충돌 이펙트 함수 crash_effect() 호출
		}

		if ((key == K_ARROW) || (key == K_NONE)) 
		{
			if (tick % 20 == 0) // 적의 움직임을 0.2초 마다 처리
			{
				turn_enemy(); // 적의 좌표를 변경
				enemy_display(); // 적의 위치를 출력
			}
		}
		player_enemy_crash(); // 플레이어와 적이 부딪힐 경우 충돌 이펙트 함수 crash_effect() 호출
	}
	outro(); // outro 화면 출력

	return 0;
}