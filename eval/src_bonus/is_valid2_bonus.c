#include "cub3d_bonus.h"

void	is_in_door(t_god *god)
{
	int	row;
	int	col;

	if (is_door(god, god->player.x, god->player.y) == OPEN_DOOR)
	{
		row = -1;
		while (++row < god->map.window_height)
		{
			col = -1;
			while (++col < god->map.window_width)
			{
				if (god->img.data[god->map.window_width * row + col]
					== NO_COLOR)
					god->img.data[god->map.window_width * row + col] = 0x000000;
			}
		}
	}
}

void	is_in_room(t_god *god)
{
	int	x;
	int	y;

	x = (int)floor(god->player.x / TILE_SIZE);
	y = (int)floor(god->player.y / TILE_SIZE);
	if (god->map.map[y][x] == '5')
		god->door.in_room = 4;
	else
		god->door.in_room = 0;
}

int	is_map_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (find_char("01235NSEWF ", line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_cub_file(const char *cub_file_path)
{
	int	file_len;
	int	is_same;

	file_len = ft_strlen(cub_file_path);
	if (ft_strncmp(cub_file_path + file_len - 4, ".cub", 4) == 0)
		is_same = TRUE;
	else
		is_same = FALSE;
	return (is_same);
}

int	is_space_around_position(t_god *god, int row, int col)
{
	if (row <= 0 || row >= god->parse.row || col <= 0 || col >= god->parse.col)
		return (ERROR);
	else if (god->parse.map[row][col + 1] == ' '
		|| god->parse.map[row][col + 1] == '\0'
		|| god->parse.map[row][col - 1] == ' ')
		return (ERROR);
	else if ((int)ft_strlen(god->parse.map[row - 1]) <= col
		|| god->parse.map[row - 1][col] == ' '
		|| god->parse.map[row - 1][col] == '\0')
		return (ERROR);
	else if ((int)ft_strlen(god->parse.map[row + 1]) <= col
		|| god->parse.map[row + 1][col] == ' '
		|| god->parse.map[row + 1][col] == '\0')
		return (ERROR);
	return (SUCCESS);
}
