#define ACTOR
#include "dink_sym.h"
#include "dink_glb.h"
 
#if (PROTOTYPE)
void actor(int n)
#else
void actor(n)
int n ;
#endif
/********************************************************************/
/*                                                                  */
/* Software by Gary A. Allen, Jr. 12 December 1992, Version: Mk 1.3 */
/*           (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int i, j ;
int sw_found ;
static int sw_door_kick = FALSE ;

OBJECT_STRUCT *pnt, *point ;

#if (PROTOTYPE)
void objector(OBJECT_STRUCT*) ;
#endif

switch(n) {

/* mine elevator */
case R_lift_entr:
	switch(Lift_door->Status) {
	case S_closed:
		printf("The lift doors are closed and the lift call button ");
		printf("is not glowing. It \nseems the electrical power has ");
		printf("been turned off at the main switch. \n");
		break ;
		
	case S_flashing:
		printf("The lift doors are closed.  However the call button");
		printf(" is flashing. There \n") ;
		printf("is the sound of electrical equipment ");
		printf("humming within the mine lift. \n");
		break ;
		
		case S_open:
		printf("The lift doors are standing open. \n");
		break ;
	}
	break;
 
/* office building door */
case R_office_entr:
	switch(Door->Status) {
	case S_open:
		printf("      --- The office front door is open. --- \n");
		break;

	case S_kicked:
		if (!sw_door_kick) {
printf("The lock of the front door has been shot at several times.\n"); 
printf("The door itself has been kicked in and is broken off at\n") ;
printf("the hinges.  The passage way is free to enter.\n");
			sw_door_kick = TRUE ;
		}
		else {
printf("The front door of the office has been kicked in. \n") ;
		}
		break ;

	default:
printf("The office has a front door with a sun faded sign \n"); 
printf("upon which is written:  \"Sorry, We are CLOSED\". \n");
printf("      --- The office door is shut. --- \n");
		break ;
	}
	break ;
 
/* Site Managers Office */
case R_office_mang:
	if (Picture->Status == S_closed) {
printf("On the wall is a picture of a platypus wearing a hat with");
		printf(" corks \ndangling from the hat's rim.\n");
		break;
	}
	if ((Safe->Status != S_open)&&(Picture->Status == S_open)) {
printf("Before you is a picture hinged to the wall that has been ");
printf("swung \nopen revealing a closed combination dial wall safe.\n");
		break;
	}
	if ((Safe->Status == S_open)&&(Picture->Status == S_open)) {
printf("Before you is a picture hinged to the wall that has been");
printf(" swung \nout revealing a wall safe with an open door.\n");
		sw_found = FALSE ;
		pnt = object ;
		for (i = 0; i < Objcnt; i++) {
			if (pnt->Location == B_in_safe) {
				sw_found = TRUE ;
printf ("You see the following inside the safe: \n");
				point = object ;
				for (j = 0; j < Objcnt; j++) {
					if (point->Location == B_in_safe) {
						printf ("        ");
						objector(point) ;
						printf("\n") ;
					}
					point++ ;
				}				
				if (gleep_safe != 0) {
					printf ("        ");
					if (gleep_safe == 1) 
						printf("one gleep\n") ;
					else printf("%d gleeps\n",gleep_safe) ;
				}
				break;
			}
			pnt++ ;
		}
		if (sw_found) break ;
		if (gleep_safe != 0) {
printf("There is nothing in the safe except ") ;
			if (gleep_safe == 1) 
				printf("a single gleep.\n") ;
			else
				printf("%d gleeps.\n",gleep_safe) ;
			break ;
		}
		printf("---The safe is empty.--- \n");
		break ;
	} /* end of the "safe open" block */

/* store room */
case R_store_room:
	printf("There is a 1500 Volt circuit breaker box on the wall");
	if (Circuit_breaker->Status) 
printf(" which has \na switch set in the \"on\" position. \n"); 
	else
printf(" which has \na switch set in the \"off\" position. \n"); 
	break;

/* lift compartment */
case R_lift_inside:
	printf("The level button with the number "); 
	switch(Lift->Status) {
		case L0:
			printf("zero"); 
			break ;
		case L49:
			printf("forty-nine"); 
			break ;
		case L67:
			printf("sixty-seven");
			break ;
		case L82:
			printf("eighty-two"); 
			break ;
	} /* end of the Lift->Status "switch" block */
	printf(" is flashing. \n"); 
	break;

} /* end of the "switch" block */ 
} /* --- end of subroutine "actor"--- */

