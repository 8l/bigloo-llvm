/*===========================================================================*/
/*   (Module/main.scm)                                                       */
/*   Bigloo (3.6a)                                                           */
/*   Inria -- Sophia Antipolis (c)       Sun Jan 23 07:38:25 CET 2011        */
/*===========================================================================*/
/* COMPILATION: (/users/serrano/prgm/project/bigloo/bin/bigloo -q -afile .afile -fsharing -fno-reflection -cc gcc -lib-dir /users/serrano/prgm/project/bigloo/lib/3.6a -unsafev -gno-error-localization -no-hello -O2 -rm -unsafe -s -indent Module/main.scm)*/
/* GC selection */
#define THE_GC BOEHM_GC

#include <bigloo.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Object type definitions */
	typedef struct BgL_ccompz00_bgl
	{
		header_t header;
		obj_t widening;
		obj_t BgL_idz00;
		obj_t BgL_producerz00;
		obj_t BgL_consumerz00;
		obj_t BgL_finaliza7erza7;
	}               *BgL_ccompz00_bglt;

	typedef struct BgL_backendz00_bgl
	{
		header_t header;
		obj_t widening;
		obj_t BgL_languagez00;
		obj_t BgL_srfi0z00;
		obj_t BgL_namez00;
		obj_t BgL_externzd2variableszd2;
		obj_t BgL_externzd2functionszd2;
		obj_t BgL_externzd2typeszd2;
		obj_t BgL_variablesz00;
		obj_t BgL_functionsz00;
		obj_t BgL_typesz00;
		bool_t BgL_typedz00;
		obj_t BgL_heapzd2suffixzd2;
		obj_t BgL_heapzd2compatiblezd2;
		bool_t BgL_callccz00;
		bool_t BgL_qualifiedzd2typeszd2;
		bool_t BgL_effectzb2zb2;
		bool_t BgL_removezd2emptyzd2letz00;
		bool_t BgL_foreignzd2closurezd2;
		bool_t BgL_typedzd2eqzd2;
		bool_t BgL_tracezd2supportzd2;
		obj_t BgL_foreignzd2clausezd2supportz00;
		obj_t BgL_debugzd2supportzd2;
		bool_t BgL_pragmazd2supportzd2;
		bool_t BgL_tvectorzd2descrzd2supportz00;
		bool_t BgL_requirezd2tailczd2;
		obj_t BgL_registersz00;
		obj_t BgL_pregistersz00;
		bool_t BgL_boundzd2checkzd2;
		bool_t BgL_typezd2checkzd2;
	}                 *BgL_backendz00_bglt;

	typedef struct BgL_typez00_bgl
	{
		header_t header;
		obj_t widening;
		obj_t BgL_idz00;
		obj_t BgL_namez00;
		obj_t BgL_siza7eza7;
		obj_t BgL_classz00;
		obj_t BgL_coercezd2tozd2;
		obj_t BgL_parentsz00;
		bool_t BgL_initzf3zf3;
		bool_t BgL_magiczf3zf3;
		obj_t BgL_z42z42;
		obj_t BgL_aliasz00;
		obj_t BgL_pointedzd2tozd2byz00;
		obj_t BgL_tvectorz00;
		obj_t BgL_locationz00;
		obj_t BgL_importzd2locationzd2;
		int BgL_occurrencez00;
	}              *BgL_typez00_bglt;

	typedef struct BgL_valuez00_bgl
	{
		header_t header;
		obj_t widening;
	}               *BgL_valuez00_bglt;

	typedef struct BgL_variablez00_bgl
	{
		header_t header;
		obj_t widening;
		obj_t BgL_idz00;
		obj_t BgL_namez00;
		struct BgL_typez00_bgl *BgL_typez00;
		struct BgL_valuez00_bgl *BgL_valuez00;
		obj_t BgL_accessz00;
		obj_t BgL_fastzd2alphazd2;
		obj_t BgL_removablez00;
		long BgL_occurrencez00;
	}                  *BgL_variablez00_bglt;

	typedef struct BgL_globalz00_bgl
	{
		header_t header;
		obj_t widening;
		obj_t BgL_idz00;
		obj_t BgL_namez00;
		struct BgL_typez00_bgl *BgL_typez00;
		struct BgL_valuez00_bgl *BgL_valuez00;
		obj_t BgL_accessz00;
		obj_t BgL_fastzd2alphazd2;
		obj_t BgL_removablez00;
		long BgL_occurrencez00;
		obj_t BgL_modulez00;
		obj_t BgL_importz00;
		bool_t BgL_evaluablezf3zf3;
		obj_t BgL_libraryz00;
		bool_t BgL_userzf3zf3;
		obj_t BgL_pragmaz00;
		obj_t BgL_srcz00;
		obj_t BgL_jvmzd2typezd2namez00;
	}                *BgL_globalz00_bglt;

	typedef struct BgL_funz00_bgl
	{
		header_t header;
		obj_t widening;
		long BgL_arityz00;
		obj_t BgL_sidezd2effectzf3z21;
		obj_t BgL_predicatezd2ofzd2;
		obj_t BgL_stackzd2allocatorzd2;
		bool_t BgL_topzf3zf3;
		obj_t BgL_thezd2closurezd2;
		obj_t BgL_effectz00;
	}             *BgL_funz00_bglt;

	typedef struct BgL_sfunz00_bgl
	{
		header_t header;
		obj_t widening;
		long BgL_arityz00;
		obj_t BgL_sidezd2effectzf3z21;
		obj_t BgL_predicatezd2ofzd2;
		obj_t BgL_stackzd2allocatorzd2;
		bool_t BgL_topzf3zf3;
		obj_t BgL_thezd2closurezd2;
		obj_t BgL_effectz00;
		obj_t BgL_propertyz00;
		obj_t BgL_argsz00;
		obj_t BgL_argszd2namezd2;
		obj_t BgL_bodyz00;
		obj_t BgL_classz00;
		obj_t BgL_dssslzd2keywordszd2;
		obj_t BgL_locz00;
		obj_t BgL_optionalsz00;
		obj_t BgL_keysz00;
		obj_t BgL_thezd2closurezd2globalz00;
	}              *BgL_sfunz00_bglt;


	extern obj_t BGl_producezd2modulezd2clausez12z12zzmodule_modulez00(obj_t);
	extern obj_t BGl_sfunz00zzast_varz00;
	BGL_IMPORT obj_t BGl_consza2za2zz__r4_pairs_and_lists_6_3z00(obj_t, obj_t);
	BGL_IMPORT obj_t BGl_readz00zz__readerz00(obj_t, obj_t);
	BGL_IMPORT bool_t BGl_iszd2azf3z21zz__objectz00(obj_t, obj_t);
	static obj_t BGl_requirezd2initializa7ationz75zzmodule_mainz00 = BUNSPEC;
	static obj_t BGl_mainzd2consumerzd2zzmodule_mainz00(obj_t, obj_t);
	static obj_t BGl_mainzd2producerzd2zzmodule_mainz00(obj_t);
	static obj_t BGl_genericzd2initzd2zzmodule_mainz00();
	extern obj_t BGl_za2moduleza2z00zzmodule_modulez00;
	static obj_t BGl__makezd2mainzd2compilerz00zzmodule_mainz00(obj_t);
	extern obj_t BGl_globalz00zzast_varz00;
	extern obj_t BGl_za2bdbzd2debugza2zd2zzengine_paramz00;
	BGL_EXPORTED_DECL obj_t BGl_makezd2mainzd2compilerz00zzmodule_mainz00();
	static obj_t BGl_cnstzd2initzd2zzmodule_mainz00();
	static obj_t BGl_duplicatezd2mainzd2errorz00zzmodule_mainz00(obj_t);
	static obj_t BGl_importedzd2moduleszd2initz00zzmodule_mainz00();
	extern obj_t BGl_userzd2errorzd2zztools_errorz00(obj_t, obj_t, obj_t, obj_t);
	BGL_EXPORTED_DECL obj_t BGl_modulezd2initializa7ationz75zzmodule_mainz00(long,
		char *);
	extern obj_t BGl_modulezd2initializa7ationz75zzengine_paramz00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zzast_envz00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zzast_varz00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zztype_cachez00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zztype_typez00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zztools_errorz00(long, char *);
	extern obj_t BGl_modulezd2initializa7ationz75zzbackend_backendz00(long,
		char *);
	extern obj_t BGl_modulezd2initializa7ationz75zzmodule_modulez00(long, char *);
	BGL_IMPORT obj_t
		BGl_modulezd2initializa7ationz75zz__r4_pairs_and_lists_6_3z00(long, char *);
	BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__readerz00(long, char *);
	BGL_IMPORT obj_t BGl_modulezd2initializa7ationz75zz__objectz00(long, char *);
	BGL_IMPORT obj_t bgl_open_input_string(obj_t, int);
	BGL_IMPORT obj_t BGl_memqz00zz__r4_pairs_and_lists_6_3z00(obj_t, obj_t);
	extern obj_t BGl_thezd2backendzd2zzbackend_backendz00();
	extern obj_t BGl_za2mainza2z00zzmodule_modulez00;
	static bool_t BGl_correctzd2mainzf3z21zzmodule_mainz00(BgL_globalz00_bglt);
	static obj_t BGl_zc3anonymousza32214ze3z83zzmodule_mainz00(obj_t);
	extern obj_t BGl_za2objza2z00zztype_cachez00;
	extern obj_t BGl_findzd2globalzf2modulez20zzast_envz00(obj_t, obj_t);
	extern BgL_ccompz00_bglt BGl_makezd2ccompzd2zzmodule_modulez00(obj_t, obj_t,
		obj_t, obj_t);
	extern obj_t BGl_za2pairza2z00zztype_cachez00;
	static obj_t BGl_libraryzd2moduleszd2initz00zzmodule_mainz00();
	static obj_t BGl__mainzd2consumerzd2zzmodule_mainz00(obj_t, obj_t, obj_t);
	static obj_t BGl_methodzd2initzd2zzmodule_mainz00();
	static obj_t BGl__mainzd2producerzd2zzmodule_mainz00(obj_t, obj_t);
	static obj_t __cnst[7];


	   
		 
		DEFINE_STRING(BGl_string2380z00zzmodule_mainz00,
		BgL_bgl_string2380za700za7za7m2391za7, "Parse error", 11);
	      DEFINE_STRING(BGl_string2379z00zzmodule_mainz00,
		BgL_bgl_string2379za700za7za7m2392za7,
		"Illegal declaration of main function", 36);
	      DEFINE_STRING(BGl_string2381z00zzmodule_mainz00,
		BgL_bgl_string2381za700za7za7m2393za7, "Illegal main clause", 19);
	      DEFINE_STRING(BGl_string2382z00zzmodule_mainz00,
		BgL_bgl_string2382za700za7za7m2394za7, "Duplicated main clause", 22);
	      DEFINE_STRING(BGl_string2383z00zzmodule_mainz00,
		BgL_bgl_string2383za700za7za7m2395za7, "module_main", 11);
	      DEFINE_STRING(BGl_string2384z00zzmodule_mainz00,
		BgL_bgl_string2384za700za7za7m2396za7,
		"argv::pair argv::obj export bdb imported void main ", 51);
	     
		DEFINE_STATIC_BGL_PROCEDURE(BGl_mainzd2producerzd2envz00zzmodule_mainz00,
		BgL_bgl__mainza7d2producer2397za7, BGl__mainzd2producerzd2zzmodule_mainz00,
		0L, BUNSPEC, 1);
	     
		DEFINE_EXPORT_BGL_PROCEDURE
		(BGl_makezd2mainzd2compilerzd2envzd2zzmodule_mainz00,
		BgL_bgl__makeza7d2mainza7d2c2398z00,
		BGl__makezd2mainzd2compilerz00zzmodule_mainz00, 0L, BUNSPEC, 0);
	      DEFINE_STATIC_BGL_PROCEDURE(BGl_proc2378z00zzmodule_mainz00,
		BgL_bgl_za7c3anonymousza7a322399z00,
		BGl_zc3anonymousza32214ze3z83zzmodule_mainz00, 0L, BUNSPEC, 0);
	     
		DEFINE_STATIC_BGL_PROCEDURE(BGl_mainzd2consumerzd2envz00zzmodule_mainz00,
		BgL_bgl__mainza7d2consumer2400za7, BGl__mainzd2consumerzd2zzmodule_mainz00,
		0L, BUNSPEC, 2);



