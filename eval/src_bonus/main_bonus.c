#include "cub3d_bonus.h"

static void	floor_ceiling_init(t_god *god)
{
	god->parse.floor_color = NO_COLOR;
	god->parse.ceiling_color = NO_COLOR;
}

static void	ft_init(t_god *god)
{
	god->map.map_rows = god->parse.row;
	god->map.map_cols = god->parse.col;
	make_even_value(&god->map.map_rows, &god->map.map_cols);
	god->map.window_height = W_HEIGHT * TILE_SIZE;
	god->map.window_width = W_WIDTH * TILE_SIZE;
	god->map.ray_count = god->map.window_width / WALL_STRIP_WIDTH;
	init_map_malloc(god);
	god->rray = (t_rray *)malloc(sizeof(t_rray) * (god->map.ray_count));
	god->mlx = mlx_init();
	god->win = mlx_new_window(god->mlx, god->map.window_width,
			god->map.window_height, "mlx_title");
	god->img.ptr = mlx_new_image(god->mlx,
			god->map.window_width, god->map.window_height);
	god->img.data = (int *)mlx_get_data_addr(god->img.ptr, &(god->img.bpp),
			&(god->img.line_size), &(god->img.endian));
}

int	main(int argc, char **argv)
{
	t_god	god;

	if (argc != 2)
		return (exit_error(&god, ERROR, "WRONG ARGUMENT COUNT!"));
	ft_memset(&god, 0, sizeof(t_god));
	floor_ceiling_init(&god);
	if (parse_file(&god, argv[1]) == ERROR)
		return (exit_error(&god, ERROR, "FAIL PARSING!"));
	if (check_parsing_value(&god) == ERROR)
		return (exit_error(&god, ERROR, "WRONG PARSING VALUE SAVED!"));
	ft_init(&god);
	load_texture(&god);
	render_master(&god);
	mlx_loop(god.mlx);
	free_texture_array(&god);
	return (0);
}
