/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/08 16:14:58 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_error(char *src, t_envp* my_env)
{
	t_lexer*	lexer;
	t_lexer*	next_lexer;
	t_token*	token;
	t_token*	next_token;

	lexer = init_lexer(src);
	next_lexer = init_lexer(src);
	lexer->my_env = my_env;
	next_lexer->my_env = my_env;
	token = lexer_next_token(lexer);
	if (token->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	next_token = lexer_next_token(next_lexer);
	while(token->type != TOKEN_EOF)
	{
		printf("%d\n\n\n", lexer->i);
		// printf("----------\n");
		// printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		next_token = lexer_next_token(next_lexer);
		// printf("\033[0;32m|---__LEXER__---###\033[0m NEXT %s NEXT \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(next_token));
		if (token->type == TOKEN_PIPE && (next_token->type == TOKEN_PIPE || !next_token->value))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (-1);
		}
		if ((token->type == TOKEN_HERDOC || token->type == TOKEN_IN || token->type == TOKEN_OU || token->type == TOKEN_APPAND || token->type == TOKEN_PIPE) &&
				(!next_token->value))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (-1);
		}
		if ((token->type == TOKEN_HERDOC || token->type == TOKEN_IN || token->type == TOKEN_OU || token->type == TOKEN_APPAND) &&
				(next_token->type == TOKEN_HERDOC || next_token->type == TOKEN_IN || next_token->type == TOKEN_OU ||
					next_token->type == TOKEN_APPAND  || next_token->type == TOKEN_PIPE))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", next_token->value);
			return (-1);
		}
		token = lexer_next_token(lexer);
	}
	// printf("FINISH\n");
	return (0);
}

int	main(int argc, char** argv, char** env)
{
	char*	buf;
	t_envp*	my_env;

	my_env = (t_envp*)malloc(sizeof(t_envp));
	my_env->env = (char**)malloc(sizeof(char*) * (ft_d_strlen(env) + 1));
	fill_env(env, my_env);
	if (argc == 1)
	{
		while(1)
		{
			buf = readline("\033[0;33m minishell > \033[0m");
			add_history(buf);
			// ft_check_error(buf);

			/* functoin  pour check les error comme an while lope in src character par chararcter   (here or in main Function)
			static int	error_befor_parser(char* src);         ((( token tab3aha token wola \n error))) */

			// here_doc whit change delemeter par name of file          {in cas de syntax error bash apre print error opning tout here_doc after this ERROR}

			if (buf)
				tac_compile(buf, my_env);
			free(buf);
		}
	}
	else
		printf("error in argemment\n");
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

SOURCE : lexer_collect_string function __
__|> https://stackoverflow.com/questions/70958263/trying-to-make-a-lexer-in-c-and-the-output-is-not-desirable
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



ls >  | ......		----->		bash: syntax error near unexpected token `|'

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