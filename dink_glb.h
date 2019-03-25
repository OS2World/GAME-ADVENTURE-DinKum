/***************************************************************/
/*                                                             */
/*             --- Global Variables Header File ---            */
/*                                                             */
/*        Software by Gary A. Allen, Jr.  16 January 1993      */
/*           (c) Copyright 1993 by Gary A. Allen, Jr.          */
/*                                                             */
/***************************************************************/
 
/* repeated global variable quantites */
/*  Do not move these into the body of the header file. */
#define Vocab_cnt		343
#define DM_tag			344	/* DM_tag    = Vocab_cnt + 1 */

#define DM_room		 	249

#define Enemy_cnt 		15 
#define Objcnt			82
#define Read_objcnt		15
#define Quest_max		9
#define Verb_max 		81 
#define	Adj_max 		20 
#define Adv_max 		30 
#define Obj_init_max 		51 


#ifndef DINKUM
extern struct object_struct *Rifle ;
extern struct object_struct *Teapot ;
extern struct object_struct *Can ;
extern struct object_struct *Clip ;
extern struct object_struct *Org_clip ;
extern struct object_struct *Recorder ;
extern struct object_struct *Cap ;
extern struct object_struct *Dynamite ;
extern struct object_struct *Letter ;
extern struct object_struct *Clapper ;
extern struct object_struct *Detector ;
extern struct object_struct *Key ;
extern struct object_struct *Umbrella ;
extern struct object_struct *Matches ;
extern struct object_struct *Pills ;
extern struct object_struct *Cube ;
extern struct object_struct *Torch ;
extern struct object_struct *Mat ;
extern struct object_struct *Map ;
extern struct object_struct *Map_frag ;
extern struct object_struct *Bottle ;
extern struct object_struct *Circuit_breaker ;
extern struct object_struct *Lift ;
extern struct object_struct *Door ;
extern struct object_struct *Safe ;
extern struct object_struct *Lift_door ;
extern struct object_struct *Picture ;
extern struct object_struct *Tank ;
extern struct object_struct *Gong ;
extern struct object_struct *Transporter ;
#endif

/***************************************************************/

#ifdef DINKUM
struct object_struct *Rifle ;
struct object_struct *Teapot ;
struct object_struct *Can ;
struct object_struct *Clip ;
struct object_struct *Org_clip ;
struct object_struct *Recorder ;
struct object_struct *Cap ;
struct object_struct *Dynamite ;
struct object_struct *Letter ;
struct object_struct *Clapper ;
struct object_struct *Detector ;
struct object_struct *Key ;
struct object_struct *Umbrella ;
struct object_struct *Matches ;
struct object_struct *Pills ;
struct object_struct *Cube ;
struct object_struct *Torch ;
struct object_struct *Mat ;
struct object_struct *Map ;
struct object_struct *Map_frag ;
struct object_struct *Bottle ;
struct object_struct *Circuit_breaker ;
struct object_struct *Lift ;
struct object_struct *Door ;
struct object_struct *Safe ;
struct object_struct *Lift_door ;
struct object_struct *Picture ;
struct object_struct *Tank ;
struct object_struct *Gong ;
struct object_struct *Transporter ;

extern int room[DM_room][16] ;
extern struct object_struct object[Objcnt] ;
extern int tag[DM_tag] ;
int gleep_count = 0 ; /* gleeps being carried */
int verb, max_score = 1100 ;
int sw_wizard = FALSE ;
long clock_explode ;
int sw_warned, flag_clock, sw_clock = FALSE, i_poison = 0 ;

/* gleep initialization matrix */
int gleep_init[10][4] = {
97,	98,	101,	102,
98,	99,	102,	103,
99,	100,	103,	96,
100,	101,	96,	97,
101,	102,	97,	98,
102,	103,	98,	99,
103,	96,	99,	100,
134,	132,	136,	137,
69,	66,	90,	89,
74,	72,	68,	92 
};
int gleep_spot[10] ; /* gleep reproduction room pointer array */

/* monster matrix initialization matrix */
/*  --- NEVER have a monster initialized next to the        */
/*  Mutant Wombat.  This leads to an intractable bug        */
/*  which need to be solved for eventually but is currently */
/*  swept under the carpet.                                 */

int mon_init[Enemy_cnt][4] = {
/* Mutant Wombat */
139,	67,	86,	115,
/* Drop Bears    */
77,	75,	78,	79,
103,	97,	98,	71,
64,	60,	62,	93,
67,	81,	66,	75,
/* Hoop Snakes   */
93,	95,	94,	64,
75,	73,	76,	67,
71,	128,	67,	77,
52,	53,	51,	103,
115,	114,	113,	129,
131,	130,	129,	80,
119,	120,	118,	84,
109,	87,	83,	52,
/* Revolutionary Guards */
241,	241,	241,	241,
/* Chief Mullah */
242,	242,	242,	242
} ;
 
/* object matrix initialization matrix */
/* --- The orange ammo clip should not be set in a dead end, otherwise  */
/*     that version of the game is almost unwinnable due to the wombat. */
int obj_init[Obj_init_max][5] = {
V_can,		1,	1,	1,	1,
V_butt,		165,	166,	161,	152,
V_bottle,	2,	2, 	2,	2,
V_gold,		54,	53,	55,	56,
V_dynamite,	78,	91,	69,	117,
V_clip,		48,	52,	52,	48,
V_org_clip,	80,	68,	113,	99,
V_rifle,	48,	56,	48,	52,
V_cap,		183,	184,	183,	184,
V_matches,	69,	85,	78,	121,
V_ring,		87,	135,	127,	105,
V_ruby,		99,	106,	114,	74,
V_coin,		127,	127,	87,	87,
V_bill,		135,	87,	135,	127,
V_pills,	85,	83,	91,	78,
V_saphire,	91,	78,	85,	69,
V_emerald,	68,	74,	117,	66,
V_letter,	177,	177,	177,	177,
V_torch,	92,	114,	66,	53,
V_cube,		202,	202,	202,	202,
V_wrapper,	171,	216,	239,	101,
V_tire,		47,	47,	47,	47,
V_shell,	82,	107,	213,	175,
V_brick,	33,	33,	33,	33,
V_rope,		209,	179,	181,	155,
V_package,	156,	137,	95,	113,
V_belt,		21,	21,	21,	21,
V_filter,	142,	142,	142,	142,
V_string,	204,	88,	118,	167,
V_umbrella,	37,	37,	37,	37,
V_tackle,	9,	9,	9,	9,
V_bit,		105,	117,	90,	184,
V_jack,		81,	81,	81,	81,
V_pen,		177,	177,	177,	177,
V_pencil,	202,	202,	202,	202,
V_wire,		214,	154,	159,	151,
V_pipe,		206,	239,	166,	151,
V_opener,	63,	62,	61,	60,
V_cord,		80,	131,	119,	79,
V_photo,	206,	160,	155,	180,
V_chair,	177,	177,	177,	177,
V_bulb,		154,	162,	164,	181,
V_rag,		92,	89,	73,	132,
V_tube,		139,	121,	129,	132,
V_carpet,	41,	41,	41,	41,
V_branch,	28,	28,	28,	28,
V_cork,		130,	122,	115,	109,
V_trap,		146,	146,	146,	146,
V_lighter,	210,	213,	46,	79,
V_lace,		126,	136,	67,	72,
V_comb,		164,	157,	156,	172
} ;

