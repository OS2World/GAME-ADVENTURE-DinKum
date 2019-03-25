#define MNSTR
#include "dink_sym.h"
#include "dink_glb.h"

int sw_snaked = FALSE, sw_wombat = FALSE ;
 
#if (PROTOTYPE)
void monster(int loc_pnt[3])
#else
void monster(loc_pnt)
int loc_pnt[3] ;
#endif
/********************************************************************/
/*                                                                  */
/*                  --- The Monster Subroutine ---                  */
/*                                                                  */
/*  monster_flag is a global variable input parameters              */
/*                                                                  */
/* Software by Gary A. Allen, Jr. 24 January 1993,  Version: Mk 1.6 */
/*           (c) Copyright 1993 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int j ;
int sw_chasing, sw_local ;
static int sw_hoop = FALSE, bear_flag = 0 ;
static int sw_replaced = FALSE ;
static int sw_nogo = FALSE, sw_guarded = TRUE ;
static int sw_letter = FALSE ;
static int count_down = 0 ;

MONSTER_STRUCT *mnstr, *mnstr_local, *mnstr_chase ;

#if (PROTOTYPE)
void ender(int), long_descp(int), hold_it(void), boom(void) ;
void ned_kills(void), mullah_kills(void) ;
void see_letter(int*, int*) ;
void chief_mullah(int*) ;
int bribe_mullah(int*) ;
void chaser(MONSTER_STRUCT*, int[3]) ;
#else
int bribe_mullah() ;
#endif
 
/* set up some of the input variables */
sw_chasing = FALSE ; /* turn off the chasing monster switch */
sw_local = FALSE ;   /* turn off the local monster switch */

/* There can be no active monsters while in the closet */
if (loc_pnt[0] == R_closet) {
	monster_flag = F_no_monster ;
	if (sw_letter == TRUE) {
		sw_letter = FALSE ;
		sw_nogo = TRUE ;
printf("\nYou hear a loud \"BOOM!\" from the Prayer Room followed\n");
printf("by the sounds of people shouting and cursing in Farsi. I\n");
printf("think it is definitely time that we leave.\n") ;
	}
	return ;
}

/* scan the enemy table for the local and/or chasing monsters */
for (j = 0; j <= Enemy_cnt; j++) {
	mnstr = (monster_start + j) ;  /* point to the monster */
	if (mnstr->Location == loc_pnt[0]) {
		sw_local = TRUE;
		mnstr_local = mnstr ;
	}
	else if (mnstr->Status != F_asleep){
		if ((N_mullah == j)||(N_guards == j)||((N_ned == j)&&
		(mnstr->Status == F_stealing))) continue ;
		sw_chasing = TRUE;
		mnstr_chase = mnstr ;
	}
} 

