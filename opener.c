#define OPNR
#include "dink_sym.h"
#include "dink_glb.h"

#if (PROTOTYPE)
void dialer(int n)
#else
void dialer(n)
int n ;
#endif
/*****************************/
/*      "dial" command"      */
/*     Version:  Mk 1.1      */
/*      29 October 1989      */
/*****************************/
{

/* deal with the question of "What is the combination?" */
if (tag[V_what]) {
printf("I really don't know.  You might try looking around for a\n") ;
printf("series of numbers. Sometimes that can be a clue to the\n") ;
printf("actual combination.\n") ;
	return ;
}

/* See if the combination was dialed in the right place */
if ((n == R_office_mang)&&(Picture->Status >= S_open)) {
	if (tag[V_0] && tag[V_49] && tag[V_67] && tag[V_82]) {
		printf ("Click!! \n");
		Safe->Status = S_dialed ;
		return ; 
	}
printf ("You turned the dial but nothing happened.  I think you \n");   
printf ("dialed the wrong thing. \n");
	return ; 
}
printf ("How am I supposed to dial that? \n");
} /* --- end of the "dialer" subroutine --- */

 
#if (PROTOTYPE)
void inventer(void)
#else
void inventer()
#endif
/*****************************/
/*   "inventory" command     */
/*     Version:  Mk 1.0      */
/*       11 March 1989       */
/*****************************/
{
#if (PROTOTYPE)
void objector(OBJECT_STRUCT*) ;
#endif

register int i;
int j_ws ;
OBJECT_STRUCT *pnt, *point ;
 
j_ws = 0 ;
pnt = object ;
for (i = 0; i < Objcnt; i++) {
	if ((pnt++)->Location == B_have) {
		++j_ws ;
		point = (pnt - 1) ;
	}
}
if ((j_ws == 0)&&(gleep_count == 0)) {
	printf("You've got NOTHING!! \n") ;
	return ;
}
if (j_ws >= 1) {
	if (j_ws == 1) {
		printf("You are carrying ") ;
		objector(point);
		printf ("\n") ;
	}
	else {
		printf ("You are carrying the following: \n");
		pnt = object ;
		for (i = 0; i < Objcnt; i++) {
			if ((pnt++)->Location == B_have) {
				printf("        ") ;
				point = (pnt - 1) ;
				objector(point);
				printf("\n") ;
			}
		}
	}
}
if (gleep_count > 0) {
	if (gleep_count == 1) {
		printf("You have one gleep.\n") ;
		return ;
	}
	printf("You are carrying %d gleeps. \n",gleep_count) ;
}

} /* --- end of the "inventor" subroutine --- */
 
#if (PROTOTYPE)
void drinker(void)
#else
void drinker()
#endif
/*****************************/
/*     "drink" command       */
/*     Version:  Mk 1.0      */
/*       11 March 1989       */
/*****************************/
{
#if (PROTOTYPE)
void no_booze(void) ;
#endif

if (tag[V_can]) {
	if (Can->Location == B_have) {
		printf("The XXXX keeps on coming on ? \n") ;
printf("I think not, for there is no Fourex left for me to drink!\n") ;
	}
	else no_booze() ;
	return ;
}

if (tag[V_bottle]) {
	if (Bottle->Location == B_have) {
printf("Some greedy larrikin has drunk up all of the Black Swan! \n") ;
	printf("Bad on Him! There is none left for me! \n") ;
	return ;
	}
	no_booze() ;
	return ;
}

if (tag[V_water]) {
	printf("There is no water here that I am willing to drink.\n") ;
	return ;
}
	
printf ("What exactly do you want me to drink? \n");
return; 

} /* --- end of the "drinker" subroutine --- */