/************************************************/
/*           --- Monster Types ---		*/
/*                                              */
/*   Monster Type       			*/
/*      = 0 = N_ned = Ned Kelly			*/
/*      = 1 = N_wombat = Mutant Wombat		*/
/*      = (2 - 5) = Drop Bears (four total)	*/
/*      = (6 - 13) = Hoop Snakes (eight total)	*/
/*      = 14 = Revolutionary Guards             */
/*      = 15 = Chief Mullah                    	*/
/*                                              */
/************************************************/
struct monster_struct *monster_start ;
struct monster_struct *Ned ;
struct monster_struct *Guards ;
struct monster_struct *Wombat ;
struct monster_struct *Mullah ;

int score = 0 ;
int monster_flag = F_no_monster ;
int carry_count, carry_weight ;
long l_time, start_time ;
#endif

/***************************************************************/

#ifdef OBJLKR
extern int tag[DM_tag] ;
extern int sw_warned, score, max_score, sw_wizard ;
extern struct monster_struct *Ned ;

/* a switch used in the "kelly" subroutine */
int sw_valuable = FALSE ;

/* layout matrix for game */
/*   n = room number      */ 

/*   The direction elements contain the adjoining room or a wall */
/*   if the element value is negative.                           */
/*     room[n][0] = north direction      */
/*     room[n][1] = south direction      */
/*     room[n][2] = east direction       */
/*     room[n][3] = west direction       */
/*     room[n][4] = up direction         */
/*     room[n][5] = down direction       */
/*     room[n][6] = north-east direction */
/*     room[n][7] = north-west direction */
/*     room[n][8] = south-east direction */
/*     room[n][9] = south-west direction */

/*  room[n][10] points to the room type                      */
/*               = -1 == instantly lethal                    */
/*               =  0 == short description                   */
/*               =  1 == long description                    */
/*               =  2 == contains an action device           */
/*               =  3 == orignally had a long description    */
/*               =  5 == room goes into itself (looping)     */
/*  room[n][11] flag indicates number of objects in room.    */
/*  room[n][12] is a switch which if TRUE indicates there    */
/*              are unmovable objects present in the room.   */
/*  room[n][13] is the monster indicater, 0 = no monsters    */
/*  room[n][14] is the gleep count                           */
/*  room[n][15] points to the description text file          */

