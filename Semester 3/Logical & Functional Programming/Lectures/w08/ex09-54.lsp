(DEFUN INS (E N L)
  (COND
    ((= N 1) (CONS E L))
    (T (CONS (CAR L) (INS E (- N 1) (CDR L))))
  )
)

(DEFUN INSERT (E N L)
  (COND
    ((= N 0) NIL)
    (T (CONS (INS E N L) (INSERT E (- N 1) L)))
  )
)

(DEFUN INSERTION (E L)
  (INSERT E  (+ (LENGTH L) 1)  L)
)

(defun insertall (E L)
  (cond 
    ((null L) ())
    (T (append (insertion E (car L)) (insertall E (cdr L))))
  )
)
  
(defun permutations (L)
  (cond
    ((null L) '(()))
    (T (insertall (car L) (permutations (cdr L))))
  )
)