NAME_LIB = libmx.a

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: create_obj copy LIBMX create_lib remove

create_obj:
	rm -rf obj
	mkdir obj

LIBMX:
	clang $(FLAGS) -c obj/*.c
	mv *.o obj/

copy:
	cp src/*.c obj
	cp inc/*.h obj

remove:
	rm obj/*.c
	rm obj/*.h

create_lib:
	ar -rc $(NAME_LIB) obj/*.o
	ranlib $(NAME_LIB)

clean:
	rm -rf obj

uninstall:
	rm -rf obj
	rm -rf $(NAME_LIB)

reinstall:
	make uninstall
	make
