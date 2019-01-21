/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:19:52 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/21 14:25:12 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft/io.h"
#include "ft/mem.h"
#include <stdbool.h>

static enum e_op	read_op_next(t_readable *in, char buffer[3])
{
	if (ft_memcmp(buffer, "ra\n", 3) == 0)
		return (OP_RA);
	if (ft_memcmp(buffer, "rb\n", 3) == 0)
		return (OP_RB);
	if (ft_memcmp(buffer, "rr", 2) == 0)
	{
		if (buffer[2] == '\n')
			return (OP_RR);
		if (buffer[2] == 'a' && io_peek(in) == '\n')
			return ((in->index++ & 0) + OP_RRA);
		if (buffer[2] == 'b' && io_peek(in) == '\n')
			return ((in->index++ & 0) + OP_RRB);
		if (buffer[2] == 'r' && io_peek(in) == '\n')
			return ((in->index++ & 0) + OP_RRR);
	}
	return (OP_INVALID);
}

static enum e_op	read_op(t_readable *in)
{
	char	buffer[3];
	size_t	r;

	if ((r = io_read(in, buffer, 3)) != 3)
		return (r ? OP_INVALID : OP_NONE);
	if (ft_memcmp(buffer, "sa\n", 3) == 0)
		return (OP_SA);
	if (ft_memcmp(buffer, "sb\n", 3) == 0)
		return (OP_SB);
	if (ft_memcmp(buffer, "ss\n", 3) == 0)
		return (OP_SS);
	if (ft_memcmp(buffer, "pa\n", 3) == 0)
		return (OP_PA);
	if (ft_memcmp(buffer, "pb\n", 3) == 0)
		return (OP_PB);
	return (read_op_next(in, buffer));
}

static bool			is_sorted(struct s_stack *stack)
{
	size_t	i;

	i = 1;
	while (i < stack->size)
	{
		if (stack->elems[i - 1] < stack->elems[i])
			return (false);
		i++;
	}
	return (true);
}

#define ERROR "Error\n"

int					main(int ac, char *av[])
{
	t_readable		stdin;
	uint8_t			buffer[4096];
	enum e_op		op;
	struct s_stacks	stacks;

	stacks = collect(ac, av);
	stdin = init_readable(fill_fd, (void *)0, buffer, sizeof(buffer));
	display(OP_NONE, stacks.a, stacks.b);
	while ((op = read_op(&stdin)) != OP_NONE && op != OP_INVALID)
	{
		exec_op(op, stacks.a, stacks.b);
		display(op, stacks.a, stacks.b);
		usleep(5000);
	}
	if (op == OP_INVALID)
		return (write(2, ERROR, sizeof(ERROR) - 1));
	write(1, stacks.b->size == 0 && is_sorted(stacks.a) ? "OK\n" : "KO\n", 3);
	return (0);
}
