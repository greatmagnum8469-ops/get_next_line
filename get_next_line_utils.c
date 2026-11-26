/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:12:06 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/24 19:50:10 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	findchar_in_str(char *p,char c)
{
	int idx;

	idx = 0;
	while (*p != '\0')
	{
		if (*p == c)
			return (idx);
		idx++;
		p++;
	}
	return (-1);
}

int place_ans(char *ans, char *source, int idx)
{
	while(*source != '\0' && *source != '\n')
	{
		*(ans + idx) = *source;
		source++;
		idx++;
	}
	return (idx);
}

int get_len_untill_nl(struct s_list **head)
{
	int		len;
	struct s_list	*now;

	len = 0;
	now = *head;
	while(now != NULL && (*now).idx_nl < 0)
	{
		len += (*now).len;
		now = (*now).next;
	}
	if (now != NULL)
		len += (*now).idx_nl;
	return (len);
}

int	shift_node_data(struct s_list	*now)
{
	char	*data;
	int		idx_start;
	int		count;

	data = (*now).data;
	count = 0;
	idx_start = (*now).idx_nl + 1;
	(*now).idx_nl = -1;
	while (*(data + idx_start) != '\0')
	{
		*data = *(data + idx_start);
		data++;
		count++;
	}
	*data = '\0';
	if (count == 0)
	{
		free((*now).data);
		free(now);
		return (0);
	}
	(*now).len = count;
	(*now).idx_nl = findchar_in_str((*now).data, '\n');
	return (1);
}