/* see if the monster is local */
if (sw_local) {
/* deal with case of being chased by monster to another monster */
if (sw_chasing) {
 
	switch(mnstr_chase->Type) {
/* Mutant wombat scares off the local monser */
	case N_wombat:
/* put the local monster to sleep and swap location with wombat  */
	mnstr_local->Status = F_asleep ;
	--room[mnstr_local->Location][M_monster] ;
	mnstr_local->Location = Wombat->Location ;
	++room[Wombat->Location][M_monster] ;
	chaser(mnstr_chase, loc_pnt) ;
	return ;
 
/* Hoop Snake breaks off the chase */
	case N_hoop_snake:
printf("                     ---- What a relief!! ---- \n") ;
printf("           The dreaded hoop snake has broken off pursuit.\n");
printf("                         But what is this!!\n\n") ;
printf("You see yet another terrible creature!\n");
	sw_replaced = TRUE  ;
	break ;
	}
 
	/* put the chasing monster to sleep */
	monster_flag = F_no_monster ;
	mnstr_chase->Status = F_asleep ;
	sw_chasing = FALSE;
}

/* local monster routines */
switch(mnstr_local->Type) {

/* Revolutionary Guard local (only) behavior */
case N_guards:
monster_flag = F_monster_active ;

/* guards always kill after the letter bomb has exploded */
if (sw_nogo) {
printf("\nWith you are three men dressed in ripped and shredded ");
printf("clothes which have\nbeen blackened by an explosion.  They ") ;
printf("are armed to the teeth and insane\nwith rage.  They take ");
printf("one look at you and proceed to cut you to pieces with\n");
printf("their automatic weapons!\n\n");
	ender(F_died) ;
}

/* guards always kill if they see a rifle */
if (Rifle->Location == B_have) {
printf("With you are four men dressed in rather shabby clothes. ");
printf("Three of them\nare clutching AK-47 assault rifles while ");
printf("the fourth one is holding an Uzi\nmachine gun. They ") ;
printf("take one look at the M-16 rifle which you are clutching,\n");
printf("point their own weapons at you and proceed to hose you ");
printf("with a hail of\nlead!  Five seconds later you look like ");
printf("a piece of Swiss cheese.\n\n") ;
	ender(F_died) ;
}

switch (Guards->Status) {
	case F_asleep:
		Guards->Status = F_passive ;
printf("With you are four men dressed in rather shabby clothes. ");
printf("Three of them\nare clutching AK-47 assault rifles while ");
printf("the fourth one is holding an Uzi\nmachine gun. They ") ;
printf("search you but find nothing that is obviously a\n") ;
printf("weapon.  They are in a quandary on what to do with ") ;
printf("you, since you\nliterally appeared out of thin air.\n");
		return ;
	
	case F_passive:
		if (Mullah->Status == F_asleep) {
printf("\nThe four men have concluded that the best thing to do\n");
printf("with you is to take you to their superiors.  Two of the men\n");
printf("roughly grab hold of you and fling you bodily through the\n");
printf("doorway to the east.\n\n") ;
		loc_pnt[0] = R_prayer;
		long_descp(R_prayer) ;
		chief_mullah(&count_down) ;
		return ;
		}
		if (sw_guarded) {
printf("\nAll of the guards are currently in the prayer room.\n") ;
			sw_guarded = FALSE ;
		}
		return ;

	case F_aggressive:
		Guards->Status = F_killing ;
printf("\nThe four guards grab you by the arms and legs, and frog\n");
printf("march you back into the prayer room.\n");
		loc_pnt[0] = R_prayer;
		return ;

	case F_killing:
printf("\nThe guards are tired of fooling with you.  One of them\n") ;
printf("hits you on the head with the butt of his rifle.  Then the\n");
printf("other two guards drag you outside where you are executed\n");
printf("before a jeering mob of 30,000 people!\n\n") ;
		ender(F_died) ;

} /* end of the Guards local routine and switch block */


/* Chief Mullah local (only) behaivor */
case N_mullah:
switch (Mullah->Status) {
	case F_asleep:
		chief_mullah(&count_down) ;
		return ;

	case F_aggressive:
		/* The Mullah takes any valuables dropped */
		if (bribe_mullah(&count_down)) return ;

		/* The Mullah sees and takes the letter */
		if (Letter->Location == R_prayer) {
			see_letter(&count_down, &sw_letter);
			return ;
		}
		count_down++ ;
		switch(count_down) {
		case 1:
printf("\nThe Mullah is waiting for you to give him something.\n") ;
			return ;
		case 2:
printf("\nThe Mullah is becoming quite impatient.  You had better\n") ;
printf("do something soon!\n") ;
		Mullah->Status = F_killing ;
		}
		return ;

	case F_passive:
		count_down++ ;
		switch(count_down) {

		case 1:
printf("\nThe Mullah is examining the envelope of Muammar's letter.\n");
			return ;

		case 2:
printf("\nThe Mullah has turned the envelope over and is just\n") ;
printf("about to open it.\n") ;
			return ;

		case 3:
			boom() ;
printf("The Mullah opened the letter.  Needless to say, the letter\n") ;
printf("was a bomb.  The good news is the nasty old Mullah died.\n");
printf("The bad news is you died in the explosion as well!\n\n") ;
			ender(F_died) ;
		}

	case F_killing:
		if (bribe_mullah(&count_down)) {
			Mullah->Status = F_aggressive ;
			return ;
		}
		if (Letter->Location==R_prayer) {
			see_letter(&count_down, &sw_letter);
			return ;
		}
printf("\n\"You are a brainless idiot!\" screams the Mullah!\n") ;
		mullah_kills() ;
} /* end of mullah status switch block */

/* The mullah sees Gaddafi's letter (this might be dead code) */
/* temporary */
see_letter(&count_down, &sw_letter);
return ;
/* end of the mullah local behavior routine */

/* Ned Kelly local behavior */
case N_ned:
if (monster_flag == F_no_monster) {
printf("\nAs you approached the entrance of Ned Kelly's hide out, a ") ;
printf("man walked out\n") ;
printf("the front door and prevented you from entering.  He is ");
printf("wearing an iron\n") ;
printf("helmet with thin eye slits which completely covers ");
printf("his head.  He has\n") ;
printf("body armour made of thin sheets of iron that covers ");
printf("his chest and abdomen.\n") ;
printf("He is holding a 12 guage double barrel shotgun ");
printf("and has a pistol on\nhis hip.  ") ;
printf("I could be wrong but I think this is Ned Kelly!\n\n");
	loc_pnt[0] = R_hideout_entr ;
	monster_flag = F_monster_active ;
	Ned->Status = F_passive ;
	return ;
}
else {
	if (Ned->Status == F_killing) ned_kills() ;
printf("\nNed is not about to allow you to enter his hide out.  He ");
printf("is now expressing\n") ;
printf("his displeasure with your continued presence by cocking both ");
printf("of the hammers on\n") ;
printf("his shotgun and pointing it at your head.  I believe it is ");
printf("time to go!!\n\n") ;
	loc_pnt[0] = R_hideout_entr ;
	Ned->Status = F_killing ;
	return ;
}

/* Mutant Wombat monster behavior */
case N_wombat:
sw_replaced = FALSE ; 
if (monster_flag == F_no_monster) {
printf("\n                        ----- OH NO!! -----\n") ;
printf("                  You are in ***SERIOUS TROUBLE*** !!!\n") ;
printf("Forget about hoop snakes, and forget about drop bears.  This ");
printf("is the WORST\n") ;
printf("thing that can be found in the ACME Mine.  You see before ");
printf("you the awful\n") ;
printf("spawn of the Pommy nuclear weapon's tests. Its ancestors ");
printf("were inoffensive\n") ;
printf("creatures, but gamma radiation has transformed this into...\n");
printf("                      The Dreadful Mutant Wombat!! \n") ;
printf("Normally I would advise you to run for your life.  However ");
printf("there's really\n");
printf("no point.  You can not out run this thing, and it's almost ");
printf("impossible to\n");
printf("kill.  You might as well just stand here and let it finish ");
printf("you off as\n") ;
printf("quickly and painlessly as possible.\n\n") ;
	monster_flag = F_monster_active ;
	Wombat->Status = F_aggressive ;
	loc_pnt[1] = loc_pnt[0] ; 
	loc_pnt[2] = 0 ; /* zero out the previous location */
}
else {
	if (Wombat->Status == F_aggressive) {
printf("\nThe wombat is approaching you.  Its mouth is wide open ") ;
printf("showing its\n") ;
printf("enormous canines.  Its claws are fully extended.  The ") ;
printf("wombat sees\n") ;
printf("you as an easy meal and is preparing to feast.\n") ;
		Wombat->Status = F_killing ;
		return ;
	}
	if (Wombat->Status == F_killing) {
		/* The Mutant Wombat kills the player */
printf("\nThe obscene creature has grasped you with its terrible ");
printf("claws!  First the\n");
printf("wombat rips off your right arm with a single jerk and ");
printf("tosses it down its\n");
printf("throat like it was an appetizer (which it was!).  Next ");
printf("the monster studies\n");
printf("you for a moment and then twists off your left leg and ") ; 
printf("chews on it like\n") ;
printf("a turkey drumstick.  After savoring your left leg, it ");
printf("opens its mouth wide\n");
printf("and stuffs you in head first!  Your last memory was ") ;
printf("hearing the crunching\n");
printf("of your own bones as the wombat's jaws clamped down!\n") ;
		ender(F_died) ;
	}
}
return ;

/* Drop Bear monster behavior */
case N_drop_bear:
sw_replaced = FALSE ; 
if (monster_flag == F_no_monster) {
	switch(bear_flag) {
case 0:
printf("\nAs you walk in, you see something that looks vaguely like") ;
printf(" a koala bear\n") ;
printf("sitting in the middle of the floor.  However this \"koala\"") ;
printf(" has vampire\n") ;
printf("teeth and blood drooling down the sides of its mouth. The") ;
printf(" bear takes\n") ;
printf("one look at you and climbs up the wall onto the ceiling.") ;
printf(" It \n") ;
printf("clings to the ceiling much like a fly and seems to be") ;
printf(" positioning\n") ;
printf("itself to be directly over you.  I could be wrong but I") ;
printf(" think this is\n") ;
printf("the deadly DROP BEAR! \n\n") ;
	bear_flag = 1 ;
	break ;

case 1:
printf("\nJust as you walk in, a drop bear flashes by and hits") ;
printf(" the ground with\n");
printf("a THUNK.  That was close!  Had it hit you, and caught ") ;
printf("hold with its\n");
printf("claws, you would have been finished.  The dreaded ");
printf("beast is now\n") ;
printf("running up the wall towards the ceiling to give it ") ;
printf("another go. I\n");
printf("think we had better leave and soon!\n\n") ;;
	bear_flag = 2 ;
	break ;

case 2:
printf("\nAs you walk in, you see a drop bear lounging lazily in") ;
printf(" the middle of\n");
printf("the floor. It rolls over and takes one look at you, ") ;
printf("runs towards\n");
printf("the wall and scampers up to the ceiling.  It is now ");
printf("positioning\n") ;
printf("itself to be directly over you.\n\n") ;
	bear_flag = 1 ;
	}

monster_flag = F_monster_active ;
mnstr_local->Status = F_aggressive ;
}
else {
	if (mnstr_local->Status == F_aggressive) {
printf("\nThe drop bear is now positioned directly above you.  It is") ;
printf(" hanging batlike\n") ;
printf("by its rear paws, with its front arms reaching out with");
printf(" claws fully \n") ;
printf("extended.  Its mouth is wide open with its vampire teeth ");
printf("clearly visible.\n") ;
printf("I think this thing means business!  Let's make a hasty ");
printf("departure!!\n") ;
		mnstr_local->Status = F_killing ;
		return ;
	}
	if (mnstr_local->Status == F_killing) {
		/* The drop bear kills the player */
printf("\nThe drop bear drops on top of you!  First it grabs hold ") ;
printf("of you with its \n") ;
printf("sharp claws that sink deep into your flesh.  Then it bites ");
printf("into your neck \n") ; 
printf("at the jugular vein and begins sucking your blood.  You ");
printf("try desperately \n") ;
printf("to pull the horrible monster off, but it only clamps on ");
printf("harder and sucks \n") ; 
printf("more vigorously.  Soon you grow weak from lack of blood, ");
printf("and lapse into death. \n") ;
		ender(F_died) ;
	}
}
return ;
 
/* Hoop Snake monster behavior */
case N_hoop_snake:
if (monster_flag == F_no_monster) {
	if (sw_replaced) { 
		sw_replaced = FALSE  ;
printf("\nA new and rested hoop snake rolls into view.  The ");
printf("snake sees you, lets go of\n") ;
printf("its tail and starts slithering towards you with fangs ");
printf("at the ready. \n\n");
	}
	else {
		if (!sw_hoop) {
printf("\nSomething that looks vaguely like a barrel hoop rolls into ");
printf("the passage. You \n") ;
printf("suddenly realize to your horror that this is no hoop but a ");
printf("snake biting its \n") ;
printf("own tail.  The snake lets go of its tail and starts to ");
printf("slither towards you \n") ;
printf("like a regular, highly aggressive snake. \n\n");
			sw_hoop = TRUE ;
		}
		else {
printf("\nA hoop snake rolls towards you.  It lets go of its ");
printf("tail and starts slithering\n") ;
printf("in your direction. \n\n");
		}
	}
	monster_flag = F_monster_active ;
	mnstr_local->Status = F_aggressive ;
	loc_pnt[1] = loc_pnt[0] ; 
	loc_pnt[2] = 0 ; /* zero out the previous location */
	return ;
}
else {
	if (mnstr_local->Status == F_aggressive) {
printf("\nThe hoop snake is coiling up in front of you and ") ;
printf("hissing very aggressively. \n") ;
printf("Venom is dripping from its sharp fangs and seems ") ;
printf("to be burning holes into\n") ;
printf("the stone floor.\n\n") ;
printf("I think it would be wise for us to leave....  Quickly!!\n") ;
		mnstr_local->Status = F_killing ;
		return ;
	}
	if (mnstr_local->Status == F_killing) {
		/* The Hoop Snake kills the player */
printf("\nThe hoop snake strikes and bites you right on the nose!") ;
printf("\n\nYou begin to thrash around ") ;
printf("like a Baygon sprayed cocky.  The nerve poison \n") ;
printf("makes you jerk around onto your back with your arms and ") ;
printf("legs flailing about\n") ;
printf("in the air.  With time your spasmodic twitching reduces") ;
printf(" in frequency.  You\n") ;
printf("slowly grind down to a halt with the coming of death. \n") ;
		ender(F_died) ;
	}

}
} /* end of the local monster switch group */
}

