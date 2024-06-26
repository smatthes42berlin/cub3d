#include "cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

u_int32_t	convert_rgb_to_hex(int *rgb)
{
	unsigned int	hex_color;

	hex_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (hex_color);
}
