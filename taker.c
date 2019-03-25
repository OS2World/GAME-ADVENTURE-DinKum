#define TAKER
#include "dink_sym.h"
#include "dink_glb.h"
 
#if (PROTOTYPE)
void taker(int n)
#else
void taker(n)
int n ;
#endif
/*********************************************************/
/*                                                       */
/*           --- Object Taking Subroutine ---            */
/*                                                       */
/*      Program by Gary A. Allen, Jr.   15 January 1993  */
/*        (c) Copyright 1993 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
register int i, j ;
int  sw_done, gleep_local, ammo_flag ;
OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
void clip_in(int), clip_out(int), ender(int), eater(void) ;
#endif

/* Alias in the object for the single word "take" command */
if (tag[V_VERB_ONLY]) {
	j = 0 ;
	/* See if there is only one object on the floor */
	pnt = object ;
	for (i = 0; i < Objcnt; i++) {
		if (n == pnt->Location) {
			j++ ;
			tag[pnt->ID] = TRUE ;
		}
		pnt++ ;
	}

	if (room[n][M_gleep] != 0) {
		j++ ;
		tag[V_gleep] = TRUE ;
		if (room[n][M_gleep] > 1) tag[V_PLURAL] = TRUE ;
	}

	/* Complain if there isn't a single object on the ground */
	if (j > 1) {
		printf ("What exactly do you want me to take? \n");
		return ;
	}
}

ammo_flag = F_no_clip ;
if (tag[V_clip]) ammo_flag = F_normal_clip ;
if (tag[V_org_clip]) ammo_flag = F_org_clip ;

/* deal with special case of "orange clip" implied by its being alone */
if (tag[V_clip]&&(Clip->Location != n)&&(Org_clip->Location == n)) {
	tag[V_org_clip] = TRUE ;
	tag[V_clip] = FALSE ;
	if (V_clip == sent[1]) sent[1] = V_org_clip ;
}

/* deal with the verb "attach" */
if (verb == V_attach) {
	if (tag[V_rifle]&&(ammo_flag != F_no_clip)) {
		clip_in(ammo_flag) ;
		return ;
	}
	if ((n != R_office_mang)&&(room[n][M_obj_cnt] <= 0)) {
		printf ("There is nothing here that I can attach!\n");
		return ;
	}
}

/* Check to see if player already has the item */
pnt = object ;
for (i = 0; i < Objcnt; i++) { 
	if (pnt->ID == sent[1]) {
		if (pnt->Location == B_have) {
printf ("You already have a %s in your possession.\n",vocab[sent[1]-1]);
			return ;
		}
		else break ;
	}
	pnt++ ;
}

sw_done = FALSE ;

/* Special case of "take pill" */
if ((tag[V_pill])&&(Pills->Location == B_have)) {
	eater() ;
	return ;
}

/* Reject "take" command when there is nothing to take */
if ((n != R_office_mang)&&(verb != V_attach)&&(verb != V_remove)&&
	(room[n][M_obj_cnt] <= 0)&&(room[n][M_gleep] == 0)&&
	(!((n == R_gleep_tank)&&(Tank->Status > 0)))
	&&(!room[n][M_unmov_obj])) {
	printf ("There is nothing here that you can take! \n");
	return ;
}

/* player takes something from the gleep tank */
if (tag[V_tank]) {
	if (n != R_gleep_tank) {
printf("I see no gleep tank to take anything from. \n") ;
		return ;
	}
printf("\nYou climb up onto the edge of the gleep tank and reach\n");
printf("into the dark blue fluid.  Suddenly the fluid begins a\n");
printf("furious boiling that instantly reduces your hand into\n") ;
printf("bleached white bones.  The shock and pain disturbs your\n");
printf("balance and you fall into the horrible stuff!!  There is\n");
printf("once again a furious boiling.  Eventually the fluid stills\n");
printf("and becomes clear again.  On the bottom of the tank can\n") ;
printf("be seen a white, clean, \"medical school quality\" human\n");
printf("skeleton.\n") ;
	ender(F_died) ;
}
 
/* Deal with "safe" taking errors */
if ((tag[V_safe])&&(n != R_office_mang)) {
	printf("There is no safe here.\n") ;
	return ;
}

