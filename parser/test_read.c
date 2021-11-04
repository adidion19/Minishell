/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:32:34 by artmende          #+#    #+#             */
/*   Updated: 2021/11/03 17:59:59 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ_LENGTH 100000

int	main(int argc, char **argv)
{
	printf("Here is data from stdin :\n");
	char	buf[READ_LENGTH + 1];
	memset(&buf, 0, READ_LENGTH + 1);
	read(0, buf, READ_LENGTH);
	printf("%s\n\n", buf);

	printf("Here is data from the first argument :\n");
	
	if (argc > 1)
	{
		int	fd = open(argv[1], O_RDONLY);
		memset(&buf, 0, READ_LENGTH + 1);
		read(fd, buf, READ_LENGTH);
		printf("%s\n\n", buf);
	}
	return (0);
}
