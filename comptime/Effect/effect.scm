;*=====================================================================*/
;*    serrano/prgm/project/bigloo/comptime/Effect/effect.scm           */
;*    -------------------------------------------------------------    */
;*    Author      :  Manuel Serrano                                    */
;*    Creation    :  Thu Jul 13 13:46:44 1995                          */
;*    Last change :  Mon May 15 07:41:27 2000 (serrano)                */
;*    Copyright   :  1995-2000 Manuel Serrano, see LICENSE file        */
;*    -------------------------------------------------------------    */
;*    The effect property                                              */
;*    -------------------------------------------------------------    */
;*    It is optional to have run the Effect pass before invoking       */
;*    this function. Nevertheless, firstly invoking Effect pass        */
;*    leads to better approximations.                                  */
;*=====================================================================*/

;*---------------------------------------------------------------------*/
;*    The module                                                       */
;*---------------------------------------------------------------------*/
(module effect_effect
   (include "Ast/node.sch")
   (export  (generic side-effect?::bool ::node)))

;*---------------------------------------------------------------------*/
;*    side-effect? ...                                                 */
;*---------------------------------------------------------------------*/
(define-generic (side-effect? node::node))

;*---------------------------------------------------------------------*/
;*    side-effect? ::node ...                                          */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::node)
   #f)

;*---------------------------------------------------------------------*/
;*    side-effect? ...                                                 */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::var)
   (not (eq? (variable-access (var-variable node)) 'read)))

;*---------------------------------------------------------------------*/
;*    side-effect? ::node ...                                          */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::node/effect)
   (let ((effect (node/effect-side-effect? node)))
      (if (boolean? effect)
	  effect
	  #t)))
 
;*---------------------------------------------------------------------*/
;*    side-effect? ::setq ...                                          */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::setq)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::fail ...                                          */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::fail)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::set-ex-it ...                                     */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::set-ex-it)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::jump-ex-it ...                                    */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::jump-ex-it)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::box-set! ...                                      */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::box-set!)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::app-ly ...                                        */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::app-ly)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::funcall ...                                       */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::funcall)
   #t)

;*---------------------------------------------------------------------*/
;*    side-effect? ::cast ...                                          */
;*---------------------------------------------------------------------*/
(define-method (side-effect? node::cast)
   (with-access::cast node (arg)
      (side-effect? arg)))



	    
