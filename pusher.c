#define PUSHER
#include "dink_sym.h"
#include "dink_glb.h"

#if (PROTOTYPE)
void pusher(int *n_arg)
#else
void pusher(n_arg) 
int *n_arg ;
#endif
/********************************************************************/
/*                                                                  */
/*                  --- The Pusher Subroutine ---                   */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 14 June 1989,    Version: Mk 1.2 */
/*           (c) Copyright 1988 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int i ;
int n ;
static long delta_time, *time_arg = 0 ;
char file_name[80] ;

#if (PROTOTYPE)
void which_button(void) ; 
void lift_moves(void) ; 
void nothing_happens(void) ; 
void cubic(void) ; 
void no_gray(void) ; 
void no_switch(void) ; 
void no_cube(void) ; 
void describe(int) ;
int yes_no(void) ;
long time(long*) ;
void ender(int) ;
#else
long time() ;
int yes_no() ;
#endif
 
/* pass the room pointer */
n = *n_arg ;

/* reject an isolated "push" command */
if (tag[V_VERB_ONLY]) {
	printf ("What exactly do you want me to push? \n");
	return; 
}

/* Deal with the recorder */
if (tag[V_red_button] || tag[V_white_button] || tag[V_green_button]
		|| tag[V_orange_button]) {
	if (Gong->Status == S_recorder) {
	if (Recorder->Location == B_have) {
		if (tag[V_red_button]) {
			if (Recorder->Status != S_inactive) {
				printf("--- The data recorder has stopped ") ;
				if (Recorder->Status == S_playing)
					printf("playing. ---\n") ;
				else printf("recording. ---\n") ;
				Recorder->Status = S_inactive ;
				fclose(fp) ;
			}
			else printf("Nothing happened!\n") ;
			return ;
		}
		if (tag[V_white_button]) {
			printf("Type in the file name for reading from:  ") ;
			scanf("%s",file_name) ;
			if ((fp = fopen(file_name,"r")) == 0) {
printf("I could not open the file:  %s \n",file_name);
printf("This file probably doesn't exit.\n") ;
printf("Try pressing the white button again and using a different name.\n") ;
			}
			else Recorder->Status = S_playing ;
			return ;
		}
		if (tag[V_green_button]) {
			printf("Type in the file name for writing to:  ") ;
			scanf("%s",file_name) ;
			if ((fp = fopen(file_name,"w")) == 0) {
printf ("I could not open the file:  %s \n",file_name);
printf("Try pressing the green button again and using a different name.\n") ;
			}
			else {
				Recorder->Status = S_recording ;
				printf("--- Recording ---\n") ;
			}
			return ;
		}
if (tag[V_orange_button]) {
	printf("Dinkum's clock has been stopped.\n\n") ;
	delta_time = time(time_arg) - (start_time + 3300L) ;

	for (;;) {
		printf("Do you wish to resume playing Dinkum?\n") ;
		if (yes_no()) {
			start_time = time(time_arg) - (delta_time + 3300L) ;
printf("\n+----------------------------------------------------------+\n") ;
printf("| Dinkum's clock is restarted with the same time remaining |\n") ;
printf("| as when it was halted.                                   |\n") ;
printf("+----------------------------------------------------------+\n\n");
			describe(n) ;
			return ;
		}
		else {
			printf("Do you wish to quit Dinkum?\n") ;
			if (yes_no()) ender(F_quit) ;
		}
	}
}
	}
	else printf("You don't have the recorder in your possession!\n") ;
	}
	else printf("I have never seen a button of that color.\n") ;
	return ;
}

