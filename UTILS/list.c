/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:30:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/19 14:30:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_list	*lst_last(t_list *lst);

void	lst_new(t_data *data, int k)
{
	t_list	*new;

	if (!data->is_key_buff)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			close_mlx(data);
		new->k = k;
		new->next = NULL;
		if (data->kbuff)
			lst_last(data->kbuff)->next = new;
		else
			data->kbuff = new;
	}
	data->is_key_buff = FALSE;
}

static t_list	*lst_last(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_clear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}