chaser(mnstr_chase, loc_pnt) ;
return ;

} /* --- end of the "monster" subroutine --- */

#if (PROTOTYPE)
void chaser(MONSTER_STRUCT *mnstr, int loc_pnt[3])
#else
void chaser(mnstr, loc_pnt)
MONSTER_STRUCT *mnstr ;
int loc_pnt[3] ;
#endif
/********************************************************************/
/*                                                                  */
/*               --- Monster Chasing Subroutine ---                 */
/*                                                                  */
/* Software by Gary A. Allen, Jr. 8 December 1992, Version: Mk 2.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{ 

#if (PROTOTYPE)
void ned_kills(void), ender(int) ;
void bugs(int) ;
#endif

switch(mnstr->Type) {
/* Ned Kelly */
case N_ned:
	if (loc_pnt[0] == R_hideout_entr) {
		if (Ned->Status == F_passive) {
printf("\nNed Kelly is standing in front of you and is holding a ");
printf("12 guage shotgun\n") ;
printf("in a rather menacing manner.  This guy is really game!\n\n") ;
printf("I suggest we leave.....   and quickly!!\n\n") ;
			Ned->Status = F_aggressive ;
			return ;
		}
		if (Ned->Status == F_aggressive) {
printf("\nNed seems to be getting impatient with you.  He is now ");
printf("expressing his\n") ;
printf("displeasure with your continued presence by cocking both ");
printf("of the hammers on\n") ;
printf("his shotgun and pointing it at your head.  I really think ");
printf("we should be\n") ;
printf("making a hasty departure!!\n\n") ;
			Ned->Status = F_killing ;
			return ;
		}
		if (Ned->Status != F_killing) {
			monster_flag = F_no_monster ;
			Ned->Status = F_asleep ;
			return ;
		}
		else ned_kills() ;
	}
	else {
		monster_flag = F_no_monster ;
		Ned->Status = F_asleep ;
		return ;
	}
 
