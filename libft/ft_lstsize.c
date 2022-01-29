int	ft_lstsize(t_list *lst)
{
	int i;
	t_list *temp;

	i = 0;
	temp = lst;
	while (temp -> next != NULL)
	{
		i++;
		temp = temp -> next;
	}
	if (temp -> next == null)
		i++;
	return (i);
}