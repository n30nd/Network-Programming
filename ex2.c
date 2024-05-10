// #include <stdio.h>

// void split1(double num, int *int_part, double *frac_part){
// 	*int_part = (int)num;
// 	*frac_part = num - *int_part;
// }

// int main(void){
// 	double num, fraction;
// 	int integer;

// 	printf("Please enter a real number: ");
//     scanf("%lf",&num);

//     split1(num, &integer, &fraction);
	
// 	printf("The integer part is %d\n", integer);
// 	printf("The remaining fraction is %f\n", fraction);

// 	return 0;
// }

// Nhap vao 1 so thap phan, in ra phan nguyen, phan thap phan, su dung tham chieu

#include "stdio.h"

void split1(double num, int* int_part, double* frac_part) {
    *int_part = (int)num;
    *frac_part = num - *int_part;
}

int main() {
    double num, fraction;
    int integer;
    printf("Nhap vao so thap phan:\n");
    scanf("%lf",&num);

    split1(num, &integer, &fraction);
    printf("Phan nguyen: %d\n", integer);
    printf("Phan thap phan: %2.1lf\n", fraction);
    return 0;
}