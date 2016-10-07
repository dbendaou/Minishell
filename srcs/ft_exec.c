/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/07 17:42:32 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_env *env, char **cmd)
{
	char	**args;
	char	*text;
	char	**mix;
	char	**envclean;
	int		i;

	while (1)
	{
		i = 0;
		envclean = get_envclean(env);
		ft_putstr(get_logname(env));
		get_next_line(0, cmd);
		ft_putstr("\033[0m");
		if (cmd)
		{
			ft_compare(cmd);
			args = ft_strsplit(*cmd, ' ');
			text = get_path(env);
			mix = ft_strsplit(text, ':');
			while (mix[i])
				i = ft_execmd(args, *mix, i, envclean);
		}
	}
}

int		ft_execmd(char **args, char *mix, int i, char **envclean)
{
	char		buffer[LEN_BUF];
	struct stat	filestat;
	pid_t		father;

	ft_bzero(buffer, LEN_BUF);
	ft_strcat(buffer, &mix[i]);
	ft_strcat(buffer, "/");
	ft_strcat(buffer, args[0]);
	if (stat(buffer, &filestat) == 0 && filestat.st_mode & S_IXUSR)
	{
		father = fork();
		if (father == 0)
		{
			execve(buffer, args, envclean);
		}
		else
			wait(NULL);
	}
	i++;
	return (i);
}

/*
** Compare si la cmd appelle un build-in
*/

void	ft_compare(char **cmd)
{
	if (ft_strcmp("exit", *cmd) == 0)
		exit(1);
	if (ft_strncmp("cd", *cmd, 2) == 0)
		exit(0);
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
