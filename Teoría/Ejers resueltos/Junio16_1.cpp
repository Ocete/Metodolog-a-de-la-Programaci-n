#include <iostream>
using namespace std;

int MezclarUnico (int *v1, int util1, int *v2, int util2, int *salida) {
	int c1 = 0, c2 = 0, util3 = 0;
	while (c1 < util1 && c2 < util2) {
		if (v1[c1] < v2[c2]) {
			salida[util3] = v1[c1];
			c1++;
		} else {
			salida[util3] = v2[c2];
			c2++;
		}
		while (v1[c1] == salida[util3]) 
			c1++;
		while (v2[c2] == salida[util3]) 
			c2++;
		util3++;
	}
	while (c1 < util1) {
		salida[util3] = v1[c1];
		c1++;
		util3++;
	}
	while (c2 < util2) {
		salida[util3] = v2[c2];
		c2++;
		util3++;
	}
	return util3;
}

int main() {
	int util1 = 5, util2 = 4, util3;
	int v1[5] = {1,3,3,4,4}, v2[4] = {2,3,4,5}, v3[5];
	util3 = MezclarUnico(v1, util1, v2, util2, v3);
	
	for (int i=0; i<util3; i++)
		cout << v3[i] << ' ';
}
