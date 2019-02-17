#include "asm.h"

int		main()
{
	int		fd;
	t_list	*lst;
	t_list	*labels;
	char	*res;
	unsigned bot_size;

	labels = NULL;
	fd = open("ffahey.s", O_RDONLY);
	lst = ft_parse_exec_code(fd);
	lst = ft_process_lst(lst, labels, 1);
	labels = ft_collect_labels(lst);
	lst = ft_process_lst(lst, labels, 2);
//	print_cmd_list(lst);
	res = ft_process_to_bytecode(lst, &bot_size);
	write(1, res, bot_size);
	free(res);
	ft_lstdel(&lst, ft_cmd_destroyer);
	ft_lstdel(&labels, ft_lbl_destroyer);
	return (0);
}
