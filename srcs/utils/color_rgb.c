/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janhan <janhan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:35:34 by janhan            #+#    #+#             */
/*   Updated: 2024/05/13 15:15:12 by janhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	create_color(int red, int green, int blue)
{
	return ((int)(255.999 * red) << 16) + ((int)(255.999 * green) << 8) + ((int)(255.999 * blue));
}

int calculate_color(double distance)
{
	double	sensitivity;

	sensitivity = 0.0004;
	double rounded_depth = round(distance / 2) * 2;
	// 깊이에 따른 색상 값을 계산하는 함수
	double brightness = 255.0 / (1 + pow(rounded_depth, 5) * sensitivity); // 깊이에 따른 밝기 계산
	int color = (int)(brightness * 3); // 밝기 값을 RGB 색상 값으로 변환
	printf("color [%d]\n", color);
	return color;
}

unsigned int	create_color_hex(int red, int green, int blue, int alpha)
{
	// 각 색상 값을 0부터 255까지의 범위로 조정
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	alpha = (alpha < 0) ? 0 : (alpha > 255) ? 255 : alpha;

	// 16진수로 변환하여 색상을 만듦
	unsigned int color = (alpha << 24) | (red << 16) | (green << 8) | blue;
	return color;
}
