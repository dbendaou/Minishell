/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:23:16 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/05 19:32:34 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_logname(t_env *env)
{
	t_env	*logname;
	char	*tmp;
	char	*tmpp;

	logname = env;
	while (logname)
	{
		if (ft_strncmp(logname->name, "LOGNAME", 7) == 0)
		{
			tmp = ft_strjoin("\033[34;1m", logname->value);
			tmpp = ft_strjoin(tmp, "$> \033[36;1m");
			free(tmp);
			return (tmpp);
		}
		logname = logname->next;
	}
	return ("NO_USER$> ");
}
