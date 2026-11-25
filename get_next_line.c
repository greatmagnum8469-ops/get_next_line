/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:12:03 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/25 17:29:41 by hzheng2          ###   ########.fr       */
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

struct s_list	*new_node(int fd,int *idx_nl)
{
	struct s_list	*node;

	node = malloc(sizeof(struct s_list));
	(*node).data = malloc(BUFFER_SIZE + 1);
	if (((*node).len = read(fd,(*node).data,BUFFER_SIZE)) <= 0)
		
	*(((*node).data) + (*node).len) = '\0';
	*idx_nl = findchar_in_str((*node).data, '\n');
	(*node).idx_nl = *idx_nl;
	(*node).next = NULL;
	return (node);
}

void	set_head(struct s_list **head,int fd)
{
	char			*data_buf;
	struct s_list	*last_node;
	struct s_list	*node;
	int				*idx_nl;
	
	data_buf = malloc(BUFFER_SIZE + 1);
	last_node = malloc(sizeof(struct s_list));
	(*last_node).len = read(fd,data_buf,BUFFER_SIZE);
	*idx_nl = findchar_in_str(data_buf,'\n');
	(*last_node).idx_nl = *idx_nl;
	if (*head == NULL)
		*head = last_node;
	else
		(**head).next = last_node;
	while(idx_nl == -1)
	{
		(*last_node).next = node;
		node = new_node(fd, &idx_nl);
		last_node = node;
	}
	(*last_node).next = node;
	node = new_node(fd, idx_nl);
}

int get_len_untill_nl(struct s_list **head)
{
	int		len;
	struct s_list	*now;

	len = 0;
	now = *head;
	while((*now).idx_nl < 0)
	{
		len += (*now).len;
		now = (*now).next;
	}
	len += (*now).idx_nl;
	return (len);
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

char *read_head(struct s_list **head,int fd)
{
	char *ans;
	int idx_ans;
	struct s_list	*now;

	ans = malloc(get_len_untill_nl(*head));
	now = *head;
	idx_ans = 0;
	while ((*now).idx_nl < 0)
	{
		idx_ans = place_ans(ans,(*now).data,idx_ans);
		now = (*now).next;
	}
	idx_ans = place_ans(ans,(*now).data,idx_ans);
}

char	*get_next_line(int fd)
{
	static struct s_list *(head[1024]);
	char *ans;

	if (fd >= MAX_FD)
		return;
	set_head(&(head[fd]),fd);
	ans = read_head(&(head[fd]),fd);
	reset_head(&(head[fd]));
	return(ans);
}