/* gleep taking routine (must be after the gleep tank routine) */
if (tag[V_gleep]) {
if (!tag[V_safe]) {

	/* Count up the gleeps available in this room */
	if ((n == R_office_mang)&&(Safe->Status == S_open)) 
		gleep_local = gleep_safe ;
	else gleep_local = 0 ;
	gleep_local += room[n][M_gleep] ;
	/* Gleeps in the tank aren't really accessible but the player */
	/*    may wish to suicide by taking them.                     */
	if (n == R_gleep_tank) gleep_local += Tank->Status ;

	/* Leave if there are no gleeps */
	if (gleep_local == 0) {
		printf("There are no gleeps here to take!\n") ;
		return ;
	}

	/* Gleeps in the tank but not on the floor */
	/*   This is to lure player into suicide.  */
	if ((n == R_gleep_tank)&&(room[n][M_gleep] == 0)) {
		printf("There are no gleeps on the floor but I see ") ;
		if (Tank->Status == 1) 
			printf("a gleep in the gleep tank.\n");
		else
			printf("%d gleeps in the gleep tank.\n",Tank->Status) ;
		return ;
	}

	/* This block is for accessible gleeps in office with open safe */
	if ((n == R_office_mang)&&(Safe->Status == S_open)
			&&(Picture->Status == S_open)) {
		if ((!tag[V_PLURAL])||(gleep_local == 1)) {
			printf("Gleep taken. \n") ; 
			++gleep_count ;
			if (gleep_safe == 0) --room[n][M_gleep] ;
			else --gleep_safe ;
		}
		else {
			if (tag[V_NUMBER]) {
				if (number_word == 0) {
					printf("Don't be silly.\n") ;
					return ;
				}
				if (number_word > gleep_local) {
printf("There aren't that many gleeps here!\n") ;
					return ;
				}
				else {
printf("%d gleeps taken.\n", number_word) ; 
					gleep_count += number_word ;
					gleep_local -= number_word ;
					gleep_safe = gleep_local ;
					room[n][M_gleep] = 0 ;
				}
			}
			else {
				printf("Gleeps taken. \n") ; 
				gleep_count += gleep_local ;
				room[n][M_gleep] = 0 ;
				gleep_safe = 0 ;
			}
		}
		return ;
	}

	/* This block is for accessible gleeps everywhere else */
	/*       or the office with the safe closed.           */
	if ((!tag[V_PLURAL])||(room[n][M_gleep] == 1)) {
		printf("Gleep taken. \n") ; 
		++gleep_count ;
		--room[n][M_gleep] ;
	}
	else {
		if (tag[V_NUMBER]) {
			if (number_word == 0) {
				printf("Don't be silly.\n") ;
				return ;
			}
			if (number_word > room[n][M_gleep]) {
printf("There aren't that many gleeps here!\n") ;
					return ;
			}
			else {
				printf("%d gleeps taken.\n", number_word) ; 
				gleep_count += number_word ;
				room[n][M_gleep] -= number_word ;
			}
		}
		else {
			printf("Gleeps taken. \n") ; 
			gleep_count += room[n][M_gleep] ;
			room[n][M_gleep] = 0 ;
		}
	}
	return ;
} /* sentence does NOT have the word "safe" block */
else {
	if ((Picture->Status == S_open)&&(Safe->Status == S_open)) {
		if (gleep_safe != 0) { 
		if (tag[V_PLURAL] && (gleep_safe > 1)) {
			if (tag[V_NUMBER]) {
				if (number_word == 0) {
					printf("Don't be silly.\n") ;
					return ;
				}
				if (number_word > gleep_safe) {
printf("There aren't that many gleeps in the safe!\n") ;
					return ;
				}
				else {
printf("%d gleeps taken.\n", number_word) ; 
					gleep_count += number_word ;
					gleep_safe -= number_word ;
				}
			}
			else {
				printf("Gleeps taken from safe. \n") ; 
				gleep_count += gleep_safe ;
				gleep_safe = 0 ;
			}
		}
		else {
			printf("Gleep taken from safe. \n") ; 
			++gleep_count ;
			--gleep_safe ;
		}
		}
		else printf("There are no gleeps in the safe!\n") ;
	}
	else {
		if (tag[V_PLURAL]) 
printf("There is no open safe to take gleeps from.\n") ;
		else
printf("There is no open safe to take the gleep from.\n") ;
	}
	return ;
} /* sentence does have the word "safe" block */
} /* end of the gleep taking block */


/* treat the verb "remove" in the context of "remove clip from rifle" */
if (verb == V_remove) {
	if ((!tag[V_safe])&&(ammo_flag != F_no_clip)) {
		clip_out(n) ;
		return ;
	}
}

if (carry_count > 5) {
printf("I can't do it!\n") ;
printf("I'm holding so many things that I can't take anymore!\n") ;
	return ;
}

if (carry_weight >= 800) {
printf("I can't do it!\n") ;
printf("This junk I'm carrying is too heavy! I can't carry anymore!\n");
	return ;
}