/* module-initialization */
	BGL_EXPORTED_DEF obj_t BGl_modulezd2initializa7ationz75zzmodule_mainz00(long
		BgL_checksumz00_689, char *BgL_fromz00_690)
	{
		AN_OBJECT;
		{
			if (CBOOL(BGl_requirezd2initializa7ationz75zzmodule_mainz00))
				{
					BGl_requirezd2initializa7ationz75zzmodule_mainz00 =
						BBOOL(((bool_t) 0));
					BGl_libraryzd2moduleszd2initz00zzmodule_mainz00();
					BGl_cnstzd2initzd2zzmodule_mainz00();
					BGl_importedzd2moduleszd2initz00zzmodule_mainz00();
					return BUNSPEC;
				}
			else
				{
					return BUNSPEC;
				}
		}
	}



/* library-modules-init */
	obj_t BGl_libraryzd2moduleszd2initz00zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 15 */
			BGl_modulezd2initializa7ationz75zz__r4_pairs_and_lists_6_3z00(((long) 0),
				"module_main");
			BGl_modulezd2initializa7ationz75zz__readerz00(((long) 0), "module_main");
			BGl_modulezd2initializa7ationz75zz__objectz00(((long) 0), "module_main");
			return BUNSPEC;
		}
	}



/* cnst-init */
	obj_t BGl_cnstzd2initzd2zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 15 */
			{	/* Module/main.scm 15 */
				obj_t BgL_cportz00_681;

				BgL_cportz00_681 =
					bgl_open_input_string(BGl_string2384z00zzmodule_mainz00,
					(int) (((long) 0)));
				{
					long BgL_iz00_682;

					BgL_iz00_682 = ((long) 6);
				BgL_loopz00_683:
					if ((BgL_iz00_682 == ((long) -1)))
						{	/* Module/main.scm 15 */
							return BUNSPEC;
						}
					else
						{	/* Module/main.scm 15 */
							{	/* Module/main.scm 15 */
								obj_t BgL_arg2390z00_685;

								{	/* Module/main.scm 15 */

									{	/* Module/main.scm 15 */
										obj_t BgL_locationz00_687;

										BgL_locationz00_687 = BBOOL(((bool_t) 0));
										{	/* Module/main.scm 15 */

											BgL_arg2390z00_685 =
												BGl_readz00zz__readerz00(BgL_cportz00_681,
												BgL_locationz00_687);
										}
									}
								}
								{	/* Module/main.scm 15 */
									int BgL_auxz00_706;

									BgL_auxz00_706 = (int) (BgL_iz00_682);
									CNST_TABLE_SET(BgL_auxz00_706, BgL_arg2390z00_685);
							}}
							{	/* Module/main.scm 15 */
								int BgL_auxz00_688;

								BgL_auxz00_688 = (int) ((BgL_iz00_682 - ((long) 1)));
								{
									long BgL_iz00_711;

									BgL_iz00_711 = (long) (BgL_auxz00_688);
									BgL_iz00_682 = BgL_iz00_711;
									goto BgL_loopz00_683;
								}
							}
						}
				}
			}
		}
	}



