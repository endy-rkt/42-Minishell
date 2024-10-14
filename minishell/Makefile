LEXER_SRC = lexer/lexer.c lexer/expander_utils_1.c lexer/expander_utils_2.c lexer/expander.c lexer/lexer_utils_1.c lexer/lexer_utils_2.c lexer/lexer_utils_3.c lexer/token_error_utils.c lexer/token_error.c

PARSER_SRC = parser/parser.c parser/cmd_utils_1.c parser/cmd_utils_2.c parser/cmd_utils_3.c parser/cmd.c parser/process_heredoc.c parser/process_heredoc_utils.c parser/process_redir.c

EXECUTOR_SRC = executor/executor.c executor/executor_utils_1.c executor/executor_utils_2.c

BUILTIN_SRC = builtin/builtin.c builtin/buildin_utils.c builtin/buildin_utils2.c builtin/chdir_utils.c builtin/chdir.c builtin/env_utils.c builtin/env_utils2.c builtin/env.c builtin/export.c builtin/export_utils.c builtin/export_utils2.c builtin/get_envp.c builtin/prompt.c builtin/unset.c

SRCS = main.c input/process_loop.c  ${LEXER_SRC}  ${PARSER_SRC} ${BUILTIN_SRC} ${EXECUTOR_SRC}

BONUS_SRCS = main.c

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BONUS = minishell_bonus

NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -g -lbsd#-lreadline -lbsd -Wall -Wextra -Werror #-g

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
