#include "generate_delay.h"

int main(void)
{
	use_indicator();

	#if defined(MILLISECONDS)
	set_milliseconds(MILLISECONDS_VALUE);
	#endif
	#elif defined(SECONDS)
	set_seconds(SECONDS_VALUE);
	#endif

	disable_timer();
	
	while(true)
	{
		// Do nothing.
	}
}
