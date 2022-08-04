#include<string.h>
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>

typedef enum { 
	ALLOC_UNKNOWN = 0,
	ALLOC_TYPE_T = 1,
	P_ALLOC_TYPE_T =  2,
	A_CALC_T
} al_type;

typedef struct {
	int a,b;
	char *c,*d, *e, *f;
	char *g,*h;
	uint8_t *l,*p;
	int size;
	char *val_array[]; 
} alloc_t;

typedef struct {
	int a,b;
	char *g,*h;
	uint8_t *l,*p;
	uint8_t *x,*y;
	uint8_t *xx,*yy;
	int size;
	char *val_array[]; 
} p_alloc_t;

typedef struct {
	char *a,*b,*c,*d;
	int target;
} calc_t;
// TODO commentary and walk through issues
//
// FIXME it's allocating half the pointers in the struct
int get_alloc_t(void *a, al_type alloc_type) {
	if(!(alloc_type == ALLOC_TYPE_T || alloc_type == P_ALLOC_TYPE_T || alloc_type == A_CALC_T)) alloc_type = ALLOC_UNKNOWN;
	switch(alloc_type) {
		case ALLOC_TYPE_T:
			alloc_t *allc = (alloc_t*)a;
			char *val_array[] = {"nigger", "cunt", "fuck", "faggot", "lol", "lmao"};
			for(int i=0,j=0;i<allc->size;i++) {
				*((int*)allc + i) = i + 1;
				if(i>(allc->size - 2)/2 && i < allc->size-1)  { 
					char **alc = ((char**)allc+ i);
					*alc = val_array[j];
					j++;
					if(j>allc->size - 2) j=0;
				}
			}
			return 0;
		case P_ALLOC_TYPE_T: 
			p_alloc_t *p_allc = (p_alloc_t*)a;
			char *val_array1[] = {"nigger", "cunt", "fuck", "faggot"};
			for(int i=0,j=0;i<p_allc->size;i++) {
				*((int*)p_allc + i) = i + 1;
				if(i>(p_allc->size - 2)/2 && i < p_allc->size-1)  { 
					char **alc = ((char**)p_allc+ i);
					*alc = val_array1[j];
					j++;
					if(j>p_allc->size - 2) j=0;
				}
			}
			return 0;
		case A_CALC_T:
			calc_t *ct = (calc_t*)a;
			*((int*)ct+8) = 69;
			return 0;

		case ALLOC_UNKNOWN:
			return -1;
	}
	
}

size_t calculate_size_calc_t(al_type atype) {
	switch(atype) {
		case ALLOC_TYPE_T:
			return (((sizeof(alloc_t) - (sizeof(int)*2))/8)) - 1;
		case P_ALLOC_TYPE_T:
			return (((sizeof(p_alloc_t) - (sizeof(int)*2))/8)) - 1;
		default:
			return -1;
	}
}



int main() {
	alloc_t a; //= malloc(32);
	p_alloc_t pa;
	calc_t ct;
	a.size = calculate_size_calc_t(ALLOC_TYPE_T) + 2;
	pa.size = calculate_size_calc_t(P_ALLOC_TYPE_T) + 2;
	int ret1 = get_alloc_t(&a,ALLOC_TYPE_T);
	int ret2 = get_alloc_t(&pa,P_ALLOC_TYPE_T);
	int ret3 = get_alloc_t(&ct,A_CALC_T);
	assert(ret1==0 && ret2==0 && ret3==0);
	printf("%s\n",  a.g);
	printf("%s\n", pa.y);
	printf("%ld\n", pa.size);
	printf("%d\n", ct.target);
	//printf("%s\n", pa.p);
	return 0;
}
