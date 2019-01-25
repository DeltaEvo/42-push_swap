/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/25 09:05:10 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "vm.h"
#include "display.h"
#include "optimiser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ft/io.h"

int		*collect_args(size_t size, char *nums[])
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
	return (res);
}

void	exec_and_print(enum e_op op, struct s_stacks stacks)
{
	push_op(op, stacks);
	exec_op(op, stacks.a, stacks.b);
}

void	sort_2(struct s_stacks stacks, enum e_direction to)
{
	const size_t	first = stacks.a->elems[stacks.a->size - 1];
	const size_t	second = stacks.a->elems[stacks.a->size - 2];

	if (to == A && first > second)
		exec_and_print(OP_SA, stacks);
	if (to == B)
	{
		exec_and_print(OP_PB, stacks);
		exec_and_print(OP_PB, stacks);
		if (first > second)
			exec_and_print(OP_SB, stacks);
	}
}

int		head(struct s_stack *stack)
{
	return (stack->elems[stack->size - 1]);
}

void	merge(struct s_stacks stacks, enum e_direction to, size_t count_b, size_t count_a)
{
	const size_t	target_len_b = stacks.b->size - count_b;
	const size_t	target_len_a = stacks.a->size - count_a;
	size_t			rotates;

	rotates = 0;
	if (to == A)
	{
		while (rotates < count_a)
		{
			exec_and_print(OP_RA, stacks);
			rotates++;
		}
		while (rotates && stacks.b->size > target_len_b)
		{
			if (head(stacks.b) > stacks.a->elems[0])
				exec_and_print(OP_PA, stacks);
			else
			{
				rotates--;
				exec_and_print(OP_RRA, stacks);
			}
		}
		while (stacks.b->size > target_len_b)
			exec_and_print(OP_PA, stacks);
	}
	if (to == B)
	{
		while (rotates < count_b)
		{
			exec_and_print(OP_RB, stacks);
			rotates++;
		}
		while (rotates && stacks.a->size > target_len_a)
		{
			if (head(stacks.a) < stacks.b->elems[0])
				exec_and_print(OP_PB, stacks);
			else
			{
				rotates--;
				exec_and_print(OP_RRB, stacks);
			}
		}
		while (stacks.a->size > target_len_a)
			exec_and_print(OP_PB, stacks);
	}
	while (rotates)
	{
		exec_and_print(to == A ? OP_RRA : OP_RRB, stacks);
		rotates--;
	}
}

void	sort(struct s_stacks stacks, enum e_direction to, size_t count)
{
	const size_t	mid = count / 2;

	if (count == 2)
		return (sort_2(stacks, to));
	else if (count <= 1)
	{
		if (to == B)
			exec_and_print(OP_PB, stacks);
		return ;
	}
	sort(stacks, B, mid);
	sort(stacks, A, count - mid);
	merge(stacks, to, mid, count - mid);
}

int		main(int ac, char *av[])
{
	struct s_stacks	stacks;

	stacks = collect(ac, av);
	sort(stacks, A, stacks.a->size);
	push_op(OP_NONE, stacks);
}
