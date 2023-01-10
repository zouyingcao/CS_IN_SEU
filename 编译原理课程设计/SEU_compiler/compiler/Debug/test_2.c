int main()
{
	double p = 1.2354;
	float a = 10.55;
	int b = 0;
	_Bool flag = true;
	while (a <= b || !(p != 0) && flag)
	{
		flag = a > b;
		p *= a;
		a -= 1;
	}
	if (p >= 10 || false)
		p = 10;
	else
		p = 100;
	return 0;
}