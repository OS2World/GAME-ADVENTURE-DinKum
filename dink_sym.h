/***********************************************************/
/*                                                         */
/*          --- Dinkum Symbol Definition File ---          */
/*                                                         */
/*            Version:  Mk 1.13,   16 January 1993         */
/*                                                         */
/***********************************************************/

#include <stdio.h> 

/* Deal with K&R C versus ANSI-C */
#if sun
#define void	int
#define PROTOTYPE	0
#else
#define PROTOTYPE	1
#endif

#ifdef CLASSIC
#define PROTOTYPE	0
#endif

/* Definitions for Bugs subroutine */
#define Failed		0
#define Request		1
#define Logic_error	2
 
/* Room code numbers */
/*  These code numbers 'n' point to the table entry in room[n][] */
#define R_WALL		-1
#define R_meadow	0
#define R_dike		3
#define R_river_edge	4
#define R_river		5
#define R_stream	6
#define R_slime		7
#define R_bunyip	8
#define R_river_exit	9
#define R_forest	11
#define R_billabong	14
#define R_taipan	18
#define R_mine_head	22
#define R_lift_entr	27
#define R_bitumen	29
#define R_office_entr	36
#define R_office_hall	37
#define R_office_mang	38
#define R_geo_w		39
#define R_store_room	40
#define R_geo_e		41
#define R_lift_inside	43
#define R_L49_entr      44
#define R_L67_entr      45
#define R_L82_entr      46
#define R_hideout_entr	144
#define R_hideout	146
#define R_bend		147
#define R_no_treasure	159
#define R_manhole_1	166
#define R_manhole_2	170
#define R_foreman	177
#define R_blast_point	185
#define R_ufo_w		191
#define R_ufo_nw	192
#define R_ufo_n		193
#define R_ufo_ne	194
#define R_ufo_e		195
#define R_ufo_se	196
#define R_ufo_s		197
#define R_ufo_sw	198
#define R_air_lock	199
#define R_ship_passage	200
#define R_flight_deck	201
#define R_panel		202
#define R_transporter	203
#define R_gleep_tank	206
#define R_warning	217
#define R_gong		238
#define R_closet	240 
#define R_guard 	241
#define R_prayer	242
#define R_road_kill_s	245
#define R_road_kill_n	248

/* Room category indicator for room[n][i] where "i" is below */
#define M_rm_type	10
#define M_obj_cnt	11
#define M_unmov_obj     12
#define M_monster	13
#define M_gleep		14
#define M_descp		15

/* Room type, referred to by room[n][M_rm_type] */
#define T_lethal	-1
#define T_short_descp	0
#define T_long_descp	1
#define T_was_long	3
#define T_looping	5

/* Unmovable object status, i.e.  Safe->Status  */
#define S_closed	0
#define S_revealed	1
#define S_flashing	1
#define S_dialed	2
#define S_unlocked	2
#define S_open		3
#define S_kicked	8
#define S_recorder	4
#define S_told		5
#define S_fair_game	6
#define S_recording	7
#define S_playing	9
#define S_inactive	10

#define L0		0
#define L49		49
#define L67		67
#define L82		82

/* Vocabulary code numbers */
/*  numbers -1 to 10 to not correspond to actual vocabulary words */
#define V_LINE_END	-1
#define V_NULL		0
#define V_MOVE		1
#define V_PLURAL	2
#define V_VERB_ONLY	3
#define V_DIRECTION	4
#define V_NUMBER	5

