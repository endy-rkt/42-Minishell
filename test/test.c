/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/22 23:55:54 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int main(void)
{
	char	*a;
	char	*b;
	char 	*tmp;

	a = strdup("texta");
	b = strdup("textb");
	tmp = a;
	a = b;
	printf("a=%s\n tmp=%s\n", a, tmp);
}