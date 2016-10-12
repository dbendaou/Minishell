/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 16:39:44 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/12 18:21:07 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Affiche l'environnement
*/

void	my_env(t_env *env)
{
	char	**tmp;
	int		i;

	i = 0;
	if (env != NULL)
	{
		tmp = get_envclean(env);
		while (tmp[i] != NULL)
		{
			ft_putstr(tmp[i]);
			ft_putstr("\n");
			i++;
		}
	}
}

/*
t_env	*set_env(t_env *env, char **cmd)
{

}*/