/* --- below are real word symbols --- */
#define V_east		3
#define V_west		4
#define V_up		5
#define V_down	 	6
#define V_u		15
#define V_quit		21
#define V_unlock	22
#define V_lock		23
#define V_take		24
#define V_leave		25
#define V_drop		26
#define V_can		27
#define V_bottle	28
#define V_mat		29  
#define V_key		30
#define V_butt		31
#define V_look		32
#define V_door		33
#define V_open		34
#define V_get		35
#define V_throw		36
#define V_turn		37
#define V_on		38
#define V_off		39
#define V_push		40
#define V_button	41
#define V_enter		42
#define V_switch	43
#define V_zero		44
#define V_forty_nine	45
#define V_sixty_seven	46
#define V_eighty_two	47
#define V_0		48
#define V_49		49
#define V_67		50
#define V_82		51
#define V_beer		52
#define V_lager		53
#define V_doormat	54
#define V_lift		55
#define V_on_q		56
#define V_off_q		57
#define V_svc		58
#define V_map		59
#define V_picture	60
#define V_safe		61
#define V_dial		62
#define V_paper		63
#define V_put		64
#define V_close		65
#define V_read		66
#define V_gold		67
#define V_bar		68
#define V_dynamite	69
#define V_rifle		70
#define V_M16		71
#define V_m16		72
#define V_cap		73
#define V_matches	74
#define V_diamond	75
#define V_ring		76
#define V_ruby		77
#define V_silver	78
#define V_coin		79
#define V_bill		80
#define V_money		81
#define V_teapot	82
#define V_clip		83
#define V_ammo		84
#define V_box		85
#define V_stick		86
#define V_pills		87
#define V_orange	88
#define V_glowing	89
#define V_saphire	90
#define V_emerald	91
#define V_score		92
#define V_inventory	93
#define V_examine	94
#define V_describe	95
#define V_drink 	96
#define V_fill		97
#define V_water		98
#define V_fourex	99
#define V_invent	100
#define V_view		101
#define V_press		102
#define V_exit		103
#define V_all		104
#define V_Fourex	105
#define V_everything	106
#define V_shoot		107
#define V_kill		108
#define V_ned		109
#define V_Ned		110
#define V_kelly		111
#define V_Kelly		112
#define V_pick		113
#define V_grab		114
#define V_combination	115
#define V_select	116
#define V_safety	117
#define V_SAFE		118
#define V_triple	119
#define V_III		120
#define V_single	121
#define V_I		122
#define V_auto		123
#define V_AUTO		124
#define V_automatic	125
#define V_set		126
#define V_insert	127
#define V_attach	128
#define V_plan		129
#define V_gun		130
#define V_magazine	131
#define V_hoop		132
#define V_snake		133
#define V_bear		134
#define V_wombat	135
#define V_remove	136
#define V_eject		137
#define V_org_clip	138
#define V_shut		139
#define V_gleep		140
#define V_gleeps	141
#define V_letter	142
#define V_envelope	143
#define V_torch		144
#define V_mail		145
#define V_tank		146
#define V_carefully	147
#define V_gently	148
#define V_softly	149
#define V_slow_drop	150
#define V_light		151
#define V_ignite	152
#define V_fuse		153
#define V_slowly	154
#define V_match		155
#define V_cube		156
#define V_blue		157
#define V_blue_button	158
#define V_gray		159
#define V_gray_button	160
#define V_clapper	161
#define V_sound		162
#define V_bang		163
#define V_hit		164
#define V_strike	165
#define V_gong		166
#define V_detector	167
#define V_give		168
#define V_stats		169
#define V_jsys		170
#define V_su		171
#define V_yellow	172
#define V_yellow_button	173
#define V_poster	174
#define V_eat		175
#define V_swallow	176
#define V_pill		177
#define V_atropine	178
#define V_packet	179
#define V_wrapper	180
#define V_tire		181
#define V_shell		182
#define V_brick		183
#define V_rope		184
#define V_package	185
#define V_belt		186
#define V_filter	187
#define V_string	188
#define V_cabinet	189
#define V_calendar	190
#define V_tackle	191
#define V_bit		192
#define V_jack		193
#define V_pen		194
#define V_pencil	195
#define V_wire		196
#define V_pipe		197
#define V_panel		198
#define V_opener	199
#define V_cord		200
#define V_photo		201
#define V_chair		202
#define V_bulb		203
#define V_rag		204
#define V_tube		205
#define V_carpet	206
#define V_branch	207
#define V_cork		208
#define V_trap		209
#define V_lighter	210
#define V_lace		211
#define V_comb		212
#define V_umbrella	213
#define V_meadow	214
#define V_billabong	215
#define V_river		216
#define V_road		217
#define V_forest	218
#define V_grass		219
#define V_stream	220
#define V_desert	221
#define V_building	222
#define V_office	223
#define V_hideout	224
#define V_dust		225
#define V_mine		226
#define V_tunnel	227
#define V_tree		228
#define V_spinifex	229
#define V_hexagon	230
#define V_spacecaft	231
#define V_airlock	232
#define V_wing		233
#define V_hole		234
#define V_tray		235
#define V_liquid	236
#define V_cockroach	237
#define V_go		238
#define V_scream	239
#define V_yell		240
#define V_bring		241
#define V_help		242
#define V_dump		243
#define V_attack	244
#define V_check		245
#define V_inspect	246
#define V_place		247
#define V_touch		248
#define V_pull		249
#define V_extinguish	250
#define V_ask		251
#define V_talk		252
#define V_tell		253
#define V_find		254
#define V_move		255
#define V_break		256
#define V_kick		257
#define V_smash		258
#define V_feed		259
#define V_taste		260
#define V_smell		261
#define V_slam		262
#define V_desk		263
#define V_in		264
#define V_into		265
#define V_under		266
#define V_out		267
#define V_from		268
#define V_by		269
#define V_with		270
#define V_fling		271
#define V_what		272
#define V_where		273
#define V_are		274
#define V_am		275
#define V_have		276
#define V_QUESTION	277
#define V_how		278
#define V_why		279
#define V_who		280
#define V_when		281
#define V_leap		282
#define V_walk		283
#define V_run		284
#define V_jump		285
#define V_hop		286
#define V_stroll	287
#define V_saunter	288
#define V_swagger	289
#define V_swing		290
#define V_dig		291
#define V_swim		292
#define V_depart	293
#define V_info		294
#define V_back		295
#define V_hold		296
#define V_fire		297
#define V_stand		298
#define V_painting	299
#define V_doors		300
#define V_treasure	301
#define V_trigger	302
#define V_load		303
#define V_unload	304
#define V_sand		305
#define V_cockroaches	306
#define V_kangaroo	307
#define V_climb		308
#define V_bulldust	309
#define V_kangaroos	310
#define V_spinifexes	311
#define V_fuze		312
#define V_message	313
#define V_wall		314
#define V_recorder	315
#define V_red		316
#define V_white		317
#define V_green		318
#define V_red_button	319
#define V_white_button	320
#define V_green_button	321
#define V_grey		322
#define V_matchbox	323
#define V_map_frag	324
#define V_circuit	325
#define V_lift_door	326
#define V_transporter	327
#define V_warning	328
#define V_explosive	329
#define V_self		330
#define V_myself	331
#define V_yourself	332
#define V_one		333
#define V_two		334
#define V_three		335
#define V_four		336
#define V_five		337
#define V_toss		338
#define V_chart		339
#define V_charts	340
#define V_schedule	341
#define V_schedules	342
#define V_orange_button	343