/* make-main-compiler */
	BGL_EXPORTED_DEF obj_t BGl_makezd2mainzd2compilerz00zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 33 */
			{	/* Module/main.scm 34 */
				obj_t BgL_arg2208z00_472;

				BgL_arg2208z00_472 = CNST_TABLE_REF(((long) 0));
				return
					(obj_t) (BGl_makezd2ccompzd2zzmodule_modulez00(BgL_arg2208z00_472,
						BGl_mainzd2producerzd2envz00zzmodule_mainz00,
						BGl_mainzd2consumerzd2envz00zzmodule_mainz00,
						BGl_proc2378z00zzmodule_mainz00));
			}
		}
	}



/* _make-main-compiler */
	obj_t BGl__makezd2mainzd2compilerz00zzmodule_mainz00(obj_t BgL_envz00_674)
	{
		AN_OBJECT;
		{	/* Module/main.scm 33 */
			return BGl_makezd2mainzd2compilerz00zzmodule_mainz00();
		}
	}



/* <anonymous:2214> */
	obj_t BGl_zc3anonymousza32214ze3z83zzmodule_mainz00(obj_t BgL_envz00_675)
	{
		AN_OBJECT;
		{	/* Module/module.scm 54 */
			{

				return CNST_TABLE_REF(((long) 1));
		}}
	}



