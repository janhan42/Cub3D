#include "cub3d.h"

void	free_memory(void *memory)
{
	if (memory != NULL)
	{
		free(memory);
		memory = NULL;
	}
}

int	free_memory_return(void *memory, int return_code)
{
	free_memory(memory);
	return (return_code);
}

void	free_texture_array(t_god *god)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		free_memory(god->parse.tex[i].texture);
		i++;
	}
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
