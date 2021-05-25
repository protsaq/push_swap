/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <apinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:11:52 by apinto            #+#    #+#             */
/*   Updated: 2021/05/25 06:55:47 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/* places elem at the top of the stack
 * at a space left unfilled; */
static	void place_at_top(array *stack, int elem)
{
	stack->stack[0] = elem;
}

/* places elem at the bottom of the stack
 * at a space left unfilled;
 * stack->count provides the information for the placement */
static	void place_at_bottom(array *stack, int elem)
{
	stack->stack[stack->count - 1] = elem;
}

/* shifs down all elements of a stack by one
 must ALWAYS precede another action to fill stack->stack[0]
 if last elem is out of stack bounds, fill pointer with elem*/
static	void down_top(array *stack, int *last, int *changed)
{
	int i;

	if (stack->count > 0)
	{
		i = 0;
		if (stack->count + 1 > stack->size)
		{
			*last = stack->stack[stack->count - 1];
			*changed = 1;
		}
		while (++i < stack->count - 1)
			stack->stack[i + 1] = stack->stack[i];
		stack->stack[0] = 0;
	}
}

/* shifs up all elements of a stack by one
 * returns the top element (which is now removed) *
 * the last element is now 0 */
static 	int remove_and_up_top(array *stack)
{
	int top;
	int i;

	if (stack->count > 0)
	{
		top = stack->stack[0];
		i = -1;
		while (++i < stack->count - 1)
			stack->stack[i] = stack->stack[i + 1];
		stack->stack[stack->count - 1] = 0;
		return (top);
	}
	return (-1);
}

/* shift all elements up;
 * fills last spot with previous top element */
void	rotate(array *stack)
{
	if (stack->count > 1)
		place_at_bottom(stack, remove_and_up_top(stack));
}

/* shift all elements down;
 * fills first spot with previous last element */
void	reverse_rotate(array *stack)
{
	int tmp;
	int changed;

	tmp = 0;
	changed = 0;
	if (stack->count > 1)
	{
		down_top(stack, &tmp, &changed);
		if (changed)
			place_at_top(stack, tmp);
	}
}

/* swap the first two elements at the top of a stack */
void	swap(array *stack)
{
	int tmp;

	if (stack->count > 1)
	{
		tmp = stack->stack[0];
		stack->stack[0] = stack->stack[1];
		stack->stack[1] = tmp;
	}
}

/* takes the first element of gives
 * puts it on top of receives*/
void	push(array *gives, array *receives)
{
	if (gives->count > 0)
	{
		down_top(receives, NULL, NULL);
		place_at_top(receives, remove_and_up_top(gives));
		gives->count--;
		receives->count++;
	}
}

void operations(array *stack_a, array *stack_b)
{
	rotate(stack_b);
	rotate(stack_a);
	reverse_rotate(stack_a);
}
