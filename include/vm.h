/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 09:57:23 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/01 10:00:08 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <stddef.h>
# include <stdbool.h>

enum			e_op {
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

struct			s_stack {
	size_t	size;
	int		elems[];
};

struct			s_stacks {
	struct s_stack	*a;
	struct s_stack	*b;
};

void			exec_op(enum e_op op, struct s_stack *a, struct s_stack *b);
struct s_stacks	collect(int ac, char *av[]);
bool			is_sorted(struct s_stack *stack);

#endif
