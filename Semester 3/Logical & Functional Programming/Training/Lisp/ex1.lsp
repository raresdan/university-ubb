; A non-linear list is given. Return the set of all numerical atoms
; (1 3 4 (A 3(2 3 ) B) 3 4) -> (1 2 3 4) - not necessarly in this order

(defun extract-numeric-atoms (lst)
    (cond ((null lst) nil)
                ((numberp (car lst))
                 (cons (car lst) (extract-numeric-atoms (cdr lst))))
                ((atom (car lst))
                 (extract-numeric-atoms (cdr lst)))
                (t
                 (append (extract-numeric-atoms (car lst))
                                 (extract-numeric-atoms (cdr lst))))))

(defun remove-duplicate-values (lst)
    (cond   ((null lst) nil)
            ((member (car lst) (cdr lst)) (remove-duplicate-values (cdr lst)))
            (t (cons (car lst) (remove-duplicate-values (cdr lst))))))


(print (remove-duplicate-values (extract-numeric-atoms '(1 3 4 (A 3 (2 C 7 3 ) B) 3 4))))