/* Mutant wombat chases */
case N_wombat:
	if (loc_pnt[0] == R_lift_inside) {
printf("\nYou run as fast as you can into the lift.  You've made it! ") ;
printf(" You're in the\n") ;
printf("lift! However as you turn around, you realize to your horror") ;
printf(" that the\n") ;
printf("wombat has also made it inside the lift, and the door ");
printf("is closing!!\n\n") ;
printf("                     Ah, Stuff of Nightmares!!!\n") ;
printf("          ---Trapped in a Lift with a Mutant Wombat!!!---\n\n");
printf("This is just too horrible.  Let it suffice... You died. \n");
	ender(F_died) ;
	}
	if (loc_pnt[0] == loc_pnt[2]) {
printf("The wombat is in that direction.  You can't go that way!\n");
		loc_pnt[0] = loc_pnt[1] ;
		return ;
	}
	if (!sw_wombat) {
printf("\nAs you flee down the passage, you hear the ");
printf("\"THUD, THUD, THUD\" of the wombat\n") ;
printf("trudging down the passage.  The horrible thing is after") ;
printf(" you!  Give up\n") ;
printf("all hope!  The wombat is driven by nuclear energy and") ;
printf(" will never stop.\n\n") ;
	sw_wombat = TRUE ;
	}
	else { 
printf("\nThe wombat is still chasing you and not tiring. \n") ;
	}
	monster_flag = F_monster_active ;
	mnstr->Status = F_aggressive ;
	--room[mnstr->Location][M_monster] ;
	++room[loc_pnt[0]][M_monster] ;
	mnstr->Location = loc_pnt[0] ;
	loc_pnt[2] = loc_pnt[1] ;
	loc_pnt[1] = loc_pnt[0] ;
	return ;
 
