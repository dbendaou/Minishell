/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/13 19:34:41 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Split la commande au bon format
*/

void	ft_exec(t_env **env, char **cmd)
{
	char	**args;
	char	**mix;
	int		i;
	int 	done;

	while (1)
	{
		i = 0;
		done = 0;
		signal(SIGINT, ft_signal);
		*cmd = NULL;
		ft_prompt(*env, cmd);
		if (*cmd)
		{
			if (ft_compare(cmd, env) == 1)
				done = 1;
			args = ft_strsplit(*cmd, ' ');
			mix = ft_strsplit(get_path(*env), ':');
			while (mix[i] && done == 0)
				i = ft_execmd(args, *mix, i, get_envclean(*env));
		}
	}
}

/*
**	Verifie le chemin d'acces de la commande et si elle est executable
*/

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
			execve(buffer, args, envclean);
		else
			wait(NULL);
	}
	i++;
	return (i);
}

/*
**	Compare si la cmd appelle un build-in
*/

int		ft_compare(char **cmd, t_env **env)
{
	if (ft_strcmp("exit", *cmd) == 0)
	{
		ft_putstr("Good bye ..\n");
		exit(1);
	}
	if (ft_strncmp("cd", *cmd, 2) == 0)
	{
		get_pwd(*env);
		return (1);
	}
	if (ft_strncmp("setenv", *cmd, 6) == 0)
		set_env(*env, cmd);
	if (ft_strncmp("unsetenv", *cmd, 8) == 0)
		unset_env(env, cmd);
	if (ft_strcmp("env", *cmd) == 0)
	{
		my_env(*env);
		return (1);
	}
	if (ft_strncmp("echo", *cmd, 4) == 0)
	{
		ft_echo(cmd, *env);
		return (1);
	}
	return (0);
}

/*
**	Affiche le prompt et la couleur
*/

void	ft_prompt(t_env *env, char **cmd)
{
	ft_putstr(get_logname(env));
	get_next_line(0, cmd);
	ft_putstr("\033[0m");
}