#if (PROTOTYPE)
void no_booze(void)
#else
void no_booze()
#endif
/*****************************/
/*     Version:  Mk 1.0      */
/*     7 December 1992       */
/*****************************/
{
printf ("You don't have it in your possession to drink!\n");
return ;
} /* --- end of the "no_booze" subroutine --- */

 
#if (PROTOTYPE)
void reader(int n)
#else
void reader(n)
int n ;
#endif
/*****************************/
/*      "read" command       */
/*     Version:  Mk 1.2      */
/*      23 December 1992     */
/*****************************/
{
register int i ;
int m, sw_no_see ;

OBJECT_STRUCT *point ;
READ_STRUCT *pnt ;

#if (PROTOTYPE)
void rdtxt(int) ;
OBJECT_STRUCT* point_to_object(int) ;
#else
OBJECT_STRUCT* point_to_object() ;
#endif

/* reject an isolated "read" command */
if (tag[V_VERB_ONLY]) { 
		printf ("What exactly do you want me to read? \n");
		return;
}

sw_no_see = FALSE ;
pnt = read_object ;
for (i = 0; i < Read_objcnt; i++) {
	m = pnt->ID ;
	if (!(pnt++)->Readable) continue ;
	if (tag[m]) {
		point = (OBJECT_STRUCT*)point_to_object(m) ;
		if (((point->Location == n)&&(point->Type == Z_unmovable))
			||(point->Location == B_have)) rdtxt(m) ;
		else {
			if (point->Type == Z_unmovable) {
				sw_no_see = TRUE ;
				continue ;
			}
			else
printf ("I can't read it because it isn't in my possession. \n");
		}
		return ;
	}
}

/* Deal with unreadable objects */
if (sw_no_see) printf ("I don't see how I can read that.\n") ;
else printf("There is no way in which I can read that. \n");
return ;

} /* --- end of the subroutine "reader" --- */

#if (PROTOTYPE)
void locker(int n)
#else
void locker(n)
int n ;
#endif
/*****************************/
/*     "lock" command        */
/*      Version: Mk 1.0      */
/*      27 January 1992      */
/*****************************/
{
if (tag[V_VERB_ONLY]) {
	printf ("What do you want me to lock? \n");
	return; 
}

if (room[n][M_unmov_obj]) {
	switch (n) {

	/* Managers office */
	case R_office_mang:
if (tag[V_safe]) {
	if (Picture->Status == S_open) { 
		if (tag[V_key]) {
printf("You can't lock a combination safe with a key (no keyhole)!\n") ;
			return ;
		}

		switch (Safe->Status) { 
		case S_open:
printf("You close the safe and it locks with a \"click\". \n");
			break ;

		case S_dialed:
printf("You give the safe's dial a twist, locking the safe. \n");
			break ;

		default:
			printf("The safe is already locked!\n") ;
			return ;
		}
		Safe->Status = S_closed ;
	}
	else printf("I don't see a safe to lock.\n") ;
}
else  printf("You're wasting your time.  You can't lock that! \n");
return;

	/* office entrance */
	case R_office_entr:
	if (tag[V_door]) {
		if (tag[V_key]) {
			if (Key->Location != B_have) {
printf("You don't have the key to this door in your possession! \n");
				return ;
			}
		}
		else {
			printf ("With what shall I lock the door? \n");
			return;
		}

		switch(Door->Status) {
		case S_open:
printf("You close the door and turn the key in the lock, locking the door.\n") ;
			break ;
		
		case S_kicked:
printf("The door has been kicked in! It'll never be locked again.\n");
			return;
		
		case S_unlocked:
		/* The door is closed but unlocked */
printf("You turn the key in the lock, locking the door.\n") ;
			break ;
		} /* end of the office entrance "switch" block */

		room[R_office_entr][2] = R_WALL ;
		Door->Status = S_closed ;
		return; 
	}

	default:
printf("I don't think that is the sort of thing one locks.\n") ;
	}  /* end of "lock" room scan switch */
} /* end of "unmovable action device" block */
else printf("There is nothing here that can be locked! \n");
return ;
}  /* --- end of the "locker" subroutine --- */
 