int room [DM_room][16] = {
  3,  2,  1, 15, -1, -1,  1, 15,  3,  2,  0,  0,  0,  0,  0,  0, 
  6,  2, 20,  0, -1, -1,  0,  3,  0,  2,  0,  0,  0,  0,  0,  1,
 28, 11, 29,148, -1, -1, 29, 11, 28,148,  0,  0,  0,  0,  0,  2, 
  4,  0,  6,  4, -1, -1,  2,  1,  4,  2,  0,  0,  0,  0,  0,  3, 
  5,  9,  4,  4, -1, -1,  5,  5,  9,  9,  5,  0,  0,  0,  0,  4,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  5,
  3, 14, 47,  3, -1, -1,  2,  3, 14,  3,  1,  0,  0,  0,  0,  6,
 14,  8, 14,  8, -1, -1, 14, 14,  8,  8,  0,  0,  0,  0,  0,  7,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  8,
  4,  1,  6,  4, -1, -1,  0,  2,  0,  1,  0,  0,  0,  0,  0,  9, 
 14,  6, 14,  3, -1, -1,  6, 14,  6, 14,  0,  0,  0,  0,  0, 10,
 28, 12, 28, 12, -1, -1, 12, 28,  3,  6,  1,  0,  0,  0,  0, 11,
 11, 13, 12, 13, -1, -1, 13, 12, 11, 13,  5,  0,  0,  0,  0, 12,
 13, 13, 13, 13, -1, -1, 13, 13, 13, 12,  5,  0,  0,  0,  0, 13,
  6,  7,  7, 10, -1, -1,  6, 10,  7,  7,  0,  0,  0,  0,  0, 14,
147,148,  0, 16, -1, -1,  0,147,  0,148,  0,  0,  0,  0,  0, 15,
 19, 19, 16, 17, -1, -1, 19, 19, 17, 17,  5,  0,  0,  0,  0, 16,
 16, 16, 16, 18, -1, -1, 16, 16, 18, 16,  0,  0,  0,  0,  0, 17,
 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 18,
  3,  2,  0, 16, -1, -1,  0, 16,  2, 16,  0,  0,  0,  0,  0, 19,
 21,142, 22,  1, -1, -1, 23,  2,141,  1,  0,  0,  0,  0,  0, 20,
 42, 20,145, 47, -1, -1,145,  1,145,  6,  0,  0,  0,  0,  0, 21,
 36, 27, -1, 20, -1, -1, -1, 20, -1, 20,  1,  0,  0,  0,  0, 22,
 25, 24, 25,145, -1, -1, 25,145, 25, 34,  4,  0,  0,  0,  0, 23,
 23, 26, 25, 33, -1, -1, 25, 33, 25, 32,  0,  0,  0,  0,  0, 24,
 25, 25, 25, 25, -1, -1,143, 23, 25, 26,  5,  0,  0,  0,  0, 25,
 24, 25, 25,141, -1, -1, 25, 31, 25,141,  4,  0,  0,  0,  0, 26,
 22, 30, -1, 20, -1, -1, -1, 20, -1, 20,  2,  0,  0,  0,  0, 27,
  0,  2, 29,148, -1, -1, 29, 11,  0,  2,  0,  0,  0,  0,  0, 28, 
142,243,141,  2, -1, -1,141,  2,141,  2,  1,  0,  0,  0,  0, 29,
 27,141, 31, 20, -1, -1, -1, 20,141,141,  0,  0,  0,  0,  0, 30,
 32,141, 24, 30, -1, -1, 24, -1, 26,141,  0,  0,  0,  0,  0, 31,
 33, 31, 24, -1, -1, -1, 24, -1, 24, -1,  0,  0,  0,  0,  0, 32,
 34, 32, 24, -1, -1, -1, 24, -1, 24, -1,  0,  0,  0,  0,  0, 33,
145, 33, 24, 35, -1, -1, 23,145, 24, -1,  0,  0,  0,  0,  0, 34,
145, 36, 34, 20, -1, -1,145,145, -1, 20,  0,  0,  0,  0,  0, 35,
 35, 22, -1, 20, -1, -1, 35, 20, -1, 20,  2,  0,  0,  0,  0, 36,
 38, 39, -1, 36, -1, -1, 38, 36, 39, 36,  0,  0,  0,  0,  0, 37,
 -1, 37, -1, -1, -1, -1, -1, -1, -1, 37,  1,  0,  0,  0,  0, 38,
 37, -1, 41, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0, 39,
 -1, 41, -1, -1, -1, -1, -1, -1, -1, 41,  2,  0,  0,  0,  0, 40,
 40, -1, -1, 39, -1, -1, 40, -1, -1, -1,  4,  0,  0,  0,  0, 41,
246, 21,145,  6, -1, -1,145,  1,145,  6,  0,  0,  0,  0,  0, 42,
 -1, -1, -1, 27, -1, -1, -1, 27, -1, -1,  1,  0,  0,  0,  0, 43,
 -1, -1, 43, 48, -1, -1, -1, -1, 43, -1,  0,  0,  0,  0,  0, 44,
 -1,204, 43,149, -1, -1, -1, -1, 43, -1,  0,  0,  0,  0,  0, 45,
239, -1, 43, -1, -1, -1, -1, -1, 43, -1,  0,  0,  0,  0,  0, 46,
  3, 20, 21,  6, -1, -1, 21,  3, 20,  6,  0,  0,  0,  0,  0, 47, 
 49, 50, 44, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48, /*48*/
 51, 48, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55, /*49*/
 48, 56, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55, /*50*/
 -1, 49, 52, 53, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 51, /*51*/
 -1, -1, 54, 51, -1, 88, -1, -1, -1, -1,  0,  0,  0,  0,  0, 59, /*52*/
 -1, -1, 51, 55, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56, /*53*/
 -1, -1, -1, 52, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 91, /*54*/
 -1, -1, 53, -1, 57, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 62, /*54*/
 50, -1, -1, -1, -1, -1, -1, -1, 74, 72,  0,  0,  0,  0,  0, 64, /*56*/
 -1, -1, -1, -1, -1, 55, -1, 58, -1, 59,  0,  0,  0,  0,  0, 76, /*57*/
 -1, -1, -1, -1, -1, -1, -1, 60, 57, -1,  0,  0,  0,  0,  0, 57, /*58*/
 -1, -1, -1, -1, -1, -1, 57, -1, -1, 61,  0,  0,  0,  0,  0, 58, /*59*/
 -1, -1, -1, -1, -1, -1, -1, -1, 58, 62,  0,  0,  0,  0,  0, 84, /*60*/
 -1, -1, -1, -1, -1, -1, 59, 63, -1, -1,  0,  0,  0,  0,  0, 87, /*61*/
 -1, -1, -1, -1, -1, -1, 60, -1, -1, 64,  0,  0,  0,  0,  0, 58, /*62*/
 -1, -1, -1, -1, -1, -1, -1, 64, 61, -1,  0,  0,  0,  0,  0, 57, /*63*/
 -1, -1, -1, -1, -1, 65, 62, -1, 63, -1,  0,  0,  0,  0,  0, 77, /*64*/
 -1, 66, -1, -1, 64, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 61, /*65*/
 65, 67, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55, /*66*/
 66, 69, 68, 70, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 78, /*67*/
 -1, -1, 71, 67, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56, /*68*/
 67, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 92, /*69*/
121,128, 67, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48, /*70*/
 -1, -1, -1, 68, -1, -1, 72, -1, 73, -1,  0,  0,  0,  0,  0, 66, /*71*/
 -1, -1, -1, -1, -1, -1, 56, -1, -1, 71,  0,  0,  0,  0,  0, 58, /*72*/
 -1, -1, -1, -1, -1, -1, -1, 71, 75, -1,  0,  0,  0,  0,  0, 57, /*73*/
 -1, -1, -1, -1, -1, -1, -1, 56, 77, -1,  0,  0,  0,  0,  0, 57, /*74*/
 -1, -1, -1, -1, -1, -1, 76, 73, -1, 80,  0,  0,  0,  0,  0, 52, /*75*/
 -1, -1, -1, -1, -1, -1, 77, -1, -1, 75,  0,  0,  0,  0,  0, 58, /*76*/
 -1, -1, -1, -1, -1, -1, 79, 74, 78, 76,  0,  0,  0,  0,  0, 79, /*77*/
 -1, -1, -1, -1, -1, -1, -1, 77, -1, -1,  0,  0,  0,  0,  0, 90, /*78*/
 -1, -1, -1, -1, -1, -1,108, -1, -1, 77,  0,  0,  0,  0,  0, 58, /*79*/
 -1, -1, 81, 82, -1, -1, 75, -1, -1, -1,  0,  0,  0,  0,  0, 74, /*80*/
 -1, -1, -1, 80, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 93, /*81*/
 -1, -1, 80, 83, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56, /*82*/
 -1, 84, 82, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81, /*83*/
 83, -1, 85, 86, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 50, /*84*/
 -1, -1, -1, 84, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90, /*85*/
 87, -1, 84, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 83, /*86*/
 -1, 86, -1,109, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 94, /*87*/
 -1, -1, -1, -1, 52, -1, 92, -1, -1, 89,  0,  0,  0,  0,  0, 96, /*88*/
 -1, -1, -1, -1, -1, -1, 88, -1, -1, 90,  0,  0,  0,  0,  0, 58, /*89*/
 -1, -1, -1, -1, -1, -1, 89, -1, -1, 91,  0,  0,  0,  0,  0, 58, /*90*/
 -1, -1, -1, -1, -1, -1, 90, -1, -1, -1,  0,  0,  0,  0,  0, 90, /*91*/
 -1, -1, -1, -1, -1, -1, 93, -1, -1, 88,  0,  0,  0,  0,  0, 58, /*92*/
 -1, -1, -1, -1, -1, -1, -1, 94, 95, 92,  0,  0,  0,  0,  0, 95, /*93*/
 -1, -1, -1, -1, 96, -1, -1, -1, 93, -1,  0,  0,  0,  0,  0, 60, /*94*/
 -1, -1, -1, -1, -1, -1, -1, 93,104, -1,  0,  0,  0,  0,  0, 57, /*95*/
 97, -1,103, -1, -1, 94, -1, -1, -1, -1,  0,  0,  0,  0,  0, 97, /*96*/
 98, 96, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55, /*97*/
 -1, 97, 99, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81, /*98*/
 -1, -1,100, 98, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56, /*99*/
 -1,101, -1, 99, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*100*/
100,102, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*101*/
101, -1, -1,103, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*102*/
 -1, -1,102, 96, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*103*/
 -1, -1, -1, -1, -1, -1, -1, 95,105, -1,  0,  0,  0,  0,  0, 57,/*104*/
 -1, -1, -1, -1, -1, -1, -1,104, -1,106,  0,  0,  0,  0,  0, 86,/*105*/
 -1, -1, -1, -1, -1, -1,105, -1, -1,107,  0,  0,  0,  0,  0, 58,/*106*/
 -1, -1, -1, -1, 79, -1,106, -1, -1, -1,  0,  0,  0,  0,  0, 89,/*107*/
 -1, -1, -1, -1, -1,106, -1, -1, -1, 79,  0,  0,  0,  0,  0, 88,/*108*/
 -1, -1, 87,110, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*109*/
 -1, -1,109, -1, -1,140, -1, -1, -1, -1,  0,  0,  0,  0,  0, 99,/*110*/
 -1, -1, -1,140,109, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 98,/*111*/
 -1, -1,140, -1,113, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 62,/*112*/
114, -1, -1, -1, -1,112, -1, -1, -1, -1,  0,  0,  0,  0,  0,100,/*113*/
115,113, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*114*/
 -1,114,118,116, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 51,/*115*/
 -1,117,115, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81,/*116*/
116, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,101,/*117*/
 -1, -1,119,115, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*118*/
 -1,125,120,118, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 51,/*119*/
 -1,122, -1,119, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*120*/
 -1, 70, -1,122, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*121*/
120,123,121, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*122*/
122, -1, -1,124, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*123*/
 -1, -1,123, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*124*/
119, -1, -1,126, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*125*/
 -1,127,125, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81,/*126*/
126, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*127*/
 70, -1, -1,129, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*128*/
130,136,128, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*129*/
 -1,129, -1,131, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*130*/
134,132,130, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*131*/
131, -1, -1,133, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*132*/
 -1, -1,132, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*133*/
 -1,131, -1,135, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*134*/
 -1, -1,134, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*135*/
129, -1, -1,137, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*136*/
 -1, -1,136,138, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*137*/
139, -1,137, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 83,/*138*/
 -1,138, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*139*/
 -1, -1,111,112, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*140*/
 30, 26, 26,142, -1, -1, 24, 20, 26,142,  0,  0,  0,  0,  0,102,/*141*/
 20, 29,141,  2, -1, -1,141,  2,141,  2,  0,  0,  0,  0,  0,103,/*142*/
 25, 25, 25, 25, -1, -1, 25, 25,144, 25,  0,  0,  0,  0,  0,104,/*143*/
143,143,146,143, -1, -1,143,143,143,143,  1,  0,  0,  0,  0,105,/*144*/
 23, 35, 23, 21, -1, -1, 23, 21, 35, 34,  0,  0,  0,  0,  0,106,/*145*/
 -1, -1, -1,144, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,107,/*146*/
  3, 15,  3,  3, -1, -1,  3,  3, 15, 15,  1,  0,  0,  0,  0,108,/*147*/
 15,  2,  2, 15, -1, -1, 15, 15,  2,  2,  0,  0,  0,  0,  0,109,/*148*/
 -1, -1, 45, -1, -1,150, -1, -1, -1, -1,  0,  0,  0,  0,  0,110,/*149*/
 -1,151, -1, -1,149, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 61,/*150*/
150,152, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*151*/
151,153, -1,159, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*152*/
152,154, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*153*/
153, -1, -1,155, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*154*/
 -1, -1,154,156, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*155*/
157, -1,155, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 83,/*156*/
158,156, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*157*/
 -1,157,159,160, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 51,/*158*/
 -1, -1,152,158, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,132,/*159*/
 -1, -1,158,161, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*160*/
 -1, -1,160,162, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*161*/
 -1, -1,161,163, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*162*/
 -1, -1,162,164, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*163*/
 -1, -1,163,165, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*164*/
 -1, -1,164, -1, -1,166, -1, -1, -1, -1,  0,  0,  0,  0,  0,110,/*165*/
 -1, -1,167,178,165, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0,111,/*166*/
168, -1, -1,166, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 82,/*167*/
169,167, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*168*/
170,168, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*169*/
 -1,169, -1, -1,171, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 61,/*170*/
 -1, -1,172, -1, -1,170, -1, -1, -1, -1,  0,  0,  0,  0,  0,110,/*171*/
 -1, -1,173,171, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*172*/
 -1, -1,174,172, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*173*/
 -1, -1,175,173, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*174*/
 -1, -1,176,174, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*175*/
 -1, -1,177,175, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*176*/
 -1, -1, -1,176, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,112,/*177*/
 -1, -1,166,179, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*178*/
 -1, -1,178,180, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*179*/
 -1,181,179, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81,/*180*/
180,182, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*181*/
181,185,184,183, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 78,/*182*/
 -1, -1,182, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*183*/
 -1, -1, -1,182, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*184*/
182, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*185*/
185,187, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*186*/
186,189,190,188, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 78,/*187*/
 -1, -1,187, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*188*/
187, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 90,/*189*/
 -1, -1,191,187, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 56,/*190*/
192,198, -1,190, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,113,/*191*/
 -1,191, -1, -1, -1, -1,193, -1, -1, -1,  1,  0,  0,  0,  0,114,/*192*/
 -1, -1, -1, -1, -1, -1, -1, -1,194,192,  1,  0,  0,  0,  0,115,/*193*/
 -1,195, -1, -1, -1, -1, -1,193, -1, -1,  1,  0,  0,  0,  0,116,/*194*/
194,196, -1, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,117,/*195*/
195, -1, -1, -1,199, -1, -1, -1, -1,197,  1,  0,  0,  0,  0,118,/*196*/
 -1, -1, -1, -1, -1, -1,196,198, -1, -1,  1,  0,  0,  0,  0,119,/*197*/
191, -1, -1, -1, -1, -1, -1, -1,197, -1,  1,  0,  0,  0,  0,120,/*198*/
200, -1, -1, -1, -1,196, -1, -1, -1, -1,  1,  0,  0,  0,  0,121,/*199*/
 -1,199,201,202, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,122,/*200*/
 -1, -1, -1,200, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,123,/*201*/
 -1, -1,200,203, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,124,/*202*/
 -1, -1,202, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,125,/*203*/
 45,205, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 55,/*204*/
204, -1,206, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 83,/*205*/
 -1, -1, -1,205, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,126,/*206*/
 -1,208,227, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81,/*207*/
207,209,226, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*208*/
208,210,225, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*209*/
209,211,224, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*210*/
210,217,223, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*211*/
217,213,222, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*212*/
212,214,221, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*213*/
213,215,220, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*214*/
214,216,219, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 48,/*215*/
215, -1,218, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 83,/*216*/
211,212, -1,239, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,128,/*217*/
 -1, -1,237,216, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*218*/
 -1, -1,236,215, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*219*/
 -1, -1,235,214, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*220*/
 -1, -1,234,213, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*221*/
 -1, -1,233,212, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*222*/
 -1, -1,232,211, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*223*/
 -1, -1,231,210, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*224*/
 -1, -1,230,209, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*225*/
 -1, -1,229,208, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*226*/
 -1, -1,228,207, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0, 56,/*227*/
 -1,229, -1,227, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 80,/*228*/
228,230, -1,226, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*229*/
229,231, -1,225, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*230*/
230,232, -1,224, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*231*/
231,233, -1,223, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*232*/
232,234, -1,222, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*233*/
233,235, -1,221, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*234*/
234,236, -1,220, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*235*/
235,237, -1,219, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*236*/
236,238, -1,218, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 49,/*237*/
237, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,127,/*238*/
 -1, 46,217, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,  0, 81,/*239*/
241, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,129,/*240*/
 -1,240,242, -1, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,130,/*241*/
 -1, -1, -1,241, -1, -1, -1, -1, -1, -1,  1,  0,  0,  0,  0,131,/*242*/
 29,244,141,  2, -1, -1,141,  2,141,  2,  4,  0,  0,  0,  0,133,/*243*/
243,245,141,  2, -1, -1,141,  2,141,  2,  0,  0,  0,  0,  0,134,/*244*/
244, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,135,/*245*/
247, 42,145,  6, -1, -1,145,  1,145,  6,  4,  0,  0,  0,  0,136,/*246*/
248,246,145,  6, -1, -1,145,  1,145,  6,  0,  0,  0,  0,  0,134,/*247*/
 -1,247, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  0,  0,  0,135 /*248*/
};
 
