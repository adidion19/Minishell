/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:20:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/25 13:53:21 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
faudra degager cette fonction, c'etait pour des tests
*/

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	a;

	if (nb < 0)
	{
		write(fd, "-", 1);
		a = -nb;
	}
	else
		a = nb;
	if (a >= 10)
	{
		ft_putnbr_fd(a / 10, fd);
		ft_putchar(a % 10 + '0', fd);
	}
	else
		ft_putchar(a + '0', fd);
}

void	ft_error_shlvl(int result)
{
	write(2, "minishell: warning: shell level (", 33);
	ft_putnbr_fd(result, 2);
	write(2, ") too high, resetting to 1\n", 28);
}

char	**ft_minishell_lvl(char **env, int ac, char **av)
{
	int		i;
	int		result;

	i = -1;
	if (ac != 1 || av)
		;
	while (env[++i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
			break ;
	}
	result = ft_atoi(env[i] + 6);
	if (result < 0)
		result = 0;
	result++;
	if (result >= 1000)
	{
		ft_error_shlvl(result);
		result = 1;
	}
	free(env[i]);
	env[i] = ft_strjoin("SHLVL=", ft_itoa(result));
	return (env);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	int				i;
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);/* gestion de l'affichage du ctrl*/
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_p);
	env = init_env(env);
	ft_minishell_lvl(env, ac, av);
	set_signal();
	while (1)
	{
		set_signal();
		line = readline("$> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (line && *line)
			i = add_history(line);
		free(line);
	}
	return (0);
}
