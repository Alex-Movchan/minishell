/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_alhpa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amovchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 19:31:56 by amovchan          #+#    #+#             */
/*   Updated: 2017/10/01 19:32:02 by amovchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	second_file(t_file **begin, t_file *file)
{
	if (ft_strcmp((*begin)->name, file->name) > 0)
	{
		file->next = *begin;
		*begin = file;
	}
	else
		(*begin)->next = file;
}

static void	ft_find_place(t_file **begin, t_file *file)
{
	t_file	*lst;

	lst = *begin;
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->next->name, file->name) > 0)
		{
			file->next = lst->next;
			lst->next = file;
			break ;
		}
		lst = lst->next;
	}
	if (lst->next != file)
	{
		lst->next = file;
	}
}

void		add_alpha_file(t_file **begin, t_file *file)
{
	if (!*begin)
		*begin = file;
	else if (!(*begin)->next)
		second_file(begin, file);
	else if (ft_strcmp((*begin)->name, file->name) > 0)
		file->next = *begin;
	else
		ft_find_place(begin, file);
}