/*****************************************************************/
/*                                                               */
/*                   --- Object Matrix ---                       */
/*                                                               */
/*  Location  = room location if =>0, else =-1 is in possesion   */
/*              of player, = -2 means unmade, = -3 means it is   */
/*              destroyed, = -5 means the object is in the safe. */ 
/*  Value     = object's value                                   */
/*  Type      = external property of the object                  */
/*                  = 1  indicates special action on taking      */
/*                  = 2  alias				         */
/*                  = 3  unmovable object which has no actions   */
/*  ID        = object parse id name                             */
/*  Weight    = object's weight                                  */
/*  Status    = internal property of the object                  */
/*  Text      = Character string describing object               */
/*                                                               */
/*****************************************************************/

struct object_struct object[Objcnt] = {
{ 0,        0,           0,  	V_can,		10,	0,		
	"an empty can of Fourex beer"},
{ 0,        0,           0,  	V_butt,		1, 	0,
	"a cigarette butt"},
{ 0,	    0,           0,  	V_bottle,	20, 	0,
	"an empty bottle of Black Swan Lager"},
{36,	    0, Z_transform,  	V_mat, 		300, 	0,
	"an old doormat with \"ACME Gold Mines Ltd.\" written on it"},
{B_unmade,  0,           0,  	V_key, 		5, 	0,
	"a large brass key"},
{ 0,        0,	         0,	V_umbrella,	100, 	0,
	"a ripped and bent up umbrella"},
{ 0,        0,	         0,	V_tackle, 	50, 	0,
	"a two metre length of fishing tackle without a hook"},
{ 0,        0,	         0,	V_bit, 		10, 	0,
	"a broken drill bit"},
{38,        0, Z_transform,  	V_map,		10, 	0,
	"a very old but detailed map of the ACME Mine"},
{B_unmade,  0,           0,  	V_map_frag,	10, 	0,
	"a fragment of a map showing the ACME Mine"},
{B_in_safe, 0,           0,  	V_paper,	10, 	0,
	"a sheet of paper with some writing on it"},
{ 0,      200,           0,	V_gold, 	500, 	0,
	"a gold bar weighing ten kilograms"},
{ 0,        0,	         0,	V_jack,		400, 	0,
	"a hydraulic jack which is rusted solid"},
{ 0,        0,	         0,	V_dynamite,	100, 	0,
	"a large stick of dynamite"},
{ 0,        0,           0,	V_clip, 	50, 	150,
	"an M16 ammo clip designed to hold up to 200 rounds"},
{ 0,        0,	         0,	V_pen, 		5, 	0,
	"a fountain pen which is dried up and useless"},
{ 0,        0,           0,	V_org_clip,	50, 	5,
	"an orange M16 ammo clip which is glowing a faint pale blue"},
{ 0,        0,	         0,	V_pencil, 	5, 	0,
	"a mechanical pencil without any leads"},
{ 0,        0,           0,	V_rifle, 	300, 	0,  /* don't modify */
	"an unloaded, fully automatic M16 infantry rifle"},
{ 0,        0,	         0,	V_wire, 	100, 	0,
	"a piece of copper wire"},
{ 0,        0,	         0,	V_pipe,		200, 	0,
	"a short length of galvanized iron pipe"},
{ 0,        0,           0,	V_cap,		5, 	0,
	"a blasting cap with 20 cm. of fuse attached"},
{ 0,        0,           0,  	V_matches,	2, 	0,
	"a box of \"Red Head\" matches"},
{ 0,      100,           0,  	V_ring, 	5, 	0,
	"a diamond ring with a three carat flawless blue diamond"},
{ 0,        0,	         0,	V_opener,	10, 	0,
	"a can opener"},
{ 0,      100,           0,  	V_ruby, 	30, 	0,
	"a bright red ruby the size of an egg"},
{B_unmade,200,           0,  	V_teapot,	50, 	0,
	"an antique sterling silver teapot with \"N.K.\" engraved on it"},
{ 0,      150,           0,  	V_coin, 	7, 	0,
	"a silver Syracusian Dekadrachma coin"},
{ 0,        0,	         0,	V_cord,		70, 	0,
	"an electrical extension cord"},
{ 0,      100,           0,	V_bill,		5, 	0,
	"a $100 dollar bill"},
{ 0,        0,	         0,	V_photo,	5, 	0,
	"an autographed photo of Sir Joh"},
{ 0,        0,           0,	V_chair,	500, 	0,
	"an old folding chair"},
{ 0,        0,           0,	V_bulb,		10, 	0,
	"a burned out light bulb"},
{ 0,        0,	         0,  	V_pills,	10, 	0,
	"a packet containing atropine pills"},
{ 0,      150,           0,  	V_saphire,	30, 	0,
	"a high quality artificial saphire"},
{ 0,      100,           0,	V_emerald,	30, 	0,
	"a huge uncut emerald"},
{ 0,        0,	         0,	V_rag, 	 	50, 	0,
	"an oily rag"},
{ 0,        0,	         0,	V_tube,		50, 	0,
	"a burned out fluorescent tube"},
{ 0,        0,	         0,	V_carpet,	400, 	0,
	"a filthy worn out carpet"},
{ 0,        0,	         0,	V_branch,	400, 	0,
	"a branch from a gum tree"},
{ 0,        0,	         0,  	V_letter,	10, 	0,
	"a thick airmail letter, marked \"Postage Due\""},
{ 0,        0,	         0,	V_cork, 	5, 	0,
	"a cork from a wine bottle"},
{ 0,        0,	         0,  	V_torch,	100, 	0,
	"a high intensity battery powered torch"},
{ 0,        0,	         0,	V_trap,		5, 	0,
	"an old cockroach trap"},
{ 0,        0,	         0,	V_lighter,	5, 	0,
	"an empty butane cigarette lighter"},
{ 0,        0,	         0,  	V_cube, 	50, 	0,
	"a small black cube with a blue push button on one side"}, 
{B_unmade,700,           0,  	V_clapper,	100, 	0,
	"an ancient and priceless gong clapper made of ivory and gold"},
{B_unmade,  0,           0,  	V_detector,	100, 	0,
	"a Semtex explosive detector with a push button switch"},
{ 0,        0,	         0,	V_lace,		2, 	0,
	"a broken shoe lace"},
{ 0,        0,	         0,	V_comb,		5, 	0,
	"a dirty old comb"},
{ 0,        0,	         0,	V_wrapper,	3, 	0,
	"a Cornetto ice cream cone wrapper"},
{ 0,        0,	         0,	V_tire,		400, 	0,
	"a bald automobile tyre"},
{ 0,        0,	         0,	V_shell,	3, 	0,
	"an empty broken egg shell"},
{ 0,        0,	         0,	V_brick,	100, 	0,
	"a broken piece of brick"},
{ 0,        0,	         0,	V_rope,		100, 	0,
	"a one metre length of rope"},
{ 0,        0,	         0,	V_package,	5, 	0,
	"an empty package of Stradbroke cigarettes"},
{ 0,        0,	         0,	V_belt,		10, 	0,
	"a broken automobile fan belt"},
{ 0,        0,	         0,	V_filter,	50, 	0,
	"a used automobile oil filter"},
{ 0,        0,	         0,	V_string,	5,	0,
	"a short piece of string"},
{B_unmade,  0,           0,  	V_recorder,	0, 	S_inactive,
	"a data recorder having three coloured buttons"},
{ 39,       0, Z_unmovable,	V_poster,	0,	0,
	"Error"},
{ 41,       0, Z_unmovable,	V_poster,	0,	0,
	"Error"},
{ 39,       0, Z_unmovable,	V_cockroach,	0,	0,
	"Error"},
{ 41,       0, Z_unmovable,	V_cockroach,	0,	0,
	"Error"},
{243,       0, Z_unmovable,	V_kangaroo,	0,	0,
	"Error"},
{246,       0, Z_unmovable,	V_kangaroo,	0,	0,
	"Error"},
{ 26,       0, Z_unmovable,	V_spinifex,	0,	0,
	"Error"},
{R_gong,    0, Z_unmovable,	V_gong, 	0,	S_fair_game,
	"Error"},
{ 23,       0, Z_unmovable,	V_bulldust,	0,	0,
	"Error"},
{159,       0, Z_unmovable,	V_message,	0,	0,
	"Error"},
{R_store_room,  0, Z_unmovable,	V_circuit,	0,	FALSE,
	"Error"},
{R_lift_inside, 0, Z_unmovable,	V_lift,		0,	L0,
	"Error"},
{R_office_entr, 0, Z_unmovable,	V_door,		0,	S_closed,
	"Error"},
{R_office_mang, 0, Z_unmovable,	V_safe,		0,	S_closed,
	"Error"},
{R_lift_entr,	0, Z_unmovable,	V_lift_door,	0,	S_closed,
	"Error"},
{R_office_mang, 0, Z_unmovable,	V_picture,	0,	S_closed,
	"Error"},
{R_gleep_tank,	0, Z_unmovable,	V_tank,		0,	0,
	"Error"},
{R_transporter,	0, Z_unmovable,	V_transporter,	0,	FALSE,
	"Error"},
{R_warning,     0, Z_unmovable,	V_warning,	0,	0,
	"Error"},
{R_office_mang, 0, Z_unmovable,	V_chart,	0,	0,
	"Error"},
{R_office_mang, 0, Z_unmovable,	V_desk,		0,	0,
	"Error"},
{R_foreman,	0, Z_unmovable,	V_desk,		0,	0,
	"Error"}
} ; 	