#if (PROTOTYPE)
void unlocker(int n)
#else
void unlocker(n)
int n ;
#endif
/*****************************/
/*     "unlock" command      */
/*      Version: Mk 1.1      */
/*      16 September 1989    */
/*****************************/
{
 
if (tag[V_VERB_ONLY]) {
	printf ("What do you want me to unlock? \n");
	return; 
}

if (room[n][M_unmov_obj]) {
	switch (n) {

	/* Managers office */
	case R_office_mang:
		if (tag[V_safe]) {
			if (Picture->Status == S_open) { 
printf("This is a combination type safe (no key hole).  You must\n");
printf("dial a combination in order to open this safe. \n");
			}
			else printf("I don't see a safe to unlock.\n") ;
		}
		else 
printf("You're wasting your time.  You can't unlock that! \n");
		return;

	/* office entrance */
	case R_office_entr:
	if (tag[V_door]) {
		switch(Door->Status) {
		case S_open:
			printf("The door is already open! \n");
			return;
		
		case S_kicked:
			printf("The door has been kicked in! \n");
			return;
		
		case S_unlocked:
printf("The door is already unlocked.  However it is still closed! \n");
			return;
		} /* end of the office entrance "switch" block */

		/* The door has to still be unlocked */
		if (tag[V_key]) {
		if (Key->Location != B_have) {
printf("You don't have the key to this door in your possession! \n");
		}
		else {
			printf("You turn the key in the lock and ") ;
			printf("hear a satisfying \"click\".\n");
			Door->Status = S_unlocked ;
		}
		}
		else printf ("With what shall I unlock the door? \n");
		return; 
	}

	default:
printf("I don't think that is the sort of thing one unlocks.\n") ;
	}  /* end of "unlock" room scan switch */
} /* end of "unmovable action device" block */
else printf("There is nothing here that can be unlocked! \n");
return ;
}  /* --- end of the "unlocker" subroutine --- */

#if (PROTOTYPE)
void closer(int n)
#else
void closer(n)
int n ;
#endif
/*****************************/
/*     "close" command       */
/*     Version:  Mk 1.0      */
/*     12 November 1988      */
/*****************************/
{
 
/* scan "close" sentence */
if (!room[n][M_unmov_obj]) {
printf("There is nothing here that can be closed! \n");
	return; 
}

if (tag[V_VERB_ONLY]) {
	printf ("What exactly do you want me to close? \n");
	return; 
}

switch (n) {
	/* office door */
	case R_office_entr:
		if (!tag[V_door]) break ;

		switch (Door->Status) {
		case S_kicked:
printf("The door has been kicked in!  It'll never be closed again.\n");
			return;
		
		case S_open:
			if (tag[V_key]) {
				if (Key->Location != B_have) {
printf("You don't have the key to this door in your possession! \n");
				}
				else {
printf("You close the office door and lock it with the key.\n") ;
					room[R_office_entr][2] = R_WALL ;
					Door->Status = S_closed ;
				}
				return ;
			}
			printf("The office door closes with a slam. \n");
			Door->Status = S_unlocked ;
			return ;
		
		default:
			printf("The office door is already closed! \n");
			return ;
		} /* end of the door status switch */

	/* managers office */
	case R_office_mang:
	if ((!tag[V_picture])&&(!tag[V_safe])) break;
	if (tag[V_safe]) {
		if (Safe->Status != S_open) 
		printf("The safe is already closed. \n");
		else {
	printf("The safe door closes and locks with a \"click\". \n");
			Safe->Status = S_closed ;
		}
	}
	if (tag[V_picture]) {
		if (Picture->Status == S_closed) 
		printf("The platypus picture is already closed. \n");
		else  {
printf("The picture swings flush against the wall, hiding the safe.\n");
			Picture->Status = S_closed ;
		}
	}
	return ;

} /* end of the "close" switch */

printf ("I really don't see how one would close that? \n");
return; 
} /* --- end of the "closer" subroutine --- */