/* correct-main? */
	bool_t BGl_correctzd2mainzf3z21zzmodule_mainz00(BgL_globalz00_bglt
		BgL_globalz00_1)
	{
		AN_OBJECT;
		{	/* Module/main.scm 44 */
			{	/* Module/main.scm 45 */
				BgL_valuez00_bglt BgL_sfunz00_476;

				{
					BgL_variablez00_bglt BgL_auxz00_718;

					BgL_auxz00_718 = (BgL_variablez00_bglt) (BgL_globalz00_1);
					BgL_sfunz00_476 =
						(((BgL_variablez00_bglt) CREF(BgL_auxz00_718))->BgL_valuez00);
				}
				{	/* Module/main.scm 46 */
					bool_t BgL_testz00_721;

					{	/* Module/main.scm 46 */
						obj_t BgL_obj2063z00_652;

						BgL_obj2063z00_652 = (obj_t) (BgL_sfunz00_476);
						BgL_testz00_721 =
							BGl_iszd2azf3z21zz__objectz00(BgL_obj2063z00_652,
							BGl_sfunz00zzast_varz00);
					}
					if (BgL_testz00_721)
						{	/* Module/main.scm 47 */
							bool_t BgL_testz00_724;

							{	/* Module/main.scm 47 */
								long BgL_auxz00_725;

								{
									BgL_funz00_bglt BgL_auxz00_726;

									BgL_auxz00_726 =
										(BgL_funz00_bglt) ((BgL_sfunz00_bglt) (BgL_sfunz00_476));
									BgL_auxz00_725 =
										(((BgL_funz00_bglt) CREF(BgL_auxz00_726))->BgL_arityz00);
								}
								BgL_testz00_724 = (BgL_auxz00_725 == ((long) 1));
							}
							if (BgL_testz00_724)
								{	/* Module/main.scm 48 */
									obj_t BgL_argsz00_479;

									{	/* Module/main.scm 48 */
										obj_t BgL_pairz00_657;

										{
											BgL_sfunz00_bglt BgL_auxz00_731;

											BgL_auxz00_731 = (BgL_sfunz00_bglt) (BgL_sfunz00_476);
											BgL_pairz00_657 =
												(((BgL_sfunz00_bglt) CREF(BgL_auxz00_731))->
												BgL_argsz00);
										}
										BgL_argsz00_479 = CAR(BgL_pairz00_657);
									}
									{	/* Module/main.scm 48 */
										BgL_typez00_bglt BgL_typez00_480;

										{
											BgL_variablez00_bglt BgL_auxz00_735;

											BgL_auxz00_735 = (BgL_variablez00_bglt) (BgL_argsz00_479);
											BgL_typez00_480 =
												(((BgL_variablez00_bglt) CREF(BgL_auxz00_735))->
												BgL_typez00);
										}
										{	/* Module/main.scm 49 */

											{	/* Module/main.scm 50 */
												bool_t BgL__ortest_2202z00_481;

												BgL__ortest_2202z00_481 =
													(
													(obj_t) (BgL_typez00_480) ==
													BGl_za2objza2z00zztype_cachez00);
												if (BgL__ortest_2202z00_481)
													{	/* Module/main.scm 50 */
														return BgL__ortest_2202z00_481;
													}
												else
													{	/* Module/main.scm 50 */
														return
															(
															(obj_t) (BgL_typez00_480) ==
															BGl_za2pairza2z00zztype_cachez00);
													}
											}
										}
									}
								}
							else
								{	/* Module/main.scm 47 */
									return ((bool_t) 0);
								}
						}
					else
						{	/* Module/main.scm 46 */
							return ((bool_t) 0);
						}
				}
			}
		}
	}