/* find the object(s) in this room */
pnt = object ;
for (i = 0; i < Objcnt; i++) {

	if ((carry_count > 5)||(carry_weight >= 800)) break ;

	/* See if the object is in the safe and was requested */
	if ((n == R_office_mang)&&(pnt->Location == B_in_safe)
		&&(tag[pnt->ID]||tag[V_all])
		&&((!tag[V_treasure])||(pnt->Value > 0))) {

		if (Picture->Status != S_open) {
			if (tag[V_all] || tag[V_treasure])
				printf("I don't see a safe.\n") ;
			else printf("You need to open the picture first.\n") ;
			return ;
		}
		if (Safe->Status == S_open) {
			pnt->Location = B_have; 
			carry_count++ ;
			carry_weight += pnt->Weight ; 
			sw_done = TRUE ;
		}
		else {
			printf("I can't do it because the safe is closed. \n") ;
			return ;
		}
	} 
	
	/* See if the object is in the room and was requested */
	if ((pnt->Location == n)&&(tag[pnt->ID] || tag[V_all])
		&&((!tag[V_treasure])||(pnt->Value > 0))) {

		/* Objects referred to in this block are not in the safe */
		if (!tag[V_safe]) {
		/* see if taking the object causes special action */
		if (pnt->Type == Z_transform) {
			switch(pnt->ID) {
			/* ACME doormat */
			case V_mat:
printf("As you lift up the dirty old doormat, you find half \n") ;
printf("hidden in the dust....  a large brass key. \n") ;
				Mat->Type = Z_normal ;
				carry_count++ ;
				carry_weight += Mat->Weight;
				Mat->Location = B_have;
				Key->Location = R_office_entr ;
				sw_done = TRUE ;
				return ;

			/* Map of the ACME Mine */
			case V_map:
printf("As you picked up the old map from the floor, most of it");
printf(" crumbled into \ndust leaving only one small piece. \n") ;
				Map->Location = B_unmade ;
				Map_frag->Location = B_have ;
				carry_count++ ;
				carry_weight += Map_frag->Weight ;
				--room[n][M_obj_cnt] ;
				sw_done = TRUE ;
				return ;
			}
		} /* end of the special action block */ 

		/* see if an object on the floor can be taken */
		if ((pnt->Type == Z_normal)||
				(pnt->Type == Z_alias)) {
			--room[n][M_obj_cnt] ;
			carry_count++ ;
			carry_weight += pnt->Weight ; 
			pnt->Location = B_have; 
			sw_done = TRUE ;
		} 
		}

		/* see if this is an unmovable, nonacting object */
		if ((pnt->Type == Z_unmovable) &&
				(pnt->Location == n) && (!tag[V_all])) {

			switch(pnt->ID) {
			case V_bulldust:
printf("The bulldust is so fine that it wafts away with a touch.\n") ;
				return ;

			/* Silver gong */
			case V_gong:
printf("The siver gong is about three metres in diameter and weighs at\n") ;
printf("least a ton!  There is no way I could move it, let alone get\n") ;
printf("it through the tunnel!\n") ;
				return ;

			/* Cockroach(es) */
			case V_cockroach:
printf("I will not touch the filthy things!\n") ;
				return ;

			/* Kangaroo(s) */
			case V_kangaroo:
printf("I will not touch a dead maggoty kangaroo!  ") ;
printf("The smell is bad enough!\n") ;
				return ;

			case V_desk:
printf("The desk is of very solid construction and can not be moved.\n") ;
				return ;

			case V_chart:
printf("The charts and production schedules are so old and brittle that\n") ;
printf("they'd fall apart the moment you touched them.  Besides they're\n") ;
printf("useless and not worth taking.\n") ;
				return ;

			case V_poster:
printf("I think this sort of poster is best left on the wall.\n") ;
				return ;

			/* Spinifex(es) */
			case V_spinifex:
printf("The thorns on the spinifex are large and nasty.\n") ;
printf("I'll just leave them to roll about.\n") ;
				return ;

			/* Platypus Picture */
			case V_picture:
printf("The picture can not be removed.  It appears to be hinged ");
printf("to the wall.\n");
				return ;

			/* Safe */
			case V_safe:
				if (sw_done) break ;
printf("The safe is set in a concrete wall.  I can see no way\n") ;
printf("the safe can be removed without destroying the wall.\n") ;
				return ;

			/* Building door */
			case V_door:
				if (Door->Status == S_kicked) 
printf("The door is too heavy and bulky to move.\n") ;
				else {
printf("The door is attached to the building with some heavy duty\n") ;
printf("hinges which I can't remove.\n") ;
				}
				return ;

			/* "Other" non-movable objects */
			default:
				printf("I don't think I can move that.\n") ;
				return ;
			} /* end of switch block */
		} /* end of unmovable object block */ 

	} 
	pnt++ ;
} /* end of the object scan loop */

/* take all gleeps if any */
if (tag[V_all]&&(!tag[V_treasure])) {
	if (room[n][M_gleep] > 0) { 
		gleep_count += room[n][M_gleep] ;
		room[n][M_gleep] = 0 ;
		sw_done = TRUE ;
	}
	if ((gleep_safe != 0)&&(n == R_office_mang)
			&&(Safe->Status == S_open)) {
		gleep_count +=  gleep_safe ;
		gleep_safe = 0 ;
		sw_done = TRUE ;
	}
}

/* Announce the "take" was successful */
if (sw_done) {
	if (((carry_count > 5)||(carry_weight >= 800))&&(tag[V_all])) 
		printf("You've taken as much as you can.\n") ;
	else printf ("Done \n");
}
/* --else-- announce the "take" was unsuccessful */
else  {
	if (tag[V_all]) printf("I see nothing which I can take.\n") ;
	else { 
		if (tag[V_VERB_ONLY]) 
			printf("What exactly should I take?\n") ;
		else {
			printf ("I don't see a") ;
			if (tag[V_PLURAL]) printf("ny") ;
			printf (" %s around here. \n",vocab[sent[1]-1]);
		}
	}
}
return ;

} /* --- end of the "taker" subroutine --- */

