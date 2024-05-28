/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:52 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 23:29:54 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	render_mini_map(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	game->minimap_img = make_image(game, game->map_len_w * MINI_MAP_PIXEL,
			game->map_len_h * MINI_MAP_PIXEL);
	while (game->map[i])
	{
		j = 0;
		x = 0;
		while (j < game->map_len_w)
		{
			if (j > ft_strlen(game->map[i]) - 1 || game->map[i][j] == ' ')
				draw_square_on_img(game->minimap_img, x, y, 0x00333333);
			else if (game->map[i][j] == '1')
				draw_square_on_img(game->minimap_img, x, y, 0x00FFFFFF);
			else if (game->map[i][j] == 'D')
				draw_square_on_img(game->minimap_img, x, y, 0xD0D7FE);
			else
				draw_square_on_img(game->minimap_img, x, y, 0x00000000);
			x += MINI_MAP_PIXEL;
			j++;
		}
		y += MINI_MAP_PIXEL;
		i++;
	}
}

// void	render_mini_map_center(t_game *game)
// {
// 	const int	px = game->player->player_x / PIXEL;
// 	const int	py = game->player->player_y / PIXEL;
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
//
// 	i = py - MINI_MAP_RADIUS;
// 	game->minimap_img = make_image(game, (MINI_MAP_RADIUS * 2 + 1) * MINI_MAP_PIXEL,
// 			(MINI_MAP_RADIUS * 2 + 1) * MINI_MAP_PIXEL);
// 	y = 0;
// 	while (i <= py + MINI_MAP_RADIUS)
// 	{
// 		x = 0;
// 		j = px - MINI_MAP_RADIUS;
// 		while (j <= px + MINI_MAP_RADIUS)
// 		{
// 			if (i < 0 || i > game->map_len_h - 1 || j < 0 || j > ft_strlen(game->map[i]) - 1 || game->map[i][j] == ' ')
// 				draw_square_on_img(game->minimap_img, x, y, 0x00333333);
// 			else if (game->map[i][j] == '1')
// 				draw_square_on_img(game->minimap_img, x, y, 0x00FFFFFF);
// 			else if (game->map[i][j] == 'D')
// 				draw_square_on_img(game->minimap_img, x, y, 0x00D0D7FE);
// 			else
// 				draw_square_on_img(game->minimap_img, x, y, 0x00030303);
// 			x += MINI_MAP_PIXEL;
// 			j++;
// 		}
// 		y += MINI_MAP_PIXEL;
// 		i++;
// 	}
// }




static void	full_map_update(t_game *game)
{
	const int  px = game->player->player_x / PIXEL;
    const int   py = game->player->player_y / PIXEL;

	if (game->full_map == FALSE)
        game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2 + 1) + game->full_map_x) * MINI_MAP_PIXEL,
        ((MINI_MAP_RADIUS * 2 + 1) + game->full_map_y) * MINI_MAP_PIXEL);
	if (game->full_map == TRUE)
        game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2) + game->full_map_x) * MINI_MAP_PIXEL,
        ((MINI_MAP_RADIUS * 2) + game->full_map_y) * MINI_MAP_PIXEL);
    if (game->full_map == MAP_SIZE_UP)
    {
        if (game->full_map_x <= game->map_len_w - 1 - MINI_MAP_RADIUS * 2)
            game->full_map_x++;
        if (game->full_map_y <= game->map_len_h - 1 - MINI_MAP_RADIUS * 2)
            game->full_map_y++;
        game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2) + game->full_map_x) * MINI_MAP_PIXEL,
        ((MINI_MAP_RADIUS * 2) + game->full_map_y) * MINI_MAP_PIXEL);
		if (game->full_map_x == game->map_len_w - 1 - MINI_MAP_RADIUS * 2)
			game->full_map = TRUE;
    }
    if (game->full_map == MAP_SIZE_DOWN)
    {
        if (game->full_map_x > 0)
            game->full_map_x--;
        if (game->full_map_y > 0)
            game->full_map_y--;
        game->minimap_img = make_image(game, ((MINI_MAP_RADIUS * 2 + 1) + game->full_map_x) * MINI_MAP_PIXEL,
        ((MINI_MAP_RADIUS * 2 + 1) + game->full_map_y) * MINI_MAP_PIXEL);
		if (game->full_map_x == 0)
			game->full_map = FALSE;
    }
}

void	render_mini_map_center(t_game *game)
{
	const int  px = game->player->player_x / PIXEL;
    const int   py = game->player->player_y / PIXEL;
    int i;
    int j;
    int x;
    int y;

    full_map_update(game); 
	if (game->full_map == TRUE)
        i = 0;
	else if (game->full_map == MAP_SIZE_DOWN)
	{
		i = 0;
		if (game->full_map_y + (MINI_MAP_RADIUS) < py)
			i += py - (game->full_map_y + MINI_MAP_RADIUS);
			
	// game->full_map_y = game->map_len_h - 1 - MINI_MAP_RADIUS * 2
	}
	else if (game->full_map == MAP_SIZE_UP)
	{
		i = py - (MINI_MAP_RADIUS);
		if (i - game->full_map_y >= 0)
			i -= game->full_map_y;
		else
			i = 0;
	}
	else
    	i = py - (MINI_MAP_RADIUS + game->full_map_y);
    y = 0;
    while (i <= py + MINI_MAP_RADIUS + game->full_map_y)
    {
        x = 0;
		if (game->full_map == TRUE)
            j = 0;
		else if (game->full_map == MAP_SIZE_DOWN)
		{
			j = 0;
			if (game->full_map_x + MINI_MAP_RADIUS < px)
				j += px - game->full_map_x - MINI_MAP_RADIUS;
		}
		else if (game->full_map == MAP_SIZE_UP)
		{
			j = px - MINI_MAP_RADIUS;
			if (j - game->full_map_x > 0)
				j -= game->full_map_x;
			else
				j = 0;
		}
		else
    	    j = px - (MINI_MAP_RADIUS + game->full_map_x);
        while (j <= px + MINI_MAP_RADIUS + game->full_map_x)
        {
            if (i < 0 || i > game->map_len_h - 1 || j < 0 || j > ft_strlen(game->map[i]) - 1 || game->map[i][j] == ' ')
                draw_square_on_img(game->minimap_img, x, y, 0x00333333);
            else if (game->map[i][j] == '1')
                draw_square_on_img(game->minimap_img, x, y, 0x00FFFFFF);
            else if (game->map[i][j] == '1')
                draw_square_on_img(game->minimap_img, x, y, 0x00D0D7FE);
            else
                draw_square_on_img(game->minimap_img, x, y, 0x00030303);
            x += MINI_MAP_PIXEL;
            j++;
        }
        y += MINI_MAP_PIXEL;
        i++;
    }
}
