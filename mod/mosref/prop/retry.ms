; Copyright (C) 2010, Chris Double <chris.double@double.co.nz>
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

(module "mosref/prop/retry")

(import "mosref/node")
(import "mosref/parse")
(import "mosref/format")

(define-prop (retry)
             doc: "Assigns a time in milliseconds that a drone will wait before"
	          " retrying a connection attempt if a connection fails."
                  "\n\n"
		  "If this property is not set then the drone will fail"
		  " immediately instead of retrying."
                  "\n\n"

             valid: (unless (or (string? value)
                                (integer? value))
                      (send-err "Expected a time in milliseconds, not " 
                                (format value) "."))
                    (parse-timeout value))
            
(define (node-retry node) 
  (find-node-prop node 'retry))

(define (set-node-retry! node value) (set-node-retry! node 'retry value))

(define (node-has-retry? node) (has-node-prop? node 'retry))

(export node-retry set-node-retry! node-has-retry?)
