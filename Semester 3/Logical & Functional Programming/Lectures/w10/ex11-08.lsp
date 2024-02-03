(DEFUN NR (L) 
   (COND 
      ((NULL (CDR L)) 1) 
      (T (+ 1 (APPLY #'+ (MAPCAR #'NR (CDR L)))) 
   ) 
) 
