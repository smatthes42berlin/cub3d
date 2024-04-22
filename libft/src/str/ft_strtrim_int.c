#include "lib_main.h"

int	ft_strtrim_int(char const *s1, char const *set, char **res)
{
	size_t	set_len;
	size_t	s1_len;
	size_t	rem_c_start;
	size_t	rem_c_end;

	rem_c_start = 0;
	rem_c_end = 0;
	*res = NULL;
	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	if (set_len == 0 || s1_len == 0)
		return (0);
	while (s1[rem_c_start] && ft_strchr((char *)set, s1[rem_c_start]) != NULL)
		rem_c_start += 1;
	while (s1[rem_c_start] && ft_strrchr((char *)set, s1[s1_len - rem_c_end - 1]) != NULL)
		rem_c_end += 1;
	if (ft_substr_int(s1, rem_c_start, s1_len - rem_c_start - rem_c_end, res))
		return (1);
	return (0);
}
