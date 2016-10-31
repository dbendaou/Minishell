/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 18:24:08 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:41:37 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Recupere le login
*/

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
			ft_strdel(&tmp);
			return (tmpp);
		}
		logname = logname->next;
	}
	tmpp = ft_strjoin("", "\033[34;1mNO_USER$> \033[36;1m");
	return (tmpp);
}

/*
** Cherche le Path sinon return une valeur bidon
*/

char	*get_path(t_env *env)
{
	t_env	*path;
	char	*tmp;

	path = env;
	while (path)
	{
		if (ft_strncmp(path->name, "PATH", 4) == 0)
		{
			tmp = ft_strdup(path->value);
			return (tmp);
		}
		path = path->next;
	}
	return (NULL);
}

/*
** Remets l'env au format char **
*/

char	**get_envclean(t_env *env)
{
	t_env	*tmp;
	char	**tmpp;
	char	*tmpenv;
	int		i;

	tmp = env;
	i = 0;
	tmpp = (char **)malloc(sizeof(char *) * (lstlen(env) + 1));
	while (tmp)
	{
		tmpenv = ft_strjoin(tmp->name, "=");
		tmpp[i] = ft_strjoin(tmpenv, tmp->value);
		ft_strdel(&tmpenv);
		i++;
		tmp = tmp->next;
	}
	tmpp[i] = NULL;
	return (tmpp);
}

/*
**	Cherche le maillon designe par name
*/

t_env	*get_env(char *name, t_env *begin)
{
	t_env		*tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp && ft_strcmp(name, tmp->name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
