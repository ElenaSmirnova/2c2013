#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "geom.h"

int main () {
	Line l = Line(1, 0);
	Circle c = Circle(1, 0, 1);
	l.print();
	c.print();
	double * inter = intersection(l,c);
	if (inter == 0) {
		printf("no intersection");
	}else{
		for (int i = 0; i<4; i++) {
			printf("%g ",inter[i]);
			if (i == 2) {
				printf("\n");
			}
		}
	}
	printf("\n");
	return 0;
}