/* Miscellaneous flags */
#define FALSE		0
#define TRUE		1
#define F_asleep	8
#define F_stealing	9
#define F_passive	10
#define F_aggressive	11
#define F_killing	12
#define F_no_monster	13
#define F_monster_active	14
#define F_no_argument	15
#define F_safety	16
#define F_single	17
#define F_triple	18
#define F_auto		19
#define F_no_clip	20
#define F_normal_clip	21
#define F_org_clip	22
#define F_wounded	23
#define F_replace	24
#define F_ignore	25
#define F_died		26
#define F_quit		27

/* enemy/monster symbols */
#define N_ned		0
#define N_wombat	1
#define N_drop_bear	2
/* 2-5 drop bear   */
#define N_hoop_snake	6
/* 6-13 hoop snake */
#define N_guards	14
#define N_mullah	15
 
/* Object status as referred to in object->Location */
#define B_have  	-1
#define B_unmade	-2
#define B_destroyed	-3
#define B_in_safe	-5

/* Object external property as referred to in object->Type */
#define Z_normal	0
#define Z_transform	1
#define Z_alias		2
#define Z_unmovable	3

/* Structure for monsters */
struct monster_struct { 
	int Type ;	/* Monster type			      */
	int Location ;	/* Location of the monster            */
	int Status ;	/* Status of the monster              */
	int Hits ;	/* Number of bullet hits into monster */
} ;

typedef struct monster_struct MONSTER_STRUCT;

/* Structure for objects */
struct object_struct {
	int Location ; 	/* Object's location or status   */
	int Value ;	/* Treasure value                */
	int Type ;	/* Object's external property    */
	int ID ;	/* Object ID number              */
	int Weight ;	/* Object weight                 */
	int Status ; 	/* Object's internal property    */
	char *Text ;	/* Text string describing object */
} ;

typedef struct object_struct OBJECT_STRUCT;

/* Structure for objects which can be examined or read */
struct read_struct {
	int ID ;	/* Object ID number              */
	int Readable ;	/* TRUE if readable              */
} ;

typedef struct read_struct READ_STRUCT;

/* Structure for adjectives */
struct adjective_struct {
	int Adjective ;		/* Adjective word number */
	int Modified_noun ;	/* Noun to be modified word number */
	int Generated_noun ;	/* Resultant noun from above adjective & noun */
	int Command ;		/* Command or action done with resultant noun */
} ;

typedef struct adjective_struct ADJECTIVE_STRUCT;

/* Structure for adverbs */
struct adverb_struct {
	int Adverb ;		/* Adverb word number */
	int Modified_verb ;	/* Verb to be modified word number */
	int Generated_verb ;	/* Resultant verb from above adverb & verb */
} ;

typedef struct adverb_struct ADVERB_STRUCT;



