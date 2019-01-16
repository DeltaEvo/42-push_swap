/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/16 16:14:21 by dde-jesu         ###   ########.fr       */
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

size_t	min(size_t a, size_t b)
{
	return (a > b ? b : a);
}

void	merge(int *n, size_t start, size_t mid, size_t end, int *tmp)
{
	const size_t	l_size = mid - start;
	const size_t	r_size = end - mid;
	size_t			i;

	if ((end - start) == 1)
	{
		printf("ra\n");
		return ;
	}
	//fprintf(stderr, "Size: %zu, %zu -> %zu\n", end - start, start, end);
	//fprintf(stderr, "Mid: %zu, LSize: %zu, RSize: %zu\n", mid, l_size, r_size);
	if ((end - start) == 2)
	{
		if (n[start] > n[end-1])
		{
			printf("sa\n");
			*tmp = n[end - 1];
			n[end - 1] = n[start];
			n[start] = *tmp;
		}
		printf("ra\n");
		printf("ra\n");
		return ;
	}
	i = 0;
	while (i < l_size)
	{
		printf("pb\n");
		printf("rb\n");
		tmp[i] = n[start + i];
		i++;
	}
	i = 0;
	while (i < r_size)
	{
		tmp[l_size + i] = n[mid + i];
		i++;
	}

	size_t j = 0;
	size_t k = start;
	i = 0;

	while (i < l_size && j < r_size)
	{
		if (tmp[i] <= tmp[l_size + j])
		{
			printf("pa\n");
			n[k] = tmp[i];
			i++;
		}
		else
		{
			n[k] = tmp[l_size + j];
			j++;
		}
		printf("ra\n");
		k++;
	}

	while (i < l_size)
	{
		printf("pa\n");
		printf("ra\n");
		n[k] = tmp[i];
		i++;
		k++;
	}

	while (j < r_size)
	{
		printf("ra\n");
		n[k] = tmp[l_size + j];
		j++;
		k++;
	}
}

void	sort(int *n, size_t size)
{
	size_t	curr_size;
	size_t	start;
	size_t	end;
	int		*tmp;

	curr_size = 1;
	tmp = malloc(size * sizeof(int));
	while (curr_size < size)
	{
		start = 0;
		while (start < size)
		{
			end = min(start + 2 * curr_size, size);
			merge(n, start, min(start + curr_size, end), end, tmp);
			start += 2 * curr_size;
		}		
		curr_size = 2 * curr_size;
	}
}

int	main(int ac, char *av[])
{
	int	*list;
	//size_t i;

	list = collect_args(ac - 1, av + 1);	
	sort(list, ac - 1);
}
