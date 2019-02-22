/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/22 15:00:05 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "vm.h"
#include "display.h"
#include "optimiser.h"
#include <stdlib.h>
#include <stdio.h>

static void	sort_3el(struct s_stacks stacks)
{
	const int	first = stacks.a->elems[2];
	const int	second = stacks.a->elems[1];
	const int	third = stacks.a->elems[0];

	if (first > second && second < third && first < third)
		push_and_exec_op(OP_SA, stacks);
	else if (first < second && third < first)
		push_and_exec_op(OP_RRA, stacks);
	else if (first > second && second < third)
		push_and_exec_op(OP_RA, stacks);
	else if (first > second && second > third)
		push_and_exec_op(OP_SA, stacks);
	else if (first > second && second < third)
		push_and_exec_op(OP_RRA, stacks);
	else if (first < second && second > third && first < third)
		push_and_exec_op(OP_RRA, stacks);
	else
		return ;
	sort_3el(stacks);
}

static void	sort_2(struct s_stacks stacks, enum e_direction to)
{
	const int	first = stacks.a->elems[stacks.a->size - 1];
	const int	second = stacks.a->elems[stacks.a->size - 2];

	if (to == A && first > second)
		push_and_exec_op(OP_SA, stacks);
	if (to == B)
	{
		push_and_exec_op(OP_PB, stacks);
		push_and_exec_op(OP_PB, stacks);
		if (first > second)
			push_and_exec_op(OP_SB, stacks);
	}
}

static void	merge(struct s_stacks stacks, enum e_direction to,
		size_t cb, size_t ca)
{
	const struct s_stack	*stack_c = to == A ? stacks.a : stacks.b;
	const struct s_stack	*stack_o = to == A ? stacks.b : stacks.a;
	const size_t			count = to == A ? ca : cb;
	const size_t			target_len_o = stack_o->size - (to == A ? cb : ca);
	size_t					rotates;

	rotates = 0;
	while (rotates < count)
	{
		push_and_exec_op(to == A ? OP_RA : OP_RB, stacks);
		rotates++;
	}
	while (rotates && stack_o->size > target_len_o)
		if (to == A ? stack_o->elems[stack_o->size - 1] > stack_c->elems[0]
					: stack_o->elems[stack_o->size - 1] < stack_c->elems[0])
			push_and_exec_op(to == A ? OP_PA : OP_PB, stacks);
		else
		{
			rotates--;
			push_and_exec_op(to == A ? OP_RRA : OP_RRB, stacks);
		}
	while (stack_o->size > target_len_o)
		push_and_exec_op(to == A ? OP_PA : OP_PB, stacks);
	while (rotates--)
		push_and_exec_op(to == A ? OP_RRA : OP_RRB, stacks);
}

static void	sort(struct s_stacks stacks, enum e_direction to, size_t count)
{
	const size_t	mid = count / 2;

	if (count == 2)
		return (sort_2(stacks, to));
	else if (count <= 1)
	{
		if (to == B)
			push_and_exec_op(OP_PB, stacks);
		return ;
	}
	sort(stacks, B, mid);
	sort(stacks, A, count - mid);
	merge(stacks, to, mid, count - mid);
}

#define ERROR "Error\n"

int			main(int ac, char *av[])
{
	struct s_stacks	stacks;

	stacks = collect(ac, av);
	if (!stacks.a || !stacks.b)
	{
		write(1, ERROR, sizeof(ERROR) - 1);
		return (1);
	}
	if (!is_sorted(stacks.a))
	{
		if (stacks.a->size == 3)
			sort_3el(stacks);
		else
			sort(stacks, A, stacks.a->size);
		push_and_exec_op(OP_NONE, stacks);
	}
	free(stacks.a);
	free(stacks.b);
}