/* Hoop Snake chases */
case N_hoop_snake:
	if (loc_pnt[0] == R_lift_inside) {
printf("\nYou seek refuge from the hoop snake by fleeing into the ") ;
printf("lift.  Just as you\n") ;
printf("enter the lift, its door begins to close.  Unfortunately the") ;
printf(" hoop snake\n") ;
printf("rolls in the instant before the door is fully closed.\n\n") ;
printf("We will not describe the unpleasant events that occur behind");
printf(" the closed door\n");
printf("of the lift. However one can hear screams, curses, futile ");
printf("banging on the\n");
printf("lift door and loud snake hissing.  After a few minutes ");
printf("there is again silence.\n");
printf("The lift door opens and the hoop snake rolls out and away. ");
printf("A peek inside the\n");
printf("lift reveals your corpse which is in the early phases of ");
printf("rigor mortis.\n") ;
	ender(F_died) ;
	}
	if (loc_pnt[0] == loc_pnt[2]) {
		if (mnstr->Status == F_killing) {
printf("The hoop snake is in that direction.  ") ;
printf("You can't go that way!\n");
		loc_pnt[0] = loc_pnt[1] ;
		return ;
		}
		else {
printf("You have run back the way you came and passed the hoop ");
printf("snake, which\n") ;
printf("is still biting its tail and rolling like a hoop. The ") ;
printf("vile creature\n") ;
printf("hisses in frustration and does a U-turn to continue ") ;
printf("the chase.\n\n") ;
		}
	}
	else {
		if (!sw_snaked) {
printf("\nAs you flee down the passage, you hear the characteristic ") ;
printf("sound of reptilian\n") ;
printf("scales rubbing the stone floor.  You look over your shoulder") ;
printf(" and see the\n") ;
printf("hoop snake is rolling along right behind you! The dreaded") ;
printf(" thing is chasing you!!\n\n") ;
			sw_snaked = TRUE ;
		}
		else {
printf("\nThe hoop snake is rolling along behind you, and still") ;
printf(" in hot pursuit!\n\n") ;
		}
	}
	monster_flag = F_monster_active ;
	mnstr->Status = F_aggressive ;
	--room[mnstr->Location][M_monster] ;
	++room[loc_pnt[0]][M_monster] ;
	mnstr->Location = loc_pnt[0] ;
	loc_pnt[2] = loc_pnt[1] ;
	loc_pnt[1] = loc_pnt[0] ;
	return ;

