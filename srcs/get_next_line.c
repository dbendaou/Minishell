/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 18:00:57 by dbendaou          #+#    #+#             */
/*   Updated: 2016/01/21 16:06:31 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_next_n(char const *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return ((str[i] == '\n') ? i + 1 : 0);
}

static int		read_static(char **line, char **str, t_file *frd)
{
	if (!(*line = ft_strsub(*str, 0, get_next_n(*str) - 1)))
		return (0);
	if (!(frd->tmp = ft_strdup(ft_strchr(*str, '\n') + 1)))
		return (0);
	ft_strdel(str);
	if (!(*str = ft_strdup(frd->tmp)))
		return (0);
	ft_strdel(&(frd->tmp));
	return (1);
}

static int		buff_join(char **line, char **str, t_file *frd)
{
	frd->tmp = ft_strsub(frd->buff, 0, get_next_n(frd->buff) - 1);
	*line = ft_strjoin(*str, frd->tmp);
	ft_strdel(&(frd->tmp));
	ft_strdel(str);
	*str = ft_strdup(ft_strchr(frd->buff, '\n') + 1);
	return (1);
}

static int		getget(char **line, char **str, t_file *frd)
{
	if (get_next_n(frd->buff) == 0)
	{
		if (*str == NULL)
			*str = ft_strdup(frd->buff);
		else
		{
			frd->tmp = ft_strjoin(*str, frd->buff);
			ft_strdel(str);
			*str = ft_strdup(frd->tmp);
			ft_strdel(&(frd->tmp));
		}
		return (0);
	}
	else if (*str == NULL)
	{
		*line = ft_strsub(frd->buff, 0, get_next_n(frd->buff) - 1);
		*str = ft_strdup(ft_strchr(frd->buff, '\n') + 1);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*str = NULL;
	t_file		*frd;

	frd = (t_file *)malloc(sizeof(t_file));
	if (line == NULL)
		return (-1);
	if (str != NULL && get_next_n(str) && read_static(line, &str, frd))
		return (1);
	while ((frd->ret = read(fd, frd->buff, BUFF_SIZE)) > 0)
	{
		frd->buff[frd->ret] = '\0';
		if (str != NULL && get_next_n(frd->buff) && buff_join(line, &str, frd))
			return (1);
		if (getget(line, &str, frd))
			return (1);
	}
	if (str != NULL && str[0] != '\0')
	{
		*line = ft_strdup(str);
		ft_strdel(&str);
		return (1);
	}
	return ((frd->ret == -1) ? -1 : 0);
}
