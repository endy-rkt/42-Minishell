#include "../header.h"

/////////////////

int	ft_check_size(char *s, char c)
{
	int	i;
	int	array_nbr;
	int	get;

	i = 0;
	array_nbr = 0;
	get = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			get = 1;
		}
		if (get == 1)
			array_nbr++;
		get = 0;
	}
	return (array_nbr);
}

int	ft_check_size_array(char *s, char c, int array_indice)
{
	int	i;
	int	len;
	int	get;

	i = 0;
	len = 0;
	get = -1;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		get++;
		if (get == array_indice)
			return (len);
		len = 0;
	}
	return (len);
}

char	**ft_fill_array(char **new, char *s, char c)
{
	int	i;
	int	index;
	int	j;

	i = 0;
	index = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			new[index][j] = s[i];
			i++;
			j++;
			if (s[i] == c || s[i] == '\0')
			{
				new[index][j] = '\0';
				index++;
			}
		}
	}
	new[index] = NULL;
	return (new);
}

void	ft_freee(char **new_1, int i)
{
	while (i >= 0)
	{
		free(new_1[i]);
		i--;
	}
	free(new_1);
}

int	is_null(char **new_1, int i)
{
	if (new_1[i] == NULL)
	{
		ft_freee(new_1, i);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**new;
	int		i;
	int		array_nbr;

	i = 0;
	len = 0;
	array_nbr = ft_check_size((char *)s, c);
	if (array_nbr == 0)
		return (NULL);
	new = (char **)malloc((array_nbr + 1) * sizeof(char *));
	if (new == NULL)
		return (NULL);
	while (i < array_nbr)
	{
		len = ft_check_size_array((char *)s, c, i);
		if (len != 0)
			new[i] = (char *)malloc((len + 1) * sizeof(char));
		if (is_null(new, i) == 0)
			return (NULL);
		i++;
	}
	new = ft_fill_array(new, (char *)s, c);
	return (new);
}


/////////////////////////////////////////////////

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (strdup(s1 + end + 1));
	while (strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

//////////////////////////////////////////////////

void pwd_prompt(char *path)
{
	const char *blue = "\033[0;33m";
    const char *reset = "\033[0m";
	char	cwd[4096];
	int		i;
	int		count;

	if (chdir(path) != 0)
	{
 		i = 0;
		count = 0;
        getcwd(cwd, sizeof(cwd)); 
		while (count < 3)
		{
			if (cwd[i] == '/')
				count++;
			i++;
		}
		write(1, blue, strlen(blue));
		write(1, "~/", 2);
		while (cwd[i])
		{	
			write(1, &cwd[i], 1);
			i++;
		}
		write(1, reset, strlen(reset));
    }
	else
        perror("cd");
}

void ft_pwd(char *path)
{
	char	pwd[1024];
	int		i;

	if (chdir(path) != 0)
	{
 		i = 0;
        getcwd(pwd, sizeof(pwd)); 
		while (pwd[i])
		{	
			write(1, &pwd[i], 1);
			i++;
		}
    }
	else
        perror("cd");
	write (1, "\n", 1);
}

void ft_echo(char *message)
{
	int i;

	i = 0;
    while (message[i])
	{
		write(1, &message[i], 1);
		i++;
	}
	printf("\n");
}

void	ft_cd(char *path)
{
	char cwd[1024];

	if (chdir(path) == 0)
		;//getcwd(cwd, sizeof(cwd));
	else
        perror("cd");
	write (1, "\n", 1);
}

void ft_copy(char *str, char *dest)
{
    int i;

	i = 0;
    while (str[i])
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
}

char **ft_copy_env(char **envp)
{
    int len;
	int j;
	int k;
	int str_len;
	char **copy;

	len = 0;
	j = 0;
	str_len = 0;
	k = 0;
    while (envp[len])
        len++;
    copy = (char **) malloc((len + 1) * sizeof(char *));
    if (copy == NULL)
        return NULL;
    while (j < len)
    {
        str_len = strlen(envp[j]);
        copy[j] = (char *)malloc((str_len + 1) * sizeof(char));
        if (copy[j] == NULL)
        {
            while (k < j)
			{
                free(copy[k]);
				k++;
			}
            free(copy);
            return NULL;
        }
        ft_copy(envp[j], copy[j]);
		j++;
    }
    copy[len] = NULL;
    return (copy);
}

char **ft_rm_env(char **copy_env, int i)
{
    int len;
	int j;
	int l;
	int k;
	int str_len;
	char **copy;

	len = 0;
	j = 0;
	str_len = 0;
	k = 0;
    while (copy_env[len])
        len++;
    copy = (char **) malloc((len) * sizeof(char *));
	if (copy == NULL)
		return (NULL);
	l = j;
	while (j < len)
    {
		if (j != i)
		{
			str_len = strlen(copy_env[j]);
			copy[l] = (char *)malloc((str_len + 1) * sizeof(char));
			if (copy[l] == NULL)
			{
				while (k < l)
				{
					free(copy[k]);
					k++;
				}
				free(copy);
				return (NULL);
			}
			ft_copy(copy_env[j], copy[l]);
			l++;
		}
		j++;
    }
    copy[l] = NULL;
    return (copy);
}

char 	**ft_unset(char *line_read, char **copy_env)
{
	int i;
	int j;
	int success;
	char **temp;

	i = 0;
	success = 0;
	while (copy_env[i])
	{
		if (copy_env[i][0] == line_read[0])
		{
			j = 1;
			while (line_read[j])
			{
				if (copy_env[i][j] != line_read[j])
				{
					success = 0;
					break ;
				}
				else
					success = 1;
				j++;
			}
		}
		if (success == 1)
		{
			temp = copy_env;
			copy_env = ft_rm_env(temp, i);
			break ;
		}
		i++;
	}
	return (copy_env);
}

/////////////////////////////////////////////////////

int check_valid_name(char *name)
{
    int i;

	i = 0;
    if ((!isalpha(name[0]) && name[0] != '_'))
        return (0);
    while (name[++i] && name[i] != '=')
	{
        if ((!isalnum(name[i]) && name[i] != '_'))
            return (0);
    }
    return (1);
}

void ft_reassign(char *name, char **to_assign)
{
    free(*to_assign);
    *to_assign = strdup(name);
}

int create_or_not(char *name, char **export)
{
    int len;
    int i;

    len = strlen(name);
    i = 0;
    while (export[i])
    {
        if (strncmp(export[i], name, len) == 0 && export[i][len] == '\0')
            return (1);
        i++;
    }
    return (0);
}

char **create_new_export(char *name, char **export)
{
    int len;
    int i;
    char **copy;

    len = 0;
    i = 0;
    while (export[len])
        len++;
    copy = malloc((len + 2) * sizeof(char *));
    if (copy == NULL)
        return NULL;
    while (i < len)
    {
        copy[i] = strdup(export[i]);
        i++;
    }
    copy[len] = strdup(name);
    copy[len + 1] = NULL;
    if (export)
    {
        i = 0;
        while (i < len)
        {
            free(export[i]);
            i++;
        }
        free(export);
    }
    return (copy);
}

int check_if_exist(char *name, char **env, char **export)
{
    int i;
    int len;
    char *equal_sign = strchr(name, '=');

    len = equal_sign ? equal_sign - name : strlen(name);

    i = 0;
    while (export[i])
    {
        if (strncmp(export[i], name, len) == 0 && (export[i][len] == '=' || export[i][len] == '\0'))
        {
            if (equal_sign) {
                ft_reassign(name, &export[i]);  // Reassign only if '=' is present
            }
            return (1);
        }
        i++;
    }
    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], name, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
        {
            if (equal_sign) {
                ft_reassign(name, &env[i]);  // Reassign only if '=' is present
            }
            return (1);
        }
        i++;
    }
    return (0);
}

