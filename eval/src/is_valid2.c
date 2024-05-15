#include "cub3d.h"

int	is_map_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (find_char("01NSEW ", line[i]) == FALSE)
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
