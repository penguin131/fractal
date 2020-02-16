#include "../inc/fractol.h"

int		get_color(int iteration, int max)
{
	double t = (double)iteration / (double)max;//доля от максимума
	double t2 = 1 - t;
	int red = (int)(15 * t2 * t2 * t * t * 255);
	int green = (int)(17 * t2 * t * t * t * 255);
	int blue = (int)(3.5 * t2 * t2 * t2 * t * 255);
	return (red << 16 | green << 8 | blue);
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
			data->mlx_map[y * HEIGHT + x] = get_color(data->fractals[data->mode](data, &c), data->max_iterations);
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
			data->mlx_map[y * HEIGHT + x] = get_color(data->fractals[data->mode](data, &c), data->max_iterations);
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
