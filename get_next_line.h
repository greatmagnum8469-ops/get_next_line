/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:12:09 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/25 16:58:57 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

struct s_list
{
	char			*data;
	int				len;
	int				idx_nl;
	struct s_list	*next;
};

char			*get_next_line(int fd);
char			*read_head(struct s_list **head);
void			set_head(struct s_list **head, int fd);
void			reset_head(struct s_list **head);
int				findchar_in_str(char *p, char c);
int				place_ans(char *ans, char *source, int idx);
int				get_len_untill_nl(struct s_list **head);
int				shift_node_data(struct s_list *now);
struct s_list	*new_node(int fd, int *idx_nl, struct s_list **head);
struct s_list	*create_node(int fd, struct s_list **head);

#endif