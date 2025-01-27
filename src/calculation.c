#include "../inc/fractol.h"

int		get_color(t_data *data, int iteration, int max)
{
	double	part;
	double	part_rev;
	int		c1;
	int		c2;
	int		c3;

	part = (double)iteration / (double)max;//доля от максимума
	part_rev = 1 - part;
	c1 = (int)(15 * part_rev * part_rev * part * part * 255);
	c2 = (int)(17 * part_rev * part * part * part * 255);
	c3 = (int)(3.5 * part_rev * part_rev * part_rev * part * 255);
	if (data->color_type == 0)
		return (c1 << 16 | c2 << 8 | c3);
	if (data->color_type == 1)
		return (c1 << 8 | c2 << 16 | c3);
	if (data->color_type == 2)
		return (c1 | c2 << 16 | c3 << 8);
	else
		return (c1 | c2 << 8 | c3 << 16);
}

void	error()
{
	write(2, "pthread error\n", 14);
	exit(1);
}

void			fill_map_slow(t_data *data)
{
	int 			y;
	int				x;
	t_complex_num	c;

	data->coeff = init((data->max.real - data->min.real) / (WIDTH - 1),
					   (data->max.img - data->min.img) / (HEIGHT - 1));
	y = 0;
	while (y < HEIGHT)
	{
		c.img = data->max.img - y * data->coeff.img;
		x = 0;
		while (x < WIDTH)
		{
			c.real = data->min.real + x * data->coeff.real;
			data->mlx_map[y * HEIGHT + x] = get_color(data, data->fractals[data->mode](data, &c), data->max_iterations);
			x++;
		}
		y++;
	}
}

static void		draw_thread(t_data *data)
{
	int 			y;
	int				x;
	t_complex_num	c;

	y = data->start;
	while (y < data->end)
	{
		c.img = data->max.img - y * data->coeff.img;
		x = 0;
		while (x < WIDTH)
		{
			c.real = data->min.real + x * data->coeff.real;
			data->mlx_map[y * HEIGHT + x] = get_color(data, data->fractals[data->mode](data, &c), data->max_iterations);
			x++;
		}
		y++;
	}
}

void			fill_map(t_data *data)
{
	pthread_t	threads[THREAD_CNT];
	t_data		data_tread[THREAD_CNT];
	int			i;

	i = 0;
	data->coeff = init((data->max.real - data->min.real) / (WIDTH - 1),
					   (data->max.img - data->min.img) / (HEIGHT - 1));
	while (i < THREAD_CNT)
	{
		data_tread[i] = *data;
		data_tread[i].start = i * (HEIGHT / THREAD_CNT);
		data_tread[i].end = (i + 1) * (HEIGHT / THREAD_CNT);
		if (pthread_create(&threads[i], NULL,
						   (void *(*)(void *))draw_thread, (void *)&data_tread[i]))
			error();
		i++;
	}
	while (i-- > 0)
	{
		if (pthread_join(threads[i], NULL))
			error();
	}
}
