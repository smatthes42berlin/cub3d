#include "lib_main.h"

static int	sort_start_end(t_subarr_arr_str *sub_def);

int	subarr_arr_str(char **org_arr, t_subarr_arr_str sub_def, char ***res)
{
	int	i[2];
	int	num_elem;
	int	str_len;

	if (!org_arr || !*org_arr)
		return (0);
	sort_start_end(&sub_def);
	num_elem = ft_abs(sub_def.str_num_end - sub_def.str_num_start);
	str_len = ft_abs(sub_def.str_start - sub_def.str_end);
	ft_printf("subarr num_elem %d\n", num_elem);
	ft_printf("subarr str_len %d\n", str_len);
	allocate_arr_str(res, '\0', num_elem + 1, str_len + 1);
	if (!*res)
		return (1);
	i[0] = 0;
	while (i[0] < num_elem)
	{
		i[1] = 0;
		while (i[1] < str_len)
		{
			(*res)[i[0]][i[1]] = org_arr[i[0]][sub_def.str_start + i[1]];
			(i[1])++;
		}
		(i[0])++;
	}
	(*res)[i[0]] = NULL;
	return (0);
}

static int	sort_start_end(t_subarr_arr_str *sub_def)
{
	int tmp;

	if (sub_def->str_start > sub_def->str_end)
	{
		tmp = sub_def->str_end;
		sub_def->str_end = sub_def->str_start;
		sub_def->str_start = tmp;
	}
	if (sub_def->str_num_start > sub_def->str_num_end)
	{
		tmp = sub_def->str_num_end;
		sub_def->str_num_end = sub_def->str_num_start;
		sub_def->str_num_start = tmp;
	}
	return (0);
}