#include "cub3d.h"

int	parse_color2(int *cf, char **color_malloc)
{
	int	i;
	int	x;
	int	color;

	i = -1;
	while (++i < 3)
	{
		if (color_malloc[i] == NULL)
			return (ERROR);
		*cf *= 256;
		x = -1;
		color = 0;
		while (color_malloc[i][++x] != '\0')
		{
			if (ft_isdigit(color_malloc[i][x]) == FALSE)
				return (ERROR);
			color = color * 10 + color_malloc[i][x] - '0';
		}
		if (color > 255 || color < 0)
			return (ERROR);
		*cf += color;
	}
	return (SUCCESS);
}

int	parse_color(int *cf, char *line)
{
	char	**color_malloc;

	*cf = 0;
	while (is_upper(*line) == TRUE)
		line++;
	while (is_space(*line) == TRUE)
		line++;
	color_malloc = ft_split(line, ',');
	if (color_malloc == NULL || color_malloc[3] != NULL)
		return (ERROR);
	if (parse_color2(cf, color_malloc) == ERROR)
		return (ERROR);
	free_array_memory((void **)color_malloc, 3);
	return (SUCCESS);
}

char	*parse_path_malloc(char *line)
{
	char	*temp_malloc;

	while (is_upper(*line) == TRUE)
		line++;
	while (is_space(*line) == TRUE)
		line++;
	temp_malloc = ft_strdup(line);
	if (temp_malloc == NULL)
		return (NULL);
	return (temp_malloc);
}

int	parse_map(t_parse *parse)
{
	int	row;
	int	col;

	parse->map = ft_split(parse->temp_map, '\n');
	if (parse->map == NULL)
		return (free_memory_return(parse->temp_map, ERROR));
	row = -1;
	col = 0;
	while (parse->map[++row] != NULL)
		if (ft_strlen(parse->map[row]) > col)
			col = ft_strlen(parse->map[row]);
	parse->row = row;
	parse->col = col;
	return (free_memory_return(parse->temp_map, SUCCESS));
}
