#!/bin/bash

###############################################################################
## ISCTE-IUL: Trabalho prático de Sistemas Operativos - Parte 1
##
## Este módulo destina-se a realizar operações de I/O utilitárias.
## Não deverá ser alterado nem submetido com o trabalho.
##
## Nome do Módulo: debug.sh
## Descrição/Explicação do Módulo:
##    Mensagens de DEBUG para os scripts
##    SYNTAX: debug <alínea> [<opcional 1>] [<opcional 2>] ... [<opcional n>]
##    Basicamente, o módulo escreve "@DEBUG ", e depois mostra todos os
##    argumentos que sejam passados, separados por "[]"
##    Dica: Quando afetarem variáveis, façam e.g., "var1=3 && debug var1 $var1"
##          para verem logo o valor das variáveis.
##    Dica: Para deixar de ver as mensagens de @DEBUG sem precisar mexer em todas
##          as linhas onde está a ser invocada, basta definir SO_HIDE_DEBUG=1
##
## @param $1..n: Informações de debug que o aluno queira mostrar. Estas
##               informações são mostradas separadas com [] para que se possa
##               perceber se há caracteres não desejados
###############################################################################

. /home/so/utils/bin/so_utils.sh
so_debug "$@"