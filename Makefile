NAME = philo
CFLAGS = -g3 -Wall -Wextra -Werror -pthread
SRCS = main.c\
	   parsing/parsing.c\
	   parsing/clean_data.c\
	   parsing/init_extra_data.c\
	   tools/utils_0.c\
	   tools/utils_1.c\
	   tools/utils_2.c\
	   routine/philo_routine.c\
	   routine/monitor_routine.c\
	   routine/start_dinner.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ 
clean:
		rm -rf $(OBJS)
fclean: clean
		rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
