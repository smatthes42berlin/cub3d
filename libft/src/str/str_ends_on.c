#include "lib_main.h"

bool	str_ends_on(const char *str, const char *ends_on)
{
	int	str_len;
	int	ends_on_len;

	if (!str || !ends_on)
		return (false);
	str_len = ft_strlen(str);
	ends_on_len = ft_strlen(ends_on);
	if (str_len < ends_on_len)
		return (false);
	return (ft_strcmp(str + str_len - ends_on_len, ends_on) == 0);
}
