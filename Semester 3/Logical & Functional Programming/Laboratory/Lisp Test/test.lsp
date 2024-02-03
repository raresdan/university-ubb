; problem 1:  map as walk 
; double the numerical values in a list at any level 
; test:  
; > (double '(1 2 a (3 4) b c))  
; (2 4 A (6 8) B C) 

(defun double (lst)
     (cond  ((null lst) nil)
            ((listp (car lst)) (cons (double (car lst)) (double (cdr lst))))
            ((numberp (car lst))  (cons (* 2 (car lst)) (double (cdr lst))))
            (t (cons (car lst) (double (cdr lst))))))

(print (double '(1 2 a (3 4) b c)))

; problem 4: workers 
; given a list of length n of sublists representing work items and a list of length n 
; of functions representing workers obtain the list of results of performing the work 
; by each worker on their corresponding work item 
; test: 
; > (work '(+ * -) '((2 3) (1 2) (7 5 1))) 
; (5 2 1) 

(defun work (operations items)
  (mapcar #'apply operations items))

(print (work '(+ * -) '((2 3) (1 2) (7 5 1))))