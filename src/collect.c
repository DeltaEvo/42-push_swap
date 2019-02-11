/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 09:40:06 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/11 11:12:50 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>
#include <limits.h>

static bool		ft_atoi(const char *str, int *res)
{
	long	result;
	char	mod;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	result = 0;
	mod = *str == '-' || *str == '+' ? *str++ == '-' : 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str++ - '0';
		if (result > ((long)INT_MAX + mod))
			return (false);
	}
	if (*str != '\0')
		return (false);
	*res = (mod ? -result : result);
	return (true);
}

bool			is_sorted(struct s_stack *stack)
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

struct s_stacks	check_duplicates(struct s_stacks stacks)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < stacks.a->size)
	{
		j = i + 1;
		while (j < stacks.a->size)
		{
			if (stacks.a->elems[i] == stacks.a->elems[j])
			{
				free(stacks.a);
				free(stacks.b);
				stacks.a = NULL;
				stacks.b = NULL;
				return (stacks);
			}
			j++;
		}
		i++;
	}
	return (stacks);
}

struct s_stacks	collect(int ac, char *av[])
{
	const size_t	len = ac - 1;
	struct s_stacks	stacks;

	if (!(stacks.a = malloc(sizeof(*stacks.a) + len * sizeof(int))))
		return (stacks);
	if (!(stacks.b = malloc(sizeof(*stacks.b) + len * sizeof(int))))
	{
		free(stacks.a);
		return (stacks);
	}
	stacks.a->size = len;
	stacks.b->size = 0;
	while (--ac)
		if (!ft_atoi(av[ac], stacks.a->elems + len - ac))
		{
			free(stacks.a);
			free(stacks.b);
			stacks.a = NULL;
			stacks.b = NULL;
			return (stacks);
		}
	return (check_duplicates(stacks));
}
