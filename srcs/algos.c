/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <apinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 06:32:39 by apinto            #+#    #+#             */
/*   Updated: 2021/06/23 07:50:05 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	operate_the_stack_strategically(list_of_arrays *arrays, int elem)
{
	array *stack;
	array *other_stack;

	/* change stack index back to 1 and 2 */
	stack = &arrays->arrays[arrays->count - 2];
	other_stack = &arrays->arrays[arrays->count - 3];
	/* LIS can be extended with a swap, in place.
	 * Needs further implementation (there are more conditions that
	 * benefit from swapping) */
	if ((stack->stack[1] == stack->start_of_lis_range
		&& stack->stack[0] > stack->start_of_lis_range
		&& stack->stack[0] < stack->end_of_lis_range) ||
		(stack->size >= 2 && stack->stack[1] == stack->lis[stack->lis_size - 1]
		&& stack->stack[0] > stack->stack[1]))
	{
		do_operations(arrays, "s", 0);
		update_lis_with_elem(stack, elem);
	}
	else
	{
		do_operations(arrays, "p", 0);
		if (element_is_in_lis(stack, elem, 0))
		{
			/* an element will be pushed to the other_stack;
			 * it then checks whether the new head of current stack is part of the LIS,
			 * and if so, rotate both stacks. This is useful because ???
			very dangerous operation! please protect this accordingly, future alex */
			if (element_is_in_lis(stack, stack->stack[0], 0))
				do_operations(arrays, "rr", 0);
			else if (other_stack->count > 1)
				do_operations(arrays, "r", 0);
		}
	}
}

static void find_target(array *stack, int elem, char *dir, int *target_lis)
{
	int lis_position;
	int iter;

	lis_position = 0;
	while(elem > stack->lis[lis_position] && lis_position < stack->lis_size - 1)
		lis_position++;
	*target_lis = stack->lis[lis_position];
	iter = 0;
	while (stack->stack[iter] != stack->lis[lis_position])
		iter++;
	if (iter < stack->count / 2)
		ft_strlcpy(dir, "r", 2);
	else
		ft_strlcpy(dir, "revr", 5);
}

static void	merge_with_previous_lis(list_of_arrays *arrays)
{
	int iter;
	array *stack;
	array *other_stack;
	int target_lis;
	char direction[5];

	iter = -1;
	arrays->count--;
	stack = &arrays->arrays[arrays->count - 1];
	other_stack = &arrays->arrays[arrays->count - 2];
	while (stack->count != 0)
	{
		/* probably decide whether to rotate or reverse rotate!! */
		if ((stack->stack[0] > other_stack->stack[other_stack->count - 1]
			&& stack->stack[0] < other_stack->stack[0]) ||
			(other_stack->stack[0] == other_stack->lis[0]
			&& stack->stack[0] < other_stack->stack[0]) ||
			(other_stack->stack[other_stack->count - 1] == other_stack->lis[other_stack->lis_size - 1]
			&& stack->stack[0] > other_stack->stack[other_stack-> count - 1]))
				do_operations(arrays, "p", 1);
		else
		{
			find_target(other_stack, stack->stack[0], direction, &target_lis);
			if (target_lis == other_stack->lis[other_stack->lis_size -1])
				while (other_stack->stack[other_stack->count - 1] != target_lis)
					do_operations(arrays, direction, 0);
			else
				while (other_stack->stack[0] != target_lis)
					do_operations(arrays, direction, 0);
			do_operations(arrays, "p", 1);
		}
	}
}

static void	end_of_stack_conditions(list_of_arrays *arrays)
{
	array *stack;
	array *other_stack;

	stack = &arrays->arrays[arrays->count - 2];
	other_stack = &arrays->arrays[arrays->count - 1];

	if (other_stack->count != 0)
		break_into_lis_algorithm(arrays);
	if (stack->identity != 0)
		merge_with_previous_lis(arrays);
	else
		while(stack->stack[0] > stack->stack[stack->count - 1])
			do_operations(arrays, "r", 0);
}

void		break_into_lis_algorithm(list_of_arrays *arrays)
{
	int iter_stack;
	int elem;
	array *this_stack;
	array *other_stack;

	iter_stack = -1;
	initializes_array(arrays, 500);
	this_stack = &arrays->arrays[arrays->count - 2];
	other_stack = &arrays->arrays[arrays->count - 1];
	find_lis(this_stack, 0);
	print_lis(this_stack);
	while (this_stack->count != this_stack->lis_size)
	{
		elem = this_stack->stack[0];
		if (element_is_in_lis(this_stack, elem, 0))
		{
			/* should this be reverse rotate? */
			do_operations(arrays, "r", 0);
			update_lis_interval(this_stack, 0);
		}
		else
			operate_the_stack_strategically(arrays, elem);
	}
	end_of_stack_conditions(arrays);
}
