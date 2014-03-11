/*
 * HexFile.h
 *
 * Created: 19/02/2014 4:53:39 PM
 *  Author: lawrencec
 */ 


#ifndef HEXFILE_H_
#define HEXFILE_H_

#define BLOCK_LEN	8	/* in bytes */

/* function prototypes */
void EncryptBin(unsigned char *src, bool doDecrypt, bool firstOp);

void testcase1(void);

#endif /* HEXFILE_H_ */