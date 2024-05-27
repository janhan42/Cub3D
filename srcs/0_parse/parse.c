/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:57:25 by janhan            #+#    #+#             */
/*   Updated: 2024/05/27 19:47:53 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_blank_line(char *line)
{
	int	i;

	if (line[0] == '\0')
		return (TRUE);
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	find_char(const char *value, char c)
{
	while (*value != '\0')
	{
		if (*value == c)
			return (TRUE);
		value++;
	}
	return (FALSE);
}

int	is_map_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (find_char("01D", line[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
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
	return (FAILURE);
}

int	check_color(int type, t_parse *parse, char *line)
{
	if (type == T_CEIL)
	{
		if (parse->is_c == TRUE || parse_color(&parse->ceiling_color, line) == FAILURE)
			return (FAILURE);
		parse->is_c = TRUE;
	}
	else if (type == T_FLOOR)
	{
		if (parse->is_f == TRUE || parse_color(&parse->floor_color, line) == FAILURE)
			return (FAILURE);
		parse->is_f = TRUE;
	}
	return (SUCCESS);
}

static int	do_parsing(t_parse *parse, int g_ret, int type, char *line)
{
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
		parse->is_f = TRUE;
	}
	else
	{
		parse->temp_map = update_map(parse->temp_map, line);
		if (g_ret == 0 && parse_map(parse) == FAILURE)
			return (free_memory_return(line, FAILURE));
	}
	return (free_memory_return(line, SUCCESS));
}
//printf("parse->row [%d] parse->col [%d]\n", parse->row, parse->col);
int	parse_file(t_game *game, const char *cub_file_path)
{
	t_single_parse	p;

	if (is_cub_file(cub_file_path) == FALSE)
		error_exit("NOT \".cub\" FILE");
	p.fd = open(cub_file_path, O_RDONLY);
	if (p.fd < 0)
		error_exit("WRONG FILE PATH OR CAN'T OPEN");
	p.gnl_ret = get_next_line(p.fd, &p.line);
	while (p.gnl_ret > 0)
	{
		printf("1\n");
		p.parse_type = check_parse_type(p.line);
		if (p.parse_type == FAILURE && is_blank_line(p.line))
			free(p.line);
		else if (p.parse_type == FAILURE)
			error_exit("WRONG PARSE TYPE");
		else if (do_parsing(&game->parse, p.gnl_ret, p.parse_type, p.line)
			== FAILURE)
			return (FAILURE);
		p.gnl_ret = get_next_line(p.fd, &p.line);
	}
	do_parsing(&game->parse, p.gnl_ret, p.parse_type, p.line);
	close(p.fd);
	return (SUCCESS);
}