#if (PROTOTYPE)
void objector(OBJECT_STRUCT *pnt)
#else
void objector(pnt)
OBJECT_STRUCT *pnt ;
#endif
{
/* Deal with transformed objects */
if (pnt->Type == Z_alias) {
	if (pnt->ID == V_rifle) {
printf("an M16 infantry rifle with an ammunition clip inserted") ;
		return ;
	}
	if (pnt->ID == V_dynamite) {
printf("a large stick of dynamite with a fuse type blasting cap") ;
		return ;
	}
}
else printf("%s",pnt->Text) ;
} /* --- end of subroutine "objector"--- */
 
#if (PROTOTYPE)
void killer(int n)
#else
void killer(n)
int n ;
#endif
/********************************************************************/
/*                                                                  */
/*  This subroutine had a serious error in it which was discovered  */
/*  by Byron Rakitzis.   Thanks, Byron!                             */
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 19 January 1992  Version: Mk 1.4 */
/*           (c) Copyright 1993 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int j ;

int hits ;
int sw_other_object ;
static int sw_hurt = FALSE ;

MONSTER_STRUCT *mnstr ; 
OBJECT_STRUCT *pnt ; 

#if (PROTOTYPE)
void boom(void), ender(int), gleeper(int), the_fork(void) ;
int shoot_it(void) ;

#else
/* Function prototype for K&R-C */
int shoot_it() ;
#endif

/* Insult the user if he asks for suicide */
if (tag[V_self]) {
	the_fork() ;
	return ;
}

/* Deal with the wrong sorts of "kill" commands */
if (verb == V_kill) {
	/* Verb "kill" only */
	if (tag[V_VERB_ONLY]) {
printf("It may be obvious to you, but you are going to have to tell\n");
printf("me exactly what it is you want to have killed, and \n") ;
printf("with what sort of weapon. \n") ;
		return;
	}

	if (!tag[V_rifle]) {
		if (tag[V_dynamite]) {
			if (Dynamite->Location == B_have) {
printf("You'll find the dynamite is not all that formidable of a weapon.\n") ;
printf("Try lighting some with a match and you'll see why.\n") ;
			}
			else 
printf("You silly gallah! You don't have any dynamite in your possession!\n") ;
		}
		else printf("What weapon am I suppose to use? \n") ;
		return ;
	}
}

sw_other_object = FALSE ;
 
/* shoot Ned Kely */
if (tag[V_ned]) {
	if (Ned->Location == B_destroyed) {
printf("Forget it, you drongo!! Ned Kelly is already dead!\n") ;
		return ;
	}
	if (Ned->Status == F_asleep) {
printf("There is no Ned Kelly here for me to kill! \n") ;
		return ;
	}

	/* Fire the rifle */
	if ((hits = shoot_it()) == 0) return  ;

printf("Ned Kelly keels over dead.  His body suddenly glows a bright ");
printf("orange like it\nis being consummed by a heatless flame ");
printf("and then the late Ned Kelly disappears\ninto a puff of ") ;
printf("blue smoke. \n\n") ;
printf("By the way, the recently deceased bushranger ***was*** ");
printf("wearing iron body\narmour.  However thin sheets of iron ");
printf("would just barely work against nineteenth\ncentury firearms ");
printf("at long range.  Against a modern infantry rifle, Ned's\n");
printf("armour offered about as much protection as a dunny paper ");
printf("bandage. \n") ;
	Ned->Location = B_destroyed ;
	Ned->Status = F_asleep ;
	monster_flag = F_no_monster ;
	room[R_hideout][M_monster] = 0 ;
	
	/* create Ned Kelly's silver teapot */
	++room[R_hideout][M_obj_cnt] ;
	Teapot->Location = R_hideout ;
	return ;
} /* end of the Ned Kelly block */

