#ifndef CLOAD_H
#define CLOAD_H

/*!
 * Access flags
 */
#define ACC_PUBLIC    0x0001
#define ACC_PRIVATE   0x0002  
#define ACC_PROTECTED 0x0004  
#define ACC_STATIC    0x0008  
#define ACC_FINAL     0x0010
#define ACC_SUPER     0x0020
#define ACC_VOLATILE  0x0040  
#define ACC_TRANSIENT 0x0080  
#define ACC_NATIVE    0x0100  
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT  0x0400
#define ACC_STRICT    0x0800  

/*!
 * Constant's flags
 */
#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1


/*!
 * Attributes flags
 */
#define ATTR_ConstantValue			0
#define ATTR_Code					1
#define ATTR_Deprecated				2
#define ATTR_Exceptions				3
#define ATTR_InnerClasses			4
#define ATTR_LineNumberTable		5
#define ATTR_LocalVariableTable		6
#define ATTR_SourceFile				7


typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

/**
 * CONSTANT_Class
 * name_index (class full name) ex. Ljava/lang/Thread;
 */
typedef struct cp_info_t
{
  u1 tag;
  u1 *info;
} cp_info;

/**
 * if wont recognized: silence
 */
typedef struct attribute_info_t
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u1 *info;     
} attribute_info;



typedef struct field_info_t
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  void **attributes; 
} field_info;

typedef struct method_info_t
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  void **attributes;
} method_info;


struct ClassFile
{
  u4      		magic;/*! Signature*/
  u2 			minor_version;
  u2 			major_version;
  u2 			constant_pool_count; /*! if [n]'s long or double, [n+1]'s invalid*/
  cp_info 		*constant_pool; 
  u2 			access_flags;
  u2 			this_class;
  u2 			super_class;
  u2 			interfaces_count;
  u2 			*interfaces; 
  u2 			fields_count;
  field_info 	*fields;
  u2 			methods_count;
  method_info   *methods; 
  u2 			attributes_count;
  void 			**attributes; 
};

struct CONSTANT_Class_info
{
  u1 tag;
  u2 name_index;
};


struct CONSTANT_Fieldref_info
{
	u1 tag;  				/* valor 9 */
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_NameAndType_info
{
	u1 tag;  				/* valor 12*/
	u2 name_index;
	u2 descriptor_index;
};

/**
 * Utf8
 * 1byte -> 0[bits6-0]
 * 2bytes-> x: 110[bits10-6] y:10[bits5-0]
 * calc c = ((x & 0x1f) << 6) + (y & 0x3f)
 * 3bytes-> x: 1110[bits15-12] y: 10[bits11-6] z: 10[bits5-0]
 * calc: c = ((x & 0xf) << 12) + ((y & 0x3f) << 6) + (z & 0x3f)
 */
struct CONSTANT_Utf8_info
{
  u1 tag;  				/* valor 1*/
  u2 length;
  u1 *bytes; 
};

struct CONSTANT_Methodref_info
{
	u1 tag;  				/* valor 10*/
	u2 class_index;
	u2 name_and_type_index; /*if starts with <, should be <init>*/
};

struct CONSTANT_InterfaceMethodref_info
{
	u1 tag;  				/* valor 11*/
	u2 class_index;
	u2 name_and_type_index;
};

struct CONSTANT_String_info
{
  u1 tag;				/* valor 8*/
  u2 string_index;
};

struct CONSTANT_Integer_info
{
  u1 tag;					/* valor 3*/
  u4 bytes;
};

/**
 * Float
 * int s = ((bits >> 31) == 0) ? 1 : -1;
 * int e = ((bits >> 23) & 0xff);
 * int m = (e == 0) ?
 * (bits & 0x7fffff) << 1 :
 * (bits & 0x7fffff) | 0x800000;
 * s . m . 2 ^ (e - 150)
 * 0x7f800000 -> +inf
 * 0xff800000 -> -inf
 * 0x7f800001 < float < 0x7fffffff || 0xff800001 < float < 0xffffffff -> NaN
 */
struct CONSTANT_Float_info
{
	u1 tag;					/* valor 4*/
	u4 bytes;
};

/**
 * Long
 * ((long) high_bytes << 32) + low_bytes
 */
struct CONSTANT_Long_info
{
	u1 tag;					/* valor 5*/
	u4 high_bytes;			/* unsigned*/
	u4 low_bytes;			/* unsigned*/
};

/**
 * Double
 * defined as long
 * 0x7ff0000000000000L -> +inf
 * 0xfff0000000000000L -> -inf
 * 0x7ff0000000000001L < double < 0x7ffffffffffffL ||
 * 0xfff0000000000001L < double < 0xffffffffffffffffL -> NaN
 * int s = ((bits >> 63) == 0) ? 1 : -1;
 * int e = ((bits >> 52) & 0x7ffL);
 * long m = (e == 0) ?
 *           (bits & 0xfffffffffffffL) << 1 :
 *           (bits & 0xfffffffffffffL) | 0x10000000000000L;
 * s . m . 2 ^ (e - 1075)
 */
struct CONSTANT_Double_info
{
	u1 tag;					/* valor 6*/
	u4 high_bytes;				/* unsigned*/
	u4 low_bytes;				/* unsigned*/
};





typedef struct ConstantValue_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 constantvalue_index;
} ConstantValue_attribute;

