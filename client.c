/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krochefo <krochefo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:36:03 by krochefo          #+#    #+#             */
/*   Updated: 2022/09/15 13:38:52 by krochefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "includes/includes.h"

static void	handler(int signum)
{
	(void)signum;
	ft_putendl_fd("Data has been received.", 1);
	exit(EXIT_SUCCESS);
}

static void	encoding(char *str, pid_t pid)
{
	int	len;
	int	byte;

	len = ft_strlen(str) + 1;
	while (len--)
	{
		byte = 8;
		while (byte)
		{
			usleep(100);
			byte--;
			if ((*str >> byte & 1) == 1)
			{
				kill (pid, SIGUSR1);
				usleep(100);
			}
			else
			{
				kill (pid, SIGUSR2);
				usleep(100);
			}
		}
		str++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Incorrect number of arguments.\n", 1);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 1 || pid > 99998)
	{
		ft_putstr_fd("Invalid PID number.\n", 1);
		return (-1);
	}
	signal(SIGUSR1, handler);
	encoding(argv[2], pid);
}