#if (PROTOTYPE)
void opener(int n)
#else
void opener(n)
int n ;
#endif
/*****************************/
/*      "open" command       */
/*     Version:  Mk 2.1      */
/*     25 April 1990         */
/*****************************/
{
register int i, j ;
int sw_found ;

OBJECT_STRUCT *pnt, *point ;

#if (PROTOTYPE)
void boom(void), ender(int), gleeper(int) ; 
void objector(OBJECT_STRUCT*) ;
#endif

/* deal with a terse command */
if (tag[V_VERB_ONLY]) {
	printf ("What exactly do you want me to open? \n");
	return;
}
 
if (tag[V_can]) {
	if (Can->Location == B_have) 
printf("Some bugger has already drunk it up. The stubee is empty!\n");
	else printf("You don't have a can to open! \n") ;
	return; 
}

if (tag[V_letter]) {
	if (Letter->Location == B_have) {
		boom() ; /* cause an explosion */
printf("It's not polite to read other people's mail!!  As you lay\n") ;
printf("bleeding on the floor with your hands and arms blown away,\n") ;
printf("you realize that envelope actually contained a letter bomb!\n");
printf("(A trick widely used by terrorists in the 1970s).  However\n");
printf("the knowledge does you little good since your spirit soon\n");
printf("departs this mortal coil.\n");
		ender(F_died) ;
	}
	else printf("You don't have a letter to open!\n") ;
	return ;
}

if (tag[V_bottle]) {
	if (Bottle->Location == B_have)
printf("Some bugger has already drunk it up. The bottle is Empty! \n");
	else printf("You don't have a bottle to open! \n") ;
	return; 
}

if (tag[V_umbrella]) {
	if (Umbrella->Location == B_have) {
printf("You open the umbrella but find it's full of holes and\n");
printf("its clasp is broken.  As soon as you release it, the\n");
printf("umbrella snaps shut.\n") ;
	}
	else printf("You don't have an umbrella to open! \n") ;
	return; 
}
 
/* Now check to see if the location is consistent with the command */
if (!room[n][M_unmov_obj]) {
	printf ("I don't understand what you want me to open. \n") ;
	return ;
}

switch (n) {
	/* office entrance (door) */
	case R_office_entr:
		if (tag[V_door]) {
		switch (Door->Status) {
			case S_kicked:
printf("The door has been kicked in!  You don't need to open it.\n");
				return;
		
			case S_open:
				printf("The door is already open! \n");
				return ;
		
			case S_unlocked:
printf("As you push open the office door, the rusty hinges creak \n");
printf("from long disuse.  Darkness and stale air seem to exude \n");
printf("from the vacant office.  The way is free for you to enter. \n");
				room[R_office_entr][2] = R_office_hall ;
				Door->Status = S_open ;
				return ;
		
			case S_closed:
				if (tag[V_key]) {
if (Key->Location != B_have) {
	printf("You don't have the key to this door in your possession! \n");
}
else {
printf("You turn the key in the lock and hear a satisfying \"click\".\n");
printf("Then you push open the office door, the rusty hinges creak \n");
printf("from long disuse.  Darkness and stale air seem to exude \n");
printf("from the vacant office.  The way is free for you to enter. \n");
	room[R_office_entr][2] = R_office_hall ;
	Door->Status = S_open ;
}
				}
				else {
printf("The office door is locked tight.");
printf("  You need to unlock it with a key. \n");
				}
				return ;
		} /* end of room status switch */
		} /* end of the door "if" block */
		break ;

	/* managers office */
	case R_office_mang:
		if ((!tag[V_picture])&&(!tag[V_safe])) {
printf("I don't understand how I would open that.\n") ;
			return ;
		}

		if (tag[V_picture]) {
			if (Picture->Status == S_closed) {
printf("You swing open the platypus picture revealing a large wall \n");
printf("safe with a combination dial. \n");
				Picture->Status = S_open ;
			}
			else {
				if (Safe->Status == S_closed) {
printf("The picture is already swung out.  The problem is to open \n");
printf("the safe!!  Hint:  Dial in a combination. \n");
				}
				else {
printf("The picture is already swung out.\n");
				}
			}
			return ;
		} /* end of the picture "if" block */

		if (tag[V_safe]) {
			if (Picture->Status == S_closed) {
printf("I do not see a safe in this office for me to open.  Perhaps\n");
printf("there is a safe hidden in this office somewhere.\n");
				return ;
			}

		switch (Safe->Status) {
		case S_closed:
printf("The safe is locked.  You must first dial the combination\n");
printf("in order to open it.  See if you can find the combination. \n");
			return ;
		
		case S_dialed:
	printf("The safe door swings open smoothly and easily. \n");
			Safe->Status = S_open ;
			sw_active = TRUE ;
			sw_found = FALSE ;
			point = object ;
			for (j = 0; j < Objcnt; j++) {
			if ((point++)->Location == B_in_safe) {
printf("Inside the safe, you see the following: \n");
				sw_found = TRUE ;
				pnt = object ;
				for (i = 0; i < Objcnt; i++) {
					if (pnt->Location == B_in_safe) {
						printf ("        ") ;
						objector(pnt);
						printf("\n") ;
					}
					pnt++ ;
				}				
				break ;
			}
			}
			if (gleep_safe != 0) {
				if (sw_found) {
					if (gleep_safe == 1) 
printf("        one gleep\n") ;
					else
printf("        %d gleeps\n", gleep_safe) ;
				}
				else {
					if (gleep_safe == 1) 
printf("Inside the safe is one gleep.\n") ;
					else
printf("Inside the safe are %d gleeps.\n", gleep_safe) ;
					sw_found = TRUE ;
				}
			}
			if (!sw_found) printf("---The safe is empty.--- \n");
			return ;

		case S_open:
			printf("The safe is already open! \n");
			return ;
		} /* end of the "safe" status switch */
		} /* end of the safe "if" block */
		return ; /* this return statement must remain */

	/* Lift door(s) */
	case R_lift_entr:
		if (tag[V_door]||tag[V_lift]) {
printf("It is not exactly clear how I would open these doors.\n") ;
printf("However I see a push button next to the lift doors.\n") ;
printf("Perhaps if I pressed the button something would happen.\n") ;
		}
		else printf("I'm confused about what I should open.\n");
		return ;
		
} /* end of the "open" room switch */
printf ("I see nothing here that I can open. \n") ;
} /* --- end of the "opener" subroutine --- */

