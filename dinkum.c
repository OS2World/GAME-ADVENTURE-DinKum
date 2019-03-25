#define DINKUM
#include "dink_sym.h"
#include "dink_glb.h"
#include <stdlib.h>

/* ---------------- Version Date --------------- */
char *lb_date = "30 January 1993" ;
/* --------------------------------------------- */

/*  ---- Version Number  ---- */
char *lb_version = "2.12" ;
/*  ------------------------- */

/* ---------------- Version Type --------------- */
char *lb_share = "[GAMES.SOURCES Version]" ;
/* --------------------------------------------- */

/*  ---- Serial Number  ---- */
#define S_number 	1
int serial = S_number ;
/*  ------------------------ */
 
/* Global variables local to this file only */
int sw_help = FALSE, sw_null = FALSE, sw_number = FALSE, sw_standard = FALSE ;

/* MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM */
#if (PROTOTYPE)
void main(int argc, char *argv[])
#else
void main(argc,argv)
int argc ;
char *argv[] ;
#endif
/*********************************************************************/
/*                                                                   */
/*                   --- The Dinkum Program ---                      */
/*                                                                   */
/* Software by Gary A. Allen, Jr. 30 January 1993  Version: Mk 2.12  */
/*            (c) Copyright 1993 by Gary A. Allen, Jr.               */
/*                                                                   */
/*********************************************************************/
{
register int i, j ;

int dig_1, dig_2, sw_loop ;
int move_dir, i_rand1, i_rand2, i_rand3, loc[3] ;
long l_pass, l_base, *time_arg = 0 ;
char chr, cmd[8] ;

MONSTER_STRUCT *mnstr ;
OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
/* Function prototypes ANSI C */
void cmd_switch(char[8], int, int, char *[]) ;
void bugs(int), help(void), locker(int) ;
void kelly(int), long_descp(int), objlooker(int), killer(int) ;
void gleeper(int), actor(int), ender(int), closer(int), opener(int) ;
void dialer(int), taker(int), dropper(int), describe(int) ;
void igniter(int), switcher(int), unlocker(int), sounder(int) ;
void loader(void), eater(void), filler(void), looker(int), exit(int) ;
void monster(int[3]), new_score(void), boom(void), parse(void) ;
int mover(int,int[3]) ; 
int yes_no(void) ;
void inventer(void), drinker(void), reader(int), pusher(int*);
void cheater(void) ; 
void pass(void), unloader(int) ;
long time(long*) ;
char getch(void), getche(void) ;
OBJECT_STRUCT* point_to_object(int) ;

#else
/* Function prototypes K&R-C */
int mover() ; 
int yes_no() ;
long time() ;
char getch(), getche() ;
OBJECT_STRUCT* point_to_object() ;
#endif

/* Software security */
if (serial != S_number) exit(0) ;  /* abort if serial number changed */

/* Load the object pointers */
Rifle = point_to_object(V_rifle) ;
Teapot = point_to_object(V_teapot) ;
Can = point_to_object(V_can) ;
Clip = point_to_object(V_clip) ;
Org_clip = point_to_object(V_org_clip) ;
Recorder = point_to_object(V_recorder) ;
Cap = point_to_object(V_cap) ;
Dynamite = point_to_object(V_dynamite) ;
Letter = point_to_object(V_letter) ;
Clapper = point_to_object(V_clapper) ;
Detector = point_to_object(V_detector) ;
Key = point_to_object(V_key) ;
Umbrella = point_to_object(V_umbrella) ;
Matches = point_to_object(V_matches) ;
Pills = point_to_object(V_pills) ;
Cube = point_to_object(V_cube) ;
Torch = point_to_object(V_torch) ;
Mat = point_to_object(V_mat) ;
Map = point_to_object(V_map) ;
Map_frag = point_to_object(V_map_frag) ;
Bottle = point_to_object(V_bottle) ;
Circuit_breaker = point_to_object(V_circuit) ;
Lift = point_to_object(V_lift) ;
Door = point_to_object(V_door) ;
Safe = point_to_object(V_safe) ;
Lift_door = point_to_object(V_lift_door) ;
Picture = point_to_object(V_picture) ;
Tank = point_to_object(V_tank) ;
Gong = point_to_object(V_gong) ;
Transporter = point_to_object(V_transporter) ;

/* Scan the after the DOS/Unix command for switches or file name */
if (argc > 1) {
for (i = 1; i <= argc-1; i++) {
	/* Flush command vector */
	for (j = 0; j <= 7; j++) cmd[j] = '\0' ;
	/* Get command vector */
	sscanf(argv[i],"%c%c%c%c%c%c%c%c%c", &chr, &cmd[0], &cmd[1],
		&cmd[2], &cmd[3], &cmd[4], &cmd[5], &cmd[6], &cmd[7]) ;
	sw_null = FALSE ;
	if (chr == '?') help() ;
	if (chr == '-') {
		for (j = 0; j <= 7; j++) {
			cmd_switch(cmd, j, i, argv) ;
			if (sw_number) {
				i++ ;
				sw_number = FALSE ;
				break ;
			}
			if (sw_null) break ;
		} /* end of command "for" loop */

		if (j > 7) {
printf("\n!!!! Too many commands on one \"-\" switch group.\n") ;
printf("!!!! Break up the commands into several \"-\" switch groups.\n") ;
			bugs(Failed) ;
		}  
	} /* end of the "-" marker block */

	/* Deal with garbage on the command line */
	else {
printf ("\n!!!! The following on the command line was not understood:  %s \n",
	argv[i]);
		bugs(Failed) ;
	} /* Nondefault scratch file opening block */

} /* end of argument token "for" loop */

if (sw_help) help() ;
} /* end of the command switch block */

/* Deal with someone cheating with switch "-s" */
if (sw_standard && (!sw_wizard)) {
	printf("!!!! Command line switch -s is unknown.\n") ;
	bugs(Failed) ;
}
 
/* Software security */
if (serial != S_number) exit(0) ;  /* abort if serial number changed */

/* Initialize the program */
sw_warned = FALSE ;
l_time = time(time_arg) ;
l_base = l_time/10 ;
l_base *= 10 ;
l_pass = l_time - l_base ;
dig_1 = (int)l_pass ;
loc[2] = 0 ; 	/* zero out the "old" location */

printf("                    ") ;
printf("                   --- Dinkum --- \n");
printf("                    ") ;
printf("     (c) Copyright 1993 by Gary A. Allen, Jr.\n") ;
printf("                    ") ;
printf("  All Rights Reserved. Version %s, %s\n\n",
	lb_version, lb_date);

printf("Would like some initial help with Dinkum?\n") ;

if (yes_no()) {
printf("\nG'day Mate!  Welcome to \"Dinkum\" the Australian adventure");
printf("\ngame.  In Dinkum you'll search for treasure in the\n") ;
printf("Australian Outback.  You give the commands and I'll do the\n");
printf("dangerous work. I understand most plain English sentences.\n");
printf("If you want me to go east then type \"Will you please go\n");
printf("east?\" and press the RETURN or ENTER key.  If you don't\n") ;
printf("enjoy typing then just type \"e\" and press RETURN.  I'll\n");
printf("still go east.  After you have gathered up some things\n") ;
printf("you can see what you have by typing \"inventory\".\n") ;
printf("Sometimes you can learn more about an object by typing\n");
printf("\"examine NAME-OF-OBJECT\".  I understand many other\n") ;
printf("commands and words.  However I'll let you have the fun of\n") ;
printf("finding out what I can and can not understand. Good luck!\n\n");
}

/* produce two random numbers ranging from 0-9 based on system clock*/
l_time = time(time_arg) ;
start_time = l_time ;
l_base = l_time/10 ;
l_base *= 10 ;
l_pass = l_time - l_base ;
dig_2 = (int)l_pass ;

/* generate the actual random array pointers */
if (sw_standard) {
	i_rand1 = 2 ; 
	i_rand2 = 3 ;
	i_rand3 = 1 ;
}
else {
	i_rand3 = (dig_1 + dig_2)/2 ;
	i_rand2 = dig_2/3 ;
	i_rand1 = (dig_1/3) + 1 ;
}

printf("\nIt's a hot summer day (in January) in ") ;
printf("Queensland, Australia.\n") ;
loc[1] = R_meadow ;
loc[0] = R_meadow ;

/* Software security */
if (serial != S_number) exit(0) ;  /* abort if serial number changed */

/* load objects into the rooms */
if (Gong->Status == S_recorder) Recorder->Location = R_meadow ;
pnt = object ;
for (j = 0; j < Objcnt; j++) {
	for (i = 0; i < Obj_init_max; i++) {
		if (pnt->ID == obj_init[i][0]) {
			pnt->Location = obj_init[i][i_rand1] ;
			break ;
		}
	}
	i = pnt->Location ;

	/* Flag the presence of unmovable objects in each room */
        if (pnt->Type == Z_unmovable) room[i][M_unmov_obj] = TRUE ; 

	/* Count up number of movable objects in each room */
	else if (i >= 0) ++room[i][M_obj_cnt] ;
	
	pnt++ ;
}

carry_count = 0 ;
carry_weight = 0 ;

/* Initialize the Monsters */
if ((monster_start = (MONSTER_STRUCT *)calloc((unsigned)(Enemy_cnt+1),
		sizeof(MONSTER_STRUCT))) == 0) {
	printf("\n---- PROBLEMS ----\n") ;
	printf("RAM memory is full!\n") ; 
	printf(" PROGRAM ABORTED\n") ;
	exit(0) ;
}

Ned = (monster_start + N_ned) ;        /* point to the Ned Kelly structure */
Guards = (monster_start + N_guards) ;  /* point to the Guards structure */
Wombat = (monster_start + N_wombat) ;  /* point to the Wombat structure */
Mullah = (monster_start + N_mullah) ;  /* point to the Mullah structure */

/* Load up the monster data structure */
for (i = 0; i <= Enemy_cnt; i++) { 
	mnstr = (monster_start + i) ; 	/* point to the monster */

 	/* locate the monster */
	if (i == 0) mnstr->Location = B_unmade ;
	else mnstr->Location = mon_init[i-1][i_rand2] ;

	/* All monsters are initially asleep */
	mnstr->Status = F_asleep ;

	/* Load Type numbers for the different monsters */
	switch(i) {
	case 2:
	case 3:
	case 4:
	case 5:
		mnstr->Type = N_drop_bear ;
		break ;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		mnstr->Type = N_hoop_snake ;
		break ;
	default:
		mnstr->Type = i ;
	} /* end of the monster Type switch block */

	/* Monsters are initially healthy */
	mnstr->Hits = 0 ;	

	j = mnstr->Location ;
	if (j != B_unmade) ++room[j][M_monster] ;
} /* end of the monster data structure loadup "for" loop */
 
/* load the gleep reproductive locations and seed gleep */
for (i = 0; i <= 9; i++)  
	gleep_spot[i] = gleep_init[i][i_rand2] ;
room[gleep_spot[0]-1][M_gleep] = 1 ; /* seed a nonreproductive spot */ 

/* load safe passage for end-game killing passages  */
room[218 + i_rand3][M_rm_type] = T_short_descp ;

/* Beginning of outer infinite "for" loop */
for(;;) {
/* special action routine */
new_score() ;  /* update the score */

/* See if the game has timed out */
l_time = time(time_arg) ;
if ((!sw_warned) && (l_time > start_time + 3300L)) {
	sw_warned = TRUE ;
	start_time = l_time ;
printf("There's suddenly a puff of blue smoke which fills the room\n") ;
printf("with a hazy cloud.  Slowly this cloud coalesces into a\n") ;
printf("ghostly human form.  This ethereal being is wearing a grey\n") ;
printf("flannel suit, a bowler hat, and glancing at a gold pocket\n") ;
printf("watch which is attached to a long golden chain.  You can\n");
printf("hear \"Waltzing Matilda\" being played softly in the\n") ;
printf("background.  You know what?  I think this ethereal being\n") ;
printf("is none other than the ghost of Banjo Patterson!  With\n") ;
printf("this realization Banjo looks up in your direction and\n") ;
printf("begins to speak:\n\n") ;
printf("\"Sorry mate, you've been at this for too long!  You've\n") ;
printf("got five more minutes to go and then you're history!\"\n\n") ;
printf("Then just as suddenly Banjo Patterson dissolves back into\n") ;
printf("smoke and disappears from view.\n\n") ;
}
if (sw_warned && (l_time > start_time + 300L)) {
printf("You hear someone clearing his throat behind you.  You turn\n") ;
printf("around and see Banjo Patterson has appeared once again.  An\n");
printf("old brass chain is hanging from mid air next to Banjo.  On\n") ;
printf("the end of the chain is a white porcelain tear drop shaped\n");
printf("nob with the word \"PULL\" written on it in black letters.\n") ;
printf("Banjo reaches for the nob and says the following:\n\n\"Sorry") ;
printf(" mate, your time has come!  Better luck next time!\"\n\n");
printf("He gives the chain a quick jerk and everything around you\n") ;
printf("slowly fades from view.\n\n") ;
	ender(F_quit) ;
}

kelly(loc[0]) ; /* check if Ned Kelly can do something */
 
/* Check if there is a long description */
if ((!((room[R_hideout][M_monster] > 0) && (loc[0] == R_hideout))) &&
	(!((monster_flag == F_monster_active) && (loc[2] == loc[0])))) {

	loc[2] = 0 ;

/* Check if there is to be a long room description */
if (room[loc[0]][M_rm_type] == T_long_descp) long_descp(loc[0]) ;
else {
	describe(loc[0]) ;  /* short description */

	/* describe unmovable action objects and status */
	if (room[loc[0]][M_unmov_obj]) actor(loc[0]) ;
}

objlooker(loc[0]) ; /* Check if there are objects in the room */
gleeper(loc[0]) ;   /* check for gleeps and update the gleep count */

/* see if the spaceship's transporter is active */
if (Transporter->Status) {
	if (loc[0] == R_ship_passage) Transporter->Status = FALSE ;
	else if (loc[0] == R_transporter) {
		loc[0] = R_closet ;
		Transporter->Status = FALSE ;
printf("\nSuddenly radiant energy seems to surge from the hexagons\n");
printf("around you.  Then there is a bright flash and you find\n");
printf("yourself in.....\n\n") ;
printf("A closet stinking of moth balls full of nondescript junk.\n") ;
printf("The only exit is to the north through a curtain hanging\n");
printf("over the entrance.\n\n") ; 
	}
} /* end of the "transporter" block */
} /* end of long description check block */

for(;;) {
sw_loop = FALSE ;

/* monster check */
if ((room[loc[0]][M_monster] > 0)||(monster_flag != F_no_monster)) {
	if (monster_flag == F_wounded) monster_flag = F_monster_active ;
	else monster(loc) ;
} /* end of the monster check block */

/* parse in the command */
parse();

/* poison check */
/* remove atropine drug with each game cycle */
if (i_poison > 0) --i_poison ;
else {
	/* accumulate poison if holding the orange clip */
	if (Org_clip->Location == B_have) {
		--i_poison ;
		switch (i_poison) {
		case -20:
	printf("You've developed a nervous tick near your eye.\n") ;
			break ;
		case -30:
	printf("You're hands are starting to shake ") ;
	printf("and you're sweating like a pig.\n") ;	
			break ;
		case -35:
	printf("You're shaking so bad you can barely stand and you ");
	printf("could lose your lunch\nat any moment.\n") ;
			break ;
		case -40:
printf("The toxic fumes coming off of the orange ammo clip you were ") ;
printf("carrying finally\ncaught up with you.  You fall over DEAD!\n") ;
			ender(F_died) ;
		}
	}
	/* remove poison after release of orange clip */
	else if (i_poison < 0) ++i_poison ;
} /* end of the poison check block */

/* clock check */
if (sw_clock) {
	switch (flag_clock) {
	/* see if the blasting cap is to explode */
	case V_cap:
		if (time(time_arg) > clock_explode) {
			if (Cap->Location == B_have) {
printf("                           POP!!\n") ;
printf("The blasting cap which you were stupidly holding in your\n") ;
printf("hand just blew up and took two of your fingers with it!\n") ;
printf("Good thing you've got another eight fingers to spare!\n\n") ;
				carry_count-- ;
				carry_weight -= Cap->Weight ;
			}
			else {
printf("Far down the tunnel you hear a POP!\n") ;
printf("The blasting cap has finally exploded, not that it\n");
printf("achieved much except make a loud noise.\n\n") ;
			}
			Cap->Location = B_destroyed ;
			sw_clock = FALSE ;
		}
		break ;
	
	/* see if the dynamite is to explode */
	case V_dynamite:
		if (time(time_arg) > clock_explode) {
			/* player dies if he is holding the dynamite */
			if (Dynamite->Location == B_have) {
			boom() ;

printf("The dynamite which you were holding and had earlier ignited\n");
printf("the fuse has finally exploded.  That was a rather noisy\n");
printf("and messy way to commit suicide!  Needless to say there is\n");
printf("nothing left of you but a greasy spot.\n") ;
			ender(F_died) ;
			}
			/* player dies if too close during explosion */
			else {
				if (((loc[0] <= 185) && (loc[0] >= 178))
				  || ((loc[0] <= 170) && (loc[0] >= 166))) {
					boom() ;

printf("You weren't far enough away from the dynamite when it\n");
printf("exploded!  The shock wave was still strong enough to blow\n");
printf("your brains out your ears.  Next time try to get to the\n") ;
printf("upper level before the dynamite goes off.\n") ;
					ender(F_died) ;
				}

				/* dynamite explodes and player survives */
				else {
printf("Far down the tunnel you hear a low BOOM!\n") ;
printf("That dynamite you set burning has finally exploded.\n\n");

/* open up the passage to the UFO */
if (Dynamite->Location == R_blast_point) {
	room[R_blast_point][1] = 186 ;
	room[R_blast_point][M_descp] = 55 ;
					}
				}
			}
			Dynamite->Location = B_destroyed ;
			sw_clock = FALSE ;
		} /* end of the dynamite explodes block */
		break ;
	}
} /* end of the clock block */

/* the command is a simple move command */
if (tag[V_MOVE]) {
	if (mover(verb,loc)) break ;
	continue ;
} /* end of the "move" block */

/* complicated command decoder */
switch (verb) {
 
/* "help" command */
case V_help:
case V_info:
printf("There is no help available.  You're on your own!\n") ;
	break ;
 
/* "quit" command */
case V_quit:
	ender(F_quit) ;

/* "question" command */
case V_QUESTION:
	if (tag[V_VERB_ONLY]) {
		if (tag[V_how]) {
printf("That's for you to figure out.\n") ;
			break ;
		}
printf("I don't have a clue!\n") ;
		break ;
	}

	/* Question "Where am I?" */
	if (tag[V_where] && tag[V_am]) {
		tag[V_VERB_ONLY] = TRUE ; /* This is for "looker" */
		looker(loc[0]) ;
		break ;
	}

	/* Question "What have I got?" */
	if (tag[V_what] && tag[V_have]) {
		inventer() ;
		break ;
	}

	/* Question which can't be processed */
printf("You asked a question.  Unfortunately I have no answers.\n") ;
	break ;

/* "inventory" command */
case V_inventory: 
case V_invent:
	inventer() ;
	break;

/* "close" command  */
case V_close:
case V_shut:
	closer(loc[0]) ;
	break;

/* "open" command  */
case V_open:
case V_swing:
	opener(loc[0]) ;
	break;

/* "dial" command  */
case V_dial:
case V_combination:
	dialer(loc[0]) ;
	break ;
 
/* "drink" command */
case V_drink: 
	drinker() ;
	break ;

/* "ignite" command */
case V_ignite: 
case V_light: 
	igniter(loc[0]) ;
	break ;

/* "read" command  */
case V_read:
	reader(loc[0]) ;
	break;
 
/* "push" command  */
case V_push:
case V_press:
	pusher(&loc[0]) ; 
	break ;
 
/* "turn", "switch" command */
case V_switch:
case V_turn:
case V_select:
case V_set:
	switcher(loc[0]) ;
	break ;
 
/* "shoot" command  */
case V_shoot:
case V_fire:
case V_kill:
	killer(loc[0]) ;
	break;
 
/* "unlock" command  */
case V_unlock:
	unlocker(loc[0]) ;
	break;
 
/* "lock" command  */
case V_lock:
	locker(loc[0]) ;
	break;
 
/* "eat" command  */
case V_eat:
case V_swallow:
	eater() ;
	break;
 
/* "fill" command  */
case V_fill:
	filler() ;
	break;
 
/* "sound" command  */
case V_sound:
case V_bang:
case V_hit:
case V_strike:
	sounder(loc[0]) ;
	break;

/* "SVC" wizard move command */
/* This command had an error in it discovered by Per-Anders Eriksson. */
/*      Thanks, Per-Anders!                                           */
case V_svc:
	if (sw_wizard) {
		printf ("Enter room coordinate number:  ");
		scanf ("%d",&loc[0]);
		monster_flag = F_no_monster ; /* turn off monsters */
		sw_loop = TRUE ;
		break ;
	}
	else cheater() ;

/* "STATS" game statistics */
case V_stats :
		printf("      --- Dinkum --- \n");
		printf("Version: %s, %s\n\n", lb_version, lb_date);
		printf("i_rand1 = %d, i_rand2 = %d, i_rand3 = %d\n",
			i_rand1, i_rand2, i_rand3) ;
		printf("Room Number = %d\n", loc[0]) ;
		printf("Room object count = %d \n",
			room[loc[0]][M_obj_cnt]) ;
		printf("Room monster count = %d\n",
			room[loc[0]][M_monster]) ; 
		printf("Gleeps on room's floor count = %d\n",
			room[loc[0]][M_gleep]) ;
		printf("Poison level = %d\n",i_poison) ;
		printf("Gleep count = %d\n", gleep_count) ;
		printf("carry_count = %d, carry_weight = %d\n",
			carry_count, carry_weight) ;
		break ;

/* "SU" wizard initiation command */
case V_su:
	pass() ;
	break ;

/* "JSYS" wizard command which deactivates a monster */
case V_jsys:
	if (sw_wizard) monster_flag = F_no_monster ;
	else cheater() ;
	break ;

/* "score" command */
case V_score: 
	new_score() ;
	if ((Tank->Status == 0)&&(score == 0)) {
printf("You haven't scored anything at all, Bozo! Try putting\n");
printf("a valuable into the safe or find some gleeps.\n") ;
		break ;
	}
	if (score == 0) { 
		if (Tank->Status > 1) {
printf("You haven't scored any points but you splashed ") ;
printf ("%d gleeps into the gleep tank.\n",Tank->Status) ;
		}
		else {
printf("You haven't scored any points at all but you did put a\n");
printf ("gleep in the gleep tank (big deal!).\n") ;
		}
	}
	else {
printf ("You scored %d points ",score) ;
		if (Tank->Status == 0) 
printf ("but have yet to put any gleeps in the gleep tank.\n") ;
		else {
			if (Tank->Status > 1) 
printf ("and put %d gleeps into the gleep tank.\n",Tank->Status) ;
	
			else 
printf ("and put a gleep in the gleep tank.\n") ;
		}
	}
	break ;
 
/* "enter" command  */
case V_enter:
switch (loc[0]) {
 
	/* Lift entrance at the ground level */
	case R_lift_entr:
		if (room[R_lift_entr][2] == R_WALL) {
printf("I can't do it!  The lift door needs to be opened.\n") ;
			continue ;
		}
		move_dir = V_east ;
		break ;
	/* office door */
	case R_office_entr:
		if (room[R_office_entr][2] == R_WALL) {
printf("I can't go in!  The office door needs to be opened.\n") ;
			continue ;
		}
		move_dir = V_east ;
		break ;
	/* Lift entrance at level #49 */
	case R_L49_entr:
		move_dir = V_east ;
		break ;
	/* Entrance to Ned Kelly's hideout */
	case R_hideout_entr:
		move_dir = V_east ;
		break ;

	/* Enter gleep tank (and suicide) */
	case R_gleep_tank:
		if (tag[V_tank]) {
printf("\nYou climb up onto the edge of the gleep tank and dip your\n");
printf("foot into the dark blue fluid.  Suddenly the fluid begins a\n");
printf("furious boiling that instantly reduces your foot into\n") ;
printf("bleached white bones.  The shock and pain disturbs your\n");
printf("balance and you fall into the horrible stuff!!  There is\n");
printf("once again a furious boiling.  Eventually the fluid stills\n");
printf("and becomes clear again.  On the bottom of the tank can\n") ;
printf("be seen a white, clean, \"medical school quality\" human\n");
printf("skeleton.\n") ;
			ender(F_died) ;
		}
 
	default:
	printf("I don't understand exactly how to enter. \n");
		continue ;
} /* end of the "enter" switch block */
if (mover(move_dir, loc)) sw_loop = TRUE ;
break ;

/* "exit" command  */
case V_exit:
case V_leave:
case V_depart:
switch (loc[0]) {
 
	/* Lift entrance at the ground level */
	case R_lift_inside:
		move_dir = V_west ;
		break ;
	/* office door */
	case R_office_hall:
		move_dir = V_west ;
		break ;
	/* Ned Kelly's hideout */
	case R_hideout :
		move_dir = V_west ;
		break ;
	default:
printf("I don't understand exactly how you want to exit.\n");
		continue ;
} /* end of the "depart" switch block */
if (mover(move_dir, loc)) sw_loop = TRUE ;
break ;

/* "dig" command */
case V_dig:
printf("You get on your knees and scrape away at the ground for\n") ;
printf("awhile. Except for getting your hands dirty you didn't\n") ;
printf("achieve much.\n") ;
	break ;

/* "stand" command */
case V_stand:
printf("You're standing there very nicely.  However you're not\n");
printf("achieving much by doing so.\n") ;
	break ;

/* "load" rifle command */
case V_load:
	loader() ;
	break ;

/* "unload" rifle command */
case V_unload:
	unloader(loc[0]) ;
	break ;

/* "pull" command */
case V_pull:
	if (tag[V_trigger]) {
		/* alias in the "shoot" command */
		verb = V_shoot ;
		tag[V_VERB_ONLY] = TRUE ;
		killer(loc[0]) ;   /* "pull trigger" */
	}
	else  printf("I don't see how I could pull that.\n") ;
	break ;

/* "climb" command */
case V_climb:
printf("I'm not climbing anything!  (I'm afraid of heights.)\n") ;
	break ;

/* "swim" command */
case V_swim:
printf("I'm not going for a swim!  (I'm afraid of the water.)\n") ;
	break ;

/* Go backwards to previous location */
case V_back:
	loc[0] = loc[1] ;
	sw_loop = TRUE ;
	break ;
 
/* "take", "get", "lift" command */
case V_take:
case V_get:
case V_lift:
case V_pick:
case V_grab:
case V_remove:
case V_attach:
case V_hold:
	taker(loc[0]) ;
	break ;
 
/* "drop", "throw", "put" command */
case V_drop:
case V_throw:
case V_put:
case V_fling:
case V_toss:
case V_insert:
case V_give:
case V_eject:
case V_slow_drop:
	dropper(loc[0]) ;
	break ;

/* "look" command */
case V_look:
case V_view:
case V_examine:
case V_inspect:
case V_describe:
	looker(loc[0]) ;
	break;

/* gibberish command */
default:
printf("Huh?  You will have to make yourself clearer! \n");

} /* end of "decoder" switch */
if (sw_loop) break ;
} /* end of the inner infinite "for" loop */
} /* end of the outer infinite "for" loop */

} /* --- end of Main routine --- */

