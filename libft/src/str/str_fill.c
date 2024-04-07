int	str_fill(char *str, int len, char c)
{
	if (len <= 0)
		return (0);
	while (len > 0)
	{
		str[len - 1] = c;
		len--;
	}
	return (0);
}