/* shoot the drop bear */
if (tag[V_bear]) {
	for (j = 2; j <= 5; j++) {
		mnstr = (monster_start + j) ;  /* point to the monster */
		if (mnstr->Status != F_asleep) break ;
	}
	if (j > 5) {
		printf("I see no drop bear for me to kill! \n") ;
		return ;
	}

	/* Fire the rifle */
	if ((hits = shoot_it()) == 0) return  ;

	/* Toggle the hurt switch if this is the first hit */
	if (mnstr->Hits == 0)  sw_hurt = FALSE ;
	mnstr->Hits += hits ;

	if (mnstr->Hits < 30) {
		/* Bear freaks out from being shot too much */
		if (sw_hurt && (mnstr->Hits >= 10)) {
printf("The drop bear has been shot at so many times, that it ");
printf("has gone mad\n") ;
printf("with rage.  It leaps three metres and rips out your ") ;
printf("throat with a\n");
printf("single swish of its claws.  You die instantly. \n") ;
			ender(F_died) ;
		}

		if (mnstr->Hits == 1) {
printf("Your bullet hit the drop bear causing it to howl in ");
printf("anguish.  However drop\n");
printf("bears are pretty tough and just one bullet isn't ");
printf("going to kill it.\n") ;
		}
		else {
			if (!sw_hurt) {
printf("You've hit the drop bear and it is bleeding fairly ");
printf("heavily.\n");
printf("Unfortunately it is still alive and kicking and wants ") ;
printf("your blood \n");
printf("in payment for its.\n") ;
				sw_hurt = TRUE ;
			}
			else {
printf("You've hit the drop bear again.  It is weakening but still ");
printf("alive.\n");
			}
		}
		monster_flag = F_wounded ;
		return ;
	}

	if (rifle_flag == F_single) {
printf("That last bullet was the straw which broke the drop ") ;
printf("bear's back.\n") ;
printf("The blasted thing is finally dead! \n") ;
	}
	else {
printf("The bullets riddled the drop bear with holes, killing it ") ;
printf("instantly.\n") ; 
	}
printf("Suddenly the drop bear's corpse turns into a cloud of greasy ");
printf("blue smoke,\n") ;
printf("which floats away without a trace.\n") ;
	sw_hurt = FALSE ;
	mnstr->Location = B_destroyed ;
	mnstr->Status = F_asleep ;
	monster_flag = F_no_monster ;
	room[n][M_monster] = 0 ;
	return ;
 
} /* end of the drop bear block */

/* shoot the mutant wombat */
if (tag[V_wombat]) {
	if (Wombat->Status == F_asleep) {
		printf("I see no wombat for me to kill!\n");
		return ;
	}

	/* Fire the rifle */
	if ((hits = shoot_it()) == 0) return  ;

	/* Toggle the hurt switch if this is the first hit */
	if (Wombat->Hits == 0)  sw_hurt = FALSE ;
	Wombat->Hits += hits ;

	if (Wombat->Hits < 300) {
		if (Wombat->Hits == 1) {
printf("Your bullet hit the wombat causing it some minor discomfort.");
printf("  Judging from its \n");
printf("behavior, killing this beast is going to be tough! \n") ;
		}
		else {
			if (!sw_hurt) {
printf("You've hit the wombat and got its attention ") ;
printf("but you've not\n");
printf("seriously wounded it.  In fact, you've made it more fierce ");
printf("than before.\n");
				sw_hurt = TRUE ;
			}
			else {
printf("You've hit the wombat again, but it is still going ");
printf("strong.\n");
			}
		}
		monster_flag = F_wounded ;
		return ;
	}

	if (rifle_flag == F_single) {
printf("That last bullet was the straw which broke the ") ;
printf("wombat's back.\n") ;
printf("The blasted thing is finally dead!\n\n") ;
	}
	else {
printf("The bullets did the trick on the wretched thing.  It's ") ;
printf("dead as a doornail.\n\n") ;
	}
printf("Suddenly the wombat's corpse starts to glow with an intense");
printf(" white light.\n") ;
printf("There is then a crackling sound as its body starts to burn.");
printf("  You can\n");
printf("smell the stench of burning hair.  Then the white light");
printf(" begins to dim,\n");
printf("leaving no trace left of the once formidable monster.\n");
	sw_hurt = FALSE ;
	Wombat->Location = B_destroyed ;
	Wombat->Status = F_asleep ;
	monster_flag = F_no_monster ;
	room[n][M_monster] = 0 ;
	return ;
} /* end of the mutant wombat block */

