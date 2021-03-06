/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:23:16 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/26 22:03:55 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Recupere l'environnement et le mets dans la structure t_env
*/

t_env	*ft_env(char **env)
{
	t_env	*new;
	t_env	*z_env;
	char	**tmp;
	int		i;

	tmp = ft_strsplit(env[0], '=');
	z_env = new_maill(tmp[0], tmp[1]);
	ft_freestrtab(&tmp);
	i = 1;
	while (env[i])
	{
		tmp = ft_strsplit(env[i], '=');
		new = new_maill(tmp[0], tmp[1]);
		classic_append(new, z_env);
		i++;
		ft_freestrtab(&tmp);
	}
	return (z_env);
}

/*
**	Fonctions de parcours de liste
*/

void	classic_append(t_env *to_add, t_env *begin)
{
	t_env	*tmp;

	tmp = begin;
	if (!tmp)
		begin = to_add;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}

/*
**	Cree un nouveau maillon dans la chaine
*/

t_env	*new_maill(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (name)
		new->name = ft_strdup(name);
	else
		new->name = NULL;
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

/*
**	Supprime un maillon de la chaine
*/

void	lst_del(char *name, t_env **begin)
{
	t_env	*tmp;
	t_env	*tmprev;

	tmp = *begin;
	tmprev = *begin;
	if (ft_strcmp(tmp->name, name) == 0)
	{
		*begin = tmp->next;
		ft_strdel2(&tmp->name, &tmp->value);
		free(tmp);
		return ;
	}
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmprev->next = tmp->next;
			ft_strdel2(&tmp->name, &tmp->value);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
		tmprev = tmprev->next;
	}
}

/*
**	Mesure la taille de la liste
*/

int		lstlen(t_env *env)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
