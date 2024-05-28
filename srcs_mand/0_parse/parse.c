/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:57:25 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:41:50 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_mand/header_mand.h"

int	check_color(int type, t_parse *parse, char *line)
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

/**
 * @brief
 * 받아온 타입을 기준으로 path를 저장할 것인지 floor 와 ceiling 색상을 파싱할것인지 아니면 그냥 맵으로 넣을것인지 분기
 * @param parse
 * @param g_ret
 * @param type
 * @param line
 * @return int
 */
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
	}
	else
	{
		parse->temp_map = update_map(parse->temp_map, line);
		if (g_ret == 0 && parse_map(parse) == FAILURE)
			return (free_memory_return(line, FAILURE));
	}
	return (free_memory_return(line, SUCCESS));
}

/**
 * @brief
 * 맵파일에서 처음 나오는 텍스트 지정과 천장 바닥 색상일때의 타입과 그 외의 Map파일에 있어도 되는 글자인지 확인하는 함수
 * @param line
 * @return int
 */
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

/**
 * @brief
 * .cub 파일의 확장자 및 오픈 체크 후 파싱하는 함수
 * @param game
 * @param cub_file_path
 * @return int
 */
int	parse_file(t_game *game, const char *cub_file_path)
{
	t_single_parse	p;

	if (!(is_cub_file(cub_file_path)))
		error_exit("NOT \".cub\" FILE");
	p.fd = open(cub_file_path, O_RDONLY);
	if (p.fd < 0)
		error_exit("WRONG FILE PATH OR CAN'T OPEN");
	p.gnl_ret = get_next_line(p.fd, &p.line);
	while (p.gnl_ret > 0)
	{
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
