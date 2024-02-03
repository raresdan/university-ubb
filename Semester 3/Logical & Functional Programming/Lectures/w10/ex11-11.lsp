(DEFUN COLUMNS (L) 
  (COND 
    ((NULL (CAR L)) NIL) 
    (T (CONS (MAPCAR #'CAR L) (COLUMNS (MAPCAR #'CDR L)))) 
  )
) 
 
(DEFUN PR (L1 L2) 
  (COND 
     ((NULL (CAR L1)) NIL) 
     (T (CONS 
          (MAPCAR 
            #'(LAMBDA (L) (APPLY #'+ (MAPCAR #'* (CAR L1) L)) )
            L2
          ) 
          (PR (CDR L1) L2)
       )
    ) 
  )
) 
 
(DEFUN PRODUCT (L1 L2) 
  (PR L1 (COLUMNS L2))
)
