#lang racket
(require 2htdp/universe)
(require 2htdp/image)
(require picturing-programs)



;;;;;;;;; BRICK ;;;;;;;;;;;;

(define st1 (scale
              7.5
              (color-list->bitmap
               (list (color 255 0 0 255) (color 240 0 0 255) (color 215 0 0 255) (color 180 0 0 255)
                     (color 180 0 0 255) (color 215 0 0 255) (color 240 0 0 255) (color 255 0 0 255))
               8 1)))
(define st2 (underlay/offset st1 0 7.5 st1))
(define BR (underlay/offset (underlay/offset (underlay/offset st2 60 0 st2) 30 30 (underlay/offset st2 60 0 st2)) 15 15
                           (underlay/offset (underlay/offset st2 60 0 st2) 30 30 (underlay/offset st2 60 0 st2))))
(define B (crop 45 0 60 60 BR))


;;;;;;;;;;;; DIAMOND ;;;;;;;;;;;;;;;;;

(define trapezium
  (beside/align "bottom" (flip-horizontal (right-triangle  10 10 "solid" "sky blue"))
            	(beside/align "bottom" (rectangle 20 10 "solid" "skyblue") (right-triangle  10 10 "solid" "sky blue")
                          	)))
(define D
  (overlay (above/align "left" trapezium (triangle/sss 36.0555 36.0555 40 "solid" "sky blue"))
       	(square 60 "solid" "black")))



;;;;;;;;;;;;;;; KEY ;;;;;;;;;;;;;;;;;;

(define ring (overlay (circle 5 "solid" "black") (circle 10 "solid" "gold")))
(define K (overlay (beside/align "middle" (above/align "left" (rectangle 20 5 "solid" "gold") (rectangle 10 5 "solid" "gold")) ring)
                 	(square 60 "solid" "black")))
;;;;;;;;;;;;;;;;;; DOOR ;;;;;;;;;;;;;;;;;

(define R (let ((rec (rectangle 40 10 50 "orange")))
           	(overlay/xy rec -10 -10
                       	(overlay rec
                                	(overlay/xy rec -10 -40 (square 60 "solid" "brown"))))))

;;;;;;;;;;;;;;;;; WATER ;;;;;;;;;;;;;;;;;;;

(define W (let ((rec (rectangle 60 2 150 "indigo")))
            	(overlay/xy rec 0 -5
                        	(overlay/xy rec 0 -17
                                    	(overlay rec
                                             	(overlay/xy rec 0 -41
                                                         	(overlay/xy rec 0 -53 (square 60 "solid" "sky blue"))))))))

;;;;;;;;;;; COIN ;;;;;;;;;;;;;;;;;;;;;;;;

(define C (overlay (circle 12 "outline" "brown") (circle 20 "outline" "brown")
                      (circle 20 "solid" "gold") (square 60 "solid" "black")))

;;;;;;;;;;;;;;;;;;;;;;;;;;EMPTY;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define E (square 60 "solid" "black"))

;;;;;;;;;;;;;;;;WOOD WALL;;;;;;;
(define L (square 60 "solid" "orange"))
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define level1
  (vector (vector B B B B B B B B B B B B B B B B B B B)
          (vector B D E E E E E E E E E E E E E E E D B)
          (vector B E E C E E E C E E E K E E E C E E B)
          (vector B E E B E E E B E E E B E E E B E E B)
          (vector B C E E E C E E E C E E E C E E E C B)
          (vector B B E E E B E E E B E E E B E E E B B)
          (vector B C E E E E E C E E E E C E E C E E B)
          (vector B E E E B B B B E E E E B B B B B E B)
          (vector B E E E E E E E E E E E B R E E E E B)
          (vector B B B B B B B B B B B B B B B B B B B)
))
;(define-syntax for
;  (syntax-rules (:)
;    [(for init : cond : step : statements)
;     (begin
;       init
;       (define (iter)
;         (cond [(condition (begin statements step (iter)))]))
;       (iter))]))


(define (view level)
  (define i 1)
  (define j 1)
  (define vec (vector-ref level1 0))
  (define image (vector-ref vec 0))
  (define (loopr)
    (when (< j 19)
      (begin (set! image
                   (beside/align "top" image (vector-ref vec j)))
             (set! j (add1 j))
             (loopr))))
  (loopr)
  (define (loopi)
    (when (< i 10)
      (begin (define j 1)
             (define vec (vector-ref level i))
             (define img (vector-ref vec 0))
             (define (loopj)
               (when (< j 19)
                 (begin (set! img
                              (beside/align "top" img (vector-ref vec j)))
                        (set! j (add1 j))
                        (loopj))))
             (loopj)
             (set! image (above/align "left" image img))
             (set! i (+ i 1))
             (loopi))))
  (begin (loopi) image))



;(big-bang level1
;    (on-draw view))









