#if (PROTOTYPE)
void loader(void)
#else
void loader()
#endif
/*********************************************************/
/*                                                       */
/*           --- Rifle Loading Subroutine ---            */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  29 April 1990     */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{

int ammo_flag ;

#if (PROTOTYPE)
void clip_in(int) ;
#endif

/* Reject single verb load command */
if (tag[V_VERB_ONLY]) {
printf("What exactly do you want me to load?\n") ;
	return ;
}
if (!tag[V_rifle]) {
printf("I don't know how I could load that.\n") ;
	return ;
}

/* Deal with implied clip type command */
if (!tag[V_clip]) {
	if ((Clip->Location != B_have)&&
		(Org_clip->Location == B_have)) ammo_flag = F_org_clip ;

	/* the case were there is no clip is found in clip_in */
	if ((Clip->Location == B_have)&&
	     (Org_clip->Location != B_have)) ammo_flag = F_normal_clip ;
}

/* Deal with specific "load [orange] clip" command */
else {
	if (tag[V_orange]) {
		if (Org_clip->Location == B_have) ammo_flag = F_org_clip ;
		else {
printf("You don't possess the orange ammunition clip.\n") ;
			return ;
		}
	}
	else {
		if (Clip->Location == B_have) ammo_flag = F_normal_clip ;

		/* Assume "load clip" with no normal clip implies orange clip */
		else {
			if (Org_clip->Location == B_have) 
				ammo_flag = F_org_clip ;
			else{
printf("You don't possess an ammunition clip to load.\n") ;
				return ;
			}
		}
	}
}

clip_in(ammo_flag) ;
} /* --- end of the "loader" subroutine --- */

#if (PROTOTYPE)
void unloader(int n)
#else
void unloader(n)
int n ;
#endif
/*********************************************************/
/*                                                       */
/*          --- Rifle Unloading Subroutine ---           */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  29 April 1990     */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
#if (PROTOTYPE)
void clip_out(int) ;
#endif

/* Reject single verb load command */
if (tag[V_VERB_ONLY]) {
printf("What exactly do you want me to unload?\n") ;
	return ;
}
if (!tag[V_rifle]) {
printf("I don't know how I could unload that.\n") ;
	return ;
}
clip_out(n) ;
} /* --- end of the "unloader" subroutine --- */

#if (PROTOTYPE)
void dropper(int n)
#else
void dropper(n)
int n ;
#endif
/*********************************************************/
/*                                                       */
/*          --- Object Dropping Subroutine ---           */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  21 May 1990       */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
register int i, k ;

int sw_possess, sw_done, ammo_flag, sw_object, i_10, i_fract ;
int sw_found ;

OBJECT_STRUCT *pnt ;

#if (PROTOTYPE)
void clip_in(int), clip_out(int), boom(void) ;
void objlooker(int), gleeper(int), unlocker(int) ;
void cap_drop(void), dynamite_drop(void), destroy_all(void) ;
void dropped_gun(void) ;
#endif

/* respond to "verb only" command */
if (tag[V_VERB_ONLY]) {
	printf ("You'll have to be more specific. \n");
	return ;
}

/* deal with special case of "orange clip" implied by its being alone */
if (tag[V_clip]&&(Clip->Location != B_have)
		&&(clip_flag != F_normal_clip)
		&&((Org_clip->Location == B_have)||(clip_flag == F_org_clip))) {
	tag[V_org_clip] = TRUE ;
	tag[V_clip] = FALSE ;
	if (V_clip == sent[1]) sent[1] = V_org_clip ;
}

ammo_flag = F_no_clip ;
if (tag[V_clip])  ammo_flag = F_normal_clip ;
if (tag[V_org_clip])  ammo_flag = F_org_clip ;

