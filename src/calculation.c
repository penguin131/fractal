#include "../inc/fractol.h"

int		get_color(int iteration, int max)
{
//	double t = (double)iteration / (double)max;//доля от максимума
//	int red = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
//	int green = (int)(17 * (1 - t) * pow(t, 3) * 255);
//	int blue = (int)(3.5 * pow((1 - t), 3) * t * 255);
//	return (red << 16 | green << 8 | blue);
	double t = (double)iteration / (double)max;//доля от максимума
	int red = (int)(9 * pow((1 - t), 2) * pow(t, 2) * 255);
	int green = (int)(15 * (1 - t) * pow(t, 3) * 255);
	int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	return (red << 16 | green << 8 | blue);
//	return (iteration == max ? 0 : 0xffffff);
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
			data->mlx_map[y * HEIGHT + x] = data->fractals[data->mode](data, &c);
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
			//get_color(i, data->max_iterations)
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
