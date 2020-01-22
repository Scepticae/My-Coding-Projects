;Samuel Leonard
;sleonar5
;HW 11
;Functional Programming in Scheme

;Swap Function
(define swap 
	(lambda (x y)
		(cons y x)))

;Average Function with two helper functions
(define sum 
	(lambda (x)
		(cond
			((null? x) 0.0)
			(#t(+(car x)(sum(cdr x)))))))

(define count
	(lambda (x)
		(cond
			((null? x) 0.0)
				(#t(+ 1.0 (count (cdr x)))))))

(define avg
	(lambda (x)
		(/ (sum x) (count x))))
		
;Tail Recursion Function with helper function
(define tail
	(lambda(x minimum)
		(cond
			((null? x) minimum)
			((< (car x) minimum)
				(tail (cdr x)(car x)))
			((> (car x) minimum)
				(tail (cdr x) minimum)))))

(define min
  (lambda (x)
    (cond
      ((null? x) '())
      ((null? (cdr x)) (car x))
      ((tail (cdr x) (car x))))))
			
;Merge Sort with two helper functions
(define merge
	(lambda (x y)
		(cond
			((null? x) y)
			((null? y) x)
			((< (car x) (car y))
				(cons (car x) (merge(cdr x) y)))
			((> (car x) (car y))
				(cons (car y) (merge(cdr y) x))))))

(define mergesorthelper
	(lambda (x left right whichlist?)
		(cond
			((null? x)
				(merge (mergesort left) (mergesort right)))
			((= whichlist? 0)
				(mergesorthelper (cdr x) (cons (car x) left) right 1))
			((= whichlist? 1)
				(mergesorthelper (cdr x) left (cons (car x) right) 0)))))
				
(define mergesort
	(lambda (x)
		(cond
			((null? x) '())
			((null? (cdr x)) x)
			((mergesorthelper x '() '() 0)))))

;Function to allow a user to filter a list
(define filter
	(lambda(x y)
		(cond
			((null? y) '())
			((x (car y))
				(cons (car y) (filter x (cdr y))))
			((filter x (cdr y))))))
			
;Function that returns the individual leafs of a tree
(define fold
	(lambda (fct identity-value sequence)
		(if (null? sequence)
			identity-value
			(fct (car sequence)
				(fold fct identity-value (cdr sequence)))))) 
		
(define fringe
	(lambda (x)
		(cond
			((null? x) '())
			((null? (cdr x)) x)
			((fold append '() (map fringe (cdr x)))))))
			
;Function that prints the fibonacci sequence
(define fib
  (lambda (n)
    (letrec ((fib-helper
		(lambda (f1 f2 i)
		  (if (= i n)
		      f2
		      (fib-helper f2 (+ f1 f2) (+ i 1))))))
	(fib-helper 0 1 0))))
		