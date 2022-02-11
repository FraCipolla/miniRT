void	calculate_idle_an(idle_animation)
{
	static int	counter;

	counter++;
	if (counter == idle_animation->frames)
		idle_animation->current_img = idle_animation->img_0;
	else if (counter >= idle_animation->frames * 2)
	{
		idle_animation->current_img = idle_animation->img_1;
		counter = 0;
	}
}