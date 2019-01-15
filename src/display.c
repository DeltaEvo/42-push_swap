/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:48:40 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/15 16:11:48 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "ft/io.h"
#include <stdbool.h>

#define ANSI_ESC "\33["
#define ANSI_CLEAR ANSI_ESC "K"
#define ANSI_CYAN ANSI_ESC "96m"
#define ANSI_GREEN ANSI_ESC "92m"
#define ANSI_RED ANSI_ESC "91m"
#define ANSI_YELLOW ANSI_ESC "93m"
#define ANSI_RESET ANSI_ESC "0m"

#define OP_HEADER ANSI_CLEAR ANSI_CYAN "OP" ANSI_RESET ": " ANSI_YELLOW

static char		*op_to_str(enum e_op op)
{
	static char		*name[] = {
		[OP_SA] = "sa",
		[OP_SB] = "sb",
		[OP_SS] = "ss",
		[OP_PA] = "pa",
		[OP_PB] = "pb",
		[OP_RA] = "ra",
		[OP_RB] = "rb",
		[OP_RR] = "rr",
		[OP_RRA] = "rra",
		[OP_RRB] = "rrb",
		[OP_RRR] = "rrr",
		[OP_NONE] = ""
	};

	return (op <= OP_RRR ? name[op] : NULL);
}

void			display(enum e_op op, struct s_stack *a, struct s_stack *b)
{
	int			i;

	/*if (op != OP_NONE)
		ft_putf(isatty(0) ? ANSI_ESC "4A" : ANSI_ESC "3A");*/
	ft_putf(ANSI_CLEAR "" ANSI_CYAN "Stack A" ANSI_RESET ":");
	i = a->size;
	while (--i >= 0)
	{
		if (i > 0)
			ft_putf(a->elems[i] < a->elems[i - 1] ? ANSI_GREEN : ANSI_RED);
		else
			ft_putf(a->elems[i] > a->elems[i + 1] ? ANSI_GREEN : ANSI_RED);
		ft_putf(" %d", a->elems[i]);
	}
	ft_putf("\n" ANSI_CLEAR "" ANSI_CYAN "Stack B" ANSI_RESET ":");
	i = b->size;
	while (--i >= 0)
		ft_putf(" %d", b->elems[i]);
	ft_putf("\n" OP_HEADER "%s" ANSI_RESET "\n", op_to_str(op));
}
