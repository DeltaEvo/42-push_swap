/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimiser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:52:59 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/05 10:14:14 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMISER_H
# define OPTIMISER_H
# include "vm.h"
# include <unistd.h>

struct	s_optimiser_state {
	ssize_t		a_pos;
	ssize_t		b_pos;
};

void	push_and_exec_op(enum e_op op, struct s_stacks stacks);

#endif
