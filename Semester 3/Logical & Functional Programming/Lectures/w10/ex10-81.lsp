(DEFUN MODIF (L)
  (COND 
    ((NUMBERP L) (* 2 L))   ; operate on digital atoms
    ((ATOM L) L)            ; operate on non-numerical atoms
    (T (MAPCAR #'MODIF L))  ; operate recursively 
  )
)
