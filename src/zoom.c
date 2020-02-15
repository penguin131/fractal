#include "../inc/fractol.h"

double	interpolation(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int		zoom(int key, int x, int y, t_data *data)
{
	t_complex_num	mouse;
	double			interp;
	double			zoom;

	if (key != GET_ZOOM)
		return (0);
	mouse = init((double)x / (WIDTH / (data->max.real - data->min.real))
				 + data->min.real,
				 (double)y / (HEIGHT / (data->max.img - data->min.img))
				 * -1 + data->max.img);
	if (data->reverse_zoom)
		zoom = ZOOM_UP_STEP;
	else
		zoom = ZOOM_DOWN_STEP;
	interp = 1.0 / zoom;
	data->min.real = interpolation(mouse.real, data->min.real, interp);
	data->min.img = interpolation(mouse.img, data->min.img, interp);
	data->max.real = interpolation(mouse.real, data->max.real, interp);
	data->max.img = interpolation(mouse.img, data->max.img, interp);
	draw_fractal(data);
	return (0);
}
