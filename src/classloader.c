/*!
 \file classloader.c
 \author Celio, Daniel, Lucas, Yuri
 \brief Class Loader da JVM. Carrega os objetos do arquivo .class em memoria.
 Os campos sao mostrados em tela. O nome do arquivo pode ser passado por parametro
 da segiunte forma:
 ./classloader arquivo.class
 ou executando  o programa e informando o nome do arquivo:
 ./classloader
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "classloader.h"
#include "mnemonics.h"
#include <errno.h>

extern int errno;

FILE* classfile;

int read_class_file()
{
  /*!
   * Inicio da leitura
   */
  class.magic = read_u4();
  class.minor_version = read_u2();
  class.major_version = read_u2();
	
  class.constant_pool_count = read_u2();
	
  /* Aloca memoria para o array de Constant Pool */
  constant_pool = calloc(sizeof(void *), class.constant_pool_count);
  read_constant_pool();
	
  class.access_flags = read_u2();
  class.this_class = read_u2();
  class.super_class = read_u2();
  class.interfaces_count = read_u2();
  read_interfaces();
  class.fields_count = read_u2();
  read_fields();
  class.methods_count = read_u2();
  read_methods();
  class.attributes_count = read_u2();
  read_attributes();

  if (errno != 0)
    return -1;

  return 0;
}

/*
 \param class_name String com o nome da class
 \brief Mostra as informacoes gerais
 */
void show_class_file(char* class_name)
{
  char string[200];

  get_access_flags(class.access_flags, string);

  printf("\n\n\t\t\tClass File - Viewer (%s)\n\n", class_name);

  /*Imprime as Informa��es gerais do ClassFile carregado*/
  printf("\n---------------- General Information -----------------\n");
  printf("\n\tMagic: %X", class.magic);
  printf("\n\tMinor version: %hu", class.minor_version);
  printf("\n\tMajor version: %hu", class.major_version);
  printf("\n\tConstant pool count: %hu", class.constant_pool_count);
  printf("\n\tAccess flags: %s", string);
  printf("\n\tThis class: %hu", class.this_class);
  printf("\n\tSuper class: %hu", class.super_class);
  printf("\n\tInterfaces count: %hu", class.interfaces_count);
  printf("\n\tFields count: %hu", class.fields_count);
  printf("\n\tMethods count: %hu", class.methods_count);
  printf("\n\tAttributes count: %hu", class.attributes_count);

  if (constant_pool != NULL) {
	/*Imprime os dados armazenados no Constant Pool*/
	printf("\n\n\n-------------------- Constant Pool --------------------");
	show_constant_pool();
	
	/*Imprime os dados armazenados das Interfaces*/
	printf("\n\n\n-------------------- Interfaces --------------------");
	show_interfaces();
	  
	/*Imprime os dados armazenados dos Fields*/
	printf("\n\n\n-------------------- Fields --------------------");
	show_fields();
	
	/*Imprime os dados armazenados dos Methods*/
	printf("\n\n\n-------------------- Methods --------------------");
    show_methods();
	
	/*Imprime os dados armazenados dos Attributes*/
	printf("\n\n\n-------------------- Attributes --------------------\n");
	show_attributes( class.attributes , class.attributes_count);
  }
}

/*
 \brief Mostra todos os campos do constant pool
 */
