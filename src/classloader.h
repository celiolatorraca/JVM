#ifndef CLOAD_H
#define CLOAD_H

#include "types.h"
#include "constants.h"


/*
 * FUNCOES
 */
struct ClassFile *class;


int open_file(char* file_name);
void close_file();
u1 read_u1();
u2 read_u2();
u4 read_u4();
void read_constant_pool();
void copy_name(char *dest, u2 name_index);
int read_s();
int read_interfaces();
int read_fields();
void *read_attribute_info();
int read_methods();
int read_attributes();
struct ClassFile * read_class_file(char *nome_arq);
void free_class_file(struct ClassFile* class_file);


#endif
