/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:54:40 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:26:25 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

void	free_memory(void *memory)
{
	if (memory == NULL)
		return ;
	free(memory);
	memory = NULL;
}

int	free_memory_return(void *memory, int return_code)
{
	free_memory(memory);
	return (return_code);
}

void	free_array_memory(void **memory, int index)
{
	if (memory == NULL)
		return ;
	while (--index >= 0)
		free_memory(memory[index]);
	free_memory(memory);
	memory = NULL;
}

void	str_free(char *str)
{
	free(str);
	str = NULL;
}
