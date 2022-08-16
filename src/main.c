#include "game/VoxelGame.h"
#include <stdio.h>

int main(){
	int error = run();
	if (error){
		printf("Program crashed with error code: %d\n", error);
		return 1;
	}
	return 0;
}