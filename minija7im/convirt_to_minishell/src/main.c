/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 04:44:09 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/lexer.h"
#include "../includes/tac.h"

#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char** argv, char** envp)
{
	char*	buf;

	if (argc > 1)
	{
		printf("error in argemment\n");
		return (0);
	}
	while(1)
	{
		buf = readline("\033[0;33m minishell > \033[0m");
		/* functoin  pour check les error comme an while lope in src character par chararcter   (here or in main Function)
		static int	error_befor_parser(char* src); */
		tac_compile(buf);
		free(buf);
	}
	return 0;
}

/* ---____---- BLAN ZWIN ghnspliti lin bi | est apres lexer cola comand bo7dha -----______------ */


// < file ls -la | wc -l > file1

/* FLAGS - : 7ata (-) rah dakhla fi les flag wo chi 7alat matatkonch,
idan madam ghn7tajha ya3ni ghtkhad com agremant dyal command 7ata hiya 
wo ay 7aja tab3a l command faraha bi basatta argement dyalha */

/* ENVIRONMENT VARIABLES $ : machi fjmi3 l7alat ndyalo kaykon teken mo3abira
bssigha okhra mara 3ando ma3na mara b7alo b7al ay caracter 3adi 
idan ghanakhdo fi PART LEXRE  kastring howa wola howa wo li m3ah 
est appre  en PARESER ghanhandli lblan  fl7alat envirenment variables valid 
wo 7ata tari9a bach daz khasha tkon valide 
examples :
---> "$HOME.fsdgs" OR "$HOME-fsdgs"
---> $USER.sgsrg  OR $USER-sgsrg    {{# $ MNI MKTKONCH LAS9A M3AH DIRICTEMENT CHI 7AJA KYT3TABAR CHARACTER 3ADI #}}
---> '$HOME' OR $ kudfhsk -|-|-|-> hna ma3labalich bi $
!!!!---> $ in heredoc la yotarjam maba3dah 

!!!!! "'$HOME'" expandade
!!!!! '"$HOME"' not_expandade

##### UNSERT ET EXPORT ###### add envp in one double **array and use realooc pour adding or delting envirimenet variables 
*/


/* !!!!!!!!! KYN TA3AROD TADAROB MABIN ENV && SQ EST DQ ila makhditch sq wo dq wo wo khdit $ kastring 
fach nbghi nparssi maghanb9ach n3raf wach kan mabibn "$" OR '$ */ // khasha chi 7al  ???????????????


/* SQ ' && DQ " : i7timal kbir ghan analysihem fi Lexer,
7int fihome bzaf dyal les cas wo ila khalithom 7ata Pareser 
ghatkharba9 liya data li m3ahom
example ----> e"c"'h'o  "l"s
*/


/* REDERICTION : kola command hado < > dyawlha khassin biha, 
fi 7alat multibale <if<if<if<if< OR >ot>ot>ot>ot>ot input from last one 
and output in last one ma3a incha2 jami3 lmilafat 
!!!!!!! CAS_OF_MULTIBLE_REDIRICTION !!!!!!!!!
INPUT : check if tout les file exist if one not exist return error (check par open);
if not error reard from last one.
OUTPUT : creat tout les files and assing output in last one (>> com > + apandad).
##### ISTINTAJ ######
ya3ni ghnhandli kolchi 3andi wo ndawoz lih ghi akhir files describtor.
*/

/* HEREDOC << : '< linked_list.c cat << l' ____----> open heredoc, aftre heredoc  cat first file est apres cat heredoc
'<< STOP | cat ' open heredoc !!!!!!!!  in bash this | is vid !!!!!!!!!!!!
TOUT les caracter est un delemetre soft << < > >> | " '  !!!!!!!!! ila kan SQ PR DQ (< > >> << | rahom walaw des caracter)
alore ghnhandli lherdoc fi lexer ila kant de erorr se non ghn9ado flparsing wola ydoz le execution 
!!!!!!!    << l << k << S cat    open ga3 li herdoc and close it est read from last one,
(bikol basasata akhir faile ghaydoz l cat ka 2anaho argement)
*/


/* PIPE :::::::: exemple :::::::::
< file |         in this cas bash open attend pour complete input,
alore pour handl sa on a realloc mon buf,
and use readline pour read from standar_input est apre join this on buf */

/* les ERROR :::::: before_parsing :::::::
::::::::::::    

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!! if open " OR ' qoute handle in ERROR, ya3ni maghanakhodhomch b3ayn l3tibar fach n9ad l7alat dyal " and ' qoute  !!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

('||' '|')------------> syntax error near unexpected token `|'
(\n if not |)---------> syntax error near unexpected token `newline'
(open " OR ' qout)----> syntax error open quote
(... < < ... OR ... << << ... OR ... > > > ... OR ... >> >> ...)-------> syntax error near unexpected token `token->value'
::::::::::::
*/








/*Environment variable VS Shell variable =----> shell variable fi lgnalib mamtlobinch,
wo mahoma ila des variable mdiclarin fi terminal mfto7a <----= */






/*
function ------> prancibale ERROR
function ------> semple command (larobama ghn7taj lexe cmd par cmd)
function ------> (lope par semple vommand)--->multble command
function ------> hndal rediriction 
function ------> here_doc
*/ 