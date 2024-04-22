#include "lib_main.h"

int	main(void)
{
    char **arr;
	char **res;
    int num_elem;
    int elem_len;
    int i;
    int j;

    i = 0;

    num_elem = 6;
    elem_len = 6;

    allocate_arr_str(&arr, '\0', 6, 5);

    while(i < num_elem) 
    {
        j = 0;
        while(j < elem_len)
        {
            arr[i][j] = j + 65;
            j++;
        }
        i++;
    }   

    print_str_arr_null(arr);

	subarr_arr_str(arr,
					(t_subarr_arr_str){
						0,
						4,
						0,
						4,
					},
					&res);

    ft_printf("\n\n");

    print_str_arr_null(res);

}