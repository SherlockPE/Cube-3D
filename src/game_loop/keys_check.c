/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albartol <albartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:56:01 by flopez-r          #+#    #+#             */
/*   Updated: 2024/09/25 15:05:26 by albartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raycast.h>

/*
Returns true if its no collisions
and false si hay colisiones
 */
static void	checker(float x, float y, t_player *player, char **map)
{
	t_cords_i	new;
	t_cords_i	old;

	old.x = (int)player->pos.x;
	old.y = (int)player->pos.y;
	new.x = (int)x;
	new.y = (int)y;
	if (new.x <= 0 || new.y <= 0 || new.y >= array_len(map)
		|| new.x >= (int)ft_strlen(map[new.y]) || map[new.y][new.x] == WALL)
		return ;
	if (old.x < new.x && map[old.y][old.x + 1] == WALL)
	{
		if (old.y < new.y && map[old.y + 1][old.x] == WALL)
			return ;
		if (old.y > new.y && map[old.y - 1][old.x] == WALL)
			return ;
	}
	if (old.x > new.x && map[old.y][old.x - 1] == WALL)
	{
		if (old.y < new.y && map[old.y + 1][old.x] == WALL)
			return ;
		if (old.y > new.y && map[old.y - 1][old.x] == WALL)
			return ;
	}
	player->pos.x = x;
	player->pos.y = y;
}

static void	wasd_movement(mlx_t *mlx, t_player *player, char **map)
{
	t_cords_d	new;
	t_cords_d	const_sin;

	const_sin.x = cos(player->angle) * MOVE_SPEED;
	const_sin.y = sin(player->angle) * MOVE_SPEED;
	new.x = player->pos.x;
	new.y = player->pos.y;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		checker(new.x + const_sin.x, new.y - const_sin.y, player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		checker(new.x - const_sin.x, new.y + const_sin.y, player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		checker(new.x - const_sin.y, new.y - const_sin.x, player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		checker(new.x + const_sin.y, new.y + const_sin.x, player, map);
}

static void	arrows_pov(mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_Q))
		rotate_lr(player, ROTATION_SPEED, -1.0);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_E))
		rotate_lr(player, ROTATION_SPEED, 1.0);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		rotate_ud(player, (ROTATION_SPEED + 1));
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		rotate_ud(player, -(ROTATION_SPEED + 1));
}

void	keys_check(t_game *data)
{
	mlx_t	*mlx;

	mlx = data->display.mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->display.mlx);
		ft_putstr_fd("Thanks for playing\n", STDOUT_FILENO);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_M))
		data->display.map->enabled = !data->display.map->enabled;
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		data->mouse = !data->mouse;
		if (data->mouse)
			mlx_set_cursor_mode(data->display.mlx, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(data->display.mlx, MLX_MOUSE_HIDDEN);
	}
	wasd_movement(mlx, &data->player, data->file.map);
	arrows_pov(mlx, &data->player);
}
// if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_A)
// 	|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_D))
// 	wasd_movement(mlx, &data->player, data->file.map);