 .?� �   
	     �a� �
	  � �  �
	  	  ���� �	 � ��� �
	 	 � � 
�0��
	    � �  � � ����
	  � �  �<�<
	  � �  � �
	  � �  � � 
	  � �   �p
	  � �  �a
��   �a
	  � �  ��
	  � �  � � ��
	  � �   ��
	  � �  ��
��   ��
	  � �  ��
	  �� ����
��   
	  � �  � � ��
	  � �   ��
	  � �  ��
��   ��
	  � �  ��
	  � �  � � ��
	  � �   ��
�� 
	    � �  ��
	  �� � � 
�� � �  � �
� � � �  	 � � ���
	     � �  
�� � �   
	 ! � � � �
	 " � �� �� ��`
	 #  $�&��
	 %   � �   
	 &  '�9��
	 ( 
	  � �   )   � �  � �
	 * � � � ��U
	 + 
	 , � �  � � �]
	 - � � � �  �` Dwaspc [OPTION] ... [SOURCE-FILE] ...
Compiles Wasp Lisp programs.

OPTIONS:
  -exe <dest-path>       A copy of the virtual machine will be linked to the
                         compiled source files, creating a standalone program.
  -platform <platform>   When used with the -exe flag, specifies which OS
                         and architecture to compile for. 
  -stub <stub-path>      Like -platform, but specifies the exact virtual
                         machine file to use instead of looking up a generic
                         virtual machine in the stubs directory.
 usage import 	lib/build main null? print 
*platform* make-tc 
parse-fail println* WASPC: 
parse-args car cdr string=? -exe Expected file name after -exe. -stub Expected file name after -stub. path-exists? Stub file does not exist. 	-platform %Expected platform ID after -platform. string-begins-with? - string-append Unrecognized option:  tc-add! build-module 
anon-fn-65 BUILD:  tc->list build-modules map 
anon-fn-69 list filter 
anon-fn-71 not core/ write-data-file build-exe-with-stub read-data-file 	build-exe