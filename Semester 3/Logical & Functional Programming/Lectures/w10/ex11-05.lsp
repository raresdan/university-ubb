(DEFUN ATOMI1 (L) 
   (COND 
    ((ATOM L) (LIST L)) 
    (T (MAPCAN #'ATOMI1 L)) 
  ) 
)  

;Remark: The same requirement could be solved using the MAPCAR function. 
 
(DEFUN ATOMI2 (L) 
   (COND 
      ((ATOM L) (LIST L)) 
      (T (APPLY #'APPEND (MAPCAR #'ATOMI2 L))) 
   ) 
) 