/* shoot the hoop snake */
if (tag[V_snake]) {
	for (j = 6; j <= 13; j++) {
		mnstr = (monster_start + j) ;  /* point to the monster */
		if (mnstr->Status != F_asleep) break ;
	}
	if (j > 13) {
		printf("I see no hoop snake for me to kill! \n") ;
		return ;
	}

	/* Fire the rifle */
	if ((hits = shoot_it()) == 0) return  ;

	/* Toggle the hurt switch if this is the first hit */
	if (mnstr->Hits == 0)  sw_hurt = FALSE ;
	mnstr->Hits += hits ;

	if ((rifle_flag == F_single)&&(mnstr->Hits < 3)) {
		if (mnstr->Hits == 1) {
printf("Your bullet hit the hoop snake.  However the hoop snake's ");
printf("thick scales \n");
printf("slowed the bullet down.  The hoop snake is now hissing ");
printf("furiously. \n") ;
		}
		else {
printf("You've hit the hoop snake again, and it's hurting.  However ");
printf("it is still \n");
printf("alive and full of venom. \n") ;
		}
		monster_flag = F_wounded ;
		return ;
	}

	if (rifle_flag == F_single) {
printf("The bullet hit the hoop snake finishing the horrible ") ;
printf("creature off. \n") ;
	}
	else {
printf("The bullets hit the hoop snake splatting it into a mass of ") ;
printf("mince meat. \n") ; 
	}
printf("Suddenly the bullet holed snake glows red and whooshes ");
printf("into a cloud \n") ;
printf("steam, leaving no traces behind.\n\n") ;
	mnstr->Location = B_destroyed ;
	mnstr->Status = F_asleep ;
	monster_flag = F_no_monster ;
	room[n][M_monster] = 0 ;
	return ;
} /* end of the hoop snake block */

/* see if the target is in the room or holding it */
pnt = object ;
for (j = 0; j < Objcnt; j++) {
	if (tag[pnt->ID]){
 		if (pnt->ID == V_rifle) continue ;
		sw_other_object = TRUE ;
		if (pnt->Location == n)  break ;
		if (pnt->Location == B_have) {
printf("I will ***NOT*** shoot at something that I'm holding!!\n");
			return ;
		}
	}
	pnt++ ;
}
/* Object shoot at */
if (j < Objcnt) {

	switch(pnt->ID) {

	case V_can:
	case V_beer:
	case V_fourex:
	case V_Fourex:
		if ((hits = shoot_it()) == 0) return  ;
printf("The can is hit by a bullet and flies off out of sight.\n");
		Can->Location = B_destroyed ;
		return;

	case V_bottle:
	case V_lager:
		if ((hits = shoot_it()) == 0) return  ;
printf("It is hit by a bullet and shatters into a million pieces.\n");
		Bottle->Location = B_destroyed ;
		return;

	case V_dynamite:
		if ((hits = shoot_it()) == 0) return  ;
printf("Nothing happens!  The \"dynamite\" is actually a very safe\n") ;
printf("mining explosive which won't detonate even if impacted by a high\n") ;
printf("speed bullet (TRUE story!).  However this sort of explosive will\n") ;
printf("always detonate with a blasting cap.\n") ;
		return;

	case V_cap:
		if ((hits = shoot_it()) == 0) return  ;
printf("POP!!  The blasting cap explodes but causes no damage.\n") ;
		Cap->Location = B_destroyed ;
		return;

	case V_gong:
		if ((hits = shoot_it()) == 0) return  ;
		printf("The bullet") ;
		if (hits > 1) printf("s") ;
printf(" went cleanly through the soft silver metal of\n") ;
printf("the gong making a weird humming noise in the process.  It's\n") ;
printf("a pointless waste of ammunition vandalizing this beautiful\n") ;
printf("gong.\n") ;
		return;
		
	case V_safe:
		if (Picture->Status == S_open) {
			if ((hits = shoot_it()) == 0) return  ;
printf("The safe is made out of harden steel.  You'll only waste ") ;
printf("ammunition \nshooting at it.  Try to unlock it instead. \n") ;
		}
		else printf("I don't see a safe to shoot at.\n") ;
		return ;

	case V_letter:
		if ((hits = shoot_it()) == 0) return  ;
		boom() ; /* cause an explosion */
printf("That was clever of you to realize the letter was really\n") ;
printf("a letter bomb.  However shooting a letter bomb while you're\n") ;
printf("right next to it was less than clever. Too bad you got blown\n") ;
printf("to pieces discovering that bit of wisdom.\n\n") ;
		ender(F_died) ;

	default:
		if ((hits = shoot_it()) == 0) return  ;
printf("Except for wasting ammunition nothing much happened.\n") ;
		return ;
	} /* end of target switch group */
} /* end of the "object shot at" block */

