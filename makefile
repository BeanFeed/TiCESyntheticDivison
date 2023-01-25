# ----------------------------
# Makefile Options
# ----------------------------

NAME = SynDiv
ICON = icon.png
DESCRIPTION = "Does Synthetic Division For You"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
