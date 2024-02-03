(DEFUN MYREVERSE_1 (L)
  (COND 
    ((ATOM L) L)
    (T (APPEND (MYREVERSE_1 (CDR L)) (LIST (CAR L)))) 
  )
)

(DEFUN MYREVERSE_AUX (L Col)
  (COND 
    ((NULL L) Col)
    (T (MYREVERSE_AUX (CDR L) (CONS (CAR L) Col))) 
  )
)

(DEFUN MYREVERSE_2 (L)  
  (MYREVERSE_AUX  L ()) 
)
