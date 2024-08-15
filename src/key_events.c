/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flopez-r <flopez-r@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:13:52 by flopez-r          #+#    #+#             */
/*   Updated: 2024/08/13 20:10:28 by flopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raycast.h>

void	draw_all(t_game *data);
int detect_colition(int x, int y, char **map);

float	transform_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

float	convert_to_radian(float number)
{
	return (number * (PI / 180));
}
/* 
Nota: las adiciones y restas tanto a x e y son segun el vector de direccion que funciona ahora
W --> mira al Oeste
 */
// void	key_events(void *param)
void	key_events(mlx_key_data_t keydata, void* param)
{
	t_game		*data;
	t_cords		save_pos;
	t_cords		save_plane;
	t_cords		new;

	data = (t_game *)param;

	// For the panzer movement
	new.x = data->player.x;
	new.y = data->player.y;

	//For the rotation
	save_pos.x = data->player.dir_vector.x;
	save_pos.y = data->player.dir_vector.y;

	//For the plane of the camera
	save_plane.x = data->player.camera_plane.x;
	save_plane.y = data->player.camera_plane.y;

	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(data->display.mlx);
		printf("Adiooooossss");
	}
	else if (keydata.key == MLX_KEY_W)
	{
		new.x += cos(convert_to_radian(data->player.angle)) * MOVE_SPEED;
		new.y -= sin(convert_to_radian(data->player.angle)) * MOVE_SPEED;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		new.x -= cos(convert_to_radian(data->player.angle)) * MOVE_SPEED;
		new.y += sin(convert_to_radian(data->player.angle)) * MOVE_SPEED;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		new.x += sin(convert_to_radian(data->player.angle)) * MOVE_SPEED;
		new.y += cos(convert_to_radian(data->player.angle)) * MOVE_SPEED;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		new.x -= sin(convert_to_radian(data->player.angle)) * MOVE_SPEED;
		new.y -= cos(convert_to_radian(data->player.angle)) * MOVE_SPEED;
	}
	if (!detect_colition((int)new.x, (int)new.y, data->file.map))
	{
		data->player.x = new.x;
		data->player.y = new.y;
		draw_all(data);
		printf(YELLOW"Mi posición es :(%d, %d)\n" RESET, (int)data->player.x, (int)data->player.y);
	}
	else
		printf(RED"COLISION DETECTED YOUUU WILL NOTT PASSSS 🧙🏻‍♂️\n"RESET);
	//Rotation
	/* 
	Dada la matriz de rotacion:
	[cos( θ )	- 	sin( θ )]
	[sin( θ )	+ 	cos( θ )]

	podemos hacer una ecuación matricial donde: x0, y0 son las coordenadas originales del player
	y θ el angulo de movimiento (rotation speed)
	
	[cos( θ )	- 	sin( θ )] [x0] = [xResult]
	[sin( θ )	+ 	cos( θ )] [y0] = [yResult]

	//Esta ecuación matricial está hecha para coordenadas dirigidas a la izq 
	(pero funciona igual si el angulo es negativo (para el otro lado(derecha)))
	 */
	if (keydata.key == MLX_KEY_LEFT)
	{
		//Rotate the direction vector
		data->player.dir_vector.x = save_pos.x * cos(ROTATION_SPEED_R) - save_pos.y * sin(ROTATION_SPEED_R);
		data->player.dir_vector.y = save_pos.x * sin(ROTATION_SPEED_R) + save_pos.y * cos(ROTATION_SPEED_R);

		//Rotate the camera plane
		data->player.camera_plane.x = save_plane.x * cos(ROTATION_SPEED_R) - save_plane.y * sin(ROTATION_SPEED_R);
		data->player.camera_plane.y = save_plane.x * sin(ROTATION_SPEED_R) + save_plane.y * cos(ROTATION_SPEED_R);
		
		printf(YELLOW"Rotando %f grados (right)\n" RESET, ROTATION_SPEED);
		draw_all(data);
		data->player.angle = transform_angle(data->player.angle - ROTATION_SPEED);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		//Rotate the direction vector
		data->player.dir_vector.x = save_pos.x * cos(-ROTATION_SPEED_R) - save_pos.y * sin(-ROTATION_SPEED_R);
		data->player.dir_vector.y = save_pos.x * sin(-ROTATION_SPEED_R) + save_pos.y * cos(-ROTATION_SPEED_R);

		//Rotate the camera plane
		data->player.camera_plane.x = save_plane.x * cos(-ROTATION_SPEED_R) - save_plane.y * sin(-ROTATION_SPEED_R);
		data->player.camera_plane.y = save_plane.x * sin(-ROTATION_SPEED_R) + save_plane.y * cos(-ROTATION_SPEED_R);

		printf(YELLOW"Rotando %f grados (right)\n" RESET, ROTATION_SPEED);
		draw_all(data);
		data->player.angle = transform_angle(data->player.angle + ROTATION_SPEED);
	}
}


// void	key_events(void *param)
// {
// 	t_game		*data;

// 	data = (t_game *)param;
// 	if (mlx_is_key_down(data->display.mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_close_window(data->display.mlx);
// 		printf("Adiooooossss");
// 	}
// 	if (mlx_is_key_down(data->display.mlx, MLX_KEY_W))
// 	{
// 		data->player.x += 0.5;
// 		printf(YELLOW"Mi posición es :(%d, %d)\n" RESET, (int)data->player.x, (int)data->player.y);
// 	}
// }
