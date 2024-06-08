import sys

class Position:
    symbols = [" ", "╴", "╷", "┐", "╶", "─", "┌", "┬", "╵", "┘", "│", "┤",
               "└", "┴", "├", "┼"]

    def __init__(self, north = False, east = False, south = False, west = False, exit = False):
        self.north = north
        self.east = east
        self.south = south
        self.west = west
        self.exit = exit


def can_escape(maze):
    height = len(maze)
    width = len(maze[0])
    if height == 1 and width == 1:
        return False
    neighbourhood = []
    for x in range(height):
        neighbourhood.append([])
    for check_row in range(height):
        for check_col in range(width):
            neighbours = []
            if maze[check_row][check_col].north:
                neighbours.append("north")
            if maze[check_row][check_col].east:
                neighbours.append("east")
            if maze[check_row][check_col].south:
                neighbours.append("south")
            if maze[check_row][check_col].west:
                neighbours.append("west")
            neighbourhood[check_row].append(neighbours)
    pending_moves = {}
    for x in range(height):
        for y in range(width):
            pending_moves[x, y] = neighbourhood [x][y]

    x = 0
    y = 0
    previous_move = None
    all_steps = []
    while not maze[x][y].exit:

        if len(pending_moves[x, y]) == 0:
            if len(all_steps) != 0:
                match all_steps[-1]:
                    case "north":
                        x += 1
                    case "east":
                        y -= 1
                    case "south":
                        x -= 1
                    case "west":
                        y += 1
                all_steps.pop(-1)

                if len(pending_moves[x, y]) == 0:
                    if not len(all_steps) == 0:
                        previous_move = all_steps[-1]
                    else:
                        return False
                else:
                    previous_move = pending_moves[x, y][0]
            else:
                return False
        else:
            previous_move = pending_moves[x, y][0]
            pending_moves[x, y].pop(0)
            all_steps.append(previous_move)
            match previous_move:
                case "north":
                    x -= 1
                case "east":
                    y += 1
                case "south":
                    x += 1
                case "west":
                    y -= 1

            if previous_move == "north" and "south" in pending_moves[x,y]:
                pending_moves[x, y].remove("south")
            if previous_move == "east" and "west" in pending_moves[x, y]:
                pending_moves[x,y].remove("west")
            if previous_move == "south" and "north" in pending_moves[x, y]:
                pending_moves[x, y].remove("north")
            if previous_move == "west" and "east" in pending_moves[x, y]:
                pending_moves[x,y].remove("east")
    return True

def escape_route(maze):
    height = len(maze)
    width = len(maze[0])
    neighbourhood = []
    for x in range(height):
        neighbourhood.append([])
    for check_row in range(height):
        for check_col in range(width):
            neighbours = []
            if maze[check_row][check_col].north:
                neighbours.append("north")
            if maze[check_row][check_col].east:
                neighbours.append("east")
            if maze[check_row][check_col].south:
                neighbours.append("south")
            if maze[check_row][check_col].west:
                neighbours.append("west")
            neighbourhood[check_row].append(neighbours)
    pending_moves = {}
    for x in range (height):
        for y in range(width):
            pending_moves[x, y] = neighbourhood[x][y]
    x = 0
    y = 0
    previous_move = None
    all_steps = []
    while not maze [x][y].exit:
        if len(pending_moves[x, y]) == 0:
            if len(all_steps) != 0:
                match all_steps[-1]:
                    case "north":
                        x += 1
                    case "east":
                        y -= 1
                    case "south":
                        x -= 1
                    case "west":
                        y += 1
                all_steps.pop(-1)
                if len(pending_moves[x, y]) == 0:
                    if not len(all_steps) == 0:
                        previous_move = all_steps[-1]
                    else:
                        return False
                else:
                    previous_move = pending_moves[x, y][0]
            else:
                return False
        else:
            previous_move = pending_moves[x, y][0]
            pending_moves[x, y].pop(0)
            all_steps.append(previous_move)
            match previous_move:
                case "north":
                    x -= 1
                case "east":
                    y += 1
                case "south":
                    x += 1
                case "west":
                    y -= 1
            if previous_move == "north" and "south" in pending_moves[x, y]:
                pending_moves[x, y].remove("south")
            if previous_move == "east" and "west" in pending_moves[x, y]:
                pending_moves[x, y].remove("west")
            if previous_move == "south" and "north" in pending_moves[x, y]:
                pending_moves[x, y].remove("north")
            if previous_move == "west" and "east" in pending_moves[x, y]:
                pending_moves[x, y].remove("east")
    return all_steps
        
