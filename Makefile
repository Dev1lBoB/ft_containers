ORIG	= original

COPY	= replica

SRC_ORIG	= orig.cpp
SRC_COPY	= copy.cpp

CLANG		= clang++

FLAGS		= -Wall -Wextra -Werror -std=c++98 -I.

all:	${COPY} ${ORIG}

${COPY}: ${SRC_COPY}
	${CLANG} ${FLAGS} ${SRC_COPY}  -o ${COPY}

${ORIG}: ${SRC_ORIG}
	${CLANG} ${FLAGS} ${SRC_ORIG}  -o ${ORIG}

clean:

fclean: clean
	rm -rf ${COPY} ${ORIG}

re: fclean all

.PHONY: all clean fclean re
