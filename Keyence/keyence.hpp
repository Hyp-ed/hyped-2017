#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CTL_SIG 29
#define STR_IN 6

using namespace std;

class keyence
{
	private: 
		int current_state = 0, 
			prev_state = 0,
			set_result = 0;

	public:
		keyence(int &stripes);
		void setUp();
		void countStripes(int &numStripes);			
};