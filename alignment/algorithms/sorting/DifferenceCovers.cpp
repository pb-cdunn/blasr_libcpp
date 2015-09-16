#include <cstring>
#include "utils.hpp"
#include "DifferenceCovers.hpp"

int InitializeDifferenceCover(int diffCoverSize, UInt &diffCoverLength, UInt *&diffCover) {
	UInt index;
	for (index = 0; index < N_COVERS; index++) {
		if (diffCovers[index][0] == diffCoverSize) {
			diffCoverLength = diffCovers[index][1];
			diffCover = ProtectedNew<UInt>(diffCoverLength);
			memcpy(diffCover, &diffCovers[index][2], sizeof(UInt)*diffCoverLength);
			return 1;
		}
	}
	return 0;
}
