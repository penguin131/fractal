#include "../inc/fractol.h"

void	switch_fractal(t_data *data, int key)
{
	if (key == RIGHT)
		data->mode++;
	else
		data->mode--;
	data->max_iterations = START_ITER;
	initialize_constant(data);
}

void	switch_color(t_data *data, int key)
{
	if (key == RIGHT_MODE && data->color_type < 3)
		data->color_type++;
	else if (key == LEFT_MODE && data->color_type > 0)
		data->color_type--;
}

int		deal_key(int key, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (key == ESC)
		end_mlx(param);
	else if (key == ITER_UP)
		data->max_iterations += ITER_STEP;
	else if (key == ITER_DOWN && data->max_iterations > ITER_STEP)
		data->max_iterations -= ITER_STEP;
	else if (key == ZOOM_REVERSE)
		data->reverse_zoom = ~(data->reverse_zoom);
	else if (key == THREAD_MODE)
		data->solo_tread = ~(data->solo_tread);
	else if ((key == RIGHT && data->mode < FRACTAL_CNT - 1) || (key == LEFT && data->mode > 0))
		switch_fractal(data, key);
	else if (key == SPACE)
		data->hold_julia = ~data->hold_julia;
	else if (key == RIGHT_MODE || key == LEFT_MODE)
		switch_color(data, key);
	//printf("%d\n", key);
	draw_fractal(data);
	return (0);
}

void	loop(t_data *data)
{
	draw_fractal(data);
	mlx_hook(data->win_ptr, 2, 0, deal_key, data);
	mlx_hook(data->win_ptr, 4, 0, zoom, data);
	mlx_hook(data->win_ptr, 6, 0, julia_flow, data);
	mlx_loop(data->mlx_ptr);
}
