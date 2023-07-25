


void	expand_env_var(t_token **head)
{
	t_token	*token;
	char	*env_var;
	char	*new_line;
	int		i;
	int		j;
	int 	f = 0;

	token = (*head);
	i = 0;
	while (token)
	{
		if (token->type == Word)
		{
			while(token->line && token->line[i])
			{
				if (token->line[i] == '$' && (ft_isalnum(token->line[i + 1]) || token->line[i + 1] == '_'))
				{
					j = 0;
					if (!ft_isalpha(token->line[++i]) && token->line[i] != '_')
						continue;
					while (ft_isalnum(token->line[i + j]) || token->line[i + j] == '_')
						j++;
					env_var = ft_substr(token->line, i, j);






				}
				else if (token->line && token->line[i] == '\"' && closed_quotes(token->line, i))
					f = closed_quotes(token->line, i);
				else if (token->line && token->line[i] == '\'' && closed_quotes(token->line, i) && f == 0)
					i = closed_quotes(token->line, i);
				else if (i == f)
					f = 0;
				else
					i++;
			}
		}

		token = token->nxt;
	}

}
//search the list for the WORD type nodes
//check if the line in the node has env_variables
//if the env_var is within the single quotes , it stays the same
//else if the env_var is within the double quotes , it should be expanded
//if the env_var is after a << , it considered as a delimiter for the heredoc and should not get expanded
//if the env_var is not founded the env_var in the line should get removed from the line
//if the env_var has a number after the $ sign , the $ and the number after it should get removed from the line
//the env_var starts from the dollar sign and ends whenever there is a whitespace or a comma, or quotes or . or - or = or + or * or / ? ...
//if there is only a dollar sign $ , the line should stay the same

//whenever i find a parse an env_var i should dynamically reallocate a new_line that i will replace when i finish with the current line

