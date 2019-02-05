/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-jesu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:19:52 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/02/05 10:45:12 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ft/args.h"
#include "ft/io.h"
#include "ft/mem.h"
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>

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

#define ERROR "Error\n"

static void			exec_and_show(enum e_op op, struct s_stacks stacks,
		bool visual, int fd)
{
	exec_op(op, stacks.a, stacks.b);
	if (visual)
	{
		display(op, stacks.a, stacks.b, fd);
		usleep(500000);
	}
}

static int			run(uintptr_t fd, bool visual, struct s_stacks stacks)
{
	t_readable		stdin;
	uint8_t			buffer[4096];
	enum e_op		op;
	int				ret;

	stdin = init_readable(fill_fd, (void *)fd, buffer, sizeof(buffer));
	if (visual)
		display(OP_NONE, stacks.a, stacks.b, fd);
	while ((op = read_op(&stdin)) != OP_NONE && op != OP_INVALID)
		exec_and_show(op, stacks, visual, (int)fd);
	close(fd);
	if (op == OP_INVALID)
		ret = (write(2, ERROR, sizeof(ERROR) - 1) & 0) + 1;
	if (stacks.b->size == 0 && is_sorted(stacks.a))
		ret = write(1, "OK\n", 3) & 0;
	else
		ret = (write(1, "KO\n", 3) & 0) + 1;
	free(stacks.a);
	free(stacks.b);
	return (ret);
}

#define ERROR "Error\n"

int					main(int argc, char *argv[])
{
	int				ret;
	bool			visual;
	char			*file;
	struct s_stacks	stacks;
	const t_arg		args[] = {
		{ ARG_BOOLEAN, 'v', "visual", &visual, "Visual" },
		{ ARG_STRING, 'f', "file", &file, "Read from file" },
		{ ARG_END, 0, 0, 0, 0 }};

	visual = false;
	file = NULL;
	if ((ret = parse_args(args, argc, argv)) < 0)
		return (args_usage(args, argv[0], "", "") || 1);
	if (argc == ret)
		return (0);
	stacks = collect(argc - (ret - 1), argv + (ret - 1));
	if (!stacks.a || !stacks.b)
	{
		write(1, ERROR, sizeof(ERROR) - 1);
		return (1);
	}
	return (run(file ? (uintptr_t)open(file, O_RDONLY) : 0, visual, stacks));
}
