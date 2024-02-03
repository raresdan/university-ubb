(DEFUN LG (L) 
  (COND 
      ((ATOM L) 1) 
      (T (APPLY #'+ (MAPCAR 'LG L))) 
   ) 
) 
