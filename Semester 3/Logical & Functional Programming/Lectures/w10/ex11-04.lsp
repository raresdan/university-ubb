(DEFUN EVEN (L) 
   (COND 
      ((= 0 (MOD (LENGTH L) 2)) T) 
      (T NIL) 
   ) 
) 
 
(DEFUN NR (L) 
   (COND 
      ((ATOM L) 0) 
      ((EVEN L) (+ 1 (APPLY #'+ (MAPCAR #'NR L)))) 
      (T (APPLY #'+ (MAPCAR #'NR L))) 
   ) 
)    
