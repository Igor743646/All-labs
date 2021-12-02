#include <stdio.h>

int main() {
	int m[255];
	int i=0;

	while (m[i]!=EOF) {
  	
  		scanf("%d", &m[i]);
  		printf("%d ", m[i]);
  		i++;
	}
	
	return 0;
}