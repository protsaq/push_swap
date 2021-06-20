/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <apinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 06:32:39 by apinto            #+#    #+#             */
/*   Updated: 2021/06/20 16:26:26 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	operate_the_stack_strategically(array *stack, array *other_stack, int elem)
{
	/* LIS can be extended with a swap, in place.
	 * Needs further implementation (there are more conditions that
	 * benefit from swapping) */
	if (stack->stack[1] == stack->start_of_lis_range
		&& stack->stack[0] > stack->start_of_lis_range
		&& stack->stack[0] < stack->end_of_lis_range)
	{
		do_operations(stack, other_stack, "s");
		update_lis_with_elem(stack, elem);
	}
	else
	{
		do_operations(stack, other_stack, "p");
		if (element_is_in_lis(stack, elem, 0))
		{
			/* an element will be pushed to the other_stack;
			 * it then checks whether the new head of current stack is part of the LIS,
			 * and if so, rotate both stacks. This is useful because ???
			very dangerous operation! please protect this accordingly, future alex */
			if (element_is_in_lis(stack, stack->stack[0], 0))
				do_operations(other_stack, stack, "rr");
			else if (other_stack->count > 1)
				do_operations(other_stack, stack, "r");
		}
	}
}

static void	end_of_stack_conditions(list_of_arrays arrays, array *stack)
{
	if (stack->count == stack->lis_size)
	{
		/* rotate until the head of the lis is on top */
		while(stack->lis[0] != stack->stack[0])
			do_operations(stack, other_stack, "r");
		printf("ENDGAME 🍄");
	}
	else
		break_into_lis_algorithm(&arrays);
}

void		break_into_lis_algorithm(list_of_arrays *arrays)
{
	int iter_stack;
	int elem;
	array *this_stack;
	array *other_stack;

	iter_stack = -1;
	this_stack = &arrays->arrays[arrays->count - 2];
	other_stack = &arrays->arrays[arrays->count - 1];
	initializes_array(arrays, 500);
	find_lis(this_stack, 0);
	print_lis(this_stack, 0);
	while (!this_stack->sorted && this_stack->count != this_stack->lis_size)
	{
		elem = this_stack->stack[0];
		if (element_is_in_lis(this_stack, elem, 0))
		{
			/* should this be reverse rotate? */
			do_operations(arrays, "r");
			update_lis_interval(this_stack, 0);
		}
		else
			operate_the_stack_strategically(this_stack, other_stack, elem);
		/* this can be worked upon? */
		iter_stack = -1;
	}
}
