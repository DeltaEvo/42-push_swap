/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:58:24 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/01/21 14:21:06 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"
#include "optimiser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	*collect_args(size_t size, char *nums[])
{
	int		*res;
	size_t	i;

	if (!(res = malloc(size * sizeof(int))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = atoi(nums[i]);
		i++;
	}
	return res;
}

enum e_direction {
	A,
	B
};

void	exec_and_print(enum e_op op, struct s_stacks stacks)
{
	push_op(op, stacks);
	exec_op(op, stacks.a, stacks.b);
	//display(op, stacks.a, stacks.b);
	//printf("%s\n", op_to_str(op));
}

void	sort_2(struct s_stacks stacks, enum e_direction to)
{
	const size_t	first = stacks.a->elems[stacks.a->size - 1];
	const size_t	second = stacks.a->elems[stacks.a->size - 2];

	if (to == A && first > second)
		exec_and_print(OP_SA, stacks);
	if (to == B)
	{
		if (second > first)
			exec_and_print(OP_SA, stacks);
		exec_and_print(OP_PB, stacks);
		exec_and_print(OP_PB, stacks);
	}
}

int		head(struct s_stack *stack)
{
	return stack->elems[stack->size - 1];
}

void	merge(struct s_stacks stacks, enum e_direction to, size_t count_b, size_t count_a)
{
	const size_t	target_len_b = stacks.b->size - count_b;
	const size_t	target_len_a = stacks.a->size - count_a;
	size_t			rotates;

	rotates = 0;
	if (to == A)
	{
		while (rotates < count_a && stacks.b->size > target_len_b)
		{
			if (head(stacks.b) < head(stacks.a))
			{
				count_a++;
				exec_and_print(OP_PA, stacks);
			}
			else
			{
				rotates++;
				exec_and_print(OP_RA, stacks);
			}
		}
		while (stacks.b->size > target_len_b)
		{
			exec_and_print(OP_PA, stacks);
			exec_and_print(OP_RA, stacks);
			rotates++;	
		}
	}
	if (to == B)
	{
		while (rotates < count_b && stacks.a->size > target_len_a)
		{
			if (head(stacks.a) < head(stacks.b))
			{
				count_b++;
				exec_and_print(OP_PB, stacks);
			}
			else
			{
				rotates++;	
				exec_and_print(OP_RB, stacks);
			}
		}
		while (stacks.a->size > target_len_a)
		{
			exec_and_print(OP_PB, stacks);
			exec_and_print(OP_RB, stacks);
			rotates++;	
		}
	}
	while (rotates > 0)
	{
		exec_and_print(to == A ? OP_RRA : OP_RRB, stacks);
		rotates--;
	}
}

void	subsort(struct s_stacks stacks, enum e_direction to, size_t count)
{
	const size_t	mid = count / 2;
	if (count == 2)
	{
		//printf("Special sort 2 to %c\n", to == A ? 'a' : 'b');
		sort_2(stacks, to);
		return ;
	}
	else if (count <= 1)
	{
		if (to == B)
		{
			//printf("Move to B\n");
			exec_and_print(OP_PB, stacks);
		}
		return ;
	}
	subsort(stacks, B, mid);
	subsort(stacks, A, count - mid);
	//printf("Subsort to: %c, size: %zu\n", to == A ? 'a' : 'b', count);
	merge(stacks, to, mid, count - mid);
}

void	sort(struct s_stacks stacks)
{
	subsort(stacks, A, stacks.a->size);
}

int		main(int ac, char *av[])
{
	struct s_stacks	stacks;

	stacks = collect(ac, av);
	sort(stacks);
	push_op(OP_NONE, stacks);
}
