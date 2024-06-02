/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:43:33 by janhan            #+#    #+#             */
/*   Updated: 2024/06/03 03:54:25 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"
#include <math.h>

/**
 * @brief
 * qsort함수용 비교 함수
 * @param a
 * @param b
 * @return int
 */
static int compare(const void *a , const void *b)
{
	const t_object *obj_a = *(const t_object **)a;
	const t_object *obj_b = *(const t_object **)b;

	if(obj_a->distance > obj_b->distance)
		return -1;
	else if(obj_a->distance < obj_b->distance)
		return 1;
	else
		return 0;
}

/**
 * @brief
 * 플레이어와 오브젝트 간의 거리 계산
 * @param obj
 * @param player
 * @param cnt
 */
static void	calculate_obj_dist(t_object **obj, t_player *player, int cnt)
{
	const int	px = player->player_x;
	const int	py = player->player_y;
	t_object	*one_obj;
	int			i;

	i = 0;
	while (i < cnt)
	{
		one_obj = obj[i];
		one_obj->distance = dist(px, py, one_obj->object_x, one_obj->object_y);
		i++;
	}
}

static void	draw_obj(t_object **obj, int cnt, t_player *player, t_game *game)
{
	int	i;
	t_object	*one_obj;
	int			height;
	int			width;
	double		scale;
	double		obj_rad;//, obj_left_rad, obj_right_rad;
	double		player_left_rad;
	double		player_right_rad;

	i = 0;
	player_left_rad = player->player_rad + M_PI / 6;
	player_right_rad = player->player_rad - M_PI / 6;
	if (player_right_rad < 0)
		player_right_rad += M_PI * 2;
	if (player_left_rad > M_PI * 2)
		player_left_rad -= M_PI * 2;
	// TODO: 현재 오브젝트와 멀어진뒤 화면 각도를 전환하면 이상한 부분에서 오브젝트가 없어지는 버그 가있음

	while (i < cnt)
	{
		one_obj = obj[i];
		if (one_obj->type == VERTICAL_DOOR || one_obj->type == HORIZONTAL_DOOR)
		{
			i++;
			continue;
		}
		//scale = (double) 64 /(one_obj->distance); // TODO: 이미지의 각 크기가 다를수 있는데 이미지의 크기를 통합할수있는 수식이 필요함
		scale = (double)WINDOW_W/(one_obj->distance * 120);

															// TODO: 이미지 크기 통합 예정 6월 3일
		// Wnew = Hnew / Horiginal * Woriginl
		// WnewA = 300 / 600 * 800 = 0.5 * 800 = 400
		// WnewB = 300 / 768 * 1024 =0.390625 * 1024 = 400
		// 적용이 가능한가 검토.

		width = game->object_texture[one_obj->type][one_obj->frame]->width * scale; // 폭 절반임
		height = game->object_texture[one_obj->type][one_obj->frame]->height * scale;
		obj_rad = atan2(one_obj->object_y - player->player_y, one_obj->object_x - player->player_x);
		if (obj_rad < 0)
			obj_rad += M_PI * 2;
		// 오브젝트의 좌우 각도 계산
		// obj_left_rad = obj_rad - atan2(width, one_obj->distance);
		// obj_right_rad = obj_rad + atan2(width, one_obj->distance);
		if(one_obj->distance > 30) // 문일때의 함수를 빼야함
			if (((obj_rad > player_right_rad && obj_rad < player_left_rad)
				|| (player_right_rad > player_left_rad)) && ((obj_rad > player_right_rad)
				|| (obj_rad < player_left_rad)))
			//
			// 오브젝트의 좌우 조금이라도 나와야 하면 그리려고 아래 조건문을 썼는데
			// 아래 조건문을 쓰면 이상하게 나왔다 안나왔다 해서
			// 오브젝트 중심으로만 계산함 일단
			// if ((obj_right_rad > player_right_rad && obj_right_rad < player_left_rad)
			// 	|| (obj_left_rad > player_right_rad && obj_left_rad < player_left_rad)
			// 	|| (player_right_rad > player_left_rad) && ((obj_right_rad > player_right_rad) || (obj_left_rad < player_left_rad)))
			//
			{
				// obj 폭까지 고려해서 넣어야함
				// 오브젝트 하나 그리는 함수 넣을곳

				// int	object_position, object_start, object_destination;
				// object_position = player->player_rad - obj_rad;
				// object_start = WINDOW_W / 2 + (int)(object_position / 0.000545415391) - width;
				// object_destination = WINDOW_W / 2 + (int)(object_position / 0.000545415391) + width;
				//
				// int	render_x = object_start;
				// t_2dot dots;
				//
				//
				// while (render_x < object_destination)
				// {
				//
				// 	dots.start_x = render_x;
				// 	dots.start_y = 1080 / 2 - height;
				// 	dots.dest_x = render_x;
				// 	dots.start_y = 1080 / 2 + height;
				// 	draw_line(game->render, dots, 0x00FF0000);
				//
				// 	render_x++;
				// }
				double angle_diff = obj_rad - player->player_rad;
				//if (angle_diff < -M_PI)
				//	angle_diff += 2 * M_PI;
				//if (angle_diff > M_PI)
				//	angle_diff -= 2 * M_PI;
				while (angle_diff < M_PI)
					angle_diff += 2 * M_PI;
				while (angle_diff > M_PI)
					angle_diff -= 2 * M_PI;
				int screen_x = (int)((angle_diff + M_PI / 6) * (WINDOW_W / (M_PI / 3)));
				int object_start_x = screen_x - width;
				int object_end_x = screen_x + width;
				int render_x = object_start_x;
				// printf("player rad: %f\n", player->player_rad);
				// printf("object rad: %f\n", obj_rad);
				// printf("angle_diff: %f\n", angle_diff);
				// printf("obj x: %d\n", object_start_x);
				// printf("obj y: %d\n", object_end_x);
				double step_x;
				double step_y;
				step_x = 0;				// 옆으로 좀 밀려서 병신되는거 이거 초기화 안했었음.
				while (render_x < object_end_x && render_x < WINDOW_W) // 오브젝트 왼쪽부터 세로로 한줄씩 그리기
				{
					step_y = 0;

					//if (render_x >= 0 && render_x <= 1920)
					if (render_x > 0 && game->w_dist[render_x] > one_obj->distance)
					{
						// dots.start_x = render_x;
						// dots.start_y = WINDOW_H / 2 - height + player->player_fov_off_y;
						// dots.dest_x = render_x;
						// dots.dest_y = WINDOW_H / 2 + height + player->player_fov_off_y;
						// draw_line(game->render, dots, 0x00FF0000);
						// 일단은 라인으로 그렸는데
						// 렌더 텍스쳐 함수에 있는거 그대로 사용해도 될듯?
					
						game->w_dist[render_x] = one_obj->distance; // 나중에 문 그려야해서 오브젝트 거리로 덮어씌움
						int	start_y = WINDOW_H / 2 - height + player->player_fov_off_y + height;
						int	dest_y = WINDOW_H / 2 + height + player->player_fov_off_y + height;
						if (dest_y > WINDOW_H)
							dest_y = WINDOW_H;
						while (start_y < dest_y)
						{
							unsigned int color;
							color = color_spoid((int)step_x, (int)step_y, game->object_texture[one_obj->type][one_obj->frame]);
							step_y += (double)game->object_texture[one_obj->type][one_obj->frame]->height / (2 * height);
							if ((color & 0xFF000000) != 0xFF000000)
								put_pixel_on_img(game->render, render_x, start_y, color);
							start_y++;
						}
					}
					render_x++;
					//draw_door 함수 테스트하려고 주석처리함
					//if (one_obj->type != DOOR_OBJECT)
						step_x += (double)game->object_texture[one_obj->type][one_obj->frame]->width / (2 * width);
					// else
					// 	step_x += (double)game->texture[DOOR].width / (2 * width);
				}
			}
		i++;
	}
}

