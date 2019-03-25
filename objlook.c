#define OBJLKR
#include "dink_sym.h"
#include "dink_glb.h"

#if (PROTOTYPE)
void objlooker(int n)
#else
void objlooker(n)
int n ;
#endif
/*********************************************************/
/*                                                       */
/*    --- Object in Room Examination Subroutine ---      */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  18 May 1990       */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
register int i ;
OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
void objector(OBJECT_STRUCT*) ;
#endif

if (((Torch->Location == B_have) && Torch->Status) || 
   (n < 186) || (n > 202)) { 
	if (room[n][M_obj_cnt] == 1) {
		pnt = object ; /* initialize the pointer */
		for (i = 0; i < Objcnt; i++) {
			if ((pnt->Location == n)&&(pnt->Type != Z_unmovable)) {
				if (n == R_office_mang) {
					printf("On the floor you see ") ;
					objector(pnt) ;
					printf (".\n") ;
				}
				else {
 					printf("You see ") ;
					objector(pnt) ;
					printf (".\n") ;
				}
			}
			pnt++ ;
		}
	}
	if (room[n][M_obj_cnt] > 1) {
		if (n == R_office_mang) 
printf ("You see the following on the floor: \n");
		else printf ("You see the following: \n");
		pnt = object ; /* initialize the pointer */
		for (i = 0; i < Objcnt; i++) {
			if ((pnt->Location == n)&&(pnt->Type != Z_unmovable)) {
				printf ("        ") ;
				objector(pnt) ;
				printf ("\n") ;
			}
			pnt++ ;
		}
	}
}
} /* end of "objlooker" subroutine */
 
#if (PROTOTYPE)
void kelly(int n)
#else
void kelly(n) 
int n ;
#endif
/********************************************************************/
/*                                                                  */
/*                  --- Ned Kelly Subroutine --                     */
/*                                                                  */
/* Software by Gary A. Allen, Jr. 5 November 1989  Version: Mk 1.2  */
/*           (c) Copyright 1989 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int i, k ;
static int ned_look = 0, sw_fiddle = TRUE ;
int  sw_ned_look, sw_ned_set ;
OBJECT_STRUCT *pnt ;

/* check if Ned  Kelly is dead */
if (Ned->Location == B_destroyed) return ;

/* this switch is for Ned looking for treasure once per cycle */
sw_ned_look = FALSE ;
sw_ned_set = FALSE ;

