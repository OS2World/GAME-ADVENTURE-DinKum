#define PARSE
#include "dink_sym.h"
#include "dink_glb.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 
#if (PROTOTYPE)
void parse(void)
#else
void parse()
#endif
/*********************************************************/
/*                                                       */
/*      --- English Language Parsing Subroutine ---      */
/*                                                       */
/*  This subroutine parses a sentence of up to nineteen  */
/*  words and decodes the words into integers and passes */
/*  a twenty element vector back to the calling          */
/*  program.  The digit 0, implies an unused word.  The  */
/*  digit -1 (V_LINE_END), indicates end of sentence.    */
/*                                                       */
/*      Program by Gary A. Allen, Jr. 24 January 1993    */
/*        (c) Copyright 1993 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
#if (PROTOTYPE)
char getche(void) ;
int synonym(int) ;
void purge(int, int*) ;
#else
char getche() ;
int synonym() ;
#endif

register int i, j ;

int m, n, jacc, i_ws, sw_purge, j_purge, sw_loop, sw_decode ;

/* a sentence can have 19 words of 15 letters */ 
char words[20][15], word[15] ;
char letter, buffer[300], *pnt ;

ADJECTIVE_STRUCT *adj ;

/* flush the "sent vector" */
for (i = 0; i <= 19; i++) sent[i] = 0 ;

/* flush the tag vector */
for (i = 0; i <= Vocab_cnt; i++) tag[i] = FALSE ;

/* Outer infinite "for" loop to parse and load in the words */
for(;;) {

/* print prompt */
/* This modification was suggested by Chris Herborth. */
#ifdef PROMPT
printf("> ") ;
#endif

/* Keyboard input "for" loop */
for (i = 0; i <= 299; i++) {
	if (Recorder->Status == S_playing) {
		if (feof(fp)) {
			Recorder->Status = S_inactive ;
			continue ;
		}
		letter = fgetc(fp) ;
		putchar(letter) ;
	}
	else {
#ifndef __TURBOC__
		letter = getchar() ;	
#endif
#ifdef __TURBOC__
		letter = getche() ;	
#endif
		if (Recorder->Status == S_recording) {
			if ((letter == '\n') || (letter == 13)) {
				fprintf(fp,"\n") ;
			}
			else fputc(letter, fp) ;
		}
	}

	buffer[i] = letter ;

	/* First pass "switch" block */
	switch(letter) {

	/* Carriage return */
	case '\n':
	case 13:
		break ;

	/* Backspace */
	case 8:
		i -= 2 ;
		if (i < 0) {
			i = -1 ;
#ifdef __TURBOC__
			putchar(0x07) ; /* ring bell */
/* "{" --- this is to balance the parenthesis below for Vi */
		}
		putchar(' ') ;
		putchar(0x08) ;
#endif
#ifndef __TURBOC__
		}
#endif
		continue ;

	default:
		continue ;
	} /* end of the first pass "switch" block */
	break ;
} /* end of keyboard input "for" loop */

/* Deal with goofy long strings */
if (i > 299) {
	printf("\n\nHuh? That last sentence was a long one!\n") ;
	printf("Try making it a bit shorter.\n\n") ;
	continue ;
}

sw_loop = FALSE ;
sw_decode = FALSE ;
pnt = buffer ;