#if (PROTOTYPE)
void boom(void)
#else
void boom()
#endif
{
printf("\n\n");
printf("BBBBBB      OOOOO        OOOOO      MM        MM      !!!\n");
printf("B    BB   OO     OO    OO     OO    M M      M M      !!!\n");
printf("B    BB   OO     OO    OO     OO    M  M    M  M      !!!\n");
printf("BBBBBB    OO     OO    OO     OO    M   M  M   M      !!!\n");
printf("B    BB   OO     OO    OO     OO    M    MM    M      !!!\n");
printf("B    BB   OO     OO    OO     OO    M          M\n");
printf("BBBBBB      OOOOO        OOOOO      M          M      !!!\n\n");
} /* --- end of the "boom" subroutine --- */

#if (PROTOTYPE)
void gleeper(int n)
#else
void gleeper(n) 
int n ;
#endif
/********************************************/
/*                                          */
/*           Gleeper Subroutine             */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
register int i ;
int count ;
static int sw_glp_st = FALSE, cnt_down = 0 ;

/* Gleep display routine */
count = room[n][M_gleep] ;

if (((Torch->Location == B_have)&&Torch->Status)
		||(n < 186)||(n > 202)) { 
	if (count != 0) {
		sw_glp_st = TRUE ; /*  gleeps can now multiply */
		if (count != 1) 
	    	   printf("There are %d gleeps here. \n",count) ;
		else printf("There is a gleep here. \n") ;
		return ;
	}
}

/* Gleep reproduction routine */
if (sw_glp_st == TRUE) {
	if (++cnt_down > 5) {
		cnt_down = 0 ;
		for (i = 0; i <= 9; i++) {
			if (room[gleep_spot[i]][M_gleep] == 0) continue;
			if (room[gleep_spot[i]][M_gleep] > 10000) 
				++room[gleep_spot[i]][M_gleep] ;
			else room[gleep_spot[i]][M_gleep] <<= 1 ;
		}
	}
}
} /* --- end of "gleeper" subroutine --- */

