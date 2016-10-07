/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:54:36 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/07 17:41:50 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_env	*z_env;
	int		i;
	char	*cmd;

	i = 0;
	if (ac == 1 && !av[1])
	{
		if (env[0] == NULL)
			ft_exec(NULL, &cmd);
		else
		{
			z_env = ft_env(env);
			ft_exec(z_env, &cmd);
		}
	}
	else
		ft_putstr(E_usage);
	return (0);
}
