/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:42:19 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/21 11:27:22 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "vm.h"

void	display(enum e_op op, struct s_stack *a, struct s_stack *b);
char	*op_to_str(enum e_op op);

#endif
