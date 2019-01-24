/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:56:50 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/24 14:14:09 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

static void		swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void		rotate_reverse(struct s_stack *stack)
{
	size_t	i;
	int		tmp;

	i = 0;
	tmp = stack->elems[0];
	while (i < stack->size - 1)
	{
		stack->elems[i] = stack->elems[i + 1];
		i++;
	}
	stack->elems[stack->size - 1] = tmp;
}

static void		rotate(struct s_stack *stack)
{
	size_t	i;
	int		tmp;

	i = stack->size;
	tmp = stack->elems[stack->size - 1];
	while (--i)
		stack->elems[i] = stack->elems[i - 1];
	stack->elems[0] = tmp;
}

struct s_stacks	collect(int ac, char *av[])
{
	const size_t	len = ac - 1;
	struct s_stacks	stacks;

	stacks.a = malloc(sizeof(*stacks.a) + len * sizeof(int));
	stacks.b = malloc(sizeof(*stacks.b) + len * sizeof(int));
	stacks.a->size = len;
	stacks.b->size = 0;
	while (--ac)
		stacks.a->elems[len - ac] = atoi(av[ac]);
	return (stacks);
}

void			exec_op(enum e_op op, struct s_stack *a, struct s_stack *b)
{
	if ((op == OP_SS || op == OP_SA) && a->size >= 2)
		swap(a->elems + a->size - 1, a->elems + a->size - 2);
	if ((op == OP_SS || op == OP_SB) && b->size >= 2)
		swap(b->elems + b->size - 1, b->elems + b->size - 2);
	if (op == OP_PA && b->size)
		a->elems[a->size++] = b->elems[--b->size];
	if (op == OP_PB && a->size)
		b->elems[b->size++] = a->elems[--a->size];
	if ((op == OP_RA || op == OP_RR) && a->size >= 2)
		rotate(a);
	if ((op == OP_RB || op == OP_RR) && b->size >= 2)
		rotate(b);
	if ((op == OP_RRA || op == OP_RRR) && a->size >= 2)
		rotate_reverse(a);
	if ((op == OP_RRB || op == OP_RRR) && b->size >= 2)
		rotate_reverse(b);
}
