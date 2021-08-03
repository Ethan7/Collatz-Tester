/* By Ethan Hughes */
/* Written on 7/31/2021 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<gmp.h>

int main(int argc, char **argv){
	int byteLen = 1024;
	int oneShot = 0;
	if(argc > 2){
		byteLen = atoi(argv[1]);
		oneShot = atoi(argv[2]);
	} else if(argc > 1){
		byteLen = atoi(argv[1]);
	}

	mpz_t initialNum;
	mpz_t currentNum;
	mpz_t testNum;
	int counter;
	int largestCount = 0;
	mp_bitcnt_t bitcounter;

	mpz_init(initialNum);
	mpz_init(currentNum);
	mpz_init(testNum);

	gmp_randstate_t randstate;
	gmp_randinit_default(randstate);
	gmp_randseed_ui(randstate, time(NULL));

	//Test for infinite loops starting at 2^69 up to 2^byteLen
	for(int i = 69; i < byteLen; i++){
		if(oneShot){
			i = byteLen-1;
		}
		bitcounter = i;
		counter = 0;
		mpz_urandomb(initialNum, randstate, bitcounter);
		//initialNum = rand();
		mpz_set(currentNum, initialNum);
		//currentNum = initialNum;

		while(mpz_cmp_ui(currentNum, 4) != 0){
		//currentNum != 4?
			/*if(oneShot){
				mpz_out_str(stdout,10,currentNum);
				printf(": %d\n", counter);
			}*/
			counter++;
			if(counter != 0 && counter % 1000 == 0){
				printf("num passing %d\n", counter);
			}
			mpz_mod_ui(testNum, currentNum, 2);
			//testNum = currentNum % 2;
			if(mpz_cmp_ui(testNum, 0) == 0){
			//testNum == 0?
				mpz_cdiv_q_ui(currentNum, currentNum, 2);
				//currentNum = currentNum/2;
			} else {
				mpz_mul_ui(currentNum, currentNum, 3);
				mpz_add_ui(currentNum, currentNum, 1);
				//currentNum = currentNum*3+1;
			}
		}
		mpz_out_str(stdout,10,initialNum);
		printf(": %d\n", counter);

		if(counter > largestCount){
			largestCount = counter;
		}
	}
	printf("Largest Counter: %d\n", largestCount);

	return 0;
}