/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 15:14:40 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:14:56 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Affiche l'environnement
*/

int		my_env(t_env *env)
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
		if (tmp != NULL)
			ft_freestrtab(&tmp);
	}
	return (1);
}

/*
**	Ajoute une variable a l'environement
*/

int		set_env(t_env **env, char **cmd)
{
	char	**tmp;
	char	**tmpp;
	t_env	*e_tmp;

	e_tmp = *env;
	tmp = ft_strsplit(*cmd, ' ');
	if ((tmpp = ft_strsplit(tmp[1], '=')) && tmpp[1])
	{
		if (get_env(tmpp[0], *env))
			lst_del(tmpp[0], env);
		classic_append(new_maill(tmpp[0], tmpp[1]), *env);
		ft_freestrtab(&tmp);
		ft_freestrtab(&tmpp);
	}
	ft_strdel(cmd);
	return (1);
}

/*
**	Enleve une variable de l'environement
*/

int		unset_env(t_env **begin, char **cmd)
{
	char	**tmp;

	tmp = ft_strsplit(*cmd, ' ');
	if (tmp[1])
	{
		lst_del(tmp[1], begin);
	}
	ft_freestrtab(&tmp);
	return (1);
}

/*
**	Creer l'environnement quand celui-ci est vide
*/

t_env	*my_env_i(void)
{
	t_env	*tmp;
	t_env	*new;

	tmp = new_maill("PATH", PATH);
	new = new_maill("SHLVL", "1");
	classic_append(new, tmp);
	return (tmp);
}

/*
**	Augmente le SHLVL
*/

int		shlvl_plus(t_env **env)
{
	t_env	*tmp;
	int		i;

	tmp = get_env("SHLVL", *env);
	i = ft_atoi(tmp->value);
	ft_strdel(&tmp->value);
	i++;
	tmp->value = ft_itoa(i);
	return (1);
}