/* Outer word counting "for" loop */
for (i = 0; i <= 18; i++) {
	/* Inner letter counting "for" loop */
	for (j = 0; j <= 14; j++) {
		/* Letter type "switch" block */
		switch (letter = *(pnt++)) {
			case '\n':
			case 13 :
				sw_loop = TRUE ;
				if ((i == 0) && (j == 0)) break ;
				words[i][j] = '\0' ;  
				sw_decode = TRUE ; 
				break ;

			/* White spaces and punctuation for cutting out words */
			case '\"':
			case ' ':
			case ',':
			case '.':
			case ';':
			case ':':
			case '?':
			case '!':
			case '&':
			case '{':
			case '}':
			case '[':
			case ']':
			case ')':
			case '(':
			case '\'':
			case '`':
			case '\t':
				words[i][j] = '\0' ;  
				break;

			default:
				words[i][j] = letter ;
				continue ;
		} /* end of letter type "switch" block */
		break ;
	} /* end of inner letter counting "for" loop */
	if (sw_loop) break ;
	if (j > 14) {
printf("\nYou're saying nonsense! Type the sentence again. \n");
		break ;
	}
	if (j == 0) i-- ;
} /* end of outer word counting "for" loop */

/* Bad sentence handling block */
if (!sw_decode) {
	if (sw_loop) continue ;

	if (i > 18) 
printf ("\nYour sentence is too long. Type something shorter! \n") ;

#ifndef __TURBOC__
	/* Purge the input buffer */
	for (;;) if ('\n' == getchar()) break ;
#endif

	continue ; /* resume the infinite "for" loop */
} /* end of bad sentence handling block */

#ifdef __TURBOC__
printf("\n") ;
#endif

/* Decode the words from the known vocabulary */
m = i ;
jacc = 0;
for (i = 0; i <= m; i++) {
	for (j = 0; j <= 14; j++) {
		word[j] = words[i][j] ; 
	}
	for (j = 0; j < Vocab_cnt; j++) {
		n = strcmp(word,vocab[j]);
		if (n == 0) {
			if ((j > 9)&&(j < 20)) j -= 10;
			sent[jacc++] = j + 1 ;
			break; 
		}
	}
	/* Deal with a number */
	if ((word[0] >= 48)&&(word[0] <= 57)) {
		tag[V_NUMBER] = TRUE ;
		for (j = 0; j <= 14; j++) {
			if ((word[j] < 48)||(word[j] > 57)) {
				if (word[j] != '\0') tag[V_NUMBER] = FALSE ;
				break ;
			}
		}
		if (tag[V_NUMBER]) number_word = atoi(word) ;
	}
} /* end of vobaulary decode block */

if (jacc == 0) {
	printf ("Huh? Nothing you said was understandable! Try again. \n");
	continue ;
}
 
/* mark last word */
sent[jacc] = V_LINE_END ;
 
/* Check to see if this is a simple move command */
if (sent[0] <= 10) {
	tag[V_MOVE] = TRUE ;
	tag[V_DIRECTION] = TRUE ;
	verb = sent[0] ;
	return ; 
} /* end of the simple move block */
 
/* adjective and "in/out" preposition "for" loop */
sw_purge = FALSE ;
for (j = 0; j <= jacc-1; j++) {

	/* check for adjectives */
	adj = adjective ;
	for (i = 0; i < Adj_max; i++) {
		if (sent[j] == adj->Adjective) {

		/* Does a noun have to be ignored ? */
		if ((adj->Command == F_ignore)
			&& (adj->Modified_noun != sent[j+1])) break ;

		/* Does a noun have to be replaced? */
		if ((adj->Command == F_replace)
			&& (adj->Modified_noun == sent[j+1])) {
				sent[j+1] = adj->Generated_noun ;
		}
		sw_purge = TRUE ;
		j_purge = j ;
		}
		adj++ ;
	} 
} /* end of adjective and "in/out" preposition "for" loop */

/* purge processed adjective from sentence */
if (sw_purge) purge(j_purge, &jacc) ;
 
/* Verb grammer check "for" loop */
/* see if the sentence is of a command sentax */
sw_loop = FALSE ;
for (i = 0; i < Verb_max; i++) {
	if (sent[0] == verb_table[i]) {
		if (synonym(jacc)) {
			sw_loop = TRUE ;
			break ;
		}
		return ;
	}
} /* end of verb grammer check "for" loop */
if (sw_loop) continue ;

