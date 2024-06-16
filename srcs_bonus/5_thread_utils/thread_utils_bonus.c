/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:24:00 by janhan            #+#    #+#             */
/*   Updated: 2024/06/16 17:51:15 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"
#include <unistd.h>

void	*sound_theme(void	*game)
{
	t_game	*sound_game;

	sound_game = (t_game *)game;
	while (1)
	{
		system("afplay resources/sound/theme.mp3 &");
		usleep(171000000);
		if (sound_game->player->player_rad == TRUE)
			pthread_exit(NULL);
	}
	return (0);
}

void	*sound_handle(void *game)
{
	t_game	*sound_game;

	sound_game = (t_game *)game;
	while (1)
	{
		if (sound_game->player->shot == TRUE
			&& sound_game->player->shot_sound == TRUE)
		{
			system("afplay resources/sound/shotgun.wav &");
			usleep(100);
			sound_game->player->shot_sound = FALSE;
		}
	}
	return (0);
}

void	*sound_npc(void *game)
{
	t_game	*sound_game;

	sound_game = (t_game *)game;
	while (1)
	{
		if (sound_game->player->npc_hit == TRUE
			&& sound_game->npc_sound_flag == TRUE)
		{
			sound_game->npc_sound = FALSE;
			system("afplay resources/sound/npc_pain.wav &");
			usleep(100);
		}
		if (sound_game->npc_death_flag == TRUE)
		{
			system("afplay resources/sound/npc_death.wav &");
			sound_game->npc_death_flag = FALSE;
		}
		if (sound_game->npc_attack_flag == TRUE)
		{
			system("afplay resources/sound/npc_attack.wav &");
			sound_game->npc_attack_flag = FALSE;
		}
	}
	return (0);
}
