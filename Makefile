COM_OBJS	=	common_functions.o	screen_manager.o
AIO_OBJS	=	data_passer.o	breed.o
DEPS	=	structs.h	common_functions.h	data_passer.h	breed.h	screen_manager.h

game:	run-jump.o	$(COM_OBJS)	$(DEPS)
	g++	run-jump.o	$(COM_OBJS)	-o	run-jump	-lncurses

ai:	run-jump-ai.o	$(AIO_OBJS)	$(COM_OBJS)	$(DEPS)
	g++	run-jump-ai.o	$(AIO_OBJS)	$(COM_OBJS)	-o	run-jump-ai	-lncurses

%.o:	%.cpp	$(DEPS)
	g++	-c	$<

.PHONY:	clean
clean:	gameclean	aiclean

.PHONY:	gameclean
gameclean:
	rm	-f	run-jump
	rm	-f	run-jump.o	$(COM_OBJS)

.PHONY:	aiclean
aiclean:
	rm	-f	run-jump-ai
	rm	-f	run-jump-ai.o	$(AIO_OBJS)	$(COM_OBJS)
	rm	-f	last_gen.bin	level.bin	mcs.bin	scores.txt	top.txt
