  ä  
	    
	    
	    
	    
	     	    D
	     1
	     3B
	    
	            M
	       Y
	         f
	           module mosref/prop/address import mosref/node mosref/parse mosref/format register-prop address 
ÿ addr þAssigns an IPv4 or DNS address to the node. This address will be used when a drone attempts to affiliate with the node.

Drones resolve these addresses at initialization, so any DNS addresses must be valid for resolution for the drone's host environment. is-valid-address? string? integer? send-err Expected DNS or IPv4 address,  format . format-address-val format-addr 	node-addr find-node-prop set-node-addr! set-node-prop!