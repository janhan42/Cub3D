#include "cub3d_bonus.h"

static int	*load_image_malloc(t_god *god, char *path, t_img *img, int i)
{
	int		col;
	int		row;
	int		*result;

	img->ptr = mlx_xpm_file_to_image(god->mlx,
			path, &img->img_width, &img->img_height);
	if (!(img->ptr))
		exit_error(god, ERROR, "WRONG TEXTURE!");
	god->parse.tex[i].width = img->img_width;
	god->parse.tex[i].height = img->img_height;
	img->data = (int *)mlx_get_data_addr(img->ptr,
			&img->bpp, &img->line_size, &img->endian);
	result = (int *)malloc(sizeof(int) * (img->img_width * img->img_height));
	row = -1;
	while (++row < img->img_height)
	{
		col = -1;
		while (++col < img->img_width)
			result[img->img_width * row + col]
				= img->data[img->img_width * row + col];
	}
	mlx_destroy_image(god->mlx, img->ptr);
	return (result);
}

void	load_texture(t_god *god)
{
	int		i;
	t_img	img;

	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		god->parse.tex[i].texture
			= load_image_malloc(god, god->parse.tex[i].tex_path, &img, i);
		free_memory(god->parse.tex[i].tex_path);
	}
}
