int test(int x)
{
	if (x == 0) {
		return 1;
	}
	x = test(x - 1) + 1;
	return x;
}