/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimiser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:45:23 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/04 11:07:47 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimiser.h"
#include "vm.h"
#include "display.h"
#include "ft/io.h"
#include <unistd.h>

static size_t	ft_abs(ssize_t a)
{
	return (a > 0 ? a : -a);
}

static void		go_to(ssize_t dist, size_t size, enum e_op op, enum e_op rev)
{
	if (ft_abs(dist) > ft_abs(dist - (ssize_t)size))
		dist -= size;
	if (ft_abs(dist) > ft_abs(dist + (ssize_t)size))
		dist += size;
	while (dist)
	{
		ft_putf("%s\n", op_to_str(dist > 0 ? op : rev));
		dist += dist > 0 ? -1 : 1;
	}
}

static void		flush_ops(enum e_op op, struct s_optimiser_state *state,
		struct s_stacks stacks)
{
	if (stacks.a->size)
		go_to(state->a_pos, stacks.a->size, OP_RA, OP_RRA);
	if (stacks.b->size)
		go_to(state->b_pos, stacks.b->size, OP_RB, OP_RRB);
	state->a_pos = 0;
	state->b_pos = 0;
	if (op != OP_NONE)
		ft_putf("%s\n", op_to_str(op));
}

void			push_op(enum e_op op, struct s_stacks stacks)
{
	static struct s_optimiser_state state = { 0, 0 };

	if (op == OP_SA && stacks.a->size <= 2)
		op = OP_RA;
	if (op == OP_SB && stacks.b->size <= 2)
		op = OP_RB;
	if (op == OP_RA || op == OP_RR)
		state.a_pos++;
	if (op == OP_RB || op == OP_RR)
		state.b_pos++;
	if (op == OP_RRA || op == OP_RRR)
		state.a_pos--;
	if (op == OP_RRB || op == OP_RRR)
		state.b_pos--;
	if (op == OP_PA || op == OP_PB || op == OP_NONE
		|| op == OP_SA || op == OP_SS || op == OP_SB)
		flush_ops(op, &state, stacks);
}