/* main-producer */
	obj_t BGl_mainzd2producerzd2zzmodule_mainz00(obj_t BgL_clausez00_2)
	{
		AN_OBJECT;
		{	/* Module/main.scm 55 */
			{	/* Module/main.scm 56 */
				bool_t BgL_testz00_743;

				if ((BGl_za2mainza2z00zzmodule_modulez00 == CNST_TABLE_REF(((long) 2))))
					{	/* Module/main.scm 56 */
						BgL_testz00_743 = ((bool_t) 1);
					}
				else
					{	/* Module/main.scm 56 */
						obj_t BgL_obj1860z00_659;

						BgL_obj1860z00_659 = BGl_za2mainza2z00zzmodule_modulez00;
						BgL_testz00_743 =
							BGl_iszd2azf3z21zz__objectz00(BgL_obj1860z00_659,
							BGl_globalz00zzast_varz00);
					}
				if (BgL_testz00_743)
					{	/* Module/main.scm 56 */
						return
							BGl_duplicatezd2mainzd2errorz00zzmodule_mainz00(BgL_clausez00_2);
					}
				else
					{
						obj_t BgL_mainz00_486;

						if (PAIRP(BgL_clausez00_2))
							{	/* Module/main.scm 58 */
								obj_t BgL_cdrzd21395zd2_491;

								BgL_cdrzd21395zd2_491 = CDR(BgL_clausez00_2);
								if (PAIRP(BgL_cdrzd21395zd2_491))
									{	/* Module/main.scm 58 */
										obj_t BgL_carzd21397zd2_493;

										BgL_carzd21397zd2_493 = CAR(BgL_cdrzd21395zd2_491);
										if (SYMBOLP(BgL_carzd21397zd2_493))
											{	/* Module/main.scm 58 */
												if (NULLP(CDR(BgL_cdrzd21395zd2_491)))
													{	/* Module/main.scm 58 */
														BgL_mainz00_486 = BgL_carzd21397zd2_493;
														{	/* Module/main.scm 60 */
															obj_t BgL_globalz00_497;

															BgL_globalz00_497 =
																BGl_findzd2globalzf2modulez20zzast_envz00
																(BgL_mainz00_486,
																BGl_za2moduleza2z00zzmodule_modulez00);
															if (BGl_iszd2azf3z21zz__objectz00
																(BgL_globalz00_497, BGl_globalz00zzast_varz00))
																{	/* Module/main.scm 61 */
																	if (BGl_correctzd2mainzf3z21zzmodule_mainz00(
																			(BgL_globalz00_bglt) (BgL_globalz00_497)))
																		{	/* Module/main.scm 62 */
																			return BFALSE;
																		}
																	else
																		{	/* Module/main.scm 63 */
																			obj_t BgL_list2236z00_500;

																			BgL_list2236z00_500 =
																				MAKE_PAIR(BNIL, BNIL);
																			return
																				BGl_userzd2errorzd2zztools_errorz00
																				(BGl_za2moduleza2z00zzmodule_modulez00,
																				BGl_string2379z00zzmodule_mainz00,
																				BgL_mainz00_486, BgL_list2236z00_500);
																		}
																}
															else
																{	/* Module/main.scm 61 */
																	{	/* Module/main.scm 68 */
																		bool_t BgL_testz00_768;

																		if (
																			((long)
																				CINT
																				(BGl_za2bdbzd2debugza2zd2zzengine_paramz00)
																				> ((long) 0)))
																			{	/* Module/main.scm 69 */
																				obj_t BgL_arg2285z00_519;

																				obj_t BgL_arg2286z00_520;

																				BgL_arg2285z00_519 =
																					CNST_TABLE_REF(((long) 3));
																				{	/* Module/main.scm 70 */
																					obj_t BgL_arg2290z00_521;

																					BgL_arg2290z00_521 =
																						BGl_thezd2backendzd2zzbackend_backendz00
																						();
																					{
																						BgL_backendz00_bglt BgL_auxz00_774;

																						BgL_auxz00_774 =
																							(BgL_backendz00_bglt)
																							(BgL_arg2290z00_521);
																						BgL_arg2286z00_520 =
																							(((BgL_backendz00_bglt)
																								CREF(BgL_auxz00_774))->
																							BgL_debugzd2supportzd2);
																				}}
																				BgL_testz00_768 =
																					CBOOL
																					(BGl_memqz00zz__r4_pairs_and_lists_6_3z00
																					(BgL_arg2285z00_519,
																						BgL_arg2286z00_520));
																			}
																		else
																			{	/* Module/main.scm 68 */
																				BgL_testz00_768 = ((bool_t) 0);
																			}
																		if (BgL_testz00_768)
																			{	/* Module/main.scm 71 */
																				obj_t BgL_arg2239z00_502;

																				{	/* Module/main.scm 71 */
																					obj_t BgL_arg2240z00_503;

																					obj_t BgL_arg2242z00_504;

																					BgL_arg2240z00_503 =
																						CNST_TABLE_REF(((long) 4));
																					{	/* Module/main.scm 71 */
																						obj_t BgL_arg2243z00_505;

																						{	/* Module/main.scm 71 */
																							obj_t BgL_arg2252z00_508;

																							{	/* Module/main.scm 71 */
																								obj_t BgL_list2253z00_509;

																								BgL_list2253z00_509 =
																									MAKE_PAIR(BNIL, BNIL);
																								BgL_arg2252z00_508 =
																									BGl_consza2za2zz__r4_pairs_and_lists_6_3z00
																									(CNST_TABLE_REF(((long) 5)),
																									BgL_list2253z00_509);
																							}
																							BgL_arg2243z00_505 =
																								MAKE_PAIR(BgL_mainz00_486,
																								BgL_arg2252z00_508);
																						}
																						{	/* Module/main.scm 71 */
																							obj_t BgL_list2246z00_507;

																							BgL_list2246z00_507 =
																								MAKE_PAIR(BNIL, BNIL);
																							BgL_arg2242z00_504 =
																								BGl_consza2za2zz__r4_pairs_and_lists_6_3z00
																								(BgL_arg2243z00_505,
																								BgL_list2246z00_507);
																					}}
																					BgL_arg2239z00_502 =
																						MAKE_PAIR(BgL_arg2240z00_503,
																						BgL_arg2242z00_504);
																				}
																				BGl_producezd2modulezd2clausez12z12zzmodule_modulez00
																					(BgL_arg2239z00_502);
																			}
																		else
																			{	/* Module/main.scm 72 */
																				obj_t BgL_arg2255z00_510;

																				{	/* Module/main.scm 72 */
																					obj_t BgL_arg2259z00_511;

																					obj_t BgL_arg2260z00_512;

																					BgL_arg2259z00_511 =
																						CNST_TABLE_REF(((long) 4));
																					{	/* Module/main.scm 72 */
																						obj_t BgL_arg2267z00_513;

																						{	/* Module/main.scm 72 */
																							obj_t BgL_arg2282z00_516;

																							{	/* Module/main.scm 72 */
																								obj_t BgL_list2283z00_517;

																								BgL_list2283z00_517 =
																									MAKE_PAIR(BNIL, BNIL);
																								BgL_arg2282z00_516 =
																									BGl_consza2za2zz__r4_pairs_and_lists_6_3z00
																									(CNST_TABLE_REF(((long) 6)),
																									BgL_list2283z00_517);
																							}
																							BgL_arg2267z00_513 =
																								MAKE_PAIR(BgL_mainz00_486,
																								BgL_arg2282z00_516);
																						}
																						{	/* Module/main.scm 72 */
																							obj_t BgL_list2275z00_515;

																							BgL_list2275z00_515 =
																								MAKE_PAIR(BNIL, BNIL);
																							BgL_arg2260z00_512 =
																								BGl_consza2za2zz__r4_pairs_and_lists_6_3z00
																								(BgL_arg2267z00_513,
																								BgL_list2275z00_515);
																					}}
																					BgL_arg2255z00_510 =
																						MAKE_PAIR(BgL_arg2259z00_511,
																						BgL_arg2260z00_512);
																				}
																				BGl_producezd2modulezd2clausez12z12zzmodule_modulez00
																					(BgL_arg2255z00_510);
																	}}
																	return (BGl_za2mainza2z00zzmodule_modulez00 =
																		BGl_findzd2globalzf2modulez20zzast_envz00
																		(BgL_mainz00_486,
																			BGl_za2moduleza2z00zzmodule_modulez00),
																		BUNSPEC);
																}
														}
													}
												else
													{	/* Module/main.scm 58 */
													BgL_tagzd21390zd2_488:
														{	/* Module/main.scm 75 */
															obj_t BgL_list2291z00_522;

															BgL_list2291z00_522 = MAKE_PAIR(BNIL, BNIL);
															return
																BGl_userzd2errorzd2zztools_errorz00
																(BGl_string2380z00zzmodule_mainz00,
																BGl_string2381z00zzmodule_mainz00,
																BgL_clausez00_2, BgL_list2291z00_522);
														}
													}
											}
										else
											{	/* Module/main.scm 58 */
												goto BgL_tagzd21390zd2_488;
											}
									}
								else
									{	/* Module/main.scm 58 */
										goto BgL_tagzd21390zd2_488;
									}
							}
						else
							{	/* Module/main.scm 58 */
								goto BgL_tagzd21390zd2_488;
							}
					}
			}
		}
	}



