/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:42:19 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/14 14:57:17 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include <stddef.h>

enum 	e_op {
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_INVALID,
	OP_NONE
};

struct	s_stack {
	size_t	size;
	int		elems[];
};

void	display(enum e_op op, struct s_stack *a, struct s_stack *b);
void	exec_op(enum e_op op, struct s_stack *a, struct s_stack *b);

#endif