#endif

/***************************************************************/

#ifdef DSCRB
int pill_count = 7 ;
extern int room[DM_room][16] ;
extern int sw_active ;
int rifle_flag = F_safety ;
extern int clip_flag ;
extern struct object_struct object[Objcnt] ;
extern struct monster_struct *Ned ;

#endif

/***************************************************************/

#ifdef PUSHER
/* subroutines: new_score, pusher, switcher */
extern int room[DM_room][16] ;
extern int tag[DM_tag] ;
extern struct object_struct object[Objcnt] ;
extern int monster_flag, rifle_flag ;
extern int verb, score;
extern long l_time, start_time ;

FILE *fp ;
#endif

/***************************************************************/

#ifdef LONG_DESCP
extern int room[DM_room][16] ;
extern struct object_struct object[Objcnt] ;
extern int monster_flag ;

#endif

/***************************************************************/

#ifdef ACTOR
extern int room[DM_room][16], tag[DM_tag] ;
extern int gleep_safe, verb ;
extern struct object_struct object[Objcnt] ;
extern int clip_flag, rifle_flag, monster_flag ;
extern struct monster_struct *Ned ;
extern struct monster_struct *Wombat ;
extern struct monster_struct *monster_start ;

#endif

/***************************************************************/

#ifdef MNSTR
extern int room[DM_room][16] ;
extern struct object_struct object[Objcnt] ;
extern int monster_flag ;
extern int carry_count, carry_weight ;
extern struct monster_struct *Ned ;
extern struct monster_struct *Wombat ;
extern struct monster_struct *Guards ;
extern struct monster_struct *Mullah ;
extern struct monster_struct *monster_start ;

