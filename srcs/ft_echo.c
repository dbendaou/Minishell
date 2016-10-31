/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 17:52:58 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:42:51 by dbendaou         ###   ########.fr       */
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
	i = 1;
	echo = ft_strsplit(*cmd, ' ');
	while (echo[i])
	{
		if (echo[i][0] == '$')
		{
			if ((begin = get_env((*(echo + i) + 1), env)))
			{
				ft_putstr2(begin->value);
			}
		}
		else
			ft_putstr2(echo[i]);
		i++;
	}
	ft_putchar('\n');
	ft_freestrtab(&echo);
	ft_strdel(cmd);
	return (1);
}

void	ft_putstr2(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
	ft_putchar(' ');
}
