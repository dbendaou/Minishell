/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 19:30:48 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/19 19:33:34 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Affiche l'erreur correspondant au chiffre envoye
*/

int		cd_error(char *path, int errnb)
{
	if (errnb == E_PATH || errnb == E_STRING)
	{
		ft_putstr((errnb == E_PATH) ? ME_PATH : ME_STRING);
		ft_putendl(path);
	}
	else if (errnb == E_ARGS)
		ft_putstr(ME_ARGS);
	else if (errnb == E_NO_OPWD)
		ft_putstr(ME_NO_OPWD);
	else if (errnb == E_NO_DIR || errnb == E_NO_RGT)
	{
		ft_putstr((errnb == E_NO_DIR) ? ME_NO_DIR : ME_NO_RGT);
		ft_putendl(path);
	}
	return (-1);
}

/*
**	Mets a jour l'env selon PWD et OLDPWD
*/

int		edit_env(t_env *env)
{
	char	tmpath[513];
	t_env	*c_wd;
	t_env	*o_pwd;

	ft_bzero(tmpath, 513);
	getcwd(tmpath, 512);
	c_wd = get_env("PWD", env);
	o_pwd = get_env("OLDPWD", env);
	if (!c_wd || !o_pwd)
		return (-1);
	if (o_pwd->value)
		ft_strdel(&o_pwd->value);
	o_pwd->value = ft_strdup(c_wd->value);
	ft_strdel(&c_wd->value);
	c_wd->value = ft_strdup(tmpath);
	return (0);
}