#if (PROTOTYPE)
void clip_in(int ammo_flag)
#else
void clip_in(ammo_flag)
int ammo_flag ;
#endif
/********************************************/
/*                                          */
/*            Clip_In Subroutine            */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 2.00               */
/* (c) Copyright 1990 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
/* ammo clip insertion routine */
if (Rifle->Location != B_have) {
printf("Galah!!  You don't have a rifle to put an ammo clip into.\n");
	return ;
}
if (clip_flag != F_no_clip) {
printf("There is already an ammo clip in the rifle. \n") ;
	return ;
}
if (((Clip->Location != B_have)&&(ammo_flag == F_normal_clip))
	||((Org_clip->Location != B_have)&&(ammo_flag == F_org_clip))) {
printf("You don't possess an ammo clip to put into the rifle.\n");
	return ;
}
/* actually load the clip into the rifle */
Rifle->Type = Z_alias ;
carry_count-- ;
carry_weight -= Clip->Weight  ;
if (ammo_flag == F_normal_clip) {
	Clip->Location = B_unmade ;
	clip_flag = F_normal_clip ;
	Rifle->Status  = Clip->Status ;
}
else {
	Org_clip->Location = B_unmade ;
	clip_flag = F_org_clip ;
	Rifle->Status = Org_clip->Status ;
}
printf("The ammunition clip slides into the rifle with a \"click\".\n");
printf("You have %d bullets in the clip \n",
			Rifle->Status) ;
if (Rifle->Status > 0) 
	printf("You cycle the M16's bolt once to chamber a round.\n");
return ;
} /* --- end of the "clip_in" subroutine --- */

#if (PROTOTYPE)
void clip_out(int n)
#else
void clip_out(n)
int n ;
#endif
/********************************************/
/*                                          */
/*           Clip_Out Subroutine            */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
int ammo_flag ; 

/* remove clip from rifle */
if (Rifle->Location != B_have) {
	printf("You Bloody Galah!  ") ;
	printf("You don't have a rifle in your possession!\n");
	return ;
}
if (clip_flag == F_no_clip) {
	printf("There is no clip in the rifle. \n") ;
	return ;
}
/* eject the clip from the rifle */
Rifle->Type = Z_normal ;
if (clip_flag == F_normal_clip) {
	Clip->Location = n ;
	ammo_flag = F_normal_clip ;
}
else {
	Org_clip->Location = n ;
	ammo_flag = F_org_clip ;
}
++room[n][M_obj_cnt] ;
clip_flag = F_no_clip ;
printf("You press the \"eject\" button on the rifle and the ") ;
printf("magazine falls to the ground.\n") ;

if (Rifle->Status > 0) {
printf("You then cycle the M16's bolt once to clear the chamber. ");
printf("The unfired round\n") ;
printf("is ejected from the breech and rolls out of sight. \n") ;
	if (ammo_flag == F_normal_clip) Clip->Status = --Rifle->Status ;
	else Org_clip->Status = --Rifle->Status ;
}
else {
	if (ammo_flag == F_normal_clip) Clip->Status = 0 ;
	else Org_clip->Status = 0 ;
}
Rifle->Status = 0 ;
return ;
} /* --- end of the "clip_out" subroutine --- */

#if (PROTOTYPE)
void igniter(int n)
#else
void igniter(n)
int n ;
#endif
/********************************************/
/*                                          */
/*           Igniter Subroutine             */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
#if (PROTOTYPE)
void switcher(int) ;
long time(long*) ;
#else
long time() ;
#endif

/* reject single verb command */
if (tag[V_VERB_ONLY]) {
	printf("What exactly do you want me to set alight?\n") ;
	return ;
}

/* deal with 'light torch' command */
if (tag[V_torch]) {
	switcher(n) ;
	return ;
}

/* see if the player has or requested matches */
if (!tag[V_match]) {
	printf("What am I to light it with?\n") ;
	printf("(I am not prepared to rub two sticks together.)\n") ;
	return ;
}
if (Matches->Location != B_have) {
	printf("I have no matches!\n") ;
	return ;
}
else {
/* reject spurious "ignite" command */
	if ((!tag[V_cap])&&(!tag[V_dynamite])
		&&(sent[2] != V_LINE_END)) {
printf("It would be a fire hazard to set that alight.\n");
		return ;
	}

/* deal with spurious "light dynamite with match" */
if (tag[V_dynamite]&&(Dynamite->Location != B_have)) {
	printf("You have no dynamite to ignite.\n") ;
	return ;
}

/* deal with spurious "light cap with match" */
if (tag[V_cap]&&(Dynamite->Location != B_have)
	&&(Cap->Location != B_have)) {
printf("You don't have one to ignite.\n") ;
	return ;
}

/* light up the match(es) */
	if (tag[V_PLURAL]) {
printf("You open up the match box and strike ALL of the matches.\n");
		Matches->Location = B_destroyed ;
	}
	else {
printf("You take one match from the match box and ignite it.\n") ;
	}
}

