/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:47:25 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Boucle infini ou la commande est verifie
*/

void	ft_exec(t_env **env, char **cmd)
{
	char	**args;
	char	**mix;
	t_gitan	*gitan;
	char	*tmp;
	char	**my_env;

	while (1)
	{
		gitan = gitan_init();
		ft_prompt(*env, cmd);
		tmp = get_path(*env);
		if ((gitan->ret = ft_compare(cmd, env)) == 0 && tmp != NULL \
			&& ln_check(*cmd) == 0)
		{
			args = ft_strsplit(*cmd, ' ');
			mix = ft_strsplit(tmp, ':');
			my_env = get_envclean(*env);
			ft_execmd(args, mix, gitan->i, my_env);
			ft_freestrtab(&my_env);
			ft_clean(mix, args, cmd, &tmp);
		}
		else if (tmp == NULL && gitan->ret == 0)
			ft_exec_err(cmd);
		free(gitan);
	}
}

/*
**	Verifie le chemin d'acces de la commande et l'execute ou E_CMD
*/

int		ft_execmd(char **args, char **mix, int i, char **envclean)
{
	char		buffer[LEN_BUF];
	struct stat	filestat;
	pid_t		father;

	while (mix[i])
	{
		ft_bzero(buffer, LEN_BUF);
		ft_strcat(buffer, mix[i]);
		ft_strcat(buffer, "/");
		ft_strcat(buffer, args[0]);
		if (stat(buffer, &filestat) == 0 && filestat.st_mode & S_IXUSR)
		{
			father = fork();
			if (father == 0)
				execve(buffer, args, envclean);
			else
				wait(NULL);
			return (1);
		}
		i++;
	}
	ft_putstr(E_CMD);
	ft_putendl(*args);
	return (0);
}

/*
**	Compare si la cmd appelle un built-in
*/

int		ft_compare(char **cmd, t_env **env)
{
	if (ft_strcmp("exit", *cmd) == 0)
	{
		ft_strdel(cmd);
		ft_exit(*env);
	}
	if (ft_strncmp("cd", *cmd, 2) == 0)
	{
		cd(cmd, *env);
		return (1);
	}
	if (ft_strncmp("setenv", *cmd, 6) == 0)
		return (set_env(env, cmd));
	if (ft_strncmp("unsetenv", *cmd, 8) == 0)
		return (unset_env(env, cmd));
	if (ft_strcmp("env", *cmd) == 0)
	{
		return (my_env(*env));
	}
	if (ft_strncmp("echo", *cmd, 4) == 0)
		return (ft_echo(cmd, *env));
	if (ft_strncmp("./", *cmd, 2) == 0)
		return (executable(cmd, env));
	return (0);
}

/*
**	Execute un executable \o/
*/

int		executable(char **cmd, t_env **env)
{
	pid_t		father;
	struct stat	filestat;
	char		**envclean;

	envclean = get_envclean(*env);
	if (stat(*cmd, &filestat) == 0 && filestat.st_mode & S_IXUSR)
	{
		father = fork();
		if (father == 0)
		{
			shlvl_plus(env);
			execve(*cmd, cmd, envclean);
			ft_freestrtab(&envclean);
			return (1);
		}
		else
		{
			ft_freestrtab(&envclean);
			wait(NULL);
			return (1);
		}
	}
	ft_freestrtab(&envclean);
	ft_exec_err(cmd);
	return (1);
}

/*
**	Affiche le prompt et la couleur
*/

void	ft_prompt(t_env *env, char **cmd)
{
	char	*tmp;
	char	buff[512];
	int		ret;

	ft_bzero(buff, 512);
	tmp = get_logname(env);
	ft_putstr(tmp);
	ft_strdel(&tmp);
	ret = read(0, buff, 512);
	buff[ret - 1] = '\0';
	*cmd = ft_strdup(buff);
	line_cleaner(cmd);
	ft_putstr("\033[0m");
}
