/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 16:39:44 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/13 04:58:41 by dbendaou         ###   ########.fr       */
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
**	Ajoute une variable a l'environement
*/

void 	set_env(t_env *env, char **cmd)
{
	char	**tmp;
	char 	**tmpp;
	t_env	*e_tmp;

	e_tmp = env;
	tmp = ft_strsplit(*cmd, ' ');
	tmp++;
	tmpp = ft_strsplit(*tmp, '=');
	if (tmpp[1])
	{
		while (e_tmp)
		{
			if (ft_strcmp(e_tmp->name, tmpp[0]) == 0)
			{
				e_tmp->value = tmpp[1];
			}
			e_tmp = e_tmp->next;
		}
		classic_append(new_maill(tmpp[0], tmpp[1]), env);
	}
}

/*
**	Enleve une variable de l'environement
*/

void	unset_env(t_env **begin, char **cmd)
{
	char 	**tmp;

	tmp = ft_strsplit(*cmd, ' ');
	lst_del(tmp[1], begin);
}
