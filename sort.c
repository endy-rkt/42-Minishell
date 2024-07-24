/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:23:46 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/24 15:49:54 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};


int ascending(int a, int b)
{
	return (a <= b);
}

t_list	*create_lst(int data)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void	tmp_sort(t_list  *lst, t_list *l_next,  int (*cmp)(int, int))
{
	int	tmp;

	if (lst)
	{
		if (l_next)
		{
			if (cmp(lst->data, l_next->data) == 0)
			{
				tmp = lst->data;
				lst->data = l_next->data;
				l_next->data = tmp;
			}
			if (l_next->next)
				tmp_sort(lst, l_next->next, cmp);
		}
	}	
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list	*tmp;

	if (lst)
	{
		tmp = lst->next;
		if (tmp)
			tmp_sort(lst, tmp, cmp);
		while (tmp)
		{
			tmp_sort(tmp, tmp->next, cmp);
			tmp = tmp->next;
		}
		return (lst);
	}
	return (NULL);
}

int	main(void)
{
	t_list *lst = create_lst(0);
	t_list *lsta = create_lst(100);
	t_list *lst1 = create_lst(3);
	t_list *lst2 = create_lst(-1);
	t_list *lst3 = create_lst(2);
	t_list *lstb = create_lst(-5466);

	lst->next = lsta;
	lsta->next = lst1;
	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lstb;
	sort_list(lst, ascending);
	while (lst)
	{
		printf("%d\n", lst->data);
		lst = lst->next;
	}
	return (0);
}