/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:54:36 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/13 19:47:01 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_env	*z_env;
	t_env	**tmp;
	int		i;
	char	*cmd;

	tmp = NULL;
	z_env = NULL;
	i = 0;
	if (ac == 1 && !av[1])
	{
		if (env[0] == NULL)
		{
			
			*tmp = my_env_i();
			printf("salope\n");
			ft_exec(tmp, &cmd);
		}
		else
		{
			z_env = ft_env(env);
			ft_exec(&z_env, &cmd);
		}
	}
	else
		ft_putstr(E_usage);
	return (0);
}
