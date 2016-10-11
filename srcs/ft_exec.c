/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/10 17:41:43 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Split la commande au bon format
*/

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
		signal(SIGINT, ft_signal);
		envclean = get_envclean(env);
		ft_prompt(env, cmd);
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

/*
**	Verifie le chemin d'acces de la commande et si executable
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

void	ft_compare(char **cmd)
{
	if (ft_strcmp("exit", *cmd) == 0)
		exit(1);
	if (ft_strncmp("cd", *cmd, 2) == 0)
		exit(0);
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
