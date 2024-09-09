SRCS = main.c lexer/char_handler.c lexer/lexer_utils.c lexer/lexer.c  lexer/expander.c  lexer/error_checker.c input/input.c parser/process_cmd.c parser/parser_utils.c parser/parser.c  parser/process_heredoc.c executor/executor.c executor/executor_utils.c builtin/builtin.c

BONUS_SRCS = main.c

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BONUS = minishell_bonus

NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -g#-Wall -Wextra -Werror #-g

LIBFT_PATH = ./libft

LIBFT_LIB = libft.a

LIBFT = ${LIBFT_PATH}/${LIBFT_LIB}

${NAME}:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${SRCS} ${LIBFT} -o ${NAME}

${LIBFT}:
			make -C ${LIBFT_PATH} bonus
			cp ${LIBFT} .

${BONUS}:	${BONUS_OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${BONUS_SRCS} ${LIBFT} -o ${BONUS}

all:		${NAME}

bonus:		${BONUS}

clean:
			${RM} ${OBJS} ${BONUS_OBJS}
			make -C ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${LIBFT_LIB}
			${RM} ${NAME} ${BONUS}
			make -C ${LIBFT_PATH} fclean

re:			fclean all

.phony:		fclean all clean re
