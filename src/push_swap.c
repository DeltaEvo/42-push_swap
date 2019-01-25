/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/25 14:47:04 by dde-jesu         ###   ########.fr       */
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

static void	exec_and_print(enum e_op op, struct s_stacks stacks)
{
	push_op(op, stacks);
	exec_op(op, stacks.a, stacks.b);
}

static void	sort_2(struct s_stacks stacks, enum e_direction to)
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
		exec_and_print(to == A ? OP_RA : OP_RB, stacks);
		rotates++;
	}
	while (rotates && stack_o->size > target_len_o)
		if (to == A ? stack_o->elems[stack_o->size - 1] > stack_c->elems[0]
					: stack_o->elems[stack_o->size - 1] < stack_c->elems[0])
			exec_and_print(to == A ? OP_PA : OP_PB, stacks);
		else
		{
			rotates--;
			exec_and_print(to == A ? OP_RRA : OP_RRB, stacks);
		}
	while (stack_o->size > target_len_o)
		exec_and_print(to == A ? OP_PA : OP_PB, stacks);
	while (rotates--)
		exec_and_print(to == A ? OP_RRA : OP_RRB, stacks);
}

static void	sort(struct s_stacks stacks, enum e_direction to, size_t count)
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

int			main(int ac, char *av[])
{
	struct s_stacks	stacks;

	stacks = collect(ac, av);
	sort(stacks, A, stacks.a->size);
	push_op(OP_NONE, stacks);
}