/* deal with special cases of the verbs */
switch(verb) {
case V_put:
	/* special case of putting (destroying) an object in water */
	if (tag[V_tank]||tag[V_gleep]||tag[V_safe]||
		tag[V_river]||tag[V_billabong]||tag[V_stream]) break ;

	/* special case of "put key in door(lock)" */
	if (tag[V_key] && tag[V_door]) {
		unlocker(n) ;
		return ;
	}

	if (!tag[V_cap]) {
		if ((!tag[V_rifle])&&(ammo_flag != F_no_clip)) {
			printf("What am I to put the clip into? \n") ;
			return ;
		}
		if (tag[V_rifle]&&(ammo_flag != F_no_clip))  
				clip_in(ammo_flag) ;
		else 
printf("I don't understand what this is to be put into. \n") ;
		return ;
	}

case V_insert:
	if (tag[V_safe]) break ;
	if (ammo_flag != F_no_clip) {
		if (!tag[V_rifle]) {
printf("What am I to insert the clip into? \n") ;
		}
		else {
			clip_in(ammo_flag) ;
		}
		return ;
	}
	if (tag[V_cap]) {
		if (!tag[V_dynamite]) {
printf("I see no reason why I should put a blasting cap into that.\n") ;
			return ;
		}
		/* Cap insertion routine */
		else {
			/* see if your are holding the dynamite or the cap */
			if ((Cap->Location != B_have)&&
				(Dynamite->Location != B_have)) {
printf("You bloody dill!  You have neither the dynamite or a ");
printf("blasting cap.\n") ;
				return ;
			}
			if (Cap->Location != B_have) {
printf("You've got the dynamite but you need a blasing cap.\n") ;
				return ;
			}
				if (Dynamite->Location != B_have) {
printf("You've got the blasting cap but you need some dynamite.\n") ;
				return ;
			}
/* transform the two objects into one */
printf("With some trepidation, you slide the blasting cap into\n");
printf("the dynamite.  What you are now holding is VERY dangerous.\n");
			Cap->Location = B_unmade ; 
			Dynamite->Type = Z_alias ;
			carry_weight -= Cap->Weight ;
			carry_count-- ;
			return ;
		} /* end of the cap insertion block */
	}
printf("I can think of some interesing places to insert this. \n") ;
printf("However I shall not reduce myself to such vulgarity.\n");
	return ;
	
case V_eject:
/* Command "eject clip" ejects clip from rifle no matter what type*/
	if ((ammo_flag == F_normal_clip)&&(clip_flag == F_org_clip)) 
		ammo_flag = F_org_clip ; 
case V_drop:
	if (((ammo_flag == F_org_clip)&&(clip_flag == F_org_clip))|| 
	((ammo_flag == F_normal_clip)&&(clip_flag == F_normal_clip))) { 
		clip_out(n) ;
		return ;
	}
	break ;

} /* end of switch */

/* Deal with "drop" when player has no objects */
if (tag[V_all]&&(carry_count == 0)&&(gleep_count == 0)) {
	printf("You dill!  You have nothing to drop!\n") ;
	return ;
}

/* deal with "drop in safe ..." errors */
if (tag[V_safe]) {
	/* see if this is the managers office */
	if (n != R_office_mang) {    	
		printf("There is no safe here! \n");
		return ;
	}

	/* See if the picture and safe are open */
	if ((Picture->Status != S_open) || (Safe->Status != S_open)) {
		printf ("I don't see an open safe to put anything into.\n") ;
		return ;
	}
}
 
