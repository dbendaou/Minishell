/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 17:52:58 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/19 19:05:14 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Built-in echo
*/

int		ft_echo(char **cmd, t_env *env)
{
	char	**echo;
	int		i;
	t_env	*begin;

	begin = env;
	i = 0;
	echo = ft_strsplit(*cmd, ' ');
	while (echo[i])
	{
		while (env && env->next)
		{
			if (ft_strcmp((*(echo + i) + 1), env->name) == 0 \
				&& echo[i][0] == '$')
			{
				ft_putstr(env->value);
				ft_putchar(' ');
			}
			env = env->next;
		}
		i++;
		env = begin;
	}
	ft_putchar('\n');
	return (1);
}
