#define DSCRB
#include "dink_sym.h"
#include "dink_glb.h"
 
#if (PROTOTYPE)
void describe(int n)         
#else
void describe(n)
int n ;         
#endif
/*********************************************************/
/*                                                       */
/*           --- Room Description and Path ---           */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  6 June 1989       */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{

static int old_n, dark_count, sw_hint = FALSE ;
char chr ;

/* room description */
static char *descript[] = {
"are in a grassy meadow that stretches out in all directions",  /* 0 */
"are on a path next to the meadow.  To the east is a road.",    /* 1 */
"are approaching a thickly wooded forest full of gum trees.",   /* 2 */
"have hiked a short distance and then climbed up onto a river dike.",
"are next to a wide murky river that looks dangerous.",         /* 4 */
"--- marker for drowing in river",                              /* 5 */
"are next to a billabong with a stream feeding into it.",       /* 6 */
"feel something slimey under the water wraping itself around your leg.",
"--- marker for the bunyip",                                    /* 8 */
"are back on top of the dike next to a great meandering river.", 
"are waist deep in the stream, the water is cool and refreshing.",
"are in a thickly wooded forest. There is a rich eucalyptus smell",
"are deeper into the gum tree forest and getting disoriented.",
"are deep in a gum tree forest and appear to be ***lost***.",   /* 13 */
"are wading in the billabong.  The water is stagnant and smelly.",
"approach an area with high grass. You can only see in a few metres.",
"are deep in the grass, which is waist high.",                  /* 16 */
"see snakes slither by in the grass.  Some are quite big.",     /* 17 */
"--- marker for the Taipan",                                    /* 18 */
"leave the grassy area and head towards the meadow.",           /* 19 */
"are on a road.  Far to the east are some deserted buildings.", /* 20 */
"are on a narrow one lane road stretching out to the horizon.", /* 21 */
"are west from the head gear of the abandoned ACME Gold Mine.", /* 22 */
"are in an orange desert with bulldust swirling about you.",    /* 23 */
"are in a desert full of high sand dunes.",                     /* 24 */
"are in between two sand dunes and can see only sand.",         /* 25 */
"are in a sandy desert with large thorny spinifexes rolling by you.",
"are west of the mine shaft lift.  The mine tower looms over head.",
"are walking away from a forest of sweet smelling gum trees. ", /* 28 */
"find yourself on a narrow potholed bitumen road with soft shoulders.",
"are southwest of the mine lift.  To the south is desert.",     /* 30 */
"are southeast of the mine lift.  To the south is desert.",     /* 31 */
"are east of the mine tower between the lift and the office.",  /* 32 */
"are east of the mine office building.  There is no door here.",
"are at the north eastern corner of the office building.",      /* 34 */
"are at the north western corner of the office building.",      /* 35 */
"are west of the ACME Gold Mine office building entrance.",     /* 36 */
"are in the entry hall.  There are doors to the north, south and west.",
"are in the Site Manager's office.  The only exit is to the south.",
"are in the western section of the Geologist's Office.",        /* 39 */
"are in the store room. The only exit is to the south.",	/* 40 */
"are in the eastern section of the Geologist's Office.",        /* 41 */
"continue walking on the narrow road which has only one lane.", /* 42 */
"are inside the mine lift.  The doorway is to the west.",
"are in a dimly lit tunnel going west.  To the east is the lift.",
"are in a poorly lit tunnel going east, west and south.",       /* 45 */
"are in a dimly lit tunnel going north.  To the east is the lift.",
"are in a pasture.  To the east is a road and west is a billabong.",
"are in a T-section going north, south or east.",               /* 48 */
"are in a T-section going north, south or west.",               /* 49 */
"are in a T-section going north, west or east.",                /* 50 */
"are in a T-section going east, west or south.",                /* 51 */
"are in a T-section going northeast, northwest, or southwest.", /* 52 */
"are in a T-section going northeast, northwest, or southeast.", /* 53 */
"are in a T-section going northeast, southeast, or southwest.",
"are in a tunnel going north and south.",                       /* 55 */
"are in a tunnel going east and west.",                         /* 56 */
"are in a tunnel going northwest and southeast.",               /* 57 */
"are in a tunnel going northeast and southwest.",               /* 58 */
"are in a tunnel that has a hole in the ground and goes east/west.",
"are in an L-section going southeast or up through a hole in the roof.",
"are in an L-section that goes south or up through a hole in the roof.",
"are in an L-section that goes east or up through a hole in the roof.",
"are in an L-section that goes west or up through a hole in the roof.",
"are in a Y-section that goes north, southeast, or southwest.", /* 64 */
"are in a Y-section that goes south, northeast, or northwest.", /* 65 */
"are in a Y-section that goes west, northeast, or southeast.",  /* 66 */
"are in a Y-section that goes east, northwest, or southwest.",  /* 67 */
"are in a Y-section that goes north, south, or southwest.",     /* 68 */
"are in a Y-section that goes south, north, or northwest.",     /* 69 */
"are in a Y-section that goes west, east, or southeast.",       /* 70 */
"are in a Y-section that goes east, west, or southwest.",       /* 71 */
"are in a Y-section that goes north, south, or southeast.",     /* 72 */
"are in a Y-section that goes south, north, or northeast.",     /* 73 */
"are in a Y-section that goes west, east, or northeast.",       /* 74 */
"are in a Y-section that goes east, west, or northwest.",       /* 75 */
"are in a Y-section that goes down a manhole, northwest, or southwest.",
"are in a Y-section that goes down a manhole, northeast, or southeast.",
"are at a tunnel crossing.  You can go north, east, south, or west.",
"are at a tunnel crossing going nw, ne, sw, and se.",           /* 79 */
"are in a tunnel corner that goes south and west.",             /* 80 */
"are in a tunnel corner that goes south and east.",             /* 81 */
"are in a tunnel corner that goes north and west.",             /* 82 */
"are in a tunnel corner that goes north and east.",             /* 83 */
"are in a tunnel corner that goes southeast and southwest.",    /* 84 */
"are in a tunnel corner that goes southeast and northeast.",    /* 85 */
"are in a tunnel corner that goes northwest and southwest.",    /* 86 */
"are in a tunnel corner that goes northwest and northeast.",    /* 87 */
"are in a tunnel going southwest with a stairway going down.",  /* 88 */
"are in a tunnel going northeast with a stairway going up.",    /* 89 */
"are at a deadend.",                                            /* 90 */
"are in the ventilation equipment room. The exit is to the west.",
"are in the worker's lunch room. The exit is to the north.",
"are at the stope face with the hydraulic jacks still in place.",
"are in an ore storage area with exits to the south and west.",
"are in a T-section going northwest, southeast, or southwest.",
"are in a tunnel going northeast/southwest, with a hole in the roof.",
"are in a corner going north and east, with a manhole going down.",
"are in a tunnel going west with a stairway going up.",         /* 98 */
"are in a tunnel going east with a stairway going down.",       /* 99 */
"can go north or climb down a man hole.",                       /*100 */
"are at a caved in section of tunnel which is now a dead end.", /*101 */
"are in a bleak and forbidding desert of bare flat stone.",     /*102 */
"are on a narrow one lane road with gum trees on either side.", /*103 */
"are in a flat and boring desert.",				/*104 */
"are in front of Ned Kelly's desert hide out.",			/*105 */
"are in a vast desert of dry salt lakes shimmering with mirages.",
"are inside Ned Kelly's hide out.  The only way out is to the west.",
"are north of a grassy area and within the bend of a great river.", 
"are south of a grassy area and on the edge of a gum tree forest.",
"can go east or climb down a man hole.",			/*110 */
"can go east, west or climb up through a hole in the roof.",	/*111 */
"are at the Level #67 Shift Foreman's office. You can go west.",
"are at the spacecraft's end.  You can go north, south and west.",
"are near the spacecraft's fin. You can go south or north-east.",
"are next to the ship's wing.  You can go south-west or south-east.",
"are beside the ship's window.  You can go north-west or south.",
"are next to the spacecraft's Mach probe.  You can north or south.",
"are facing the access hatch.  You can go up, north, or south-west.",
"are beside the landing gear.  You can go north-east or north-west.",
"are beside the wing's edge.  You can go north or south-east.",
"are in the spacecraft's airlock.  You can go down or north.",
"are in the central access way.  You can east, west, or south.",
"are on the flight deck of an ancient spacecraft.  You can go west.",
"are at a mysterious control panel.  You can east or west.",	/* 124 */
"are in the chamber with glowing hexagons. The only exit is east.",
"are in a room with a tank full of dark blue liquid.  You can go west.",
"are in a cavernous room with a huge silver gong in the middle.",
"are in a room with a warning on the wall going north, south and west.",
"are in a closet stinking of moth balls. The only exit is north.",
"are in the guard room. The closet is south, the main doorway is east.",
"are in the prayer room of the Iranian Parliament. The guard room is west.",
"are in a tunnel going east and west with a message on the wall.",
"are on a narrow country road.  There is a dead kangaroo by the road.",
"are on a road with a low rise ahead of you.  You hear a distant rumbling.",
"--- marker for getting hit by a road train.",                  /* 135 */
"are on a narrow country road.  There is a dead red kangaroo by the road."
}  ;

#if (PROTOTYPE)
void ender(int) ;
char getch(void) ;
#endif

/* give the short description */
if (((Torch->Location == B_have) && Torch->Status) || 
	(n < 186)||(n > 202)) { 
/* Deal with the possibility of a hint for the safe */
	if (n == R_office_mang) {
		if ((!sw_active)&&(Rifle->Status != 0)&&
(Ned->Location == B_destroyed)&&(!sw_hint)) {
			sw_hint = TRUE ;
printf("For half of the bullets in your M-16 rifle I will\n") ;
printf("give you a hint on how to get into the safe.\n") ;
printf("             Are you interested? \n") ;

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

				if (('n' == chr)||
('N' == chr)||('y' == chr)||('Y' == chr)) {
					if (('y' == chr)||
						('Y' == chr)) { 
				Rifle->Status /= 2 ;
printf("\nTake the missing word in the sentence:\n") ;
printf("                      \"The chook **** an egg.\"\n");
printf("and spell it backwards.  Then look very carefully at the\n") ;
printf("map which you found in the manager's office.  Also, you\n") ;
printf("now have %d bullets in your rifle.\n",
				Rifle->Status) ;
					}
				break ;
				}
			}
			printf("\n") ;
		}
	}
printf ("You %s \n",descript[room[n][M_descp]]);
	old_n = n;
	dark_count = 0 ;

}