#endif

/***************************************************************/

#ifdef OPNR
int sw_active = FALSE ;
extern int room[DM_room][16] ;
extern struct object_struct object[Objcnt] ;
extern int sent[20];
extern int gleep_count, gleep_safe ;
extern int tag[DM_tag] ;
extern int sw_active ;
extern int pill_count ;
extern int gleep_spot[10] ;
extern int score, clip_flag ;
extern int carry_count, carry_weight ;
extern long clock_explode ;
extern int flag_clock, sw_clock, i_poison ;

struct read_struct read_object[Read_objcnt] = {
	{V_map_frag,	TRUE }, 
	{V_can,		FALSE }, 
	{V_recorder,	FALSE }, 
	{V_pills,	FALSE }, 
	{V_letter,	TRUE },
	{V_paper,	TRUE }, 
	{V_cube,	FALSE }, 
	{V_clip,	FALSE }, 
	{V_org_clip,	FALSE }, 
	{V_rifle,	FALSE }, 
	{V_detector,	FALSE }, 
	{V_safe,	FALSE }, 
	{V_gong,	FALSE },
	{V_message,	TRUE },
	{V_warning,	TRUE }
} ; 

#endif
  
/***************************************************************/

#ifdef PARSE
int sent[20], number_word ;
extern int verb ;
extern int sw_wizard ; 
extern int room[DM_room][16] ;
extern struct object_struct object[Objcnt] ;
extern struct read_struct read_object[Read_objcnt] ;
int tag[DM_tag] ;
extern FILE *fp ;

