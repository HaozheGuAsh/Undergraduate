; HW4 Haozhe Gu lisp programming

; all-length return count of list for all level
(defun all-length (l)
    (cond 
        (( null l ) 0)
        (( atom l ) 1)
    (t  (+ 
            (all-length (car l))
            (all-length (cdr l)))
        )
    )
)

; range return the min and max of a list 
(defun range(l)
    (list
        (apply 'min l)
        (apply 'max l)
    )
)

; before return items between two argument
(defun before(a b l)
    (setq add 0)
    (setq stop 0)
    (setq mylist(list 'a 'b))
    (dolist ( x l)
        (setq z(cons x nil))
        (cond
            ((equal a x) (setq add 1))              ; if a appear 
            ((equal add 1)                          ; if a appear then b appear
                    (cond   
                        ((equal stop 1)0)    ; if extra b
                        ((equal b x) (setq stop 1) (setq mylist(cons (car z) mylist))); first b after a
                    )
            )
        )
            
        (cond
            ((equal stop 1) 0)
            ((equal add 1)
                (setq mylist(cons(car z) mylist))
            )
        )
    )
    
    (setq mylist(reverse mylist))
    (setq mylist(cdr mylist))
    (setq mylist(cdr mylist))
)


;    (cond
;        ((not (equal a (car l)))
;           (do ((list1 l (cdr list1)))
;                ((equal a (car list1)) list1)
;            ))

;        ((equal a (car l)) l)
;    )

;    (setq mylist (list  (car l) (car(cdr l)) ))
;    (write mylist)
;    (loop 
;        (setq mylist (cons (car(cdr l))  mylist))
;       (setq l (cdr l))
;        (when (equal b (car l)) (return) )
;    )
;   (setq mylist(reverse mylist))
;    (setq mylist(cdr mylist))


;split-if that returns a list into two parts. It takes two arguments: a function (f) and
;a list. All members for which f is true go into one list, and the rest go into another list.
(defun split-if( f l)
    (setq leftlist (list 'a'b))
    (setq rightlist(list 'a'b))
    (dolist (ele l)
        (setq x(cons ele nil))
        (if (funcall f ele) (setq rightlist(cons (car x)rightlist))  ;if then add to leftlist
            (setq leftlist(cons (car x) leftlist))
        )
    )
        
        (setq leftlist(reverse leftlist))
        (setq leftlist(cdr leftlist))
        (setq leftlist(cdr leftlist))    
        (setq rightlist(reverse rightlist))
        (setq rightlist(cdr rightlist))
        (setq rightlist(cdr rightlist))  
        (list leftlist rightlist)
)

;group that takes arguments: a list l and a number n. It returns a new list in which the
;elements of l are grouped into sublists of length n. The remainder is put in a final sublist
(defun group(l c)
    (setq wholelist (list 'a'b))
    (setq wholelist(cdr wholelist))
    (setq wholelist(cdr wholelist))
    (setq count c)
    (setq first 1)
    (setq lastone (car(last l)))
    (dolist (ele l)
        (setq x(cons ele nil))
        (cond
                          
            ((equal count 1) (setq count c) 
                  (cond ((equal c 1)  ; case c is one then need to end list here 
                            (setq newlist(list 'a'b)) (setq newlist(cons (car x) newlist))
                        )
                        (t 
                            (setq newlist(cons (car x) newlist))
                        )
                  )
                  ;last one   reset count  add element
                  (setq newlist(reverse newlist))(setq newlist(cdr newlist))(setq newlist(cdr newlist))
                
                  ;reverse list remove dummy first 2
                  (cond ((equal first 1)(setq wholelist(cons (car newlist) (cdr newlist)))(setq first 0)
                                        
                                                    (setq wholelist(cons wholelist nil))
                        )
                        ((equal first 0)(setq wholelist(cons newlist wholelist)))
                  )
                  
            ) ;add to main list (write wholelist)

            ((equal count c )(setq count(- count 1))(setq newlist(list 'a'b)) (setq newlist(cons (car x) newlist))
                            (cond ((eq (car x) lastone); last one case use eq
                                    (setq newlist(reverse newlist))(setq newlist(cdr newlist))(setq newlist(cdr newlist))
                                        (cond ((equal first 1)(setq wholelist(cons (car newlist) (cdr newlist)))(setq first 0)
                                                                (setq wholelist(cons wholelist nil)))
                                              ((equal first 0)(setq wholelist(cons newlist wholelist))))
                                        )
                            )  
              );new sublist   
              
            ((< count c) (setq count(- count 1))(setq newlist(cons (car x) newlist))
                            ; below is when last one pass to here need to end the list 
                         (cond ((eq (car x) lastone)(setq newlist(reverse newlist))
                            (setq newlist(cdr newlist))(setq newlist(cdr newlist))
                                (cond ((equal first 1)(setq wholelist(cons (car newlist) (cdr newlist)))(setq first 0)
                                                        (setq wholelist(cons wholelist nil)))
                                ((equal first 0)(setq wholelist(cons newlist wholelist))))))
            )
        );exist sublist just decrease count and add ele
    )
    (setq wholelist(reverse wholelist))
)

;mostn that takes two arguments: a function f and a list l. It returns a list of all elements
;for which the function yields the highest score (along with the score itself), where score the value returned
;from the given function:
(defun mostn( f l)
    (setq maxval 0)
    (setq wholelist (list 'a'b))
    (setq wholelist(cdr wholelist))
    (setq wholelist(cdr wholelist))
    (dolist (x l)
        (setq ele(cons x nil))
        (setq val (funcall f x))
        ;(write val)
        (cond 
             ((> val maxval)
                    (setq maxval val)(setq wholelist (list 'a'b))(setq wholelist(cdr wholelist))(setq wholelist(cdr wholelist))
                    (setq wholelist(cons (car ele) wholelist))
             )
             ((equal val maxval)
                    (setq wholelist(cons (car ele) wholelist))
             )
        )
    )
    ;(write wholelist)
    (setq maxval(cons maxval nil))
    (setq wholelist(reverse wholelist))
    (setq wholelist(list wholelist(car maxval) ))
)

; Assertions and Simple Pattern-Matching
(defun match (assert pattern)
    (cond 
            ((or (null assert) (null pattern)) (equal assert pattern))      ; l1 or l2 null return l1==l2
            
            ((equal (car assert) '?) (match (cdr assert) (cdr pattern)))    ; l1 head is ? return match(l1 rest l2 rest)
            
            ((and (equal (car assert) '!) (match (cdr assert) (cdr pattern))) t)  ; if l1 head is ! and match(l1rest l2rest) return true
            
            ((equal (car assert) '!) (match assert (cdr pattern)))              ; if l1head is ! return match(l1 l2rest)
            
            (t(and (equal (car assert) (car pattern))  (match (cdr assert) (cdr pattern))))  ; else return (l1head == l2head) and match(l1rest l2rest)
                
    )
)  

;Pattern-Matching Variables
(defun match-var(assert pattern)
    (clean-var assert)
    (match-var-process assert pattern)
)
(defun match-var-process (assert pattern)
    (cond 
            ((or (null assert) (null pattern))  (equal assert pattern))      ; l1 or l2 null return l1==l2
            
            ((and(listp (car assert))(not(equal (car assert) nil)))(cond                                       ; if variable list 
                                    ((equal (caar assert) '?)(set (cadar assert) (car pattern)) (match-var-process (cdr assert) (cdr pattern)))    ; l1 head is ? return match(l1 rest l2 rest); if l1 head is ! and match(l1rest l2rest) return true
                                    
                                    ((equal (caar assert) '!)(cond ((not(boundp (cadar assert)))(set (cadar assert) nil)(set (cadar assert)(cons (car pattern)(symbol-value(cadar assert)))))
                                                                                 ((listp (symbol-value(cadar assert)))(set (cadar assert) (append (symbol-value(cadar assert)) (cons(car pattern)nil)))))
                                                                                                                                                 ; if l1head is ! append l2head to l1head variable
                                                            (cond   ((match-var-process (cdr assert) (cdr pattern))t)               ; return match-var(l1rest l2rest)
                                                                    (t(clean-var (cdr assert))(match-var-process assert (cdr pattern)))                  ; if not, reset variable and return match-var(l1, l2rest)
                                                            )
                                    )
                                )
            )
            (t(and (equal (car assert) (car pattern))  (match-var-process (cdr assert) (cdr pattern))))  ; else return (l1head == l2head) and match-var(l1rest l2rest)(write (cadar assert))(write (symbol-value(cadar assert)))(terpri)(write 'con)(write (symbol-value(cadar assert)))(terpri)
                
    )
)
; helper function for match-var     clean-var
(defun clean-var(l)
    (cond
            ((null l)0)      ;finish
            ((and(listp (car l))(not(equal (car l) nil)))(makunbound (cadar l))(clean-var (cdr l))) ; clean var(though ? not necessaily) and go on
            (t(clean-var (cdr l))); go on when not var
    )
)
 
; 
;(write (cadar assert))(terpri)(write (car pattern))(terpri)(write 'islist)(terpri)(write (cadar assert))(terpri)(write'nul)(terpri)
;(write 'nlist)(terpri)(write (car assert))(terpri)(write'lst)(terpri)(write (symbol-value(cadar assert)))
;
;
;
;
;(defun match (assert pattern)
;    (setq result 't)
;    (setq exclaim 0)
;    (setq err 0)
;    (dolist (p pattern)
;        (cond 
;            ((null assert) (cond ((= exclaim 0) (setq result 'nil))
;                              ((= exclaim 1) (setq result 't)))) ;lastone check
;                              
;            ((and (not(equal (car assert) '?)) (not(equal (car assert) '!))) ; current not ? or !
;                (cond ((= exclaim 0) (cond ((equal (car assert) p) (setq assert(cdr assert)) ); match
;                                            ((not(equal (car assert) p)) (setq result 'nil) (setq err 1))));not match 
;                                            
;                      ((= exclaim 1) (cond ((equal (car assert) p) (setq assert(cdr assert)) (setq exclaim 0)); with ! if match cancel !
;                                            ((not(equal (car assert) p)) )))  ; with ! not match go on
;                )  
;              )
;             ((equal (car assert) '?) (setq assert(cdr assert))); with ? go on anyway
;             ((equal (car assert) '!) (setq exclaim 1) (setq assert(cdr assert))); with ! go on set exclaim on 
;        )
;    )
;    (cond ((or (not (null assert)) (equal err 1)) (setq result nil)); either assert not finish or err happen return nil
;    )
;    result
;)

;Pattern-Matching Variables
;(defun match-var (assert pattern)
;    (setq result 't)
;    (setq exclaim 0)
;    (setq err 0)
;    (setq namewaitlist nil)
;    (setq namewaitcount 0)
;    (setq valuewaitlist nil)
;   (setq valuewaitcount 0)
;    (dolist (p pattern)
;        (cond 
;            ((null assert) (cond ((= exclaim 0) (setq result 'nil))
;                              ((= exclaim 1) (setq result 't)))) 
;                              
;            ((atom (car assert))
;                (cond ((= exclaim 0) (cond ((equal (car assert) p) (setq assert(cdr assert)) )
;                                            ((not(equal (car assert) p)) (setq result 'nil) (setq err 1)))) 
;                                            
;                      ((= exclaim 1) (cond ((equal (car assert) p) (setq assert(cdr assert)) (setq exclaim 0))
;                                           ((not(equal (car assert) p)) )))  
;                )  
;            )
;            ((listp (car assert))
;                (cond
;                    ((equal (caar assert) '?)(cond ((= exclaim 0)(set (cadar assert) p) (setq assert(cdr assert)))
;                                                   ((= exclaim 1)(setq namewaitlist(cons (cadar assert) namewaitlist))(setq namewaitcount(1+namewaitcount))(setq assert(cdr assert))))
;                    ((equal (caar assert) '!)(setq exclaim 1) (setq assert(cdr assert))(setq waitlist (cons p waitlist)))
;               )
;           )
;        )
;    )
;    (cond ((or (not (null assert)) (equal err 1)) (setq result nil)); either assert not finish or err happen return nil
;    )
;    result
;)


   
    
    