/* gleep droping routine */
if (tag[V_gleep]||tag[V_tank]) {
	/* drop gleeps in a normal way */
	if (!tag[V_tank]) {
		if (gleep_count == 0) { 
			printf("You have no gleeps to drop! \n") ;
			return ;
		}
		if ((!tag[V_PLURAL])||(gleep_count == 1)) {
			if (tag[V_safe]) {
				printf("Gleep put into safe.\n") ;
				++gleep_safe ;
				--gleep_count ;
			}
			else {
				printf("Gleep dropped. \n") ; 
				--gleep_count ;
				++room[n][M_gleep] ;
			}
		}
		else {
			if (tag[V_safe]) {
				if (tag[V_NUMBER]) {
					if (number_word == 0) {
						printf("Don't be silly.\n") ;
						return ;
					}
					if (number_word > gleep_count) {
printf("I don't have that many gleeps!\n") ;
						return ;
					}
					else {
printf("You put %d gleeps into the safe.\n", number_word) ; 
						gleep_safe += number_word ;
						gleep_count -= number_word ;
					}
				}
				else {
					printf("Gleeps put into safe.\n") ;
					gleep_safe += gleep_count ;
					gleep_count = 0 ;
				}
			}
			else {
				if (tag[V_NUMBER]) {
					if (number_word == 0) {
						printf("Don't be silly.\n") ;
						return ;
					}
					if (number_word > gleep_count) {
printf("I don't have that many gleeps!\n") ;
						return ;
					}
					else {
printf("You drop %d gleeps.\n", number_word) ; 
					room[n][M_gleep] += number_word ;
					gleep_count -= number_word ;
					}
				}
				else {
					printf("Gleeps dropped. \n") ; 
					room[n][M_gleep] += gleep_count ;
					gleep_count = 0 ;
				}
			}
		}
		gleep_drop = TRUE ;
		return ;
	}

	/* drop objects(including gleeps) into a gleep tank */
	else {
		sw_found = FALSE ;
		if (n != R_gleep_tank) {
			printf("I don't see a gleep tank here. \n") ;
			return ;
		}
		if (tag[V_gleep]) {
			if (gleep_count <= 0) {
printf("You have no gleeps to put in the tank. \n") ; 
				return ;
			}
			sw_found = TRUE ;
			if ((!tag[V_PLURAL])||(gleep_count == 1)) {
printf("Your gleep falls into the tank with a \"plonk\".\n") ;
				++Tank->Status ;
				--gleep_count ;
			}
			if (tag[V_PLURAL]) {
				if (tag[V_NUMBER]) {
					if (number_word == 0) {
						printf("Don't be silly.\n") ;
						return ;
					}
					if (number_word > gleep_count) {
printf("I don't have that many gleeps!\n") ;
						return ;
					}
					else {
printf("You drop %d gleeps into the gleep tank.\n", number_word) ;
						Tank->Status += number_word ;
						gleep_count -= number_word ;
					}
				}
				else {
printf("Your gleeps fall into the tank causing a splash.\n") ;
					Tank->Status += gleep_count ;
					gleep_count = 0 ;
				}
			}
		} /* end of the tag[V_gleep] block */

		/* Drop non-gleeps into the tank */
		/* the "drop all" routine */
		if (tag[V_all]) {
			sw_possess = FALSE ;
			pnt = object ;
			for (i = 0; i < Objcnt; i++) {
				if ((pnt->Location == B_have)&&
					((!tag[V_treasure])||
					(pnt->Value > 0))) {
					sw_possess = TRUE ;
					pnt->Location = B_destroyed; 
					carry_count-- ;
				carry_weight -= pnt->Weight ;
				}
				pnt++ ;
			}
			if (gleep_count == 0) {
				if (sw_possess) {
printf("You dump everything into the gleep tank. There is a furious\n");
printf("bubbling as the corrosive fluid of the tank turns the\n");
printf("objects into NOTHING.\n") ;
				}
				else 
printf("You've got nothing to throw into the tank.\n") ;
			}
			else {
				if (sw_possess) {
printf("You fling everything into the gleep tank.  The gleep");
				if (gleep_count > 1) {
printf("s\nsplash into the tank and settle to the bottom of the\n") ;
				}
				else {
printf("\nplonks into the tank and settles to the bottom of the\n") ;
				}
printf("tank.  However the other objects begin to dissolve the\n");
printf("moment the tank's fluid touches them.  Time passes and\n");
printf("the objects dissolve into NOTHING.\n") ;
				}
				/* you possess no non-gleeps */
				else {
				if (gleep_count == 1) 
printf("Your gleep falls into the tank with a \"plonk\".\n") ;
				else
printf("Your gleeps fall into the tank causing a splash.\n") ;
				}
			Tank->Status += gleep_count ;
			gleep_count = 0 ;
			}
			return ;
		} /* end of the "drop all" if block */

		/* Individual non-gleeps are dropped into the tank */

		/* see if your are holding the object(s) */
		pnt = object ;
		for (i = 0; i < Objcnt; i++) {
 			if (tag[pnt->ID] && (pnt->ID != V_tank)) {
				if (pnt->Location == B_have) {
printf ("You fling the %s into the gleep tank.  As soon as it\n",
	vocab[pnt->ID - 1]);
printf ("touched the tank's fluid there was a furious effervescence\n");
printf ("as it began to dissolve.  With the passage of time, the\n") ;
printf ("fluid stills and there is NOTHING left.\n") ;
					carry_count-- ;
					carry_weight -= pnt->Weight ;
					pnt->Location = B_destroyed; 
				}
				else {
printf("You don't have a %s to toss into the gleep tank.\n",
	vocab[pnt->ID - 1]);
				}
				return ;
			}
			pnt++ ;
		} /* object scan "for" loop */

		/* deal with garbage object to drop */
if (!sw_found) printf("I don't understand what you want me to drop.\n") ;
		return ;
	}
}

sw_done = FALSE ;