/* First word is not a verb so check to see if this is a "question" sentence */
/*    this logic can certainly be improved  */
for (i = 0; i < Quest_max; i++) {
	if (sent[0] == quest[i]) {
		/* shift the sentence over and load in "question" */ 
		for (j = jacc; j >= 0; j--) sent[j+1] = sent[j] ;
		sent[0] = V_QUESTION ;
		tag[V_QUESTION] = TRUE ; 
		if (++jacc == 2) {
		/* Sentence is a one word command */
			tag[V_VERB_ONLY] = TRUE ;
			tag[sent[1]] = TRUE ;
			verb = V_QUESTION ;
			return ;
		}
		if (synonym(jacc)) {
			sw_loop = TRUE ;
			break ;
		}
		return ;
	} 
} /* end of first word not a verb so check if "question" block */
if (sw_loop) continue ;
 
/* This is not a question and the first word is --not-- a verb. */
/*     Therefore a verb is embedded and must be swapped in. */
if (jacc != 1) for (j = 1; j <= jacc-1; j++) {
	/* Check to see if the word is a move command */
	if (sent[j] <= 10) {
		tag[V_MOVE] = TRUE ;
		i_ws = sent[0] ;
		sent[0] = sent[j] ;
		sent[j] = i_ws ;
		if (synonym(jacc)) {
			sw_loop = TRUE ;
			break ;
		}
		return ;
	} /* end of simple move command block */

	/* if not a move command then check the verb table */
	for (i = 0; i < Verb_max; i++) {
		if (sent[j] == verb_table[i]) {
			i_ws = sent[0] ;
			sent[0] = sent[j] ;
			sent[j] = i_ws ;
			if (synonym(jacc)) {
				sw_loop = TRUE ;
				break ;
			}
			return ;
		}
	}
	if (sw_loop) break ;
} /* end of verb is embedded and must be swapped in block */
if (sw_loop) continue ;

/* Verb error routine */
printf ("If there was a verb in that sentence, I didn't understand ") ;
printf ("it.\n") ;

} /* end of outer most infinite "for" loop to parse in the words */

} /* --- end of "parse" subroutine --- */