/* see if player selected burnable objects */
if (tag[V_cap]&&(Cap->Location == B_have)) {
printf("You then ignite the fuse of the blasting cap.\n\n"); 
printf("Ssssssssssssssssssssssss........\n");
	clock_explode = time(0) + 11 ;
	sw_clock = TRUE ;
	flag_clock = V_cap ;
	return ;
}

if ((tag[V_cap]||tag[V_dynamite])&&
	(Dynamite->Location == B_have)) {
	if (Dynamite->Type == Z_alias) {
printf("You then ignite the fuse of the dynamite's blasting cap....\n");
printf("You need to very quickly get very far away from this thing!!");
printf("\n\nSsssssssssssssssssssssss........\n");
		clock_explode = time(0) + 11 ;
		sw_clock = TRUE ;
		flag_clock = V_dynamite ;
	 	return ;
	}
	else {
printf("You then ignite the dynamite. Which is an odd thing\n"); 
printf("to do since it doesn't have a blasting cap in it.  The\n");
printf
  ("\"dynamite\" (which is actually a very safe mining explosive)\n");
printf("burns for a few minutes, billowing out smelly black smoke\n");
printf("and eventually goes out leaving a few scant ashes behind.\n") ;
		Dynamite->Location = B_destroyed ;
	 	return ;
	}
}

} /* -- end of the "igniter" subroutine --- */

#if (PROTOTYPE)
void hold_it(void)
#else
void hold_it()
#endif
/********************************************/
/*                                          */
/*            Wait Subroutine               */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
#if (PROTOTYPE)
char getch(void) ;
#endif

#ifdef __TURBOC__
/* Stop scrolling the screen until the user is ready */
printf("               [Press any key to continue]\r") ;
getch() ;
printf("                                          \n") ;
#endif

#ifndef __TURBOC__
printf("               [Press RETURN to continue]\n") ;
getchar() ;
#endif

} /* --- end of the "hold_it" subroutine --- */

#if (PROTOTYPE)
void eater(void)
#else
void eater()
#endif
/********************************************/
/*                                          */
/*            Eater Subroutine              */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{

#if (PROTOTYPE)
void ender(int) ;
#endif

/* reject single verb command */
if (tag[V_VERB_ONLY]) {
	printf("What exactly do you want me to swallow?\n") ;
	return ;
}

/* deal with "eat (atropine) pill(s)" command */
if (tag[V_pill]) {
	if (Pills->Location != B_have) {
printf("You don't have the atropine pills in your possesion!\n") ;
		return ;
	}
	if (tag[V_PLURAL]) {
printf("You remove ALL of the pills from the packet and swallow\n");
printf("the lot.  For a couple of minutes nothing happens, then you\n");
printf("start seeing double and have nervous twitches. You then\n");
printf("start shaking violently and collapse to the ground.\n") ;
printf("Eventually you pass out and expire from atropine poisoning.\n");
		ender(F_died) ;
	}
	if (--pill_count <= 0 ) {
		Pills->Location = B_destroyed ;
		carry_count-- ;
		carry_weight -= Pills->Weight  ;
printf("You swallow the last atropine pill and throw away the empty\n");
printf("packet which disappears from sight.  ") ;
	}
else printf("You swallow one atropine pill.  ") ;
		i_poison += 10 ;
		if (i_poison >= 30) {
printf("\nAfter a moment you have a violent seizure and die.\n") ;
			ender(F_died) ;
		}
		if (i_poison >= 20) {
printf("\nYou begin to shake violently and can barely stand.\n") ;
			return ;
		}
		if (i_poison >= 15) {
printf("\nYour hands become a bit jittery and your vision blurred.\n") ;
			return ;
		}
		printf("The drug has no ill effect.\n") ;
	return ;
}
else 
printf("I am not inclined towards putting that into my mouth!\n") ;

} /* --- end of the "eater" subroutine --- */

