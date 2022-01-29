/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:15:50 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/29 17:16:00 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp -> next != NULL)
	{
		i++;
		temp = temp -> next;
	}
	if (temp -> next == null)
		i++;
	return (i);
}