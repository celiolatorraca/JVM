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

#include "printclass.h"
#include "classloader.h"
#include "mnemonics.h"
#include "carregador.h"

FILE *fp;

char *base_path2 = "/Users/celio/UnB/workspace/JVM/src/";

void printClassloader(char *class_name, FILE *file)
{
	fp = file;

	loadClass(class_name);

	/* Carrega o opcode info para usar o mnemonicos */
	populate_opcode_info();

	/*Imprime o ClassFile carregado na tela*/
	show_class_file(class_name);

	fflush(fp);

	printf("\n\nEscrita do classloader completa");
	if ( fp != stdout )
		printf("(em arquivo)");
	printf(".\nPressione <enter> para continuar com a execucao do .class\n");
	getchar();

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


/*
 \param class_name String com o nome da class
 \brief Mostra as informacoes gerais
 */
void show_class_file(char* class_name)
{
  char string[200];

  loadClass(class_name);
  class = getClassByIndex(0);

  get_access_flags(class->access_flags, string);

  fprintf( fp, "\n\n\t\t\tClass File - Viewer (%s)\n\n", class_name);

  /*Imprime as Informacoes gerais do ClassFile carregado*/
  fprintf( fp, "\n---------------- General Information -----------------\n");
  fprintf( fp, "\n\tMagic: %X", class->magic);
  fprintf( fp, "\n\tMinor version: %hu", class->minor_version);
  fprintf( fp, "\n\tMajor version: %hu", class->major_version);
  fprintf( fp, "\n\tConstant pool count: %hu", class->constant_pool_count);
  fprintf( fp, "\n\tAccess flags: %s", string);
  fprintf( fp, "\n\tThis class: %hu", class->this_class);
  fprintf( fp, "\n\tSuper class: %hu", class->super_class);
  fprintf( fp, "\n\tInterfaces count: %hu", class->interfaces_count);
  fprintf( fp, "\n\tFields count: %hu", class->fields_count);
  fprintf( fp, "\n\tMethods count: %hu", class->methods_count);
  fprintf( fp, "\n\tAttributes count: %hu", class->attributes_count);

  if (class->constant_pool != NULL) {
	/*Imprime os dados armazenados no Constant Pool*/
	fprintf( fp, "\n\n\n-------------------- Constant Pool --------------------");
	show_constant_pool();

	/*Imprime os dados armazenados das Interfaces*/
	fprintf( fp, "\n\n\n-------------------- Interfaces --------------------");
	show_interfaces();

	/*Imprime os dados armazenados dos Fields*/
	fprintf( fp, "\n\n\n-------------------- Fields --------------------");
	show_fields();

	/*Imprime os dados armazenados dos Methods*/
	fprintf( fp, "\n\n\n-------------------- Methods --------------------");
    show_methods();

	/*Imprime os dados armazenados dos Attributes*/
	fprintf( fp, "\n\n\n-------------------- Attributes --------------------\n");
	show_attributes( class->attributes , class->attributes_count);
  }
}

/*
 \brief Mostra todos os campos do constant pool
 */
void show_constant_pool()
{
  int i;
  u1 cp_tag;

  for (i = 0; i < class->constant_pool_count - 1; i++)
  {
    fprintf( fp, "\n\n\t[%d] ", i+1);
    cp_tag = ((struct cp_info_t*) class->constant_pool[i])->tag;
    switch(cp_tag)
    {
    case CONSTANT_Class:
	  fprintf( fp, "CONSTANT_Class_info");
      fprintf( fp, "\n\t\tClass name index: %hu", ((struct CONSTANT_Class_info*) class->constant_pool[i])->name_index);
      break;
    case CONSTANT_Fieldref:
	  fprintf( fp, "CONSTANT_Fieldref_info");
      fprintf( fp, "\n\t\tClass name index: %hu", ((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->class_index);
      fprintf( fp, "\n\t\tName and type index: %hu", ((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_Methodref:
	  fprintf( fp, "CONSTANT_Methodref_info");
	  fprintf( fp, "\n\t\tClass name index: %hu", ((struct CONSTANT_Methodref_info*) class->constant_pool[i])->class_index);
	  fprintf( fp, "\n\t\tName and type index: %hu", ((struct CONSTANT_Methodref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_InterfaceMethodref:
	  fprintf( fp, "CONSTANT_InterfaceMethodref_info");
	  fprintf( fp, "\n\t\tClass name index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->class_index);
	  fprintf( fp, "\n\t\tName and type index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_String:
	  fprintf( fp, "CONSTANT_String_info");
	  fprintf( fp, "\n\t\tString index index: %hu", ((struct CONSTANT_String_info*) class->constant_pool[i])->string_index);
      break;
    case CONSTANT_Integer:
	  fprintf( fp, "CONSTANT_Integer_info");
	  fprintf( fp, "\n\t\tBytes: %X", ((struct CONSTANT_Integer_info*) class->constant_pool[i])->bytes);
	  fprintf( fp, "\n\t\tInteger: %d", ((struct CONSTANT_Integer_info*) class->constant_pool[i])->bytes);
      break;
    case CONSTANT_Float:
	  fprintf( fp, "CONSTANT_Float_info");
	  fprintf( fp, "\n\t\tBytes: %X", ((struct CONSTANT_Float_info*) class->constant_pool[i])->bytes);
	  fprintf( fp, "\n\t\tFloat: %f", (float)((struct CONSTANT_Float_info*) class->constant_pool[i])->bytes);
      break;
    case CONSTANT_Long:
	  fprintf( fp, "CONSTANT_Long_info");
	  fprintf( fp, "\n\t\tHigh bytes: %X", ((struct CONSTANT_Long_info*) class->constant_pool[i])->high_bytes);
	  fprintf( fp, "\n\t\tLow bytes: %X", ((struct CONSTANT_Long_info*) class->constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Double:
	  fprintf( fp, "CONSTANT_Double_info");
	  fprintf( fp, "\n\t\tHigh bytes: %X", ((struct CONSTANT_Double_info*) class->constant_pool[i])->high_bytes);
	  fprintf( fp, "\n\t\tLow bytes: %X", ((struct CONSTANT_Double_info*) class->constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Utf8:
	  fprintf( fp, "CONSTANT_Utf8_info");
	  fprintf( fp, "\n\t\tLength of byte array: %hu", ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
	  fprintf( fp, "\n\t\tLength of string: %hu", ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
	  fprintf( fp, "\n\t\tString: ");
	  print_name(((struct CONSTANT_Utf8_info*) class->constant_pool[i])->bytes, ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
      break;
    case CONSTANT_NameAndType:
	  fprintf( fp, "CONSTANT_NameAndType_info");
	  fprintf( fp, "\n\t\tName index: %hu", ((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->name_index);
	  fprintf( fp, "\n\t\tDescriptor index: %hu", ((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->descriptor_index);
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

  for (i = 0; i < class->interfaces_count; i++) {
	getName(getClassByName(nome), ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[class->interfaces[i] - 1])->class_index);

	fprintf( fp, "\n\n\t[%d] %s", i+1, nome);
	fprintf( fp, "\n\t\tClass index: %hu", class->interfaces[i]);
  }
}

/*
 \brief Mostra os metodos
 */
void show_methods() {
  int i;
  char string[200], *nome;

  for ( i = 0 ; i < class->methods_count; i++ ) {
    get_access_flags(class->methods[i].access_flags, string);
	nome = getName(class, class->methods[i].name_index);

    fprintf( fp, "\n\n\t[%d] %s", i+1, nome);
	fprintf( fp, "\n\t\tName index: %hu", class->methods[i].name_index );
	fprintf( fp, "\n\t\tDescriptor index: %hu", class->methods[i].descriptor_index );
	fprintf( fp, "\n\t\tAccess flags: %s", string);
	fprintf( fp, "\n\t\tAttributes count: %hu", class->methods[i].attributes_count);

	show_attributes( class->methods[i].attributes , class->methods[i].attributes_count);
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
	fprintf( fp, "\n\t\t\t[%d] ", i+1);
    switch(((attribute_info *) attributes[i])->tag) {
	  case ATTR_ConstantValue:
		fprintf( fp, "ConstantValue");

	    fprintf( fp, "\n\t\t\tAttribute name index: %hu", ((ConstantValue_attribute *) attributes[i])->attribute_name_index);
	    fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((ConstantValue_attribute *) attributes[i])->attribute_length);
	    fprintf( fp, "\n\t\t\t\tConstantValue index: %hu", ((ConstantValue_attribute *) attributes[i])->constantvalue_index);
	    break;

	  case ATTR_Code:
		fprintf( fp, "Code");

	    fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((Code_attribute *) attributes[i])->attribute_name_index);
	    fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((Code_attribute *) attributes[i])->attribute_length);

		/* Misc */
		fprintf( fp, "\n\t\t\t\tMisc:");
	    fprintf( fp, "\n\t\t\t\t\tMaximum stack depth: %hu", ((Code_attribute *) attributes[i])->max_stack);
		fprintf( fp, "\n\t\t\t\t\tMaximum local variable: %hu", ((Code_attribute *) attributes[i])->max_locals);
		fprintf( fp, "\n\t\t\t\t\tCode length: %hu", ((Code_attribute *) attributes[i])->code_length);

		/* Exceptions */
		fprintf( fp, "\n\t\t\t\tException table length: %hu", ((Code_attribute *) attributes[i])->exception_table_length);
		if (((Code_attribute *) attributes[i])->exception_table_length > 0) {
		  fprintf( fp, "\n\t\t\t\tException table:");
		  for (j = 0; j < ((Code_attribute *) attributes[i])->exception_table_length; j++) {
		    fprintf( fp, "\n\t\t\t\t[%d]", j+1);
		    fprintf( fp, "\n\t\t\t\t\tStart pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].start_pc);
		    fprintf( fp, "\n\t\t\t\t\tEnd pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].end_pc);
		    fprintf( fp, "\n\t\t\t\t\tHandler pc: %hu", ((Code_attribute *) attributes[i])->exception_table[j].handler_pc);
		    fprintf( fp, "\n\t\t\t\t\tCatch type: %hu", ((Code_attribute *) attributes[i])->exception_table[j].catch_type);
		  }
		}

		/* Code */
		fprintf( fp, "\n\t\t\t\tBytecode length: %u", ((Code_attribute *) attributes[i])->code_length);
		if (((Code_attribute *) attributes[i])->code_length > 0) {
		  fprintf( fp, "\n\t\t\t\tBytecode:");
		  /* Escreve os mnemonicos do bytecode */
		  print_mnemonics( ((Code_attribute *) attributes[i])->code , ((Code_attribute *) attributes[i])->code_length );
		}

		/* Attributes */
		fprintf( fp, "\n\t\t\t\tAttributes count: %u", ((Code_attribute *) attributes[i])->attributes_count);
		if (((Code_attribute *) attributes[i])->attributes_count > 0) {
		  show_attributes( ((Code_attribute *) attributes[i])->attributes , ((Code_attribute *) attributes[i])->attributes_count );
		}
	    break;

	  case ATTR_Deprecated:
		fprintf( fp, "Deprecated");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((Deprecated_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((Deprecated_attribute *) attributes[i])->attribute_length);
	    break;

	  case ATTR_Exceptions:
		fprintf( fp, "Exception");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((Exceptions_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((Exceptions_attribute *) attributes[i])->attribute_length);

		/* Exceptions */
		fprintf( fp, "\n\t\t\t\tNumber of exceptions: %hu", ((Exceptions_attribute *) attributes[i])->number_of_exceptions);
		if (((Exceptions_attribute *) attributes[i])->number_of_exceptions > 0) {
		  fprintf( fp, "\n\t\t\t\tExceptions:");
		  for (j = 0; j < ((Exceptions_attribute *) attributes[i])->number_of_exceptions; j++) {
		    fprintf( fp, "\n\t\t\t\t\t[%d]", j+1);
		    fprintf( fp, "\n\t\t\t\t\t\tException index table: %hu", ((Exceptions_attribute *) attributes[i])->exception_index_table[j]);
		  }
		}
	    break;

	  case ATTR_InnerClasses:
		fprintf( fp, "InnerClass");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((InnerClasses_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((InnerClasses_attribute *) attributes[i])->attribute_length);

		/* Classes */
		fprintf( fp, "\n\t\t\t\tNumber of classes: %hu", ((InnerClasses_attribute *) attributes[i])->number_of_classes);
		if (((InnerClasses_attribute *) attributes[i])->number_of_classes > 0) {
		  fprintf( fp, "\n\t\t\t\tClasses:");
		  for (j = 0; j < ((InnerClasses_attribute *) attributes[i])->number_of_classes; j++) {
		    /* Pega o nome das Access Flags */
		    get_access_flags(((InnerClasses_attribute *) attributes[i])->classes[j].inner_class_access_flags, string);

		    fprintf( fp, "\n\t\t\t\t\t[%d]", j+1);
		    fprintf( fp, "\n\t\t\t\t\t\tInnerClass info index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].inner_class_info_index);
		    fprintf( fp, "\n\t\t\t\t\t\tOuterClass info index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].outer_class_info_index);
		    fprintf( fp, "\n\t\t\t\t\t\tInnerClass name index: %hu", ((InnerClasses_attribute *) attributes[i])->classes[j].inner_name_index);
		    fprintf( fp, "\n\t\t\t\t\t\tInnerClass access flags: %s", string);
		  }
		}
	    break;

	  case ATTR_LineNumberTable:
		fprintf( fp, "LineNumberTable");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((LineNumberTable_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((LineNumberTable_attribute *) attributes[i])->attribute_length);

		/* Line Numbers */
		fprintf( fp, "\n\t\t\t\tLine number table length: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table_length);
		if (((LineNumberTable_attribute *) attributes[i])->line_number_table_length > 0) {
		  fprintf( fp, "\n\t\t\t\tLine numbers:");
		  for (j = 0; j < ((LineNumberTable_attribute *) attributes[i])->line_number_table_length; j++) {
		    fprintf( fp, "\n\t\t\t\t\t[%d]", j+1);
		    fprintf( fp, "\n\t\t\t\t\t\tStart pc: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table[j].start_pc);
		    fprintf( fp, "\n\t\t\t\t\t\tLine number: %hu", ((LineNumberTable_attribute *) attributes[i])->line_number_table[j].line_number);
		  }
		}
	    break;

	  case ATTR_LocalVariableTable:
		fprintf( fp, "LocalVariableTable");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((LocalVariableTable_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((LocalVariableTable_attribute *) attributes[i])->attribute_length);

		/* Local Variables */
		fprintf( fp, "\n\t\t\t\tLocal variable table length: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length);
		if (((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length > 0) {
		  fprintf( fp, "\n\t\t\t\tLocal variables:");
		  for (j = 0; j < ((LocalVariableTable_attribute *) attributes[i])->local_variable_table_length; j++) {
			fprintf( fp, "\n\t\t\t\t\t[%d]", j+1);
			fprintf( fp, "\n\t\t\t\t\t\tStart pc: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].start_pc);
			fprintf( fp, "\n\t\t\t\t\t\tLength: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].length);
			fprintf( fp, "\n\t\t\t\t\t\tName index: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].name_index);
			fprintf( fp, "\n\t\t\t\t\t\tDescriptor index: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].descriptor_index);
			fprintf( fp, "\n\t\t\t\t\t\tIndex: %hu", ((LocalVariableTable_attribute *) attributes[i])->local_variable_table[j].index);
		  }
		}
	    break;

	  case ATTR_SourceFile:
		fprintf( fp, "SourceFile");

		fprintf( fp, "\n\t\t\t\tAttribute name index: %hu", ((SourceFile_attribute *) attributes[i])->attribute_name_index);
		fprintf( fp, "\n\t\t\t\tAttribute length: %u", ((SourceFile_attribute *) attributes[i])->attribute_length);
		fprintf( fp, "\n\t\t\t\tSourceFile name index: %u", ((SourceFile_attribute *) attributes[i])->sourcefile_index);
	    break;
	}
  }
}

/*
 \brief Mostra os fields de tod o arquivo
 */
void show_fields()
{
  int i;
  char string[200], nome[200];

  for (i = 0; i < class->fields_count; i++) {
	/* Pega o nome das Access Flags */
	get_access_flags(class->fields[i].access_flags, string);
	getName(getClassByName(nome), class->fields[i].name_index);

    fprintf( fp, "\n\n\t[%d] %s", i+1, nome);
	fprintf( fp, "\n\t\tName index: %hu", class->fields[i].name_index );
	fprintf( fp, "\n\t\tDescriptor index: %hu", class->fields[i].descriptor_index );
	fprintf( fp, "\n\t\tAccess flags: %s", string );

	fprintf( fp, "\n\t\tAttributes count: %hu", class->fields[i].attributes_count );
	if (class->fields[i].attributes_count > 0) {
	  fprintf( fp, "\n\t\tAttributes:");
	  show_attributes(class->fields[i].attributes, class->fields[i].attributes_count);
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
	fprintf( fp, "\n\t\t\t\t\t");
	opcode_tmp = op_info[bytecode[i]];
	fprintf( fp, "%d    %s", line, opcode_tmp.desc);
	opcode_tmp.operands_index = calloc(sizeof(u4), opcode_tmp.operands_count);
	for (j = 0; j < opcode_tmp.operands_count; j++) {
	  opcode_tmp.operands_index[j] = bytecode[++i];
	  fprintf( fp, " $%hu", opcode_tmp.operands_index[j]);
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
	fprintf( fp, "%c", string[i]);
  }
}



