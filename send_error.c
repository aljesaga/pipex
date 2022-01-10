/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:32:41 by alsanche          #+#    #+#             */
/*   Updated: 2022/01/10 12:32:41 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, str[i], 1);
		i++;
	}
}

void	send_error(int n, char *str)
{
	if (n == 0)
	{	
		ft_putstr("zsh: permission denied: ");
		ft_putstr(str);
		write(1, "\n", 1);
	}
	else if (n == 1)
	{
		ft_putstr(str);
		ft_putstr("is invalid\n");
		exit (-1);
	}
	else if  (n == 2)
	{
		ft_putstr(str);
		ft_putstr("it doesn't work\n");
		exit (-1);
	}
}

char *str_path(char **enpv)
{
	int	i;

	i = 0;
	while (enpv[i])
	{
		if (enpv[i][0] == "P" && enpv[i][1] == "A"
			&& enpv[i][2] == "T" && enpv[i][3] == "H")
			return (enpv[i]);
		i++;
	}
	return (NULL);
}

char	**find_path(char **enpv)
{
	char	**gps;
	char	*path;
	char	*aux;
	int		i;

	path = str_path(enpv);
	if (!path)
		send_error(1, "PATH");
	i = -1;
	gps = ft_split(path, ":");
	while(gps[++i])
	{
		aux = gps[i];
		gps[i] = ft_strjoin(aux, "/");
		free(aux);
	}
	return (gps);
}
