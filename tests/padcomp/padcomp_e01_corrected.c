/*	Rule: padcomp	Test File: padcomp_e01.c
 *
 * Copyright (c) 2012 Carnegie Mellon University.
 * All Rights Reserved.
 *  
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions
 * are met:
 *  
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following acknowledgments 
 *    and disclaimers.
 *  
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the 
 *    distribution.
 *  
 * 3. The names “Carnegie Mellon University,” "CERT” and/or “Software
 *    Engineering Institute" shall not be used to endorse or promote 
 *    products derived from this software without prior written 
 *    permission. For written permission, please contact 
 *    permission@sei.cmu.edu.
 *  
 * 4. Products derived from this software may not be called "CERT" 
 *    nor may "CERT" appear in their names without prior written 
 *    permission of permission@sei.cmu.edu.
 *  
 * 5. Redistributions of any form whatsoever must retain the following 
 *    acknowledgment:
 *  
 * "This product includes software developed by CERT with funding and 
 *  support from the Department of Defense under Contract No. FA 
 *  8721-05-C-0003.  The U.S. Government's rights to use, modify,
 *  reproduce, release, perform, display, or disclose this material are
 *  restricted by the Rights in Technical Data-Noncommercial Items
 *  clauses (DFAR 252-227.7013 and DFAR 252-227.7013 Alternate I contained
 *  in the foregoing identified contract.
 *  
 *  THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY “AS IS” AND
 *  CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AS TO ANY MATTER, AND ALL SUCH WARRANTIES,
 *  INCLUDING WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE, ARE EXPRESSLY DISCLAIMED.  WITHOUT LIMITING THE GENERALITY OF
 *  THE FOREGOING, CARNEGIE MELLON UNIVERSITY DOES NOT MAKE ANY WARRANTY
 *  OF ANY KIND RELATING TO EXCLUSIVITY, INFORMATIONAL CONTENT, ERROR-FREE
 *  OPERATION, RESULTS TO BE OBTAINED FROM USE, FREEDOM FROM PATENT,
 *  TRADEMARK AND COPYRIGHT INFRINGEMENT AND/OR FREEDOM FROM THEFT OF TRADE
 *  SECRETS.”
 * 
 *
 * Rule: [padcomp]
 * Description: diagnostic is required because the C Standard Library 
 *              function memcmp() is used to compare the structures b1 
 *              and b2, including any padding data
 * Diagnostic: required on line 108
 * Additional Test Files: None
 * Command-line Options: None
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUF 25

struct S_buffer {
  char buff_type;
  size_t size;
  char buffer[MAX_BUF];
};

typedef struct S_buffer buffer;

int buf_comp(const buffer *, const buffer *);
int buf_init(buffer *, buffer *);

int main(void) {

  buffer a, b; // Not static anymore

  if((buf_init(&a, &b)) == 1) {
    printf("buffers match\n");
  } else {
    printf("buffers do not match\n");
  }
  return EXIT_SUCCESS;
}

int buf_init(buffer *b1, buffer *b2) {
   int i;
   b1->buff_type = 'a';
   b2->buff_type = 'a'; // Same as b1->buff_type

   b1->size = sizeof(buffer);
   b2->size = sizeof(buffer);

   for (i = 0; i < MAX_BUF; i++) {
     b1->buffer[i] = i;
     b2->buffer[i] = i;
   }

   return buf_comp(b1, b2);
}  

int buf_comp(const buffer *s1, const buffer *s2) {

  if (!memcmp(s1, s2, sizeof(buffer))) {  // diagnostic required
    return 1; 
  } else {
    return 0;
  }
}