#if (PROTOTYPE)
int synonym(int jacc)
#else
int synonym(jacc)
int jacc ;
#endif
/**************************************/
/*                                    */
/*         Synonym Function           */
/*                                    */
/* Version: Mk 1.0    6 December 1992 */
/*                                    */
/**************************************/
{
register int i, j ;
int j_point ;
int sw_movement, sw_adverb, sw_adverb_fnd ;

ADVERB_STRUCT *adv ;

#if (PROTOTYPE)
void purge(int, int*) ;
#endif

/* prescan for verb connected movement commands */
switch(sent[0]) { 
case V_go:
case V_move:
case V_walk:
case V_run:
case V_jump:
case V_leap:
case V_hop:
case V_stroll:
case V_saunter:
case V_swagger:
	sw_movement = TRUE ;
	break ;
default:
	sw_movement = FALSE ;
}

/* adverb scan, sent[0] is the verb */
sw_adverb = FALSE ;
sw_adverb_fnd = FALSE ;
adv = adverb ;
for (i = 0; i < Adv_max; i++) {
	for (j = 1; j <= jacc-1; j++) {
		/* see if this is an adverb */
		if (sent[j] == adv->Adverb) {
			j_point = j ;
			sw_adverb = TRUE ;

			/* does the sentence have the companion verb? */
			if (adv->Modified_verb == sent[0]) {
				sent[0] = adv->Generated_verb ;
				sw_adverb = FALSE ;
				sw_adverb_fnd = TRUE ;

			/* purge processed adverb from sentence */
				purge(j, &jacc) ;
			}
		}
	}
	adv++ ;
}

/* purge unprocessed adverb from sentence */
if (sw_adverb && (!sw_movement)) purge(j_point, &jacc) ;
 
/* scan the sentence for the movement direction */
if ((!sw_adverb_fnd) && sw_movement) {
	for (j = 0; j <= jacc-1; j++) {
		if (sent[j] <= 10) {
			tag[V_MOVE] = TRUE ;
			tag[V_DIRECTION] = TRUE ;
			verb = sent[j] ;
			return(FALSE) ;
		}
		if (sent[j] == V_LINE_END) break ;
	}
	printf("Where to?  In what direction?\n") ;
	return(TRUE) ;
} 

tag[sent[0]] = TRUE ;  /* activate the tag for the verb */
 
if (jacc == 1) {
/* Sentence is a one word command */
	tag[V_VERB_ONLY] = TRUE ;
	verb = sent[0] ;
	if (sent[0] <= 4) return(FALSE) ; /* first 5 elements are reserved */
	return(FALSE) ;
}

/* Load the "tag" matrix for detected words and synonyms */
for (j = 1; j <= 19; j++) {
	if (sent[j] == V_LINE_END) break ;
	if (sent[j] <= 10) tag[V_DIRECTION] = TRUE ;
	if (sent[j] <= 4) continue ; /* first 5 elements are reserved */
	tag[sent[j]] = TRUE ;  /* activate an element for each word */

	/* Deal with synonym nouns */
	switch(sent[j]) {

	case V_automatic:
	case V_AUTO:
		tag[V_auto] = TRUE ;
		continue ;
 
	case V_bar:
		tag[V_gold] = TRUE ;
		continue ;

	case V_beer:
	case V_fourex:
	case V_Fourex:
		tag[V_can] = TRUE ;
		continue ;

	case V_cockroaches:
		tag[V_PLURAL] = TRUE ;
		tag[V_cockroach] = TRUE ;
		continue ;

	case V_diamond:
		tag[V_ring] = TRUE ;
		continue ;
 
	case V_doormat:
		tag[V_mat] = TRUE ;
		continue ;

	case V_drop:
		tag[V_bear] = TRUE ;
		continue ;

	case V_everything:
		tag[V_all] = TRUE ;
		continue ;

	case V_wall:
		tag[V_warning] = TRUE ;
		tag[V_message] = TRUE ;
		continue ;

	case V_money:
		tag[V_bill] = TRUE ;
		continue ;

	case V_lager:
		tag[V_bottle] = TRUE ;
		continue ;

	case V_fuze:
	case V_fuse:
		tag[V_cap] = TRUE ;
		continue ;

	case V_gleeps:
		tag[V_PLURAL] = TRUE ;
		tag[V_gleep] = TRUE ;
		continue ;

	case V_hoop:
		tag[V_snake] = TRUE ;
		continue ;

	case V_M16:
	case V_m16:
	case V_gun:
		tag[V_rifle] = TRUE ;
		continue ;

	case V_kangaroos:
		tag[V_PLURAL] = TRUE ;
		tag[V_kangaroo] = TRUE ;
		continue ;

	case V_magazine:
	case V_ammo:
		tag[V_clip] = TRUE ;
		continue ;

	case V_mail:
	case V_envelope:
		tag[V_letter] = TRUE ;
		continue ;

	case V_charts:
	case V_schedule:
	case V_schedules:
		tag[V_chart] = TRUE ;
		continue ;

	case V_matchbox:
		tag[V_matches] = TRUE ;
	case V_matches:
		tag[V_PLURAL] = TRUE ;
		tag[V_match] = TRUE ;
		continue ;

	case V_Ned:
	case V_kelly:
	case V_Kelly:
		tag[V_ned] = TRUE ;
		continue ;

	case V_off_q:
		tag[V_off] = TRUE ;
		continue ;

	case V_on_q:
		tag[V_on] = TRUE ;
		continue ;
 
	case V_plan:
		tag[V_map] = TRUE ;
	case V_map:
		tag[V_map_frag] = TRUE ;
		continue ;

	case V_painting:
		tag[V_picture] = TRUE ;
		continue ;

	case V_picture:
		tag[V_photo] = TRUE ;
		continue ;

	case V_doors:
		tag[V_PLURAL] = TRUE ;
		tag[V_door] = TRUE ;
		continue ;

	case V_pills:
	case V_packet:
		tag[V_PLURAL] = TRUE ;
	case V_atropine:
		tag[V_pill] = TRUE ;
		continue ;

	case V_safety:
	case V_SAFE:
		tag[V_safe] = TRUE ;
		continue ;
 
	case V_silver:
		tag[V_coin] = TRUE ;
		continue ;

	case V_spinifexes:
		tag[V_PLURAL] = TRUE ;
		tag[V_spinifex] = TRUE ;
		continue ;

	case V_yourself:
	case V_myself:
		tag[V_self] = TRUE ;
		continue ;

	case V_stick:
	case V_explosive:
		tag[V_dynamite] = TRUE ;
		continue ;

	case V_switch:
		tag[V_button] = TRUE ;
		continue ;

	case V_treasure:
		tag[V_all] = TRUE ;
		continue ;

	case V_I:
		tag[V_single] = TRUE ;
		continue ;

	case V_III:
		tag[V_triple] = TRUE ;
		continue ;

	case V_zero:
		tag[V_0] = TRUE ;
		tag[V_NUMBER] = TRUE ;
		number_word = 0 ;
		continue ;

	case V_one:
		tag[V_NUMBER] = TRUE ;
		number_word = 1 ;
		continue ;

	case V_two:
		tag[V_NUMBER] = TRUE ;
		number_word = 2 ;
		continue ;

	case V_three:
		tag[V_NUMBER] = TRUE ;
		number_word = 3 ;
		continue ;

	case V_four:
		tag[V_NUMBER] = TRUE ;
		number_word = 4 ;
		continue ;

	case V_five:
		tag[V_NUMBER] = TRUE ;
		number_word = 5 ;  /* Dinkum doesn't count past 5 */
		continue ;

	case V_forty_nine:
		tag[V_49] = TRUE ;
		continue ;

	case V_sixty_seven:
		tag[V_67] = TRUE ;
		continue ;

	case V_eighty_two:
		tag[V_82] = TRUE ;
		continue ;

	default:
		continue ;
	}
} /* end of sentence tag word scan */
verb = sent[0] ;
return(FALSE) ;

} /* --- end of "synonym" subroutine --- */