/* Deactive all other possible monsters */
case N_drop_bear:
case N_mullah:
case N_guards:
	monster_flag = F_no_monster ;
	mnstr->Status = F_asleep ;
	return ;
} /* end of the chasing monster switch group */

/* This logic detects a potentially bad error. */
/*         Normally this is dead code.         */
printf("Run time error detected in \"chaser\" subroutine.\n") ;
printf("\"mnstr->Type\" value was %d.\n",  mnstr->Type) ;
bugs(Logic_error) ;
return ;  /* this is just a dummy return for Lint */

} /* --- end of the "chaser" subroutine --- */

#if (PROTOTYPE)
void ned_kills(void)
#else
void ned_kills()
#endif
/********************************************************************/
/*                                                                  */
/*           --- Ned Killy Kills the Player Subroutine ---           */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 7 December 1992, Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{

#if (PROTOTYPE)
void ender(int) ;
#endif

printf("\nWith an air of professional detachment, Ned Kelly pulls ");
printf("both triggers\n") ;
printf("on his shotgun and blows your head clean off your ") ;
printf("shoulders. \n\n") ;
	ender(F_died) ;
} /* --- end of the ned_kills" subroutine --- */

#if (PROTOTYPE)
void mullah_kills(void)
#else
void mullah_kills()
#endif
/********************************************************************/
/*                                                                  */
/*             --- Mullah Kills the Player Subroutine ---           */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 7 December 1992, Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{

#if (PROTOTYPE)
void ender(int) ;
#endif

printf("\nWith that pronouncement, the chief Mullah claps his hands\n");
printf("twice.  Two Revolutionary Guards drag you outside where you\n");
printf("are executed before a jeering mob of 30,000 people!\n") ;
	ender(F_died) ;
} /* --- end of the "mullah_kills" subroutine --- */

#if (PROTOTYPE)
void see_letter(int *count_on, int *sw_letter)
#else
void see_letter(count_on, sw_letter)
int *count_on, *sw_letter ;
#endif
/********************************************************************/
/*                                                                  */
/*         --- Mullah see Gaddafi's Letter Subroutine ---           */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 7 December 1992, Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
printf("\nThe Mullah gives the letter a casual glance, then\n");
printf("suddenly his face lights up and he claps his hands with\n") ;
printf("glee.\n\n") ;
printf("\"It's a letter from my old friend Muammar!\", he exclaims!\n");
printf("\"This is an occasion for much jubulation.  As a token of\n");
printf("my esteem take this ancient gong clapper made of gold and\n");
printf("ivory.  It was recovered from the personal collection of\n") ;
printf("the deposed Shah. It once belonged to the ancient Persian\n") ;
printf("King Cyrus and is priceless!\"\n\n") ;
printf("With this glad tiding the Mullah hands you the ancient\n") ;
printf("clapper and then reaches down to pick up the letter from\n") ;
printf("his old friend.\n") ;

