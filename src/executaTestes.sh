#
# Autor: Marcelo Valenca de Almeida - 02/2010.
#
# Descricao: O presente arquivo captura todos os arquivos ".java" existentes na
#            raiz e executa na JVM.
#            Ao final sao gerados dois relatorio:
#                1) ARQUIVO_RESULTADO: Contem o resultado da execucao de cada um
#                                      dos arquivos ".class" (OK ou Falhou).
#		           2) ARQUIVO_LOG:       Contem a impressao referente a execucao
#                                      de cada um dos arquivos ".class".
# 
# Comentario adicional: Ainda ha muito o que melhorar, por isso sinta-se livre
#                       para modificar este arquivo conforme a sua necessidade.
#                       Apenas nao se esqueca de compartilhar as melhorias.
#

#!/bin/bash

ARQUIVO_RESULTADO="resultado.txt"
ARQUIVO_LOG="log.txt"
QUANT_ERROS=0
QUANT_SUCESSOS=0

if [ `find -name ourOut | wc -l` -eq "1" ]; then
        rm ourOut
fi

if [ `find -name theirOut | wc -l` -eq "1" ]; then
        rm theirOut
fi


if [ `find -name $ARQUIVO_RESULTADO | wc -l` -eq "1" ]; then
	rm $ARQUIVO_RESULTADO
fi

if [ `find -name $ARQUIVO_LOG | wc -l` -eq "1" ]; then
	rm $ARQUIVO_LOG
fi

if [ `ls *.class | wc -l` -gt "0" ]; then

	clear

	echo
	echo "Gravando resultado do teste nos arquivos:"
	echo
	echo "    [ $ARQUIVO_RESULTADO ]"
	echo "    [ $ARQUIVO_LOG ]"
	echo

	for PROGRAMA in `ls *.class`; do

		echo " Executando [ $PROGRAMA ]"

		echo ""																									>> $ARQUIVO_LOG
		echo "----------------------------------------------------------------------" 	>> $ARQUIVO_LOG
		echo "Executando [ $PROGRAMA ]"		 															>> $ARQUIVO_LOG
		echo ""																									>> $ARQUIVO_LOG

		# Altere essa linha para refletir a forma como a sua JVM e executada.
		./jvm $PROGRAMA 																					>> ourOut
		java `echo "$PROGRAMA" | cut -d'.' -f1`																>> theirOut 
		
		RESULTADO_EXECUCAO="$?"

		sleep 1

		if [ "$RESULTADO_EXECUCAO" == "0" ]; then
			LINHA="$PROGRAMA : OK"
			QUANT_SUCESSOS=$[$QUANT_SUCESSOS+1];
		else
			LINHA="$PROGRAMA : Falhou"
			QUANT_ERROS=$[$QUANT_ERROS+1];
		fi
		echo $LINHA																								>> $ARQUIVO_RESULTADO

		echo ""																									>> $ARQUIVO_LOG
		echo "----------------------------------------------------------------------" 	>> $ARQUIVO_LOG
		echo ""																									>> $ARQUIVO_LOG

	done

	echo
	echo "Resultado gravado!"
	echo

	echo																											>> $ARQUIVO_RESULTADO
	echo																											>> $ARQUIVO_RESULTADO
	echo "===========================================================================" 	>> $ARQUIVO_RESULTADO
	echo "  RESUMO:"																							>> $ARQUIVO_RESULTADO
	echo																											>> $ARQUIVO_RESULTADO
	echo "  Arquivos \".class\" existentes:  [ $(($QUANT_ERROS + $QUANT_SUCESSOS)) ]."	>> $ARQUIVO_RESULTADO
	echo "  Arquivos \".class\" com erros:   [ $QUANT_ERROS ]."									>> $ARQUIVO_RESULTADO
	echo "  Arquivos \".class\" com sucesso: [ $QUANT_SUCESSOS ]."								>> $ARQUIVO_RESULTADO
	echo																											>> $ARQUIVO_RESULTADO
	echo "===========================================================================" 	>> $ARQUIVO_RESULTADO
	echo																											>> $ARQUIVO_RESULTADO

else

	echo
	echo "ERRO: Não existem arquivos \".class\" em `pwd`"
	echo

fi


