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
		free(now);
		now = NULL;
	}
	else if (shift_node_data(now) == 0)
		now = NULL;
	*head = now;
}

struct s_list	*new_node(int fd, int *idx_nl, struct s_list **head)
{
	struct s_list	*node;

	node = malloc(sizeof(struct s_list));
	if (!node)
		return (NULL);
	(*node).data = malloc(BUFFER_SIZE + 1);
	if (!((*node).data))
		return (NULL);
	(*node).len = read(fd, (*node).data, BUFFER_SIZE);
	if ((*node).len <= 0)
	{
		if ((*node).len < 0)
			reset_head(head);
		free((*node).data);
		free(node);
		return (NULL);
	}
	*(((*node).data) + (*node).len) = '\0';
	*idx_nl = findchar_in_str((*node).data, '\n');
	(*node).idx_nl = *idx_nl;
	(*node).next = NULL;
	return (node);
}

void	set_head(struct s_list **head,int fd)
{
	struct s_list	*last_node;
	struct s_list	*node;
	int				idx_nl;
	
	if ((*head != NULL && (**head).idx_nl != -1))
		return;
	last_node = new_node(fd, &idx_nl, head);
	if (last_node == NULL)
		return;
	if (*head == NULL)
		*head = last_node;
	else
		(**head).next = last_node;
	while(idx_nl == -1)
	{
		node = new_node(fd, &idx_nl, head);
		if (node == NULL)
			return;
		(*last_node).next = node;
		last_node = node;
	}
}

char *read_head(struct s_list **head)
{
	char *ans;
	int idx_ans;
	struct s_list	*now;
	int len;

	len = get_len_untill_nl(head);
	ans = malloc(len + 1);
	now = *head;
	idx_ans = 0;
	while ((*now).idx_nl < 0)
	{
		idx_ans = place_ans(ans,(*now).data,idx_ans);
		now = (*now).next;
	}
	if (now != NULL)
	{
		idx_ans = place_ans(ans, (*now).data, idx_ans);
		*(ans + idx_ans) = '\n';
		idx_ans++;
	}
	*(ans + idx_ans) = '\0';
	return (ans);
}

char	*get_next_line(int fd)
{
	static struct s_list *(head[MAX_FD]);
	char *ans;

	if (fd >= 1024 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	set_head(&(head[fd]),fd);
	if ((head[fd]) == NULL)
		return (NULL);
	ans = read_head(&(head[fd]));
	reset_head(&(head[fd]));
	return(ans);
}