/* check if player is in Ned's trigger rooms */
switch (n) {
/* Cause Ned Kelly to steal */
case R_lift_inside:
	/* are there valuables in the safe and the safe open? */
	if ((score > 0) && (Safe->Status != S_closed)) {
	/* is the office building open? */
		if ((ned_look > 3)||(Door->Status == S_open)
				||(Door->Status == S_kicked)
				||(Door->Status == S_unlocked)) {

			if (ned_look > 3) {
				Door->Status = S_kicked ;
				room[R_office_entr][2] = R_office_hall ;
			}

/* scan the object list for treasure in safe and transfer to hideout */
			pnt = object ; /* initialize the pointer */
			for (i = 0; i < Objcnt; i++) {
				if ((pnt->Location == B_in_safe)
						&& (pnt->Value > 0)) {
					++room[R_hideout][M_obj_cnt] ;
					pnt->Location = R_hideout; 
					sw_ned_set = TRUE ;
					Picture->Status = S_open ;
				}
				pnt++ ;
			}	
		}
/* the safe is open with treasure but the door is locked */
		else {
			++ned_look ;
			sw_ned_look = TRUE ;
		}
	} /* end of the block concerning Ned and the safe */

	if (sw_valuable) {
		pnt = object ; /* initialize the pointer */
		for (i = 0; i < Objcnt; i++) {
/* scan for treasure laying around outside the building on surface */
			for (k = 22; k <= 36; k++) { 
				if ((pnt->Location == k)
					&&(pnt->Value > 0)) {
					++room[R_hideout][M_obj_cnt] ;
					--room[k][M_obj_cnt] ;
					pnt->Location = R_hideout; 
					sw_ned_set = TRUE ;
					sw_valuable = FALSE ;
					break ;
				}
			}	
			for (k = 144; k <= 145; k++) {
				if ((pnt->Location == k)&&
					(pnt->Value > 0)) {
					++room[R_hideout][M_obj_cnt] ;
					--room[k][M_obj_cnt] ;
					pnt->Location = R_hideout; 
					sw_valuable = FALSE ;
					sw_ned_set = TRUE ;
					break ;
				}
			}	
		/* scan the office building for treasure on the floor */
			for (k = 37; k <= 41; k++) { 
				if ((pnt->Location == k)&&
					(pnt->Value > 0)) {
/* if the office bldg. door is open then Ned Kelly steals treasure */
		if ((Door->Status == S_open)||(Door->Status == S_unlocked)
				||(Door->Status == S_kicked)) {
			++room[R_hideout][M_obj_cnt] ;
			--room[k][M_obj_cnt] ;
			pnt->Location = R_hideout; 
			sw_valuable = FALSE ;
			sw_ned_set = TRUE ;
			break ;
		}
/* if Ned Kelly sees locked treasure four times, he kicks in the door */
		if (ned_look > 3) {
			Door->Status = S_kicked ;
			room[R_office_entr][2] = R_office_hall ;
			++room[R_hideout][M_obj_cnt] ;
			--room[k][M_obj_cnt] ;
			pnt->Location = R_hideout; 
			sw_valuable = FALSE ;
			sw_ned_set = TRUE ;
		}
		else {
			if (!sw_ned_look) ++ned_look ;
			sw_ned_look = TRUE ;
			break ; /* conclude the office bldg. loop */
		}
		break ;
				}
			}	
			pnt++ ;
		}	
	} /* end of block concerning Ned and loose treasure */

	if (sw_ned_set) {
		Ned->Status = F_stealing ; 
		Ned->Location = R_hideout ;
		room[R_hideout][M_monster] = 1 ;
		sw_ned_set = FALSE ;
	}
	return ;

case R_office_entr:
/* Cause Ned Kelly to run away with treasure */
	if (Ned->Status == F_stealing) {
		Ned->Status = F_asleep ;
printf("There is an odd looking character with an iron bucket on his ");
printf("head and a swag\n");
printf("bag over his shoulder running away from the ");
printf("office building towards\nthe desert. \n\n") ;
		return ;
	}
	if ((ned_look == 2) && sw_fiddle && (Door->Status != S_open)
			&&(Door->Status != S_kicked)
			&&(Door->Status != S_unlocked)) {
		sw_fiddle = FALSE ;
printf("As you approach the office building's door, you see a\n");
printf("strange looking character with a bucket on his head and\n") ;
printf("wearing an iron breast plate.  He is on his knees before\n") ;
printf("the door trying to pick the lock with a bit of coat hanger\n") ;
printf("wire. Suddenly, he turns and sees you coming. With amazing\n"); 
printf("speed, he throws away his wire and runs off towards the\n") ;
printf("open desert.\n\n") ;
		return ;
	}
} /* end of the ned kelly room switch block */
} /* --- end of the "kelly" subroutine  --- */ 

#if (PROTOTYPE)
void sounder(int n)
#else
void sounder(n) 
int n ;
#endif
/********************************************************************/
/*                                                                  */
/*                  --- Gong Sounding Subroutine --                 */
/*                                                                  */
/* Software by Gary A. Allen, Jr. 21 June 1989     Version: Mk 1.0  */
/*           (c) Copyright 1989 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
#if (PROTOTYPE)
void exit(int), hold_it(void) ;
void los_angeles(void) ;
char getche(void) ;
#endif

char letter ;

/* see if player is in the gong room */
if (n != R_gong) {
	if (tag[V_gong]) printf("I don't see a gong here.\n") ;
	else printf("I don't see how you can do that.\n") ;
	return ;
}