/* Game vocabulary */
char *vocab[Vocab_cnt] = {
"north","south","east","west","up",
"down","northeast","northwest","southeast","southwest",
"n","s","e","w","u",                            /* "u"          = 15 */
"d","ne","nw","se","sw",                        /* "sw"         = 20 */
"quit","unlock","lock","take","leave",          /* "leave"      = 25 */
"drop","can","bottle","mat","key",              /* "key"        = 30 */
"butt","look","door","open","get",              /* "get"        = 35 */
"throw","turn","on","off","push",               /* "push"       = 40 */
"button","enter","switch","zero","forty-nine",  /* "forty-nine" = 45 */
"sixty-seven","eighty-two","0","49","67",       /* "67"         = 50 */
"82","beer","lager","doormat","lift",           /* "lift"       = 55 */ 
"'on'","'off'","SVC","map","picture",           /* "picture"    = 60 */
"safe","dial","paper","put","close",            /* "close"      = 65 */
"read","gold","bar","dynamite","rifle",         /* "rifle"      = 70 */
"M16","m16","cap","matches","diamond",          /* "diamond"    = 75 */
"ring","ruby","silver","coin","bill",           /* "bill"       = 80 */
"money","teapot","clip","ammo","box",           /* "box"        = 85 */
"stick","pills","orange","glowing","saphire",   /* "saphire"    = 90 */
"emerald","score","inventory","examine","describe",
"drink","fill","water","fourex","invent",	/* "invent"	= 100 */
"view","press","exit","all","Fourex",		/* "Fourex"	= 105 */
"everything","shoot","kill","ned","Ned",	/* "Ned"	= 110 */
"kelly","Kelly","pick","grab","combination",	/* "combination"= 115 */
"select","safety","SAFE","triple","III",	/* "III"	= 120 */
"single","I","auto","AUTO","automatic",		/* "automatic"	= 125 */
"set","insert","attach","plan","gun",           /* "gun"        = 130 */
"magazine","hoop","snake","bear","wombat",	/* "wombat"     = 135 */
"remove","eject","org_clip","shut","gleep",	/* "gleep"	= 140 */
"gleeps","letter","envelope","torch","mail",	/* "mail"       = 145 */
"tank","carefully","gently","softly","slow_drop",
"light","ignite","fuse","slowly","match",	/* "match"	= 155 */
"cube","blue","blue-button","gray","gray-button",
"clapper","sound","bang","hit","strike",	/* "strike"	= 160 */
"gong","detector","give","STATS","JSYS",
"SU","yellow","yellow-button","poster","eat",
"swallow","pill","atropine","packet","wrapper",
"tyre","shell","brick","rope","package",
"belt","filter","string","cabinet","calendar",
"tackle","bit","jack","pen","pencil",
"wire","pipe","panel","opener","cord",
"photo","chair","bulb","rag","tube",		/* "tube"	= 200 */
"carpet","branch","cork","trap","lighter",
"lace","comb","umbrella","meadow","billabong",
"river","road","forest","grass","stream",
"desert","building","office","hideout","dust",
"mine","tunnel","tree","spinifex","hexagon",
"spacecaft","airlock","wing","hole","tray",
"liquid","cockroach","go","scream","yell",
"bring","help","dump","attack","check",
"inspect","place","touch","pull","extinguish",
"ask","talk","tell","find","move",		/* "move"	= 250 */
"break","kick","smash","feed","taste",
"smell","slam","desk","in","into",
"under","out","from","by","with",
"fling","what","where","are","am",		/* "am"		= 275 */
"have","qUeStIoN","how","why","who",		/* "who"	= 280 */
"when","leap","walk","run","jump",		/* "jump"       = 285 */
"hop","stroll","saunter","swagger","swing",	/* "swing"    	= 290 */
"dig","swim","depart","info","back",		/* "back"	= 295 */
"hold","fire","stand","painting","doors",	/* "doors"	= 300 */
"treasure","trigger","load","unload","sand",	/* "sand"	= 305 */
"cockroaches","kangaroo","climb","bulldust","kangaroos",
"spinifexes","fuze","message","wall","recorder",
"red","white","green","red-button","white-button",
"green-button","grey","matchbox","map","circuit",   /* "map" is "map_frag" */
"lift-door","transporter","warning","explosive","self",
"myself","yourself","one","two","three",
"four","five","toss","chart","charts","schedule",
"schedules","orange-button"
};