#if (PROTOTYPE)
void cmd_switch(char cmd[8], int cmd_arg, int i_point, char *argv[])
#else
void cmd_switch(cmd, cmd_arg, i_point, argv)
char cmd[8], *argv[] ;
int cmd_arg, i_point ;
#endif
/*****************************************************/
/*                                                   */
/*         --- Command line Switch Parser ---        */
/*                                                   */
/*  (c) Copyright 1992,   University of Queensland   */
/*        Program written by Gary A. Allen, Jr.      */
/*           Version:  Mk 1.1   24 February 1992     */
/*                                                   */
/*****************************************************/
{

#if (PROTOTYPE)
void bugs(int), pass(void) ;
#endif

switch (cmd[cmd_arg]) {
case '\0':
case -1:
	sw_null = TRUE ;
	return ;

/* Activate save script capability */
case 's':
case 'S':
	Gong->Status = S_recorder ;
	break ;

/* Version verification command switch */
case 'v':
	if ((cmd[cmd_arg+1] == 'e')&&(cmd[cmd_arg+2] == 'r')) {
		printf("Version: %s, Serial Number: %06d %s \n", 
			lb_version, serial, lb_share) ;
		bugs(Request) ;
	}
	else {
		printf("!!!! Command line switch -v is unknown.\n") ;
		bugs(Failed) ;
	}

/* Wizard mode command switch */
case 'w':
case 'W':
	pass() ;
	break ;

/* Standard matrix load command switch */
case 'x':
case 'X':
	sw_standard = TRUE ;
	break ;

/* Rubbish option to supress a warning */
case 'y':
case 'Y':
	sw_number = TRUE ;
	printf("y = %d\n", atoi(argv[i_point+1])) ;
	return ;

/* Help option */
case '?':
case 'h':
case 'H':
	sw_help = TRUE ;
	return ;

case ' ':
case '-':
case '1':
case '2':
case '3':
case '4':
case '5':
case '6':
case '7':
case '8':
case '9':
	return ;

default:
printf("!!!! Command line switch -%c is unknown.\n", cmd[cmd_arg]) ;
	bugs(Failed) ;
}
} /* --- end of the cmd_switch subroutine --- */

