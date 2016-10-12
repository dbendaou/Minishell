/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 18:24:08 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/12 18:23:12 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
** Cherche le Path et si env-i le fourni
*/

char	*get_path(t_env *env)
{
	t_env	*path;

	path = env;
	while (path)
	{
		if (ft_strncmp(path->name, "PATH", 4) == 0)
			return (path->value);
		path = path->next;
	}
	return ("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin");
}

/*
** Remets l'env au formar char **
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
**	Cherche le current directory
*/

char	*get_pwd(t_env *env)
{
	t_env	*pwd;

	pwd = env;
	while (pwd)
	{
		if (ft_strncmp(pwd->name, "PWD", 4) == 0)
		{
			ft_putstr(pwd->value);
			return (pwd->value);
		}
		pwd = pwd->next;
	}
	return (NULL);
}