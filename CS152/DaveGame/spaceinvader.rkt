;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname spaceinvaders) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp") (lib "batch-io.rkt" "teachpack" "2htdp")))))
; A SIGS (short for “space invader game state”) is one of:
; – (make-aim UFO Tank)
; – (make-fired UFO Tank Missile)
(define-struct aim (UFO tank))
(define-struct fired (UFO tank missile))

; A UFO is Posn.
; interp. (make-posn x y) is the UFO's current location
 
(define-struct tank (pos vel))
; A Tank is (make-tank Number Number).
; interp. (make-tank x dx) means the tank is at (x ,HEIGHT)
;   and that it moves dx pixels per clock tick
 
; A Missile is Posn.
; interp. (make-posn x y) is the missile's current location


; Space invader game with UFO, tank and missile
;   Properties of the background
;    Constants: width, height for blue sky background
;               dimensions of ground layer at bottom
;               tree and bush and cloud graphics definitions
;               a definition for the whole of these parts
;
;   Properties of the tank
;    Constants: rendered as a grey square
;               moves at a fixed speed
;    Fields: x pos
;            direction
;
;   Properties of the UFO
;    moves slightly left and right at random
;    Constants: rendered as a circle and rectangle
;               moves down at a fixed speed
;    Fields: posn
;
;   Properties of the missile
;    When it collides with the UFO, ya fookin win
;    Constants: rendered as a yellow triangle
;               moves up at least twice as fast as the UFO moves down
;    Fields: posn
;            status
;                - false - isn't drawn
;                - "created" - references tank for x pos; initializes y pos
;                - "moving" - references itself for x pos; increments y pos

; Background constants
(define SCENE-WIDTH 400)
(define SCENE-HEIGHT 300)
(define GROUND-HEIGHT 20)

(define IMG-TREE
  (underlay/xy (circle 10 'solid 'green)
               9 15
               (rectangle 2 20 'solid 'brown)))
(define Y-TREE (- SCENE-HEIGHT GROUND-HEIGHT (/ (image-height IMG-TREE) 2)))

(define BUSHPIECE (circle 10 "solid" "darkgreen"))
(define CLOUDPIECE (circle 10 "solid" "white"))

(define IMG-BUSH (overlay/xy BUSHPIECE -10 -10
                             (overlay/xy BUSHPIECE 12 -5
                                         (overlay/xy BUSHPIECE 12 5 BUSHPIECE))))
(define Y-BUSH (- SCENE-HEIGHT GROUND-HEIGHT (/ (image-height IMG-BUSH) 4)))

(define IMG-CLOUD (overlay/xy CLOUDPIECE -10 -10
                             (overlay/xy CLOUDPIECE 12 -5
                                         (overlay/xy CLOUDPIECE 12 5 CLOUDPIECE))))

(define IMG-SKY (rectangle SCENE-WIDTH SCENE-HEIGHT "solid" "lightblue"))
(define IMG-GROUND (rectangle SCENE-WIDTH GROUND-HEIGHT "solid" "darkgray"))

(define BACKGROUND (overlay/align "middle" "bottom" IMG-GROUND IMG-SKY))

(define SCENE (place-image IMG-CLOUD 68 45
               (place-image IMG-BUSH 277 Y-BUSH
                (place-image IMG-TREE
                           91 Y-TREE
                           BACKGROUND))))

; Graphical constants
(define IMG-TANK (rectangle 20 20 "solid" "black"))
(define Y-TANK (- SCENE-HEIGHT GROUND-HEIGHT (/ (image-width IMG-TANK) 2)))

(define IMG-UFO
  (overlay (circle 10 "solid" "silver")
           (rectangle 40 2 "solid" "silver")))

(define IMG-MISSILE (triangle 8 "solid" "red"))

(define MOCKUP (place-image IMG-MISSILE 230 130
                (place-image IMG-UFO 250 40
                 (place-image IMG-TANK (/ SCENE-WIDTH 2) Y-TANK
                            SCENE))))

