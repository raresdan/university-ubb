(DEFUN LGM (L)
  (COND 
    ((ATOM L) 0)
    (T (MAX (LENGTH L) (APPLY #'MAX (MAPCAR #'LGM L))))
  )
)
