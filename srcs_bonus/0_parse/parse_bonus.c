/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:57:25 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:49:50 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

static int	check_color(int type, t_parse *parse, char *line)
{
	if (type == T_CEIL)
	{
		if (parse->is_c == TRUE
			|| parse_color(&parse->ceiling_color, line) == FAILURE)
			return (FAILURE);
		parse->is_c = TRUE;
	}
	else if (type == T_FLOOR)
	{
		if (parse->is_f == TRUE
			|| parse_color(&parse->floor_color, line) == FAILURE)
			return (FAILURE);
		parse->is_f = TRUE;
	}
	return (SUCCESS);
}

static int	do_parsing(t_parse *parse, int g_ret, int type, char *line)
{
	g_ret++;
	(void)g_ret;
	if (T_NO <= type && type <= T_EA)
	{
		if (parse->tex[type].tex_path)
			return (free_memory_return(line, FAILURE));
		parse->tex[type].tex_path = parse_path_malloc(line);
	}
	else if (type == T_FLOOR || type == T_CEIL)
	{
		if (check_color(type, parse, line) == FAILURE)
			return (free_memory_return(line, FAILURE));
	}
	return (free_memory_return(line, SUCCESS));
}

int	check_parse_type(char *line)
{
	if (line == NULL)
		return (EMPTY);
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
	else if (line[0] == '\n' && line[1] == '\0')
		return (EMPTY);
	else if (is_map_valid(line))
		return (T_MAP);
	return (FAILURE);
}

static int	read_map(t_game *game, char *s, int fd)
{
	char	*one_line;
	char	*tmp_map;
	char	*joined_str;
	int		type;

	tmp_map = s;
	one_line = get_next_line(fd);
	type = check_parse_type(one_line);
	while (one_line && type == T_MAP)
	{
		joined_str = ft_strjoin(tmp_map, one_line);
		free(one_line);
		free(tmp_map);
		tmp_map = joined_str;
		one_line = get_next_line(fd);
		type = check_parse_type(one_line);
	}
	close(fd);
	if (one_line != NULL)
	{
		free(one_line);
		return (FAILURE);
	}
	return (parse_map(&game->parse, tmp_map));
}

int	parse_file(t_game *game, const char *cub_file_path)
{
	t_single_parse	p;

	p.fd = open(cub_file_path, O_RDONLY);
	if (p.fd < 0)
		error_exit("WRONG FILE PATH OR CAN'T OPEN");
	p.line = get_next_line(p.fd);
	p.parse_type = check_parse_type(p.line);
	while (p.line && p.parse_type != T_MAP)
	{
		if ((p.parse_type == FAILURE && is_blank_line(p.line))
			|| p.parse_type == EMPTY)
			free(p.line);
		else if (p.parse_type == FAILURE)
			error_exit("WRONG PARSE TYPE");
		else if (do_parsing(&game->parse, p.gnl_ret, p.parse_type, p.line)
			== FAILURE)
			error_exit("do_parsing failed");
		p.line = get_next_line(p.fd);
		p.parse_type = check_parse_type(p.line);
	}
	if (p.parse_type == T_MAP)
		return (read_map(game, p.line, p.fd));
	close(p.fd);
	return (SUCCESS);
}