void ft_export(char *command, char ***existing_export, char **env)
{
    int i;
    char **to_export;

    i = 0;
    to_export = ft_split(command, ' ');
    while (to_export[i])
    {
        if (check_valid_name(to_export[i]))
        {
            if (!check_if_exist(to_export[i], env, *existing_export))
            {
                if (create_or_not(to_export[i], *existing_export) == 0)
                    *existing_export = create_new_export(to_export[i], *existing_export);
            }
        }
        else
            printf("invalid identifier\n");
        i++;
    }
    //ft_free_split(to_export);
}

///////////////////////////////////////////////

int main(int argc, char *argv[], char *envp[])
{
    char *line_read;
    char **copy_env;
    char **export;
	int yes;

	yes = 0;
    (void)argc;
    (void)argv;
    line_read = NULL;
    export = malloc(sizeof(char *));
    export[0] = NULL;
    copy_env = ft_copy_env(envp);

    while (1)
    {
        if (line_read)
        {
            free(line_read);
            line_read = NULL;
        }
        pwd_prompt("pwd");
        line_read = readline("\n\033[0;35m❯ \033[0m");
        add_history(line_read);

        if (strncmp(line_read, "pwd", 3) == 0)
            ft_pwd(line_read + 3);
        else if (strncmp(line_read, "echo ", 5) == 0)
            ft_echo(line_read + 5);
        else if (strncmp(line_read, "cd ", 3) == 0)
            ft_cd(line_read + 3);
        else if (strncmp(line_read, "env", 3) == 0)
        {
            for (int a = 0; copy_env[a]; a++)
                printf("%s\n", copy_env[a]);
			int yes;
			yes = 0;
			for (int i = 0; export[i]; i++)
			{
				if (strchr(export[i], '='))
				{
					for (int a = 0; export[i][a]; a++)
					{	
						printf("%c", export[i][a]);
						if (export[i][a] == '=')
						{
							yes = 1;
							printf("\"");
						}
					}
					if (yes == 1)
						printf("\"");
					printf("\n");
					yes = 0;
				}
            }
        }
        else if (strncmp(line_read, "unset ", 6) == 0)
        {
            char **temp = copy_env;
            copy_env = ft_unset(line_read + 6, temp);
        }
        else if (strncmp(line_read, "export", 6) == 0)
        {
            if (line_read[7] == '\0')
			{
				for (int a = 0; copy_env[a]; a++)
				{
					printf("declare -x ");
					printf("%s\n", copy_env[a]);	
				}
                for (int i = 0; export[i]; i++)
				{
					printf("declare -x ");
					for (int a = 0; export[i][a]; a++)
					{
						printf("%c", export[i][a]);
						if (export[i][a] == '=')
						{
							yes = 1;
							printf("\"");
						}
					}
					if (yes == 1)
						printf("\"");
					printf("\n");
					yes = 0;
                }
            } else {
                ft_export(line_read + 7, &export, copy_env);
            }
        }
        else if (strcmp(line_read, "exit") == 0)
            break;
        else
            printf("Command not found: %s\n", line_read);
        printf("\n");
    }
    for (int i = 0; export[i]; i++) free(export[i]);
    free(export);
    for (int i = 0; copy_env[i]; i++) free(copy_env[i]);
    free(copy_env);
    return 0;
}

