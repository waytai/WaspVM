 l_� �
	    
	    
	    
	    
	     	 
	 
           ����
	  
	  � �   � �   � �
	  � �   � �
	  � �   � �
	  � �  � �
	  � �
	  � � � �� ��g�m
	    
	  � � � �
	  � � � � � �	 ����
	    ��
	  � � � �	 � � � � � � � �
  ����
	   ! 
	 " 
	 # ��    $ ��
	 % � �� �
 
	 &  ' 
	 ( � � � � � �	 � � � �
	 ) � �  * � � 
	 + � � � �   +����

	  � �  � �
	 , � � � �
	 - � � � �
	 . � � � �
	 &  / 
	 " � �   0 
	 1  2��� ��� � �� � 3�{� �  4�7��
	 5 � �  
	 &  6 ��  7 
	 8 
	 9 � �     $ ��C
	 : ��  �� �� �� �� �G�H ;�j��
	 5 � �  
	 &  < ��  = 
	 8 
	 9 � �     $ ��y
	 > �� 
	 ? ��  ��� �� ���
� � �|
	 8 � �  � �
	 &  @ ��  A 
	 B � �   $ 
	 C �� � 
	 D �� 
	 E 	 F 	 G � �   + H� � 
	 U 
	 P 	 V � �   :�a��
	 W � �  ��  � �
	 8 � � � �
	 # � � � �
	 X � �
	 Y � �  � �
	 O 
	 P � � � �  � � 
	 K � � � �
	 O  T � � 
	 Z � � � 
	 [ 
	 8 � �   Q �W
	 ? � � � �
	 8 � � � �
	 # � � � �
	 \ � � � � � �� ��V
	 P � � 
	 ] � �  
	 ^ � �  �V�W
	 _  `  a � �  
	 b 
	 c  :  �u
	 c  : �v	 d  :
	 U 
	 P 	 e � �   :����
	  � �  � �
	 L � � � � � �
	 P 
	 R � �  
	 f � �  
	 g � �   
	 b 
	 c  :  ��
	 c  : ��	 d  : h� �
	 U 
	 P 	 V �   ���

	 W � �  �� � �
	 8 � � � �
	 # � � � �
	 O � � � � 
	 K � � � �
	 O  T � � 
	 j � � �� ��
	 _  `  k � �  
	 b 
	 c    �0
	 c   �1	 d  
	 U 
	 P 	 e �   �H��
	 i � �  
	 b 
	 c    �\
	 c   �]	 d   module mosref/cmd/drone import mosref/shell mosref/node mosref/listener bind-mosref-cmd drone drone <file> <id> <platform> string-append 9Creates a new drone executable for the specified platform 5 and places it at file, then spawns a listener on the : current node.  When the drone connects to the listener, a 5 the drone will be bound to the specified identifier. 	cmd-drone req-path mosref-shell-console  for drone executable req-term  drone identifier  drone platform mosref-shell-node make-console-ecdh 	node-addr send-err 1 node address unknown, use set addr to assign one 	node-port node-make-sin 	anon-fn-5 Could not compile drone. make-drone-exe 	anon-fn-8 Could not write file  format cadr . put-node-file 	send-line Drone executable created. make-drone-node set-node-prop! platform spawn-drone-listener node-id drone-node-sin drone-node-ecdh Listening for drone on  ... spawn 
anon-fn-11 attempt-affiliation 
anon-fn-15 	traceback ERROR: Listener for  failed,  car 
error-info node-sin-listen 
anon-fn-20 ERROR: Affilation of  	 failed,  console-affiliation cdr Drone   affiliated from address  format-ipv4 set-node-online! set-node-bridge! spawn-endpoint console-endpoint console-broken �� �
	    
	   I 	 J� � 
	 K � �
	 L � �� �
	 M � �  � �
	 N � � � � 
	 O 
	 P  Q 
	 R � �  
	 S � �   
	 O  T  mosref/patch *drone-bridge* wait mosref-sin-listen make-reserved-lane patch2 send list connect 	peer-addr lane-tag close make-multimethod <drone-node> spawn-node-program make-channel drone-node-bridge pair? eq? find-reserved-lane 	lane-xmit 	lane-recv error mosref ,Bogus message while waiting for session lane 	function? 
get-global refuse-method <console-node> input output #� � 
	    
	 O 
	 i 
	 K    make-mosref-sin string? =Bogus message while waiting for service identification number