(DEFUN VERIF (L) 
   (DEFUN MYAND (L) 
      (COND 
         ((NULL L) T) 
         ((NOT (CAR L)) NIL) 
         (T (MYAND (CDR L))) 
      ) 
   ) 
   (COND 
      ((ATOM L) T) 
      ((NOT (EVEN L)) NIL) 
      (T (FUNCALL #'MYAND (MAPCAR #'VERIF L))) 
   ) 
) 