// -----------------------------------------------------
// 아래부터 도어 함수

static int	get_door_width(t_object *door, t_player *player, t_game *game)
{
	int	x;
	int	y;
	double	rad;
	int		width;

	x = door->object_x;
	y = door->object_y;
	if (door->type == VERTICAL_DOOR)
	{
		y = y - (y & 63); //  == y - (y % 64);
		// rad = atan((y - player->player_y) / (x - player->player_x));
		// rad -= atan((y + 64 - player->player_y) / (x - player->player_x));
		// rad = fabs(rad);
		// width = rad / (M_PI / 3.0) * WINDOW_W;
	}
	else
	{
		x = x - (y & 63);
	}
	rad = atan((y - player->player_y) / (x - player->player_x));
	rad -= atan((door->object_y - player->player_y) / (door->object_x - player->player_x));
	rad = fabs(rad * 2);
	width = rad / (M_PI / 3) * WINDOW_W;
	return (width);
}

static double	get_door_height(t_object *door, t_player *player, int width, double *offset)
{
	double	middle;
	double	longer;
	double	smaller;
	double	gap;

	middle = (WINDOW_H / door->distance) * 100;
	if (door->type == VERTICAL_DOOR)
	{
		longer = dist(player->player_x, player->player_y, door->object_x, door->object_y - ((int)door->object_y & 63));
		longer = (WINDOW_H / longer) * 100;
		smaller = dist(player->player_x, player->player_y, door->object_x, door->object_y - ((int)door->object_y & 63) + 64);
		smaller = (WINDOW_H / smaller) * 100;
	}
	else
	{
		longer = dist(player->player_x, player->player_y, door->object_x - ((int)door->object_x & 63), door->object_y);
		longer = (WINDOW_H / longer) * 100;
		smaller = dist(player->player_x, player->player_y, door->object_x - ((int)door->object_x & 63) + 64, door->object_y);
		smaller = (WINDOW_H / smaller) * 100;
	}
	gap = fabs(longer - smaller);
	*offset = gap / width;
	// printf("offset: %f", *offset);
    return (middle);
}


