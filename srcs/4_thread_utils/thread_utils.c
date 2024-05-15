/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:24:00 by janhan            #+#    #+#             */
/*   Updated: 2024/05/14 20:24:41 by janhan           ###   ########.fr       */
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
