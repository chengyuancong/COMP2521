int search(int k, int a[], int N)
{
	int i;
	for (i = 0; i < N; i++)
		if (a[i] == k) return i;
	return -1;
}

// OR

int search(int k, int a[], int N)
{
	int i, where;
	where = -1;
	for (i = 0; i < N; i++)
		if (a[i] == k) where = i;
	return where;
}

// OR

int search(int k, int a[], int N)
{
	int i;
	for (i = 0; i < N; i++)
		if (a[i] == k) break;
	return (i == N) ? -1 : i
	/**
	if (i == N)
		return -1;
	else
		return i;
	**/
}

// OR

int search(int k, int a[], int N)
{
	int i, found;
	i = 0;
	found = 0;
	while (i < N && !found) {
		if (a[i] == k)
			found = 1;
		else
			i++;
	}
	if (found)
		return i;
	else
		return -1;
}

// OR

...
