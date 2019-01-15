/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/15 16:35:08 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	*collect_args(size_t size, char *nums[])
{
	int		*res;
	size_t	i;

	if (!(res = malloc(size * sizeof(int))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = atoi(nums[i]);
		i++;
	}
	return res;
}

void	go_to(size_t from, size_t to, size_t size)
{
	ssize_t	dist;

	dist = ((ssize_t)to - (ssize_t)from) % (ssize_t)size;
	if (labs(dist) > labs(dist - (ssize_t)size))
		dist -= size;
	if (labs(dist) > labs(dist + (ssize_t)size))
		dist += size;
	while (dist)
	{
		printf(dist > 0 ? "ra\n" : "rra\n");
		dist += dist > 0 ? -1 : 1;
	}
}

void	go_to2(size_t from, size_t to, size_t size)
{
	size_t	i;

	(void)size;
	//printf("from %zu -> to %zu\n", from, to);
	//printf("%zd\n", dist);
	if (from < to)
	{
		//printf("from %zu -> to %zu\n", from, to);
		to = from + ((to - from) % size);
		//printf("from %zu -> to %zu\n", from, to);
		i = from;
		while (i < to)
		{
			printf("ra\n");
			i++;
		}
	} else if (from > to) {
		i = from;
		//printf("from %zu -> to %zu\n", from, to);
		to = from - ((from - to) % size);
		//printf("from %zu -> to %zu\n", from, to);
		while (i > to)
		{
			printf("rra\n");
			i--;
		}
	}
}

void	insertion_sort(int *list, size_t size)
{
	size_t	i;
	size_t	j;
	int		x;
	size_t	last;

	i = 1;
	last = 0;
	while (i < size)
	{
		x = list[i];
		j = i;
		while (j > 0 && list[j - 1] > x)
		{
			list[j] = list[j - 1];
			j--;
		}
		if (i != j)
		{
			if (i == j + 1 || i + 1 == j)
			{
				go_to(last, j, size);
				printf("sa\n");
				last = j;
			}
			else
			{
				go_to(last, i, size);
				printf("pb\n");
				go_to(i, j, size - 1);
				printf("pa\n");
				last = j;
			}
			list[j] = x;
		}
		i++;
	}
	go_to(last, size, size);
}

int	main(int ac, char *av[])
{
	int	*list;

	list = collect_args(ac - 1, av + 1);	
	insertion_sort(list, ac - 1);
}
