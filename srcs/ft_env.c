/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:23:16 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/10 16:24:29 by dbendaou         ###   ########.fr       */
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
	i = 1;
	while (env[i])
	{
		tmp = ft_strsplit(env[i], '=');
		new = new_maill(tmp[0], tmp[1]);
		classic_append(new, z_env);
		i++;
	}
	return (z_env);
}

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
