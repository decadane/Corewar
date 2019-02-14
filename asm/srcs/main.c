#include "asm.h"

int		main()
{
	t_cmd	*cmd;
	char	*str = "zjmp r5";

	cmd = ft_parse_cmd_line(str);
	cmd = ft_cmd_destroyer(cmd);
	return (0);
}