/* _main-producer */
	obj_t BGl__mainzd2producerzd2zzmodule_mainz00(obj_t BgL_envz00_676,
		obj_t BgL_clausez00_677)
	{
		AN_OBJECT;
		{	/* Module/main.scm 55 */
			return BGl_mainzd2producerzd2zzmodule_mainz00(BgL_clausez00_677);
		}
	}



/* main-consumer */
	obj_t BGl_mainzd2consumerzd2zzmodule_mainz00(obj_t BgL_modulez00_3,
		obj_t BgL_clausez00_4)
	{
		AN_OBJECT;
		{	/* Module/main.scm 80 */
			{	/* Module/main.scm 81 */
				bool_t BgL_testz00_801;

				{	/* Module/main.scm 81 */
					obj_t BgL_obj1860z00_672;

					BgL_obj1860z00_672 = BGl_za2mainza2z00zzmodule_modulez00;
					BgL_testz00_801 =
						BGl_iszd2azf3z21zz__objectz00(BgL_obj1860z00_672,
						BGl_globalz00zzast_varz00);
				}
				if (BgL_testz00_801)
					{	/* Module/main.scm 81 */
						BGl_duplicatezd2mainzd2errorz00zzmodule_mainz00(BgL_clausez00_4);
					}
				else
					{	/* Module/main.scm 81 */
						BGl_za2mainza2z00zzmodule_modulez00 = CNST_TABLE_REF(((long) 2));
			}}
			return BNIL;
		}
	}



