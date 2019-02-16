#include "asm.h"

int		main()
{
	int		fd;
	t_list	*lst;

	fd = open("test.s", O_RDONLY);
	lst = ft_parse_exec_code(fd);
	lst = ft_first_process_lst(lst);
	print_cmd_list(lst);
	ft_lstdel(&lst, ft_cmd_destroyer);
	return (0);
}
