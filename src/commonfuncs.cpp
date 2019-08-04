#include <time.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

static int rand_seed = -1;

void seed_random(int s)
{
	if ( s > 0 ) {
		srand(s);
		rand_seed = s;
	}
}

int random_int(int lo, int hi)
{
	int	range = hi - lo + 1;
	char	*seed_str;

	if ( rand_seed == -1 ) {
		
		seed_random( (unsigned) time(NULL) );
	}
	if ( range <= 0 )
		return 17;		// add to function specs

	return lo + ( rand() % range );
}



