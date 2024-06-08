import sys

class Position:
    symbols = [" ", "╴", "╷", "┐", "╶", "─", "┌", "┬", "╵", "┘", "│", "┤",
               "└", "┴", "├", "┼"]

    def __init__(self, north, east, south, west, exit):
        self.north = north
        self.east = east
        self.south = south
        self.west = west
        self.exit = exit


    def has_direction(self, direction):
        match direction:
            case "north":
                return self.north
            case "east":
                return self.east
            case "south":
                return self.south
            case "west":
                return self.west
            case _:
                return False

    def is_exit(self):
        return self.exit

class Maze:

    def __init__(self, height, width):
        self.height = height
        self.width = width
        self.map = {}

    def get_position(self, x, y):
        try:
            return self.map[x,y]
        except:
            return None

    def set_position(self, x, y, position):
        self.map[x,y] = position

    def get_height(self):
        return self.height

    def get_width(self):
        return self.width

def read_maze(filename):
    f = open(filename, "r")
    lines = f.readlines()
    height = len(lines)
    if height != 0 and height != 1:
        width = len(lines[0]) - 1
    elif height == 1:
        width = 1
    else:
        width = 0
    map = Maze(height, width)
    for x, w in enumerate(lines):
        for y, z in enumerate(lines[x]):
            if z != "\n":
                info = str(bin(Position.symbols.index(z)).replace("0b", ""))
                while len(info) != 4:
                    info = "0" + info
                set_north = False
                set_east = False
                set_south = False
                set_west = False
                exit = False
                if info[0] == "1":
                    set_north = True
                if info[1] == "1":
                    set_east = True
                if info[2] == "1":
                    set_south = True
                if info[3] == "1":
                    set_west = True
                if x == 0 and set_north == True:
                    exit = True
                if x == height - 1 and set_south == True:
                    exit = True
                if y == 0 and set_west == True:
                    exit = True
                if y == width - 1 and set_east == True:
                    exit = True
                if info != "0000":
                    if height == 0 and width == 0:
                        exit = True
                    if height ==1 and width ==1:
                        exit = True
                pos = Position(set_north, set_east, set_south, set_west, exit)
                map.set_position(x, y, pos)
    f.close()
    return map
if __name__ == "__main__":
    maze = read_maze("test_maze.txt")
    print("width: " + str(maze.get_width()))
    print("height: " + str(maze.get_height()))
    print(maze.get_position(0, 0).is_exit())
    pass