/* the "drop all" routine */
if (tag[V_all]) {

	/* Deal with throwing stuff into water */
	if(tag[V_stream]) {
		if (n == R_stream) {
printf("You fling everything into the stream.\n");
			destroy_all() ;
			return ;
		}
		else
printf("I see no stream to toss stuff into.\n") ;
		return ;
	}
	if(tag[V_billabong]) {
		if ((n == R_stream)||(n == R_slime)||
			(n == R_billabong)) { 
printf("You fling everything into the billabong.\n");
			destroy_all() ;
			return ;
		}
		else
printf("I see no billabong to toss stuff into.\n") ;
		return ;
	}
	if(tag[V_river]) {
		if ((n == R_dike)||(n == R_river_edge)||
			(n == R_river_exit)) {
printf("You fling everything into the river.\n");
			destroy_all() ;
			return ;
		}
		else
printf("I see no river to toss stuff into.\n") ;
		return ;
	}

	if (!tag[V_safe]) {
/* normal drop */
if (room[n][M_rm_type] != T_looping) {
	/* normal room */
	pnt = object ;
	for (i = 0; i < Objcnt; i++) {
		if ((pnt->Location == B_have)&&
			((!tag[V_treasure]) || (pnt->Value > 0))) {

		sw_done = TRUE ;

		/* see if the blasting cap was hard dropped */
		if ((pnt->ID == V_cap)&&(verb != V_slow_drop)) {
			cap_drop() ;
			return ;
		}

/* see if the dynamite with blasting cap was hard dropped */
		if ((pnt->ID == V_dynamite)&&(Dynamite->Type == Z_alias)
			&&(verb != V_slow_drop)) dynamite_drop() ;
		++room[n][M_obj_cnt] ;
		carry_count-- ;
		carry_weight -= pnt->Weight ;
		pnt->Location = n; 
/* set valuable switch if valuable object dropped in Ned's area */
		if (pnt->Value > 0) {
			for (k = 22; k <= 41; k++) 
				if (k == n) sw_valuable = TRUE;
			for (k = 144; k <= 146; k++) 
			 	if (k == n) sw_valuable = TRUE;
		}
	}
	pnt++ ;
}
			/* drop all gleeps */
			if ((gleep_count > 0) &&
					(!tag[V_treasure])) {
				room[n][M_gleep] += gleep_count ;
				gleep_count = 0 ;
				sw_done = TRUE ;
				gleep_drop = TRUE ;
			}

			if (sw_done) {
				printf ("Done\n");
				objlooker(n) ;
				gleeper(n) ; 
			} 
			else printf("Don't have it to drop.\n") ;
			return ;
		}
		/* object destroyer room */
		else {
		/* Code assumes that player has something to drop */
printf ("You dropped everything you had in a heap, which \n");
printf ("promptly vaporized into a bright blue flash followed \n");
printf ("by a low \"BOOM\". \n") ; 
printf ("       --- You've blown it Bozo!! ---\n") ;
			destroy_all() ;
			return ;
		}
	}
	/* "drop all into the safe" routine */
	else {
		pnt = object ;
		for (i = 0; i < Objcnt; i++) {
			if ((pnt->Location == B_have) &&
				((!tag[V_treasure])||
				(pnt->Value > 0))) {
				pnt->Location = B_in_safe ;	
				carry_count-- ;
				carry_weight -= pnt->Weight ;
				sw_done = TRUE ;
			}
			pnt++ ;
		}
		if (!tag[V_treasure]) {
			gleep_safe += gleep_count ;
			gleep_count = 0 ;
			sw_done = TRUE ;
		}
		if (sw_done) printf ("Done \n");
		else printf("You don't have it to put in the safe!\n") ;
		return ;
	}
}

/* see if your are holding the object(s) */
for (i = 0; i < Objcnt; i++) {
	if (i == 0) pnt = object ;
	else pnt++ ;
	sw_object = FALSE ;
	if (tag[pnt->ID]) {
		sw_object = TRUE ;
 		if (pnt->Location == B_have) {
			/* Safe storage routine */
			if (tag[V_safe]) {
				pnt->Location = B_in_safe ;	
printf ("The %s is now inside the safe. \n", 
	vocab[pnt->ID - 1]);
				sw_done = TRUE ;
				carry_count-- ;
				carry_weight -= pnt->Weight ;
				continue ;
			}
 
			/* Single 'drop' routine */
			if (tag[V_river]||tag[V_billabong]||
				tag[V_stream]) {
		/* The object is to be dropped in water */
				if(tag[V_stream]) {
					if (n == R_stream) {
printf("You fling the %s into the stream.\n", 
	vocab[pnt->ID - 1]);
					carry_count-- ;
				carry_weight -= pnt->Weight ;
					pnt->Location = B_destroyed; 
					return ;
					}
					else
printf("I see no stream to toss it into.\n") ;
					return ;
				}
			if(tag[V_billabong]) {
				if ((n == R_stream)||
				(n == R_slime)||(n == R_billabong)) { 
printf("You fling the %s into the billabong.\n",
	vocab[pnt->ID - 1]);
					carry_count-- ;
				carry_weight -= pnt->Weight ;
					pnt->Location = B_destroyed; 
					return ;
				}
				else
printf("I see no billabong to toss it into.\n") ;
				return ;
			}
			if(tag[V_river]) {
				if ((n == R_dike)||(n == R_river_edge)||
					(n == R_river_exit)) {
printf("You fling the %s into the river.\n", 
	vocab[pnt->ID - 1]);
					carry_count-- ;
				carry_weight -= pnt->Weight ;
					pnt->Location = B_destroyed; 
					return ;
				}
				else
printf("I see no river to toss it into.\n") ;
				return ;
			}
		}
		/* Normal Drop */
		else if (room[n][M_rm_type] != T_looping) {
			if ((pnt->ID == V_cap)&&(verb != V_slow_drop)) {
				cap_drop() ;
				return ;
			}
			if ((pnt->ID == V_dynamite)&&(verb != V_slow_drop)&&
		(Dynamite->Type == Z_alias)) dynamite_drop();

/* If the he rifle is dropped.  See if it kills the player */
if (pnt->ID == V_rifle) {
	if ((clip_flag != F_no_clip) && 
(Rifle->Status > 0)) switch(rifle_flag) {
	case F_safety:
		break ;
			
	case F_single:
		printf("\nBam!\n") ;
		dropped_gun() ;

	case F_triple:
		printf("\n") ;
		if (Rifle->Status >= 3) {
			printf("Bam! Bam! Bam! \n\n") ;
		}
		else {
		for (k = 1; k <= Rifle->Status; k++) 
			printf("Bam! ") ;
		}
		dropped_gun() ;

	case F_auto:
		printf("\n") ;
		if (Rifle->Status >= 30) {
			for (k = 1; k <= 3; k++) 
printf("Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! \n") ;
		}
		else {
			i_10 = Rifle->Status / 10 ;
		i_fract = Rifle->Status - (i_10 * 10) ;
			for (k = 1; k <= i_10; k++) 
printf("Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! Bam! \n") ;
			for (k = 1; k <= i_fract; k++) 
				printf("Bam! ") ;
		}
		dropped_gun() ;
	} /* end of the switch block */
} /* end of "drop rifle" block */

			carry_count-- ;
			carry_weight -= pnt->Weight ;
			++room[n][M_obj_cnt] ;
			pnt->Location = n; 
			sw_done = TRUE ;
/* set valuable switch if valuable object dropped in Ned's area */
			if (pnt->Value > 0) {
				for (k = 22; k <= 41; k++) 
					if (k == n) sw_valuable = TRUE ;
				for (k = 144; k <= 146; k++) 
					if (k == n) sw_valuable = TRUE ;
			}
			continue ;
		}
		else {
printf ("As the %s left your possession there was a bright \n",
	vocab[pnt->ID - 1]);
printf ("blue flash, followed by a low \"BOOM\" as it vaporized \n");
printf ("into nonexistence. \n");
			carry_count-- ;
			carry_weight -= pnt->Weight ;
			pnt->Location = B_destroyed; 
			return ;
		}
		}
 		if (pnt->Location == B_unmade) continue ;
	} /* end of the object requested block */
	if ((!sw_done)&&sw_object) {
printf("You do not possess a %s.\n", vocab[pnt->ID - 1]);
		return ;
	}
} /* end of the object scan loop */
if (sw_done) {
	printf ("Done \n");
	objlooker(n) ;
	gleeper(n) ; 
} 
else 
printf("I don't understand what it is I'm supposed to drop.\n") ;

