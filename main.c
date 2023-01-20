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
	initialize(); // 모든 적 좌표를 시작 위치로 초기화, 폭탄 효과 배열을 TRUE 혹은 FALSE로 초기화

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
		bomb_effect(); // 폭탄 효과 함수
		score_service(tick); // 점수 서비스 함수
		print_time(tick); // 게임 시간 출력 함수
	}
	outro(tick); // outro 화면 출력

	return 0;
}