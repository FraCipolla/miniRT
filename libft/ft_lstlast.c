t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp -> next != '\0')
		temp = temp -> next;
	return (temp);
}