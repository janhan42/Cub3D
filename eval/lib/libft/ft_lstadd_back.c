#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *a)
{
	if (*lst == 0)
		*lst = a;
	else
		(ft_lstlast(*lst))->next = a;
}