void	draw_door(t_object **obj, int cnt, t_player *player, t_game *game)
{
	t_object 	*one_door;
	int			i;


	i = 0;
	while (i < cnt)
	{
		one_door = obj[i];
		// 만약 오브젝트가 도어 타입이 아니면 건너뛰기
		if (one_door->type != VERTICAL_DOOR && one_door->type != HORIZONTAL_DOOR)
		{
			i++;
			continue;
		}
		// 오브젝트가 도어 타입이면

		double	player_door_rad = atan2(one_door->object_y - player->player_y, one_door->object_x - player->player_x);
		double	door_rad;
		double	rad_diff;

		double		line_h;
		int		width;
		double		h_offset;

		double		current_height;

		width = get_door_width(one_door, player, game); // 문 전체 폭
		// 위 함수에 Rad_diff 를 같이 줘서 오프셋을 아예 양수 음수로 바꿔도 될듯

		double angle_diff = player_door_rad - player->player_rad;
		line_h = get_door_height(one_door, player, width ,&h_offset);
		if (player_door_rad < 0)
			player_door_rad += M_PI * 2;
		if (one_door->type == VERTICAL_DOOR)
			door_rad = M_PI_2;
		else
			door_rad = 2 * M_PI;

		rad_diff = door_rad - player_door_rad;
		if (rad_diff < 0)
			rad_diff += M_PI * 2;
		//printf("door: (%d, %d)\n", (int)one_door->object_x, (int)one_door->object_y);
		if ((rad_diff > 0 && rad_diff < M_PI_2) || (rad_diff > M_PI && rad_diff < M_PI_2 + M_PI))
		// 문이 왼쪽에서 오른쪽으로 갈수록 높이 감소
		{
			current_height	= line_h + h_offset * width / 2.0;
			h_offset = -h_offset;
		}
		else // 문이 왼쪽에서 오른쪽으로 갈수록 높이 증가
		{
			current_height = line_h - h_offset * width / 2.0;
		}
		while (angle_diff < M_PI)
			angle_diff += 2 * M_PI;
		while (angle_diff > M_PI)
			angle_diff -= 2 * M_PI;
		int	screen_x = (int)((angle_diff + M_PI / 6) * (WINDOW_W / (M_PI / 3)));
		int	door_start = screen_x - width / 2;
		int	door_end = screen_x + width / 2;
		// printf("player rad: %f\n", player->player_rad);
		// printf("door_rad: %f\n", player_door_rad);
		// printf("angle_diff: %f\n", angle_diff);
		// printf("screen_x: %d\n", screen_x);
		// printf("door_start: %d\n", door_start);
		// printf("door_end: %d\n", door_end);
		// printf("width: %d\n", width);

		int render_x = door_start;
		double step_x;
		double step_y;
		int	start_y;
		double one_step_x = (double)game->object_texture[one_door->type][0]->width / width;
		step_x = 0;
		while (render_x < door_end && render_x < WINDOW_W)
		{
			step_y = 0;
			start_y = (WINDOW_H / 2.0) - current_height / 2 + player->player_fov_off_y;
			if (render_x > 0 && game->w_dist[render_x] > one_door->distance)
			{

				// 아래는 한색깔로 그리는 함수
				// t_2dot dots;
				// dots.start_x = render_x;
				// dots.start_y = start_y;
				// if (dots.start_y < 0)
				// 	dots.start_y = 0;
				// dots.dest_x = render_x;
				// dots.dest_y = start_y + current_height;
				// if (dots.dest_y > WINDOW_H)
				// 	dots.dest_y = WINDOW_H;
				// //printf("%d -> %d\n", dots.start_y, dots.dest_y);
				// draw_line(game->render, dots, 0x00FF0000);
				
				int dest_y = start_y + current_height;
				if (dest_y > WINDOW_H)
					dest_y = WINDOW_H;
				double one_step_y = (double)game->object_texture[one_door->type][0]->height / current_height;
				while (start_y < dest_y)
				{
					unsigned int color;
					if (start_y > WINDOW_H)
						break ;
					int j = 0;
					while (start_y + j < 0)
						j++;
					step_y += one_step_y * j;
					start_y += j;
					color = color_spoid((int)step_x, (int)step_y, game->object_texture[one_door->type][0]);
					if ((color & 0xFF000000) != 0xFF000000)
						put_pixel_on_img(game->render, render_x, start_y, color);
					step_y += one_step_y;
					start_y++;
				}
			}
			render_x++;
			current_height += h_offset;
			step_x += one_step_x;
		}
		i++;
	}
}


void	render_sprite_object(t_game *game)
{
	calculate_obj_dist(game->objects, game->player, game->object_count);
	qsort(game->objects, game->object_count, sizeof(t_object *), compare);
	draw_obj(game->objects, game->object_count, game->player, game);
	draw_door(game->objects, game->object_count, game->player, game);

}


/* 높이 : (WINDOW_H / dest->distance) * 50; <- 원래는 곱하기 100이었음
 * 폭   :
 *
 * 스프라이트의 기존 높이/폭 비율을 유지해야함
 * 기존 이미지 폭 * scale -> 새로 그릴 오브젝트의 폭
 *
 *
 * 3. 거리별로 오브젝트의 길이를 구해야함
 * 4. 각 오브젝트가 플레이어의 시야 안에 있는지 체크 (일부더라도)
 * 5. wall 까지 거리랑 비교하면서 거리가 더 짧은 것들은 그리기 (거리가 먼 순서대로)
 */
