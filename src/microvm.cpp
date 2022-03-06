#include <stdlib.h>
#include "vm.h"
#include "state.h"

int main() {
	state_file sf = readstate();
	if(sf.err_no > 0) {
		exit(sf.err_no);
	}
	int mvm = microvm(sf.state_ptr,sf.state_length);
	if(mvm > 0) {
		exit(2 + mvm);
	}
	return 0;
}