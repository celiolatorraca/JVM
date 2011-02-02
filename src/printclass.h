#ifndef PRINTCLASS_H
#define PRINTCLASS_H

#include "types.h"

void printClassloader(char *class_name, FILE *file);
void get_access_flags(u2 flags, char *string);
void show_class_file(char *class_name);
void show_attributes(void **attributes, u2 attributes_count);
void show_constant_pool();
void show_interfaces();
void show_methods();
void show_fields();
void print_name(u1 *string, u2 length);
void print_mnemonics(u1 *bytecode, u2 size);


#endif /* PRINTCLASS_H */