switch (n) {
/* Lift entrance at the ground level */
case R_lift_entr:
	if (tag[V_gray_button]) {
		no_gray() ;
		return ;
	}
	if (!tag[V_button]) {
		if (!tag[V_blue_button]) {
			printf ("I don't see why I should push that! \n");
		}
		else nothing_happens() ;
		return ;
	}
	if (Lift_door->Status == S_flashing ) {
printf ("You push the call button and there is a loud \"whirr\" from ");
printf ("an electric motor. \nThe massive steel doors slide open ");
printf ("revealing a huge lift that could hold \ntwenty men at once. ");
printf ("The way is now open for you to enter. \n");
		Lift_door->Status = S_open ;
		room[R_lift_entr][2] = R_lift_inside ;
		break ;
	}
	else {
		if (Lift_door->Status == S_open) {
printf ("You push the call button and there is a loud \"whirr\" from ");
printf ("an electric motor. \nThe massive steel doors slide shut, ");
printf ("closing off access to the lift.\n");
			Lift_door->Status = S_flashing ;
			room[R_lift_entr][2] = R_WALL ;
			break ;
		}
		else {
printf("You pushed the lift call button, but nothing happened.\n");
printf("I think the electrical power has been turned off at the\n") ;
printf("circuit breaker.\n") ;
		break ;
		}
	}
 
/* Lift Compartment */
case R_lift_inside:
	if (tag[V_gray_button]) {
		no_gray() ;
		return ;
	}
 
	/* scan push sentence */
	/* zero level */
	if (tag[V_0]) {
		if (Lift->Status == L0) {
printf ("You pushed the flashing button, but nothing happened.\n");
			break ;
		}
printf ("The steel doors slam shut and you feel heavy as the lift ");
printf ("accelerates \nupwards.  Finally the lift jerks to a halt ");
printf ("and the doors whirr open.  \nSunlight is streaming in. ");
printf ("Once again you are breathing the fresh air.\n");
		Lift->Status = L0 ;
		room[R_lift_inside][3] = R_lift_entr;
		room[R_lift_inside][7] = R_lift_entr;
		return ;
	}
 
	/* forty-ninth level */
	if (tag[V_49]) {
		if (Lift->Status == L49) {
printf ("You pushed the forty-nine button, but nothing happened.\n");
			return ;
		}	
		Lift->Status = L49 ;
		room[R_lift_inside][3] = R_L49_entr;
		room[R_lift_inside][7] = R_L49_entr;
		lift_moves() ;
		return ;
	}
 
	/* sixty-seventh level */
	if (tag[V_67]) {
		if (Lift->Status == L67) {
printf ("You pushed the sixty-seven button, but nothing happened.\n");
			return ;
		}	
		Lift->Status = L67;
		room[R_lift_inside][3] = R_L67_entr;
		room[R_lift_inside][7] = R_L67_entr;
		lift_moves() ;
		return ;
	}

	/* eighty-second level */
	if (tag[V_82]) {
		if (Lift->Status == L82) {
printf ("You pushed the eighty-two button, but nothing happened.\n");
			return ;
		}	
		Lift->Status  = L82;
		room[R_lift_inside][3] = R_L82_entr;
		room[R_lift_inside][7] = R_L82_entr;
printf ("The steel doors slam shut and you feel a sense of ");
printf ("weightlessness as \nthe lift plummets down the mine shaft. ");
printf ("Finally the lift comes to a halt \n");
printf ("and the doors whirr open. \n");
		return ;
	}
	if (tag[V_blue_button]) {
		nothing_happens() ;
		return ;
	}
printf ("This lift can go only to levels 0, 49, 67, or 82 \n");
	return ;

/* inside the closet at the Iranian Parliament */
case R_closet:
	if (tag[V_gray_button]) {
		no_gray() ;
		return ;
	}
	if (tag[V_blue_button] || tag[V_button]) {
		/* Is the command for the black cube */
		if (Cube->Location != B_have) {
			no_switch() ;
		}
printf("There is a bright flash of light! Then suddenly you are\n");
printf("back in the hexagon chamber of the ancient spaceship.\n\n");
		*n_arg = R_transporter ;
	}
	else no_switch() ;
	return ;
 

/* the transporter control panel room */
case R_panel:
	if (tag[V_button]) {
		which_button() ;
		return;
	}
	if (tag[V_blue_button]) {
		if (Cube->Location==B_have) cubic() ;
		else no_cube() ;
		return ;
	}
	if (tag[V_gray_button]) {
		if (!Transporter->Status) {
printf("Lots of the \"Sanskrit\" text is flashing by on the display\n");
printf("panel's CRTs.  There is a whirring noise coming out of the\n");
printf("equipment around you which is increasing in both loudness\n");
printf("and pitch. You've turned something on, that's for sure!\n") ;
			Transporter->Status = TRUE ;
		}
		else nothing_happens() ;
		return ;
	}
default:
	/* Semtex explosive detector */
	if (tag[V_detector] || tag[V_yellow_button] ||
		((Cube->Location != B_have) &&
		(Detector->Location == B_have))) { 
			if (Detector->Location == B_have) {
				/* press Semtex detector button */
printf("You press the button on the Semtex explosive detector and\n");
				for (i = 0; i <= 9; i++) {
					if ((n == i+207)||(n == i+228)) {
if (room[227-i][M_rm_type] == T_lethal) {
	printf("hear a \"beep, beep, beep\".\n") ;
	return ;
}
					}
				}
				printf("the yellow light flashed.\n") ;
			}
			else {
printf("You don't have the detector in your possession.\n") ;
			}
			return ;
		}
		/* Transporter return device */
		if (Cube->Location == B_have) {
			if ((Detector->Location == B_have) && 
				(!tag[V_blue_button])) {
					which_button() ;
					return;
			}
			cubic() ;
			return ;
		}
		if (tag[V_blue_button]) {
			no_cube() ;
			return ;
		}
		if (tag[V_gray_button]) {
			no_gray() ;
			return ;
		}

printf ("You can push as much as you like, but nothing will happen.\n");
} /* end of the switch block */
return; 

} /* --- end of the "pusher" subroutine --- */

