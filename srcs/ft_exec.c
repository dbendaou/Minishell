/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/19 19:10:49 by dbendaou         ###   ########.fr       */
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
	int		done;

	shlvl_plus(env);
	while (1)
	{
		i = 0;
		done = 0;
		*cmd = NULL;
		ft_prompt(*env, cmd);
		if (ln_check(*cmd) == 0)
		{
			args = ft_strsplit(*cmd, ' ');
			mix = ft_strsplit(get_path(*env), ':');
			if (ft_execmd(args, *mix, i, get_envclean(*env)) == 0\
				&& ft_compare(cmd, env) == 0)
			{
				ft_putstr(E_CMD);
				ft_putendl(*cmd);
			}
		}
	}
}

/*
**	Verifie le chemin d'acces de la commande et l'execute
*/

int		ft_execmd(char **args, char *mix, int i, char **envclean)
{
	char		buffer[LEN_BUF];
	struct stat	filestat;
	pid_t		father;

	while (mix[i])
	{
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
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**	Compare si la cmd appelle un built-in
*/

int		ft_compare(char **cmd, t_env **env)
{
	if (ft_strcmp("exit", *cmd) == 0)
	{
		ft_putstr("\033[33mGood bye ...\033[0m\n");
		exit(1);
	}
	if (ft_strncmp("cd", *cmd, 2) == 0)
	{
		return (1);
	}
	if (ft_strncmp("setenv", *cmd, 6) == 0)
		return (set_env(*env, cmd));
	if (ft_strncmp("unsetenv", *cmd, 8) == 0)
		return (unset_env(env, cmd));
	if (ft_strcmp("env", *cmd) == 0)
		return (my_env(*env));
	if (ft_strncmp("echo", *cmd, 4) == 0)
		return (ft_echo(cmd, *env));
	if (ft_strncmp("./minishell", *cmd, 11) == 0)
		return (executable(cmd, env));
	return (0);
}

/*
**	Execute ./minishell
*/

int		executable(char **cmd, t_env **env)
{
	pid_t	father;

	if (ft_strcmp("./minishell", *cmd) != 0)
		ft_putstr(E_USAGE);
	else
	{
		father = fork();
		if (father == 0)
		{
			execve("./minishell", cmd, get_envclean(*env));
		}
		else
			wait(NULL);
		return (1);
	}
	ft_strdel(cmd);
	return (1);
}

/*
**	Affiche le prompt et la couleur
*/

void	ft_prompt(t_env *env, char **cmd)
{
	ft_putstr(get_logname(env));
	get_next_line(0, cmd);
	ft_putstr("\033[0m");
	if (ln_check(*cmd) == 0)
		return ;
}
