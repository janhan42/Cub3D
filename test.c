#include "includes/header.h"
#include <math.h>
#include <stdio.h>

int color_spoid(int x, int y, t_img *texture)
{
	return *(int *)(texture->addr + (y * texture->line_length + x * (texture->bit_per_pixel / 8)));
}

void put_pixel_on_img(t_img *img, int x, int y, int color) {
    *(int *)(img->addr + (y * img->line_length + x * (img->bit_per_pixel / 8))) = color;
}

void draw_wall_slice(t_game *game, int screen_x, double ray_distance, int texture_x) {
    double wall_height = 600 / ray_distance;  // 예시: 화면 높이 600
    double step = game->texture->height / wall_height;
    double texture_pos = 0;

    int start = (300 - wall_height / 2);
    if (start < 0)
        start = 0;
    int end = (300 + wall_height / 2);
    if (end >= 600)
        end = 599;

    for (int y = start; y < end; y++) {
        int tex_y = (int)texture_pos & (game->texture->height - 1);
        texture_pos += step;
        int color = color_spoid(texture_x, tex_y, game->texture);
        put_pixel_on_img(game->render->img, screen_x, y, color);
    }
}

int main() {
    t_game game;
    game.mlx = mlx_init();
    game.mlx_win = mlx_new_window(game.mlx, 800, 600, "Raycasting with Texture Mapping");
	game.texture = malloc(sizeof(t_img ));
    game.texture->img = mlx_xpm_file_to_image(game.mlx, "path/to/texture->xpm", &game.texture->width, &game.texture->height);
    game.texture->addr = mlx_get_data_addr(game.texture->img, &game.texture->bit_per_pixel, &game.texture->line_length, &game.texture->endian);
	game.render = malloc(sizeof(t_img));
    game.render->img = mlx_new_image(game.mlx, 800, 600);
    game.render->addr = mlx_get_data_addr(game.render->img, &game.render->bit_per_pixel, &game.render->line_length, &game.render->endian);
    game.render->width = 800;
    game.render->height = 600;

    game.player->player_x = 1.5;
    game.player->player_y = 1.5;
    game.player->player_rad = M_PI / 4;

    // 레이캐스팅 및 텍스처 매핑 루프 (간단한 예제)
    for (int x = 0; x < 800; x++) {
        double ray_angle = (game.player->player_rad - M_PI / 6) + (x * M_PI / 3 / 800);
        double ray_x = game.player->player_x;
        double ray_y = game.player->player_y;
        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);
        double distance = 0;

        while (1) {
            ray_x += ray_dir_x * 0.1;
            ray_y += ray_dir_y * 0.1;
            if (ray_x >= 2 || ray_y >= 2 || ray_x <= 0 || ray_y <= 0) {
                break; // 벽에 닿았다고 가정
            }
            distance += 0.1;
        }

        int texture_x = (int)(ray_x * game.texture->width) % game.texture->width;
        draw_wall_slice(&game, x, distance, texture_x);
    }

    mlx_put_image_to_window(game.mlx, game.mlx_win, game.render->img, 0, 0);
    mlx_loop(game.mlx);
    return 0;
}
