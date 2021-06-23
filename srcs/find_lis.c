/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <apinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:19:27 by apinto            #+#    #+#             */
/*   Updated: 2021/06/23 08:19:41 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/* returns an index that signifies the list
 * in which to insert the new node;
 *		-1 means it is smallest among all candidates,
 *			thus create a new list;
 *		chains->count - 1 means it is largest among all candidates,
 *			thus clone the largest list and append it;
 *		any other number signifies the index of the list to append to. */
int		finds_localisation_of_node(chains *chain, int elem)
{
	int iter;

	iter = 0;
	while (iter < chain->count && elem > chain->tails[iter])
		iter++;
	return (iter);
}

/* updates the size array and handles
 * determining which is the largest sequence */
void	size_and_largest_sequence(chains *chain, int index, int size)
{
	chain->sizes[index] = size;
	if (size >= chain->largest_size)
	{
		chain->largest_active = chain->heads[index];
		chain->largest_size = size;
	}
}

void	copies_new_largest_list(int *old_list, int *new_list, int size)
{
	int i;
	i = -1;
	if (old_list != NULL && old_list != new_list)
		while (++i < size)
			new_list[i] = old_list[i];
}

int		find_index_by_size(chains *chain, int size)
{
	int res;

	res = 0;
	while (chain->sizes[res] != size)
		res++;
	return res;
}

/*
 * adds the size to the chain, and triggers deprecated sequences
 * new_list should be statically allocated outside of the chain
 * and then added; this avoids redundant copies of the same list in the chain */
void	extends_list(chains *chain, int elem, int index)
{
	int *new_list;
	int *list;
	int size;
	int copy_from;

	if (index == chain->count)
	{
		list = chain->largest_active;
		size = chain->largest_size + 1;
		new_list = chain->heads[chain->count];
		chain->count += 1;
	}
	else
	{
		new_list = chain->heads[index];
		size = chain->sizes[index];
		copy_from = find_index_by_size(chain, size - 1);
		list = chain->heads[copy_from];
	}
	new_list[size - 1] = elem;
	copies_new_largest_list(list, new_list, size - 1);
	chain->tails[index] = elem;
	size_and_largest_sequence(chain, index, size);
}

void	initializes_lis_variables(array *stack, int first)
{
	chain.largest_size = 0;
	chain.largest_active = NULL;
	chain.count = 0;
	if (first)
	{
		chain.really_largest_active = NULL;
		chain.really_largest_size = 0;
	}
}

void	find_lis(array *stack)
{
	chains chain;
	int	rotation;
	int index;
	int iter;
	int elem;
	int	*source;
	int	number_of_elems;

	source = stack->stack;
	number_of_elems = stack->count;
	rotation = -1;
	initializes_lis_variables(stack, 1);
	while (++rotation < number_of_elems)
	{
		iter = -1;
		while (++iter < number_of_elems)
		{
			elem = source[iter];
			index = finds_localisation_of_node(&chain, elem);
			extends_list(&chain, elem, index);
		}
		if (chain.largest_size > stack->lis_size)
		{
			ft_memcpy(stack->lis, chain.largest_active, 4 * chain.largest_size);
			stack->lis_size = chain.largest_size;
			stack->rotations = rotation;
		}
		rotate(stack);
		initializes_lis_variables(stack, 0);
	}
	update_lis_interval(stack, 1);
}