#if (PROTOTYPE)
void ender(int i_quit)
#else
void ender(i_quit)
int i_quit ;
#endif
/********************************************/
/*                                          */
/*            Ender Subroutine              */
/*                                          */
/*     Software by Gary A. Allen, Jr.       */
/*           Version: Mk 1.00               */
/* (c) Copyright 1989 by Gary A. Allen, Jr. */
/*                                          */
/********************************************/
{
#if (PROTOTYPE)
void hold_it(void), new_score(void), exit(int) ;
#endif

/* get last score */
new_score() ;

if (Tank->Status != 0) sw_active = TRUE ; 

if (i_quit == F_died) { 
	hold_it() ;
	score -= 100 ;
printf ("\nOh Dear!  You've just turned yourself into a corpse! \n\n");
printf ("For getting killed you lose 100 points. \n\n") ;
}

/* Scoring Block */
for(;;) {
if (!sw_active) {
	if (score == 0) { 
		printf("You concluded the game with no points.  ") ; 
		printf("What a pitiful performance!!\n") ;
	}
	else {
printf("You concluded the game with a miserable negative score\n") ;
printf("of %d points.  Your score was better BEFORE you \n",score);
printf("started playing (need I say more on how this reflects\n");
printf("upon your limited aptitude at Dinkum).\n") ;
	}
	break ;  /* drop out of the scoring block */
}

if (score == 0)  {
printf("You concluded the game with no points ") ;
	if (Tank->Status == 0) { 
printf("and didn't drop a single gleep\n") ;
printf("into the gleep tank. The word \"embarrassing\" sums it up!\n") ;
	}
	else {
		if (Tank->Status > 1) {
printf("but you did put %d gleeps\n",Tank->Status) ;
printf("into the gleep tank.\n") ;
		}
		else {
printf("but you did manage to find a gleep\n") ;
printf("and put it in the gleep tank, (Hah!! What an achievement!).\n");
		}
	}
}

else {
if (score > 0)
printf ("You concluded the game with %d points",score);
else {
printf("You concluded the game with a miserable negative score\n") ;
printf("of %d points.  Your score was better BEFORE you \n",score);
printf("started playing (need I say more on how this reflects\n");
printf("upon your limited aptitude at Dinkum).  You ") ;
	if (Tank->Status == 0) { 
printf("also failed to\nget any gleeps into the tank.  At least ");
printf("you're consistent.\n\n") ;
	}
	else {
printf("managed\nto get something into the gleep tank.  However ");
printf("it hardly\nmatters, considering your poor score.\n\n") ;
	}
	break ;  /* drop out of the scoring block */
}
	if (Tank->Status == 0) 
printf(".\nHowever you placed no gleeps in the gleep tank.\n") ;
	else {
		if (Tank->Status > 1) {
printf (" and placed %d gleeps\n",Tank->Status) ;
printf ("in the gleep tank.  Good on you, Mate!\n") ;
		}
		else {
printf(" but you did manage to find a gleep\n") ;
printf("and put it in the gleep tank.\n") ;
		}
	}
}
break ;  /* drop out of the scoring block */
} /* end of the ifinite "for" loop scoring block */

/* Closing Remark */
printf("\nDinkum has ended.  If you are interested in more ") ;
printf("information\nabout this program type:    dinkum -h\n") ;
exit(0);

} /* --- end of "ender" routine --- */
 
#if (PROTOTYPE)
OBJECT_STRUCT* point_to_object(int find_id)
#else
OBJECT_STRUCT* point_to_object(find_id)
int find_id ;
#endif
/*****************************/
/*  Object Pointer Function  */
/*     Version:  Mk 1.0      */
/*      9 January 1993       */
/*****************************/
{

register int i;
OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
void bugs(int) ;
#endif
 
pnt = object ;
for (i = 0; i < Objcnt; i++) {
	if (pnt->ID == find_id) return(pnt) ;
	pnt++ ;
}
printf("Run time error detected in \"point_to_object\" function.\n") ;
printf("\"find_id\" value was %d.\n", find_id) ;
bugs(Logic_error) ;
return(pnt) ;  /* this is just a dummy return for Lint */

} /* --- end of "point_to_object" function --- */