return ;


} /* --- end of the "dropper" subroutine --- */

#if (PROTOTYPE)
void cap_drop(void)
#else
void cap_drop()
#endif
/*********************************************************/
/*                                                       */
/*         --- Blasing Cap Dropping Subroutine ---       */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  6 December 1992   */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
printf("Bang!! The blasting cap you were carrying detonated when\n") ;
printf("it hit the ground.  Fortunately no damage was caused.\n") ;  
Cap->Location = B_destroyed; 
carry_count-- ;
carry_weight -= Cap->Weight ;

} /* --- end of the "cap_drop" subroutine --- */

#if (PROTOTYPE)
void dynamite_drop(void)
#else
void dynamite_drop()
#endif
/*********************************************************/
/*                                                       */
/*           --- Dynamite Dropping Subroutine ---        */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  6 December 1992   */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
#if (PROTOTYPE)
void ender(int), boom(void) ;
#endif

boom() ;
printf("Dropping a stick of dynamite with a blasting cap in it\n");
printf("ranks high as one of the dumbest things a person can do.\n") ;
printf("Needless to say you were blown to bits. Next time drop\n") ;
printf("the dynamite slowly or gently.\n") ;
ender(F_died) ;

} /* --- end of the "dynamite_drop" subroutine --- */

#if (PROTOTYPE)
void destroy_all(void)
#else
void destroy_all()
#endif
/*********************************************************/
/*                                                       */
/*        --- Destroy Everything Held Subroutine ---     */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  6 December 1992   */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
register int i ;
OBJECT_STRUCT *pnt ;

gleep_count = 0 ;
carry_count = 0 ;
carry_weight = 0 ;
pnt = object ;
for (i = 0; i < Objcnt; i++) {
	if (pnt->Location == B_have)  pnt->Location = B_destroyed; 
	pnt++ ;
}
} /* --- end of the "destroy_all" subroutine --- */

#if (PROTOTYPE)
void dropped_gun(void)
#else
void dropped_gun()
#endif
/*********************************************************/
/*                                                       */
/*     --- Player Suicides by Dropping Armed Rifle ---   */
/*                                                       */
/*      Program by Gary A. Allen, Jr.  31 December 1992  */
/*        (c) Copyright 1992 by Gary A. Allen, Jr.       */
/*                                                       */
/*********************************************************/
{
#if (PROTOTYPE)
void ender(int) ;
#endif

printf("\n") ;
printf("Dropping a loaded and armed automatic rifle is a stupid way\n");
if ((Rifle->Status == 1) || (rifle_flag == F_single)) {
printf("to commit suicide.  Needless to say you were hit by the\n") ;
printf("bullet after the rifle went off.\n") ;
}
else {
printf("to commit suicide.  The bullets shot from the rifle fly\n") ;
printf("around.  One of them bounces back and hits you!\n") ;
}
ender(F_died) ;
} /* --- end of the "dropped_gun" subroutine --- */
