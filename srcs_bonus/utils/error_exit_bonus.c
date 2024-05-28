/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:18:10 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:26:19 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

/**
 * @brief
 * "Error\n" 를 출력후 "msg\n"를 출력하고 exit (1);
 * @param msg // 출력시킬 문자열
 */
void	error_exit(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(1);
}
