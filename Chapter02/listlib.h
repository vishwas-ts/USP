#ifndef _LISTLIB_H_
#define _LISTLIB_H_ 

#include <time.h>


typedef struct data_struct {
	time_t time;
	char * string;
} data_t;


int accessdata(void);
int adddata(data_t data);
int freekey(int key);
int getdata(int key, data_t *datap);

#endif /* _LISTLIB_H_ */