#if (PROTOTYPE)
void which_button(void) 
#else
void which_button() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("Which button do you want me to push? \n") ;
return; 
} /* --- end of the "which_button" subroutine --- */

#if (PROTOTYPE)
void lift_moves(void) 
#else
void lift_moves() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf ("The steel doors slam shut and you feel the vibration of ");
printf ("the lift \nmoving in its shaft. Finally the lift jerks ");
printf ("to a halt and the doors whirr open. \n");
return; 
} /* --- end of the "lift_moves" subroutine --- */

#if (PROTOTYPE)
void nothing_happens(void) 
#else
void nothing_happens() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("Nothing happens!\n");
return; 
} /* --- end of the "nothing_happens" subroutine --- */
 
#if (PROTOTYPE)
void cubic(void) 
#else
void cubic() 
#endif
/********************************************************************/
/*                                                                  */
/*              Press cube button in wrong place.                   */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("You press the button on the cube but nothing happens.\n");
return; 
} /* --- end of the "cubic" subroutine --- */
 
#if (PROTOTYPE)
void no_gray(void) 
#else
void no_gray() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("I see no gray button to push!\n");
return; 
} /* --- end of the "no_gray" subroutine --- */
 
#if (PROTOTYPE)
void no_switch(void) 
#else
void no_switch() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("There is nothing here with a push button switch.\n");
return; 
} /* --- end of the "no_switch" subroutine --- */
 
#if (PROTOTYPE)
void no_cube(void) 
#else
void no_cube() 
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992  Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("You don't have the black cube with the blue button in your") ;
printf(" possession!\n") ;
return; 
} /* --- end of the "no_cube" subroutine --- */
 
 
#if (PROTOTYPE)
void switcher(int n)
#else
void switcher(n) 
int n ;
#endif
/********************************************************************/
/*                                                                  */
/*                --- The Switcher Subroutine ---                   */
/*                                                                  */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 29 October 1989  Version: Mk 1.4 */
/*           (c) Copyright 1988 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
int flag_switch, flag_rifle_md ;

#if (PROTOTYPE)
void dialer(int) ;
#endif

/* deal with single verb commands */
if (tag[V_VERB_ONLY]) {
	if (tag[V_turn]) printf("Turn what?\n") ;
	if (tag[V_set]) printf("Set what?\n") ;
	if (tag[V_select]) printf("Select what?\n") ;
	if (tag[V_switch]) printf("Switch what?\n") ;
	return ;
}

/* Deal with changing the safety on the rifle */
if (tag[V_safety]) {
	if (Rifle->Location == B_have) {
		if (tag[V_off]) {
			rifle_flag = F_single ;
printf("The M16 rifle is set to single shot mode ") ;
printf("with the safey off.\n") ;
			return ;
		}
		if (tag[V_on]) {
			rifle_flag = F_safety ;
printf("The M16 rifle's safety has been turned on.\n") ;
			return ;
		}
		printf("How do you want the safety set?\n") ;
	}
	else printf("You're not holding the rifle!\n") ;
	return ;
}

/* deal with special case "turn (safe) dial 0 49 67 82" */
if (tag[V_turn] && tag[V_dial] && (!tag[V_rifle])) {
	dialer(n) ;
	return ;
}

/* deal with special case "turn safe ..." */
if (tag[V_turn] && (!tag[V_dial]) && tag[V_safe]) {
	if (n != R_office_mang) {
		printf("There is no safe here to turn!\n") ;
		return  ;
	}
printf("Since the safe is set in a concrete wall, turning it would\n");
printf("be rather difficult!  Perhaps I should turn the safe's\n") ;
printf("dial instead?\n") ;
	return ;
}

/* initialize the local switches */
flag_switch = F_no_argument ; 
if (tag[V_on]) flag_switch = TRUE ;
if (tag[V_off]) flag_switch = FALSE ;
if (verb == V_light) flag_switch = TRUE ;

flag_rifle_md = F_no_argument ;
if (tag[V_safe]) flag_rifle_md = F_safety ;
if (tag[V_triple]) flag_rifle_md = F_triple ;
if (tag[V_single]) flag_rifle_md = F_single ;
if (tag[V_auto]) flag_rifle_md = F_auto ;

if ((flag_switch == F_no_argument)&&(flag_rifle_md == F_no_argument)) {
printf("You will have to be a little more specific than that. \n") ;
	return ;
}