/* _main-consumer */
	obj_t BGl__mainzd2consumerzd2zzmodule_mainz00(obj_t BgL_envz00_678,
		obj_t BgL_modulez00_679, obj_t BgL_clausez00_680)
	{
		AN_OBJECT;
		{	/* Module/main.scm 80 */
			return
				BGl_mainzd2consumerzd2zzmodule_mainz00(BgL_modulez00_679,
				BgL_clausez00_680);
		}
	}



/* duplicate-main-error */
	obj_t BGl_duplicatezd2mainzd2errorz00zzmodule_mainz00(obj_t BgL_clausez00_5)
	{
		AN_OBJECT;
		{	/* Module/main.scm 89 */
			{	/* Module/main.scm 90 */
				obj_t BgL_list2294z00_525;

				BgL_list2294z00_525 = MAKE_PAIR(BNIL, BNIL);
				return
					BGl_userzd2errorzd2zztools_errorz00(BGl_string2380z00zzmodule_mainz00,
					BGl_string2382z00zzmodule_mainz00, BgL_clausez00_5,
					BgL_list2294z00_525);
			}
		}
	}



/* generic-init */
	obj_t BGl_genericzd2initzd2zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 15 */
			return BUNSPEC;
		}
	}



/* method-init */
	obj_t BGl_methodzd2initzd2zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 15 */
			return BUNSPEC;
		}
	}



/* imported-modules-init */
	obj_t BGl_importedzd2moduleszd2initz00zzmodule_mainz00()
	{
		AN_OBJECT;
		{	/* Module/main.scm 15 */
			BGl_modulezd2initializa7ationz75zzmodule_modulez00(((long) 358171001),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zzbackend_backendz00(((long) 466514915),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zztools_errorz00(((long) 139755433),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zztype_typez00(((long) 445289072),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zztype_cachez00(((long) 328872856),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zzast_varz00(((long) 43233168),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			BGl_modulezd2initializa7ationz75zzast_envz00(((long) 531182497),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
			return
				BGl_modulezd2initializa7ationz75zzengine_paramz00(((long) 397025513),
				BSTRING_TO_STRING(BGl_string2383z00zzmodule_mainz00));
		}
	}

#ifdef __cplusplus
}
#endif
