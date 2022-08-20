/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/20 04:06:26 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/lexer.h"
#include "../includes/tac.h"

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
		buf = readline("\033[0;33m minishell >\033[0m");
		tac_compile(buf);
		free(buf);
	}

	return 0;
}
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
and output in last one ma3a incha2 jami3 lmilafat */