; Physical constants
(define TANK-SPEED 3)
(define UFO-SPEED 2)
(define MISSILE-SPEED 5)

; Functions

(check-expect (tank-render (make-tank 4 3) SCENE)
              (place-image IMG-TANK 4 Y-TANK SCENE))

; Tank, Image -> Image
; Places a tank on the scene
(define (tank-render t im)
  (place-image IMG-TANK (tank-pos t) Y-TANK im))

(check-expect (UFO-render (make-posn 4 3) SCENE)
              (place-image IMG-UFO 4 3 SCENE))

; Posn, Image -> Image
; Places a UFO on the scene
(define (UFO-render p im)
  (place-image IMG-UFO (posn-x p) (posn-y p) im))

(check-expect (missile-render (make-posn 4 3) SCENE)
              (place-image IMG-MISSILE 4 3 SCENE))

; Posn, Image -> Image
; Places a missile on the scene
(define (missile-render p im)
  (place-image IMG-MISSILE (posn-x p) (posn-y p) im))

(check-expect (si-render (make-aim (make-posn 5 6) (make-tank 4 3)))
              (UFO-render (make-posn 5 6)
                (tank-render (make-tank 4 3) SCENE)))

(check-expect (si-render (make-fired (make-posn 5 6)
                                     (make-tank 4 3)
                                     (make-posn 7 8)))
              (UFO-render (make-posn 5 6)
                (tank-render (make-tank 4 3)
                 (missile-render (make-posn 7 8) SCENE))))

(check-expect (si-render (make-fired (make-posn 250 40)
                         (make-tank (/ SCENE-WIDTH 2) TANK-SPEED)
                         (make-posn 230 130)))
              MOCKUP)

; SIGS -> Image
(define (si-render s)
  (cond
    [(aim? s) (UFO-render (aim-UFO s)
                (tank-render (aim-tank s) SCENE))]
    [(fired? s) (UFO-render (fired-UFO s)
                 (tank-render (fired-tank s)
                  (missile-render (fired-missile s) SCENE)))]))

(define TEST1 (make-fired (make-posn 40 60)
                           (make-tank 30 3)
                           (make-posn 40 60)))

(check-expect (si-collision? TEST1) true)

(check-expect (si-collision?
               (make-fired (make-posn 40 60)
                           (make-tank 30 3)
                           (make-posn 12 40))) false)

(check-expect (si-collisionx+ TEST1)
               (+ 40 (/ (image-width IMG-UFO) 2)))

(check-expect (si-collisionx- TEST1)
               (- 40 (/ (image-width IMG-UFO) 2)))

(check-expect (si-collisiony+ TEST1)
               (+ 60 (/ (image-height IMG-UFO) 2)))

(check-expect (si-collisiony- TEST1)
               (- 60 (/ (image-height IMG-UFO) 2)))

; fired -> number
; Determines the right bound x for a UFO instance
; in a fired struct
(define (si-collisionx+ f)
        (+ (posn-x (fired-UFO f)) (/ (image-width IMG-UFO) 2)))

; fired -> number
; Left bound x for UFO
(define (si-collisionx- f)
  (- (posn-x (fired-UFO f)) (/ (image-width IMG-UFO) 2)))

; fired -> number
; Bottom bound y for UFO
(define (si-collisiony+ f)
  (+ (posn-y (fired-UFO f)) (/ (image-height IMG-UFO) 2)))

; fired -> number
; Top bound y for UFO
(define (si-collisiony- f)
  (- (posn-y (fired-UFO f)) (/ (image-height IMG-UFO) 2)))

; fired -> boolean
; determines whether the center of the missile
; is within the area of the UFO.
; If missile < highestx and > lowestx and
; if missile < highesty and > lowesty
(define (si-collision? f) 
  (and (< (posn-x (fired-missile f)) (si-collisionx+ f))
       (> (posn-x (fired-missile f)) (si-collisionx- f))
       (< (posn-y (fired-missile f)) (si-collisiony+ f))
       (> (posn-y (fired-missile f)) (si-collisiony- f))))

