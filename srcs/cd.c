/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:26:45 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/25 18:09:58 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	change le premier argument si present ds path par le 2eme
*/

int		replace_path(char *to_replace, char *to_add, char *path)
{
	int		i;
	char	tmp[512];
	int		size;

	size = ft_strlen(to_replace);
	ft_bzero(tmp, 512);
	i = 0;
	while (ft_strncmp(&path[i], to_replace, size) != 0)
		i++;
	ft_strncat(tmp, path, i);
	ft_strcat(tmp, to_add);
	i += size;
	if (path[i])
		ft_strcat(tmp, &path[i]);
	ft_bzero(path, 512);
	ft_strcat(path, tmp);
	return (0);
}

/*
**	checke la validite des args envoyes a cd, notemment le path,
**	droits et nb args. renvoie 0 ou le nb d'erreur
*/

int		path_check(char **args)
{
	struct stat		buf;
	int				ret;
	int				size;

	size = ft_tablen(args);
	if (size == 3)
		return (E_STRING);
	if (size > 3)
		return (E_ARGS);
	if (args[1] && ((ft_strcmp(args[1], "~") == 0)
		|| (ft_strcmp(args[1], "-") == 0)))
		return (0);
	if (!args[1] || (ret = lstat(args[1], &buf) == 0))
	{
		if (S_ISREG(buf.st_mode))
			return (E_NO_DIR);
		if (!args[1] || (buf.st_mode & S_IRUSR))
			return (0);
		if ((buf.st_mode & S_IXUSR) == 0)
			return (E_NO_RGT);
	}
	return (E_PATH);
}

/*
**	ouvre le directory designe
*/

int		change_wd(char *dir, int opt, t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	if (opt == OPN_HOME)
		chdir(P_HOME);
	if (opt == OPN_PREV)
	{
		tmp = get_env("OLDPWD", env);
		if (!tmp->value || ft_strcmp(tmp->value, " ") == 0)
			return (cd_error(NULL, E_NO_OPWD));
		chdir(tmp->value);
	}
	else
	{
		if (chdir(dir) != 0)
			return (-1);
	}
	return (0);
}

int		change_cdstr(char **args)
{
	char	tmpdir[513];

	ft_bzero(tmpdir, 513);
	getcwd(tmpdir, 512);
	if (ft_strstr(tmpdir, args[1]))
		replace_path(args[1], args[2], tmpdir);
	else
		return (cd_error(args[1], E_STRING));
	if (chdir(tmpdir) != 0)
		return (cd_error(tmpdir, E_PATH));
	return (0);
}

/*
**	gestion generale du built_in cd
*/

int		cd(char **cmd, t_env *env)
{
	int		ret;
	char	**args;

	args = ft_strsplit(*cmd, ' ');
	if (ft_tablen(args) == 3)
		change_cdstr(args);
	else if ((ret = path_check(args)) != 0)
		return (cd_error(args[1], ret));
	else if (!args[1] || ft_strcmp(args[1], "~") == 0)
		change_wd(NULL, OPN_HOME, env);
	else if (ft_strcmp(args[1], "-") == 0)
		change_wd(NULL, OPN_PREV, env);
	else
		change_wd(args[1], 0, env);
	ft_freestrtab(&args);
	if (edit_env(env) == 0)
		return (0);
	return (-1);
}
