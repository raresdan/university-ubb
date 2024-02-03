(DEFUN F (L)
  (COND
    ((ATOM L) NIL)
    (T T)
  )
)

(SETQ L '(1 (2) (3 (4)))

(REMOVE-IF 'F L)
