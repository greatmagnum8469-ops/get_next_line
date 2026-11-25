/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzheng2 <hzheng2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:12:09 by hzheng2           #+#    #+#             */
/*   Updated: 2026/11/24 19:50:10 by hzheng2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#  define MAX_FD 1024
# endif

typedef struct s_list
{
	char *data;
	int len;
	int idx_nl;
	struct s_list *next;
};

char *get_next_line(int fd);