if (sw_other_object) {
printf("I don't see the target.\n") ;
	return ;
}

/* There was no target specified so the shot was wasted */
if (tag[V_DIRECTION]) { 
	/* Fire the rifle */
	if ((hits = shoot_it()) == 0) return  ;
printf("You shoot in that direction but didn't accomplish anything\n") ;
printf("except waste ammunition.\n") ;
}
else {
printf("It may be obvious to you, but I don't understand what you\n") ;
printf("want to shoot at.\n");
}
return ;

} /* --- end of the "killer" subroutine --- */
 
#if (PROTOTYPE)
int shoot_it(void)
#else
int shoot_it()
#endif
/********************************************************************/
/*                                                                  */
/*  Software by Gary A. Allen, Jr. 23 January 1993  Version: Mk 1.0 */
/*           (c) Copyright 1993 by Gary A. Allen, Jr.               */
/*                                                                  */
/********************************************************************/
{
register int i ;

int hits, i_10, i_fract ;

if (Rifle->Location != B_have) {
printf("I would do that.  Only there is one small problem.... \n") ;
	printf("I don't have a rifle in my possession! \n") ;
	return(0) ;
}
 
/* Shoot the gun (or at least try to) */
printf("You pull the trigger... \n\n") ;
 
if (clip_flag == F_no_clip) {
printf("Nothing happens!  \n") ;
printf("Your rifle doesn't have an ammunition clip in it.\n") ;
	return(0) ;
}
 
if (Rifle->Status <= 0) {
	printf("Nothing happens!  The ammo clip is out of bullets.\n") ;
	return(0) ;
}
 
switch(rifle_flag) {
case F_safety:
	printf("Nothing happens!  The rifle's safety is still on.\n");
	return(0) ;
			
case F_single:
	printf("Bam! \n\n") ;
	--Rifle->Status ;
	if (clip_flag == F_normal_clip) hits = 1;
		else hits = 100 ;
	break ;

case F_triple:
	if (Rifle->Status >= 3) {
		printf("Bam! Bam! Bam! \n\n") ;
		Rifle->Status -= 3 ;
		if (clip_flag == F_normal_clip) hits = 3;
			else hits = 300 ;
	}
	else {
		for (i = 1; i <= Rifle->Status; i++)  printf("Bam! ") ;
		printf("\n\nYou've run out of bullets. \n\n") ;
		if (clip_flag == F_normal_clip) hits = Rifle->Status ;
		else hits = Rifle->Status * 100 ;
		Rifle->Status = 0 ;
	}
	break ;

case F_auto:
	if (Rifle->Status >= 30) {
		for (i = 1; i <= 3; i++) 
printf("Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! \n") ;
		Rifle->Status -= 30 ;
		hits = 30;
	}
	else {
		i_10 = Rifle->Status / 10 ;
		i_fract = Rifle->Status - (i_10 * 10) ;
		for (i = 1; i <= i_10; i++) 
printf("Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! \n") ;
		for (i = 1; i <= i_fract; i++)  printf("Bam! ") ;
		printf("\n\nYou've run out of bullets. \n") ;
		if (clip_flag == F_normal_clip)  hits = Rifle->Status ;
		else hits = Rifle->Status * 100 ;
		Rifle->Status = 0 ;
	}
	printf("\n") ;
	break ;
} /* end of rifle_flag "switch" block */

return(hits) ;
} /* --- end of the "shoot_it" function --- */

#if (PROTOTYPE)
void the_fork(void)
#else
void the_fork()
#endif
{
printf("If you could see me now then you'd see me giving you a well\n") ;
printf("known Australian finger sign called \"The Fork\".  This is\n") ;
printf("similar to the \"V\" for victory sign but has an entirely\n") ;
printf("different meaning which I trust you understand.\n") ;
} /* --- end of the "the_fork" function --- */
