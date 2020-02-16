#include "../inc/fractol.h"

int 	mandelbrot(t_data *data, t_complex_num *c)
{
	int				i;
	t_complex_num	z;

	i = 0;
	z = init(c->real, c->img);
	while (pow(z.real, 2.0) + pow(z.img, 2.0) <= 4 && i < data->max_iterations)
	{
		z = init(pow(z.real, 2.0) - pow(z.img, 2.0) + c->real,
				2.0 * z.real * z.img + c->img);
		i++;
	}
	return (i);
}

int		julia(t_data *data, t_complex_num *c)
{
	int				i;
	t_complex_num	z;

	i = 0;
	z = init(c->real, c->img);
	while (pow(z.real, 2.0) + pow(z.img, 2.0) <= 4 && i < data->max_iterations)
	{
		z = init(
				pow(z.real, 2.0) - pow(z.img, 2.0) + data->julia_c.real,
				2.0 * z.real * z.img + data->julia_c.img);
		i++;
	}
	return (i);
}

int				julia_flow(int x, int y, t_data *data)
{
	if (data->mode == JULIA && !data->hold_julia)
	{
		data->julia_c = init(
				4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		draw_fractal(data);
	}
	return (0);
}

int				burning_ship(t_data *data, t_complex_num *c)
{
	int				iteration;
	t_complex_num	z;

	iteration = 0;
	z = init(c->real, c->img);
	while (pow(z.real, 2.0) + pow(z.img, 2.0) <= 4 && iteration < data->max_iterations)
	{
		z = init(pow(z.real, 2.0) - pow(z.img, 2.0) + c->real,
				-2.0 * fabs(z.real * z.img) + c->img);
		iteration++;
	}
	return (iteration);
}
