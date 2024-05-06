/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:05:10 by janhan            #+#    #+#             */
/*   Updated: 2023/12/12 13:50:42 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	init_lstmap(t_list *lst, void*(*f)(void *), void(*del)(void *),
t_list **new)
{
	*new = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (1);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void*(*f)(void *), void(*del)(void *))
{
	t_list	*new;
	t_list	*temp_cpy;
	void	*new_content;

	if (init_lstmap(lst, f, del, &new) == 1)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		if (new_content == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		temp_cpy = ft_lstnew(new_content);
		if (temp_cpy == NULL)
		{
			del(new_content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp_cpy);
		lst = lst->next;
	}
	return (new);
}