#if (PROTOTYPE)
void purge(int k_start, int *k_finish)
#else
void purge(k_start, k_finish)
int k_start, *k_finish ;
#endif
/***********************************/
/*                                 */
/*   Sentence Purging Subroutine   */
/*                                 */
/* Version: Mk 1.0  3 March 1990   */
/*                                 */
/***********************************/
{
register int k ;
int k_end ;

k_end = *k_finish ;
for (k = k_start; k <= k_end-1; k++) sent[k] = sent[k+1] ;
*k_finish = --k_end ;
} /* --- end of "purge" subroutine --- */

#if (PROTOTYPE)
void filler(void)
#else
void filler()
#endif
/***********************************/
/*                                 */
/*        Looker Subroutine        */
/*                                 */
/* Version: Mk 1.0  18 August 1989 */
/*                                 */
/***********************************/
{

if (tag[V_VERB_ONLY]) {
	printf("Fill what?\n") ;
	return ;
}
if (tag[V_can]) {
	if (Can->Location != B_have) 
printf("You don't have the Fourex can in your possession!\n") ;
else printf("I can't do it!  There's a hole in the can's bottom.\n") ;
	return ;
}
if (tag[V_bottle]) {
	if (Bottle->Location != B_have) 
printf("You don't have the bottle in your possession!\n") ;
else printf("I can't do it!  The bottle has a crack in it's bottom.\n");
	return ;
}
printf("I can't fill that!\n") ;
} /* --- end of the "filler" subroutine --- */