; SIGS -> Boolean
; If the UFO touches the ground, or the missile hits the UFO,
; the game ends.
(define (si-game-over? s)
  (cond
    [(aim? s) (> (posn-y (aim-UFO s)) Y-TANK)]
    [(fired? s) (or (> (posn-y (fired-UFO s)) Y-TANK)
                    (si-collision? s))]))

(check-within (si-move TEST1) (make-fired (make-posn 40 62)
                              (make-tank 33 3)
                              (make-posn 40 55)) 2)

; SIGS -> SIGS
; On-tick function
; Tank moves by velocity increment
; UFO moves down and a small random amount left or right
; Missile moves up and retains its x position
(define (si-move s)
  (cond
    [(aim? s) 
     (make-aim (make-posn
                (+ (- (posn-x (aim-UFO s)) 2)
                   (random 4))
                (+ (posn-y (aim-UFO s))
                      UFO-SPEED))
      (make-tank (+ (tank-pos (aim-tank s))
                    (tank-vel (aim-tank s)))
                 (tank-vel (aim-tank s))))]
    [(fired? s)
     (make-fired (make-posn
                  (+ (- (posn-x (fired-UFO s)) 2)
                     (random 4))
                  (+ (posn-y (fired-UFO s))
                     UFO-SPEED))
      (make-tank (+ (tank-pos (fired-tank s))
                    (tank-vel (fired-tank s)))
                 (tank-vel (fired-tank s)))
      (make-posn (posn-x (fired-missile s))
                 (- (posn-y (fired-missile s))
                    MISSILE-SPEED)))]))

(check-expect (si-control (make-aim (make-posn 39 62)
                                    (make-tank 33 3)) "left")
              (make-aim (make-posn 39 62)
                        (make-tank 33 -3)))

(check-expect (si-control (make-aim (make-posn 39 62)
                                    (make-tank 33 -3)) "right")
              (make-aim (make-posn 39 62)
                        (make-tank 33 3)))

(check-expect (si-control (make-aim (make-posn 39 62)
                                    (make-tank 33 -3)) "right")
              (make-aim (make-posn 39 62)
                        (make-tank 33 3)))

(check-expect (si-control (make-aim (make-posn 39 62)
                                    (make-tank 33 -3)) "a")
              (make-aim (make-posn 39 62)
                        (make-tank 33 -3)))

(check-expect (si-control (make-aim (make-posn 39 62)
                                    (make-tank 33 -3)) " ")
              (make-fired (make-posn 39 62)
                          (make-tank 33 -3)
                          (make-posn 33 Y-TANK)))
; SIGS, KeyEvent -> SIGS
; Key handler function
; Left and right arrows invert the velocity of the tank
; Spacebar fires the missile if it hasn't been fired already.
(define (si-control s ke)
  (cond
    [(and (aim? s) (string=? " " ke))
     (make-fired (aim-UFO s)
                 (aim-tank s)
                 (make-posn (tank-pos (aim-tank s))
                            Y-TANK))]
    [(aim? s)
     (make-aim (aim-UFO s)
               (make-tank (tank-pos (aim-tank s))
                          (cond
                            [(string=? "left" ke) (* -1 TANK-SPEED)]
                            [(string=? "right" ke) TANK-SPEED]
                            [else (tank-vel (aim-tank s))])))]
    [else s]))

; Any value -> Boolean
; Is this a SIGS?
(define (SIGS? s)
  (or (aim? s) (fired? s)))

(define MAIN
  (big-bang (make-aim (make-posn (/ SCENE-WIDTH 2) 0)
                      (make-tank (/ SCENE-WIDTH 2) 3))
            (to-draw si-render)
            (on-tick si-move)
            (on-key si-control)
            (check-with SIGS?)
(stop-when si-game-over?)))