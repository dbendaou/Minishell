/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 03:46:34 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:46:57 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return -1 si cmd contient que espace ou tab
*/

int			ln_check(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			if (cmd[i] != '\t')
				return (0);
		}
		i++;
	}
	ft_strdel(&cmd);
	return (-1);
}

/*
**	Efface les espace et tab
*/

void		line_cleaner(char **line)
{
	char	new[1024];
	int		i;

	i = 0;
	ft_bzero(new, 1024);
	if (ft_strchr(*line, '\t'))
	{
		while ((*line)[i])
		{
			if ((*line)[i] == '\t')
				new[i] = ' ';
			else
				new[i] = (*line)[i];
			i++;
		}
		ft_strdel(line);
		*line = ft_strdup(new);
	}
}

/*
**	Merci la norme Pt.3 \o/
**						 |
**						/ \
*/

void		ft_exec_err(char **cmd)
{
	ft_putstr(E_CMD);
	ft_putendl(*cmd);
	ft_strdel(cmd);
}

/*
**	Sans commentaire..
*/

t_gitan		*gitan_init(void)
{
	t_gitan		*new;

	new = (t_gitan *)malloc(sizeof(t_gitan));
	new->i = 0;
	new->ret = 0;
	return (new);
}
