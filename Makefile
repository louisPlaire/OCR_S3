CC = gcc
CFLAGS = -Wall -Wextra -O2


SRC_DIR = Solver_File
SRC_DIR1 = Neural_Network_File
GTK_DIR = GTK_Interface_File


SRC = $(SRC_DIR)/Solver.c
SRC1 = $(SRC_DIR1)/ReseauNeurone.c
GTK_SRC = $(GTK_DIR)/GTK.c $(GTK_DIR)/Source.c


TARGET = solver
TARGET1 = Reseau
GTK_TARGET = Gtk

GTK_CFLAGS = `pkg-config --cflags gtk4 sdl2`
GTK_LDFLAGS = `pkg-config --libs gtk4 sdl2`

all: solver Reseau Gtk


solver: $(TARGET)
Reseau: $(TARGET1)
Gtk: $(GTK_TARGET)


$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $@ $<

$(GTK_TARGET): $(GTK_SRC)
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ $^ $(GTK_LDFLAGS)

clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(SRC_DIR1)/*.o
	rm -f $(GTK_DIR)/*.o
	rm -f $(TARGET) $(TARGET1) $(GTK_TARGET)

recompile: clean all

.PHONY: all solver Reseau Gtk clean recompile