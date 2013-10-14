/*
** program name: status.h
** author:       luo feng
** date:         2013/9/12
*/

#ifndef _STATUS_H
#define _STATUS_H

typedef enum status {
    SUCCESS,	//operation success
    FAIL_FULL,	//operation fail because stack is full
    FAIL_EMPTY	//operation fail because stack is empty
} status;

#endif
