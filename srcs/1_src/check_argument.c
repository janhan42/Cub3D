/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:53:59 by janhan            #+#    #+#             */
/*   Updated: 2024/05/02 15:14:31 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_argument(int ac, char **av)
{
	char	*file;
	size_t	len;

	if (ac != 2)
		error_exit("Invalid argument");
	file = av[1];
	len = ft_strlen(file);
	if (len <= 4 || ft_strncmp(file + len - 4, ".cub", 4) \
		|| file[len - 5] == '/')
		error_exit("Invalid filename");
}
