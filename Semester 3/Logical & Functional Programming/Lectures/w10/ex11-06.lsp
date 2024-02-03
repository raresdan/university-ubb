(DEFUN ELIM (L) 
   (COND 
      ((AND (ATOM L) (MINUSP L)) NIL) 
      ((ATOM L) (LIST L)) 
    (T (LIST (MAPCAN #'ELIM L))) 
  ) 
) 
 
(DEFUN ELIMIN (L) 
  (CAR (ELIM L)) 
)
