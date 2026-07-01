CC      := gcc
CFLAGS  := -Werror -Wall -Wextra
NAME    := libft.a

# ─── libft ────────────────────────────────────────────────────────────────────
SRCS :=	ft_isascii.c ft_memmove.c ft_strlcat.c \
		ft_strtrim.c ft_atoi.c ft_isdigit.c \
		ft_memset.c ft_strlcpy.c ft_substr.c \
		ft_bzero.c ft_isprint.c ft_strlen.c \
		ft_tolower.c ft_calloc.c ft_memchr.c \
		ft_strchr.c ft_strncmp.c ft_toupper.c \
		ft_isalnum.c ft_memcmp.c ft_strdup.c \
		ft_strnstr.c ft_isalpha.c ft_memcpy.c \
		ft_strjoin.c ft_strrchr.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c

BONUS :=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
		ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
		ft_lstsize_bonus.c

# ─── get_next_line ────────────────────────────────────────────────────────────
GNL_DIR  := get_next_line
GNL_SRCS := $(GNL_DIR)/get_next_line_bonus.c

# ─── ft_printf ────────────────────────────────────────────────────────────────
PRINTF_DIR  := ft_printf
PRINTF_SRCS := $(PRINTF_DIR)/ft_printf.c \
               $(PRINTF_DIR)/ft_printf_utils.c \
               $(PRINTF_DIR)/ft_print_pointer.c \
               $(PRINTF_DIR)/ft_print_hex.c \
               $(PRINTF_DIR)/ft_print_unsigned.c

# ─── objects ──────────────────────────────────────────────────────────────────
OBJECTS        := $(SRCS:.c=.o)
BONUS_OBJECTS  := $(BONUS:.c=.o)
GNL_OBJECTS    := $(GNL_SRCS:.c=.o)
PRINTF_OBJECTS := $(PRINTF_SRCS:.c=.o)

ALL_OBJECTS    := $(OBJECTS) $(BONUS_OBJECTS) $(GNL_OBJECTS) $(PRINTF_OBJECTS)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(ALL_OBJECTS)
	ar -rcs $(NAME) $(ALL_OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@
	
$(BONUS_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -I$(GNL_DIR) -c $< -o $@

$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@

clean:
	rm -f $(ALL_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all