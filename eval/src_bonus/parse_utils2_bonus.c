#include "cub3d_bonus.h"

static int	check_parse2_type(char *line)
{
	if (line[0] == 'N' && line[1] == 'R')
		return (TI_NO);
	else if (line[0] == 'S' && line[1] == 'R')
		return (TI_SO);
	else if (line[0] == 'W' && line[1] == 'R')
		return (TI_WE);
	else if (line[0] == 'E' && line[1] == 'R')
		return (TI_EA);
	else if (line[0] == 'D' && line[1] == 'O')
		return (T_DO);
	else if (line[0] == 'D' && line[1] == 'C')
		return (T_DC);
	else if (line[0] == 'S' && line[1] == ' ')
		return (T_S);
	else if (line[0] == 'S' && line[1] == 'F')
		return (T_SF);
	else if (line[0] == 'S' && line[1] == 'T')
		return (T_ST);
	else if (line[0] == 'S' && line[1] == 'U')
		return (T_SU);
	else if (line[0] == 'S' && line[1] == 'V')
		return (T_SV);
	return (T_ERROR);
}

int	check_parse_type(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (T_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (T_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (T_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (T_EA);
	else if (line[0] == 'F' && line[1] == ' ')
		return (T_FLOOR);
	else if (line[0] == 'C' && line[1] == ' ')
		return (T_CEIL);
	else if (is_map_valid(line))
		return (T_MAP);
	else
		return (check_parse2_type(line));
	return (T_ERROR);
}

int	put_sprite(t_god *god, int row, int col, int symbol)
{
	int	cnt;

	cnt = god->sprite_cnt;
	if (is_space_around_position(god, row, col) == ERROR)
		return (exit_error(god, ERROR, "space around sprite!"));
	if (cnt >= SPRITE_COUNT)
		return (exit_error(god, ERROR, "Too much sprite!"));
	god->sprite[cnt].x = col * TILE_SIZE + TILE_SIZE / 2;
	god->sprite[cnt].y = row * TILE_SIZE + TILE_SIZE / 2;
	god->sprite[cnt].exist = TRUE;
	god->sprite[cnt].symbol = symbol;
	god->sprite_cnt++;
	return (SUCCESS);
}
