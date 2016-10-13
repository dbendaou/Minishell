/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 16:39:44 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/14 01:23:19 by dbendaou         ###   ########.fr       */
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

	tmp = NULL;
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
	ft_strdel(tmp);
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
				ft_strdel2(tmp, tmpp);
				return ;
			}
			e_tmp = e_tmp->next;
		}
		classic_append(new_maill(tmpp[0], tmpp[1]), env);
		ft_strdel2(tmp, tmpp);
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

/*
**	Creer l'environnement quand celui-ci est vide
*/

t_env	*my_env_i()
{
	t_env	*tmp;
	t_env	*new;
	tmp = new_maill("PATH", PATH);
	new = new_maill("SHLVL", "1");
	classic_append(new, tmp);
	return (tmp);
}