#if (PROTOTYPE)
void bugs(int i_type)
#else
void bugs(i_type)
int i_type ;
#endif
/***************************************************************/
/*                                                             */
/*       (c) Copyright 1992,   University of Queensland        */
/*            Program written by Gary A. Allen, Jr.            */
/*             Version:  Mk 1.0        24 April 1992           */
/*                                                             */
/***************************************************************/
{
switch(i_type) {
case Failed:
	printf("!!!! If confused, type:  dinkum -h \n");
	printf("!!!! --- Program ABORTED --- \n");
	break ;

case Request:
	printf("Program terminated by user request.\n") ;
	break ;

case Logic_error:
	printf("Please refer to program author's address by typing\n") ;
	printf("\"dinkum -h\" and inform the author of this error.\n") ;
	printf("             --- Program ABORTED ---\n") ;
	break ;
}
exit (0) ; 
} /* --- end of the "bugs" subroutine --- */

#if (PROTOTYPE)
void help(void) 
#else
void help() 
#endif
/*****************************************************/
/*                                                   */
/*                    Help Routine                   */
/*                                                   */
/*  (c) Copyright 1992,   University of Queensland   */
/*        Program written by Gary A. Allen, Jr.      */
/*           Version:  Mk 1.0    24 April 1992       */
/*                                                   */
/*****************************************************/
{
char chr ;

printf("                    --- Dinkum --- \n");
printf("       (c) Copyright 1993 by Gary A. Allen, Jr.\n") ;
printf("   All Rights Reserved. Version: %s, %s\n\n", 
		lb_version, lb_date);

printf("      Dinkum is a text style \"adventure\" game.\n\n") ;

printf("You are free to use, copy and distribute Dinkum provided:\n") ;
printf("       NO FEE IS CHARGED FOR USE, COPYING OR DISTRIBUTION.\n") ;
printf("       THIS PROGRAM IS FOR PRIVATE, NONCOMMERICAL USE ONLY.\n");
printf("       THE PROGRAM MAY NOT BE MODIFIED IN ANY WAY.\n\n") ;

printf("This program is provided AS IS without any warranty,\n") ;
printf("expressed or implied, including but not limited to fitness\n") ;
printf("for any particular purpose.\n\n") ;

/* keep the screen from scrolling */
#ifndef __TURBOC__
printf("         [Press RETURN or ENTER to continue]") ;
chr = getchar() ;
#endif

#ifdef __TURBOC__
printf("  [Press \"q\" to quit or any other key to continue]") ;
chr = getche() ;
printf("\r                                                        \r") ;
#endif

if ((chr == 'q')||(chr == 'Q')) exit (0) ;

printf("If you start the game by typing \"dinkum -s\" rather than \n");
printf("simply \"dinkum\" then the game creates a \"data recorder\" \n"); 
printf("which appears in the beginning  of  the game.  The data \n"); 
printf("recorder acts like a tape recorder allowing the user to \n"); 
printf("save moves and play them back in the current  or  later \n"); 
printf("games.  The generated file is in ASCII format  and  can \n"); 
printf("be  edited  after  finishing  Dinkum.    Type  \"examine \n"); 
printf("recorder\" after having taken it and Dinkum will explain \n"); 
printf("how to use it.  This data  recorder  has  a  couple  of \n"); 
printf("important  limitations:   Unlike  most adventure games, \n"); 
printf("Dinkum is  dynamic,  viz.  the  game changes every time \n"); 
printf("you play it.  So if you record  a  script  for  a  game \n"); 
printf("which takes you to a room where you find a  weapon  and \n"); 
printf("then to another room where you find a monster, then the \n"); 
printf("next time you use  that script you may find the monster \n"); 
printf("where you  previously  found  the  weapon (leading to a \n"); 
printf("fairly short game). The other limitation  of  the  data \n"); 
printf("recorder is if you use the \"dinkum -s\" switch then  you \n"); 
printf("will  not  be  admitted  into  the  end  game  with the \n"); 
printf("consequence being that  \"winning\" Dinkum is impossible. \n"); 
printf("To win Dinkum you must  play  it  \"on your own\" without \n"); 
printf("the unfair advantage of script files and data recorders.\n\n");

/* keep the screen from scrolling */
#ifndef __TURBOC__
printf("         [Press RETURN or ENTER to continue]") ;
chr = getchar() ;
#endif

#ifdef __TURBOC__
printf("  [Press \"q\" to quit or any other key to continue]") ;
chr = getche() ;
printf("\r                                                        \r") ;
#endif

if ((chr == 'q')||(chr == 'Q')) exit (0) ;

printf("When corresponding please state the current version of\n") ;
printf("Dinkum which you are using.  Contributions and questions\n") ;
printf("about this program should be sent to the following address:\n\n") ;
printf("          E-mail address:     gary@sun.mech.uq.oz.au\n\n") ;
printf("          Postal address:     Gary A. Allen, Jr. \n");
printf("                              P.O. Box 13\n") ;       
printf("                              St. Lucia, Queensland  4067\n");
printf("		 	 	            Australia\n") ;

exit(0);
} /* ---- end of the "help" subroutine ---- */

