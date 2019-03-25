#define LONG_DESCP
#include "dink_sym.h"
#include "dink_glb.h"

#if (PROTOTYPE)
void long_descp(int n)
#else
void long_descp(n)
int n ;
#endif
/*********************************************************************/
/*                                                                   */
/*               --- Long Description Subroutine ---                 */
/*                                                                   */
/* Software by Gary A. Allen, Jr. 23 December 1992  Version: Mk 2.0  */
/*            (c) Copyright 1992 by Gary A. Allen, Jr.               */
/*                                                                   */
/*********************************************************************/
{
static int sw_bend = TRUE, sw_mob = TRUE ;

#if (PROTOTYPE)
void boom(void), describe(int), ender(int) ;
#endif

if (((Torch->Location == B_have) && Torch->Status)|| 
	(n < 186)||(n > 202)) { 

/* See if player entered the killing passage in the end game */
if ((n >= 218)&&(n <= 227)) {
printf("As you're walking down the passage you feel the slight\n") ;
printf("tug of a trip wire on your leg.  Out the corner of your\n");
printf("eye you see the trip wire is connected to an olive green\n") ;
printf("cylinder attached to the wall of the tunnel....\n\n") ;
boom() ;
printf("\nIn case you're wondering that was a booby trap which you\n") ;
printf("set off!\n") ;
ender(F_died) ;
}

/* Select individual rooms */
switch (n) {
case R_river:      /* drowing in the river description */
printf ("As you approach the edge of the dike, there is a small\n");
printf ("earth slide which pitches you into the river.  You\n");
printf ("flounder around in the water for a short while.  Luckily\n");
printf ("before you have the chance to drown, a crocodile pulls\n") ;
printf ("you under, bringing you to a rather quick though painful\n");
printf ("end. \n") ;
return ;

case R_bunyip:      /* getting eaten by the bunyip */
printf ("The slimey tentacle suddenly tightens around your leg, and\n");
printf ("the water in the billabong starts to churn furiously. Then\n");
printf ("surfaces the one thing that all Australians fear the most...");
printf ("\n\nBefore you stands an enormous sickly green Queensland\n") ;
printf ("Bunyip in all its awesome horror. It does not make a quick\n");
printf ("end of you....  Such is not the way of Bunyips.  First it \n");
printf ("peels off your skin as if you were a banana.  After much\n");
printf ("fearful agony, comes release as you pass into death.\n");
return ;

case R_road_kill_n:  /* getting run over by a road train */
case R_road_kill_s: 
printf("The distant rumble becomes a loud roar.  Suddenly a huge Mack\n") ;
printf("truck pulling three carriages packed with cattle leaps over the\n") ;
printf("low rise, filling the narrow country road.  You stand terrified\n") ;
printf("in the middle of the road with the metal monster bearing down\n") ;
printf("at 120 km/hr.  The last thing you see before being flattened\n") ;
printf("like a cockroach is a sign on the truck's roo bar saying:\n") ;
printf("                 \"CAUTION:  ROAD TRAIN\"\n\n") ;
return ;

case R_forest:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are in a forest thickly wooded with gum trees.  The forest\n") ;
printf("floor is covered with long thin leaves from gum trees mixed\n") ;
printf("with their seed pods.  There is a strong eucalytus smell in the\n") ;
printf("air.  Up in the forest canopy you can hear kookaburras engaged\n") ;
printf("in their raucous cackling.\n") ;
return ;

case R_bend:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are north of the grassy area in the bend of a great meandering\n") ;
printf("river.  All around you are the tall black fronds of grass trees.\n") ;
if (sw_bend) {
	sw_bend = FALSE ;
printf("Off in the distance you can see a mob of emus striding out of\n") ;
printf("sight.\n") ;
}
return ;

case R_bitumen:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are on a narrow country road made out of potholed bitumen.\n") ;
printf("The road's shoulders are of soft red earth which could cause\n") ;
printf("a driver to lose control of his car if he took a wheel off the\n") ;
printf("bitumen.  ") ;
if (sw_mob) {
	sw_mob = FALSE ;
printf("A few metres away is a mob of grey kangroos grazing\n") ;
printf("on grass by the road.  A huge buck looks up at you and doesn't\n") ;
printf("like what he sees.  He bounds off with the rest of the mob\n") ;
printf("following.  You can see the heads of joeys protruding from\n") ;
printf("their mother's pouches as the mob leaps off into the bush and\n") ;
printf("out of sight.\n") ;
}
else printf("\n") ;
return ;

case R_stream:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You approach a billabong with a small stream flowing into it.\n") ;
printf("Cane toads can be heard croaking nearby and you see countless\n") ;
printf("numbers of their tadpoles swimming in the stream.\n") ;
return ;

case R_taipan:      /* getting bitten by a taipan */
printf("As you wander aimlessly in the grass, you accidently step\n");
printf("upon a taipan which is perhaps the most poisonous of Oz's \n");
printf("snakes. The snake strikes upwards and bites you in the\n");
printf("worst possible place.  You thrash around for a short while\n");
printf("and then the venom takes hold. Your body begins to decompose");
printf("\nbefore your very eyes.  Death comes only after an hour \n");
printf("of the worst possible agony.  \n");
return ;

case R_mine_head:  /* Front of ACME Mine */
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf ("East of you is a large iron open truss tower, topped with \n");
printf ("two rusting wheels holding a pair of thick steel cables.  \n");
printf ("This is the head gear of the once highly successful ACME \n"); 
printf ("Gold Mine, which now is completely mined out.  Where \n");
printf ("there were once rich veins of gold is now a honeycomb of \n");
printf ("tunnels and caverns.  There are stories about strange \n");
printf ("events in the old tunnels of the ACME mine and only fools \n");
printf ("or reckless adventurers would dare explore them. \n");
printf ("To the north is the old office building.  Rumor has it \n");
printf ("the safe in this building once had millions of dollars in \n");
printf ("gold processed from the rich ore of the ACME mine.  To \n");
printf ("the south is the mine lift, which once transported up to \n");
printf ("twenty miners at a time down the long mine shaft to the \n");
printf ("working tunnels deep under the earth below.\n");
return ;

case R_office_mang:  /* Manager's office */
room[n][M_rm_type] = T_short_descp ;   /* disable long description  */
printf("You are in the Manager's office of the ACME Mine.  In \n");
printf("former times this room saw many lively meetings between \n"); 
printf("the Site Manager and Shift Bosses.  Fixed to the wall are\n");
printf("old production schedules and organizational charts. In\n");
printf("the middle of the room is a beautiful silky oak desk.\n");
printf("Unfortunately it is too heavy to move.  Attached to\n"); 
printf("the far wall is a curious picture of a platypus wearing a \n");
printf("hat with old wine corks dangling from the hat's brim. The\n");
printf("only exit is to the south.\n\n") ;
return ;

case R_geo_w:  /* Geologist's office */
room[n][M_rm_type] = T_short_descp ;   /* disable long description  */
printf("As you entered this room, huge cockroaches scuttled off ");
printf("in every \n"); 
printf("direction. On the far wall is a rather tasteless poster ");
printf("depicting \n");
printf("an extremely well endowed (unclad) young woman holding a ");
printf("mining \n"); 
printf("drill.  This office was once occupied by the mine ");
printf("geologist.  One \n");
printf("can still see traces of the office's former occupant.  ");
printf("There are only \n");
printf("two doors to this room.  Both go to the north. You entered ");
printf("through \n");
printf("the west door.  However there is another door in ");
printf("the eastern section \nof the office. \n");
return ;
 
/* lift compartment */
case R_lift_inside:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are inside the lift, which has only one ");   
printf("entrance doorway to the west. \n");
printf("To the left of the door is a panel of buttons.  Most of "); 
printf("the buttons are \ninoperative with tape over them.  However ");
printf("there are four buttons \nthat still work. Each of the four ");
printf("buttons have a number stamped on them.  \nThe numbers are ");
printf("zero, forty-nine, sixty-seven, and eighty-two. \n \n");
return ;
 
case R_hideout_entr:  /* Ned Kelly's Hide Out */
room[n][M_rm_type] = T_was_long;   /* long description only on request  */

if (monster_flag == F_no_monster) {
printf ("Before you is a Queensland house with large verandas. ") ;
printf ("The front of\nthe house is to the east. The house ") ;
printf ("is painted fluorescent orange.\nOn the roof of the house is ");
printf ("a large, bright flashing neon sign which reads: \n\n");
printf("___________________________________________________________\n");
printf("|                                                         |\n");
printf("|            Ned Kelly's ---SECRET--- Hide Out            |\n");
printf("| Policemen, troopers, law enforcement officers and all   |\n");
printf("| other minions of the law and public decency are advised |\n");
printf("| to look else where for bush rangers, thieves, and other |\n");
printf("| larrikins, since ***only*** honest, law abiding         |\n");
printf("| Australians (loyal to Queen and Country) live here.     |\n");
printf("|                                                         |\n");
printf("___________________________________________________________\n");
}
else describe(n) ;
return ;

case R_foreman:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You have entered the office of the Level #67 Foreman. In ");
printf("the middle of the\nroom is the Foreman's large and immovable ");
printf("desk.  To one side can be seen an\nempty file cabinet and ");
printf("a series of pidgeon holes for holding mine worker's\nmail. ");
printf("The only exit is to the west.\n\n") ;
return ;

case R_no_treasure:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are in a tunnel going east and west. Crude letters have\n");
printf("been scratched into the wall of the tunnel.  The following\n") ;
printf("was written:\n\n") ;
printf("Dear Treasure Hunter:\n") ;
printf("There was lots of treasure on this level when I first\n") ;
printf("discovered this mine.  However I have since carted it all\n") ;
printf("away.  You might try looking on another level.") ;
printf("\n\n                            Good Luck!\n") ;
printf("                         Dr. I. Jones, Ph.D.\n\n") ;
return ;

case R_gleep_tank:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You have walked into a room with a large plastic tank set "); 
printf("in the middle.\nThe tank is about two metres deep and ");
printf("full of dark blue liquid which\nsmells strongly of chlorine.");
printf(" The words \"Gleep Tank\" have been crudely\n");
printf("spray painted on the wall.\n") ;
return ;
 
case R_ufo_e:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You crawl under a long thin sting that projects from the ");
printf("front of the\nspacecraft.  It's made from a different metal ");
printf("(stainless steel?), and appears\nto have been retractable. ");
printf("This was probably a Mach probe for measuring flight\n") ;
printf("speed. You can go north or south.\n") ;
return ;
 
case R_ufo_w:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("Before you is perhaps the real reason why the ACME Mine ");
printf("was closed. You see\nthe bent and twisted remains of what ");
printf("could only be an ancient spacecraft. It\nsits ") ;
printf("embedded within a gold bearing");
printf(" reef of conglomerate stone from the\nPrecambrain Period ");
printf("(hundreds of millions of years old).  The old spacecraft\n") ;
printf("was based on a delta wing design which the miners had ");
printf("chiped free from\nthe rock. You can see clearly the interior ");
printf("of the engine exhaust ducts.  The\nvehicle has air inlets ");
printf("so it must have been air breathing when it flew in\nthe ");
printf("atmosphere. ") ;
printf("The edges of the ducts appear to be made of titanium ");
printf("and are\nabout six centimetres thick. No wonder it could ");
printf("survive millions of years\nunder tons of stone. ") ;
printf("This spacecraft is literally built like a battleship!\nYou ") ;
printf("can climb over the vehicle to the north or go south.\n\n");
return ;
 
case R_ufo_n:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You're now doing a tight squeeze between the tunnel wall ");
printf("and the leading\nedge of the wing.  You can see the titanium");
printf(" surface is covered with many\nregularly placed little ");
printf("holes, each about half a millimetre in diameter.\nThis ");
printf("was probably part of the wing's cooling system for ") ;
printf("atmospheric entry\nfrom orbit. You can go south-east or ");
printf("south-west.\n\n");
return ;
 
case R_ufo_s:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You're crawling under the wing and next to the spacecraft's ");
printf("landing gear.\nThe landing gear strut is almost snapped ");
printf("off.  The tyre has long ago turned\nto dust, but the tyre ");
printf("rim is still in place.  The braking system used is\nquite ");
printf("odd.  The brake rotor is basicly a ring being gripped by ");
printf("a caliper with\nconcave brake pads.  You ") ;
printf("can go north-west or north-east.\n") ;
return ;
 
case R_ufo_ne:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are now near the nose of the derelict spacecraft.  You ");
printf("see a quartz\nwindow in the side of the vehicle.  It has been");
printf(" so scratched by the\ncenturies that it is now opaque.  ");
printf("You can go north-west or south.\n") ;
return ;
 
case R_ufo_nw:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("As you scrambled over the old derelict, you passed under ");
printf("the vertical\nstabilizer which centuries of geological ") ;
printf("forces had bent into what\nlooks like a sagging shark's ");
printf("fin. You can go south or do a tight squeeze\nto the ");
printf("north-east.\n\n");
return ;
 
case R_ufo_se:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are under the forward section of the spacecraft. ");
printf("Above you is an\nopened access hatch which leads into the ");
printf("dark interior of the derelict.\n");
printf("You can go north, up or crawl under the wing to the ");
printf("south-west\n") ;
return ;
 
case R_ufo_sw:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are hunching over as you scramble underneath the ");
printf("spacecraft's wing.\nNear the trailing edge of the wing ");
printf("you can see what is left of the\nwing flaps.  The flap ");
printf("was actuated by a very conventional hydraulic system.\n");
printf("Some of the metal tubing for the actuaters are still in ");
printf("place, though\nthe hydraulic fluid has long since ") ;
printf("fossilized into stone. You can\ngo north or south-east.\n") ;
return ;
 
case R_air_lock:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are inside what is obviously an airlock.  There are ");
printf("two hatchways\ninto this airlock.  One leads to the exterior ");
printf("while the other goes into\nthe spacecraft's interior.  Both ");
printf("hatches appear to have originally been\nleft open and not ");
printf("forced by the miners (the hinges are immovable). ");
printf("It\nappears that the ship's crew left in a hurry. ") ;
printf("You can go north or down.\n") ;
return ;

case R_ship_passage:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You've entered the intercompartment access passage.  To the ") ;
printf("south is an\nopen air tight door leading to the airlock. ");
printf("The access door to the east\nis open and recessed into the ");
printf("wall. The access door to the west has been\nforced open ");
printf("with a cutting torch and folded back with a pneumatic\n") ;
printf("hammer (obviously the work of the miners). ") ;
printf("The passage itself has about\nten centimetres of silt on the") ;
printf(" bottom and has the appearance of ancient\ndilapidation.\n") ;
return ;

case R_flight_deck:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You have made it to the flight deck. Unfortunately ");
printf("it's not much to\nwrite home about. Since the access door ");
printf("was open, this area has been full\nof water and silt for ");
printf("millennia.  The miners have shoveled out most of it.\nOnce ");
printf("the wall panels were covered with some kind of plastic which");
printf(" has long\nsince turned to dust.  There are three corroded ");
printf("frames which were once crew\nseats. The beings that flew ") ;
printf("this machine were taller and wider than humans\nbut they ");
printf("had anthropoid form. The flight controls are still here");
printf(" but they\nare so heavily corroded that they can no longer "); 
printf("be moved.  The only way out\nis to the west.\n\n") ;
return ;

case R_panel:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are in a compartment that seems brand new, which is ");
printf("unbelievable.  Perhaps\nthe machinery in this ship was once ");
printf("self repairing.  Before you is a control\npanel with CRT type");
printf(" displays and buttons that still work.  Beneath each button\n");
printf("is a description written in a strange alien script ");
printf("vaguely like Sanskrit.\nI wouldn't dare ") ;
printf("press any button except for a gray button.  Beneath\n");
printf("this button is some masking tape that was obviously placed ") ;
printf("there by the miners.\nSomeone has written \"TEHR.\" on the ") ;
printf("masking tape with a pencil.\n\n") ;
return ;

case R_transporter:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You have walked into an elevated chamber with strange ") ;
printf("glowing hexagons on\nthe floor which are about half a ") ;
printf("metre across.  The hexagon pattern on the\nfloor is ");
printf("matched by one on the ceiling which is also glowing.\n\n") ;
return ;

case R_prayer:
room[n][M_rm_type] = T_short_descp ;   /* disable long description  */
printf("You are in a large and very grand room with walls made of\n");
printf("polished mahogany, and crystal chandeliers hanging from an\n");
printf("ornate ceiling.  There is a mihrab incongruously set in the\n");
printf("western wall of the building.  Also there are quotations\n");
printf("from the Quram written in golden letters along the top of\n") ;
printf("the walls near the ceiling.  On the floor are sumptuous\n") ;
printf("cushions made of silk and fine green velvet. Sitting on the\n");
printf("cushions are old men wearing black pajamas with white\n");
printf("towels wrapped around their heads. In the middle of the\n");
printf("floor is a raised dais, upon which is sitting a rather\n");
printf("stately old man wearing similar clothing. In the far corner\n");
printf("of the room is standing a wax dummy of the Ayatolla\n") ;
printf("Khomeini. His right arm is upright much like the Statue of\n") ;
printf("Liberty and in his right hand is a glowing 100 watt light\n") ;
printf("bulb.  I think this is the prayer room for the Iranian\n") ;
printf("Parliament!  You'll have to go west if you wish to leave.\n\n") ;
return ;
 
case R_guard:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are in a rather small room with a table in the ");
printf("middle that is covered\nwith half filled cups of tea, dirty ") ;
printf("ash trays, and a newspaper written in\nwhat appears to be ") ;
printf("Arabic.  There is ") ;
printf("a brightly coloured poster on the\nwall depicting the Kaba ") ;
printf("Stone of Mecca with a calendar below it.  The only\n") ;
printf("exits are through an open doorway to the east and through");
printf(" a curtain covered\ndoorway to the south.\n\n") ;
return ;
 
case R_closet:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You are in a closet full of grubby, nondescript things not\n") ;
printf("worth taking. The closet stinks of moth balls. The only way\n");
printf("out is through a curtain covered doorway to the north.\n\n");
return ;
 
case R_gong:
room[n][M_rm_type] = T_short_descp ;   /* disable long description  */
printf("You have entered an enormous room which is walled with\n");
printf("polished black granite supported by vast curving arches\n");
printf("much like a gothic cathedral.  The cavernous room is a seven\n");
printf("sided polygon in layout with huge flaming torches set in\n");
printf("brass holders in every corner of the room.  In the flickering\n");
printf("light of the torches you see an enormous silver gong\n");
printf("weighing at least a ton.  The huge gong is suspended from\n");
printf("a finely polished red cedar frame, the top of which is\n");
printf("about four metres above the floor.  The room is deathly\n");
printf("quiet like an ancient tomb. The only sound you can hear is\n");
printf("your own heart beating.\n") ;
return ;
 
case R_warning:
room[n][M_rm_type] = T_was_long;   /* long description only on request  */
printf("You have entered a passage with exits to the north, south,\n");
printf("and west.  There is a poster glued to the wall which reads:\n");
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
	return ;
 
	} 
}
else describe(n) ;

} /* --- end of long_descp subroutine --- */
