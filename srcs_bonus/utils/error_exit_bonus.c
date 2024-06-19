/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:18:10 by janhan            #+#    #+#             */
/*   Updated: 2024/06/19 12:57:07 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/**
 * @brief
 * print "ERROR\n" and print msg and exit (1);
 * @param msg // string to print
 */
void	error_exit(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(1);
}
