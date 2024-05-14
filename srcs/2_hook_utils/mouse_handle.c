/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 07:23:35 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 10:06:13 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	*sound_theme(void	*game)
{
	t_game *sound_game;// = (t_game *)malloc(sizeof(t_game));
	sound_game = (t_game *)game;

	while (1)
	{
		system("afplay resources/sound/theme.mp3 &");
		printf("sound_game->pthread_kill : %d\n", sound_game->pthread_kill);
		usleep(171000000);
		if (sound_game->player->player_rad == TRUE)
			pthread_exit(NULL);
	}
	return (0);
}

void	*sound_handle(void *game)
{
	t_game	*sound_game;

	//sound_game = (t_game *)malloc(sizeof(t_game));
	sound_game =  (t_game *)game;

	while (1)
	{
		//if (pthread_equal(pthread_self(), sound_game->sound_test))
		//	pthread_exit(NULL);
		if (sound_game->player->shot == TRUE && sound_game->player->shot_sound == TRUE)
		{
			system("afplay resources/sound/shotgun.wav &");
			usleep(100);
			sound_game->player->shot_sound = FALSE;
		}
	}
	return (0);
}

int	mouse_handle(int button, int x, int y, t_game *game)
{
	game->mouse->mouse_x = x;
	game->mouse->mouse_x = y;
	if (button == 1 && game->player->shot == FALSE)
	{
		game->player->shot = TRUE;
		game->player->shot_sound = TRUE;
		game->player->shot_time = 0;
		game->player->shot_frame = 0;
	}
	return (0);
}