/* deal with dark rooms */
else {
	if (n == 186) {
printf("You have entered a north/south passage which does not have\n") ;
printf("electric lighting.  There is some light coming in from the\n");
printf("north, but the tunnel to the south is completely dark.\n");
		return;
	}
	if (n == 187) {
printf("The tunnel you are in is pitch black.  There is a little\n");
printf("light coming in from the north.  If you keep going you will\n");
printf("probably fall down a hole.\n") ;
		return ;
	}
	if ((n >= 188)&&(n <= 202)) {
		if ((dark_count==0)||(old_n == n)) {
printf("You are in a mine tunnel in total darkness, which is \n") ;
printf("extremely dangerous.  I have no clue where we are going.\n") ;
printf("Let's go back to where there is some light!\n") ;
			++dark_count ;
			old_n = n;
		}
		else {
printf("Twit!!  You have fallen down a hole and broken your neck!\n");
		ender(F_died) ;
		}
		return ;
	}
}
} /* end of the "describe" subroutine */
 
#if (PROTOTYPE)
void rdtxt(int k)
#else
void rdtxt(k)
int k;
#endif
/*********************************************************/
/*                                                       */
/*     --- Text for the "Read"/"Describe" Command ---    */
/*                                                       */
/*       Program by Gary A. Allen, Jr.  21 February 1989 */
/*         (c) Copyright 1992 by Gary A. Allen, Jr.      */
/*                                                       */
/*********************************************************/
{
#if (PROTOTYPE)
void hold_it(void) ;
#else
void hold_it() ;
#endif

switch(k) {

/* text for the map fragment in the manager's office */
case V_map_frag:
printf("______________________________________________________ \n");
printf("|..................................................... \n");
printf("|...._______________________.......................... \n");
printf("|...|  Current Operational  |........................ \n");
printf("|...|  Levels are:          |......D--W--W--W--W--W- \n");
printf("|...|     0, 49, 67, 82     |......|................ \n");
printf("|...| Level #67 is depicted |......S................ \n");
printf("|...._______________________.......|................ \n");
printf("|..................................S............... \n");
printf("|..................................|............... \n");
printf("|......................S--W--W--D--W.............. \n");
printf("|......................|........|................. \n");
printf("|......................S........E--E--E--E--E--E- \n");
printf("|......................|.......................... \n");
printf("|.......[dead end]--W--*--E--[dead end].......... \n");
printf("|......................|........................ \n");
printf("|......................S......................");
printf("       The rest of the map\n");
printf("|......................|.....................");
printf("        has turned into dust.\n");
printf("|.........[false dead end (partition)]......\n");
printf("|...........^..........|................. \n");
printf("|.{use an explosive}...S.............. \n");
printf("|......................|.... \n");
printf("|.............. \n");
	break;

/* Can of Fourex Beer */
case V_can:
printf("You see an aluminum beer can with a hole in the bottom. The\n");
printf("can is coloured yellow-orange.  Written in red letters\n");
printf("across the can's front is the following:\n\n") ;
printf("                  \"CASTLEMAINE\"\n") ;
printf("                      XXXX\n") ;
printf("                   BITTER ALE\n\n") ;
printf("There's a picture of Fourex's Milton brewery in the middle.\n");
	break ;

/* Atropine pills */
case V_pills:
printf("You're holding a packet which once contained ") ;
printf("30 pills but now\nholds only") ;
printf(" %d pills.  On the back of the packet is written:\n\n",
	pill_count) ;
printf("                       ATROPINE PILLS\n");
printf("The pills in this packet will protect the user against ") ;
printf("poisoning\nby organo-phosphorous ") ;
printf("compounds, i.e. VX nerve gas.\n") ;
printf("    Dosage:  Take ONE pill when poisoning symptons occur.\n");
printf("    Warning:  Atropine is itself a poison.  An overdose can\n");
printf("              be lethal!\n\n") ;
	break ;


/* description of Qaddafi's letter bomb */
case V_letter:
printf("___________________________________________________________\n");
printf("|                                               +-----+   |\n");
printf("| Col. M. Gaddafi                               |Libya|   |\n");
printf("| Azizya Barracks                Postage Due    |5 zl.|   |\n");
printf("| Tripoli, Libya                   $1.50        | -o- |   |\n");
printf("|                                               +-----+   |\n");
printf("|                 Sam Cohen                               |\n");
printf("|                 Level #67 Shift Boss                    |\n");
printf("|                 ACME Mine Ltd.                          |\n");
printf("|                 Birdsville, Queensland 4482             |\n");
printf("|  AIR MAIL                   Australia                   |\n");
printf("|                                                         |\n");
printf("___________________________________________________________\n");
printf("\n\nThe envelope must be opened before the ");
printf("letter can be read.\n\n") ;
	break;

/* text for the paper found in the safe */
case V_paper:
printf("                             Congratulations!!! \n");
printf("You got the safe open!  Now you can start scoring points for ");
printf("treasure.\n") ;
printf("Credit is awarded **only** for treasure put into the safe. ");
printf("Beware of fell\nbush ") ;
printf("rangers who steal treasure (and sometimes kill adventurers).") ;
printf("\n\n                        ---  Concerning Gleeps ---\n");
printf("Gleeps are potent adjuncts which are credited separately from");
printf(" treasure.  Gleeps\n") ;
printf("will reproduce if left undisturbed in special locations ") ;
printf("underground. However\n") ;
printf("in most locations they will remain dormant. Credit ");
printf("for gleeps is awarded \n") ;
printf("only for those placed in a \"gleep tank\". While anyone ");
printf("can gather treasure, the\n") ;
printf("ability to cultivate and collect gleeps is the mark of a ");
printf("fair dinkum master.\n") ;
printf("                               Have Fun !!\n");
	break;

/* description of the rifle */
case V_rifle:
printf("--- You are looking at a Colt M16 infantry rifle. --- \n");
printf("This fully automatic weapon is supplied bullets from a \n") ;
printf("detachable magazine which can hold up to 200 rounds. \n") ;
printf("The rifle has a selector knob that can place the weapon \n") ;
printf("into one of four possible firing modes: \n\n") ;
printf("     SAFE = Rifle can't fire, even if dropped \n") ;
printf("     I    = Single fire mode. Shoots one bullet at a time \n");
printf("     III  = Triple fire mode. Shoots three bullets rapidly \n");
printf("            every time the trigger is pulled. \n") ;
printf("     AUTO = Fully automatic, firing bullets at a rate of \n") ;
printf("            660 rounds/min. when trigger is pulled. \n\n") ;
if (rifle_flag == F_safety)
printf("The rifle is currently set in the SAFE mode. \n") ;
if (rifle_flag == F_single)
printf
  ("The rifle is currently set in the \"I\" or single fire mode.\n");
if (rifle_flag == F_triple)
printf("The rifle is now set in the \"III\" or triple fire mode.\n");
if (rifle_flag == F_auto)
printf("The rifle is currently set in the AUTO mode. \n") ;
if (clip_flag == F_no_clip)
printf("The rifle does not have an ammunition clip attached to it.\n") ;
if (clip_flag == F_normal_clip) {
	printf("The rifle has a standard ammunition clip attached ") ;
	printf("which contains %d rounds.\n",
				Rifle->Status) ;
}
if (clip_flag == F_org_clip) {
	printf("The rifle has an orange ammunition clip attached ") ;
	printf("which contains %d rounds.\n",
				Rifle->Status) ;
}
	break ;
 
/* description of the safe */
case V_safe:
	if (Picture->Status >= S_open) {
printf("You see a conventional combination dial type wall safe \n");
printf("fixed immovably into the wall.  The dial is black with \n");
printf("white numbers written onto it.  The numbers range from \n");
printf("one to one hundred. Attached to the upper right hand \n");
printf("corner of the safe is a manufacturer's label which reads:\n\n");
printf("                     _____________________________  \n") ;
printf("                    |     Kryptonite Safe Co.     | \n") ;
printf("                    |  Model Number:  C-3283      | \n") ; 
printf("                    |  Serial Number: 10149167182 | \n") ;
printf("                    |      Made in Australia      | \n") ;
printf("                     _____________________________  \n") ;
	}
	else printf("I don't see a safe here for me to describe.\n");
	break ;
 
/* Message on wall from Indiana Jones */
case V_wall:
case V_message:
printf("You've read this message before.  It says:\n\n") ;
printf("Dear Treasure Hunter:\n") ;
printf("There was lots of treasure on this level when I first\n") ;
printf("discovered this mine.  However I have since carted it all\n") ;
printf("away.  You might try looking on another level.") ;
printf("\n\n                            Good Luck!\n") ;
printf("                         Dr. I. Jones, Ph.D.\n\n") ;
	return ;
 
/* description of the save script recorder */
case V_recorder:
printf("  --- You are holding a Fair Dinkum data recorder. ---\n") ;
printf("This device is a metal box with four coloured buttons.  The\n") ;
printf("buttons have the following functions:\n\n") ;
printf("Green Button:\n") ;
printf("When the green button is pressed the recorder will query the user\n") ;
printf("for a data file name.  Once the name has been provided, every\n") ;
printf("move made after will be recorded in the named file.  The recording\n") ;
printf("session will end when the red button is pressed.\n\n") ;
printf("White Button:\n") ;
printf("When the white button is pressed the recorder will query the user\n") ;
printf("for a data file name.  Once the name for an existing data file has\n") ;
printf("been provided, then all the moves listed in that file will be\n") ;
printf("played back with the player acting accordingly.\n\n") ;
printf("Red Button:\n") ;
printf("When the red button is pressed a recording or play back session\n") ;
printf("is ended.  Otherwise nothing happens.\n\n") ;
	hold_it() ;
printf("Orange Button:\n") ;
printf("When the orange button is pressed then play is suspended and\n") ;
printf("Dinkum's clock stopped.  You are then asked if you want to\n") ;
printf("start the clock running again.\n\n") ;
printf("                          -------------\n\n") ;
printf("Warning:  Things Change!  A recorder file which worked for one\n") ;
printf("situation could become lethal for another.\n") ;
	break ;
 
/* Strike warning */
case V_warning:
printf("+---------------------------------------------------------+\n");
printf("|                                                         |\n");
printf("|              ACME MINE IS UNFAIR TO WORKERS!!           |\n");
printf("|                                                         |\n");
printf("|                       ON STRIKE!!                       |\n");
printf("|                                                         |\n");
printf("| The Loyal Brotherhood of Australian Miners and Under-   |\n");
printf("| ground Workers is on strike against Acme Mines Ltd. due |\n");
printf("| to unfair treatment of its workers.  Our Union demands  |\n");
printf("| the following:  Worker's wages be increased by 30%%, the |");
printf("\n") ;
printf("| week shall have only 4 working days, the working day    |\n");
printf("| shall be reduced to 5 hours, triple wages for overtime  |\n");
printf("| work and immunity from sacking for all Union members.   |\n");
printf("| To discourage scabs and other strike breakers from      |\n");
printf("| working during the strike, we have planted booby traps  |\n");
printf("| through out the tunnels on this level.  We do hope you  |\n");
printf("| don't mind the mine being mined so it won't be mined.   |\n");
printf("+---------------------------------------------------------+\n");
	break ;
 
/* description of the Semtex detector*/
case V_detector:
printf("You see an olive green box with a yellow button in its\n");
printf("centre, a yellow light in its upper right hand corner and\n");
printf("Cryllic writing all over it.  Below the Cryllic letters\n") ;
printf("is a translation in English which reads:\n\n") ;
printf("              Mk 5.12 Semtex Explosive Detector\n") ;
printf("This device is used in detecting explosive weapons such as\n");
printf("antipersonal mines which utilize the high velocity plastic\n") ;
printf("explosive Semtex.  To operate this device merely press the\n") ;
printf("yellow button and an air sample will be taken. If trace\n");
printf("amounts of Semtex are detected then a warning beeper will\n");
printf("be activated.   If there is no detectable Semtex then a\n") ;
printf("yellow light will flash.\n\n") ;
printf("               Made in the Czeckoslovak Socialist Republic\n") ;
	break ;
 
/* description of the black cube with the blue button */
case V_cube:
printf("You're holding a cube made of dull black metal which is about\n") ;
printf("6 cm across each face.  There is a strange alien writing much\n") ;
printf("like Sanskrit stamped into the metal.  On one cube face is a\n") ;
printf("large iridescent blue push button projecting out from the surface.\n") ;
break ;
 
/* description of the normal ammunition clip */
case V_clip:
printf("You see a conventional M16 ammunition clip.  It is olive "); 
printf(" green\n") ;
printf("in colour and about 30 centimetres long.\n"); 

if (Clip->Status == 0)
	printf("\nThe clip is EMPTY with NO bullets.\n") ;
else {
if (Clip->Status == 1)
	printf("\nThe clip contains one bullet.\n") ;
else
printf("\nThe clip contains %d bullets.\n", Clip->Status) ;
}
break ;

/* description of the gong */
case V_gong:
printf("You see an enormous silver gong weighing at least a ton.  The\n") ;
printf("huge gong is suspended from a finely polished red cedar frame,\n") ;
printf("the top of which is about four metres above the floor.\n") ;
break ;
 
/* description of the orange clip */
case V_org_clip:
printf("You see an M16 ammunition clip which has been painted bright");
printf(" orange.\n") ;
printf("A strange blue glow seems to be radiating from the clip. ");
printf("There is\n") ;
printf("a placard attached to the side of the clip which reads:\n\n") ;
printf("     ____________________________________________________ \n");
printf("    |    Hypertoxic 0.223 Caliber Ammunition Magazine    |\n");
printf("    |                                                    |\n");
printf("    | The ammunition contained in this magazine is       |\n");
printf("    | manufactured from spent nuclear fuel rods composed |\n");
printf("    | of uranium and plutonium metal.  The bullets have  |\n");
printf("    | been hollowed out and filled with mercury metal.   |\n");
printf("    | The exterior of each bullet has been striated and  |\n");
printf("    | impregnated with VX nerve gas and anthrax bacillus.|\n");
printf("    | The use of this ammunition violates the Geneva     |\n");
printf("    | Convention on the Rules of War, the International  |\n");
printf("    | Moratorium on Biological Weapons, and the United   |\n");
printf("    | Nations Charter.  Close proximity to this          |\n");
printf("    | ammunition can be harmful to your health.          |\n");
printf("    |                                                    |\n");
printf("    |    Developed under DOE Contract: LLNL 89-5632/Z    |\n");
printf("    |                  Patent Pending                    |\n");
printf("     ____________________________________________________ \n");

if (Org_clip->Status == 0)
	printf("\nThe orange clip is EMPTY with NO bullets.\n") ;
else {
if (Org_clip->Status == 1)
	printf("\nThe orange clip contains one bullet.\n") ;
else printf("\nThe orange clip contains %d bullets.\n",
	Org_clip->Status) ;
}
	break ;
} /* end of the "switch" block */
} /* --- end of "rdtxt" subroutine --- */