/**
 * exception table
 */
typedef struct Exc_tab
{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} exception_tab;
/**
 * Code atribute
 */
typedef struct Code_attribute
{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 tag;
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 *code; 
  u2 exception_table_length;
  exception_tab *exception_table;
  u2 attributes_count;
  void **attributes; 
} Code_attribute;

typedef struct Deprecated_attribute
{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 tag;
} Deprecated_attribute;

typedef struct Exceptions_attribute
{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 tag;
  u2 number_of_exceptions;
  u2 *exception_index_table; 
} Exceptions_attribute;

typedef struct Class_t
{
  u2 inner_class_info_index;
  u2 outer_class_info_index;
  u2 inner_name_index;
  u2 inner_class_access_flags;
} class_tab;

typedef struct InnerClasses_attribute
{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 tag;
  u2 number_of_classes;
  class_tab *classes; 
} InnerClasses_attribute;

typedef struct LineNum
{
  u2 start_pc;
  u2 line_number;
} line_number_tab;

typedef struct LineNumberTable_attribute
{
  u2 attribute_name_index;
  u4 attribute_length;
  u2 tag;
  u2 line_number_table_length;
  line_number_tab *line_number_table; 
} LineNumberTable_attribute;

typedef struct local_variable
{
  u2 start_pc;
  u2 length;
  u2 name_index;
  u2 descriptor_index;
  u2 index;
} local_variable_tab;

typedef struct LocalVariableTable_attribute 
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 local_variable_table_length;
	local_variable_tab *local_variable_table; 
} LocalVariableTable_attribute;

typedef struct SourceFile_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 tag;
	u2 sourcefile_index;
} SourceFile_attribute;



/**
 * FUNCOES
 */

FILE *classfile;
void** constant_pool; 
struct ClassFile class;

int open_file(char* file_name);
void close_file();
u1 read_u1();
u2 read_u2();
u4 read_u4();
void read_constant_pool();
void show_constant_pool();
void show_interfaces();
void show_methods();
void show_fields();
void print_name(u1 *string, u2 length);
void print_mnemonics(u1 *bytecode, u2 size);
void copy_name(char *dest, u2 name_index);
int read_s();
void get_access_flags(u2 flags, char* string);
void show_class_file(char* class_name);
void show_attributes(void ** attributes, u2 attributes_count);
int read_interfaces();
int read_fields();
void * read_attribute_info();
int read_methods();
int read_attributes();
int read_class_file();

#endif
