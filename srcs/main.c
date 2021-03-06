/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:54:36 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:27:18 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_env	*z_env;
	char	*cmd;

	z_env = NULL;
	if (ac == 1 && !av[1])
	{
		ft_putstr(FIRST);
		if (env[0] == NULL)
		{
			z_env = my_env_i();
			ft_exec(&z_env, &cmd);
		}
		else
		{
			z_env = ft_env(env);
			shlvl_plus(&z_env);
			ft_exec(&z_env, &cmd);
		}
	}
	else
		ft_putstr(E_USAGE);
	return (0);
}