Mullah->Status = F_passive ;
Guards->Status = F_passive ;
Letter->Location = B_destroyed ;
--room[R_prayer][M_obj_cnt] ;
Clapper->Location = B_have ;
Detector->Location = R_guard ;
++room[R_guard][M_obj_cnt] ;
carry_count++ ;
carry_weight += Clapper->Weight ;
*sw_letter = TRUE ;
*count_on = 0 ;

} /* --- end of the "see_letter" subroutine --- */

#if (PROTOTYPE)
void chief_mullah(int *count_on)
#else
void chief_mullah(count_on)
int *count_on ;
#endif
/********************************************************************/
/*                                                                  */
/*               --- Chief Mullah Subroutine ---                    */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 8 December 1992, Version: Mk 1.0 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int i ;

OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
void hold_it(void) ;
void mullah_kills(void) ;
#endif

printf("\n") ;
hold_it() ;
Mullah->Status = F_aggressive ;
Guards->Status = F_aggressive ;

printf("The chief Mullah (or whatever he is) who is sitting on the\n");
printf("dias glares in your direction and begins expounding in a\n");
printf("long monologue in Farsi. One of his Revolutionary Guards\n") ;
printf("starts translating the Mullah's words into fairly good\n");
printf("English (with an American accent!). Here is what he said:\n") ;
printf("\n\"I can see by your slouch hat, singlet and short pants\n");
printf("that you are a good-for-nothing satanic Australian. I am\n");
printf("compelled to point out that your sort is most unwelcomed in\n");

/* see if the player has any valuables or the letter */
pnt = object ;
for (i = 0; i < Objcnt; i++) { 
	if ((pnt->Location == B_have)&& 
 		((V_letter == pnt->ID)||(pnt->Value > 0))) {

/* Player has something the Mullah wants, so he lives */
printf("this holy precinct.  Unless you can provide some good\n");
printf("reasons (preferably financial ones) to the contrary, I\n");
printf("shall order you to be executed immediately for the\n");
printf("amusement and edification of the local populace!\"\n") ;
			*count_on = 0 ;
			return ;	
	}
	pnt++ ;
}

/* Player has no valuables and doesn't have the letter so he dies */
printf("this holy precinct.  Since you have nothing of value, our\n");
printf("usual practice would be to take you hostage and extract a\n");
printf("ransom from your government.  However the Ozzie Dollar\n") ;
printf("doesn't buy all that much anymore, so we'll just execute\n");
printf("you and leave it at that.\"\n") ;
mullah_kills() ;

} /* --- end of the "chief_mullah" subroutine --- */

#if (PROTOTYPE)
int bribe_mullah(int *count_on)
#else
int bribe_mullah(count_on)
int *count_on ;
#endif
/********************************************************************/
/*                                                                  */
/*               --- Chief Mullah Subroutine ---                    */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 3 January 1993 , Version: Mk 1.0 */
/*           (c) Copyright 1993 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int j ;
int sw_bribe ;
OBJECT_STRUCT *pnt ;

/* The Mullah takes any valuables dropped */
sw_bribe = FALSE ;
pnt = object ;
for (j = 0; j < Objcnt; j++) { 
	if ((pnt->Location == R_prayer) && (pnt->Value > 0)) {
		pnt->Location = B_destroyed ;
		--room[R_prayer][M_obj_cnt] ;
		sw_bribe = TRUE ;
	}
	pnt++ ;
}
if (sw_bribe) {
printf("\nOne of the guards picks up the treasure and hands it over to\n") ;
printf("the chief Mullah who discretely pockets it within his robe.  The\n") ;
printf("Mullah then looks expectantly towards you...  I think he wants\n") ;
printf("more treasure.\n") ;
	*count_on = 0 ;
	return(TRUE) ;	
}
return(FALSE) ;

} /* --- end of the "bribe_mullah" function --- */

