(DEFUN AD (L) 
   (COND 
      ((NULL (CDR L)) 0) 
      (T (+ 1 (APPLY #'MAX (MAPCAR #'AD (CDR L)))) 
   ) 
) 
