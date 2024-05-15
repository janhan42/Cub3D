#include "cub3d.h"

static int	check_col(int type, t_parse *parse, char *line)
{
	if (type == T_CEIL)
	{
		if (parse->is_c == TRUE || parse_color(&parse->ceiling_color, line)
			== ERROR)
			return (ERROR);
		parse->is_c = TRUE;
	}
	else if (type == T_FLOOR)
	{
		if (parse->is_f == TRUE || parse_color(&parse->floor_color, line)
			== ERROR)
			return (ERROR);
		parse->is_f = TRUE;
	}
	return (SUCCESS);
}

static int	do_parsing(t_parse *parse, int g_ret, int type, char *line)
{
	if (type >= T_NO && type <= T_EA)
	{
		if (parse->tex[type].tex_path)
			return (free_memory_return(line, ERROR));
		parse->tex[type].tex_path = parse_path_malloc(line);
	}
	else if (type == T_CEIL || type == T_FLOOR)
	{
		if (check_col(type, parse, line) == ERROR)
			return (free_memory_return(line, ERROR));
	}
	else
	{
		parse->temp_map = update_map_malloc(parse->temp_map, line);
		if (g_ret == 0 && parse_map(parse) == ERROR)
			return (free_memory_return(line, ERROR));
	}
	return (free_memory_return(line, SUCCESS));
}

static int	is_blank_line(char *line)
{
	int		i;

	if (line[0] == '\0')
		return (TRUE);
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	parse_file(t_god *god, const char *cub_file_path)
{
	t_dpable_parse	p;

	if (!(is_cub_file(cub_file_path)))
		return (exit_error(god, ERROR, "NOT \".cub\" FILE"));
	p.fd = open(cub_file_path, O_RDONLY);
	if (p.fd < 0)
		return (exit_error(god, ERROR, "WRONG FILE PATH OR CAN'T OPEN!"));
	p.gnl_ret = get_next_line(p.fd, &p.line);
	while (p.gnl_ret > 0)
	{
		p.parse_type = check_parse_type(p.line);
		if (p.parse_type == T_ERROR && is_blank_line(p.line))
			free(p.line);
		else if (p.parse_type == T_ERROR)
			return (exit_error(god, ERROR, "WRONG PARSE TYPE"));
		else if (do_parsing(&god->parse, p.gnl_ret, p.parse_type, p.line)
			== ERROR)
			return (ERROR);
		p.gnl_ret = get_next_line(p.fd, &p.line);
	}
	do_parsing(&god->parse, p.gnl_ret, p.parse_type, p.line);
	close(p.fd);
	return (SUCCESS);
}
