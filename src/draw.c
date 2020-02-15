#include "../inc/fractol.h"

void	draw_menu(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 20, 0xf54242, "Commands:");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 40, 0xf54242, "exit esc");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 60, 0xf54242, "iterations up 1");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 80, 0xf54242, "iterations down 2");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 100, 0xf54242, "reverse zoom 3");
	if (!data->solo_tread)
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, HEIGHT + 10, 0xf54242, "Many threads. Press 4 to swap mode.");
	else
		mlx_string_put(data->mlx_ptr, data->win_ptr, 30, HEIGHT + 10, 0xf54242, "Solo thread. Press 4 to swap mode.");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, HEIGHT + 30, 0xf54242, g_fractals[data->mode]);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, HEIGHT + 50, 0xf54242, "Use left/right arrows to switch");
}

void	draw_fractal(t_data *data)
{
	if (data->solo_tread)
		fill_map_slow(data);
	else
		fill_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	draw_menu(data);
}
