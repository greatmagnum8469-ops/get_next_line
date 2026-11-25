/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:12:03 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/25 15:20:29 by hzheng2          ###   ########.fr       */
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

int	ultimate_read(int size_buf, int idx_nl, char *buf)
{

}

char	*found_nl(int idx_nl, char *buf, int *buf_len)
{
	char	*ans;
	int		idx_and;

	ans = malloc(idx_nl + 2);
	idx_and = 0;
	while(idx_and <= idx_nl + 1)
	{
		*(ans + idx_and) = *(buf + idx_and);
		idx_and++;
	}
	*(ans + idx_and) = '\0';
	return (ans);
}

void	shift_node_data(struct s_list	*now)
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
		if (*(data + idx_start) == '\0')
			(*now).idx_nl = count;
		*data = *(data + idx_start);
		data++;
		count++;
	}
	*data = '\0';
	(*now).len = count;
	(*now).idx_nl = -1;
}

void	reset_head(struct s_list **head)
{
	struct s_list	*next;
	struct s_list	*now;

	if (*head == NULL)
		return;
	now = *head;
	while((*now).next != NULL && (*now).idx_nl == -1)
	{
		next = (*now).next;
		free((*now).data);
		free(now);
		now = next;
	}
	if ((*now).idx_nl == -1)
	{
		free((*now).data);
		free((*now).next);
		free(now);
	}
	else
		shift_node_data(now);
	*head = now;
}

void	set_head(struct s_list **head,int fd)
{
	char			*data_buf;
	struct s_list	*last_node;
	struct s_list	*node;
	int				idx_nl;
	
	data_buf = malloc(sizeof(BUFFER_SIZE + 1));
	last_node = malloc(sizeof(struct s_list));
	(*last_node).len = read(fd,data_buf,BUFFER_SIZE);
	(*last_node).idx_nl = findchar_in_str(data_buf,'\n');
	if (*head != NULL)
		*head = last_node;
	else
		(**head).next = last_node;
	while((idx_nl = findchar_in_str(data_buf,'\n') == -1))
	{
		node = malloc(sizeof(struct s_list));
		(*node).len = read(fd,data_buf);
		(*node).idx_nl = idx_nl;
	}
}

char	*get_next_line(int fd)
{
	static struct s_list *(head[1024]);
	char *ans;

	if (fd >= MAX_FD)
		return;
	set_head(head[fd],fd);
	ans = read_head(head[fd]);
	reset_head(head[fd]);
	return(ans);
}