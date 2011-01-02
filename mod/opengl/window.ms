; Copyright (C) 2009, Chris Double.
;
; This library is free software; you can redistribute it and/or modify it
; under the terms of the GNU Lesser General Public License, version 2.1
; as published by the Free Software Foundation.
;
; This library is distributed in the hope that it will be useful, but WITHOUT
; ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
; FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
; for more details.
;
; You should have received a copy of the GNU Lesser General Public License
; along with this library; if not, write to the Free Software Foundation,
; Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

(module "opengl/window")
(import "lib/object")

(define-class main-window <object>
  (make-main-window handle)
  main-window?
  (handle main-window-handle))

(define *windows* (make-dict))

(define (register-window mw)
  (dict-set! *windows* (window-handle (main-window-handle mw)) mw))

(define (find-window handle)
  (dict-ref *windows* handle))

(define *display* #f)

(define (display)
  (or *display* (set! *display* (open-display))))

(define (handle-event window event)
  (print "generic handle-event")
  #f)

(define (process-event display)
  (define event (display-next-event display))
  (handle-event (find-window (event-window-handle event)) event))

(define (process-all-events)
  (when (> (display-events-pending (display)) 0)
	(process-event (display))
	(pause)
	(process-all-events)))

(define (process-one-event)
  (when (> (display-events-pending (display)) 0)
	(process-event (display))))

(define (start-event-server)
  (define d (display))
  (define service (display-service d))
  (define (server)
    (forever
     (print "hello\n")
     (process-one-event)
     (print "there\n")
     (wait service)))

  (spawn server))

(define-class test1 <main-window> (make-test1 handle) test1? (handle main-window-handle))
(define-class test2 <main-window> (make-test2 handle) test2? (handle main-window-handle))


(define (handle-event (<test1> window) event)
  (print "test1 handle-event")
  #f)

(define (handle-event (<test2> window) event)
  (print "test2 handle-event")
  #f)

(define (test1-window)
  (define w (create-window (display) "hello" 0 0 500 500))
  (define mw (make-test1 w))
  (register-window mw)
  (process-all-events)
  mw)

(define (test2-window)
  (define w (create-window (display) "hello" 0 0 500 500))
  (define mw (make-test2 w))
  (register-window mw)
  (process-all-events)
  mw)

(export display process-all-events start-event-server test-window *windows* register-window find-window handle-event test1-window test2-window)
