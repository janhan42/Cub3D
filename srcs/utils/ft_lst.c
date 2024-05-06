/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:18:55 by janhan            #+#    #+#             */
/*   Updated: 2024/05/04 13:39:06 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map	*ft_lst_last(t_map *lst)
{
	if (lst == NULL)
		return (lst);
	if (lst->next == NULL)
		return (lst);
	return (ft_lst_last(lst->next));
}

void	ft_lst_del_one(t_map *lst, void (*del)(void*))
{
	if (lst)
	{
		if (lst->content)
			del(lst->content);
		free(lst);
	}
}

void	ft_lst_clear(t_map **lst, void (*del)(void*))
{
	t_map	*temp;

	if (del)
	{
		while (*lst)
		{
			temp = *lst;
			*lst = (*lst)->next;
			ft_lst_del_one(temp, del);
		}
	}
}

void	ft_lst_add_back(t_map **lst, t_map *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_lst_last(*lst)->next = new;
}

void	ft_lst_add_front(t_map **lst, t_map *new)
{
	new->next = *lst;
	*lst = new;
}