/* Question Table */
int quest[Quest_max] = {
V_what, V_where, V_are, V_am, V_have,
V_how, V_why, V_who, V_when
} ;

/* Adjective Table */
struct adjective_struct adjective[Adj_max] = {
{ V_drop, V_bear,F_ignore,F_ignore},		/* drop bear */
{ V_gold, V_bar,F_ignore,F_ignore},		/* gold bar */
{ V_orange,V_clip,V_org_clip,F_replace},	/* orange clip */
{ V_glowing, V_clip, V_org_clip,F_replace},	/* glowing clip */
{ V_blue,V_switch,V_blue_button,F_replace},	/* blue switch */
{ V_blue,V_button,V_blue_button,F_replace},	/* blue button */
{ V_gray,V_switch,V_gray_button,F_replace},	/* gray switch */
{ V_gray,V_button,V_gray_button,F_replace},	/* gray button */
{ V_yellow,V_switch,V_yellow_button,F_replace},	/* yellow switch */
{ V_yellow,V_button,V_yellow_button,F_replace},	/* yellow button */
{ V_red,V_switch,V_red_button,F_replace},	/* red switch */
{ V_red,V_button,V_red_button,F_replace},	/* red button */
{ V_white,V_switch,V_white_button,F_replace},	/* white switch */
{ V_white,V_button,V_white_button,F_replace},	/* white button */
{ V_green,V_switch,V_green_button,F_replace},	/* green switch */
{ V_green,V_button,V_green_button,F_replace},	/* green button */
{ V_grey,V_switch,V_gray_button,F_replace},	/* grey switch */
{ V_grey,V_button,V_gray_button,F_replace},	/* grey button */
{ V_orange,V_switch,V_orange_button,F_replace},	/* orange switch */
{ V_orange,V_button,V_orange_button,F_replace}	/* orange button */
} ;

/* Adverb Table */
struct adverb_struct adverb[Adv_max] = { 
{ V_down, V_put, V_drop},			/* put down */
{ V_down, V_set, V_drop},			/* set down */
{ V_carefully, V_drop, V_slow_drop},		/* drop carefully */
{ V_gently, V_drop, V_slow_drop},		/* drop slowly */
{ V_softly, V_drop, V_slow_drop},		/* drop softly */
{ V_slowly, V_drop, V_slow_drop},		/* drop slowly */
{ V_carefully, V_put, V_slow_drop},		/* put carefully */
{ V_gently, V_put, V_slow_drop},		/* put slowly */
{ V_softly, V_put, V_slow_drop},		/* put softly */
{ V_slowly, V_put, V_slow_drop},		/* put slowly */
{ V_in, V_go, V_enter},				/* go in */
{ V_in, V_move, V_enter},			/* move in */
{ V_in, V_leap, V_enter},			/* leap in */
{ V_in, V_walk, V_enter},			/* walk in */
{ V_in, V_run, V_enter},			/* run in */
{ V_in, V_jump, V_enter},			/* jump in */
{ V_in, V_hop, V_enter},			/* hop in */
{ V_in, V_stroll, V_enter},			/* stroll in */
{ V_in, V_saunter, V_enter}, 			/* saunter in */
{ V_in, V_swagger, V_enter},			/* swagger in */
{ V_out, V_go, V_exit},				/* go out */
{ V_out, V_move, V_exit},			/* move out */
{ V_out, V_leap, V_exit},			/* leap out */
{ V_out, V_walk, V_exit},			/* walk out */
{ V_out, V_run, V_exit},			/* run out */
{ V_out, V_jump, V_exit},			/* jump out */
{ V_out, V_hop, V_exit},			/* hop out */
{ V_out, V_stroll, V_exit},			/* stroll out */
{ V_out, V_saunter, V_exit}, 			/* saunter out */
{ V_out, V_swagger, V_exit}			/* swagger out */
} ;

/* Verb Table */
int verb_table[Verb_max] = {
V_quit,V_unlock,V_lock,V_take,V_leave,
V_drop,V_look,V_open,V_get,V_throw,
V_turn,V_push,V_enter,V_switch,V_lift,
V_svc,V_dial,V_put,V_close,V_read,
V_score,V_inventory,V_examine,V_describe,V_drink,
V_fill,V_invent,V_view,V_press,V_exit,
V_shoot,V_kill,V_pick,V_grab,V_combination,
V_select,V_set,V_insert,V_attach,V_remove,
V_eject,V_shut,V_light,V_ignite,V_sound,
V_bang,V_hit,V_strike,V_give,V_stats,
V_jsys,V_su,V_eat,V_swallow,V_fling,
V_help,V_leap,V_walk,V_run,V_jump,
V_hop,V_stroll,V_saunter,V_swagger,V_go,
V_move,V_swing,V_dig,V_swim,V_depart,
V_info,V_back,V_hold,V_fire,V_pull,
V_stand,V_load,V_unload,V_climb,V_toss,
V_inspect
};
 
#endif

/***************************************************************/

#ifdef TAKER
int clip_flag = F_no_clip ;
int gleep_safe = 0, gleep_drop = FALSE ;
extern char *vocab[Vocab_cnt] ;
extern int room[DM_room][16] ;
extern int rifle_flag, number_word ; 
extern struct object_struct object[Objcnt] ;
extern int carry_count, carry_weight ;
extern int gleep_count, verb, sent[20], tag[DM_tag] ;
extern int sw_valuable ;

#endif
