/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:32:45 by janhan            #+#    #+#             */
/*   Updated: 2024/05/28 17:25:58 by sangshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/header_bonus.h"

double	dist(double x, double y, double hx, double hy)
{
	return (sqrt((hx - x) * (hx - x) + (hy - y) * (hy - y)));
}
