/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albartol <albartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:27:18 by albartol          #+#    #+#             */
/*   Updated: 2024/06/17 16:57:27 by albartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void print(void *str)
{
	ft_putstr_fd((char *)str, 1);
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
	{
		print_error("Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (read_scene_file(&data.file, argv[1]))
		return (EXIT_FAILURE);
	ft_lstiter(data.file.file_content, print);
	return (EXIT_SUCCESS);
}
