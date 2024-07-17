int is_token(char c)
{
	if (c == '>' || c == '<' || c == -1 || c == -2)
		return 1;
	else
		return 0;
}
int is_set(char c)
{
    if (c == 32)
        return 1;
    else
        return 0;
}