/* see if it is a simple "on/off" power equipment switch command */
if ((!tag[V_torch])&&(!tag[V_rifle])&&
	(flag_rifle_md == F_no_argument)) {
if (n == R_store_room) {
	/* The circuit breaker is switched off */
	if (flag_switch == FALSE) {
	if (Circuit_breaker->Status) {
printf ("As you pull the switch lever, there is a bright blue \n");
printf ("arc and then all of the lights go out. \n");
		Circuit_breaker->Status = FALSE ;
		Lift_door->Status = S_closed ;
		room[R_lift_entr][2] = R_WALL ;
	}
	else printf ("The circuit breaker is already turned off! \n");
	return;
	}
	/* The circuit breaker is switched on */
	if (flag_switch == TRUE) {
	if (Circuit_breaker->Status) {
	printf ("The circuit breaker is already turned on! \n");
	}
	else {
printf ("As you pull the switch lever, there is a loud \"CLUNK\" \n");
printf ("and you see a POWER ON light glowing. \n");
		Circuit_breaker->Status = TRUE ;
		Lift_door->Status = S_flashing ;
	}
	return;
	}
}          

/* Deal with a garbage command */
printf("I don't understand what you want me to switch. \n") ;
return ;
} /* end of the simple "on/off" switch group */

/* the switch command is to select an M16 rifle firing mode */
if (tag[V_rifle]) {
	if (Rifle->Location == B_have) {

		/* turn the rifle on naively */
		if ((flag_switch==TRUE)||
	           ((flag_rifle_md==F_safety)&&(flag_switch==FALSE))) {
			if (rifle_flag != F_safety) {
printf("The rifle's safety is already off! \n") ; 
				return;
			}
			rifle_flag = F_single ;
printf("The M16 rifle has been set to single shot mode. \n") ;
			return ;
		} 
/* turn on the safety */
	if ((flag_switch==FALSE)||
	  ((flag_rifle_md==F_safety)&&((flag_switch==TRUE)||
	  (flag_switch==F_no_argument)))) {
				if (rifle_flag == F_safety) {
printf("The rifle's safety is already on! \n") ; 
				return;
				}
			rifle_flag = F_safety ;
printf("The M16 rifle's safety has now been turned on. \n") ;
			return ;
	} 
		/* select single shot mode */  
		if (flag_rifle_md == F_single) {
			if (rifle_flag == F_single) {
printf("The rifle has already been set to single shot mode.\n");
				return;
			}
			rifle_flag = F_single ;
printf("The M16 rifle has been set to single shot mode. \n") ;
			return ;
		} 
		/* select triple fire mode */  
		if (flag_rifle_md == F_triple) {
			if (rifle_flag == F_triple) {
printf("The rifle has already been set to triple fire mode.\n");
				return;
			}
			rifle_flag = F_triple ;
printf("The M16 rifle has been set to triple fire mode. \n") ;
			return ;
		} 
		/* select to fully automatice mode */
		if (flag_rifle_md == F_auto) {
			if (rifle_flag == F_auto) {
printf("The rifle has already been set to fully automatic.\n");
				return;
			}
			rifle_flag = F_auto ;
printf("The M16 rifle has been set to fully automatic. \n") ;
			return ;
		} 
	}
	/* This is the rifle nonpossession error handler */
	else {
printf("You don't have a rifle in your possession! \n") ;
		return ;
	}
} /* end of the rifle mode switching block */

/* the switch command is to turn the torch off or on. */
if (tag[V_torch]) {
	if (Torch->Location == B_have) {
		/* "switch torch on" command */
		if (flag_switch==TRUE) {
			if (Torch->Status) {
printf("The torch is already turned on.\n") ;
				return ;
			}
printf("An intense beam of light is projected from the torch.\n") ;
			Torch->Status = TRUE ;
			return ;
		}
		/* "switch torch off" command */
		if (flag_switch==FALSE) {
			if (!Torch->Status) {
printf("The torch isn't switched on.\n") ;
				return ;
			}
printf("The torch switches off with a \"click\".\n") ;
			Torch->Status = FALSE ;
			return ;
		}
	}
printf("You don't have a torch in your possession to switch! \n") ;
	return ;
}

} /* --- end of the "switcher" subroutine --- */

#if (PROTOTYPE)
void new_score(void) 
#else
void new_score() 
#endif
/* This subroutine calculates the score based on treasure in the safe */
{
register int i ;
OBJECT_STRUCT *pnt ;

score = 0 ;
pnt = object ;
for (i = 0; i < Objcnt; i++) if ((pnt++)->Location == B_in_safe)  {
		score += (pnt - 1)->Value ;
} ;
} /* --- end of the "new_score" subroutine --- */

