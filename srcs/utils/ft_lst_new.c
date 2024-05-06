/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:16:24 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 10:18:08 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map	*ft_lst_new(void *content)
{
	t_map	*new;

	new = NULL;
	new = (t_map *)malloc(sizeof(t_map));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lst_size(t_map *lst)
{
	if (!lst)
		return (0);
	return (ft_lst_size(lst->next) + 1);
}