/* The player is in the gong room. Does he have the clapper? */
if (tag[V_clapper]) {
	if (Clapper->Location == B_have) {
		if (!tag[V_gong]) {
printf("With what are you going to do that with the clapper?\n") ;
			return ;
		}
printf
("\n  GGGGGGGG       OOOOOOOO     NN       NN     GGGGGGGG     !!!\n") ;
printf
("GG        GG   OO        OO   NNN      NN   GG        GG   !!!\n") ;
printf
("GG             OO        OO   NN N     NN   GG             !!!\n") ;
printf
("GG             OO        OO   NN  N    NN   GG             !!!\n") ;
printf
("GG   GGGGGGG   OO        OO   NN   N   NN   GG    GGGGGG   !!!\n") ;
printf
("GG        GG   OO        OO   NN    N  NN   GG        GG   !!!\n") ;
printf
("GG        GG   OO        OO   NN     N NN   GG        GG\n") ;
printf
("GG        GG   OO        OO   NN      NNN   GG        GG   000\n") ;
printf
("  GGGGGGGG       OOOOOOOO     NN       NN     GGGGGGGG     000\n\n") ;

/* see if the "end game" can begine */
		/* Check to see if the recorder was used */
		if (Gong->Status == S_recorder) {
printf("You hear an ethereal voice which says:\n\n") ;
printf("Sorry Mate!  You used the bloody data recorder which gave you\n") ;
printf("an unfair advantage.  If you want to be admitted into the final\n") ;
printf("part of Dinkum and have a chance at winning then you must find\n") ;
printf("all the treasure, come back here and sound the gong WITHOUT having\n") ;
printf("started Dinkum with the command switch \"-S\" (NO data recorder).\n\n");
printf("You did however put in a good effort.  Better luck next time!\n") ;
			Gong->Status = S_told ;
			return ;
		}
		if (Gong->Status == S_told) {
			printf("Nothing happened.\n") ;
			return ;
		}

		/* No recorder so admit player to endgame */
		if ((score < max_score)||(Tank->Status == 0)) {
printf("You hear an ethereal voice which says:\n\n") ;
			if (score < max_score) {
printf("Sorry Mate!  You haven't put all of the treasure in the\n") ;
printf("safe yet.  Find the rest, and then the secret of the gong\n") ;
printf("will be revealed.\n") ;
				return ;
			}
			if (Tank->Status == 0) {
printf("Good on you Mate!  You've found all of the treasure.\n") ;
printf("However you haven't put a single gleep in the gleep tank!\n");
printf("You're not a Fair Dinkum Adventurer until you've put at\n") ;
printf("least one gleep in the tank.\n") ;
				return ;
			}
		}
		/* Begin the End Game */
printf("There is a loud \"Fromp!\" as a portcullis crashes down and\n");
printf("seals the northern (and only) exit.  The lights go dim and\n");
printf("a hazy fog appears in the room.  Slowly this fog coalesces\n") ;
if (sw_warned) {
printf("into the now familiar form of Banjo Patterson.  For some\n") ;
printf("odd reason Banjo is holding in his right hand a sword of\n") ;
printf("fire such as one reads about in Genesis. The deathly quiet\n");
printf("is broken when Banjo begins to speak:\n") ;
}
else {
printf("into a ghostly human form.  This ethereal being is wearing\n") ;
printf("a grey flannel suit, a bowler hat, and has a gold pocket\n") ;
printf("watch chain looped across the front of his waist coat.  He\n");
printf("is holding in his right hand a sword of fire such as one\n") ;
printf("reads about in Genesis.  You can hear \"Waltzing Matilda\"\n");
printf("being played softly in the background.  You know what?\n");
printf("I think this ethereal being is none other than the ghost\n") ;
printf("of Banjo Patterson!  With this realization Banjo begins to\n") ;
printf("speak:\n") ;
}
		hold_it() ;
printf("\"Good on you, Fair Dinkum Adventurer!  You have braved\n") ; 
printf("the perils of hoop snakes, drop bears, and mutant wombats.\n") ;
printf("You have solved many riddles, collected much treasure and\n") ;
printf("encountered true evil and dealt with it appropriately.\n");
printf("However it has occured to us that you might not be one of\n") ;
printf("the chosen few who can be admitted into the Land of the\n") ;
printf("Blessed.  The possibility remains that you could be a\n") ;
printf("whinging Pom or a bleeding Yank.  Therefore you will be\n") ;
printf("tested with three questions.  If you answer correctly, you\n") ;
printf("will be admitted into paradise. However should you answer\n");
printf("falsely, you will be sent to another place, an abode of\n");
printf("darkness and dread.  So answer wisely, for you will not be\n") ;
printf("given a second chance!\"\n\n") ;

printf("What is the capital of Australia?\n\n") ;
printf("     A) Sydney\n") ;
printf("     B) Canberra\n") ;
printf("     C) Melbourne\n\n") ;
printf("Answer A, B, or C:  ") ;
#ifndef __TURBOC__
		for(;;) {
			letter = getchar() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('b' == letter)||('B' == letter)) 
			printf("\nCorrect!\n\n") ;
#endif

#ifdef __TURBOC__
		for(;;) {
			letter = getche() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('b' == letter)||('B' == letter)) 
			printf("\n\nCorrect!\n\n") ;
#endif
		else {
			los_angeles() ;
			return ;
		}

printf("In the Australian emblem there appears two animals on\n") ;
printf("either side of a shield.  One of the two animals is a\n") ;
printf("kangaroo.  What species is the other animal?\n\n") ;
printf("     A) Koala Bear\n") ;
printf("     B) Platypus\n") ;
printf("     C) Emu\n\n") ;
printf("Answer A, B, or C:  ") ;
#ifndef __TURBOC__
		for(;;) {
			letter = getchar() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('c' == letter)||('C' == letter)) 
			printf("\nCorrect!\n\n") ;
#endif

#ifdef __TURBOC__
		for(;;) {
			letter = getche() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('c' == letter)||('C' == letter)) 
			printf("\n\nCorrect!\n\n") ;
#endif
		else {
			los_angeles() ;
			return ;
		}

printf("Which place is a state in Australia?\n\n") ;
printf("     A) Arcadia\n") ;
printf("     B) Patagonia\n") ;
printf("     C) Tasmania\n\n") ;
printf("Answer A, B, or C:  ") ;
#ifndef __TURBOC__
		for(;;) {
			letter = getchar() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('c' == letter)||('C' == letter)) 
			printf("\nCorrect!\n\n") ;
#endif

#ifdef __TURBOC__
		for(;;) {
			letter = getche() ;
			if ((letter != '\n')&&(letter != ' ')) break ;
		}
		if (('c' == letter)||('C' == letter)) 
			printf("\n\nCorrect!\n\n") ;
#endif
		else {
			los_angeles() ;
			return ;
		}

/* Player has won the game */
printf("You see Banjo Patterson with a beatific smile.  He waves\n") ;
printf("his firey sword with a florish and the scene around you\n") ;
printf("dissolves into a million tiny motes of light.  You now\n") ;
printf("find yourself wearing swimming togs.  You are being carried\n");
printf("by a guard of honour made up of four sumptuous shielas\n") ;
printf("dressed in string bikinis and four handsome lifeguards.\n") ;
printf("They carry you to a perfect beach on South Stradbroke\n") ;
printf("Island.  Off in the distance on the Queensland mainland\n") ;
printf("you see the Gold Coast which vaguely resembles the Emerald\n") ;
printf("City of the classic movie.  Your guard of honour sets you\n") ;
printf("down and hands you a can of Power's Bitter.  Three\n") ;
printf("beautiful white pelicans float over head in a clear blue\n") ;
printf("sky completing a scene of exquisite beauty.\n\n") ;
printf("You're in paradise Mate and you've also won the game!\n\n") ;

/* deal with final gleep announcement */
if (Tank->Status == 1) {
printf("---- A hint for those who want to go on playing Dinkum ----\n");
printf("In this game you only put the minimum single gleep in the\n");
printf("gleep tank.  In future games try seeding fertile tunnels\n");
printf("with gleeps and reproducing them.  Build up as many gleeps\n");
printf("as you can and then hit the gong before Dinkum times out.\n");
}
else {
printf("You won this game with %d gleeps in the gleep tank.\n\n",
	Tank->Status) ;
}
		if (sw_wizard) return ;
		else exit(0) ;
	}
	else {
		printf("I don't have a clapper to hit it with! \n") ;
		return ;
	}
}
else {
	printf("\nThud!\n\n") ;
	printf("Nothing happened.\n") ;
printf("I think you'd have more success if you used a gong clapper.\n");
	return ;
}
} /* --- end of the "sounder" subroutine  --- */ 

