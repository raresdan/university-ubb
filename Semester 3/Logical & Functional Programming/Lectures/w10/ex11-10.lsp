; a. recursive, without MAP functions 
 
(DEFUN INVERS1 (L) 
  (COND 
    ((NULL L) NIL) 
    ((ATOM (CAR L)) (APPEND (INVERS1 (CDR L)) (LIST (CAR L)))) 
     (T (APPEND (INVERS1 (CDR L)) (INVERS1 (CAR L)))) 
  ) 
) 
 
b. using MAP functions 
 
(DEFUN INVERS2 (L) 
  (COND 
     ((ATOM L) (LIST L)) 
      (T (MAPCAN #'INVERS2 (REVERSE L))) 
   ) 
) 
