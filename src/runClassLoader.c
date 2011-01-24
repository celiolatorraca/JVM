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


#include "classloader.h"
#include "mnemonics.h"
#include "carregador.h"


void get_access_flags(u2 flags, char* string);
void show_class_file(char* class_name);
void show_attributes(void ** attributes, u2 attributes_count);
void show_constant_pool();
void show_interfaces();
void show_methods();
void show_fields();
void print_name(u1 *string, u2 length);
void print_mnemonics(u1 *bytecode, u2 size);


int main(int argc, char *argv[])
{
	char nome_arq[200];

	if (argc == 1)
	{
		printf("\nDigite o nome do arquivo: ");
		scanf("%s", nome_arq);
		getchar();
	}
	else if (argc == 2)
	{
		strcpy(nome_arq, argv[1]);
	}
	else
	{
		printf("Usage: ./classloader class_file\n");
		return EXIT_FAILURE;
	}


	read_class_file(nome_arq);

	/* Carrega o opcode info para usar o mnemonicos */
	populate_opcode_info();

	/*Imprime o ClassFile carregado na tela*/
	printf("\n\n");
	show_class_file(nome_arq);
	printf("\n\n");

	fflush(stdout);

	printf("\nPressione qualquer tecla para sair.\n");
	getchar();

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

  printf("\n\n\t\t\tClass File - Viewer (%s)\n\n", class_name);

  /*Imprime as Informacoes gerais do ClassFile carregado*/
  printf("\n---------------- General Information -----------------\n");
  printf("\n\tMagic: %X", class->magic);
  printf("\n\tMinor version: %hu", class->minor_version);
  printf("\n\tMajor version: %hu", class->major_version);
  printf("\n\tConstant pool count: %hu", class->constant_pool_count);
  printf("\n\tAccess flags: %s", string);
  printf("\n\tThis class: %hu", class->this_class);
  printf("\n\tSuper class: %hu", class->super_class);
  printf("\n\tInterfaces count: %hu", class->interfaces_count);
  printf("\n\tFields count: %hu", class->fields_count);
  printf("\n\tMethods count: %hu", class->methods_count);
  printf("\n\tAttributes count: %hu", class->attributes_count);

  if (class->constant_pool != NULL) {
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
    printf("\n\n\t[%d] ", i+1);
    cp_tag = ((struct cp_info_t*) class->constant_pool[i])->tag;
    switch(cp_tag)
    {
    case CONSTANT_Class:
	  printf("CONSTANT_Class_info");
      printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Class_info*) class->constant_pool[i])->name_index);
      break;
    case CONSTANT_Fieldref:
	  printf("CONSTANT_Fieldref_info");
      printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->class_index);
      printf("\n\t\tName and type index: %hu", ((struct CONSTANT_Fieldref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_Methodref:
	  printf("CONSTANT_Methodref_info");
	  printf("\n\t\tClass name index: %hu", ((struct CONSTANT_Methodref_info*) class->constant_pool[i])->class_index);
	  printf("\n\t\tName and type index: %hu", ((struct CONSTANT_Methodref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_InterfaceMethodref:
	  printf("CONSTANT_InterfaceMethodref_info");
	  printf("\n\t\tClass name index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->class_index);
	  printf("\n\t\tName and type index: %hu", ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[i])->name_and_type_index);
      break;
    case CONSTANT_String:
	  printf("CONSTANT_String_info");
	  printf("\n\t\tString index index: %hu", ((struct CONSTANT_String_info*) class->constant_pool[i])->string_index);
      break;
    case CONSTANT_Integer:
	  printf("CONSTANT_Integer_info");
	  printf("\n\t\tBytes: %X", ((struct CONSTANT_Integer_info*) class->constant_pool[i])->bytes);
	  printf("\n\t\tInteger: %d", ((struct CONSTANT_Integer_info*) class->constant_pool[i])->bytes);
      break;
    case CONSTANT_Float:
	  printf("CONSTANT_Float_info");
	  printf("\n\t\tBytes: %X", ((struct CONSTANT_Float_info*) class->constant_pool[i])->bytes);
	  printf("\n\t\tFloat: %f", (float)((struct CONSTANT_Float_info*) class->constant_pool[i])->bytes);
      break;
    case CONSTANT_Long:
	  printf("CONSTANT_Long_info");
	  printf("\n\t\tHigh bytes: %X", ((struct CONSTANT_Long_info*) class->constant_pool[i])->high_bytes);
	  printf("\n\t\tLow bytes: %X", ((struct CONSTANT_Long_info*) class->constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Double:
	  printf("CONSTANT_Double_info");
	  printf("\n\t\tHigh bytes: %X", ((struct CONSTANT_Double_info*) class->constant_pool[i])->high_bytes);
	  printf("\n\t\tLow bytes: %X", ((struct CONSTANT_Double_info*) class->constant_pool[i])->low_bytes);
	  i++;
      break;
    case CONSTANT_Utf8:
	  printf("CONSTANT_Utf8_info");
	  printf("\n\t\tLength of byte array: %hu", ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
	  printf("\n\t\tLength of string: %hu", ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
	  printf("\n\t\tString: ");
	  print_name(((struct CONSTANT_Utf8_info*) class->constant_pool[i])->bytes, ((struct CONSTANT_Utf8_info*) class->constant_pool[i])->length);
      break;
    case CONSTANT_NameAndType:
	  printf("CONSTANT_NameAndType_info");
	  printf("\n\t\tName index: %hu", ((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->name_index);
	  printf("\n\t\tDescriptor index: %hu", ((struct CONSTANT_NameAndType_info*) class->constant_pool[i])->descriptor_index);
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
	  copy_name(nome, ((struct CONSTANT_InterfaceMethodref_info*) class->constant_pool[class->interfaces[i] - 1])->class_index);

	printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tClass index: %hu", class->interfaces[i]);
  }
}

/*
 \brief Mostra os metodos
 */
void show_methods() {
  int i;
  char string[200], nome[200];

  for ( i = 0 ; i < class->methods_count; i++ ) {
    get_access_flags(class->methods[i].access_flags, string);
	copy_name(nome, class->methods[i].name_index);

    printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tName index: %hu", class->methods[i].name_index );
	printf("\n\t\tDescriptor index: %hu", class->methods[i].descriptor_index );
	printf("\n\t\tAccess flags: %s", string);
	printf("\n\t\tAttributes count: %hu", class->methods[i].attributes_count);

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
 \brief Mostra os fields de tod o arquivo
 */
void show_fields()
{
  int i;
  char string[200], nome[200];

  for (i = 0; i < class->fields_count; i++) {
	/* Pega o nome das Access Flags */
	get_access_flags(class->fields[i].access_flags, string);
	copy_name(nome, class->fields[i].name_index);

    printf("\n\n\t[%d] %s", i+1, nome);
	printf("\n\t\tName index: %hu", class->fields[i].name_index );
	printf("\n\t\tDescriptor index: %hu", class->fields[i].descriptor_index );
	printf("\n\t\tAccess flags: %s", string );

	printf("\n\t\tAttributes count: %hu", class->fields[i].attributes_count );
	if (class->fields[i].attributes_count > 0) {
	  printf("\n\t\tAttributes:");
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



