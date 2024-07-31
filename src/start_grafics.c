/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_grafics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flopez-r <flopez-r@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:44:53 by flopez-r          #+#    #+#             */
/*   Updated: 2024/07/31 16:33:17 by flopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

#define LINE_SPEED 1

int	init_images(t_display *display)
{
	display->grafics.wall = mlx_new_image(display->mlx, P_SIZE, P_SIZE);
	display->grafics.player = mlx_new_image(display->mlx, 20, 20);

	if (!display->grafics.wall || !display->grafics.player)
		return (exit_msg(mlx_strerror(mlx_errno), EXIT_FAILURE));
	fill_color(display->grafics.wall, 255, 255, 255, 255);
	fill_color(display->grafics.player, 30, 202, 75, 255);
	return (EXIT_SUCCESS);
}

void init_player(t_player *player, t_game *data)
{
	player->mlx = data->display.mlx;
	player->angle = INIT_ANGLE;
	player->rotation = 0.5;
	player->x = data->scene.player_x * P_SIZE;
	player->y = data->scene.player_y * P_SIZE;
	player->img = data->display.grafics.player;
	player->map = data->file.map;
}


void	print_pos(t_player *player)
{
	printf("=============================\n");
	printf("Player pos (window)--> (%d, %d)\n", player->img->instances[0].x, player->img->instances[0].y);
	printf("Player pos (  map )--> (%d, %d)\n", player->img->instances[0].x / P_SIZE, player->img->instances[0].y / P_SIZE);
	printf("=============================\n");
}

double	calculate_distance(t_player *player, int x2, int y2)
{
	double	distance;
	int		x1;
	int		y1;

	x1 = player->img->instances[0].x;
	y1 = player->img->instances[0].y;
	distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	if (distance < 0)
		distance *= -1;
	return (distance);
}

void	get_distance(void *param)
{
	t_player	*player;
	float		distance;
	int			x2;
	int			y2;

	player = (t_player *)param;
	distance = 0;
	x2 = player->img->instances[0].x;
	y2 = player->img->instances[0].y;
	while (1)
	{
		if (player->map[y2 / P_SIZE][x2 / P_SIZE] == '1')
			return ((void)printf("Distance --> %f\n", calculate_distance(player, x2, y2)));
		x2 += cos(convert_to_radian(player->angle)) * LINE_SPEED;
		y2 -= sin(convert_to_radian(player->angle)) * LINE_SPEED;
	}
	player = (t_player *)param;
	print_pos(player);
}

void	draw_escene(void *param)
{
	t_player *player;

	player = (t_player *)param;
	get_distance(player);
}

int start_grafics(t_game *data)
{
	t_player	player;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->display.mlx = mlx_init(data->scene.map_width * P_SIZE,
		data->scene.map_height * P_SIZE, "cube3d", true);
	if (!data->display.mlx)
		return (exit_msg(mlx_strerror(mlx_errno), EXIT_FAILURE));
	if (init_images(&data->display))
		return (EXIT_FAILURE);
	if (put_map(data->file.map, &data->display, data->display.grafics.wall))
		return (EXIT_FAILURE);
	init_player(&player, data);

	// printf("Player pos --> (%f, %f)\n", player.x, player.y);
	if (mlx_image_to_window(player.mlx, player.img, player.x * P_SIZE, player.y * P_SIZE) == -1)
		return (EXIT_FAILURE);

	mlx_loop_hook(data->display.mlx, movement, &player);
	mlx_loop_hook(data->display.mlx, draw_escene, &player);
	mlx_loop(data->display.mlx);
	mlx_terminate(data->display.mlx);
	free_scene_info(&data->file);
	return (EXIT_SUCCESS);
}
