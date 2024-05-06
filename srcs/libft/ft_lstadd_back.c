/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:54:06 by janhan            #+#    #+#             */
/*   Updated: 2024/01/02 08:02:38 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*cursor;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		cursor = *lst;
		while (cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = new_node;
	}
}
