#include "../includes_bonus/cub3d_bonus.h"

static int	check_bonus_symbol(t_god *god, int row, int col, int value)
{
	if (value == '2')
	{
		if (put_sprite(god, row, col, T_S) == ERROR)
			return (exit_error(god, ERROR, "SPRITE ERROR!"));
	}
	else if (value == 'F')
	{
		if (put_sprite(god, row, col, T_SF) == ERROR)
			return (exit_error(god, ERROR, "SPRITE ERROR!"));
	}
	else if (value == '3')
	{
		if (is_space_around_position(god, row, col)
			== ERROR || set_door(god, row, col) == ERROR)
			return (exit_error(god, ERROR, "door error!"));
	}
	else if (ft_strchr("05", value) != NULL)
	{
		if (is_space_around_position(god, row, col) == ERROR)
			return (exit_error(god, ERROR, "Empty space next to 0!"));
	}
	return (SUCCESS);
}

static int	check_symbol2(t_god *god, int row, int col)
{
	char	value;

	value = god->parse.map[row][col];
	if (ft_strchr("NSEW", value) != NULL)
	{
		if (is_space_around_position(god, row, col) == ERROR
			|| set_angle(god, row, col) == ERROR)
			return (exit_error(god, ERROR,
					"Empty space next to NSEW!"));
		god->parse.is_d = TRUE;
	}
	else if (ft_strchr("2305F", value) != NULL)
		if (check_bonus_symbol(god, row, col, value) == ERROR)
			return (ERROR);
	return (SUCCESS);
}

static int	check_symbol(t_god *god)
{
	int		row;
	int		col;

	row = -1;
	while (god->parse.map[++row] != NULL)
	{
		col = -1;
		while (god->parse.map[row][++col] != '\0')
		{
			if (check_symbol2(god, row, col) == ERROR)
				return (ERROR);
		}
	}
	if (god->parse.is_d != TRUE)
		return (exit_error(god, ERROR, "no NSEW!"));
	if (god->sprite_cnt < SPRITE_COUNT)
		return (exit_error(god, ERROR, "not enough sprites!"));
	return (SUCCESS);
}

static int	check_type(t_god *god)
{
	int	i;

	if (!(god->parse.row) || !(god->parse.col))
		return (exit_error(god, ERROR, "map error!"));
	if ((god->parse.ceiling_color == NO_COLOR)
		|| (god->parse.floor_color == NO_COLOR))
		return (exit_error(god, ERROR,
				"Ceiling and Floor color wasn't parsed!"));
	if (check_tex(god) == ERROR)
		return (exit_error(god, ERROR,
				"NO,SO,EA,WE direction must be different each other!"));
	i = -1;
	while (++i < TEXTURE_COUNT)
		if ((god->parse.tex[i].tex_path) == NULL)
			return (exit_error(god, ERROR, "Some texture weren't parsed!"));
	return (SUCCESS);
}

int	check_parsing_value(t_god *god)
{
	if (check_type(god) == ERROR)
		return (exit_error(god, ERROR, "NOT PARSDED_TYPE"));
	if (check_symbol(god) == ERROR)
		return (exit_error(god, ERROR, "NOT PARSDED_MAP"));
	return (SUCCESS);
}