void show_constant_pool()
{
  int i;
  u1 cp_tag;

  for (i = 0; i < class.constant_pool_count - 1; i++)
  {
    printf("\n\n\t[%d] ", i+1);
    cp_tag = ((struct cp_info_t*) constant_pool[i])->tag;
    switch(cp_tag)
    {
    case CONSTANT_Class:
	  printf("CONSTANT_Class_info");
      printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Class_info*) constant_pool[i])->name_index);
      break;
    case CONSTANT_Fieldref:
	  printf("CONSTANT_Fieldref_info");
      printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Fieldref_info*) constant_pool[i])->class_index);
      printf("\n\t\tName and type index: %hu", ((struct CONSTANT_Fieldref_info*) constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_Methodref:
	  printf("CONSTANT_Methodref_info");
	  printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Methodref_info*) constant_pool[i])->class_index);
	  printf("\n\t\tName and type index: %hu", ((struct CONSTANT_Methodref_info*) constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_InterfaceMethodref:
	  printf("CONSTANT_InterfaceMethodref_info");
	  printf("\n\t\tClass name index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[i])->class_index);
	  printf("\n\t\tName and type index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_String:
	  printf("CONSTANT_String_info");
	  printf("\n\t\tString index index: %hu", ((struct CONSTANT_String_info*) constant_pool[i])->string_index);
      break;
    case CONSTANT_Integer:
	  printf("CONSTANT_Integer_info");
	  printf("\n\t\tBytes: %X", ((struct CONSTANT_Integer_info*) constant_pool[i])->bytes);
	  printf("\n\t\tInteger: %d", ((struct CONSTANT_Integer_info*) constant_pool[i])->bytes);
      break;
    case CONSTANT_Float:
	  printf("CONSTANT_Float_info");
	  printf("\n\t\tBytes: %X", ((struct CONSTANT_Float_info*) constant_pool[i])->bytes);
	  printf("\n\t\tFloat: %f", (float)((struct CONSTANT_Float_info*) constant_pool[i])->bytes);
      break;
    case CONSTANT_Long:
	  printf("CONSTANT_Long_info");
	  printf("\n\t\tHigh bytes: %X", ((struct CONSTANT_Long_info*) constant_pool[i])->high_bytes);
	  printf("\n\t\tLow bytes: %X", ((struct CONSTANT_Long_info*) constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Double:
	  printf("CONSTANT_Double_info");
	  printf("\n\t\tHigh bytes: %X", ((struct CONSTANT_Double_info*) constant_pool[i])->high_bytes);
	  printf("\n\t\tLow bytes: %X", ((struct CONSTANT_Double_info*) constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Utf8:
	  printf("CONSTANT_Utf8_info");
	  printf("\n\t\tLength of byte array: %hu", ((struct CONSTANT_Utf8_info*) constant_pool[i])->length);
	  printf("\n\t\tLength of string: %hu", ((struct CONSTANT_Utf8_info*) constant_pool[i])->length);
	  printf("\n\t\tString: ");
	  print_name(((struct CONSTANT_Utf8_info*) constant_pool[i])->bytes, ((struct CONSTANT_Utf8_info*) constant_pool[i])->length);
      break;
    case CONSTANT_NameAndType:
	  printf("CONSTANT_NameAndType_info");
	  printf("\n\t\tName index: %hu", ((struct CONSTANT_NameAndType_info*) constant_pool[i])->name_index);
	  printf("\n\t\tDescriptor index: %hu", ((struct CONSTANT_NameAndType_info*) constant_pool[i])->descriptor_index);
      break;    
    default:
	  break;
    }
  }
}

/*
 \brief Mostra as interfaces
 */
void show_interfaces() {
  int i;
  char nome[200];
	
  for (i = 0; i < class.interfaces_count; i++) {
	  copy_name(nome, ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[class.interfaces[i] - 1])->class_index);
	  
	printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tClass index: %hu", class.interfaces[i]);
  }
}

/*
 \brief Mostra os metodos
 */
void show_methods() {
  int i;
  char string[200], nome[200];

  for ( i = 0 ; i < class.methods_count; i++ ) {
    get_access_flags(class.methods[i].access_flags, string);	
	copy_name(nome, class.methods[i].name_index);
	  
    printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tName index: %hu", class.methods[i].name_index ); 
	printf("\n\t\tDescriptor index: %hu", class.methods[i].descriptor_index );
	printf("\n\t\tAccess flags: %s", string);
	printf("\n\t\tAttributes count: %hu", class.methods[i].attributes_count);

	show_attributes( class.methods[i].attributes , class.methods[i].attributes_count);
  }
}


/*
 \brief Mostra os atributos
 \param attributes Lista de parametros
 \param atributes_count Quantidade de parametros
 */
void show_attributes(void ** attributes, u2 attributes_count) {
  int i, j;
  char string[200];
	
  for ( i = 0 ; i < attributes_count; i++ ) {
	printf("\n\t\t\t[%d] ", i+1);
    switch(((attribute_info *) attributes[i])->tag) {
	  case ATTR_ConstantValue:
		printf("ConstantValue");
		
	    printf("\n\t\t\tAttribute name index: %hu", ((ConstantValue_attribute *) attributes[i])->attribute_name_index);
	    printf("\n\t\t\t\tAttribute length: %u", ((ConstantValue_attribute *) attributes[i])->attribute_length);
	    printf("\n\t\t\t\tConstantValue index: %hu", ((ConstantValue_attribute *) attributes[i])->constantvalue_index);
	    break;
	    
	  case ATTR_Code:
		printf("Code");
		
	    printf("\n\t\t\t\tAttribute name index: %hu", ((Code_attribute *) attributes[i])->attribute_name_index);
	    printf("\n\t\t\t\tAttribute length: %u", ((Code_attribute *) attributes[i])->attribute_length);
		
		/* Misc */
		printf("\n\t\t\t\tMisc:");
	    printf("\n\t\t\t\t\tMaximum stack depth: %hu", ((Code_attribute *) attributes[i])->max_stack);
		printf("\n\t\t\t\t\tMaximum local variable: %hu", ((Code_attribute *) attributes[i])->max_locals);
		printf("\n\t\t\t\t\tCode length: %hu", ((Code_attribute *) attributes[i])->code_length);
		
		/* Exceptions */
		printf("\n\t\t\t\tException table length: %hu", ((Code_attribute *) attributes[i])->exception_table_length);
		if (((Code_attribute *) attributes[i])->exception_table_length > 0) {
		  printf("\n\t\t\t\tException table:");
		  for (j = 0; j < ((Code_attribute *) attributes[i])->exception_table_length; j++) {
		    printf("\n\t\t\t\t[%d]", j+1);
		    printf("\n\t\t\t\t\tStart pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].start_pc);
		    printf("\n\t\t\t\t\tEnd pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].end_pc);
		    printf("\n\t\t\t\t\tHandler pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].handler_pc);
		    printf("\n\t\t\t\t\tCatch type: %hu", ((Code_attribute *) attributes[i])->exception_table[j].catch_type);
		  }
		}
			
		/* Code */
		printf("\n\t\t\t\tBytecode length: %u", ((Code_attribute *) attributes[i])->code_length);
		if (((Code_attribute *) attributes[i])->code_length > 0) {
		  printf("\n\t\t\t\tBytecode:");
		  /* Escreve os mnemonicos do bytecode */
		  print_mnemonics( ((Code_attribute *) attributes[i])->code , ((Code_attribute *) attributes[i])->code_length );
		}
			
		/* Attributes */
		printf("\n\t\t\t\tAttributes count: %u", ((Code_attribute *) attributes[i])->attributes_count);
		if (((Code_attribute *) attributes[i])->attributes_count > 0) {
		  show_attributes( ((Code_attribute *) attributes[i])->attributes , ((Code_attribute *) attributes[i])->attributes_count );
		}
	    break;
	    
	  case ATTR_Deprecated:
		printf("Deprecated");
		
		printf("\n\t\t\t\tAttribute name index: %hu", ((Deprecated_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((Deprecated_attribute *) attributes[i])->attribute_length);
	    break;
	    
	  case ATTR_Exceptions:
		printf("Exception");
		
		printf("\n\t\t\t\tAttribute name index: %hu", ((Exceptions_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((Exceptions_attribute *) attributes[i])->attribute_length);
		
		/* Exceptions */
		printf("\n\t\t\t\tNumber of exceptions: %hu", ((Exceptions_attribute *) attributes[i])->number_of_exceptions);
		if (((Exceptions_attribute *) attributes[i])->number_of_exceptions > 0) {
		  printf("\n\t\t\t\tExceptions:");
		  for (j = 0; j < ((Exceptions_attribute *) attributes[i])->number_of_exceptions; j++) {
		    printf("\n\t\t\t\t\t[%d]", j+1);
		    printf("\n\t\t\t\t\t\tException index table: %hu", ((Exceptions_attribute *) attributes[i])->exception_index_table[j]);
		  }
		}
	    break;
	    
	  case ATTR_InnerClasses:
		printf("InnerClass");
		
		printf("\n\t\t\t\tAttribute name index: %hu", ((InnerClasses_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((InnerClasses_attribute *) attributes[i])->attribute_length);
		
		/* Classes */
		printf("\n\t\t\t\tNumber of classes: %hu", ((InnerClasses_attribute *) attributes[i])->number_of_classes);
		if (((InnerClasses_attribute *) attributes[i])->number_of_classes > 0) {
		  printf("\n\t\t\t\tClasses:");
		  for (j = 0; j < ((InnerClasses_attribute *) attributes[i])->number_of_classes; j++) {
		    /* Pega o nome das Access Flags */
		    get_access_flags(((InnerClasses_attribute *) attributes[i])->classes[j].inner_class_access_flags, string);
			
		    printf("\n\t\t\t\t\t[%d]", j+1);
		    printf("\n\t\t\t\t\t\tInnerClass info index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].inner_class_info_index);
		    printf("\n\t\t\t\t\t\tOuterClass info index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].outer_class_info_index);
		    printf("\n\t\t\t\t\t\tInnerClass name index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].inner_name_index);
		    printf("\n\t\t\t\t\t\tInnerClass access flags: %s", string);
		  }
		}
	    break;
	    
	  case ATTR_LineNumberTable:
		printf("LineNumberTable");
			
		printf("\n\t\t\t\tAttribute name index: %hu", ((LineNumberTable_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((LineNumberTable_attribute *) attributes[i])->attribute_length);
		
		/* Line Numbers */
		printf("\n\t\t\t\tLine number table length: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table_length);
		if (((LineNumberTable_attribute *) attributes[i])->line_number_table_length > 0) {
		  printf("\n\t\t\t\tLine numbers:");
		  for (j = 0; j < ((LineNumberTable_attribute *) attributes[i])->line_number_table_length; j++) {
		    printf("\n\t\t\t\t\t[%d]", j+1);
		    printf("\n\t\t\t\t\t\tStart pc: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table[j].start_pc);
		    printf("\n\t\t\t\t\t\tLine number: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table[j].line_number);
		  }
		}
	    break;
	    
	  case ATTR_LocalVariableTable:
		printf("LocalVariableTable");
			
		printf("\n\t\t\t\tAttribute name index: %hu", ((LocalVariableTable_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((LocalVariableTable_attribute *) attributes[i])->attribute_length);
			
		/* Local Variables */
		printf("\n\t\t\t\tLocal variable table length: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length);
		if (((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length > 0) {
		  printf("\n\t\t\t\tLocal variables:");
		  for (j = 0; j < ((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length; j++) {
			printf("\n\t\t\t\t\t[%d]", j+1);
			printf("\n\t\t\t\t\t\tStart pc: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].start_pc);
			printf("\n\t\t\t\t\t\tLength: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].length);
			printf("\n\t\t\t\t\t\tName index: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].name_index);
			printf("\n\t\t\t\t\t\tDescriptor index: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].descriptor_index);
			printf("\n\t\t\t\t\t\tIndex: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].index);
		  }
		}
	    break;
	    
	  case ATTR_SourceFile:
		printf("SourceFile");
		
		printf("\n\t\t\t\tAttribute name index: %hu", ((SourceFile_attribute *) attributes[i])->attribute_name_index);
		printf("\n\t\t\t\tAttribute length: %u", ((SourceFile_attribute *) attributes[i])->attribute_length);
		printf("\n\t\t\t\tSourceFile name index: %u", ((SourceFile_attribute *) attributes[i])->sourcefile_index);
	    break;
	}
  }
}

/*
 \brief Mostra os fields de todo arquivo
 */
void show_fields()
{
  int i;
  char string[200], nome[200];
	
  for (i = 0; i < class.fields_count; i++) {
	/* Pega o nome das Access Flags */
	get_access_flags(class.fields[i].access_flags, string);
	copy_name(nome, class.fields[i].name_index);

    printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tName index: %hu", class.fields[i].name_index );
	printf("\n\t\tDescriptor index: %hu", class.fields[i].descriptor_index );
	printf("\n\t\tAccess flags: %s", string );
	
	printf("\n\t\tAttributes count: %hu", class.fields[i].attributes_count );
	if (class.fields[i].attributes_count > 0) {
	  printf("\n\t\tAttributes:");
	  show_attributes(class.fields[i].attributes, class.fields[i].attributes_count);
    }
  }
}

/*
 \brief Traduz o bytecode para mnemonicos
 \param bytecode Array de bytes com o codigo
 \param size Tamanho em bytes do codigo
 */
void print_mnemonics(u1 *bytecode, u2 size)
{
  int i, j, line;

  struct OPCODE_info opcode_tmp;
	
  for (i = 0, line = 1; i < size; i++, line++) {
	printf("\n\t\t\t\t\t");
	opcode_tmp = op_info[bytecode[i]];
	printf("%d    %s", line, opcode_tmp.desc);
	opcode_tmp.operands_index = calloc(sizeof(u4), opcode_tmp.operands_count);
	for (j = 0; j < opcode_tmp.operands_count; j++) {
	  opcode_tmp.operands_index[j] = bytecode[++i];
	  printf(" $%hu", opcode_tmp.operands_index[j]);
	}
  }
}

/*
 \brief Escreve determinado numero de bytes de uma string
 \param string String a ser impressa
 \param length Quantidade de bytes  a serem impressos
 */
void print_name(u1 *string, u2 length)
{
  int i;
	
  for (i = 0; i < length; i++) 
  {
	printf("%c", string[i]);
  }
}

/*
 \brief Escreve em dest o nome enderecado pelo index
 \param dest String de destino
 \param name_index indice no constant pool
 */
void copy_name(char *dest, u2 name_index) {
  int i;

  for (i = 0; i < ((struct CONSTANT_Utf8_info*) constant_pool[name_index - 1])->length; i++) {
    dest[i] = (char) ((struct CONSTANT_Utf8_info*) constant_pool[name_index - 1])->bytes[i];
  }
  dest[i] = '\0';
}


/*
 \brief Abre um arquivo binario para leitura
 \param file_name Nome do arquivo
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int open_file(char *file_name)
{
  if ((classfile = fopen(file_name, "rb")) == NULL)
  {
    perror("openfile");
    return -1;
  }
  return 0;
}

void close_file()
{
	fclose(classfile);
}

/*
 \brief Le 1 byte do arquivo
 \return Byte lido
 */
u1 read_u1()
{
  u1 buffer;
  if (fread(&buffer, sizeof (u1), 1, classfile) < 0)
  {
    perror("readU1");
    return -1;
  }
  return buffer;
}

/*
 \brief Le 2 bytes do arquivo trocando ordem dos bytes
 \return Bytes lidos
 */
u2 read_u2()
{
  u2 buffer;
  u2 aux;
  if (fread(&buffer, sizeof (u1), 2, classfile) < 0)
  {
    perror("readU2");
    return -1;
  }
  aux = buffer & 0xFF;
  buffer >>= 8;
  buffer |= aux<<8;
  return buffer;
}

/*
 \brief Le 4 bytes do arquivo trocando ordem dos bytes
 \return Bytes lidos
 */
u4 read_u4()
{
  u4 buffer;
  u4 aux = 0;

  if (fread(&buffer, sizeof (u4), 1, classfile) < 0)
  {
    perror("readU4");
    return -1;
  }	
    
  aux |= (buffer & 0xFF000000) >> 24;
  aux |= (buffer & 0x00FF0000) >> 8;
  aux |= (buffer & 0x0000FF00) << 8;
  aux |= (buffer & 0x000000FF) << 24;

  return aux;
}

/*
 \brief Le a constant pool
 */
void read_constant_pool()
{
  int i, j;
  u1 cp_tag;

  for (i = 0; i < class.constant_pool_count - 1; i++)
  {
    cp_tag = read_u1();
    switch(cp_tag)
    {
    case CONSTANT_Class:
      constant_pool[i] = (struct CONSTANT_Class_info*) calloc(sizeof (struct CONSTANT_Class_info), 1);
      ((struct CONSTANT_Class_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Class_info*) constant_pool[i])->name_index = read_u2();
      break;
    case CONSTANT_Fieldref:
      constant_pool[i] = (struct CONSTANT_Fieldref_info*) calloc(sizeof (struct CONSTANT_Fieldref_info), 1);
      ((struct CONSTANT_Fieldref_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Fieldref_info*) constant_pool[i])->class_index = read_u2();
      ((struct CONSTANT_Fieldref_info*) constant_pool[i])->name_and_type_index = read_u2();
      break;
    case CONSTANT_Methodref:
      constant_pool[i] = (struct CONSTANT_Methodref_info*) calloc(sizeof (struct CONSTANT_Methodref_info), 1);
      ((struct CONSTANT_Methodref_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Methodref_info*) constant_pool[i])->class_index = read_u2();
      ((struct CONSTANT_Methodref_info*) constant_pool[i])->name_and_type_index = read_u2();
      break;
    case CONSTANT_InterfaceMethodref:
      constant_pool[i] = (struct CONSTANT_InterfaceMethodref_info*) calloc(sizeof (struct CONSTANT_InterfaceMethodref_info), 1);
      ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[i])->class_index = read_u2();
      ((struct CONSTANT_InterfaceMethodref_info*) constant_pool[i])->name_and_type_index = read_u2();
      break;
    case CONSTANT_String:
      constant_pool[i] = (struct CONSTANT_String_info*) calloc(sizeof (struct CONSTANT_String_info), 1);
      ((struct CONSTANT_String_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_String_info*) constant_pool[i])->string_index = read_u2();
      break;
    case CONSTANT_Integer:
      constant_pool[i] = (struct CONSTANT_Integer_info*) calloc(sizeof (struct CONSTANT_Integer_info), 1);
      ((struct CONSTANT_Integer_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Integer_info*) constant_pool[i])->bytes = read_u4();
      break;
    case CONSTANT_Float:
      constant_pool[i] = (struct CONSTANT_Float_info*) calloc(sizeof (struct CONSTANT_Float_info), 1);
      ((struct CONSTANT_Float_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Float_info*) constant_pool[i])->bytes = read_u4();
      break;
    case CONSTANT_Long:
      constant_pool[i] = (struct CONSTANT_Long_info*) calloc(sizeof (struct CONSTANT_Long_info), 1);
      ((struct CONSTANT_Long_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Long_info*) constant_pool[i])->high_bytes = read_u4();
      ((struct CONSTANT_Long_info*) constant_pool[i])->low_bytes = read_u4();
	  i++;
      break;
    case CONSTANT_Double:
      constant_pool[i] = (struct CONSTANT_Double_info*) calloc(sizeof (struct CONSTANT_Double_info), 1);
      ((struct CONSTANT_Double_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_Double_info*) constant_pool[i])->high_bytes = read_u4();
      ((struct CONSTANT_Double_info*) constant_pool[i])->low_bytes = read_u4();
	  i++;
      break;
    case CONSTANT_Utf8:
      constant_pool[i] = (struct CONSTANT_Utf8_info*) calloc(1, sizeof (struct CONSTANT_Utf8_info));
      ((struct CONSTANT_Utf8_info*) (constant_pool[i]))->tag = cp_tag;
      ((struct CONSTANT_Utf8_info*) (constant_pool[i]))->length = read_u2();
      ((struct CONSTANT_Utf8_info*) (constant_pool[i]))->bytes = calloc( ((struct CONSTANT_Utf8_info*) constant_pool[i])->length , sizeof (u1) );
      for (j = 0; j < ((struct CONSTANT_Utf8_info*) constant_pool[i])->length; j++)
        ((struct CONSTANT_Utf8_info*) constant_pool[i])->bytes[j] = read_u1();
      break;
    case CONSTANT_NameAndType:
      constant_pool[i] = (struct CONSTANT_NameAndType_info*) calloc(sizeof (struct CONSTANT_NameAndType_info), 1);
      ((struct CONSTANT_NameAndType_info*) constant_pool[i])->tag = cp_tag;
      ((struct CONSTANT_NameAndType_info*) constant_pool[i])->name_index = read_u2();
      ((struct CONSTANT_NameAndType_info*) constant_pool[i])->descriptor_index = read_u2();
      break;
    default:
	  break;
    }
  }
}

/*
 \brief Le as interfaces para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_interfaces()
{
  int i;

  if ((class.interfaces = (u2*)calloc(sizeof (u2), class.interfaces_count)) == NULL) 
  {
    perror("Interface");
    return -1;
  }
  
  for (i = 0; i < class.interfaces_count; i++)
  {
	class.interfaces[i] = read_u2();
  }
  return 0;
}


/*
 \brief Le os fields para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_fields()
{
  int i, j;

  if ((class.fields = calloc(sizeof (field_info), class.fields_count)) == NULL)
  {
    perror("Fields");
    return -1;
  }
  
  for (i = 0; i < class.fields_count; i++)
  {
	class.fields[i].access_flags = read_u2();
	class.fields[i].name_index = read_u2();
	class.fields[i].descriptor_index = read_u2();
	class.fields[i].attributes_count = read_u2();

    if ((class.fields[i].attributes = calloc(sizeof (void *), class.fields[i].attributes_count)) == NULL)
    {
      perror("Attributes");
      return -1;
    }
    
    for (j = 0; j < class.fields[i].attributes_count; j++){
      class.fields[i].attributes[j] = read_attribute_info();
    }
    
  }
  
  return 0;
}


/*
 \brief Le um atribute_info e retorna o ponteiro para tal
 \return Ponteiro para um atributo
 */
void * read_attribute_info()
{
  int i;
  char nome[200];
  
  void *attribute;
	
  u2 name_index;
  u4 length;
  
  name_index = read_u2();
  length = read_u4();
  
  copy_name(nome, name_index);
  
  if (strcmp("ConstantValue", nome) == 0) {
    attribute = (ConstantValue_attribute *) calloc(sizeof (ConstantValue_attribute), 1);
    ((ConstantValue_attribute *) attribute)->attribute_name_index = name_index;
    ((ConstantValue_attribute *) attribute)->attribute_length = length;
    ((ConstantValue_attribute *) attribute)->tag = ATTR_ConstantValue;
    ((ConstantValue_attribute *) attribute)->constantvalue_index = read_u2();
  }
  
  else if (strcmp("Code", nome) == 0) {
    attribute = (Code_attribute *) calloc(sizeof (Code_attribute), 1);
    ((Code_attribute *) attribute)->attribute_name_index = name_index;
    ((Code_attribute *) attribute)->attribute_length = length;
    ((Code_attribute *) attribute)->tag = ATTR_Code;
    ((Code_attribute *) attribute)->max_stack = read_u2();
    ((Code_attribute *) attribute)->max_locals = read_u2();
    
    ((Code_attribute *) attribute)->code_length = read_u4();
    ((Code_attribute *) attribute)->code = (u1 *) calloc(sizeof (u1), ((Code_attribute *) attribute)->code_length);
    for (i = 0; i < ((Code_attribute *) attribute)->code_length; i++) {
	  ((Code_attribute *) attribute)->code[i] = read_u1();
	}
    
    ((Code_attribute *) attribute)->exception_table_length = read_u2();
    ((Code_attribute *) attribute)->exception_table = (exception_tab *) calloc(sizeof (exception_tab), 
              ((Code_attribute *) attribute)->exception_table_length);
    for (i = 0; i < ((Code_attribute *) attribute)->exception_table_length; i++) {
      ((Code_attribute *) attribute)->exception_table[i].start_pc = read_u2();
	  ((Code_attribute *) attribute)->exception_table[i].end_pc = read_u2();
      ((Code_attribute *) attribute)->exception_table[i].handler_pc = read_u2();
	  ((Code_attribute *) attribute)->exception_table[i].catch_type = read_u2();
	}
	
	((Code_attribute *) attribute)->attributes_count = read_u2();
	((Code_attribute *) attribute)->attributes = (void *) calloc(sizeof (void *), 
			((Code_attribute *) attribute)->attributes_count);
    for (i = 0; i < ((Code_attribute *) attribute)->attributes_count; i++) {
	  ((Code_attribute *) attribute)->attributes[i] = read_attribute_info();
	}
  }
    
  else if (strcmp("Deprecated", nome) == 0) {
	attribute = (Deprecated_attribute *) calloc(sizeof (Deprecated_attribute), 1);
    ((Deprecated_attribute *) attribute)->attribute_name_index = name_index;
    ((Deprecated_attribute *) attribute)->attribute_length = length;
    ((Deprecated_attribute *) attribute)->tag = ATTR_Deprecated;
  }
  
  else if (strcmp("Exceptions", nome) == 0) {
	attribute = (Exceptions_attribute *) calloc(sizeof (Exceptions_attribute), 1);
    ((Exceptions_attribute *) attribute)->attribute_name_index = name_index;
    ((Exceptions_attribute *) attribute)->attribute_length = length;
    ((Exceptions_attribute *) attribute)->tag = ATTR_Exceptions;
    
    ((Exceptions_attribute *) attribute)->number_of_exceptions = read_u2();
    ((Exceptions_attribute *) attribute)->exception_index_table = (u2 *) calloc(sizeof (u2), 
			((Exceptions_attribute *) attribute)->number_of_exceptions);
    for (i = 0; i < ((Exceptions_attribute *) attribute)->number_of_exceptions; i++) {
	  ((Exceptions_attribute *) attribute)->exception_index_table[i] = read_u2();
	} 
  }
  
  else if (strcmp("InnerClasses", nome) == 0) {
	attribute = (InnerClasses_attribute *) calloc(sizeof (InnerClasses_attribute), 1);
    ((InnerClasses_attribute *) attribute)->attribute_name_index = name_index;
    ((InnerClasses_attribute *) attribute)->attribute_length = length;
    ((InnerClasses_attribute *) attribute)->tag = ATTR_InnerClasses;
    
    ((InnerClasses_attribute *) attribute)->number_of_classes = read_u2();
    ((InnerClasses_attribute *) attribute)->classes = (class_tab *) calloc(sizeof (class_tab), 
			((InnerClasses_attribute *) attribute)->number_of_classes);
	for (i = 0; i < ((InnerClasses_attribute *) attribute)->number_of_classes; i++) {
	  ((InnerClasses_attribute *) attribute)->classes[i].inner_class_info_index = read_u2();
	  ((InnerClasses_attribute *) attribute)->classes[i].outer_class_info_index = read_u2();
	  ((InnerClasses_attribute *) attribute)->classes[i].inner_name_index = read_u2();
	  ((InnerClasses_attribute *) attribute)->classes[i].inner_class_access_flags = read_u2();
	}
  }
  
  else if (strcmp("LineNumberTable", nome) == 0) {
	attribute = (LineNumberTable_attribute *) calloc(sizeof (LineNumberTable_attribute), 1);
    ((LineNumberTable_attribute *) attribute)->attribute_name_index = name_index;
    ((LineNumberTable_attribute *) attribute)->attribute_length = length;
    ((LineNumberTable_attribute *) attribute)->tag = ATTR_LineNumberTable;
    
    ((LineNumberTable_attribute *) attribute)->line_number_table_length = read_u2();
    ((LineNumberTable_attribute *) attribute)->line_number_table = (line_number_tab *) calloc(sizeof (line_number_tab), 
			((LineNumberTable_attribute *) attribute)->line_number_table_length);
	for (i = 0; i < ((LineNumberTable_attribute *) attribute)->line_number_table_length; i++) {
	  ((LineNumberTable_attribute *) attribute)->line_number_table[i].start_pc = read_u2();
	  ((LineNumberTable_attribute *) attribute)->line_number_table[i].line_number = read_u2();
	}
  }
  
  else if (strcmp("LocalVariableTable", nome) == 0) {
	attribute = (LocalVariableTable_attribute *) calloc(sizeof (LocalVariableTable_attribute), 1);
    ((LocalVariableTable_attribute *) attribute)->attribute_name_index = name_index;
    ((LocalVariableTable_attribute *) attribute)->attribute_length = length;
    ((LocalVariableTable_attribute *) attribute)->tag = ATTR_LocalVariableTable;
    
    ((LocalVariableTable_attribute *) attribute)->local_variable_table_length = read_u2();
    ((LocalVariableTable_attribute *) attribute)->local_variable_table = (local_variable_tab *) calloc(sizeof (local_variable_tab),
			((LocalVariableTable_attribute *) attribute)->local_variable_table_length);
	for (i = 0; i < ((LocalVariableTable_attribute *) attribute)->local_variable_table_length; i++) {
	  ((LocalVariableTable_attribute *) attribute)->local_variable_table[i].start_pc = read_u2();
	  ((LocalVariableTable_attribute *) attribute)->local_variable_table[i].length = read_u2();
	  ((LocalVariableTable_attribute *) attribute)->local_variable_table[i].name_index = read_u2();
	  ((LocalVariableTable_attribute *) attribute)->local_variable_table[i].descriptor_index = read_u2();
	  ((LocalVariableTable_attribute *) attribute)->local_variable_table[i].index = read_u2();
	}
  }
  
  else if (strcmp("SourceFile", nome) == 0) {
	attribute = (SourceFile_attribute *) calloc(sizeof (SourceFile_attribute), 1);
    ((SourceFile_attribute *) attribute)->attribute_name_index = name_index;
    ((SourceFile_attribute *) attribute)->attribute_length = length;
    ((SourceFile_attribute *) attribute)->tag = ATTR_SourceFile;
    ((SourceFile_attribute *) attribute)->sourcefile_index = read_u2();
  }
  
  else {
  }

  return attribute;
}

/*
 \brief Le metodos para memoria
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */
int read_methods() {

  int i, j;
  
  if ((class.methods = (method_info*) calloc(sizeof (method_info), class.methods_count)) == NULL)
  {
    perror("Methods");
    return -1;
  }

  for (i = 0; i < class.methods_count; i++)
  {
    class.methods[i].access_flags = read_u2();
    class.methods[i].name_index = read_u2();
    class.methods[i].descriptor_index = read_u2();
    class.methods[i].attributes_count = read_u2();
    
    if ((class.methods[i].attributes = calloc(sizeof (void *), class.methods[i].attributes_count)) == NULL)
    {
      perror("Methods");
      return -1;
    }  
    
    for (j = 0; j < class.methods[i].attributes_count; j++)
	{
      class.methods[i].attributes[j] = read_attribute_info();
    }
  }
  
  return 0;
}

/*
 \brief Le atributos da class file
 \return 0 Nao houve erro na funcao
 \return -1 Ocorreu erro
 */

int read_attributes()
{
  int i;

  if ((class.attributes = calloc(sizeof (void *), class.attributes_count)) == NULL)
  {
    perror("Attributes");
    return -1;
  }  

  for (i = 0; i < class.attributes_count; i++){
    class.attributes[i] = read_attribute_info();
  }

  return 0;
}

/*
 \brief Retorna a string com os mnemonicos das flags
 \param flags Valor hexa das flags
 \param string String de destino
 */
void get_access_flags(u2 flags, char* string)
{
  string[0] = '\0';
  flags & ACC_PUBLIC ? strcat(string, "ACC_PUBLIC "):0;
  flags & ACC_PRIVATE ? strcat(string, "ACC_PRIVATE "):0;
  flags & ACC_PROTECTED ? strcat(string, "ACC_PROTECTED "):0;
  flags & ACC_STATIC ? strcat(string, "ACC_STATIC "):0;
  flags & ACC_FINAL ? strcat(string, "ACC_FINAL "):0;
  flags & ACC_SUPER ? strcat(string, "ACC_SUPER "):0;
  flags & ACC_VOLATILE ? strcat(string, "ACC_VOLATILE "):0;
  flags & ACC_TRANSIENT ? strcat(string, "ACC_TRANSIENT "):0;
  flags & ACC_NATIVE ? strcat(string, "ACC_NATIVE "):0;
  flags & ACC_INTERFACE ? strcat(string, "ACC_INTERFACE "):0;
  flags & ACC_ABSTRACT ? strcat(string, "ACC_ABSTRACT "):0;
  flags & ACC_STRICT ? strcat(string, "ACC_STRICT "):0;
}