#if (PROTOTYPE)
void cheater(void) 
#else
void cheater() 
#endif
/*****************************************************/
/*                                                   */
/*  (c) Copyright 1992,   University of Queensland   */
/*        Program written by Gary A. Allen, Jr.      */
/*           Version:  Mk 1.0   9 December 1992      */
/*                                                   */
/*****************************************************/
{
printf("Rather than cheat at this game by using a disassembler, you\n");
printf("should send the author $150 and he'll gladly send you\n") ;
printf("the source code.  If you just want a clue, then send $20\n") ;
printf("with your question and he'll provide the answer.  You can find\n") ;
printf("the author's address by typing:  dinkum -h\n") ;
		exit(0) ;
} /* ---- end of the "cheater" subroutine ---- */

#if (PROTOTYPE)
int mover(int direction, int loc[3])
#else
int mover(direction,loc)
int direction, loc[3] ;
#endif
/*****************************************************/
/*                                                   */
/*  (c) Copyright 1992,   University of Queensland   */
/*        Program written by Gary A. Allen, Jr.      */
/*           Version:  Mk 1.0  17 December 1992      */
/*                                                   */
/*****************************************************/
{

#if (PROTOTYPE)
/* Function prototypes */
void long_descp(int), ender(int), boom(void) ;
#endif

/* see if this movement prohibits blasting caps */
if (((direction == V_u)||(direction == V_up)) &&
		((loc[0] == R_manhole_1)||(loc[0] == R_manhole_2))) {

	if (Cap->Location == B_have) {
printf("As you were climbing up through the hole in the ceiling,\n");
printf("the blasting cap slipped from your grasp and fell to the\n") ;
printf("floor below where it detonated on impact.  The explosion\n") ;
printf("was deafening, but caused no damage.\n") ;
		carry_count-- ;
		carry_weight -= Cap->Weight ;
		Cap->Location = B_destroyed; 
	}
	else {
		if ((Dynamite->Location == B_have)&&(Dynamite->Type == Z_alias)) {
			boom() ;

printf("As you were climbing up through the hole in the ceiling,\n");
printf("the dynamite with the blasting cap inside slipped from\n") ;
printf("your grasp and fell to the floor below where it detonated\n") ;
printf("on impact.  At that point you literally became a human\n");
printf("cannon ball as the shock wave carried you up the vertical\n");
printf("passage and splattered you into protoplasmic jelly on the\n");
printf("ceiling above.\n") ; 
			ender(F_died) ;
		}
	}
} /* end of the cap/manhole block */

direction-- ;
if (room[loc[0]][direction] == R_WALL) {
	printf("You can't go that way. \n");
	return(FALSE) ;
}

/* save previous location */
loc[1] = loc[0] ;
loc[0] = room[loc[0]][direction] ;

/* See if player walked into a lethal room */
if (room[loc[0]][M_rm_type] == T_lethal) {
	long_descp(loc[0]) ;
	ender(F_died) ;
}
return(TRUE) ;
} /* --- end of the "mover" function --- */

#if (PROTOTYPE)
int yes_no(void)
#else
int yes_no()
#endif
/*****************************************************/
/*                                                   */
/*  (c) Copyright 1993,   University of Queensland   */
/*        Program written by Gary A. Allen, Jr.      */
/*           Version:  Mk 1.0  27 January 1993       */
/*                                                   */
/*****************************************************/
{

char chr ;

#if (PROTOTYPE)
/* Function prototypes ANSI C */
char getch(void), getche(void) ;

#else
/* Function prototypes K&R-C */
char getch(), getche() ;
#endif

for (;;) {

#ifndef __TURBOC__
	do {
		printf("(Answer:  Yes or No) ") ; 
	} while ('\n' == (chr = getchar())) ;

	while ('\n' != getchar()) ;
#endif

#ifdef __TURBOC__
	printf("\n") ;
	do {
		printf("(Answer:  Yes or No) ") ; 
	} while ('\n' == (chr = getch())) ;
	printf("\n") ;
#endif

	if (('n' == chr)||('N' == chr)||('y' == chr)||('Y' == chr)) break ;
} /* end of the infinite "for" loop */

if (('y' == chr)||('Y' == chr)) return(TRUE) ;
else return(FALSE) ;

} /* --- end of the "yes_no" function --- */
