LEXER_SRC = lexer/expander.c lexer/expand_params.c lexer/expand_quote.c lexer/expand_word.c lexer/lexer.c lexer/lexer_handler.c lexer/lexer_utils.c lexer/tk_operation.c lexer/token_error.c lexer/token_error_utils.c

PARSER_SRC = parser/cmd.c parser/cmd_creation.c parser/cmd_operation.c parser/cmd_operation_utils.c.c parser/expand_heredoc.c parser/parser.c  parser/parser_utils.c parser/process_heredoc.c parser/process_redir.c parser/redirection_utils.c parser/utils.c

EXECUTOR_SRC = executor/exec_builtin.c executor/exec_cmd.c executor/exec_pipeline.c executor/exec_pipeline_utils.c executor/executor.c  executor/executor_utils.c executor/get_path.c executor/get_path_utils.c

BUILTIN_SRC = builtin/builtin.c builtin/buildin_utils.c   builtin/chdir.c builtin/env_utils.c builtin/env_utils2.c builtin/env.c builtin/export.c  builtin/get_envp.c builtin/prompt.c builtin/unset.c builtin/ft_strncpy.c builtin/exit.c builtin/export_unset_utils.c

SRCS = main.c utils/process_loop.c  ${LEXER_SRC}  ${PARSER_SRC} ${BUILTIN_SRC} ${EXECUTOR_SRC}

OBJS = ${SRCS:.c=.o}

NAME = minishell

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror #-g

LIBFT_PATH = ./libft

LIBFT_LIB = libft.a

LIBFT = ${LIBFT_PATH}/${LIBFT_LIB}

${NAME}:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} ${SRCS} ${LIBFT} -o ${NAME} -lreadline

${LIBFT}:
			make -C ${LIBFT_PATH} bonus
			cp ${LIBFT} .

all:		${NAME}

val:		${NAME}
			valgrind --suppressions=.readline.supp --leak-check=full --show-leak-kinds=all -s ./${NAME}

vals:		${NAME}
			valgrind --suppressions=.readline.supp --leak-check=full --show-leak-kinds=all  --trace-children=yes -s ./${NAME}

clean:
			${RM} ${OBJS}
			make -C ${LIBFT_PATH} clean

fclean:		clean
			${RM} ${LIBFT_LIB}
			${RM} ${NAME}
			make -C ${LIBFT_PATH} fclean

re:			fclean all

.phony:		fclean all clean re
