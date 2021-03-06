;*=====================================================================*/
;*    serrano/prgm/project/bigloo/comptime/BackEnd/c-main.scm          */
;*    -------------------------------------------------------------    */
;*    Author      :  Manuel Serrano                                    */
;*    Creation    :  Thu Mar 16 17:59:38 1995                          */
;*    Last change :  Tue Jul 28 17:11:09 2009 (serrano)                */
;*    Copyright   :  1995-2009 Manuel Serrano, see LICENSE file        */
;*    -------------------------------------------------------------    */
;*    We produce a Bigloo's `main' function.                           */
;*=====================================================================*/

;*---------------------------------------------------------------------*/
;*    The module                                                       */
;*---------------------------------------------------------------------*/
(module backend_c_main
   (import  engine_param
	    module_module
	    type_type
	    type_cache
	    object_class
	    object_slots
	    ast_var
	    ast_node
	    ast_env
	    ast_sexp
	    ast_local
	    ast_glo-def
	    tools_shape
	    backend_c_prototype
	    backend_cplib)
   (export  (make-bigloo-main)))

;*---------------------------------------------------------------------*/
;*    make-bigloo-main ...                                             */
;*---------------------------------------------------------------------*/
(define (make-bigloo-main)
   (let* ((args        (list (make-local-svar 'argv *obj*)))
	  (main-body   (if (global? *main*)
			   `(begin
			       (,(module-initialization-id *module*)
				0
				,(symbol->string *module*))
			       ((@ bigloo-initialized! __param))
			       (%exit ((@ ,(global-id *main*)
					  ,(global-module *main*))
				       argv)))
			   `(begin
			       (,(module-initialization-id *module*)
				0
				,(symbol->string *module*))
			       ((@ bigloo-initialized! __param))
			       (let ((z::bint ($int->bint 0)))
				  (%exit z))
			       #unspecified)))
	  (node        (let ((_ *_*))
			  (set! *_* *obj*)
			  (let ((node (sexp->node main-body args #f 'value)))
			     (set! *_* _)
			     node)))
	  (bigloo-main (def-global-sfun! 'bigloo_main::obj
			  '(argv::obj)
			  args
			  *module*
			  'sfun
			  'bigloo-main-procedure
			  'now
			  node)))
      (global-import-set! bigloo-main 'export)
      (global-name-set! bigloo-main "bigloo_main")
      bigloo-main))