#if (PROTOTYPE)
void los_angeles(void)
#else
void los_angeles()
#endif
/********************************************************************/
/*                                                                  */
/*                 --- Los Angeles Subroutine --                    */
/*                                                                  */
/*       Player enters false answer and goes to Los Angeles.        */
/*                                                                  */
/* Software by Gary A. Allen, Jr. 7 December 1992  Version: Mk 1.0  */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
#if (PROTOTYPE)
void exit(int) ;
#endif

printf("\n        -!-!-!-!-!-     Wrong!    -!-!-!-!-!-\n\n") ;
printf("Banjo Patterson brings down the sword of fire onto your\n");
printf("head. The scene around you disappears in a flash and you\n");
printf("find yourself transported to.....\n\n") ;
printf("             Pico Blvd., West Los Angeles\n\n") ;
printf("L.A. is having a stage three smog alert.  The air is so\n");
printf("foul you can taste it.  A Los Angeles municipal bus roars\n");
printf("by covering you in soot.  Across the street you see a\n");
printf("modern day Neanderthal selling vials of Crack to children.\n"); 
printf("The person next to you has taken a definite physical\n");
printf("interest in you.  She/he is wearing a short skirt and has a\n");
printf("beehive hairdo.  He/she also has a five o'clock shadow, and\n");
printf("bicepts so thick that he could collapse your skull with a\n");
printf("single thump.\n\n") ; 
printf("We now leave this unhappy scene.  Since you were sent to\n") ;
printf("Los Angeles your score has been zeroed.\n\n") ; 
printf("So ends yet another unsuccessful session at Dinkum!\n") ;

if (sw_wizard) return ;
else exit(0) ;

} /* --- end of the "los_angeles" subroutine  --- */ 


