#include "lib_main.h"

int	ft_substr_int(char const *s, unsigned int start, size_t len, char **res)
{
	size_t			str_len;
	char			*substr;
	unsigned int	sub_len;

	*res = NULL;
	str_len = ft_strlen(s);
	if (len == 0 || str_len == 0 || str_len <= start)
		return (0);
	if (str_len < (start + len))
		sub_len = str_len - start;
	else
		sub_len = len;
	substr = malloc(sizeof(*substr) * (sub_len + 1));
	if (!substr)
		return (1);
	ft_strlcpy(substr, (s + start), sub_len + 1);
	return (0);
}
