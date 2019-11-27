all: file_control process_fork thread process_synchronisation file_lock bankers buddy

file_control: copy move remove list
    
copy: copy.c
	gcc copy.c -o copy
    
move: move.c
	gcc move.c -o move
    
remove: remove.c 
	gcc remove.c -o remove

list: list.c
	gcc list.c -o list
   
process_fork: fork    
    
fork: fork.c prog1 prog2
	gcc fork.c -o fork        
    
prog1:      	
	gcc prog1.c -o prog1

prog2: prog2.c
	gcc prog2.c -o prog2

thread: thread.c 
	gcc thread.c -lpthread -o thread
    
process_synchronisation: dinphil procon readwrite

dinphil: dinphil.c
	gcc dinphil.c -lpthread -o dinphil
        
procon: procon.c
	gcc procon.c -lpthread -o procon
 
readwrite: readwrite.c
	gcc readwrite.c -lpthread -o readwrite

file_lock: filelock.c
	gcc filelock.c -o filelock

bankers: bankers.c
	gcc bankers.c -o bankers      
    
buddy: buddy.c
	gcc buddy.c -o buddy                  
    
clean_file_control: 
	rm copy move remove list
    
clean_process_synchronisation:
	rm dinphil procon readwrite
 
clean_process_fork:
	rm fork prog1 prog2
    
clean: clean_file_control clean_process_synchronisation clean_process_fork
	rm thread filelock bankers buddy         
            