#if (PROTOTYPE)
void looker(int n)
#else
void looker(n)
int n ;
#endif
/***********************************/
/*                                 */
/*        Looker Subroutine        */
/*                                 */
/* Version: Mk 1.0  18 August 1989 */
/*                                 */
/***********************************/
{
register int i ;
int m, sw_no_see ;

OBJECT_STRUCT *pnt ;
READ_STRUCT *point ;

#if (PROTOTYPE)
void long_descp(int), describe(int), objlooker(int), gleeper(int) ;
void actor(int), rdtxt(int) ;
OBJECT_STRUCT* point_to_object(int) ;
#else
OBJECT_STRUCT* point_to_object() ;
#endif

/* an isolated "look" means to just look at the room */
if (tag[V_VERB_ONLY]) { 
	/* Check for long description */
	if ((room[n][M_rm_type] == T_was_long)||(n == R_lift_inside))
	   long_descp(n);
	else describe (n) ;
	objlooker(n) ; /* Check if there are objects in the room */
	gleeper(n) ;   /* check for gleeps and update the gleep count */
	/* describe unmovable action objects and status */
	if (room[n][M_unmov_obj]) actor(n) ;
	return ;
}

/* Gleep tank */
if (tag[V_tank]) {
	if (n == R_gleep_tank) {
printf("You look inside the gleep tank and see a blue fluid which\n") ;
printf("smells of chlorine") ;
		if (Tank->Status == 0) {
printf(".\n") ;
			return ;
		}
		if (Tank->Status == 1) {
printf(" and a single gleep submerged in the fluid.\n") ;
			return ;
		}
printf(" and %d gleeps submerged in the fluid.\n",
		Tank->Status) ;
		return ;
	}
	else {
		printf("There is no gleep tank here!\n") ;
		return ;
	}
}

sw_no_see = FALSE ;
point = read_object ;
for (i = 0; i < Read_objcnt; i++) {
	m = (point++)->ID ;
	if (tag[m]) {
		pnt = point_to_object(m) ;
		if (pnt->Type == Z_unmovable) {
			if (pnt->Location == n) {
				rdtxt(m) ;
				return ;
			}
			else sw_no_see = TRUE ;
		}
		else {
			if (pnt->Location == B_have) rdtxt(m) ;
			else 
printf("I can examine an object only if it is in my possession.\n");
			return ;
		}
	}
}
if (sw_no_see) {
	printf("I don't see it here.\n") ;
	return ;
}

/* Deal with unreadable objects */
printf("There is nothing more that I can describe about it.\n");
return ;

} /* --- end of the "looker" subroutine --- */

#if (PROTOTYPE)
void pass(void)
#else
void pass()
#endif
/***********************************/
/*                                 */
/*        Password Subroutine      */
/*                                 */
/* Version: Mk 1.0  29 July 1989   */
/*                                 */
/***********************************/
{
register int i ;
char chr ;
static char *passwd = "2Xngootx7Ysd4Du9" ;

#if (PROTOTYPE)
void exit(int);
char getch(void) ;
#else
char getch() ;
#endif

/* Request password */
printf("Enter password:  ") ;

#ifndef __TURBOC__
for (i = 2; i <= 7; i++) {
	chr = getchar() ;
	if (chr+i-1 != passwd[i]) exit(0) ;
}	
if (getchar() != '\n') exit(0) ;
printf(".\n") ;  /* indicate that the password was accepted */
#endif

#ifdef __TURBOC__
for (i = 2; i <= 7; i++) {
	chr = getch() ;
	if (chr+i-1 != passwd[i]) { 
		for (;;) if (getch() == 3) break ;
		printf("\r                    \n") ;
		exit(0) ;
	}
}
printf("\r.                     \n") ;
#endif

sw_wizard = TRUE ; /* toggle wizard switch */

} /* --- end of the "pass" subroutine */
