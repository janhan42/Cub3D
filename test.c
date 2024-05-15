#include "includes/header.h"

// resources/sprites/weapon/shotgun/0.xpm
typedef struct s_image {
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    int width;
    int height;
} t_image;

void scale_texture(t_image *src, t_image *dst, float scale_factor) {
	int x, y;
	int new_x, new_y;
	int color;
	float inv_scale = 1.0 / scale_factor;

	for (new_y = 0; new_y < dst->height; new_y++) {
		for (new_x = 0; new_x < dst->width; new_x++) {
			x = (int)(new_x * inv_scale);
			y = (int)(new_y * inv_scale);
			if (x >= src->width || y >= src->height)
				continue;
			color = *(int *)(src->data + (y * src->size_line + x * (src->bpp / 8)));
			*(int *)(dst->data + (new_y * dst->size_line + new_x * (dst->bpp / 8))) = color;
		}
	}
}

int main() {
    void *mlx;
    void *win;
    t_image src_img;
    t_image dst_img;
    float scale_factor = 0.2; // Example scale factor

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Texture Scaling");

	// Load your source texture
	src_img.img = mlx_xpm_file_to_image(mlx, "resources/sprites/weapon/shotgun/0.xpm", &src_img.width, &src_img.height);
	src_img.data = mlx_get_data_addr(src_img.img, &src_img.bpp, &src_img.size_line, &src_img.endian);

	// Create destination image with scaled dimensions
	dst_img.width = (int)(src_img.width * scale_factor);
	dst_img.height = (int)(src_img.height * scale_factor);
	dst_img.img = mlx_new_image(mlx, dst_img.width, dst_img.height);

	dst_img.data = mlx_get_data_addr(dst_img.img, &dst_img.bpp, &dst_img.size_line, &dst_img.endian);

	// Scale the texture
	scale_texture(&src_img, &dst_img, scale_factor);

	// Display the scaled image
	mlx_put_image_to_window(mlx, win, dst_img.img, 0, 0);
	mlx_loop(mlx);

	return 0;
}
